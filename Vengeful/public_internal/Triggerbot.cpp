#include "Triggerbot.hpp"
#include "utils\FeatureUtils.hpp"
#include "Helpers\math.hpp"
#include "Options.hpp"


C_BasePlayer* aim_entity(CUserCmd* cmd)
{
	CGameTrace tr;
	Ray_t ray;
	CTraceFilterPlayersOnlySkipOne filter = CTraceFilterPlayersOnlySkipOne(g_LocalPlayer);

	Vector Forward;
	QAngle viewangles = viewangles = cmd->viewangles;

	Math::AngleVectors(viewangles, Forward);
	Vector aimpunch;
	aimpunch = (g_LocalPlayer->m_aimPunchAngle() * 2).ConvertQAngleToVector();
	auto start = g_LocalPlayer->GetEyePos() + aimpunch;
	auto endpos = start + (Forward * (g_LocalPlayer->m_hActiveWeapon()->GetCSWeaponData()->flRange));

	ray.Init(start, endpos);
	g_EngineTrace->TraceRay(ray, 0x46004003, &filter, &tr);

	auto entity = reinterpret_cast<C_BaseEntity*>(tr.hit_entity);
	if (!entity)
		return nullptr;

	auto entity_client_class = entity->GetClientClass();
	if (!entity_client_class)
		return nullptr;

	auto player = reinterpret_cast<C_BasePlayer*>(entity);
	if (!player)
		return nullptr;

	if (!(player->IsPlayer()))
		return nullptr;

	if (player->IsDormant())
		return nullptr;

	if (!player->IsAlive())
		return nullptr;
	if (player->m_iTeamNum() == g_LocalPlayer->m_iTeamNum())
		return nullptr;

	return player;
}



bool CTriggerbot::HitchanceValid(C_BaseEntity *ent, QAngle angles)
{
	auto weapon = g_LocalPlayer->m_hActiveWeapon();

	if (!weapon)
		return false;

	Vector forward, right, up;
	Vector src = g_LocalPlayer->GetEyePos();
	Math::AngleVectors(angles, forward, right, up);

	int cHits = 0;
	int cNeededHits = static_cast<int>(150.f * (g_pOptions->TriggerbotSettings.hitchance / 100.f));

	weapon->UpdateAccuracyPenalty();
	float weap_spread = weapon->GetSpread();
	float weap_inaccuracy = weapon->GetInaccuracy();

	for (int i = 0; i < 150; i++)
	{
		float a = Utils::RandomFloat(0.f, 1.f);
		float b = Utils::RandomFloat(0.f, 2.f * 3.14);
		float c = Utils::RandomFloat(0.f, 1.f);
		float d = Utils::RandomFloat(0.f, 2.f * 3.14);

		float inaccuracy = a * weap_inaccuracy;
		float spread = c * weap_spread;

		if (weapon->GetItemDefinitionIndex() == 64)
		{
			a = 1.f - a * a;
			a = 1.f - c * c;
		}

		Vector spreadView((cos(b) * inaccuracy) + (cos(d) * spread), (sin(b) * inaccuracy) + (sin(d) * spread), 0), direction;

		direction.x = forward.x + (spreadView.x * right.x) + (spreadView.y * up.x);
		direction.y = forward.y + (spreadView.x * right.y) + (spreadView.y * up.y);
		direction.z = forward.z + (spreadView.x * right.z) + (spreadView.y * up.z);
		direction.Normalized();

		QAngle viewAnglesSpread;
		Utils::VectorAngles(direction, up, viewAnglesSpread);
		Math::NormalizeAngles(viewAnglesSpread);

		Vector viewForward;
		Utils::AngleVectors(viewAnglesSpread, &viewForward);
		viewForward.NormalizeInPlace();

		viewForward = src + (viewForward * weapon->GetCSWeaponData()->flRange);

		trace_t tr;
		Ray_t ray;

		ray.Init(src, viewForward);
		g_EngineTrace->ClipRayToEntity(ray, MASK_SHOT | CONTENTS_GRATE, ent, &tr);

		if (tr.hit_entity == ent)
			++cHits;

		if (static_cast<int>((static_cast<float>(cHits) / 150.f) * 100.f) >= g_pOptions->TriggerbotSettings.hitchance)
			return true;

		if ((150 - i + cHits) < cNeededHits)
			return false;
	}
	return false;
}

void CTriggerbot::OnCreateMove(CUserCmd* cmd)
{


	if (!g_EngineClient->IsInGame() || !g_LocalPlayer->IsAlive())
		return;


	if (!g_LocalPlayer)
		return;
	if (!g_LocalPlayer->m_hActiveWeapon())
		return;

	if (g_LocalPlayer->m_hActiveWeapon()->IsGrenade())
		return;
	if (g_LocalPlayer->m_hActiveWeapon()->IsKnife())
		return;
	if (g_LocalPlayer->m_hActiveWeapon()->GetClientClass()->m_ClassID == ClassId_CC4)
		return;

	if (g_LocalPlayer->m_hActiveWeapon()->IsKnife())
		return;

	if (!g_LocalPlayer->m_hActiveWeapon()->CanFire()) {
		cmd->buttons &= ~IN_ATTACK;
		return;
	}

	Vector localeyepos = g_LocalPlayer->GetEyePos();

	QAngle aimangle;
	aimangle = cmd->viewangles;

	C_BasePlayer* aimplayer = aim_entity(cmd);
	if (aimplayer)
	{
		if (f_utils->CanSeePlayer(aimplayer)) {
			if (HitchanceValid(aimplayer, aimangle)) {
				if (g_pOptions->TriggerbotSettings.delay == 0) {
					cmd->buttons |= IN_ATTACK;
					return;
				}
				else {
					static int target_time = 0;

					int current_time = g_GlobalVars->curtime * 1000;
					if (!target_time) target_time = current_time + g_pOptions->TriggerbotSettings.delay;

					if (target_time <= current_time && target_time > 0) {
						cmd->buttons |= IN_ATTACK;
						target_time = 0;
					}
				}
			}
		}
	}


	if (!(GetKeyState(VK_LBUTTON) & 0x100) != 0) {
		cmd->buttons &= ~IN_ATTACK;
	}



};


std::unique_ptr<CTriggerbot> triggerbot = std::make_unique<CTriggerbot>();