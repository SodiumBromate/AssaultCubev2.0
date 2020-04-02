#include <iostream>
#include <vector>
#include <windows.h>
#include "proc.h"

void ammo(uintptr_t ptr2, HANDLE hProcess)
{
	//Resolve our ammo,health whatever pointer chain
	std::vector <unsigned int> ammoOffsets = { 0x374, 0x14, 0x0 };
	uintptr_t ammoAddr = findDMAAddy(hProcess, ptr2, ammoOffsets);

	std::cout << "Ammo Address = " << "0x" << std::hex << ammoAddr << std::endl;

	//Read ammo,health whatever value

	int ammoValue = 0;

	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);

	std::cout << "Old Ammo = " << std::dec << ammoValue << std::endl;

	//Write to ammo,health whatever value

	int newAmmo = 99999;
	WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);

	//Read out again to confirm it works

	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);

	std::cout << "New Ammo = " << newAmmo << std::endl;
}


