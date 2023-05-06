#include "misc.h"
#include "vector.h"

constexpr Vector3 calculateAngle(
	const Vector3& localPosition,
	const Vector3& enemyPosition,
	const Vector3& viewAngles) noexcept {

	return ((enemyPosition - localPosition).ToAngle() - viewAngles);

}

void bhop() {

	while (true) {

		if (toggle::Bhop) {

			DWORD cheater = readMem<DWORD>((DWORD)clientBase + offset::dwLocalPlayer); //finds local player in memory 
			DWORD onGround = readMem<DWORD>((DWORD)cheater + offset::m_fFlags); //finds player flag so we can work out if on ground or in air 

			if (GetAsyncKeyState(VK_SPACE)) {

				if (onGround == 256) { //if off ground 
					writeMem<int>(clientBase + offset::dwForceJump, 4); //don't force jump
				}
				else { //if on ground 
					writeMem<int>(clientBase + offset::dwForceJump, 5); //do force jump 
				}
			}

		}
	}

}

void radar() {

	while (true) {

		Sleep(1);

		if (toggle::Radar) {

			DWORD cheater = readMem<DWORD>(clientBase + offset::dwLocalPlayer);
			DWORD myTeam = readMem<DWORD>(clientBase + offset::m_iTeamNum);

			for (int i = 1; i <= 64; i++) {

				DWORD entity = readMem<DWORD>(clientBase + offset::dwEntityList + i * 0x10);

				if (readMem<DWORD>(entity + offset::m_iTeamNum) == myTeam) {
					continue;
				}

				writeMem<bool>(entity + offset::m_bSpotted, true);

			}

		}

	}

}

void jumpScout() {

	while (true) {

		DWORD cheater = readMem<DWORD>(clientBase + offset::dwLocalPlayer);
	
		if (readMem<int>(cheater + offset::m_fFlags) == 256 && GetAsyncKeyState(0x43)) {

			Sleep(320);
			writeMem<int>(clientBase + offset::dwForceAttack, 6);
			Sleep(30);
			writeMem<int>(clientBase + offset::dwForceAttack, 4);

		}

	}

	

}

void soundEsp() {

	while (true) {

		if (toggle::SoundEsp) {

			// get local player
			const auto localPlayer = readMem<DWORD>(clientBase + offset::dwLocalPlayer);
			const auto localTeam = readMem<int32_t>(localPlayer + offset::m_iTeamNum);

			// eye position = origin + viewOffset
			const auto localEyePosition = readMem<Vector3>(localPlayer + offset::m_vecOrigin) +
				readMem<Vector3>(localPlayer + offset::m_vecViewOffset);

			//get client state
			DWORD clientState = readMem<DWORD>(engineBase + offset::dwClientState);

			//get local player id
			const auto localPlayerId = readMem<int>(clientState + offset::dwClientState_GetLocalPlayer);

			//get local view angle
			Vector3 viewAngles = readMem<Vector3>(clientState + offset::dwClientState_ViewAngles);
			Vector3 aimPunch = readMem<Vector3>(localPlayer + offset::aimpunchangle) * 2;

			float bestFov = 4.f;
			Vector3 bestAngle = Vector3{ };

			for (int i = 1; i <= 64; i++) {

				DWORD player = readMem<DWORD>(clientBase + offset::dwEntityList + i * 0x10);
				//checks

				if (readMem<int>(player + offset::m_iTeamNum) == localTeam) {
					continue;
				}

				if (readMem<int32_t>(player + offset::m_lifeState)) {
					continue;
				}

				if (readMem<bool>(player + offset::m_bDormant)) {
					continue;
				}

				if (!readMem<std::int32_t>(player + offset::m_bSpottedByMask) && (1 << localPlayerId)) {

					const auto boneMatrix = readMem<DWORD>(player + offset::m_dwBoneMatrix);

					const auto playerHeadPosition = Vector3{
						readMem<float>(boneMatrix + 0x30 * 6 + 0x0C),
						readMem<float>(boneMatrix + 0x30 * 6 + 0x1C),
						readMem<float>(boneMatrix + 0x30 * 6 + 0x2C)
					};

					const auto angle = calculateAngle(
						localEyePosition,
						playerHeadPosition,
						viewAngles + aimPunch
					);

					const auto fov = std::hypot(angle.x, angle.y);

					if (fov < bestFov){

						Beep(556, 500);

					}
				}

			}

		}

		
	}
	
	

}
