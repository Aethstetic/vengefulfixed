#pragma once
#include <memory>
#include <d3d9.h>
#include <d3dx9.h>
#define CHEAT_NAME "blackman"
#define AIMBOT_TAB_NAME "Aimbot"
#define VISUAL_TAB_NAME "Visuals"
#define MISC_TAB_NAME "Misc"
class CMenu {
public:
	void Init(LPDIRECT3DDEVICE9 device);
	void RenderTabs();
	void RenderAimbotTab();
	void RenderVisualSubTabs();
	void RenderColorTab();
	void RenderTriggerbotTab();
	void RenderConfigTab();
	void RenderVisualTab();
	void ResetDraw();
	void RenderMiscTab();
	void DoFrameUpdate();
	void CreateObjects();

	void ReleaseObjects();

	bool opened;

	bool inited;

	int currentab;
	int currentabv;
	int currentabvtype;
	char* optiontext = "";


private:
	bool togglepress;
	bool last;
};

extern std::unique_ptr<CMenu> g_pMenu;