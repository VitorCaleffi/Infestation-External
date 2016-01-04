#include "Memory.h"

namespace Memory
{
	struct Module_t
	{
		DWORD		dwBase;
		DWORD		dwSize;
		std::string	szName;

	}Module[MAX_MEMORY_MODULE];

	
	HANDLE	hProcess = NULL;
	HWND	hWindow = NULL;
	int		iLastAddedModule = 0;

	DWORD GameAddress = 0;
	DWORD GameWorldAddress = 0;
	DWORD LocalPlayerAddress = 0;
	DWORD baseAddress = 0;
	DWORD ProcessID = 0x0;
	
	BOOL CALLBACK enumWindowsProc(__in  HWND hWnd,__in  LPARAM lParam) 
	{
		DWORD pID;

		if (hWindow != NULL)
			return true;

		GetWindowThreadProcessId(hWnd, &pID);

		if (pID == ProcessID)
			hWindow = hWnd;

		return true;
	}

	int GetLastAddedModule(void)
	{
		return iLastAddedModule;
	}

	extern void GetGame()
	{
		GameAddress = Read<DWORD>(GameOffset + baseAddress);
		GameAddress ^= GameXOR;
	}

	extern void GetGameWorld()
	{
		GameWorldAddress = Read<DWORD>(GameWorldOffset + baseAddress);
		GameWorldAddress ^= GameWorldXOR;
	}

	extern void GetLocalPlayer()
	{
		LocalPlayerAddress = Read<DWORD>(GameAddress + LocalPlayerOffset);
		LocalPlayerAddress ^= LocalPlayerXOR;
	}

	DWORD GetModuleSize(std::string szModuleName)
	{
		for (int i = 0; i < GetLastAddedModule(); i++)
		{
			if (!strcmp((char*)szModuleName.c_str(), (char*)Module[i].szName.c_str()))
				return Module[i].dwSize;
		}
		return 0x0;
	}

	MODULEENTRY32 GetModuleBaseExtern(std::string szModuleName)
	{
		MODULEENTRY32	ME32 = { 0 };
		HANDLE			hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);

		if (!hSnapshot)
			return ME32;

		ME32.dwSize = sizeof(ME32);

		BOOL			bModule = Module32First(hSnapshot, &ME32);

		while (bModule)
		{
			if (!strcmp((char*)ME32.szModule, (char*)szModuleName.c_str()))
			{
				CloseHandle(hSnapshot);
				return ME32;
			}
			bModule = Module32Next(hSnapshot, &ME32);
		}
		CloseHandle(hSnapshot);
		return ME32;
	}

	void SetLastAddedModule(int Value)
	{
		iLastAddedModule = Value;
	}

	bool Initialize(std::string szGameWindowTitle)
	{
		PROCESSENTRY32   pe32;
		HANDLE         hSnapshot = NULL;

		pe32.dwSize = sizeof(PROCESSENTRY32);
		hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (Process32First(hSnapshot, &pe32))
		{
			do
			{
				if (strcmp(pe32.szExeFile, szGameWindowTitle.c_str()) == 0)
				{
					ProcessID = pe32.th32ProcessID;
				}
			} 
			while (Process32Next(hSnapshot, &pe32));
		}

		if (hSnapshot != INVALID_HANDLE_VALUE)
			CloseHandle(hSnapshot);

		
		if (!ProcessID)
			return false;

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID);

		if (!hProcess)
			return false;

		MODULEENTRY32 ModBuff = GetModuleBaseExtern(szGameWindowTitle.c_str());
		baseAddress = (DWORD)ModBuff.modBaseAddr;

		if (!baseAddress)
			return false;

		EnumWindows(enumWindowsProc, NULL);

		if (hWindow == NULL)
			return false;

		return true;
	}
	DWORD GetModule(std::string szName)
	{
		for (int i = 0; i < GetLastAddedModule(); i++)
		{
			if (!strcmp((char*)szName.c_str(), (char*)Module[i].szName.c_str()))
				return Module[i].dwBase;
		}
		return 0x0;
	}
	void AddModule(std::string szName, std::string szModuleName)
	{
		int i = GetLastAddedModule();

		if (i > MAX_MEMORY_MODULE - 1)
			return;

		Module[i].dwBase = 0x0;
		Module[i].szName = szName;

		while (Module[i].dwBase == 0x0)
		{
			MODULEENTRY32 ModBuff = GetModuleBaseExtern(szModuleName);
			Module[i].dwBase = (DWORD)ModBuff.modBaseAddr;
			Module[i].dwSize = (DWORD)ModBuff.modBaseSize;
			Sleep(5);
		}

		SetLastAddedModule(i + 1);
	}
}