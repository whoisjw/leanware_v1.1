#pragma once

#include "includes.h"

namespace offset { //offsets to be added to clientBase or engineBase to access game values
	
	const DWORD dwLocalPlayer = 0xDEA964;
	const DWORD m_fFlags = 0x104;
	const DWORD dwForceJump = 0x52BBC9C;
	const DWORD dwEntityList = 0x4DFFF14;
	const DWORD m_iTeamNum = 0xF4;
	const DWORD m_bSpotted = 0x93D;
	const DWORD m_iGlowIndex = 0x10488;
	const DWORD dwGlowObjectManager = 0x535A9D8;
	const DWORD m_flFlashDuration = 0x10470;
	const DWORD CrosshairID = 0x11838;
	const DWORD attack = 0x322DD10;
	const DWORD fovof = 0x31F4;
	const DWORD sendpackets = 0xDD072;
	const DWORD Oberserver = 0x3388;
	const DWORD thirdpersonviewangle = 0x31E8;
	const DWORD viewangle = 0x4D90;
	const DWORD aimpunchangle = 0x303C;
	const DWORD scoped = 0x9974;
	const DWORD render = 0x70;
	const DWORD dwClientState_ViewAngles = 0x4D90;
	const DWORD dwClientState_State = 0x108;
	const DWORD dwClientState = 0x59F194;
	const DWORD m_dwBoneMatrix = 0x26A8;
	const DWORD m_iHealth = 0x100;
	const DWORD m_vecOrigin = 0x138;
	const DWORD m_vecVelocity = 0x114;
	const DWORD m_vecViewOffset = 0x108;
	const DWORD m_bSpottedByMask = 0x980;
	const DWORD m_bDormant = 0xED;
	const DWORD dwClientState_GetLocalPlayer = 0x180;
	const DWORD m_lifeState = 0x25F;
	const DWORD dwForceAttack = 0x322DD10;
	const DWORD model_ambient_min = 0x5A118C;
	const DWORD m_iObserverMode = 0x3388;
	const DWORD dwViewMatrix = 0x4DF0D44;
	const DWORD m_hViewModel = 0x3308;

	//skinchanger offsets
	const DWORD m_hMyWeapons = 0x2E08;
	const DWORD m_nFallbackPaintKit = 0x31D8;
	const DWORD m_nFallbackSeed = 0x31DC;
	const DWORD m_nFallbackStatTrak = 0x31E4;
	const DWORD m_flFallbackWear = 0x31E0;
	const DWORD m_iItemDefinitionIndex = 0x2FBA;
	const DWORD m_iItemIDHigh = 0x2FD0;
	const DWORD m_iEntityQuality = 0x2FBC;
	const DWORD m_iAccountID = 0x2FD8;
	const DWORD m_OriginalOwnerXuidLow = 0x31D0;

	const DWORD m_hActiveWeapon = 0x2F08;

}

namespace toggle { //flags to toggle cheats on and off 

	inline bool Bhop = false;
	inline bool Glow = false;
	inline bool Aim = false;
	inline bool Radar = false;
	inline bool NoFlash = false;
	inline bool Trigger = false;
	inline bool Jump = false;
	inline bool SoundEsp = false;

}

namespace vals { //activation delay for the triggerbot

	inline int triggerDelay = 0;

}

inline HANDLE process; //csgo process
inline DWORD clientBase; //base address of client.dll
inline DWORD engineBase; //base address of engine.dll

/*
* Templates for ReadProcessMemory and WriteProcessMemory
* These are used pretty much everywhere in the cheat and 
* only the address value needs to change so it makes it 
* easier to shorten these functions.
*/
template <typename T>
T readMem(DWORD address) {

	T buffer;
	ReadProcessMemory(process, (LPVOID)address, &buffer, sizeof(buffer), 0);
	return buffer;

}

template <typename T>
void writeMem(DWORD address, T value) {

	WriteProcessMemory(process, (LPVOID)address, &value, sizeof(value), 0);

}