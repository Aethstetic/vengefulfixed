#pragma once
#include "..\sdk\sdk.hpp"
#include "..\sdk\csgostructs.hpp"

#include <deque>
#include <d3dx9.h>
struct BOXESP
{
	float x;
	float y;
	int w;
	int h;
	Color color;
};

struct HEALTHBARESP
{
	int topx;
	int topy;
	int bottomx;
	int bottomy;
	float health;
	bool render;
};

struct NAMEESP
{
	int x;
	int y;
	LPD3DXFONT font;
	std::string message;
};
struct DrawPos
{
	int x1;
	int y1;
	int x2;
	int y2;
};

struct SKELETONESP
{
	DrawPos BonesToDraw[255];
	bool draw;
	int numbones;
	Color color;
};


class CESP
{
public:
	SKELETONESP skeletons[64];
	BOXESP boxes[64];
	HEALTHBARESP healthbars[64];
	NAMEESP playernames[64];
	NAMEESP ammonames[64];
	NAMEESP weaponnames[64];
	void GetData_SceneEnd();
	void Render_EndScene();
	void RenderHealthBars();
	void RenderWeaponNames();
	void RenderAmmoNames();
	void RenderPlayerNames();
	void RenderSkeletons();
	void RenderBoxes();
	void PlayerBox(float x, float y, float w, float h, Color clr);
	void HealthBar(Vector bot, Vector top, float health);
};

extern std::unique_ptr<CESP> g_pESP;