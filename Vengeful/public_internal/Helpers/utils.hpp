#pragma once

#define NOMINMAX
#include <Windows.h>
#include <string>
#include <initializer_list>
#include "../sdk/sdk.hpp"

namespace Utils
{
	/*
	* @brief Create console
	*
	* Create and attach a console window to the current process
	*/
	void AttachConsole();

	/*
	* @brief Detach console
	*
	* Detach and destroy the attached console
	*/
	void DetachConsole();

	/*
	* @brief Print to console
	*
	* Replacement to printf that works with the newly created console
	*/
	bool ConsolePrint(const char* fmt, ...);

	/*
	* @brief Blocks execution until a key is pressed on the console window
	*
	*/
	char ConsoleReadKey();

	/*
	* @brief Wait for all the given modules to be loaded
	*
	* @param timeout How long to wait
	* @param modules List of modules to wait for
	*
	* @returns See WaitForSingleObject return values.
	*/
	int WaitForModules(std::int32_t timeout, const std::initializer_list<std::wstring>& modules);

	/*
	* @brief Scan for a given byte pattern on a module
	*
	* @param module    Base of the module to search
	* @param signature IDA-style byte array pattern
	*
	* @returns Address of the first occurence
	*/
	std::uint8_t* PatternScan(void* module, const char* signature);

	/*
	* @brief Set player clantag
	*
	* @param tag New clantag
	*/
	void SetClantag(const char* tag);

	/*
	* @brief Set player name
	*
	* @param name New name
	*/
	void SetName(const char* name);

	/*
	* @brief Reveal the ranks of all players on the server
	*
	*/
	void RankRevealAll();

	void inline SinCos(float radians, float* sine, float* cosine);
	bool IsLocalAlive();
	void AngleVectors(const QAngle& angles, Vector* forward);
	void AngleVectors(const QAngle &angles, Vector& forward, Vector& right, Vector& up);
	float GetFov(const QAngle& viewAngle, const QAngle& aimAngle);
	void VectorAngles(const Vector& forward, QAngle& angles);
	float RandomFloat(float min, float max);
	void VectorAngles(const Vector& forward, Vector& up, QAngle& angles);
	void VectorAngles(const Vector& forward, QAngle& angles);
	QAngle CalcAngle(Vector src, Vector dst);
	bool CanSeePlayer(C_BasePlayer* player);
	void CalcAngle(Vector src, Vector dst, Vector &angles);
	C_BasePlayer* Getg_LocalPlayer();
	void TraceLine(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, C_BaseEntity* ignore, trace_t* ptr);
	bool TraceToExit(Vector& end, trace_t& tr, Vector start, Vector vEnd, trace_t* trace);
	DWORD FindPattern(std::string moduleName, BYTE* Mask, char* szMask);
	bool EntityIsInvalid(C_BaseEntity* Entity);
	Vector AngleVectors1(const QAngle& angles);
	DWORD FindPatternV2(std::string moduleName, std::string pattern);
	unsigned int FindInDataMap(datamap_t *pMap, const char *name);
	uint64_t FindPatternIDA(const char* szModule, const char* szSignature);
}
