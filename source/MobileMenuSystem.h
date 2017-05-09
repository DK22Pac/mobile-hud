#pragma once
// plugin-sdk
#include <plugin.h>
#include "game_sa\common.h"
#include "game_sa\CFont.h"
#include "game_sa\CMenuSystem.h"
#include "game_sa\CMessages.h"
#include "game_sa\CText.h"

// mobile-hud
#include "Utility.h"

class MobileMenuSystem {
public:
    static void InstallPatches();
    static void DisplayStandardMenu(unsigned char menuId, bool bBrightFont);
    static void DrawRect(CRect const& rect, bool bFading, CRGBA const& color);

private:
    static void DrawRect(float x, float y, float width, float height, bool bFading, CRGBA const &color) {
        DrawRect(CRect(x, y, x + width, y + height), bFading, (color));
    }
};