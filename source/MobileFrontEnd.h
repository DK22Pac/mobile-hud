#pragma once

#include "plugin.h"
#include "CMenuManager.h"
#include "Fx_c.h"
#include "CAERadioTrackManager.h"
#include "CControllerConfigManager.h"
#include "CCamera.h"
#include "MobileMenuPage.h"
#include "MobileTextures.h"

#define MenuPages (MobileMenuPage::PagesMenu)

class MobileFrontEnd {
public:
    bool      IsTimeForBackground;
    CVector2D BGCoords;
    int       BGAlpha;
    int       CharAlpha;
    bool      BGFrameZero;
    bool      BGFrameFirst;
    bool      BGFrameSecond;
    bool      BGCoordsEnded;
    int       SlotValidation[8 + 1];


public:
    static void InstallPatches();
    static void __fastcall DrawBackground(void *ecx0);
    static void GetRandomBGCoords(int coordsId);
    static float __fastcall CheckMouseInput(float a1);
    static void DrawStandardMenu();
    static void __fastcall ProcessMobileMenuOptions(void *ecx0, int, signed char nArrowsInput, bool* bReturn, bool bEnterInput);
    static void PrintRadioStationList();
    static void PrintMap();
    static void PrintLegend();
    static void PrintPlaceName();
    static void DisplaySlider(float x, float y, float width, float height, float progress, bool bNub);

    static void PrintStats();
    static void PrintStatsText(float x, float y, char *str);
    static void PrintStatsText2(float x, float y, char * str);
    static void DrawStatsSlider(float x, float y, unsigned short width, unsigned char height, float percentage, signed char,
        unsigned char, unsigned char, CRGBA, CRGBA);
    static void PrintBriefsText(float x, float y, char *str);
};

extern MobileFrontEnd FrontEndMobileMenuManager;
