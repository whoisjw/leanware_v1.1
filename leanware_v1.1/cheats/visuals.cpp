#include "visuals.h"

void glow() {

	while (true) {

		Sleep(1);

		if (toggle::Glow) { //check if toggled on 

			DWORD cheater = readMem<DWORD>(clientBase + offset::dwLocalPlayer); //find local player

			DWORD glowObject = readMem<DWORD>(clientBase + offset::dwGlowObjectManager); //find cs:go's glow value
			int myTeam = readMem<int>(cheater + offset::m_iTeamNum); //find player's team

			for (int i = 0; i < 64; i++) { //64 is the max players in a game so the cheat iterates over all 64 possible players

				DWORD entity = readMem<DWORD>(clientBase + offset::dwEntityList + i * 0x10); //player

				if (entity != NULL) { //check to see if the player exists (for example, in a competitive game there would only be 10 players and we don't want to change the glow value of a non-existant player)
					int glowIndex = readMem<int>(entity + offset::m_iGlowIndex);
					int entityTeam = readMem<int>(entity + offset::m_iTeamNum);

					if (myTeam == entityTeam) { //don't make my team glow
						continue;
					}

					else if (myTeam != entityTeam && readMem<bool>(entity + offset::m_bSpottedByMask)) //one colour for visible enemies 
					{
						writeMem<float>(glowObject + ((glowIndex * 0x38) + 0x8), 2); //red
						writeMem<float>(glowObject + ((glowIndex * 0x38) + 0xC), 0);
						writeMem<float>(glowObject + ((glowIndex * 0x38) + 0x10), 2);
						writeMem<float>(glowObject + ((glowIndex * 0x38) + 0x14), 1.3);//alpha
					}

					else {

						writeMem<float>(glowObject + ((glowIndex * 0x38) + 0x8), 255); //red
						writeMem<float>(glowObject + ((glowIndex * 0x38) + 0xC), 255);
						writeMem<float>(glowObject + ((glowIndex * 0x38) + 0x10), 255);
						writeMem<float>(glowObject + ((glowIndex * 0x38) + 0x14), 1.3);//alpha

					}

					writeMem<bool>(glowObject + ((glowIndex * 0x38) + 0x28), true);

				}


			}

		}

	}

}
