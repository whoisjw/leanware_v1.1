#include "../functions/global.h"
#include "../functions/includes.h"


DWORD getModuleAddress(DWORD pid, const wchar_t* name) {

	DWORD moduleBase = 0; //initialize var for pointer 
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);  //create snapshot 

	if (hSnapshot != INVALID_HANDLE_VALUE) { //only runs if csgo handle is valid 

		MODULEENTRY32 moduleEntry;
		moduleEntry.dwSize = sizeof(MODULEENTRY32);

		if (Module32First(hSnapshot, &moduleEntry)) {

			do {

				if (wcscmp(moduleEntry.szModule, name) == 0) {

					moduleBase = (DWORD)moduleEntry.modBaseAddr;
					break;
				}

			} while (Module32Next(hSnapshot, &moduleEntry));
		}
		CloseHandle(hSnapshot);
	}

	return moduleBase; //returns pointer

}

