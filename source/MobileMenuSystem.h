#pragma once
#include "plugin.h"
#include "common.h"
#include "CFont.h"
#include "CMenuSystem.h"
#include "CMessages.h"
#include "CText.h"
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
