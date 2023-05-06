#pragma once

#include "trigger.h"

void trigger() {

	while (true) {

		Sleep(1);

		if (toggle::Trigger) { //check for toggle 

			DWORD cheater = readMem<DWORD>((DWORD)clientBase + offset::dwLocalPlayer); //find local player
			int myTeam = readMem<int>(cheater + offset::m_iTeamNum); //find local player's team
			int crosshair = readMem<int>(cheater + offset::CrosshairID); //check what the player's crosshair is aiming at 

			if (crosshair && crosshair <= 64) { //check that the crosshair is aiming at a player

				DWORD player = readMem<DWORD>((DWORD)clientBase + offset::dwEntityList + (crosshair - 1) * 0x10);
				int playerTeam = readMem<int>(player + offset::m_iTeamNum);
				int playerHealth = readMem<int>(player + offset::m_iHealth);

				if (playerTeam != myTeam && playerHealth > 0) { //check that the crosshair is aiming at an enemy 

					Sleep(vals::triggerDelay);
					writeMem<int>(clientBase + offset::dwForceAttack, 6);
					Sleep(30);
					writeMem<int>(clientBase + offset::dwForceAttack, 4);
					/*
					* it would be better practice to simulate a click as directly writing to memory can be 
					* detected by Valve Anti Cheat however this project was only created to learn so that wasn't
					* important to me.
					*/

				}

			}

		}

	}

}