#include "plugin.h"
#include "MobileFrontEnd.h"
#include "CPad.h"
#include "CRadar.h"
#include "CHudColours.h"
#include "CVector2D.h"
#include "CStats.h"
#include "Settings.h"
#include <time.h>

using namespace plugin;

MobileFrontEnd FrontEndMobileMenuManager;

void MobileFrontEnd::InstallPatches() {
    patch::RedirectJump(0x57B750, DrawBackground);
    patch::RedirectCall(0x57FEAB, CheckMouseInput);
    patch::RedirectCall(0x57B66F, ProcessMobileMenuOptions);
    patch::RedirectCall(0x57B702, ProcessMobileMenuOptions);
    patch::RedirectCall(0x5764E7, PrintBriefsText);
    patch::RedirectCall(0x574DC1, PrintStatsText);
    patch::RedirectCall(0x574E4D, PrintStatsText2);
    patch::RedirectCall(0x574F54, DrawStatsSlider);

    // PrintMap Patches
    // Legend
    patch::Set<BYTE>(0x5760A1, 0x83);
    patch::Set<BYTE>(0x5760A2, 0xC4);
    patch::Set<BYTE>(0x5760A3, 0x18);
    patch::Nop(0x5760A4, 0x90);
    patch::Nop(0x5760A5, 0x90);
    patch::Nop(0x5761D3, 0x90);
    patch::Nop(0x5761D4, 0x90);
    patch::Nop(0x5761D5, 0x90);
    patch::Nop(0x5761D6, 0x90);
    patch::Nop(0x5761D7, 0x90);
    patch::Nop(0x5761D8, 0x90);
    // Borders
    patch::Set(0x575E12, 5);
    patch::Set(0x575DC2, 5);
    patch::Set(0x575D6F, 5);
    patch::Set(0x575D1F, 5);
    patch::Set(0x575CCE, 5);
    patch::Set(0x575C84, 5);
    patch::Set(0x575C40, 5);
    patch::Set(0x575BF6, 5);
    // Place name 
    patch::Set(0x575F89, 5);
    // Help texts
    patch::SetChar(0x5762E7 + 1, 0);
    patch::SetChar(0x5762FD + 1, 0);
    // Legend text
    patch::Set(0x582DEE, 5);
    // PrintStats Patches
    patch::Set(0x5750BA, 5);
    patch::Set(0x57511B, 5);
    patch::Set(0x574957, 5);
}

void MobileFrontEnd::DrawBackground(void *ecx0) {
    CSprite2d::DrawRect(CRect(0.0f, 0.0f, 0.0f + SCREEN_WIDTH, 0.0f + SCREEN_HEIGHT), CRGBA(0, 0, 0, 255));

    if (FrontEndMenuManager.m_nCurrentMenuPage != 5) {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));

        // Background
        mobileTex.m_nBackgroundSprite.m_pTexture = mobileTex.m_nBackgroundSpriteTxd.GetTexture(MENU_BGMAP);
        mobileTex.m_nBackgroundSprite.Draw(CRect(SCREEN_COORD(-FrontEndMobileMenuManager.BGCoords.x), SCREEN_COORD(-FrontEndMobileMenuManager.BGCoords.y), SCREEN_COORD(-FrontEndMobileMenuManager.BGCoords.x) + SCREEN_WIDTH + SCREEN_COORD(900.0f), SCREEN_COORD(-FrontEndMobileMenuManager.BGCoords.y) + SCREEN_HEIGHT + SCREEN_COORD(1024.0f)), CRGBA(255, 255, 255, FrontEndMobileMenuManager.BGAlpha));

        // Mask
        mobileTex.m_nBackgroundSprite.m_pTexture = mobileTex.m_nBackgroundSpriteTxd.GetTexture(MENU_MAINMASK);
        mobileTex.m_nBackgroundSprite.Draw(CRect(0.0, 0.0f, 0.0f + SCREEN_WIDTH, 0.0f + SCREEN_HEIGHT), CRGBA(255, 255, 255, 250));
        mobileTex.m_nBackgroundSprite.m_pTexture = nullptr;

        int coordsId;

        if (FrontEndMobileMenuManager.BGFrameFirst)
            coordsId = 1;
        else if (FrontEndMobileMenuManager.BGFrameSecond)
            coordsId = 2;
        else
            coordsId = 0;

        MobileFrontEnd::GetRandomBGCoords(coordsId);
    }

    // Char     
    int charId;

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_MAIN_MENU)
        charId = MENU_CHAR_0;
    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_OPTIONS)
        charId = MENU_CHAR_1;
    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_SELECT_GAME)
        charId = MENU_CHAR_5;
    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_QUIT)
        charId = MENU_CHAR_6;
    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_LANGUAGE_SETTINGS)
        charId = MENU_CHAR_7;
    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_BRIEFS)
        charId = MENU_CHAR_8;
    else
        charId = MENU_CHAR_2;

    if (FrontEndMobileMenuManager.CharAlpha != 255)
        FrontEndMobileMenuManager.CharAlpha += 5;

    mobileTex.m_nBackgroundSprite.m_pTexture = mobileTex.m_nBackgroundSpriteTxd.GetTexture(charId);
    if (FrontEndMenuManager.m_nCurrentMenuPage != 0)
        mobileTex.m_nBackgroundSprite.Draw(CRect(SCREEN_COORD_CENTER_X - SCREEN_COORD(1113.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(843.7f / 2),
            SCREEN_COORD_CENTER_X - SCREEN_COORD(1113.0f / 2) + SCREEN_MULTIPLIER(375.0f), SCREEN_COORD_CENTER_Y - SCREEN_COORD(843.7f / 2) + SCREEN_MULTIPLIER(837.0f)), CRGBA(255, 255, 255, FrontEndMobileMenuManager.CharAlpha));

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_MAP) {
        MobileFrontEnd::PrintMap();
        MobileFrontEnd::PrintLegend();
        MobileFrontEnd::PrintPlaceName();
    }

    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_REDEFINE_CONTROLS) {
        FrontEndMenuManager.DrawControllerSetupScreen();
    }

    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_EMPTY) {
        FrontEndMenuManager.SaveSettings();
        exit(0);
    }

    else {
        MobileFrontEnd::DrawStandardMenu();
    }

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_STATS) {
        MobileFrontEnd::PrintStats();
    }

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_BRIEFS) {
        FrontEndMenuManager.PrintBriefs();
    }

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_SOUND_SETTINGS) {
        MobileFrontEnd::PrintRadioStationList();
    }

    if (FrontEndMenuManager.m_bScanningUserTracks) {
        // TODO: ScanningUserTracks
        CFont::SetBackground(0, 0);
        CFont::SetProportional(1);
        CFont::SetWrapx(SCREEN_COORD_MAX_X - 12.5f);
        CFont::SetFontStyle(FONT_SUBTITLES);
        CFont::SetOrientation(ALIGN_RIGHT);
        CFont::SetEdge(2);
        CFont::SetDropColor(CRGBA(0, 0, 0, 255));
        CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
        CFont::SetScale(SCREEN_MULTIPLIER(0.6f), SCREEN_MULTIPLIER(1.2f));
        CFont::PrintStringFromBottom(SCREEN_COORD_RIGHT(10.0f), SCREEN_COORD_BOTTOM(-35.0f), TheText.Get("FEA_SMP"));

        FrontEndMenuManager.m_bScanningUserTracks = 0;
    }

    if (FrontEndMenuManager.m_bShowMouse) {
        // TODO: Get cursor icon from system.
        POINT position;
        if (GetCursorPos(&position)) {
            if (FrontEndMenuManager.m_nCurrentMenuPage == 5 && CPad::NewMouseControllerState.lmb)
                FrontEndMenuManager.m_aMenuSprites[24].Draw(position.x, position.y, SCREEN_MULTIPLIER(22.5f), SCREEN_MULTIPLIER(22.5f), CRGBA(255, 255, 255, 255));
            else
                FrontEndMenuManager.m_aMenuSprites[23].Draw(position.x, position.y, SCREEN_MULTIPLIER(22.5f), SCREEN_MULTIPLIER(22.5f), CRGBA(255, 255, 255, 255));

        }
    }
}

void MobileFrontEnd::GetRandomBGCoords(int coordsId) {
    switch (coordsId) {
    case 0:
        if (!FrontEndMenuManager.m_bMenuActive) {
            FrontEndMobileMenuManager.BGCoords.x = 0.0f;
            FrontEndMobileMenuManager.BGCoords.y = 0.0f;
            FrontEndMobileMenuManager.BGAlpha = 0;
        }
        else {
            if (FrontEndMobileMenuManager.BGCoords.y >= SCREEN_COORD(750.0f)) {
                // End Animation
                if (FrontEndMobileMenuManager.BGAlpha != 0.0f)
                    FrontEndMobileMenuManager.BGAlpha -= 1;

                else if (FrontEndMobileMenuManager.BGAlpha == 0.0f) {
                    if (FrontEndMobileMenuManager.BGAlpha != 40.0f)
                        FrontEndMobileMenuManager.BGAlpha += 1;

                    FrontEndMobileMenuManager.BGCoords.x = 640.0f;
                    FrontEndMobileMenuManager.BGCoords.y = 1024.0f;

                    FrontEndMobileMenuManager.BGFrameFirst = 1;
                }
            }
            else {
                // Start Animation
                if (FrontEndMobileMenuManager.BGAlpha != 40.0f)
                    FrontEndMobileMenuManager.BGAlpha += 1;
                if (FrontEndMobileMenuManager.BGCoords.y != SCREEN_COORD(1024.0f))
                    FrontEndMobileMenuManager.BGCoords.y += 1.0f * 0.3f;
            }
        }
        break;
    case 1:
        if (!FrontEndMenuManager.m_bMenuActive) {
            FrontEndMobileMenuManager.BGCoords.x = 0.0f;
            FrontEndMobileMenuManager.BGCoords.y = 0.0f;
            FrontEndMobileMenuManager.BGAlpha = 0;
        }
        else {
            if (FrontEndMobileMenuManager.BGCoords.y <= SCREEN_COORD(330.0f)) {
                // End Animation
                if (FrontEndMobileMenuManager.BGAlpha != 0.0f)
                    FrontEndMobileMenuManager.BGAlpha -= 1;

                else if (FrontEndMobileMenuManager.BGAlpha == 0.0f) {
                    if (FrontEndMobileMenuManager.BGAlpha != 40.0f)
                        FrontEndMobileMenuManager.BGAlpha += 1;

                    FrontEndMobileMenuManager.BGCoords.x = 800.0f;
                    FrontEndMobileMenuManager.BGCoords.y = 0.0f;

                    FrontEndMobileMenuManager.BGFrameFirst = 0;
                    FrontEndMobileMenuManager.BGFrameSecond = 1;
                }
            }
            else {
                // Start Animation
                if (FrontEndMobileMenuManager.BGAlpha != 40.0f)
                    FrontEndMobileMenuManager.BGAlpha += 1;
                if (FrontEndMobileMenuManager.BGCoords.y != SCREEN_COORD(0.0f))
                    FrontEndMobileMenuManager.BGCoords.y -= 1.0f * 0.3f;
            }
        }
        break;
    case 2:
        if (!FrontEndMenuManager.m_bMenuActive) {
            FrontEndMobileMenuManager.BGCoords.x = 0.0f;
            FrontEndMobileMenuManager.BGCoords.y = 0.0f;
            FrontEndMobileMenuManager.BGAlpha = 0;
        }
        else {
            if (FrontEndMobileMenuManager.BGCoords.x < SCREEN_COORD(40.0f) || FrontEndMobileMenuManager.BGCoords.y >= SCREEN_COORD(800.0f)) {
                // End Animation
                if (FrontEndMobileMenuManager.BGAlpha != 0.0f)
                    FrontEndMobileMenuManager.BGAlpha -= 1;

                else if (FrontEndMobileMenuManager.BGAlpha == 0.0f) {
                    if (FrontEndMobileMenuManager.BGAlpha != 40.0f)
                        FrontEndMobileMenuManager.BGAlpha += 1;

                    FrontEndMobileMenuManager.BGCoords.x = 0.0f;
                    FrontEndMobileMenuManager.BGCoords.y = 0.0f;

                    FrontEndMobileMenuManager.BGFrameZero = 1;
                    FrontEndMobileMenuManager.BGFrameFirst = 0;
                    FrontEndMobileMenuManager.BGFrameSecond = 0;
                }
            }
            else {
                // Start Animation
                if (FrontEndMobileMenuManager.BGAlpha != 40.0f)
                    FrontEndMobileMenuManager.BGAlpha += 1;
                if (FrontEndMobileMenuManager.BGCoords.x != SCREEN_COORD(900.0f))
                    FrontEndMobileMenuManager.BGCoords.x -= 1.0f * 0.3f;
                if (FrontEndMobileMenuManager.BGCoords.y != SCREEN_COORD(1024.0f))
                    FrontEndMobileMenuManager.BGCoords.y += 1.0f * 0.4f;
            }
        }
        break;
    };
}

float __fastcall MobileFrontEnd::CheckMouseInput(float a1) {
    return SCREEN_COORD_CENTER_Y - SCREEN_COORD(-a1 - 32.5f);
}

void MobileFrontEnd::DrawStandardMenu() {
    CFont::SetBackground(0, 0);
    CFont::SetProportional(1);
    CFont::SetWrapx(SCREEN_COORD_MAX_X - 12.5f);
    CFont::SetEdge(2);
    CFont::SetRightJustifyWrap(12.5f);
    CFont::SetCentreSize(SCREEN_COORD_MAX_X);
    CFont::SetDropColor(CRGBA(0, 0, 0, 255));

    // Header
    if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_szTitleName[0]) {
        if (FrontEndMenuManager.m_nCurrentMenuPage != 5 || !FrontEndMenuManager.m_bStandardInput) {
            CFont::SetOrientation(ALIGN_LEFT);
            CFont::SetFontStyle(FONT_GOTHIC);
            CFont::SetScale(SCREEN_MULTIPLIER(1.8f), SCREEN_MULTIPLIER(3.6f));
            CFont::SetEdge(2);
            CFont::SetColor(CRGBA(255, 255, 255, 255));
            CFont::SetDropColor(CRGBA(0, 0, 0, 255));
            if (FrontEndMenuManager.m_nCurrentMenuPage != 0)
                CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(282.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(794.0f / 2), TheText.Get(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_szTitleName));
            else
                CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(1113.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(794.0f / 2), TheText.Get(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_szTitleName));
        }
    }

    // Actions
    if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_nActionType == 1)
    {
        static char* pText;
        CFont::SetFontStyle(FONT_SUBTITLES);
        CFont::SetOrientation(ALIGN_LEFT);
        CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7f));
        CFont::SetEdge(2);
        CFont::SetColor(CRGBA(255, 255, 255, 255));
        CFont::SetDropColor(CRGBA(0, 0, 0, 255));

        switch (FrontEndMenuManager.m_nCurrentMenuPage)
        {
        case 6:
        {
            pText = TheText.Get(FrontEndMenuManager.m_bGameNotLoaded ? "FESZ_QQ" : MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_szName);
            break;
        }
        case 35:
        {
            pText = TheText.Get(FrontEndMenuManager.m_bGameNotLoaded ? "FEQ_SRW" : MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_szName);
            break;
        }
        case 17:
        {
            switch (FrontEndMobileMenuManager.SlotValidation[FrontEndMenuManager.m_nSelectedSaveGame + 1]) {
            case 0:
                    pText = TheText.Get("FESZ_QO");
                    break;
            case 2:
                    pText = TheText.Get("FESZ_QC");
                    break;
            default:
                pText = TheText.Get(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_szName);
                break;
            }
            break;
        }
        case 11:
        {
            pText = TheText.Get(FrontEndMenuManager.m_bGameNotLoaded ? "FES_LCG" : MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_szName);
            break;
        }
        default:
        {
            pText = TheText.Get(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_szName);
            break;
        }
        }
        CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(282.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(640.0f / 2), pText);
    }

    for (unsigned int i = 0; i < 12; i++) {
        CFont::SetFontStyle(FONT_MENU);
        CFont::SetEdge(2);

        if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nActionType != 1 && MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_szName[0]) {
            const char* LeftColumn = nullptr;
            const char* RightColumn = nullptr;
            char ReservedSpace[64];

            if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nType >= MENUENTRY_SAVE_1 && MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nType <= MENUENTRY_SAVE_8) { 
                switch (FrontEndMobileMenuManager.SlotValidation[i]) {
                case 0:
                    LeftColumn = CallAndReturn<const char*, 0x5D0F40>(i - 1);
                    break;
                case 2:
                    LeftColumn = TheText.Get("FESZ_CS");
                    break;
                }

                if (!LeftColumn || !LeftColumn[0]) {
                    sprintf(gString, "FEM_SL%X", i);
                    LeftColumn = TheText.Get(gString);

                }
            }

            else if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nType == MENUENTRY_MISSIONPACK) {
            }

            else if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nType == MENUENTRY_JOYMOUSE) {
                LeftColumn = TheText.Get(FrontEndMenuManager.m_nController ? "FEJ_TIT" : "FEC_MOU");
            }

            else {
                LeftColumn = TheText.Get(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_szName);
            }

            CAERadioTrackManager RadioEntity;

            switch (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nActionType) {
            case 30:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsRadioEq? "FEM_ON" : "FEM_OFF");
                break;
            case 31:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsRadioAutoSelect ? "FEM_ON" : "FEM_OFF");
                break;
            case 32:
                RightColumn = RadioEntity.GetRadioStationName(FrontEndMenuManager.m_nPrefsRadioStation);
                break;
            case 33:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsShowLegends ? "FEM_ON" : "FEM_OFF");
                break;
            case 25:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsShowSubtitles ? "FEM_ON" : "FEM_OFF");
                break;
            case 26:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsUseWideScreen? "FEM_ON" : "FEM_OFF");
                break;
            case 34:
                switch (FrontEndMenuManager.m_nPrefsRadarMode) {
                case 0:
                    RightColumn = TheText.Get("FED_RDM");
                    break;
                case 1:
                    RightColumn = TheText.Get("FED_RDB");
                    break;
                case 2:
                    RightColumn = TheText.Get("FEM_OFF");
                    break;
                }
                break;
            case 35:
                switch (FrontEndMenuManager.m_bPrefsShowHud) {
                case 0:
                    RightColumn = TheText.Get("FEM_OFF");
                    FrontEndMenuManager.m_nPrefsRadarMode = 2;
                    break;
                case 1:
                    RightColumn = TheText.Get("FEM_ON");
                    FrontEndMenuManager.m_nPrefsRadarMode = 0;
                    break;
                }
                break;
            case 65:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsSavePhotos ? "FEM_ON" : "FEM_OFF");
                break;
            case 63:
                switch (FrontEndMenuManager.m_nPrefsRadarMode) {
                case 0:
                    RightColumn = TheText.Get("FEA_PR1");
                    break;
                case 1:
                    RightColumn = TheText.Get("FEA_PR2");
                    break;
                case 2:
                    RightColumn = TheText.Get("FEA_PR3");
                    break;
                }
                break;
            case 24:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsVsync ? "FEM_ON" : "FEM_OFF");
                break;
            case 43:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsMipMapping ? "FEM_ON" : "FEM_OFF");
                break;
            case 64:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsTracksAutoScan ? "FEM_ON" : "FEM_OFF");
                break;
            case 46:
                RightColumn = TheText.Get(!FrontEndMenuManager.bInvertMouseY ? "FEM_ON" : "FEM_OFF");
                break;
            case 47:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsInvertPadX1 ? "FEM_ON" : "FEM_OFF");
                break;
            case 48:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsInvertPadY1 ? "FEM_ON" : "FEM_OFF");
                break;
            case 49:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsInvertPadX2 ? "FEM_ON" : "FEM_OFF");
                break;
            case 50:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsInvertPadY2 ? "FEM_ON" : "FEM_OFF");
                break;
            case 51:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsSwapPadAxis1 ? "FEM_ON" : "FEM_OFF");
                break;
            case 52:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bPrefsSwapPadAxis2 ? "FEM_ON" : "FEM_OFF");
                break;
            case 59:
                RightColumn = TheText.Get(CVehicle::m_bEnableMouseSteering ? "FEM_ON" : "FEM_OFF");
                break;
            case 60:
                RightColumn = TheText.Get(CVehicle::m_bEnableMouseFlying ? "FEM_ON" : "FEM_OFF");
                break;
            case 56:
            {
                const char* pszResolution = ((const char**(*)())0x745AF0)()[FrontEndMenuManager.m_nPrefsVideoMode];

                if (!pszResolution)
                    pszResolution = "";

                strncpy(ReservedSpace, pszResolution, sizeof(ReservedSpace));
                RightColumn = ReservedSpace;
            }
            break;
            case 44:
                if (FrontEndMenuManager.m_nAntiAliasingLevel <= 1)
                    RightColumn = TheText.Get("FEM_OFF");
                else {
                    switch (FrontEndMenuManager.m_nAntiAliasingLevel)
                    {
                    case 2:
                        RightColumn = "2x";
                        break;
                    case 3:
                        RightColumn = "4x";
                        break;
                    case 4:
                        RightColumn = "8x";
                        break;
                    }
                }
                break;
            case 42:
                switch (g_fx.GetFxQuality()) {
                case FXQUALITY_LOW:
                    RightColumn = TheText.Get("FED_FXL");
                    break;
                case FXQUALITY_MEDIUM:
                    RightColumn = TheText.Get("FED_FXM");
                    break;
                case FXQUALITY_HIGH:
                    RightColumn = TheText.Get("FED_FXH");
                    break;
                case FXQUALITY_VERY_HIGH:
                    RightColumn = TheText.Get("FED_FXV");
                    break;
                }
                break;
            case 58:
                RightColumn = TheText.Get(FrontEndMenuManager.m_nController ? "FET_CCN" : "FET_SCN");
                break;
            }

            unsigned int savedAlpha;
            float f_leftPosX = SCREEN_COORD_CENTER_X - SCREEN_COORD(282.0f / 2);
            float fPosnXForStats = SCREEN_COORD_CENTER_X - SCREEN_COORD(1113.0f / 2);
            float f_rightPosX = SCREEN_COORD_CENTER_X - SCREEN_COORD(-1113.0f / 2);
            float fPosY = SCREEN_COORD_CENTER_Y - SCREEN_COORD(-MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nPosnY) + (0.0f / 2);

            if (i == FrontEndMenuManager.m_nCurrentMenuEntry) {
                if (FrontEndMenuManager.m_nCurrentMenuPage != 5) {
                    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
                    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));

                    if (FrontEndMenuManager.m_nCurrentMenuPage == 0)
                        CSprite2d::DrawRect(CRect(fPosnXForStats - SCREEN_COORD(25.0f / 2), fPosY - SCREEN_COORD(12.5f / 2), (fPosnXForStats - SCREEN_COORD(25.0f / 2)) + SCREEN_MULTIPLIER(330.0f), (fPosY - SCREEN_COORD(12.5f / 2)) + SCREEN_MULTIPLIER(50.0f)), CRGBA(255, 255, 255, 50));
                    else
                        CSprite2d::DrawRect(CRect(f_leftPosX - SCREEN_COORD(25.0f / 2), fPosY - SCREEN_COORD(12.5f / 2), (f_leftPosX - SCREEN_COORD(25.0f / 2)) + SCREEN_MULTIPLIER(725.0f), (fPosY - SCREEN_COORD(12.5f / 2)) + SCREEN_MULTIPLIER(50.0f)), CRGBA(255, 255, 255, 50));

                    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
                }
            }

            CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7f));

            if (FrontEndMenuManager.m_nCurrentMenuPage == 7 || FrontEndMenuManager.m_nCurrentMenuPage == 9 || FrontEndMenuManager.m_nCurrentMenuPage == 10 || FrontEndMenuManager.m_nCurrentMenuPage == 16) {
                float width = CFont::GetStringWidth((char*)LeftColumn, true, false);

                if (width > SCREEN_COORD(690.0f))
                    CFont::SetScale(SCREEN_MULTIPLIER(0.9f * SCREEN_COORD(690.0f) / width), SCREEN_MULTIPLIER(1.7f));
            }

            // Print left column
            CFont::SetDropColor(CRGBA(0, 0, 0, 255));
            CFont::SetColor(CRGBA(255, 255, 255, 255));
            CFont::SetOrientation(ALIGN_LEFT);

            if (FrontEndMenuManager.m_nCurrentMenuPage == 0)
                CFont::PrintString(fPosnXForStats, fPosY, (char*)LeftColumn);
            else
                CFont::PrintString(f_leftPosX, fPosY, (char*)LeftColumn);


            // Print right column
            if (RightColumn) {
                float width = CFont::GetStringWidth((char*)RightColumn, true, false);

                if (width > SCREEN_COORD(312.0f))
                    CFont::SetScale(SCREEN_MULTIPLIER(0.8f * SCREEN_COORD(312.0f) / width), SCREEN_MULTIPLIER(1.7f));

                CFont::SetOrientation(ALIGN_RIGHT);
                CFont::PrintString(f_rightPosX, fPosY, (char*)RightColumn);
            }

            // Sliders
            CVector2D vecPosition;
            CVector2D vecScale;
            vecPosition.x = 285.0f;
            vecPosition.y = MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nPosnY + 2.0f;
            vecScale.x = 265.0f;
            vecScale.y = 28.5f;

            switch (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nActionType)
            {
            case 27:
            {
                // Brightness
                DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), FrontEndMenuManager.m_nPrefsBrightness * 0.0026041667f, true);
                break;
            }
            case 28:
            {
                // Radio Volume
                DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), FrontEndMenuManager.m_nPrefsMusicVolume * 0.015625f, true);
                break;
            }
            case 29:
            {
                // SFX Volume
                DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), FrontEndMenuManager.m_nPrefsSfxVolume * 0.015625f, true);
                break;
            }
            case 61:
            {
                // Draw Distance
                DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), (FrontEndMenuManager.m_fPrefsLOD - 0.925f) * 1.1428572f, true);
                break;
            }
            case 62:
            {
                // Mouse Sensitivity
                DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), (CCamera::m_fMouseAccelHorzntal / 0.005f), true);
                break;
            }
            }
        }
    }
}

void __fastcall MobileFrontEnd::ProcessMobileMenuOptions(void *ecx0, int, signed char nArrowsInput, bool *bReturn, bool bEnterInput) {
    switch (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_nCurrentMenuEntry].m_nActionType)
    {
    case 2:
        *bReturn = true;
        return;
    case 25:
        FrontEndMenuManager.m_bPrefsShowSubtitles = FrontEndMenuManager.m_bPrefsShowSubtitles == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 33:
        FrontEndMenuManager.m_bPrefsShowLegends = FrontEndMenuManager.m_bPrefsShowLegends == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 26:
        FrontEndMenuManager.m_bPrefsUseWideScreen = FrontEndMenuManager.m_bPrefsUseWideScreen == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 35:
        FrontEndMenuManager.m_bPrefsShowHud = FrontEndMenuManager.m_bPrefsShowHud == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 23:
        FrontEndMenuManager.field_31 = FrontEndMenuManager.field_31 == false;
        return;
    case 30:
        FrontEndMenuManager.m_bPrefsRadioEq = FrontEndMenuManager.m_bPrefsRadioEq == false;
        ((char(__stdcall *)(char))0x506F90)(FrontEndMenuManager.m_bPrefsRadioEq);
        FrontEndMenuManager.SaveSettings();
        return;
    case 31:
        FrontEndMenuManager.m_bPrefsRadioAutoSelect = FrontEndMenuManager.m_bPrefsRadioAutoSelect == false;
        ((char(__stdcall *)(char))0x506F80)(FrontEndMenuManager.m_bPrefsRadioAutoSelect);
        FrontEndMenuManager.SaveSettings();
        return;
    case 21:
        if (nArrowsInput >= 0)
        {
            if (FrontEndMenuManager.m_nStatsScrollDir == 1)
            {
                if (FrontEndMenuManager.m_fStatsScrollSpeed == 0.0f)
                    FrontEndMenuManager.m_fStatsScrollSpeed = 150.0f;
                else if (FrontEndMenuManager.m_fStatsScrollSpeed == 150.0f)
                    FrontEndMenuManager.m_fStatsScrollSpeed = 30.0f;
            }
            else
            {
                if (FrontEndMenuManager.m_fStatsScrollSpeed == 0.0f)
                    FrontEndMenuManager.m_fStatsScrollSpeed = 150.0f;
                else
                    FrontEndMenuManager.m_fStatsScrollSpeed = 0.0f;

                FrontEndMenuManager.m_nStatsScrollDir = 1;
            }
        }
        else
        {
            if (FrontEndMenuManager.m_nStatsScrollDir == 1)
            {
                if (FrontEndMenuManager.m_fStatsScrollSpeed != 0.0f)
                    FrontEndMenuManager.m_fStatsScrollSpeed = 0.0f;
                FrontEndMenuManager.m_nStatsScrollDir = 0;
            }
            else
            {
                if (FrontEndMenuManager.m_fStatsScrollSpeed == 0.0f)
                    FrontEndMenuManager.m_fStatsScrollSpeed = 150.0f;
                else if (FrontEndMenuManager.m_fStatsScrollSpeed == 150.0f)
                    FrontEndMenuManager.m_fStatsScrollSpeed = 30.0f;
            }
        }
        FrontEndMenuManager.SaveSettings();
        return;
    case 32:
        FrontEndMenuManager.ScrollRadioStations(nArrowsInput);
        FrontEndMenuManager.SaveSettings();
        return;
    case 34:
        if (nArrowsInput >= 0)
        {
            if (++FrontEndMenuManager.m_nPrefsRadarMode > 2)
                FrontEndMenuManager.m_nPrefsRadarMode = 0;
        }
        else
        {
            if (FrontEndMenuManager.m_nPrefsRadarMode)
                --FrontEndMenuManager.m_nPrefsRadarMode;
            else
                FrontEndMenuManager.m_nPrefsRadarMode = 2;
        }
        FrontEndMenuManager.SaveSettings();
        return;
    case 3:
    case 4:
    case 5:
        FrontEndMenuManager.SwitchToNewScreen(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_nCurrentMenuEntry].m_nTargetMenu);
        return;
    case 11:
        FrontEndMenuManager.m_nSelectedMissionPack = 261 * FrontEndMenuManager.m_nCurrentMenuEntry - 169;
        FrontEndMenuManager.SwitchToNewScreen(8);
    return;
    case 10:
        FrontEndMenuManager.ProcessMissionPackNewGame();
        return;
    case 13:
        if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_nCurrentMenuEntry].m_nType >= MENUENTRY_SAVE_1 && MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_nCurrentMenuEntry].m_nType <= MENUENTRY_SAVE_8)
        {
            FrontEndMenuManager.m_nSelectedSaveGame = FrontEndMenuManager.m_nCurrentMenuEntry - 1;
            if (FrontEndMenuManager.m_nCurrentMenuPage == 9)
            {
                if (FrontEndMobileMenuManager.SlotValidation[FrontEndMenuManager.m_nCurrentMenuEntry] != 1 && FrontEndMobileMenuManager.SlotValidation[FrontEndMenuManager.m_nCurrentMenuEntry] != 2)
                    FrontEndMenuManager.SwitchToNewScreen(11);
            }
            else if (FrontEndMenuManager.m_nCurrentMenuPage == 10)
            {
               if (FrontEndMobileMenuManager.SlotValidation[FrontEndMenuManager.m_nCurrentMenuEntry] != 1)
                    FrontEndMenuManager.SwitchToNewScreen(12);
            }
        }
        return;
    case 18:
        if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_nCurrentMenuEntry].m_nType >= MENUENTRY_SAVE_1 && MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_nCurrentMenuEntry].m_nType <= MENUENTRY_SAVE_8)
        {
            FrontEndMenuManager.m_nSelectedSaveGame = FrontEndMenuManager.m_nCurrentMenuEntry - 1;
            FrontEndMenuManager.SwitchToNewScreen(17);
        }
        return;
    case 12:
        *(char*)0xB72910 = FrontEndMenuManager.m_nSelectedMissionPack;
        FrontEndMenuManager.DoSettingsBeforeStartingAGame();
        return;
    case 14:
        *(char*)0xB72910 = 0;
        FrontEndMenuManager.DoSettingsBeforeStartingAGame();
        FrontEndMenuManager.m_bShutDownFrontEndRequested = true;
        return;
    case 15:
        FrontEndMenuManager.m_bShutDownFrontEndRequested = true;
        return;
    case 46:
        FrontEndMenuManager.bInvertMouseY = FrontEndMenuManager.bInvertMouseY == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 47:
        FrontEndMenuManager.m_bPrefsInvertPadX1 = FrontEndMenuManager.m_bPrefsInvertPadX1 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 48:
        FrontEndMenuManager.m_bPrefsInvertPadY1 = FrontEndMenuManager.m_bPrefsInvertPadY1 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 49:
        FrontEndMenuManager.m_bPrefsInvertPadX2 = FrontEndMenuManager.m_bPrefsInvertPadX2 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 50:
        FrontEndMenuManager.m_bPrefsInvertPadY2 = FrontEndMenuManager.m_bPrefsInvertPadY2 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 51:
        FrontEndMenuManager.m_bPrefsSwapPadAxis1 = FrontEndMenuManager.m_bPrefsSwapPadAxis1 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 52:
        FrontEndMenuManager.m_bPrefsSwapPadAxis2 = FrontEndMenuManager.m_bPrefsSwapPadAxis2 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 59:
        if (!FrontEndMenuManager.m_nController)
        {
            CVehicle::m_bEnableMouseSteering = CVehicle::m_bEnableMouseSteering == false;
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 60:
        if (!FrontEndMenuManager.m_nController)
        {
            CVehicle::m_bEnableMouseFlying = CVehicle::m_bEnableMouseFlying == false;
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 24:
        FrontEndMenuManager.m_bPrefsVsync = FrontEndMenuManager.m_bPrefsVsync == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 64:
        FrontEndMenuManager.m_bPrefsTracksAutoScan = FrontEndMenuManager.m_bPrefsTracksAutoScan == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 65:
        FrontEndMenuManager.m_bPrefsSavePhotos = FrontEndMenuManager.m_bPrefsSavePhotos == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 58:
        if (FrontEndMenuManager.m_nController == 1)
        {
            FrontEndMenuManager.m_nController = 0;
            *(bool*)0xB6EC2E = true;
        }
        else
        {
            FrontEndMenuManager.m_nController = 1;
            *(bool*)0xB6EC2E = false;
        }
        FrontEndMenuManager.SaveSettings();
        return;
    case 56:
        if (bEnterInput)
        {
            if (FrontEndMenuManager.m_nPrefsVideoMode != FrontEndMenuManager.m_nDisplayVideoMode)
            {
                FrontEndMenuManager.m_nDisplayVideoMode = FrontEndMenuManager.m_nPrefsVideoMode;
                ((void(*)(int))0x745C70)(FrontEndMenuManager.m_nDisplayVideoMode);

                FrontEndMenuManager.m_bShowMouse = true;
                FrontEndMenuManager.SaveSettings();
            }
        }
        else
        {
            char** pVideoModes = ((char**(*)())0x745AF0)();
            int nNumVideoModes = RwEngineGetNumVideoModes();

            if (nArrowsInput > 0)
            {
                int        nCurrentVidMode = FrontEndMenuManager.m_nPrefsVideoMode + 1;

                if (nCurrentVidMode >= nNumVideoModes)
                    nCurrentVidMode = 0;

                while (!pVideoModes[nCurrentVidMode])
                {
                    ++nCurrentVidMode;

                    if (nCurrentVidMode >= nNumVideoModes)
                        nCurrentVidMode = 0;
                }

                FrontEndMenuManager.m_nPrefsVideoMode = nCurrentVidMode;
            }
            else
            {
                int nCurrentVidMode = FrontEndMenuManager.m_nPrefsVideoMode - 1;

                if (nCurrentVidMode < 0)
                    nCurrentVidMode = nNumVideoModes - 1;

                while (!pVideoModes[nCurrentVidMode])
                {
                    --nCurrentVidMode;

                    if (nCurrentVidMode < 0)
                        nCurrentVidMode = nNumVideoModes - 1;
                }

                FrontEndMenuManager.m_nPrefsVideoMode = nCurrentVidMode;
            }
        }
        return;
    case 44:
        if (bEnterInput)
        {
            if (FrontEndMenuManager.m_nAntiAliasingLevel != FrontEndMenuManager.m_nAntiAliasingLevel)
            {
                FrontEndMenuManager.m_nAntiAliasingLevel = FrontEndMenuManager.m_nAntiAliasingLevel;

                RwD3D9ChangeMultiSamplingLevels(FrontEndMenuManager.m_nAntiAliasingLevel);
                ((void(*)(int))0x745C70)(FrontEndMenuManager.m_nDisplayVideoMode);
                FrontEndMenuManager.SaveSettings();
            }
        }
        else
        {
            int nNumMultiSamplingModes = RwD3D9EngineGetMaxMultiSamplingLevels();

            if (nNumMultiSamplingModes > 4)
                nNumMultiSamplingModes = 4;

            if (nArrowsInput > 0)
            {
                int nCurrentMode = FrontEndMenuManager.m_nAntiAliasingLevel + 1;

                if (nCurrentMode > nNumMultiSamplingModes)
                    nCurrentMode = 1;

                FrontEndMenuManager.m_nAntiAliasingLevel = nCurrentMode;
            }
            else
            {
                int nCurrentMode = FrontEndMenuManager.m_nAntiAliasingLevel - 1;

                if (nCurrentMode <= 0)
                    nCurrentMode = nNumMultiSamplingModes;

                FrontEndMenuManager.m_nAntiAliasingLevel = nCurrentMode;
            }
        }
        return;
    case 42:
        if (nArrowsInput >= 0)
        {
            switch (g_fx.GetFxQuality())
            {
            case FXQUALITY_LOW:
                g_fx.SetFxQuality(FXQUALITY_MEDIUM);
                break;
            case FXQUALITY_MEDIUM:
                g_fx.SetFxQuality(FXQUALITY_HIGH);
                break;
            case FXQUALITY_HIGH:
                g_fx.SetFxQuality(FXQUALITY_VERY_HIGH);
                break;
            case FXQUALITY_VERY_HIGH:
                g_fx.SetFxQuality(FXQUALITY_LOW);
                break;
            }
        }
        else
        {
            switch (g_fx.GetFxQuality())
            {
            case FXQUALITY_LOW:
                g_fx.SetFxQuality(FXQUALITY_VERY_HIGH);
                break;
            case FXQUALITY_MEDIUM:
                g_fx.SetFxQuality(FXQUALITY_LOW);
                break;
            case FXQUALITY_HIGH:
                g_fx.SetFxQuality(FXQUALITY_MEDIUM);
                break;
            case FXQUALITY_VERY_HIGH:
                g_fx.SetFxQuality(FXQUALITY_HIGH);
                break;
            }
        }
        FrontEndMenuManager.SaveSettings();
        return;
    case 63:
        if (nArrowsInput >= 0)
        {
            if (++FrontEndMenuManager.m_nPrefsRadioMode > 2)
                FrontEndMenuManager.m_nPrefsRadioMode = 0;
        }
        else
        {
            if (FrontEndMenuManager.m_nPrefsRadioMode)
                --FrontEndMenuManager.m_nPrefsRadioMode;
            else
                FrontEndMenuManager.m_nPrefsRadioMode = 2;
        }
        FrontEndMenuManager.SaveSettings();
        return;
    case 54:
        FrontEndMenuManager.m_bShutDownFrontEndRequested = true;
        return;
    case 57:
        FrontEndMenuManager.SetDefaultPreferences((eMenuPage)MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[2].m_nTargetMenu);

        if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[2].m_nTargetMenu == 36)
            CallAndReturn<char, 0x531F20>();

        FrontEndMenuManager.SaveSettings();
        FrontEndMenuManager.SwitchToNewScreen(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[2].m_nTargetMenu);
        return;
    case 7:
        FrontEndMenuManager.SwitchToNewScreen(FrontEndMenuManager.m_nController == 1 ? 40 : 39);
        return;
    case 8:
        FrontEndMenuManager.m_bInVehicleControlsScreen = false;
        FrontEndMenuManager.SwitchToNewScreen(38);
        FrontEndMenuManager.field_90 = 0;
        return;
    case 9:
        FrontEndMenuManager.m_bInVehicleControlsScreen = true;
        FrontEndMenuManager.SwitchToNewScreen(38);
        FrontEndMenuManager.field_90 = 0;
        return;
    case 45:
        FrontEndMenuManager.field_1B14 = 1;
        FrontEndMenuManager.field_1B09 = 1;
        FrontEndMenuManager.field_1B08 = 1;
        FrontEndMenuManager.field_1B0C = FrontEndMenuManager.m_nCurrentMenuEntry;
        FrontEndMenuManager.pControlEdit = (int*)FrontEndMenuManager.field_36[2];
        return;
    case 53:
        FrontEndMenuManager.SwitchToNewScreen(43);
        return;
    case 55:
        FrontEndMenuManager.SwitchToNewScreen(-2);
        return;
    case 6:
        FrontEndMenuManager.m_bScanningUserTracks = 1;
        return;
    case 37:
        if (FrontEndMenuManager.m_nPrefsLanguage != 0)
        {
            FrontEndMenuManager.m_nPrefsLanguage = 0;
            FrontEndMenuManager.m_bReinitLanguageSettings = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 38:
        if (FrontEndMenuManager.m_nPrefsLanguage != 1)
        {
            FrontEndMenuManager.m_nPrefsLanguage = 1;
            FrontEndMenuManager.m_bReinitLanguageSettings = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 39:
        if (FrontEndMenuManager.m_nPrefsLanguage != 2)
        {
            FrontEndMenuManager.m_nPrefsLanguage = 2;
            FrontEndMenuManager.m_bReinitLanguageSettings = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 40:
        if (FrontEndMenuManager.m_nPrefsLanguage != 3)
        {
            FrontEndMenuManager.m_nPrefsLanguage = 3;
            FrontEndMenuManager.m_bReinitLanguageSettings = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 41:
        if (FrontEndMenuManager.m_nPrefsLanguage != 4)
        {
            FrontEndMenuManager.m_nPrefsLanguage = 4;
            FrontEndMenuManager.m_bReinitLanguageSettings = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
        // Net
    case 100:
        return;
    }
}

void MobileFrontEnd::PrintRadioStationList() {
    signed int v2 = 1;
    int savedAlpha;
    float fPosX = SCREEN_COORD_CENTER_X - SCREEN_COORD(282.5f / 2);
    float fPosY = SCREEN_COORD_CENTER_Y - SCREEN_COORD(-270.0f / 2);
    float spacing = SCREEN_COORD(0.5f);
    float size = SCREEN_MULTIPLIER(58.125f);

    do {
        if (FrontEndMenuManager.m_nPrefsRadioStation == v2) {
            RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));
            CSprite2d::DrawRect(CRect((fPosX - SCREEN_COORD(2.0f)) + (spacing), fPosY - SCREEN_COORD(2.0f), (fPosX - SCREEN_COORD(2.0f)) + (spacing) + (size + SCREEN_COORD(4.0f)), fPosY - SCREEN_COORD(2.0f) + (size + SCREEN_COORD(4.0f))), CRGBA(255, 255, 255, 100));
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
        }

        FrontEndMenuManager.m_aMenuSprites[v2].Draw(CRect(fPosX + (spacing), fPosY, fPosX + (spacing) + (size), fPosY + (size)), CRGBA(255, 255, 255, FrontEndMenuManager.m_nPrefsRadioStation == v2 ? 255 : 50));

        if (FrontEndMenuManager.m_nPrefsRadioStation == v2) {
            RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));
            CSprite2d::DrawRect(CRect((fPosX - SCREEN_COORD(2.0f)) + (spacing), fPosY - SCREEN_COORD(2.0f), (fPosX - SCREEN_COORD(2.0f)) + (spacing) + (size + SCREEN_COORD(4.0f)), fPosY - SCREEN_COORD(2.0f) + (size + SCREEN_COORD(4.0f))), 
                CRGBA(255, 255, 255, 50), CRGBA(255, 255, 255, 50),
                CRGBA(255, 255, 255, 0), CRGBA(255, 255, 255, 0));
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
        }

        ++v2;
        spacing += size;
    } while (v2 < 13);
}

void MobileFrontEnd::PrintMap() {
    int savedAlpha;
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));

    // Background
    CSprite2d::DrawRect(CRect(0.0f, 0.0f, 0.0f + SCREEN_WIDTH, 0.0f + SCREEN_HEIGHT), CRGBA(0, 0, 0, 255));

    // PrintMap TODO: Draw our own map?!?
    FrontEndMenuManager.PrintMap();

    // Mask
    mobileTex.m_nBackgroundSprite.m_pTexture = mobileTex.m_nBackgroundSpriteTxd.GetTexture(MENU_MAINMASK);
    mobileTex.m_nBackgroundSprite.Draw(CRect(SCREEN_COORD(-600.0), SCREEN_COORD_BOTTOM(535.0f), SCREEN_COORD(-600.0) + SCREEN_WIDTH + SCREEN_COORD(600.0 * 2), SCREEN_COORD_BOTTOM(535.0f) + SCREEN_MULTIPLIER(535.0f)), CRGBA(255, 255, 255, 240));
    mobileTex.m_nBackgroundSprite.m_pTexture = nullptr;

    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
}

void MobileFrontEnd::PrintLegend() {
    signed int v104 = 0;
    float fSpacingX = 0.0f;
    float fSpacingY = 0.0f;
    char *str;
    CFont::SetBackground(0, 0);
    CFont::SetProportional(1);
    CFont::SetWrapx(SCREEN_COORD_MAX_X - 12.5f);
    CFont::SetEdge(0);
    CFont::SetDropShadowPosition(1);
    CFont::SetDropColor(CRGBA(0, 0, 0, 255));
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_BLUELIGHT, 255));
    CFont::SetOrientation(ALIGN_LEFT);
    CFont::SetFontStyle(FONT_MENU);

   // if (FrontEndMenuManager.m_bMapLegend) {
        if (CRadar::MapLegendCounter) {
            do {
                switch (CRadar::MapLegendList[v104])
                {
                case 3:
                    str = TheText.Get("LG_01");
                    break;
                case 5:
                    str = TheText.Get("LG_02");
                    break;
                case 6:
                    str = TheText.Get("LG_03");
                    break;
                case 7:
                    str = TheText.Get("LG_04");
                    break;
                case 8:
                    str = TheText.Get("LG_05");
                    break;
                case 9:
                    str = TheText.Get("LG_06");
                    break;
                case 10:
                    str = TheText.Get("LG_07");
                    break;
                case 12:
                    str = TheText.Get("LG_09");
                    break;
                case 13:
                    str = TheText.Get("LG_10");
                    break;
                case 14:
                    str = TheText.Get("LG_11");
                    break;
                case 15:
                    str = TheText.Get("LG_12");
                    break;
                case 16:
                    str = TheText.Get("LG_13");
                    break;
                case 18:
                    str = TheText.Get("LG_15");
                    break;
                case 19:
                    str = TheText.Get("LG_16");
                    break;
                case 20:
                    str = TheText.Get("LG_17");
                    break;
                case 21:
                    str = TheText.Get("LG_18");
                    break;
                case 22:
                    str = TheText.Get("LG_19");
                    break;
                case 23:
                    str = TheText.Get("LG_20");
                    break;
                case 24:
                    str = TheText.Get("LG_21");
                    break;
                case 25:
                    str = TheText.Get("LG_22");
                    break;
                case 26:
                    str = TheText.Get("LG_23");
                    break;
                case 27:
                    str = TheText.Get("LG_24");
                    break;
                case 28:
                    str = TheText.Get("LG_25");
                    break;
                case 29:
                    str = TheText.Get("LG_26");
                    break;
                case 30:
                    str = TheText.Get("LG_27");
                    break;
                case 31:
                    str = TheText.Get("LG_28");
                    break;
                case 32:
                    str = TheText.Get("LG_29");
                    break;
                case 33:
                    str = TheText.Get("LG_30");
                    break;
                case 34:
                    str = TheText.Get("LG_31");
                    break;
                case 35:
                    str = TheText.Get("LG_32");
                    break;
                case 36:
                    str = TheText.Get("LG_33");
                    break;
                case 63:
                    str = TheText.Get("LG_34");
                    break;
                case 38:
                    str = TheText.Get("LG_35");
                    break;
                case 39:
                    str = TheText.Get("LG_36");
                    break;
                case 40:
                    str = TheText.Get("LG_37");
                    break;
                case 42:
                    str = TheText.Get("LG_39");
                    break;
                case 43:
                    str = TheText.Get("LG_40");
                    break;
                case 44:
                    str = TheText.Get("LG_41");
                    break;
                case 45:
                    str = TheText.Get("LG_42");
                    break;
                case 46:
                    str = TheText.Get("LG_43");
                    break;
                case 47:
                    str = TheText.Get("LG_44");
                    break;
                case 48:
                    str = TheText.Get("LG_45");
                    break;
                case 49:
                    str = TheText.Get("LG_46");
                    break;
                case 50:
                    str = TheText.Get("LG_47");
                    break;
                case 51:
                    str = TheText.Get("LG_48");
                    break;
                case 52:
                    str = TheText.Get("LG_51");
                    break;
                case 53:
                    str = TheText.Get("LG_52");
                    break;
                case 54:
                    str = TheText.Get("LG_53");
                    break;
                case 55:
                    str = TheText.Get("LG_57");
                    break;
                case 58:
                    str = TheText.Get("LG_58");
                    break;
                case 59:
                    str = TheText.Get("LG_59");
                    break;
                case 60:
                    str = TheText.Get("LG_60");
                    break;
                case 61:
                    str = TheText.Get("LG_61");
                    break;
                case 62:
                    str = TheText.Get("LG_62");
                    break;
                case 37:
                    str = TheText.Get("LG_63");
                    break;
                case 41:
                    str = TheText.Get("LG_64");
                    break;
                case 11:
                    str = TheText.Get("LG_66");
                    break;
                case 17:
                    str = TheText.Get("LG_67");
                    break;
                case 57:
                    str = TheText.Get("LG_65");
                    break;
                case 4294967295:
                    str = TheText.Get("LG_49");
                    break;
                case 4294967294:
                    str = TheText.Get("LG_50");
                    break;
                case 4294967293:
                    str = TheText.Get("LG_54");
                    break;
                case 4294967292:
                    str = TheText.Get("LG_55");
                    break;
                case 4294967291:
                    str = TheText.Get("LG_56");
                    break;
                default:
                    str = TheText.Get("LG_00");
                    break;
                }

                CFont::SetScale(SCREEN_MULTIPLIER(0.4f), SCREEN_MULTIPLIER(1.0f));
                float width = CFont::GetStringWidth(str, true, false);
                if (width > SCREEN_MULTIPLIER(150.0f))
                    CFont::SetScale(SCREEN_MULTIPLIER(0.4f * SCREEN_MULTIPLIER(150.0f) / width), SCREEN_MULTIPLIER(1.0f));
                CFont::PrintString(SCREEN_COORD_LEFT(45.0f) + fSpacingX, SCREEN_COORD_BOTTOM(225.0f) + fSpacingY, str);
                CRadar::DrawLegend(SCREEN_COORD_LEFT(5.0f) + fSpacingX, SCREEN_COORD_BOTTOM(230.0f) + fSpacingY, CRadar::MapLegendList[v104]);

                if (v104 == 6) {
                    fSpacingX += SCREEN_COORD(200.0f);
                    fSpacingY -= SCREEN_COORD(32.0f * 6);
                }
                else if (v104 == 13) {
                    fSpacingX += SCREEN_COORD(200.0f);
                    fSpacingY -= SCREEN_COORD(32.0f * 6);
                }
                else if (v104 == 20) {
                    fSpacingX += SCREEN_COORD(200.0f);
                    fSpacingY -= SCREEN_COORD(32.0f * 6);
                }
                else if (v104 == 27) {
                    fSpacingX += SCREEN_COORD(200.0f);
                    fSpacingY -= SCREEN_COORD(32.0f * 6);
                }
                else
                    fSpacingY += SCREEN_COORD(32.0f);

                ++v104;

            } while (v104 < CRadar::MapLegendCounter);
        }
   // }
}

void MobileFrontEnd::PrintPlaceName() {
    // Place 
    CFont::SetBackground(0, 0);
    CFont::SetProportional(1);
    CFont::SetWrapx(SCREEN_COORD_MAX_X - 12.5f);
    CFont::SetEdge(3);
    CFont::SetDropColor(CRGBA(0, 0, 0, 255));
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
    CFont::SetOrientation(ALIGN_RIGHT);
    CFont::SetFontStyle(FONT_PRICEDOWN);
    CFont::SetScale(SCREEN_MULTIPLIER(0.8f), SCREEN_MULTIPLIER(1.8f));

    char *strc = GetForMap(FrontEndMenuManager.m_vMousePos.x, FrontEndMenuManager.m_vMousePos.y);
    CFont::PrintString(SCREEN_COORD_RIGHT(30.0f), SCREEN_COORD_BOTTOM(120.0f), strc);
}

void MobileFrontEnd::DisplaySlider(float x, float y, float width, float height, float progress, bool bNub) {
    // empty
    mobileTex.m_menuSlider.m_pTexture = mobileTex.m_menuSliderTxd.GetTexture(MENU_SLIDER_EMPTY);
    mobileTex.m_menuSlider.Draw(CRect(x, y, x + width, y + height), CRGBA(255, 255, 255, 255));
    // full
    mobileTex.m_menuSlider.m_pTexture = mobileTex.m_menuSliderTxd.GetTexture(MENU_SLIDER_FULL);
    mobileTex.m_menuSlider.Draw(CRect(x, y, x + width * progress, y + height), CRGBA(255, 255, 255, 255),
        0.0f, 1.0f, progress, 1.0f, 0.0f, 0.0f, progress, 0.0f);

    // percentage
    static char text[4];
    static float percentage;
    percentage = progress * 100.0f;
    sprintf(text, "%d%%", static_cast<int>(percentage));

    CFont::SetWrapx(SCREEN_WIDTH);
    CFont::SetRightJustifyWrap(0.0f);
    CFont::SetEdge(0);
    CFont::SetFontStyle(FONT_SUBTITLES);
    CFont::SetScale(height * 0.020f, height * 0.038f);

    if (percentage > 80.0f) {
        CFont::SetOrientation(ALIGN_LEFT);
        CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_BLACK, 200));
        CFont::PrintString(x + SCREEN_COORD(12.0f), y + SCREEN_COORD(3.5f), text);
    }
    if (percentage < 80.0) {
        CFont::SetOrientation(ALIGN_RIGHT);
        CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
        CFont::PrintString(x + width - SCREEN_COORD(12.0f), y + SCREEN_COORD(3.5f), text);
    }

    // nub
    mobileTex.m_menuSlider.m_pTexture = mobileTex.m_menuSliderTxd.GetTexture(MENU_SLIDER_NUB);

    if (bNub)
        mobileTex.m_menuSlider.Draw((x)+(width - SCREEN_COORD(29.0f)) * (progress), (y), height * 1.0f, height * 1.0f, CRGBA(255, 255, 255, 255));
 
    mobileTex.m_menuSlider.m_pTexture = nullptr;
}


void MobileFrontEnd::PrintStats() {
    FrontEndMenuManager.PrintStats();

    char *Rate = CStats::FindCriminalRatingString();
    static char Value[6];

    // Player Rating 
    CFont::SetBackground(0, 0);
    CFont::SetProportional(1);
    CFont::SetWrapx(SCREEN_COORD_MAX_X - 12.5f);
    CFont::SetEdge(0);
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
    CFont::SetOrientation(ALIGN_LEFT);
    CFont::SetFontStyle(FONT_PRICEDOWN);
    CFont::SetScale(SCREEN_MULTIPLIER(0.8f), SCREEN_MULTIPLIER(1.5f));

    sprintf(gString, "%d", CStats::FindCriminalRatingNumber());
    AsciiToGxtChar(gString, Value);

    CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(1113.0f / 2), SCREEN_COORD_BOTTOM(60.0f), Rate);
    CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(1075.0f / 2) + CFont::GetStringWidth(Rate, true, false), SCREEN_COORD_BOTTOM(60.0f), Value);
}

void MobileFrontEnd::PrintStatsText(float x, float y, char *str) {
    CFont::SetOrientation(ALIGN_LEFT);
    CFont::SetFontStyle(FONT_SUBTITLES);
    CFont::SetEdge(2);
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
    CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7f));
    CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(450.0f / 2), y, str);
}

void MobileFrontEnd::PrintStatsText2(float x, float y, char *str) {
    CFont::SetOrientation(ALIGN_RIGHT);
    CFont::SetFontStyle(FONT_SUBTITLES);
    CFont::SetEdge(2);
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
    CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7f));
    CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(-1113.0f / 2), y - SCREEN_COORD(35.0f), str);
}

void MobileFrontEnd::DrawStatsSlider(float x, float y, unsigned short width, unsigned char height, float percentage, signed char,
    unsigned char, unsigned char, CRGBA, CRGBA) {
    CVector2D vecPosition;
    CVector2D vecScale;
    vecPosition.x = 285.0f;
    vecPosition.y = 0.0f;
    vecScale.x = 265.0f;
    vecScale.y = 28.5f;

    DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), y - SCREEN_COORD(28.0f), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), percentage / 100, false);
}

void MobileFrontEnd::PrintBriefsText(float x, float y, char *str) {
    CFont::SetEdge(2);
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
    CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7f));
    CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(282.0f / 2), y, str);
}
