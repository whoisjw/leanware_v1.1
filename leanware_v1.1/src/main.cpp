//essential includes
#include "../functions/includes.h"
#include "../functions/global.h" 
#include "memory.h"

//includes for cheats
#include "../cheats/visuals.h"
#include "../cheats/misc.h"
#include "../cheats/trigger.h"
#include "../cheats/aim.h"
using namespace std;

string aimMsg = "Aimbot - F6 [OFF] (feature down)\n",
radarMsg = "Radar reveal - F5 [OFF]\n",
espMsg = "Glow - F8 [OFF]\n",
bhopMsg = "Bhop - F7 [OFF]\n",
trigMsg = "Triggerbot - F9 [OFF] ",
jsMsg = "Auto jumpscout - F4 [OFF] (keybind = c)\n";

void drawTitle() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 5); //make it purple

	std::cout << "##       ########    ###    ##    ## ##      ##    ###    ########  ########    ##  #######  \n"
		<< "##       ##         ## ##   ###   ## ##  ##  ##   ## ##   ##     ## ##         ##  ##     ## \n"
		<< "##       ##        ##   ##  ####  ## ##  ##  ##  ##   ##  ##     ## ##        ##          ## \n"
		<< "##       ######   ##     ## ## ## ## ##  ##  ## ##     ## ########  ######   ##     #######  \n"
		<< "##       ##       ######### ##  #### ##  ##  ## ######### ##   ##   ##        ##          ## \n"
		<< "##       ##       ##     ## ##   ### ##  ##  ## ##     ## ##    ##  ##         ##  ##     ## \n"
		<< "######## ######## ##     ## ##    ##  ###  ###  ##     ## ##     ## ########    ##  #######  \n"
		<< "---------------------------------------------------------------------------------------------\n";

	SetConsoleTextAttribute(hConsole, 7);
}

void drawMenu(string a, string b, string c, string d, string e, string f) {

	system("cls"); //bad practice but this program is only compatible with windows systems anyway

	drawTitle();

	cout << f
		<< a
		<< b
		<< c
		<< d
		<< e << "Delay: " << vals::triggerDelay << " [SHIFT + F9]\n"; //outputs what cheats are active, is updated when one is turned on or off

}

int main() {

	drawTitle();

	HWND hwnd;

	DWORD pID;

	do {

		//find csgo window
		hwnd = FindWindowA(0, "Counter-Strike: Global Offensive - Direct3D 9");
		Sleep(50);

	} while (!hwnd); //until it is found

	GetWindowThreadProcessId(hwnd, &pID);

	process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID); //request elevated access to the game

	std::cout << "Searching for client.dll";

	do {

		Sleep(10);
		std::cout << ".";
		clientBase = getModuleAddress(pID, L"client.dll");

	} while (!clientBase);


	std::cout << "\nSearching for engine.dll";

	do {

		Sleep(10);
		std::cout << ".";
		engineBase = getModuleAddress(pID, L"engine.dll");

	} while (!engineBase);

	/*
	* Threads for each cheat that run the functions separately
	*/
	thread GLOW(glow);
	thread BHOP(bhop);
	thread TRIGGER(trigger);
	thread AIM(aim);
	thread RADAR(radar);
	thread JUMPSCOUT(jumpScout);
	thread SOUNDING(soundEsp);

	drawMenu(radarMsg, aimMsg, bhopMsg, espMsg, trigMsg, jsMsg);

	while (true) {

		Sleep(100);

		/*
		* Each statement activates/deactivates a feature in the cheat
		*/

		if (GetAsyncKeyState(VK_F4)) //check for F4 key press 
		{

			toggle::Jump = !toggle::Jump; //toggles true/false for said feature

			if (toggle::Jump) {

				jsMsg = "Auto jumpscout - F4 [ON] (keybind = c)\n"; //updates message on menu

			}

			else {

				jsMsg = "Auto jumpscout - F4 [OFF] (keybind = c)\n";

			}

			drawMenu(radarMsg, aimMsg, bhopMsg, espMsg, trigMsg, jsMsg); //redraws menu with the change made

		}

		if (GetAsyncKeyState(VK_F8)) {

			toggle::Glow = !toggle::Glow;

			if (toggle::Glow) {

				espMsg = "Glow - F8 [ON]\n";

			}

			else {

				espMsg = "Glow - F8 [OFF]\n";

			}

			drawMenu(radarMsg, aimMsg, bhopMsg, espMsg, trigMsg, jsMsg);

		}

		if (GetAsyncKeyState(VK_F7)) {

			toggle::Bhop = !toggle::Bhop;

			if (toggle::Bhop) {

				bhopMsg = "Bhop - F7 [ON]\n";

			}

			else {

				bhopMsg = "Bhop - F7 [OFF]\n";

			}

			drawMenu(radarMsg, aimMsg, bhopMsg, espMsg, trigMsg, jsMsg);

		}

		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState(VK_F9)) {

			if (vals::triggerDelay == 0) {

				vals::triggerDelay = 50;

			}

			else if (vals::triggerDelay == 50) {

				vals::triggerDelay = 0;

			}

			drawMenu(radarMsg, aimMsg, bhopMsg, espMsg, trigMsg, jsMsg);

		}

		if (GetAsyncKeyState(VK_F9)) {

			toggle::Trigger = !toggle::Trigger;

			if (toggle::Trigger) {

				trigMsg = "Triggerbot - F9 [ON] ";

			}

			else {

				trigMsg = "Triggerbot - F9 [OFF] ";

			}

			drawMenu(radarMsg, aimMsg, bhopMsg, espMsg, trigMsg, jsMsg);

		}

		if (GetAsyncKeyState(VK_F6)) {

			toggle::Aim = !toggle::Aim;

			if (toggle::Aim) {

				aimMsg = "Aimbot - F6 [ON] (feature down)\n";

			}

			else {

				aimMsg = "Aimbot - F6 [OFF] (feature down)\n";

			}

			drawMenu(radarMsg, aimMsg, bhopMsg, espMsg, trigMsg, jsMsg);

		}
		if (GetAsyncKeyState(VK_F5)) {

			toggle::Radar = !toggle::Radar;

			if (toggle::Radar) {

				radarMsg = "Radar reveal - F5 [ON]\n";

			}

			else {

				radarMsg = "Radar reveal - F5 [OFF]\n";

			}

			drawMenu(radarMsg, aimMsg, bhopMsg, espMsg, trigMsg, jsMsg);

		}

	}
}
