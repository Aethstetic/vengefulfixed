#include <Windows.h>
#include <memory>
#include "hooks.h"
#include "SDK/sdk.hpp"
#include "Helpers\utils.hpp"


void initialization_thread(void* module_handle) {
	Interfaces::Initialize();
	Interfaces::Dump();

	NetvarSys::Get().Initialize();
	hooks::initialize(module_handle);
}

bool __stdcall DllMain(HINSTANCE dll_instance, DWORD reason, void* reserved) {
	if (reason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)initialization_thread, dll_instance, 0, 0);
	//else
	//	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)hooks::destroy, 0, 0, 0);

	return true;
}