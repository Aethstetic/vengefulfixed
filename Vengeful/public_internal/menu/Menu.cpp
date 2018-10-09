#include "Menu.hpp"
#include "S1lentgui.hpp"
#include "../Config.h"
#include "../Options.hpp"
#include "../sdk/sdk.hpp"


Style* GetStyle()
{
	return &s1lentgui::GetStyle();
}
void CMenu::CreateObjects()
{
	g_pDraw->CreateObjects();
}
void CMenu::ReleaseObjects()
{
	g_pDraw->ReleaseObjects();
}
void CMenu::Init(LPDIRECT3DDEVICE9 device)
{
	g_pDraw->Init(device);
}
void CMenu::RenderTabs()
{

	if (s1lentgui::Tab(AIMBOT_TAB_NAME, 5, 20, 75, 25, (currentab == 0)))
		currentab = 0;
	if (s1lentgui::Tab("Triggerbot", 5, 50, 75, 25, (currentab == 1)))
		currentab = 1;
	if (s1lentgui::Tab(VISUAL_TAB_NAME, 5, 80, 75, 25, (currentab == 2)))
		currentab = 2;
	if (s1lentgui::Tab(MISC_TAB_NAME, 5, 110, 75, 25, (currentab == 3)))
		currentab = 3;
	if (s1lentgui::Tab("Color", 5, 140, 75, 25, (currentab == 4)))
		currentab = 4;
	if (s1lentgui::Tab("Config", 5, 170, 75, 25, (currentab == 5)))
		currentab = 5;
}
void CMenu::RenderAimbotTab()
{
	s1lentgui::Checkbox("Enabled", &g_pOptions->AimbotSettings.enabled);
	s1lentgui::Checkbox("Use Aimbot Key", &g_pOptions->AimbotSettings.useaimkey);
	s1lentgui::KeyButton("Aimbot Key", &g_pOptions->AimbotSettings.aimkey);
	s1lentgui::Checkbox("Use BAim Key", &g_pOptions->AimbotSettings.usebaimkey);
	s1lentgui::KeyButton("BAim Key", &g_pOptions->AimbotSettings.baimkey); 
	s1lentgui::SliderFloat("FOV", &g_pOptions->AimbotSettings.fov, 0.0f, 180.0f);
	s1lentgui::Checkbox("Smoothed", &g_pOptions->AimbotSettings.smoothed);
	s1lentgui::SliderFloat("Smoothing", &g_pOptions->AimbotSettings.smoothing, 0.0f, 300.0f);
	s1lentgui::Checkbox("Visual Check", &g_pOptions->AimbotSettings.vischeck);
	s1lentgui::Checkbox("Jump Check", &g_pOptions->AimbotSettings.jumpcheck);
	s1lentgui::Checkbox("Enemy Check", &g_pOptions->AimbotSettings.enemycheck);
	s1lentgui::Checkbox("Team Check", &g_pOptions->AimbotSettings.teamcheck);
	s1lentgui::Checkbox("Flash Check", &g_pOptions->AimbotSettings.flashcheck);
	s1lentgui::Checkbox("Smoke Check", &g_pOptions->AimbotSettings.smokecheck);
	s1lentgui::NextColumn();
	s1lentgui::Checkbox("RCS", &g_pOptions->AimbotSettings.rcs);
	s1lentgui::SliderFloat("RCS Intensity", &g_pOptions->AimbotSettings.rcsintesity, 0.0f, 2.0f);
	s1lentgui::Checkbox("Visible RCS", &g_pOptions->AimbotSettings.visiblercs);
	s1lentgui::NewLine();
	s1lentgui::SliderInt("Backtracking Ticks", &g_pOptions->AimbotSettings.backtrackingticks, 0, 12);
}
void CMenu::RenderVisualSubTabs()
{
	if (s1lentgui::Tab1("ESP", 90, 20, 50, 20, (currentabv == 0)))
		currentabv = 0;
	if (s1lentgui::Tab1("Glow", 150, 20, 50, 20, (currentabv == 1)))
		currentabv = 1;
	if (s1lentgui::Tab1("Chams", 210, 20, 50, 20, (currentabv == 2)))
		currentabv = 2;

	s1lentgui::Text("");
	s1lentgui::NewLine();
}

void CMenu::RenderColorTab()
{
	RenderVisualSubTabs();

	if (currentabv == 0)
	{
		static bool eexpanded;
		static bool fexpanded;
		static bool esexpanded;
		static bool fsexpanded;

		s1lentgui::ColorPicker("Enemy Box Color", &g_pOptions->VisualSettings.EspSettings.eboxcolor, eexpanded);
		s1lentgui::ColorPicker("Friendly Box Color", &g_pOptions->VisualSettings.EspSettings.fboxcolor, fexpanded);
		s1lentgui::ColorPicker("Enemy Skeleton Color", &g_pOptions->VisualSettings.EspSettings.eskeletoncolor, esexpanded);
		s1lentgui::ColorPicker("Friendly Skeleton Color", &g_pOptions->VisualSettings.EspSettings.fskeletoncolor, fsexpanded);
	}
	else if (currentabv == 1)
	{
		static bool aexpanded;
		static bool eexpanded;
		static bool gexpanded;
		static bool cexpanded;
		static bool dexpanded;

		s1lentgui::ColorPicker("Ally Glow Color", &g_pOptions->VisualSettings.GlowSettings.friendlyglow, aexpanded);
		s1lentgui::ColorPicker("Enemy Glow Color", &g_pOptions->VisualSettings.GlowSettings.enemyglow, eexpanded);
		s1lentgui::ColorPicker("Grenade Glow Color", &g_pOptions->VisualSettings.GlowSettings.grenadeglow, gexpanded);
		s1lentgui::ColorPicker("C4 Glow Color", &g_pOptions->VisualSettings.GlowSettings.c4glow, cexpanded);
		s1lentgui::ColorPicker("Defuse Glow Color", &g_pOptions->VisualSettings.GlowSettings.defuseglow, dexpanded);
	}
	else if (currentabv == 2)
	{
		static bool aexpanded;
		static bool eexpanded;
		s1lentgui::ColorPicker("Friendly Cham Color", &g_pOptions->VisualSettings.ChamSettings.fchamcolor, aexpanded);
		s1lentgui::ColorPicker("Enemy Cham Color", &g_pOptions->VisualSettings.ChamSettings.echamcolor, eexpanded);
	}

}

void CMenu::RenderTriggerbotTab()
{
	s1lentgui::Checkbox("Enabled", &g_pOptions->TriggerbotSettings.enabled);
	s1lentgui::SliderFloat("Hitchance", &g_pOptions->TriggerbotSettings.hitchance, 0.0f, 100.0f);
	s1lentgui::SliderFloat("Delay", &g_pOptions->TriggerbotSettings.delay, 0.0f, 1000.0f);
}

void CMenu::RenderConfigTab()
{
	s1lentgui::TextBox("Config Name", &optiontext);
	std::string totaltext = optiontext + std::string(".vfp");
	if (s1lentgui::Button("Save"))
		Config::Save(totaltext);
	if (s1lentgui::Button("Load"))
		Config::Load(totaltext);
}

void CMenu::RenderVisualTab()
{
	RenderVisualSubTabs();
	

	if (currentabv == 0) //ESP
	{
			s1lentgui::Checkbox("Enabled", &g_pOptions->VisualSettings.EspSettings.enabled);
			s1lentgui::Checkbox("Box ESP", &g_pOptions->VisualSettings.EspSettings.box);
			s1lentgui::Checkbox("Health ESP", &g_pOptions->VisualSettings.EspSettings.healthbar);
			s1lentgui::Checkbox("Name ESP", &g_pOptions->VisualSettings.EspSettings.name);
			s1lentgui::Checkbox("Weapon ESP", &g_pOptions->VisualSettings.EspSettings.weapon);
			s1lentgui::Checkbox("Ammo ESP", &g_pOptions->VisualSettings.EspSettings.ammo);
			s1lentgui::Checkbox("Skeleton ESP", &g_pOptions->VisualSettings.EspSettings.skeleton);
			s1lentgui::NewLine();
			s1lentgui::Checkbox("ESP Friendlies", &g_pOptions->VisualSettings.EspSettings.friendlies);
			s1lentgui::Checkbox("ESP Enemies", &g_pOptions->VisualSettings.EspSettings.enemies);
			s1lentgui::NextColumn();
			s1lentgui::Checkbox("FOV Changer", &g_pOptions->VisualSettings.EspSettings.fovchanger);
			s1lentgui::SliderFloat("FOV", &g_pOptions->VisualSettings.EspSettings.fov, 0.0f, 300.0f);
		
	} 
	else if (currentabv == 1) //Glow
	{
			s1lentgui::Checkbox("Enabled", &g_pOptions->VisualSettings.GlowSettings.enabled);
			s1lentgui::Checkbox("Players", &g_pOptions->VisualSettings.GlowSettings.glowplayers);
			s1lentgui::Checkbox("Allies", &g_pOptions->VisualSettings.GlowSettings.glowfriendlies);
			s1lentgui::Checkbox("Enemies", &g_pOptions->VisualSettings.GlowSettings.glowenemies);
			s1lentgui::Checkbox("Grenades", &g_pOptions->VisualSettings.GlowSettings.glowgrenades);
			s1lentgui::Checkbox("C4", &g_pOptions->VisualSettings.GlowSettings.glowplantedc4);
			s1lentgui::Checkbox("Defuse Kits", &g_pOptions->VisualSettings.GlowSettings.glowdefusekits);
			s1lentgui::Checkbox("Weapons", &g_pOptions->VisualSettings.GlowSettings.glowweapons);
			s1lentgui::NewLine();
		

	}
	else if (currentabv == 2) //Chams
	{
			s1lentgui::Checkbox("Enabled", &g_pOptions->VisualSettings.ChamSettings.enabled);
			s1lentgui::Checkbox("Friendlies", &g_pOptions->VisualSettings.ChamSettings.chamfriendlies);
			s1lentgui::Checkbox("Friendly XQZ", &g_pOptions->VisualSettings.ChamSettings.xqzf);
			s1lentgui::Checkbox("Enemies", &g_pOptions->VisualSettings.ChamSettings.chamenemies);
			s1lentgui::Checkbox("Enemy XQZ", &g_pOptions->VisualSettings.ChamSettings.xqze);
	}

}
void CMenu::ResetDraw()
{
	g_pDraw->Reset();
}

void CMenu::RenderMiscTab()
{
	s1lentgui::Checkbox("Bunnyhops", &g_pOptions->MiscSettings.bhops);
	std::vector<const char *> dropdown = { "Legit","Perfect" };
	s1lentgui::DropDown("Bunnyhop Type", dropdown, &g_pOptions->MiscSettings.bhoptype);
	s1lentgui::Checkbox("Auto Strafer", &g_pOptions->MiscSettings.autostrafer);
}

void CMenu::DoFrameUpdate()
{
	g_pDraw->Reset(); //Reset Drawing Device

	if (GetAsyncKeyState(VK_INSERT) && !togglepress)
		togglepress = true;
	else if (!GetAsyncKeyState(VK_INSERT) && togglepress)
	{
		opened = !opened;
		togglepress = false;
	}

	last = opened;
	if (opened != last)
	{
		last = opened;
		std::string cmd = "cl_mouseenable " + std::to_string(opened);
		g_EngineClient->ExecuteClientCmd(cmd.c_str());
	}

	Style* Style = GetStyle();

	if (s1lentgui::Begin(CHEAT_NAME, &opened, false))
	{
		RenderTabs();



		switch (currentab) {
			case(0):
			{
				RenderAimbotTab();
				break;
			}
			case(1):
			{
				RenderTriggerbotTab();
				break;
			}
			case(2):
			{
				RenderVisualTab();
				break;
			}
			case(3):
			{
				RenderMiscTab();
				break;
			}
			case(4):
			{
				RenderColorTab();
				break;
			}
			case(5):
			{
				RenderConfigTab();
				break;
			}
		}
		s1lentgui::End();
	}

}

std::unique_ptr<CMenu> g_pMenu = std::make_unique<CMenu>();