#pragma once
#include "plugin.h"
#include "CFont.h"
#include "Settings.h"

class MobileVehicleName {
public:
    static void InstallPatches();
    static void DrawVehicleName(float x, float y, char* str);
};
