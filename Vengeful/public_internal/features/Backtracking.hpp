#pragma once
#include "../sdk\sdk.hpp"
#include "../sdk\csgostructs.hpp"
#include <vector>
#include <memory>

struct BacktrackRecord
{
	C_BasePlayer* entity;
	Vector head;
	Vector origin;
	float simtime;
	int flags;
};

struct BacktrackTick
{
	int tickcount;
	std::vector<BacktrackRecord> records;
};

class CBacktracking
{
public:
	std::vector<BacktrackTick> ticks;
	C_BasePlayer* entity;
	Vector prevOrig;

	void RegisterTick(CUserCmd* cmd);
	void Begin(CUserCmd* cmd);
	void End();
	void OnCreateMove(CUserCmd* cmd);
};

extern std::unique_ptr<CBacktracking> g_pBacktracking;