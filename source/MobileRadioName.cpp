#include "MobileRadioName.h"
#include "plugin.h"
#include "Settings.h"

using namespace plugin;

void MobileRadioName::InstallPatches() {
    patch::RedirectCall(0x4E9F3F, MySetRadioNameScale);
    patch::RedirectCall(0x4E9F4D, MySetRadioNameAlignment);
    patch::RedirectCall(0x4E9FF1, MyDrawRadioName);
}

void MobileRadioName::MySetRadioNameScale(float x, float y) {
    CFont::SetScale(SCREEN_MULTIPLIER(settings.vecRadioNameScale.x), SCREEN_MULTIPLIER(settings.vecRadioNameScale.y));
}

void MobileRadioName::MyDrawRadioName(float x, float y, char *name) {
    if (settings.bRadioNameTop)
        CFont::PrintString(SCREEN_COORD_CENTER_X, SCREEN_COORD_TOP(settings.fRadioNameTopPosnY), name);
    else
        CFont::PrintString(SCREEN_COORD(settings.vecRadioNamePosn.x), SCREEN_COORD_BOTTOM(settings.vecRadioNamePosn.y), name);
}

void MobileRadioName::MySetRadioNameAlignment(eFontAlignment alignment) {
    if (settings.bRadioNameTop) {
        CFont::SetOrientation(ALIGN_CENTER);
        CFont::SetCentreSize(SCREEN_WIDTH);
    }
    else {
        CFont::SetOrientation(ALIGN_LEFT);
        CFont::SetWrapx(SCREEN_COORD_MAX_X);
    }
}
