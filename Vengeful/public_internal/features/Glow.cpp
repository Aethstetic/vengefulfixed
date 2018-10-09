#include "Glow.hpp"
#include "../sdk/sdk.hpp"
#include "../sdk/csgostructs.hpp"
#include "../Options.hpp"
void CGlow::DoGlow()
{
	for (int i = 0; i < g_GlowObjManager->size; ++i)
	{
		CGlowObjectManager::GlowObjectDefinition_t* glowEntity = &g_GlowObjManager->m_GlowObjectDefinitions[i];
		C_BasePlayer* Entity = glowEntity->GetEntity();

		if (glowEntity->IsEmpty())
			continue;

		if (!Entity)
			continue;
		if (Entity->IsDormant())
			continue;

		auto color = Color{};

		switch (Entity->GetClientClass()->m_ClassID)
		{
		case ClassId_CCSPlayer:
		{
			if (!g_pOptions->VisualSettings.GlowSettings.glowplayers)
				continue;

			if (Entity->m_iTeamNum() == g_LocalPlayer->m_iTeamNum())
			{
				if (!g_pOptions->VisualSettings.GlowSettings.glowfriendlies)
					continue;

				color = g_pOptions->VisualSettings.GlowSettings.friendlyglow;

			}
			else {
				if (!g_pOptions->VisualSettings.GlowSettings.glowenemies)
					continue;

				color = g_pOptions->VisualSettings.GlowSettings.enemyglow;
			}

			break;

		}
		case ClassId_CBaseCSGrenade:
		{
			if (!g_pOptions->VisualSettings.GlowSettings.glowgrenades)
				continue;
			color = g_pOptions->VisualSettings.GlowSettings.grenadeglow;
			break;
		}
		case ClassId_CBaseAnimating:
		{
			if (!g_pOptions->VisualSettings.GlowSettings.glowdefusekits)
				continue;
			color = g_pOptions->VisualSettings.GlowSettings.defuseglow;
			break;
		}
		case ClassId_CEconEntity:
		{
			if (!g_pOptions->VisualSettings.GlowSettings.glowdefusekits)
				continue;
			color = g_pOptions->VisualSettings.GlowSettings.defuseglow;
			break;
		}
		case ClassId_CPlantedC4:
		{
			if (!g_pOptions->VisualSettings.GlowSettings.glowplantedc4)
				continue;
			color = g_pOptions->VisualSettings.GlowSettings.c4glow;
			break;
		}
		case ClassId_CC4:
		{
			if (!g_pOptions->VisualSettings.GlowSettings.glowplantedc4)
				continue;
			color = g_pOptions->VisualSettings.GlowSettings.c4glow;
			break;
		}

		default:
			if (!Entity->IsWeapon())
				continue;
			if (g_pOptions->VisualSettings.GlowSettings.glowweapons)
			{
				color = g_pOptions->VisualSettings.GlowSettings.weaponglow;
			}
			else {
				continue;
			}
			break;
		}
		glowEntity->Set(color);
	}
}

std::unique_ptr<CGlow> glow= std::make_unique<CGlow>();