#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "sdk\sdk.hpp"
#include "sdk\csgostructs.hpp"
#include "utils\vmt.h"

namespace hooks {
	extern void* this_module;

	using createmove_function = void(WINAPI *)(int, float, bool);
	typedef void(__thiscall* painttraverse_function)(void*, unsigned int, bool, bool);
	typedef HRESULT(WINAPI* endscene_function)(LPDIRECT3DDEVICE9 device);
	typedef int(__thiscall* dopostscreeneffects_function)(void*, int);
	typedef HRESULT(WINAPI* reset_function)(LPDIRECT3DDEVICE9 device, D3DPRESENT_PARAMETERS* pPresentationParameters);
	typedef HRESULT(WINAPI* present_function)(IDirect3DDevice9*, RECT*, CONST RECT*, HWND, CONST RGNDATA*);
	using sceneend_function = void(__fastcall*)(void*, void*);
	using ov_function = void(__stdcall*)(CViewSetup*);

	using dip_function = HRESULT(WINAPI*)(LPDIRECT3DDEVICE9, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);


	extern NolanHookManager* client_hook;
	extern NolanHookManager* vguipanel_hook;

	extern ov_function original_ov;
	extern dopostscreeneffects_function original_dpse;
	extern sceneend_function original_sceneend;
	extern createmove_function original_createmove;
	extern present_function original_present;
	extern painttraverse_function original_painttraverse;
	extern endscene_function original_endscene;
	extern reset_function original_reset;
	extern dip_function orginal_dip;



	void __stdcall createmove_proxy(int sequence_number, float input_sample_frametime, bool active);
	void __stdcall createmove(int sequence_number, float input_sample_frametime, bool active, bool& send_packet);
	void __stdcall painttraverse(unsigned int panel, bool force_repaint, bool allow_force);

	void initialize(void* module_handle);
	void destroy();
};