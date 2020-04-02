#pragma once

#include "functions.h"
#include "singleton.hpp"

class procAndAddr : public singleton<procAndAddr>
{
SETUP_SINGLETON(procAndAddr);
public:
	DWORD procID = GetProcID(L"ac_client.exe");

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);

	uintptr_t moduleBase = GetModuleBaseAddress(procID, L"ac_client.exe"),
		localPlayerPtrBase = moduleBase + 0x10F4F4,
		healthAddr = findDMAAddy(hProcess, localPlayerPtrBase, { 0xF8 }),
		fireRateAddr = findDMAAddy(hProcess, localPlayerPtrBase, {0x374, 0xC, 0x10A}),
		velocityZAddr = findDMAAddy(hProcess, localPlayerPtrBase, { 0x18 }),
		velocityXYAddr = findDMAAddy(hProcess, localPlayerPtrBase, { 0x14 }),
		velocityYXAddr = findDMAAddy(hProcess, localPlayerPtrBase, { 0x10 });

	std::vector <unsigned int> velocityAddr = { velocityZAddr, velocityXYAddr, velocityYXAddr };
};

