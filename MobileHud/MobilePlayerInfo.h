#pragma once
#include "game_sa\RenderWare.h"
#include "game_sa\CSprite2d.h"
#include "game_sa\CPed.h"

class MobilePlayerInfo {
public:
	static unsigned int m_CurrentStar;

	static void InstallPatches();

	static void MyDrawWeaponIcon(CPed *player, int, int, float alpha);
    static void MyDrawWeaponAmmo(CPed *player, int, int, float alpha);

	static void MySetClockScale(float scaleX, float scaleY);
	static void MyDrawClock(float x, float y, char *text);

	static void MySetMoneyScale(float scaleX, float scaleY);
	static void MyDrawMoney(float x, float y, char *text);

	static void MyDrawHealth(int playerId, int, int);
	static void MyDrawArmor(int playerId, int, int);
	static void MyDrawBreath(int playerId, int, int);

	static void MyStoreCurrentStar(short);
	static void MyDrawWantedLevel(float x, float y, char *text);
};