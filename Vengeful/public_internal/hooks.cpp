#include "hooks.h"
#include "features\Aimbot.hpp"
#include "features\ESP.hpp"
#include "features\Glow.hpp"
#include "features\Backtracking.hpp"
#include "menu\DrawManager.h"
#include "Triggerbot.hpp"
#include "menu\Menu.hpp"
#include "Options.hpp"

namespace hooks {
	void* this_module = nullptr;

	NolanHookManager* client_hook = nullptr;
	NolanHookManager* vguipanel_hook = nullptr;
	NolanHookManager* d3dhook = nullptr;
	NolanHookManager* renderviewhook = nullptr;

	sceneend_function original_sceneend;
	createmove_function original_createmove;
	painttraverse_function original_painttraverse;
	endscene_function original_endscene;
	reset_function original_reset;
	dip_function orginal_dip;
	present_function original_present;
	dopostscreeneffects_function original_dpse;
	ov_function original_ov;

	HRESULT WINAPI reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
	{
		if (!g_pMenu->inited)
			return original_reset(device, pPresentationParameters);
		HRESULT res = original_reset(device, pPresentationParameters);
		g_pDraw->ReleaseObjects();
		if (res >= 0)
		{
			g_pMenu->CreateObjects();
		}
		return res;
	}
	HRESULT WINAPI endscene(LPDIRECT3DDEVICE9 device) {
		if (!g_pMenu->inited)
		{
			g_pMenu->Init(device);
			g_pMenu->inited = true;
		}

		g_pMenu->ResetDraw();

		DWORD oValue;
		device->GetRenderState(D3DRS_COLORWRITEENABLE, &oValue);
		device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);
		g_pMenu->DoFrameUpdate();
		g_pESP->Render_EndScene();

		device->SetRenderState(D3DRS_COLORWRITEENABLE, oValue);

		return original_endscene(device);
	}

	__declspec(naked) void __stdcall createmove_proxy(int sequence_number, float input_sample_frametime, bool active) {
		__asm {
			push ebp
			mov  ebp, esp
			push ebx
			lea  ecx, [esp]
			push ecx
			push dword ptr[active]
			push dword ptr[input_sample_frametime]
			push dword ptr[sequence_number]
			call hooks::createmove
			pop  ebx
			pop  ebp
			retn 0Ch
		}
	}

	void __stdcall createmove(int sequence_number, float input_sample_frametime, bool active, bool& send_packet) {
		original_createmove(sequence_number, input_sample_frametime, active);

		CUserCmd* cmdlist = *(CUserCmd**)((DWORD)g_Input + 0xEC);

		CUserCmd* cmd = &cmdlist[sequence_number % 150];

		if (!cmd || !cmd->command_number)
			return;


		if (g_pOptions->MiscSettings.bhops) {
				if (g_LocalPlayer
					&& g_LocalPlayer->IsAlive()
					&& cmd->buttons & IN_JUMP
					&& !(g_LocalPlayer->m_fFlags() & FL_ONGROUND))
					cmd->buttons &= ~IN_JUMP;
			
		}

		if (g_pOptions->MiscSettings.autostrafer)
		{
			if (g_LocalPlayer->m_fFlags() & FL_ONGROUND) {
				if (cmd->buttons & IN_ATTACK) {
					static bool flip;
					cmd->sidemove = flip ? -450.0f : 450.0f;
					flip = !flip;
				}
			}
		}


		g_pBacktracking->OnCreateMove(cmd);

		if (g_pOptions->AimbotSettings.enabled)
			aimbot->DoAimbotFull(cmd);

		aimbot->DoRCS(cmd);

		if (g_pOptions->TriggerbotSettings.enabled)
			triggerbot->OnCreateMove(cmd);



		CVerifiedUserCmd* verifiedlist = *(CVerifiedUserCmd**)((DWORD)g_Input + 0xF0);

		CVerifiedUserCmd* verified = &verifiedlist[sequence_number % 150];

		verified->m_cmd = *cmd;
		verified->m_crc = cmd->GetChecksum();



	}

	HRESULT WINAPI Present(IDirect3DDevice9* pDevice, RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
	{
		char* waterwark = "♥ vengeful.club - public";
		g_pDraw->Text(waterwark, 30, 10, FONT_LEFT, g_pDraw->fonts.fnormal, true, D3DCOLOR_RGBA(255, 255, 255, 255), D3DCOLOR_RGBA(255, 255, 255, 255));
		return original_present(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	}

	void __stdcall painttraverse(unsigned int panel, bool force_repaint, bool allow_force) {
		original_painttraverse(g_VGuiPanel, panel, force_repaint, allow_force);

		static uintptr_t vpanel = 0;
		if (!vpanel && !strcmp(g_VGuiPanel->GetName(panel), "FocusOverlayPanel"))
			vpanel = panel;
		if (vpanel == panel) {
			g_pESP->GetData_SceneEnd();
		}

	}

	int __stdcall hkDoPostScreenEffects(int a1)
	{
		if (g_LocalPlayer && g_pOptions->VisualSettings.GlowSettings.enabled && !g_EngineClient->IsTakingScreenshot() && g_EngineClient->IsInGame() && g_EngineClient->IsConnected())
			glow->DoGlow();
		return original_dpse(g_ClientMode, a1);
	}

	void* draw_points_ret_addr = nullptr;

	void* traverse_stack(void** ebp)
	{
		if (!ebp)
			return nullptr;

		void** next = *(void***)ebp;

		if (ebp[1] == draw_points_ret_addr)
			return next[4];

		return traverse_stack(next);
	}

	void* get_ent()
	{
		void** data = nullptr;
		__asm mov data, ebp
		return traverse_stack((void**)data);
	}

	bool ShadersCreated = false;


	class Cham
	{
	public:
		void Release()
		{
			Texture->Release();
			Shader->Release();
		}

		IDirect3DTexture9* Texture;
		IDirect3DPixelShader9* Shader;
	};




	Cham FriendlyCham;
	Cham CustomCham;
	Cham EnemyCham;

	//	HRESULT GenerateShader(IDirect3DPixelShader9** Shader, int r, int g, int b, int a)
	//{
	//		char ShaderAsmBuf[256];
	//		ID3DXBuffer* ShaderBuf = NULL;
	//		sprintf_s(ShaderAsmBuf, "ps_3_0\ndef c0, %f, %f, %f, %f\nmov oC0,c0", (float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f);

	//		if (FAILED(D3DXAssembleShader(ShaderAsmBuf, (strlen(ShaderAsmBuf) + 1), NULL, NULL, 0, &ShaderBuf, NULL)))
	//			return E_FAIL;

	//		return d3ddevice9->CreatePixelShader((const DWORD*)ShaderBuf->GetBufferPointer(), Shader);
	//	}


	HRESULT GenerateTexture(IDirect3DTexture9** ppD3Dtex, DWORD color, LPDIRECT3DDEVICE9 pDevice)
	{
		HRESULT hr = pDevice->CreateTexture(8, 8, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, ppD3Dtex, NULL);

		if (FAILED(hr))
			return hr;

		D3DLOCKED_RECT d3dlr;
		(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
		BYTE* pDstRow = (BYTE*)d3dlr.pBits;
		DWORD* pDst32;

		for (int y = 0; y < 8; y++)
		{
			pDst32 = (DWORD*)pDstRow;
			for (int x = 0; x < 8; x++) *pDst32++ = color;
			pDstRow += d3dlr.Pitch;
		}

		(*ppD3Dtex)->UnlockRect(0);

		return S_OK;
	}

#define ApplyPixelShaderCham(VisibleShader, HiddenShader, xqz) { \
	if (xqz) \
	{ \
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); \
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER); \
		pDevice->SetPixelShader(HiddenShader.Shader); \
		orginal_dip(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount); \
	} \
\
	d3ddevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE); \
	d3ddevice9->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL); \
	d3ddevice9->SetPixelShader(VisibleShader.Shader); \
}

#define ApplyTextureCham(VisibleTexture, HiddenTexture, xqz) { \
	if (xqz) \
	{ \
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); \
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER); \
		pDevice->SetTexture(0, HiddenTexture.Texture); \
		orginal_dip(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount); \
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE); \
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL); \
		pDevice->SetTexture(0, VisibleTexture.Texture); \
		orginal_dip(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount); \
	} else { \
\
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE); \
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL); \
	pDevice->SetTexture(0, VisibleTexture.Texture); \
	orginal_dip(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount); \
    }\
}


	Color lastfcolor;
	Color lastecolor;

	Color rainbow;
	bool firsteverinit = false;
	HRESULT WINAPI hkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
	{
		__asm nop
		


		HRESULT hRet = orginal_dip(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
		if (!firsteverinit)
		{
			GenerateTexture(&CustomCham.Texture, D3DCOLOR_RGBA(0,0,0,255),pDevice);
			firsteverinit = true;
		}
		if (!ShadersCreated)
		{
			//	GenerateShader(&FriendlyCham.Shader, g_pOptions.settings_visuals.settings_cham.friendlycham.r(), g_pOptions.settings_visuals.settings_cham.friendlycham.g(), g_pOptions.settings_visuals.settings_cham.friendlycham.b(), g_pOptions.settings_visuals.settings_cham.friendlycham.a());
			//	GenerateShader(&EnemyCham.Shader, g_pOptions.settings_visuals.settings_cham.enemycham.r(), g_pOptions.settings_visuals.settings_cham.enemycham.g(), g_pOptions.settings_visuals.settings_cham.enemycham.b(), g_pOptions.settings_visuals.settings_cham.enemycham.a());



			//GenerateTexture(&RainbowCham.Shader, static_cast<int>(rainbow.r), static_cast<int>(rainbow.g), static_cast<int>(rainbow.b), static_cast<int>(rainbow.a));



			GenerateTexture(&FriendlyCham.Texture, D3DCOLOR_RGBA(g_pOptions->VisualSettings.ChamSettings.fchamcolor.r(), g_pOptions->VisualSettings.ChamSettings.fchamcolor.g(), g_pOptions->VisualSettings.ChamSettings.fchamcolor.b(), g_pOptions->VisualSettings.ChamSettings.fchamcolor.a()),pDevice);
			GenerateTexture(&EnemyCham.Texture, D3DCOLOR_RGBA(g_pOptions->VisualSettings.ChamSettings.echamcolor.r(), g_pOptions->VisualSettings.ChamSettings.echamcolor.g(), g_pOptions->VisualSettings.ChamSettings.echamcolor.b(), g_pOptions->VisualSettings.ChamSettings.echamcolor.a()),pDevice);


			if (!draw_points_ret_addr)
				draw_points_ret_addr = (void*)(Utils::PatternScan(GetModuleHandleW(L"studiorender.dll"), "EB 1F FF 75 F0") - 8);
			ShadersCreated = true;
			lastfcolor = g_pOptions->VisualSettings.ChamSettings.fchamcolor;
			lastecolor = g_pOptions->VisualSettings.ChamSettings.echamcolor;
		}

		//if (g_pOptions.settings_visuals.settings_cham.rendercustomcham)
		//{
		//	D3DXCreateTextureFromFile(pDevice, g_pOptions.settings_visuals.settings_cham.customchampath, &CustomCham.Texture);
		//	g_pOptions.settings_visuals.settings_cham.rendercustomcham = false;
	//	}

		if (lastecolor != g_pOptions->VisualSettings.ChamSettings.echamcolor)
			ShadersCreated = false;

		if (lastfcolor != g_pOptions->VisualSettings.ChamSettings.fchamcolor)
			ShadersCreated = false;

		lastfcolor = g_pOptions->VisualSettings.ChamSettings.fchamcolor;
		lastecolor = g_pOptions->VisualSettings.ChamSettings.echamcolor;

		if (!g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
			return hRet;

		C_BasePlayer* pEntity = (C_BasePlayer*)get_ent();
		C_BasePlayer* local = (C_BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer());

		if (!pEntity)
			return hRet;
		if (!local)
			return hRet;

		if (pEntity && g_pOptions->VisualSettings.ChamSettings.enabled)
		{
			if (pEntity->IsAlive() && pEntity->m_iHealth() > 0)
			{
				if ((pEntity->m_iTeamNum() != local->m_iTeamNum()) && g_pOptions->VisualSettings.ChamSettings.chamenemies) {
					//if (g_pOptions.settings_visuals.settings_cham.custome) {
					//	ApplyTextureCham(CustomCham, CustomCham, g_pOptions.settings_visuals.settings_cham.xqz);
					//}
					ApplyTextureCham(EnemyCham, EnemyCham, g_pOptions->VisualSettings.ChamSettings.xqze);
					
				}
				else if ((pEntity->m_iTeamNum() == local->m_iTeamNum()) && g_pOptions->VisualSettings.ChamSettings.chamfriendlies) {
					//if (g_pOptions.settings_visuals.settings_cham.customf) {
					//	ApplyTextureCham(CustomCham, CustomCham, g_pOptions.settings_visuals.settings_cham.xqz);
					//}
					//else {
						ApplyTextureCham(FriendlyCham, FriendlyCham, g_pOptions->VisualSettings.ChamSettings.xqzf);
					//}
				}

			}
		}

		return hRet;
	}

	void hkOverrideView(CViewSetup* setup) {
		if (g_EngineClient->IsInGame() && g_EngineClient->IsConnected())
		{
			if (g_pOptions->AimbotSettings.visiblercs) {
				ConVar* view_tracking = g_CVar->FindVar("view_recoil_tracking");
				setup->angles -= (g_LocalPlayer->m_aimPunchAngle() * g_pOptions->AimbotSettings.rcsintesity * view_tracking->GetFloat()).ConvertQAngleToVector();
			}
			if (g_pOptions->VisualSettings.EspSettings.fovchanger)
			{
				setup->fov = g_pOptions->VisualSettings.EspSettings.fov;
			}
		}

		original_ov(setup);
	}

	void __fastcall hkSceneEnd(void* thisptr, void* edx)
	{
		original_sceneend(thisptr, edx);
		g_pESP->GetData_SceneEnd();
	}

	

	void initialize(void* module_handle) {
		this_module = module_handle;


		NolanHookManager* client_hook = new NolanHookManager(g_CHLClient);
		NolanHookManager* vguipanel_hook = new NolanHookManager(g_VGuiPanel);
		NolanHookManager* d3dhook = new NolanHookManager(g_D3DDevice9);
		NolanHookManager* renderhook = new NolanHookManager(g_RenderView);
		NolanHookManager* clientmodehook = new NolanHookManager(g_ClientMode);

		original_dpse = (dopostscreeneffects_function)clientmodehook->HookFunction(44, hkDoPostScreenEffects);
		original_createmove = (createmove_function)client_hook->HookFunction(22, createmove_proxy);
		//original_painttraverse = (painttraverse_function)vguipanel_hook->HookFunction(41, painttraverse);
		original_reset = (reset_function)d3dhook->HookFunction(16, reset);
		original_endscene = (endscene_function)d3dhook->HookFunction(42, endscene);
		orginal_dip = (dip_function)d3dhook->HookFunction(82, hkDrawIndexedPrimitive);
		original_present = (present_function)d3dhook->HookFunction(17, Present);
		original_sceneend = (sceneend_function)renderhook->HookFunction(9, hkSceneEnd);
		original_ov = (ov_function)clientmodehook->HookFunction(18, hkOverrideView);

		clientmodehook->HookTable(true);
		client_hook->HookTable(true);
		//vguipanel_hook->HookTable(true);
		d3dhook->HookTable(true);
		renderhook->HookTable(true);
	}

	void destroy() {
		client_hook->HookTable(false);
		vguipanel_hook->HookTable(false);

		FreeLibraryAndExitThread((HMODULE)this_module, 0);
	}
}