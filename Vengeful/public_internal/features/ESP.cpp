#include "ESP.hpp"
#include "../utils/FeatureUtils.hpp"
#include "../Helpers/math.hpp"
#include "../menu/DrawManager.h"
#include "../Options.hpp"



void CESP::GetData_SceneEnd() {
	if (g_EngineClient->IsInGame() && g_EngineClient->IsConnected()) {
		for (int i = 0; i < g_EngineClient->GetMaxClients(); ++i)
		{
			C_BasePlayer* Entity = (C_BasePlayer*)g_EntityList->GetClientEntity(i);

			if (!Entity) {
				this->boxes[i] = { 0 };
				this->healthbars[i] = { 0 };
				this->playernames[i] = { 0 };
				this->weaponnames[i] = { 0 };
				this->ammonames[i] = { 0 };
				this->skeletons[i] = { 0 };
				continue;
			}

			if (f_utils->EntityIsInvalid(Entity)) {
				this->boxes[i] = { 0 };
				this->healthbars[i] = { 0 };
				this->playernames[i] = { 0 };
				this->weaponnames[i] = { 0 };
				this->ammonames[i] = { 0 };
				this->skeletons[i] = { 0 };
				continue;
			}


			if (!g_pOptions->VisualSettings.EspSettings.friendlies && !f_utils->IsEnemy(Entity)) {
				this->boxes[i] = { 0 };
				this->healthbars[i] = { 0 };
				this->playernames[i] = { 0 };
				this->weaponnames[i] = { 0 };
				this->ammonames[i] = { 0 };
				this->skeletons[i] = { 0 };
				continue;
			}

			if (!g_pOptions->VisualSettings.EspSettings.enemies && f_utils->IsEnemy(Entity)) {
				this->boxes[i] = { 0 };
				this->healthbars[i] = { 0 };
				this->playernames[i] = { 0 };
				this->weaponnames[i] = { 0 };
				this->ammonames[i] = { 0 };
				this->skeletons[i] = { 0 };
				continue;
			}


			Vector max = Entity->GetCollideable()->OBBMaxs();
			Vector pos, pos3D;
			Vector top, top3D;
			pos3D = Entity->m_vecOrigin();
			top3D = pos3D + Vector(0, 0, max.z);

			if (!Math::WorldToScreen(pos3D, pos) || !Math::WorldToScreen(top3D, top))
				continue;

			float height = (pos.y - top.y);
			float width = height / 4.f;


			if (pos.IsValid() && top.IsValid()) {
				//BOX ESP
				BOXESP box;
				box.x = top.x;
				box.y = top.y;
				box.w = width;
				box.h = height;
				if (f_utils->IsEnemy(Entity))
					box.color = g_pOptions->VisualSettings.EspSettings.eboxcolor;
				else
					box.color = g_pOptions->VisualSettings.EspSettings.fboxcolor;


				this->boxes[i] = box;

				//HEALTH BAR
				HEALTHBARESP healthbar;

				healthbar.bottomx = pos.x;
				healthbar.bottomy = pos.y;
				healthbar.topy = top.y;
				healthbar.topx = top.x;
				healthbar.health = Entity->m_iHealth();
				healthbar.render = true;

				this->healthbars[i] = healthbar;

				//WEAPON NAMES


				NAMEESP weaponname;
				weaponname.message = "No Data";
				if (Entity->IsPlayer()) {
					auto weapon = Entity->m_hActiveWeapon();
					if (weapon) {
						auto weapondata = weapon->GetCSWeaponData();
						if (weapondata) {
							weaponname.message = weapondata->szWeaponName;
							int underscorepos = weaponname.message.find("_");
							weaponname.message = weaponname.message.substr(underscorepos+1, weaponname.message.length());
						}
					}
				}
				weaponname.x = top.x;
				weaponname.y = pos.y;
				weaponname.font = g_pDraw->fonts.fnormal;

				this->weaponnames[i] = weaponname;


				//PLAYER NAMES

				NAMEESP playername;


				player_info_t info;
				if (g_EngineClient->GetPlayerInfo(Entity->EntIndex(), &info))
					playername.message = info.szName;
				else
					playername.message = "Error getting name";
				playername.x = top.x;
				playername.y = top.y - 10;
				playername.font = g_pDraw->fonts.fnormal;

				this->playernames[i] = playername;

				//AMMO NAMES

				NAMEESP ammoname;

				ammoname.message = "No Data";
				
				if (Entity->IsPlayer()) {
					auto weapon = Entity->m_hActiveWeapon();
					if (weapon) {
						ammoname.message = (std::to_string(weapon->m_iClip1()) + " / " + std::to_string(weapon->m_iPrimaryReserveAmmoCount()));
					}
				}
				ammoname.x = top.x;
				ammoname.y = pos.y;
				if (g_pOptions->VisualSettings.EspSettings.weapon)
					ammoname.y += 20;
				ammoname.font = g_pDraw->fonts.fnormal;

				this->ammonames[i] = ammoname;

				//Skeleton ESP

				SKELETONESP skeletonesp;

				matrix3x4_t bone_matrix[128];
				if (!Entity->SetupBones(bone_matrix, 128, BONE_USED_BY_ANYTHING, 0)) {
					this->skeletons[i] = { 0 };
					continue;
				}

					auto studio_model = g_MdlInfo->GetStudioModel(Entity->GetModel()); 
					if (!studio_model) {
						this->skeletons[i] = { 0 };
						continue;
					}

					for (int i = 0; i < studio_model->numbones; i++) {
						auto bone = studio_model->pBone(i);
						if (!bone || bone->parent < 0 || !(bone->flags & BONE_USED_BY_HITBOX))
						{
							continue;
						}

						// 2 bone matrices, 1 for the child and 1 for the parent bone
						matrix3x4_t bone_matrix_1, bone_matrix_2;
						if (bone_matrix) {
							bone_matrix_1 = bone_matrix[i];
							bone_matrix_2 = bone_matrix[bone->parent];
						}
						else {
							bone_matrix_1 = Entity->GetBoneMatrix(i);
							bone_matrix_2 = Entity->GetBoneMatrix(bone->parent);
						}

						Vector bone_position_1 = Vector(bone_matrix_1[0][3], bone_matrix_1[1][3], bone_matrix_1[2][3]),
							bone_position_2 = Vector(bone_matrix_2[0][3], bone_matrix_2[1][3], bone_matrix_2[2][3]);

						Vector screen1, screen2;
						if (Math::WorldToScreen(bone_position_1, screen1) && Math::WorldToScreen(bone_position_2, screen2))
						{
							DrawPos pos;
							pos.x1 = screen1.x;
							pos.x2 = screen2.x;
							pos.y1 = screen1.y;
							pos.y2 = screen2.y;
							skeletonesp.BonesToDraw[i] = pos;
						}
					}
					skeletonesp.numbones = studio_model->numbones;
					skeletonesp.draw = true;
					if (f_utils->IsEnemy(Entity))
						skeletonesp.color = g_pOptions->VisualSettings.EspSettings.eskeletoncolor;
					else 
						skeletonesp.color = g_pOptions->VisualSettings.EspSettings.fskeletoncolor;
					this->skeletons[i] = skeletonesp;




			}
		}

	}
}



void CESP::Render_EndScene()
{
	if (!g_pOptions->VisualSettings.EspSettings.enabled)
		return;
	if (!g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
		return;
	if (g_pOptions->VisualSettings.EspSettings.box)
		if (this->boxes)
			RenderBoxes();

	if (g_pOptions->VisualSettings.EspSettings.healthbar)
		if (this->healthbars)
			RenderHealthBars();
	if (g_pOptions->VisualSettings.EspSettings.name)
		if (this->playernames)
			RenderPlayerNames();
	if (g_pOptions->VisualSettings.EspSettings.weapon)
		if (this->weaponnames)
			RenderWeaponNames();
	if (g_pOptions->VisualSettings.EspSettings.ammo)
		if (this->ammonames)
			RenderAmmoNames();

	if (g_pOptions->VisualSettings.EspSettings.skeleton)
		if (this->skeletons)
			RenderSkeletons();
}

void CESP::RenderPlayerNames()
{
	for (int index = 0; index < 64; index++)
	{
		auto playertext = this->playernames[index];
		if (playertext.message != "" && playertext.x > 0 && playertext.y > 0 && playertext.font)
			g_pDraw->String(playertext.x, playertext.y - 10, FONT_CENTER, playertext.font, true, WHITE(255), playertext.message.c_str());
	}
}

void CESP::RenderWeaponNames()
{

	for (int index = 0; index < 64; index++)
	{
		auto playertext = this->weaponnames[index];
		if (strlen(playertext.message.c_str()) && playertext.x > 0 && playertext.y > 0 && playertext.font)
			g_pDraw->String(playertext.x, playertext.y, FONT_CENTER, playertext.font, true, WHITE(255), playertext.message.c_str());
	}
}

void CESP::RenderAmmoNames()
{

	for (int index = 0; index < 64; index++)
	{
		auto weapontext = this->ammonames[index];
		if (strlen(weapontext.message.c_str()) && weapontext.x > 0 && weapontext.y > 0 && weapontext.font)
			g_pDraw->String(weapontext.x, weapontext.y, FONT_CENTER, weapontext.font, true, WHITE(255), weapontext.message.c_str());
	}
}


void CESP::RenderSkeletons()
{

	for (int index = 0; index < 64; index++)
	{
		auto skeletondata = this->skeletons[index];
		if (skeletondata.draw)
		{
			for (int i = 0; i < skeletondata.numbones; i++) {
				auto cdata = skeletondata.BonesToDraw[i];
				g_pDraw->Line(cdata.x1, cdata.y1, cdata.x2, cdata.y2,D3DCOLOR_RGBA(skeletondata.color.r(), skeletondata.color.g(), skeletondata.color.b(), skeletondata.color.a()));
			}
		}
	}
}

void CESP::RenderBoxes()
{
	for (int index = 0; index < 64; index++)
	{
		auto box = this->boxes[index];
		if (box.x > 0 && box.y > 0 && box.w > 0 && box.h > 0) {
			PlayerBox(box.x, box.y, box.w, box.h, box.color);
		}
	}
}

void CESP::RenderHealthBars()
{
	for (int index = 0; index < 64; index++)
	{
		auto healthbar = this->healthbars[index];
		if (healthbar.render && healthbar.health > 0.0f && healthbar.bottomx > 0 && healthbar.bottomy > 0 && healthbar.topx > 0 && healthbar.topy > 0) {
			Vector bottom = Vector(healthbar.bottomx, healthbar.bottomy, 0);
			Vector top = Vector(healthbar.topx, healthbar.topy, 0);
			HealthBar(bottom, top, healthbar.health);
		}
	}
}

void CESP::PlayerBox(float x, float y, float w, float h, Color clr)
{
	int x1 = Math::Get3DDelta(Vector(x - w, 0, 0), Vector(x + w, 0, 0));
	int y1 = Math::Get3DDelta(Vector(y, 0, 0), Vector(y + h, 0, 0));


	D3DCOLOR color = D3DCOLOR_RGBA(clr.r(), clr.g(), clr.b(), clr.a());

	g_pDraw->BorderedBox(x - w - 3, y - 3, x1 + 3, y1 + 3, color,2);
}

void CESP::HealthBar(Vector bot, Vector top, float health)
{
	float h = (bot.y - top.y);
	float offset = (h / 4.f) + 5;
	float w = h / 64.f;

	UINT hp = h - (UINT)((h * health) / 100); // Percentage

	int Red = 255 - (health * 2.55);
	int Green = health * 2.55;


	float healthwidth = sqrtf(powf((top.x - offset) - (top.x - offset + 1.5), 2.0f)) + 2;
	float healthheight = sqrtf(powf((top.y + hp) - (top.y + h), 2.0f));

	float centerx = ((top.x - offset) + (top.x - offset) - 7.5)/2;

	g_pDraw->FilledBox(centerx, top.y + hp, healthwidth, healthheight, D3DCOLOR_ARGB(255, Red, Green, 0));

}

std::unique_ptr<CESP> g_pESP = std::make_unique<CESP>();