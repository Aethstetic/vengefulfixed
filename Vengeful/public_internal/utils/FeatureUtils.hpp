#pragma once
#define NOMINMAX
#include <Windows.h>
#include <string>
#include <initializer_list>
#include "../sdk/sdk.hpp"
#include "../sdk/csgostructs.hpp"
class FUtils
{
public:
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
	bool IsEnemy(C_BasePlayer* player);
	bool WeaponCanFire(C_BaseCombatWeapon * weapon);
	Vector GetHitboxPos(C_BasePlayer * player, int hitbox_id);
	void AngleVectors(const QAngle& angles, Vector* forward);
	void AngleVectors(const QAngle &angles, Vector& forward, Vector& right, Vector& up);
	float GetFov(const QAngle& viewAngle, const QAngle& aimAngle);
	void VectorAngles(const Vector& forward, QAngle& angles);
	float RandomFloat(float min, float max);
	Vector CrossProduct(const Vector & a, const Vector & b);
	void VectorAngles(const Vector& forward, Vector& up, QAngle& angles);
	QAngle CalcAngle(Vector src, Vector dst);
	void CalcAngle(Vector src, Vector dst, Vector &angles);
	bool CanSeePlayer(C_BasePlayer* player);
	bool LineGoesThroughSmoke(Vector vStartPos, Vector vEndPos);
	bool EntityIsInvalid(C_BasePlayer * Entity);
private:
	HANDLE _out = NULL, _old_out = NULL;
	HANDLE _err = NULL, _old_err = NULL;
	HANDLE _in = NULL, _old_in = NULL;
};

extern std::unique_ptr<FUtils> f_utils;