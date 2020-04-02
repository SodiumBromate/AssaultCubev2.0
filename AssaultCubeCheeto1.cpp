#include <iostream>
#include <vector>
#include <windows.h>
#include "functions.h"
#include "globals.hpp"
#include "singleton.hpp"


int main()
{

	std::cout << "Process Handle: " << procAndAddr::instance()->hProcess << "\n";                                         //prints process handle
	std::cout << "Process ID: " << procAndAddr::instance()->procID << "\n" << "\n";                                       //prints process id

	std::cout << "Sodium's Cheeto\n"
		<< "---------------------------------------------\n"
		<< "Press H for Infinite Health\n"
		<< "Press J for Infinite Ammo\n"
		<< "Press K for No-recoil\n"                                                                                     //quick console menu
		<< "Press L for Rapid Fire!\n"
		<< "Press M for Sanik Mode!\n"
		<< "---------------------------------------------\n";


	if (!procAndAddr::instance()->procID)                                                                                 //if procID is not found then go into the loop
	{
		std::cout << "Process not found! Press enter to close\n";
		(void)getchar();                                                                         //dont need to worry because we dont need return value
		return 0;
	}
	

	DWORD terminStatus = 0;

	while (GetExitCodeProcess(procAndAddr::instance()->hProcess, &terminStatus) && terminStatus == STILL_ACTIVE)
	{
		infHealth();                                                         //health function (infHealth.cpp)

		infAmmo();                                                           //ammo function (infAmmo.cpp)
        
		noRecoil();                                                          //recoil function(noRecoil.cpp)

		fireRate();                                                        //fire rate function(rapidFire.cpp)

		speed();                                                           //speed function(speed.cpp)

		if (GetAsyncKeyState(VK_INSERT) & 1)                                                     //if you press INS the cheat will stop and close
		{
			std::cout << "Cheat closed\n";
			return 0;
		}


		Sleep(10);
	}
	
	std::cout << "Process not found, press enter to exit\n";
    (void)getchar(); //dont need to worry because we dont need return value
    return 0;
}


