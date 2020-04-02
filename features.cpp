#include <windows.h>
#include <iostream>
#include "functions.h"
#include "globals.hpp"

bool bAmmo = false, bHealth = false, bRecoil = false, bFireRate = false, bSpeed = false;

void infAmmo()
{
	if (GetAsyncKeyState(0x4A) & 1)
	{
		bAmmo = !bAmmo;

		std::cout << "Unlimited Ammo!\n";

		if (bAmmo)
		{
			mem::PatchEx((BYTE*)(procAndAddr::instance()->moduleBase + 0x637E9), (BYTE*)"\xFF\x06", 2, procAndAddr::instance()->hProcess); //when we find what accesses we end up on the address 0x637E9 and if you change dec [esi] to inc [esi]
		}                                                                                //the bytes go from FF 0E to FF 06 so we are changing the bytes to increment
		else
		{
			mem::PatchEx((BYTE*)(procAndAddr::instance()->moduleBase + 0x637E9), (BYTE*)"\xFF\x0E", 2, procAndAddr::instance()->hProcess);
		}
	}
}

void infHealth()
{
	if (GetAsyncKeyState(0x48) & 1)
	{
		bHealth = !bHealth;

		std::cout << "Unlimited Health!\n";

	}

	if (bHealth)
	{
		mem::PatchEx((BYTE*)procAndAddr::instance()->healthAddr, (BYTE*)&newValue, sizeof(newValue), procAndAddr::instance()->hProcess);     //assign a new health value to the current one

	}
}

void noRecoil()
{
	if (GetAsyncKeyState(0x4B) & 1)
	{
		bRecoil = !bRecoil;

		std::cout << "No recoil!\n";

		if (bRecoil)
		{
			mem::NopEx((BYTE*)(procAndAddr::instance()->moduleBase + 0x63786), 10, procAndAddr::instance()->hProcess);   // gets rid of the bytes that call the recoil function
		}
		else
		{
			mem::PatchEx((BYTE*)(procAndAddr::instance()->moduleBase + 0x63786), (BYTE*)"\x50\x8d\x4c\x24\x1c\x51\x8b\xce\xff\xd2", 10, procAndAddr::instance()->hProcess); // replaces the bytes 
		}
	}
}

void fireRate()
{
	if (GetAsyncKeyState(0x4C) & 1)
	{
		bFireRate = !bFireRate;

		std::cout << "Rapid Fire!\n";
	}
	if (bFireRate)
	{
		mem::PatchEx((BYTE*)procAndAddr::instance()->fireRateAddr, (BYTE*)&shootSpeed, sizeof(shootSpeed), procAndAddr::instance()->hProcess);  //assigns a new fire rate to the current one
	}
}

void speed()
{
	if (GetAsyncKeyState(0x4D) & 1)
	{
		bSpeed = !bSpeed;

		std::cout << "Sanik mode!\n";
	}
	if (bSpeed)
	{
		for (int i = 0; i < 3; i++)                                                                       //(i know the speedhack is pretty weird but its my first attempt at it)
		{
			float SpeedValue = 0;
			ReadProcessMemory(procAndAddr::instance()->hProcess, (BYTE*)procAndAddr::instance()->velocityAddr[i], &SpeedValue, sizeof(SpeedValue), 0);         //reads the velocity value of all 3 addresses
			float OldSpeedValue = SpeedValue / 2.4;                                                                                                            //divides the old speed value by 2.1
			float newSpeedValue = OldSpeedValue * 3;                                                                                                           //multiplies the new speed value by 3 making you go slightly faster
			mem::PatchEx((BYTE*)procAndAddr::instance()->velocityAddr[i], (BYTE*)&newSpeedValue, sizeof(newSpeedValue), procAndAddr::instance()->hProcess);    //assigns the new value to all 3 addresses
			Sleep(20);

		}                                                                                                 //modifying the 2.4 may send you into hyperdrive (you have been warned!)
	}
}