#pragma once
// plugin-sdk
#include <plugin.h>
#include "game_sa\CFont.h"

// mobile-hud
#include "Settings.h"

class MobileAreaName {
public:
	static void InstallPatches();
	static void DrawAreaName(float x, float y, char* str);
};