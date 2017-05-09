// mobile-hud
#include "MobileVehicleName.h"

void MobileVehicleName::InstallPatches() {
    plugin::patch::RedirectCall(0x58B156, DrawVehicleName);
}

void MobileVehicleName::DrawVehicleName(float x, float y, char *str) {
    CFont::SetBackground(0, 0);
    CFont::SetAlignment(ALIGN_RIGHT);
    CFont::SetProp(true);
    CFont::SetJustify(false);
    CFont::SetFontStyle(FONT_MENU);
    CFont::SetScale(SCREEN_MULTIPLIER(settings.vecVehicleNameScale.x), SCREEN_MULTIPLIER(settings.vecVehicleNameScale.y));

    CFont::PrintString(SCREEN_COORD_RIGHT(settings.vecVehicleNamePosn.x), SCREEN_COORD_BOTTOM(settings.vecVehicleNamePosn.y), str);

}