#include "plugin.h"
#include "CFont.h"
#include "MobileAreaName.h"
#include "Settings.h"

using namespace plugin;

void MobileAreaName::InstallPatches() {
    patch::RedirectCall(0x58AE5D, DrawAreaName);
}

void MobileAreaName::DrawAreaName(float x, float y, char *str) {
    CFont::SetBackground(0, 0);
    CFont::SetOrientation(ALIGN_RIGHT);
    CFont::SetProportional(true);
    CFont::SetJustify(false);
    CFont::SetFontStyle(FONT_GOTHIC);
    CFont::SetEdge(3);
    CFont::SetScale(SCREEN_MULTIPLIER(settings.vecAreaNameScale.x), SCREEN_MULTIPLIER(settings.vecAreaNameScale.y));
    CFont::PrintString(SCREEN_COORD_RIGHT(settings.vecAreaNamePosn.x), SCREEN_COORD_BOTTOM(settings.vecAreaNamePosn.y), str);
}
