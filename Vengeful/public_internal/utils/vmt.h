#pragma once
#include <Windows.h>

class CVMT
{
public:
	template<typename type> type getvfunc(void* base, uintptr_t index) {
		uintptr_t** VTablePointer = (uintptr_t**)base;
		uintptr_t* VTableFunctionBase = *VTablePointer;
		uintptr_t dwAddress = VTableFunctionBase[index];
		return (type)(dwAddress);
	}

	inline void* GetFunction(void* Instance, int Index) {
		uintptr_t VirtualFunction = (*(uintptr_t*)Instance) + 0x4 * Index;
		return (void*)*((uintptr_t*)VirtualFunction);
	}
}; 

extern CVMT VMT;


#define k_page_writeable (PAGE_READWRITE | PAGE_EXECUTE_READWRITE)
#define k_page_readable (k_page_writeable|PAGE_READONLY|PAGE_WRITECOPY|PAGE_EXECUTE_READ|PAGE_EXECUTE_WRITECOPY)
#define k_page_offlimits (PAGE_GUARD|PAGE_NOACCESS)
class NolanHookManager
{
public:
	NolanHookManager() {}

	~NolanHookManager() {
		this->HookTable(false);
	}
	NolanHookManager(void* Interface)
	{
		this->Init(Interface);
	}
	/*Inits the function*/
	bool Init(void* Interface)
	{
		pOrgTable = *(void**)Interface;
		this->count = this->GetCount();
		pCopyTable = malloc(sizeof(void*)* count);
		memcpy(pCopyTable, pOrgTable, sizeof(void*) * count);
		pObject = (DWORD*)Interface;
		return true;
	}
	/*Hook/Unhook*/
	void HookTable(bool hooked)
	{
		if (hooked)
		{
			*pObject = (DWORD)pCopyTable;
		}
		else
		{
			*pObject = (DWORD)pOrgTable;
		}
	}
	/*Hooks function*/
	void* HookFunction(int Index, void* hkFunction)
	{
		if (Index < this->count && Index >= 0)
		{
			((DWORD*)pCopyTable)[Index] = (DWORD)hkFunction;
			return (void*)((DWORD*)pOrgTable)[Index];
		}
		return NULL;
	}

private:
	/*Returns if you can read the pointer*/
	bool CanReadPointer(void* table)
	{
		MEMORY_BASIC_INFORMATION mbi;
		if (table == nullptr) return false;
		if (!VirtualQuery(table, &mbi, sizeof(mbi))) return false;
		if (mbi.Protect & k_page_offlimits) return false;
		return (mbi.Protect & k_page_readable);
	}
	/*Gets VMT count*/
	int GetCount()
	{
		int index = 0;
		void** table = ((void**)pOrgTable);
		for (void* fn; (fn = table[index]) != nullptr; index++)
		{
			if (!this->CanReadPointer(fn)) break;
		}
		return index;
	}
	int count;
	void* pCopyTable;
	DWORD* pObject;
	void* pOrgTable;
};