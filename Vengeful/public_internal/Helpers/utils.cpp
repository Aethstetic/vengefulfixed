#include "utils.hpp"
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


#include "../sdk/sdk.hpp"
#include "../sdk/csgostructs.hpp"
#include "math.hpp"

HANDLE _out = NULL, _old_out = NULL;
HANDLE _err = NULL, _old_err = NULL;
HANDLE _in = NULL, _old_in = NULL;

namespace Utils
{
	/*
	* @brief Create console
	*
	* Create and attach a console window to the current process
	*/
	void inline SinCos(float radians, float* sine, float* cosine)
	{
		*sine = sin(radians);
		*cosine = cos(radians);
	}

	void AngleVectors(const QAngle& angles, Vector* forward)
	{
		float sp, sy, cp, cy;

		SinCos(DEG2RAD(angles.yaw), &sy, &cy);
		SinCos(DEG2RAD(angles.pitch), &sp, &cp);

		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}



	DWORD WaitOnModuleHandle(std::string moduleName)
	{
		DWORD ModuleHandle = NULL;
		while (!ModuleHandle)
		{
			ModuleHandle = (DWORD)GetModuleHandle(moduleName.c_str());
			if (!ModuleHandle)
				Sleep(50);
		}
		return ModuleHandle;
	}

	bool bCompare(const BYTE* Data, const BYTE* Mask, const char* szMask)
	{
		for (; *szMask; ++szMask, ++Mask, ++Data)
		{
			if (*szMask == 'x' && *Mask != *Data)
			{
				return false;
			}
		}
		return (*szMask) == 0;
	}
	Vector CrossProduct(const Vector &a, const Vector &b)
	{
		return Vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
	}

	void VectorAngles(const Vector& forward, Vector& up, QAngle& angles)
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

	float RandomFloat(float min, float max)
	{
		static auto ranFloat = reinterpret_cast<float(*)(float, float)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomFloat"));
		if (ranFloat)
			return ranFloat(min, max);
		else
			return 0.f;
	}

	void VectorAngles(const Vector& forward, QAngle& angles)
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


	DWORD FindPattern(std::string moduleName, BYTE* Mask, char* szMask)
	{
		DWORD Address = WaitOnModuleHandle(moduleName.c_str());
		MODULEINFO ModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)Address, &ModInfo, sizeof(MODULEINFO));
		DWORD Length = ModInfo.SizeOfImage;
		for (DWORD c = 0; c < Length; c += 1)
		{
			if (bCompare((BYTE*)(Address + c), Mask, szMask))
			{
				return (DWORD)(Address + c);
			}
		}
		return 0;
	}
	uint64_t FindPatternIDA(const char* szModule, const char* szSignature)
	{
		//CREDITS: learn_more
#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

		MODULEINFO modInfo;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &modInfo, sizeof(MODULEINFO));
		DWORD startAddress = (DWORD)modInfo.lpBaseOfDll;
		DWORD endAddress = startAddress + modInfo.SizeOfImage;
		const char* pat = szSignature;
		DWORD firstMatch = 0;
		for (DWORD pCur = startAddress; pCur < endAddress; pCur++) {
			if (!*pat) return firstMatch;
			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
				if (!firstMatch) firstMatch = pCur;
				if (!pat[2]) return firstMatch;
				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
				else pat += 2;    //one ?
			}
			else {
				pat = szSignature;
				firstMatch = 0;
			}
		}
		return NULL;
	}



	void CalcAngle(Vector src, Vector dst, Vector &angles)
	{
		Vector delta = src - dst;
		double hyp = delta.Length2D(); //delta.Length
		angles.y = (atan(delta.y / delta.x) * 57.295779513082f);
		angles.x = (atan(delta.z / hyp) * 57.295779513082f);
		angles[2] = 0.00;

		if (delta.x >= 0.0)
			angles.y += 180.0f;
	}




	void AngleVectors(const QAngle &angles, Vector& forward, Vector& right, Vector& up)
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

	float GetFov(const QAngle& viewAngle, const QAngle& aimAngle)
	{
		Vector ang, aim;

		AngleVectors(viewAngle, &aim);
		AngleVectors(aimAngle, &ang);

		return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
	}



	QAngle CalcAngle(Vector src, Vector dst)
	{
		QAngle angles;
		Vector delta = src - dst;
		VectorAngles(delta, angles);
		delta.Normalized();
		return angles;
	}
	void AttachConsole()
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
	void DetachConsole()
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
	bool ConsolePrint(const char* fmt, ...)
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
	char ConsoleReadKey()
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
	int WaitForModules(std::int32_t timeout, const std::initializer_list<std::wstring>& modules)
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
	std::uint8_t* PatternScan(void* module, const char* signature)
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


	C_BasePlayer* GetLocalPlayer()
	{
		return reinterpret_cast<C_BasePlayer*>(g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer()));
	}


	DWORD FindPatternV2(std::string moduleName, std::string pattern)
	{
		const char* pat = pattern.c_str();
		DWORD firstMatch = 0;
		DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
		MODULEINFO miModInfo;
		GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
		DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
		for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
		{
			if (!*pat)
				return firstMatch;

			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
			{
				if (!firstMatch)
					firstMatch = pCur;

				if (!pat[2])
					return firstMatch;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else
					pat += 2; //one ?
			}
			else
			{
				pat = pattern.c_str();
				firstMatch = 0;
			}
		}
		return NULL;
	}

	void TraceLine(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, C_BaseEntity* ignore, trace_t* ptr)
	{
		Ray_t ray;
		ray.Init(vecAbsStart, vecAbsEnd);
		CTraceFilter filter;
		filter.pSkip = ignore;

		g_EngineTrace->TraceRay(ray, mask, &filter, ptr);
	}


	void UTIL_ClipTraceToPlayers(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, trace_t* tr)
	{
		// UTIL_ClipTraceToPlayers Signature
		static DWORD dwAddress = FindPatternV2("client_panorama.dll", "53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 81 EC ? ? ? ? 8B 43 10");

		if (!dwAddress)
			return;

		_asm
		{
			MOV		EAX, filter
			LEA		ECX, tr
			PUSH	ECX
			PUSH	EAX
			PUSH	mask
			LEA		EDX, vecAbsEnd
			LEA		ECX, vecAbsStart
			CALL	dwAddress
			ADD		ESP, 0xC
		}
	}





	bool PlayerAimingAtEnemy()
	{
		Ray_t ray;
		trace_t trace;

		CTraceFilter filter;

		ray.Init(g_LocalPlayer->GetEyePos(), g_LocalPlayer->GetEyePos() + Vector(0, 0, 500.0f));
		g_EngineTrace->TraceRay(ray, MASK_PLAYERSOLID, &filter, &trace);

		return trace.DidHit();
	}

	/*
	* @brief Set player clantag
	*
	* @param tag New clantag
	*/
	void SetClantag(const char* tag)
	{
		static auto fnClantagChanged = (int(__fastcall*)(const char*, const char*))PatternScan(GetModuleHandleW(L"engine.dll"), "53 56 57 8B DA 8B F9 FF 15");

		fnClantagChanged(tag, tag);
	}

	/*
	* @brief Set player name
	*
	* @param name New name
	*/
	void SetName(const char* name)
	{
		static auto nameConvar = g_CVar->FindVar("name");
		nameConvar->m_fnChangeCallbacks.m_Size = 0;

		// Fix so we can change names how many times we want
		// This code will only run once because of `static`
		static auto do_once = (nameConvar->SetValue("\n���"), true);

		nameConvar->SetValue(name);
	}

	/*
	* @brief Reveal the ranks of all players on the server
	*
	*/
	Vector AngleVectors1(const QAngle& angles)
	{
		float sp, sy, cp, cy;

		SinCos(DEG2RAD(angles.yaw), &sy, &cy);
		SinCos(DEG2RAD(angles.pitch), &sp, &cp);

		Vector forward;
		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
		return forward;
	}

	bool EntityIsInvalid(C_BaseEntity* Entity)
	{

		if (!Entity)
			return true;

		auto pEntity = (C_BasePlayer*)Entity;
		if (!pEntity)
			return true;

		if (Entity == g_LocalPlayer)
			return true;
		if (pEntity->m_iHealth() <= 0)
			return true;
		if (Entity->IsDormant())
			return true;

		return false;
	}


	void RankRevealAll()
	{
		using ServerRankRevealAll = char(__cdecl*)(int*);

		static auto fnServerRankRevealAll = PatternScan(GetModuleHandleW(L"client_panorama.dll"), "55 8B EC 8B 0D ? ? ? ? 68");

		int v[3] = { 0,0,0 };

		reinterpret_cast<ServerRankRevealAll>(fnServerRankRevealAll)(v);
	}

	unsigned int FindInDataMap(datamap_t *pMap, const char *name)
	{

		while (pMap)
		{
			for (int i = 0; i<pMap->dataNumFields; i++)
			{
				if (pMap->dataDesc[i].fieldName == NULL)
					continue;

				if (strcmp(name, pMap->dataDesc[i].fieldName) == 0)
					return pMap->dataDesc[i].fieldOffset[TD_OFFSET_NORMAL];

				if (pMap->dataDesc[i].fieldType == FIELD_EMBEDDED)
				{
					if (pMap->dataDesc[i].td)
					{
						unsigned int offset;

						if ((offset = FindInDataMap(pMap->dataDesc[i].td, name)) != 0)
							return offset;
					}
				}
			}
			pMap = pMap->baseMap;
		}

		return 0;
	}

	

}