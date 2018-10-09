#include "Backtracking.hpp"
#include "../utils/FeatureUtils.hpp"
#include "../Options.hpp"
std::unique_ptr<CBacktracking> g_pBacktracking = std::make_unique<CBacktracking>();

void CBacktracking::RegisterTick(CUserCmd* cmd)
{
	ticks.insert(ticks.begin(), BacktrackTick{ cmd->tick_count });

	auto& cur = ticks[0];

	while (ticks.size() > g_pOptions->AimbotSettings.backtrackingticks)
		ticks.pop_back();

	for (int i = 1; i < g_EngineClient->GetMaxClients(); i++)
	{
		auto entity = reinterpret_cast<C_BasePlayer*>(g_EntityList->GetClientEntity(i));

		if (!entity ||
			entity->IsDormant() ||
			entity->m_iHealth() <= 0 ||
			entity->m_iTeamNum() == g_LocalPlayer->m_iTeamNum() ||
			entity->m_bGunGameImmunity())
			continue;



		cur.records.emplace_back(BacktrackRecord{ entity, entity->GetBonePos(8), entity->m_vecOrigin(), entity->m_flSimulationTime(), entity->m_fFlags() });
	}
}

void CBacktracking::Begin(CUserCmd* cmd)
{
	entity = nullptr;

	float serverTime = g_LocalPlayer->m_nTickBase() * g_GlobalVars->interval_per_tick;
	auto weapon = g_LocalPlayer->m_hActiveWeapon();


	if (weapon)
	{
		if (((cmd->buttons & IN_ATTACK) || (cmd->buttons & IN_ATTACK2)) && weapon->m_flNextPrimaryAttack() < serverTime + 0.001f)
		{
			float fov = 180.0f;
			int tickcount = 0;
			bool hasTarget = false;
			Vector orig;
			int flags;
			float simtime;

			for (auto& tick : ticks)
			{
				for (auto& record : tick.records)
				{
					QAngle angle = f_utils->CalcAngle(g_LocalPlayer->GetEyePos(), record.head);
					float tmpFOV = f_utils->GetFov(cmd->viewangles, angle);

					if (tmpFOV < fov)
					{
						fov = tmpFOV;
						tickcount = tick.tickcount;
						hasTarget = true;
						entity = record.entity;
						orig = record.origin;
						simtime = record.simtime;
						flags = record.flags;

						static auto invalidateBoneCache = f_utils->PatternScan(GetModuleHandle("client_panorama.dll"), "80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81");
						DWORD modelBoneCounter = **(DWORD**)(invalidateBoneCache + 0xA);
						*(DWORD*)((DWORD)entity + 0x2914) = 0xFF7FFFFF;
						*(DWORD*)((DWORD)entity + 0x2680) = (modelBoneCounter - 0x1);
					}
				}
			}

			if (entity && hasTarget)
			{
				auto entityplayer = reinterpret_cast<C_BasePlayer*>(entity);
				cmd->tick_count = tickcount;
				prevOrig = entity->m_vecOrigin();
				entity->m_vecOrigin() = orig;
				entityplayer->m_flSimulationTime() = simtime;
				entityplayer->m_fFlags() = flags;
			}
		}
	}
}

void CBacktracking::End()
{
	auto pWeapon = g_LocalPlayer->m_hActiveWeapon();

	if (pWeapon)
	{
		if (entity)
			entity->m_vecOrigin() = prevOrig;

		entity = nullptr;
	}
}

void CBacktracking::OnCreateMove(CUserCmd* cmd)
{
	if (g_LocalPlayer && g_EngineClient->IsInGame() && g_EngineClient->IsConnected())
	{
		RegisterTick(cmd);

		if (g_LocalPlayer->IsAlive() && g_LocalPlayer->m_hActiveWeapon())
		{
			if (g_pOptions->AimbotSettings.backtrackingticks > 0)
			{
				Begin(cmd);
				End();
			}
		}
	}
}