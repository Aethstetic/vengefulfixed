#pragma once
#include "..\sdk\sdk.hpp"
#include "..\sdk\csgostructs.hpp"
struct AimData
{
	AimData()
	{
		targetpos = Vector(0, 0, 0);
		aimangle = QAngle(0, 0, 0);
		player = nullptr;
	}
	Vector targetpos;
	QAngle aimangle;
	C_BasePlayer* player;
};


class CAimbot
{
public:
	void DoAimbotFull(CUserCmd * cmd);
	void SmoothAngle(AimData &data,QAngle currentang);
	Vector GetBestHitbox(C_BasePlayer * player);
	void DoAimbot(AimData target);
	AimData GetBestData();

	bool DoRCS(CUserCmd * pCmd);

};

extern std::unique_ptr<CAimbot> aimbot;