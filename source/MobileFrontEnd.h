#pragma once
#include "plugin.h"
#include "game_sa\CMenuManager.h"
#include "MobileTextures.h"

class MobileFrontEnd {
public:
    enum eMenuSliderTexture {
        MENU_SLIDER_NUB,
        MENU_SLIDER_FULL,
        MENU_SLIDER_EMPTY
    };

    static MobileTexDictionary m_menuSliderTxd;

    static void InstallPatches();
    static void Setup();
    static void DrawStatsSlider(float x, float y, unsigned short width, unsigned char height, float percentage, signed char,
        unsigned char, unsigned char, CRGBA, CRGBA);
};