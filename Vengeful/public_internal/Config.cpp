#include "Config.h"
#include "Options.hpp"
#define NOMINMAX
#include <Windows.h>
#include <WinBase.h>
#include <chrono>
#include <stdio.h>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <fstream>


namespace Config
{
	void GetVal(Json::Value &config, int* setting)
	{
		if (config.isNull())
			return;

		*setting = config.asInt();
	}

	void GetVal(Json::Value &config, bool* setting)
	{
		if (config.isNull())
			return;

		*setting = config.asBool();
	}

	void GetVal(Json::Value &config, float* setting)
	{
		if (config.isNull())
			return;

		*setting = config.asFloat();
	}

	void GetVal(Json::Value &config, Color* setting)
	{
		if (config.isNull())
			return;

		static int R, G, B, A;

		GetVal(config["R"], &R);
		GetVal(config["G"], &G);
		GetVal(config["B"], &B);
		GetVal(config["A"], &A);

		setting->SetColor(R, G, B, A);
	}

	void GetVal(Json::Value &config, char** setting)
	{
		if (config.isNull())
			return;

		*setting = _strdup(config.asCString());
	}

	void GetVal(Json::Value &config, char* setting)
	{
		if (config.isNull())
			return;

		strcpy(setting, config.asCString());
	}

	void LoadColor(Json::Value &config, Color* color)
	{
		static int R, G, B, A;

		color->GetColor(R, G, B, A);

		config["R"] = R;
		config["G"] = G;
		config["B"] = B;
		config["A"] = A;
	}


	void Save(std::string path)
	{
		//path = path + ".vfp";
		Json::Value settings;

		//Aimbot

		settings["Aimbot"]["Enabled"] = g_pOptions->AimbotSettings.enabled;
		settings["Aimbot"]["AimKey"] = g_pOptions->AimbotSettings.aimkey;
		settings["Aimbot"]["UseAimKey"] = g_pOptions->AimbotSettings.useaimkey;
		settings["Aimbot"]["UseBAimKey"] = g_pOptions->AimbotSettings.usebaimkey; 
		settings["Aimbot"]["BAimKey"] = g_pOptions->AimbotSettings.baimkey; 
		settings["Aimbot"]["TeamCheck"] = g_pOptions->AimbotSettings.teamcheck;
		settings["Aimbot"]["EnemyCheck"] = g_pOptions->AimbotSettings.enemycheck;
		settings["Aimbot"]["VisualCheck"] = g_pOptions->AimbotSettings.vischeck;
		settings["Aimbot"]["SmokeCheck"] = g_pOptions->AimbotSettings.smokecheck;
		settings["Aimbot"]["FlashCheck"] = g_pOptions->AimbotSettings.flashcheck;
		settings["Aimbot"]["Smoothed"] = g_pOptions->AimbotSettings.smoothed;
		settings["Aimbot"]["Smoothing"] = g_pOptions->AimbotSettings.smoothing;
		settings["Aimbot"]["FOV"] = g_pOptions->AimbotSettings.fov;
		settings["Aimbot"]["RCS"]["Enabled"] = g_pOptions->AimbotSettings.rcs;
		settings["Aimbot"]["RCS"]["RCSIntensity"] = g_pOptions->AimbotSettings.rcsintesity;
		settings["Aimbot"]["RCS"]["Visible"] = g_pOptions->AimbotSettings.visiblercs; 
		settings["Aimbot"]["BacktrackTicks"] = g_pOptions->AimbotSettings.backtrackingticks; 

		//Triggerbot all new

		settings["Triggerbot"]["Enabled"] = g_pOptions->TriggerbotSettings.enabled;
		settings["Triggerbot"]["Hitchance"] = g_pOptions->TriggerbotSettings.hitchance;
		settings["Triggerbot"]["Delay"] = g_pOptions->TriggerbotSettings.delay;


		//Visuals

		settings["Visuals"]["ESP"]["Enabled"] = g_pOptions->VisualSettings.EspSettings.enabled;
		settings["Visuals"]["ESP"]["Box"] = g_pOptions->VisualSettings.EspSettings.box;
		settings["Visuals"]["ESP"]["Health"] = g_pOptions->VisualSettings.EspSettings.healthbar;
		settings["Visuals"]["ESP"]["Name"] = g_pOptions->VisualSettings.EspSettings.name;
		settings["Visuals"]["ESP"]["Weapon"] = g_pOptions->VisualSettings.EspSettings.weapon;
		settings["Visuals"]["ESP"]["Ammo"] = g_pOptions->VisualSettings.EspSettings.ammo;
		settings["Visuals"]["ESP"]["Skeleton"] = g_pOptions->VisualSettings.EspSettings.skeleton; //new
		settings["Visuals"]["ESP"]["FOVChanger"]["Enabled"] = g_pOptions->VisualSettings.EspSettings.fovchanger; //new
		settings["Visuals"]["ESP"]["FOVChanger"]["FOV"] = g_pOptions->VisualSettings.EspSettings.fov; //new

		settings["Visuals"]["ESP"]["Friendlies"] = g_pOptions->VisualSettings.EspSettings.friendlies;
		settings["Visuals"]["ESP"]["Enemies"] = g_pOptions->VisualSettings.EspSettings.enemies;
		Config::LoadColor(settings["Visuals"]["ESP"]["FriendlyColor"], &g_pOptions->VisualSettings.EspSettings.fboxcolor);
		Config::LoadColor(settings["Visuals"]["ESP"]["EnemyColor"], &g_pOptions->VisualSettings.EspSettings.eboxcolor);
		Config::LoadColor(settings["Visuals"]["ESP"]["EnemySkeletonColor"], &g_pOptions->VisualSettings.EspSettings.eskeletoncolor); //new
		Config::LoadColor(settings["Visuals"]["ESP"]["FriendlySkeletonColor"], &g_pOptions->VisualSettings.EspSettings.fskeletoncolor); //new

		/// WORKING CONFIRMED ABOVE HERE

		settings["Visuals"]["Glow"]["Enabled"] = g_pOptions->VisualSettings.GlowSettings.enabled;
		settings["Visuals"]["Glow"]["Players"] = g_pOptions->VisualSettings.GlowSettings.glowplayers;
		settings["Visuals"]["Glow"]["Friendlies"] = g_pOptions->VisualSettings.GlowSettings.glowfriendlies;
		settings["Visuals"]["Glow"]["Enemies"] = g_pOptions->VisualSettings.GlowSettings.glowenemies;
		settings["Visuals"]["Glow"]["Weapons"] = g_pOptions->VisualSettings.GlowSettings.glowweapons;
		settings["Visuals"]["Glow"]["Grenades"] = g_pOptions->VisualSettings.GlowSettings.glowgrenades;
		settings["Visuals"]["Glow"]["C4"] = g_pOptions->VisualSettings.GlowSettings.glowplantedc4;
		settings["Visuals"]["Glow"]["DefuseKits"] = g_pOptions->VisualSettings.GlowSettings.glowdefusekits;
		Config::LoadColor(settings["Visuals"]["Glow"]["FriendlyColor"], &g_pOptions->VisualSettings.GlowSettings.friendlyglow);
		Config::LoadColor(settings["Visuals"]["Glow"]["EnemyColor"], &g_pOptions->VisualSettings.GlowSettings.enemyglow);
		Config::LoadColor(settings["Visuals"]["Glow"]["WeaponColor"], &g_pOptions->VisualSettings.GlowSettings.weaponglow);
		Config::LoadColor(settings["Visuals"]["Glow"]["GrenadeColor"], &g_pOptions->VisualSettings.GlowSettings.grenadeglow);
		Config::LoadColor(settings["Visuals"]["Glow"]["C4Color"], &g_pOptions->VisualSettings.GlowSettings.c4glow);
		Config::LoadColor(settings["Visuals"]["Glow"]["DefuseColor"], &g_pOptions->VisualSettings.GlowSettings.defuseglow);

		/// WORKING CONFIRMED ABOVE HERE

		settings["Visuals"]["Chams"]["Enabled"] = g_pOptions->VisualSettings.ChamSettings.enabled;
		settings["Visuals"]["Chams"]["FEnabled"] = g_pOptions->VisualSettings.ChamSettings.chamfriendlies;
		settings["Visuals"]["Chams"]["EEnabled"] = g_pOptions->VisualSettings.ChamSettings.chamenemies;
		settings["Visuals"]["Chams"]["FXQZ"] = g_pOptions->VisualSettings.ChamSettings.xqzf;
		settings["Visuals"]["Chams"]["EXQZ"] = g_pOptions->VisualSettings.ChamSettings.xqze;
		Config::LoadColor(settings["Visuals"]["Chams"]["FColor"], &g_pOptions->VisualSettings.ChamSettings.fchamcolor);
		Config::LoadColor(settings["Visuals"]["Chams"]["EColor"], &g_pOptions->VisualSettings.ChamSettings.echamcolor);

		settings["Misc"]["BHOPS"]["Enabled"] = g_pOptions->MiscSettings.bhops;
		settings["Misc"]["BHOPS"]["Type"] = g_pOptions->MiscSettings.bhoptype;
		settings["Misc"]["AutoStrafer"] = g_pOptions->MiscSettings.autostrafer;

		




		
	



		Json::StyledWriter styledWriter;
		std::string strJson = styledWriter.write(settings);
		FILE* file = fopen(path.c_str(), "w+");
		if (file)
		{
			fwrite(strJson.c_str(), 1, strJson.length(), file);
			fclose(file);
		}
	}

	void Load(std::string path)
	{
		//path = path + ".vfp";
		FILE* infile = fopen(path.c_str(), "r");

		if (!infile)
		{
			Save(path);
			return;
		}

		fseek(infile, 0, SEEK_END);
		long filesize = ftell(infile);
		char* buf = new char[filesize + 1];
		fseek(infile, 0, SEEK_SET);
		fread(buf, 1, filesize, infile);
		fclose(infile);

		buf[filesize] = '\0';
		std::stringstream ss;
		ss.str(buf);
		delete[] buf;

		Json::Value settings;
		ss >> settings;

		Config::GetVal(settings["Aimbot"]["Enabled"], &g_pOptions->AimbotSettings.enabled);
		Config::GetVal(settings["Aimbot"]["AimKey"], &g_pOptions->AimbotSettings.aimkey);
		Config::GetVal(settings["Aimbot"]["UseAimKey"], &g_pOptions->AimbotSettings.useaimkey);
		Config::GetVal(settings["Aimbot"]["UseBAimKey"],& g_pOptions->AimbotSettings.usebaimkey); //new
		Config::GetVal(settings["Aimbot"]["BAimKey"],& g_pOptions->AimbotSettings.baimkey); // new
		Config::GetVal(settings["Aimbot"]["TeamCheck"], &g_pOptions->AimbotSettings.teamcheck);
		Config::GetVal(settings["Aimbot"]["EnemyCheck"], &g_pOptions->AimbotSettings.enemycheck);
		Config::GetVal(settings["Aimbot"]["VisualCheck"], &g_pOptions->AimbotSettings.vischeck);
		Config::GetVal(settings["Aimbot"]["SmokeCheck"], &g_pOptions->AimbotSettings.smokecheck);
		Config::GetVal(settings["Aimbot"]["FlashCheck"], &g_pOptions->AimbotSettings.flashcheck);
		Config::GetVal(settings["Aimbot"]["Smoothed"], &g_pOptions->AimbotSettings.smoothed);
		Config::GetVal(settings["Aimbot"]["Smoothing"], &g_pOptions->AimbotSettings.smoothing);
		Config::GetVal(settings["Aimbot"]["FOV"], &g_pOptions->AimbotSettings.fov);
		Config::GetVal(settings["Aimbot"]["RCS"]["Enabled"], &g_pOptions->AimbotSettings.rcs);
		Config::GetVal(settings["Aimbot"]["RCS"]["RCSIntensity"], &g_pOptions->AimbotSettings.rcsintesity);
		Config::GetVal(settings["Aimbot"]["RCS"]["Visible"],& g_pOptions->AimbotSettings.visiblercs); //new
		Config::GetVal(settings["Aimbot"]["BacktrackTicks"], &g_pOptions->AimbotSettings.backtrackingticks); // new

		Config::GetVal(settings["Triggerbot"]["Enabled"], &g_pOptions->TriggerbotSettings.enabled);
		Config::GetVal(settings["Triggerbot"]["Hitchance"], &g_pOptions->TriggerbotSettings.hitchance);
		Config::GetVal(settings["Triggerbot"]["Delay"], &g_pOptions->TriggerbotSettings.delay);

		Config::GetVal(settings["Visuals"]["ESP"]["Enabled"], &g_pOptions->VisualSettings.EspSettings.enabled);
		Config::GetVal(settings["Visuals"]["ESP"]["Box"], &g_pOptions->VisualSettings.EspSettings.box);
		Config::GetVal(settings["Visuals"]["ESP"]["Health"], &g_pOptions->VisualSettings.EspSettings.healthbar);
		Config::GetVal(settings["Visuals"]["ESP"]["Name"], &g_pOptions->VisualSettings.EspSettings.name);
		Config::GetVal(settings["Visuals"]["ESP"]["Weapon"], &g_pOptions->VisualSettings.EspSettings.weapon);
		Config::GetVal(settings["Visuals"]["ESP"]["Ammo"], &g_pOptions->VisualSettings.EspSettings.ammo);
		Config::GetVal(settings["Visuals"]["ESP"]["Friendlies"], &g_pOptions->VisualSettings.EspSettings.friendlies);
		Config::GetVal(settings["Visuals"]["ESP"]["Enemies"], &g_pOptions->VisualSettings.EspSettings.enemies);
		Config::GetVal(settings["Visuals"]["ESP"]["FriendlyColor"], &g_pOptions->VisualSettings.EspSettings.fboxcolor);
		Config::GetVal(settings["Visuals"]["ESP"]["EnemyColor"], &g_pOptions->VisualSettings.EspSettings.eboxcolor);
		Config::GetVal(settings["Visuals"]["ESP"]["Skeleton"], &g_pOptions->VisualSettings.EspSettings.skeleton); //new
		Config::GetVal(settings["Visuals"]["ESP"]["FOVChanger"]["Enabled"], &g_pOptions->VisualSettings.EspSettings.fovchanger); //new
		Config::GetVal(settings["Visuals"]["ESP"]["FOVChanger"]["FOV"], &g_pOptions->VisualSettings.EspSettings.fov); //new
		Config::GetVal(settings["Visuals"]["ESP"]["EnemySkeletonColor"], &g_pOptions->VisualSettings.EspSettings.eskeletoncolor); //new
		Config::GetVal(settings["Visuals"]["ESP"]["FriendlySkeletonColor"], &g_pOptions->VisualSettings.EspSettings.fskeletoncolor); //new

		Config::GetVal(settings["Visuals"]["Glow"]["Enabled"], &g_pOptions->VisualSettings.GlowSettings.enabled);
		Config::GetVal(settings["Visuals"]["Glow"]["Players"], &g_pOptions->VisualSettings.GlowSettings.glowplayers);
		Config::GetVal(settings["Visuals"]["Glow"]["Friendlies"], &g_pOptions->VisualSettings.GlowSettings.glowfriendlies);
		Config::GetVal(settings["Visuals"]["Glow"]["Enemies"], &g_pOptions->VisualSettings.GlowSettings.glowenemies);
		Config::GetVal(settings["Visuals"]["Glow"]["Weapons"], &g_pOptions->VisualSettings.GlowSettings.glowweapons);
		Config::GetVal(settings["Visuals"]["Glow"]["Grenades"], &g_pOptions->VisualSettings.GlowSettings.glowgrenades);
		Config::GetVal(settings["Visuals"]["Glow"]["C4"], &g_pOptions->VisualSettings.GlowSettings.glowplantedc4);
		Config::GetVal(settings["Visuals"]["Glow"]["DefuseKits"], &g_pOptions->VisualSettings.GlowSettings.glowdefusekits);
		Config::GetVal(settings["Visuals"]["Glow"]["FriendlyColor"], &g_pOptions->VisualSettings.GlowSettings.friendlyglow);
		Config::GetVal(settings["Visuals"]["Glow"]["EnemyColor"], &g_pOptions->VisualSettings.GlowSettings.enemyglow);
		Config::GetVal(settings["Visuals"]["Glow"]["WeaponColor"], &g_pOptions->VisualSettings.GlowSettings.weaponglow);
		Config::GetVal(settings["Visuals"]["Glow"]["GrenadeColor"], &g_pOptions->VisualSettings.GlowSettings.grenadeglow);
		Config::GetVal(settings["Visuals"]["Glow"]["C4Color"], &g_pOptions->VisualSettings.GlowSettings.c4glow);
		Config::GetVal(settings["Visuals"]["Glow"]["DefuseColor"], &g_pOptions->VisualSettings.GlowSettings.defuseglow);

		Config::GetVal(settings["Visuals"]["Chams"]["Enabled"], &g_pOptions->VisualSettings.ChamSettings.enabled);
		Config::GetVal(settings["Visuals"]["Chams"]["FEnabled"], &g_pOptions->VisualSettings.ChamSettings.chamfriendlies);
		Config::GetVal(settings["Visuals"]["Chams"]["EEnabled"], &g_pOptions->VisualSettings.ChamSettings.chamenemies);
		Config::GetVal(settings["Visuals"]["Chams"]["FXQZ"], &g_pOptions->VisualSettings.ChamSettings.xqzf);
		Config::GetVal(settings["Visuals"]["Chams"]["EXQZ"], &g_pOptions->VisualSettings.ChamSettings.xqze);
		Config::GetVal(settings["Visuals"]["Chams"]["EColor"], &g_pOptions->VisualSettings.ChamSettings.fchamcolor);
		Config::GetVal(settings["Visuals"]["Chams"]["FColor"], &g_pOptions->VisualSettings.ChamSettings.echamcolor);

		Config::GetVal(settings["Misc"]["BHOPS"]["Enabled"], &g_pOptions->MiscSettings.bhops);
		Config::GetVal(settings["Misc"]["BHOPS"]["Type"], &g_pOptions->MiscSettings.bhoptype);
		Config::GetVal(settings["Misc"]["AutoStrafer"], &g_pOptions->MiscSettings.autostrafer);
	}
}