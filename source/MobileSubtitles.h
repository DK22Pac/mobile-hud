#pragma once
#include "plugin.h"
#include "CFont.h"
#include "CCamera.h"
#include "Settings.h"

class MobileSubtitles {
public:
    static void InstallPatches();
    static void DrawSubtitles(float x, float y, char* str);
};
