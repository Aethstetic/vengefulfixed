#pragma once
#include "Config.h"
#include "sdk\misc\Color.hpp"
#include <memory>
struct AimSettings { //Aimbot Settings Here
	int aimkey;
	bool useaimkey;
	int baimkey;
	bool usebaimkey;
	bool enabled;
	bool teamcheck;
	bool enemycheck;
	bool vischeck;
	bool jumpcheck;
	bool smokecheck;
	bool smoothed;
	float fov;
	float rcsintesity;
	bool flashcheck;
	float smoothing = 1.0f;
	bool rcs;
	int backtrackingticks;
	bool backtracking;
	bool visiblercs;
};
struct RageBotSettings {

};
struct TriggerbotSettings
{
	bool enabled;
	float hitchance = 5.0f;
	float delay;
};

struct ESPSettings
{
	bool enabled;
	bool box;
	bool healthbar;
	bool name;
	bool weapon;
	bool ammo;
	bool enemies;
	bool friendlies;
	bool skeleton;
	bool fovchanger;
	float fov;
	Color fboxcolor = Color(0, 255, 0, 255);
	Color eboxcolor = Color(255, 0, 0, 255);
	Color fskeletoncolor = Color(0, 255, 0, 255);
	Color eskeletoncolor = Color(255, 0, 0, 255);
};
struct GlowSettings
{
	bool enabled;
	bool glowplayers;
	bool glowfriendlies;
	bool glowenemies;
	bool glowweapons;
	bool glowgrenades;
	bool glowplantedc4;
	bool glowdefusekits;
	Color enemyglow = Color(255, 0, 0, 255);
	Color friendlyglow = Color(0, 255, 0, 255);
	Color weaponglow = Color(0, 0, 255, 255);
	Color grenadeglow = Color(255, 255, 0, 255);
	Color c4glow = Color(0, 255, 255, 255);
	Color defuseglow = Color(255, 255, 255, 255);
};
struct ChamSettings
{
	bool enabled;
	bool chamfriendlies;
	bool chamenemies;
	bool xqzf;
	bool xqze;
	Color echamcolor = Color(255, 0, 0, 255);
	Color fchamcolor = Color(0, 255, 0, 255);
};

struct VisualSettings { //Visual Settings Here
	ESPSettings EspSettings;
	GlowSettings GlowSettings;
	ChamSettings ChamSettings;
};
struct MiscSettings { //Misc Settings Here
	bool bhops;
	int bhoptype;
	bool autostrafer;
};


class COptions
{
public:
	AimSettings AimbotSettings;
	VisualSettings VisualSettings;
	MiscSettings MiscSettings;
	RageBotSettings RageBotSettings;
	TriggerbotSettings TriggerbotSettings;
};



extern std::unique_ptr<COptions> g_pOptions;