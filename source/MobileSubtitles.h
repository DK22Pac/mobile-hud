#pragma once
// plugin-sdk
#include <plugin.h>
#include "game_sa\CFont.h"
#include "game_sa\CCamera.h"

// mobile-hud
#include "Settings.h"

class MobileSubtitles {
public:
    static void InstallPatches();
    static void DrawSubtitles(float x, float y, char* str);
};