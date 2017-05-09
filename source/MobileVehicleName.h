#pragma once
// plugin-sdk
#include <plugin.h>
#include "game_sa\CFont.h"

// mobile-hud
#include "Settings.h"

class MobileVehicleName {
public:
    static void InstallPatches();
    static void DrawVehicleName(float x, float y, char* str);
};