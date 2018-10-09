#include "FeatureUtils.hpp"
#include <Psapi.h>
#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
#define NOMINMAX
#ifndef M_PI
#define M_PI        3.14159265358979323846    // matches value in gcc v2 math.h
#endif

#define M_PI_F        ((float)(M_PI))    // Shouldn't collide with anything.
#ifndef RAD2DEG
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "../Helpers/math.hpp"

void inline FUtils::SinCos(float radians, float* sine, float* cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}

void FUtils::AngleVectors(const QAngle& angles, Vector* forward)
{
	float sp, sy, cp, cy;

	SinCos(DEG2RAD(angles.yaw), &sy, &cy);
	SinCos(DEG2RAD(angles.pitch), &sp, &cp);

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}




Vector FUtils::CrossProduct(const Vector &a, const Vector &b)
{
	return Vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

void FUtils::VectorAngles(const Vector& forward, Vector& up, QAngle& angles)
{
	Vector left = CrossProduct(up, forward);
	left.NormalizeInPlace();

	float forwardDist = forward.Length2D();

	if (forwardDist > 0.001f)
	{
		angles.pitch = atan2f(-forward.z, forwardDist) * 180 / M_PI;
		angles.yaw = atan2f(forward.y, forward.x) * 180 / M_PI;

		float upZ = (left.y * forward.x) - (left.x * forward.y);
		angles.roll = atan2f(left.z, upZ) * 180 / M_PI;
	}
	else
	{
		angles.pitch = atan2f(-forward.z, forwardDist) * 180 / M_PI;
		angles.yaw = atan2f(-left.x, left.y) * 180 / M_PI;
		angles.roll = 0;
	}
}

float FUtils::RandomFloat(float min, float max)
{
	static auto ranFloat = reinterpret_cast<float(*)(float, float)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomFloat"));
	if (ranFloat)
		return ranFloat(min, max);
	else
		return 0.f;
}

void FUtils::VectorAngles(const Vector& forward, QAngle& angles)
{
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
		angles[1] = 0.0f; //yaw left/right
	}
	else
	{
		angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
		angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

		if (angles[1] > 90)
			angles[1] -= 180;
		else if (angles[1] < 90)
			angles[1] += 180;
		else if (angles[1] == 90)
			angles[1] = 0;
	}

	angles[2] = 0.0f;
}




void FUtils::CalcAngle(Vector src, Vector dst, Vector &angles)
{
	Vector delta = src - dst;
	double hyp = delta.Length2D(); //delta.Length
	angles.y = (atan(delta.y / delta.x) * 57.295779513082f);
	angles.x = (atan(delta.z / hyp) * 57.295779513082f);
	angles[2] = 0.00;

	if (delta.x >= 0.0)
		angles.y += 180.0f;
}




void FUtils::AngleVectors(const QAngle &angles, Vector& forward, Vector& right, Vector& up)
{
	float sr, sp, sy, cr, cp, cy;

	SinCos(DEG2RAD(angles[1]), &sy, &cy);
	SinCos(DEG2RAD(angles[0]), &sp, &cp);
	SinCos(DEG2RAD(angles[2]), &sr, &cr);

	forward.x = (cp * cy);
	forward.y = (cp * sy);
	forward.z = (-sp);
	right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
	right.y = (-1 * sr * sp * sy + -1 * cr *  cy);
	right.z = (-1 * sr * cp);
	up.x = (cr * sp * cy + -sr * -sy);
	up.y = (cr * sp * sy + -sr * cy);
	up.z = (cr * cp);
}

float FUtils::GetFov(const QAngle& viewAngle, const QAngle& aimAngle)
{
	Vector ang, aim;

	AngleVectors(viewAngle, &aim);
	AngleVectors(aimAngle, &ang);

	return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
}



QAngle FUtils::CalcAngle(Vector src, Vector dst)
{
	QAngle angles;
	Vector delta = src - dst;
	VectorAngles(delta, angles);
	delta.Normalized();
	return angles;
}
void FUtils::AttachConsole()
{
	_old_out = GetStdHandle(STD_OUTPUT_HANDLE);
	_old_err = GetStdHandle(STD_ERROR_HANDLE);
	_old_in = GetStdHandle(STD_INPUT_HANDLE);

	::AllocConsole() && ::AttachConsole(GetCurrentProcessId());

	_out = GetStdHandle(STD_OUTPUT_HANDLE);
	_err = GetStdHandle(STD_ERROR_HANDLE);
	_in = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(_out,
		ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);

	SetConsoleMode(_in,
		ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS |
		ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);
}

/*
* @brief Detach console
*
* Detach and destroy the attached console
*/
void FUtils::DetachConsole()
{
	if (_out && _err && _in) {
		FreeConsole();

		if (_old_out)
			SetStdHandle(STD_OUTPUT_HANDLE, _old_out);
		if (_old_err)
			SetStdHandle(STD_ERROR_HANDLE, _old_err);
		if (_old_in)
			SetStdHandle(STD_INPUT_HANDLE, _old_in);
	}
}

/*
* @brief Print to console
*
* Replacement to printf that works with the newly created console
*/
bool FUtils::ConsolePrint(const char* fmt, ...)
{
	if (!_out)
		return false;

	char buf[1024];
	va_list va;

	va_start(va, fmt);
	_vsnprintf_s(buf, 1024, fmt, va);
	va_end(va);

	return !!WriteConsoleA(_out, buf, static_cast<DWORD>(strlen(buf)), nullptr, nullptr);
}

/*
* @brief Blocks execution until a key is pressed on the console window
*
*/
char FUtils::ConsoleReadKey()
{
	if (!_in)
		return false;

	auto key = char{ 0 };
	auto keysread = DWORD{ 0 };

	ReadConsoleA(_in, &key, 1, &keysread, nullptr);

	return key;
}


/*
* @brief Wait for all the given modules to be loaded
*
* @param timeout How long to wait
* @param modules List of modules to wait for
*
* @returns See WaitForSingleObject return values.
*/
int FUtils::WaitForModules(std::int32_t timeout, const std::initializer_list<std::wstring>& modules)
{
	bool signaled[32] = { 0 };
	bool success = false;

	std::uint32_t totalSlept = 0;

	if (timeout == 0) {
		for (auto& mod : modules) {
			if (GetModuleHandleW(std::data(mod)) == NULL)
				return WAIT_TIMEOUT;
		}
		return WAIT_OBJECT_0;
	}

	if (timeout < 0)
		timeout = INT32_MAX;

	while (true) {
		for (auto i = 0u; i < modules.size(); ++i) {
			auto& module = *(modules.begin() + i);
			if (!signaled[i] && GetModuleHandleW(std::data(module)) != NULL) {
				signaled[i] = true;

				//
				// Checks if all modules are signaled
				//
				bool done = true;
				for (auto j = 0u; j < modules.size(); ++j) {
					if (!signaled[j]) {
						done = false;
						break;
					}
				}
				if (done) {
					success = true;
					goto exit;
				}
			}
		}
		if (totalSlept > std::uint32_t(timeout)) {
			break;
		}
		Sleep(10);
		totalSlept += 10;
	}

exit:
	return success ? WAIT_OBJECT_0 : WAIT_TIMEOUT;
}

/*
* @brief Scan for a given byte pattern on a module
*
* @param module    Base of the module to search
* @param signature IDA-style byte array pattern
*
* @returns Address of the first occurence
*/
std::uint8_t* FUtils::PatternScan(void* module, const char* signature)
{
	static auto pattern_to_byte = [](const char* pattern) {
		auto bytes = std::vector<int>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current) {
			if (*current == '?') {
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else {
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	auto dosHeader = (PIMAGE_DOS_HEADER)module;
	auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

	auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto patternBytes = pattern_to_byte(signature);
	auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

	auto s = patternBytes.size();
	auto d = patternBytes.data();

	for (auto i = 0ul; i < sizeOfImage - s; ++i) {
		bool found = true;
		for (auto j = 0ul; j < s; ++j) {
			if (scanBytes[i + j] != d[j] && d[j] != -1) {
				found = false;
				break;
			}
		}
		if (found) {
			return &scanBytes[i];
		}
	}
	return nullptr;
}

bool FUtils::IsEnemy(C_BasePlayer* player)
{
	return player->m_iTeamNum() != g_LocalPlayer->m_iTeamNum();
}





bool FUtils::CanSeePlayer(C_BasePlayer* player)
{
	for (int i = 4; i < 8; i++) {
		Ray_t ray;
		trace_t trace;

		CTraceFilter filter;
		filter.pSkip = g_LocalPlayer;

		auto endpos = player->GetBonePos(i);

		ray.Init(g_LocalPlayer->GetEyePos(), endpos);
		g_EngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &trace);

		if (reinterpret_cast<C_BasePlayer*>(trace.hit_entity) == player)
			return true;
	}
	return false;

}

bool FUtils::LineGoesThroughSmoke(Vector vStartPos, Vector vEndPos)
{
	static auto LineGoesThroughSmokeFn = (bool(__cdecl*)(Vector, Vector))(Utils::PatternScan(GetModuleHandleA("client_panorama.dll"), ("55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0")));
	return LineGoesThroughSmokeFn(vStartPos, vEndPos);
}


bool FUtils::EntityIsInvalid(C_BasePlayer* Entity)
{

	if (!Entity)
		return true;

	if (Entity == g_LocalPlayer)
		return true;
	if (Entity->m_iHealth() <= 0)
		return true;
	if (Entity->IsDormant())
		return true;

	return false;
}

std::unique_ptr<FUtils> f_utils = std::make_unique<FUtils>();