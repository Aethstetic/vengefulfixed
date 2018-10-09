#include "Aimbot.hpp"
#include "../Options.hpp"
#include "../Helpers/math.hpp"
#include "../utils/FeatureUtils.hpp"



void CAimbot::SmoothAngle(AimData &data, QAngle currentang)
{

	QAngle angledifference = data.aimangle - currentang;

	Math::NormalizeAngles(angledifference);
	Math::ClampAngles(angledifference);
	angledifference.pitch = angledifference.pitch / g_pOptions->AimbotSettings.smoothing + currentang.pitch;
	angledifference.yaw = angledifference.yaw/ g_pOptions->AimbotSettings.smoothing + currentang.yaw;
	Math::NormalizeAngles(angledifference);
	Math::ClampAngles(angledifference);

	data.aimangle = angledifference;


}

Vector CAimbot::GetBestHitbox(C_BasePlayer* player)
{
	if (GetAsyncKeyState(g_pOptions->AimbotSettings.baimkey) && g_pOptions->AimbotSettings.usebaimkey)
		return player->GetBonePos(5);
	
	return player->GetBonePos(8);
}

void CAimbot::DoAimbot(AimData targetdata)
{
	if (!targetdata.player)
		return;

	QAngle localangs;
	g_EngineClient->GetViewAngles(localangs);

	Math::NormalizeAngles(targetdata.aimangle);
	Math::ClampAngles(targetdata.aimangle);

	if (g_pOptions->AimbotSettings.smoothed)
		SmoothAngle(targetdata,localangs);

	g_EngineClient->SetViewAngles(targetdata.aimangle);
}
AimData CAimbot::GetBestData()
{
	if (g_pOptions->AimbotSettings.flashcheck && g_LocalPlayer->m_flFlashDuration() > 1.25f)
		return AimData();

	if (!g_LocalPlayer || !g_EngineClient->IsConnected() || !g_EngineClient->IsInGame())
		return AimData();

	AimData returndata;
	C_BasePlayer* bestplayer;
	float BestFOV = 99999.0f;
	
	for (int i = 1; i < g_EngineClient->GetMaxClients(); ++i)
	{
		auto pEntity = (C_BasePlayer*)g_EntityList->GetClientEntity(i);

		if (!pEntity)
			continue;
		if (!pEntity->IsAlive() && pEntity != g_LocalPlayer)
			continue;


		QAngle targetangle = f_utils->CalcAngle(g_LocalPlayer->GetEyePos(), GetBestHitbox(pEntity));
		QAngle ang;
		g_EngineClient->GetViewAngles(ang);

		static QAngle RCSLastPunch1;
		QAngle rcsang = ang;
		rcsang = rcsang -= g_LocalPlayer->m_aimPunchAngle() * 2.0f;
		RCSLastPunch1 = g_LocalPlayer->m_aimPunchAngle();

		Math::NormalizeAngles(rcsang);
		Math::ClampAngles(rcsang);

		float FOV = f_utils->GetFov(rcsang, targetangle);

		bool enemy = f_utils->IsEnemy(pEntity);

		if (enemy && !g_pOptions->AimbotSettings.enemycheck)
			continue;
		if (!enemy && !g_pOptions->AimbotSettings.teamcheck)
			continue;

		if (g_pOptions->AimbotSettings.jumpcheck && !(pEntity->m_fFlags() & FL_ONGROUND))
			continue;

		if (g_pOptions->AimbotSettings.vischeck && !f_utils->CanSeePlayer(pEntity))
			continue;

		Vector HitBox = GetBestHitbox(pEntity);

		if (g_pOptions->AimbotSettings.smokecheck && f_utils->LineGoesThroughSmoke(g_LocalPlayer->GetEyePos(), HitBox))
			continue;

		


		if (FOV < BestFOV && FOV <= g_pOptions->AimbotSettings.fov)
		{
			bestplayer = pEntity;
			BestFOV = FOV;
			returndata.player = bestplayer;
			returndata.aimangle = targetangle;
			returndata.targetpos = HitBox;
		}

	}

	return returndata;

}
bool CAimbot::DoRCS(CUserCmd* pCmd)
{
	if (g_EngineClient->IsInGame() && g_LocalPlayer->IsAlive() && g_pOptions->AimbotSettings.rcsintesity > 0.0f)
	{
		auto punchAngles = g_LocalPlayer->m_aimPunchAngle() * g_pOptions->AimbotSettings.rcsintesity;
		if (punchAngles.pitch != 0.0f || punchAngles.yaw != 0)
		{
			pCmd->viewangles -= punchAngles;

			Math::NormalizeAngles(pCmd->viewangles);
			Math::ClampAngles(pCmd->viewangles);
			
			return true;
		}
	}
	return false;
}
void CAimbot::DoAimbotFull(CUserCmd* cmd)
{
	if (!g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
		return;

	if (!g_LocalPlayer->IsAlive())
		return;


	if (!GetAsyncKeyState(g_pOptions->AimbotSettings.aimkey) && g_pOptions->AimbotSettings.useaimkey)
		return;

	AimData bestdata = GetBestData();
	if (bestdata.player)
		DoAimbot(bestdata);
	
}

std::unique_ptr<CAimbot> aimbot = std::make_unique<CAimbot>();