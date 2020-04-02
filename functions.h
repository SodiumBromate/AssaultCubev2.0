#pragma once

#include <vector>
#include <windows.h>
#include <TlHelp32.h>

// (I know global variables are bad but this one does not need to change so its fine chief)
const int newValue = 9999; //value for health
const int shootSpeed = 25;  //makes you shoot as fast as possible


//byte patching functions

namespace mem
{
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);                    //used to patch bytes 

	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);                                 //used to nop bytes

}

//process

DWORD GetProcID(const wchar_t* procNAME);                                                      //procID function

uintptr_t GetModuleBaseAddress(DWORD procID, const wchar_t* modName);                          //getmodbaseaddress function

uintptr_t findDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);          //resolves the address when you feed it offsets + base

//features

void infHealth(); //health

void infAmmo();  //ammo

void noRecoil(); //recoil

void fireRate(); //firerate

void speed(); //speed








