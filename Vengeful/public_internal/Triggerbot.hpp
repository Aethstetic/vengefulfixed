#pragma once
#include "sdk\sdk.hpp"
#include "sdk\csgostructs.hpp"
#include <memory>

class CTriggerbot
{
public:
	bool IsAimingAtPlayer(CUserCmd* cmd);
	void OnCreateMove(CUserCmd* cmd);
	bool HitchanceValid(C_BaseEntity * ent, QAngle angles);
};

extern std::unique_ptr<CTriggerbot> triggerbot;