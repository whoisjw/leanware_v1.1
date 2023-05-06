#include "aim.h"
#include "vector.h"

constexpr Vector3 calculateAngle(
	const Vector3& localPosition,
	const Vector3& enemyPosition,
	const Vector3& viewAngles) noexcept {

	return ((enemyPosition - localPosition).ToAngle() - viewAngles);

}

using namespace offset;

void aim() noexcept {

	while (true) {

		Sleep(1);

		if (toggle::Aim) {

			// get local player
			const auto localPlayer = readMem<DWORD>(clientBase + dwLocalPlayer);
			const auto localTeam = readMem< int32_t>(localPlayer + m_iTeamNum);

			// eye position = origin + viewOffset
			const auto localEyePosition = readMem<Vector3>(localPlayer + m_vecOrigin) +
				readMem<Vector3>(localPlayer + m_vecViewOffset);

			//get client state
			const auto clientState = readMem<DWORD>(engineBase + dwClientState);

			//get local player id
			const auto localPlayerId = readMem<int>(clientState + dwClientState_GetLocalPlayer);

			//get local view angle
			const auto viewAngles = readMem<Vector3>(clientState + dwClientState_ViewAngles);
			const auto aimPunch = readMem<Vector3>(localPlayer + aimpunchangle) * 2;

			auto bestFov = 5.f;
			auto bestAngle = Vector3{};

			for (int i = 1; i <= 64; i++) {

				DWORD player = readMem<DWORD>(clientBase + dwEntityList + i * 0x10);
				//checks

				if (readMem<int>(player + m_iTeamNum) == localTeam) {
					continue;
				}

				if (readMem<bool>(player + m_bDormant)) {
					continue;
				}

				if (!readMem<int>(player + m_iHealth)) {
					continue;
				}

				if (!readMem<bool>(player + m_bSpottedByMask)) {
					continue;
				}

				DWORD boneMatrix = readMem<DWORD>(player + m_dwBoneMatrix);

				Vector3 playerHeadPos = Vector3{
					readMem<float>(boneMatrix + 0x30 * 8 + 0x0C),
					readMem<float>(boneMatrix + 0x30 * 8 + 0x1C),
					readMem<float>(boneMatrix + 0x30 * 8 + 0x2C)
				};

				Vector3 angle = calculateAngle(
					localEyePosition,
					playerHeadPos,
					viewAngles + aimPunch
				);

				const auto fov2 = std::hypot(angle.x, angle.y);

				if (fov2 < bestFov) {
					bestFov = fov2;
					bestAngle = angle;
				}

			}
			if (!bestAngle.IsZero()) {
				writeMem<Vector3>(clientState + dwClientState_ViewAngles, viewAngles + bestAngle / 3.f);
			}

		}

	}

}