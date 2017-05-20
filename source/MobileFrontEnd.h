#pragma once
#define MenuPages (MobileMenuPage::PagesMenu)

#include "plugin.h"
#include "game_sa\CMenuManager.h"
#include "game_sa\Fx_c.h"
#include "game_sa\CAERadioTrackManager.h"
#include "game_sa\CControllerConfigManager.h"
#include "game_sa\CCamera.h"
#include "MobileMenuPage.h"
#include "MobileTextures.h"

class MobileFrontEnd {
public:
    int SlotValidation[8 + 1];

public:
    enum eMenuSliderTexture {
        MENU_SLIDER_NUB,
        MENU_SLIDER_FULL,
        MENU_SLIDER_EMPTY
    };

    static MobileTexDictionary m_menuSliderTxd;

    static void Setup();

    static void InstallPatches();
    static void __fastcall DrawStandardMenu(void *ecx0, int, char a2);
    static void __fastcall ProcessMobileMenuOptions(void *ecx0, int, signed char nArrowsInput, bool* bReturn, bool bEnterInput);
    static void PrintRadioStationList();
    static void DisplaySlider(float x, float y, float width, float height, float progress);
    static void DrawTexturedProgressBar(float x, float y, float width, float height, float progress, float deltaProgress);

    static void DrawStatsSlider(float x, float y, unsigned short width, unsigned char height, float percentage, signed char,
        unsigned char, unsigned char, CRGBA, CRGBA);
};

extern MobileFrontEnd FrontEndMobile;