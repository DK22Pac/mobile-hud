#include "MobileFrontEnd.h"
#include "game_sa\CHudColours.h"

MobileTexDictionary MobileFrontEnd::m_menuSliderTxd;
MobileFrontEnd FrontEndMobile;

void MobileFrontEnd::InstallPatches() {
    plugin::patch::Set(0x57B764, 0x36EBC030);
    plugin::patch::RedirectCall(0x57BA58, DrawStandardMenu);
    plugin::patch::RedirectCall(0x57B66F, ProcessMobileMenuOptions);
    plugin::patch::RedirectCall(0x57B702, ProcessMobileMenuOptions);
    plugin::patch::RedirectCall(0x574F54, DrawStatsSlider);
}

void MobileFrontEnd::Setup() {
    m_menuSliderTxd.Init(PLUGIN_PATH("MobileHud\\menu_slider.txd"));
}

void __fastcall MobileFrontEnd::DrawStandardMenu(void *ecx0, int, char a2) {
    CFont::SetBackground(0, 0);
    CFont::SetProp(1);
    CFont::SetWrapx(SCREEN_COORD_MAX_X - 12.5f);
    CFont::SetOutlinePosition(2);
    CFont::SetRightJustifyWrap(12.5f);
    CFont::SetCentreSize(SCREEN_COORD_MAX_X);
    CFont::SetDropColor(CRGBA(0, 0, 0, 255));

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_STATS) {
        // PrintStats
    }

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_BRIEF) {
        // PrintBrief
    }

    // Header
    if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_szTitleName[0]) {
        if (FrontEndMenuManager.m_nCurrentMenuPage != 5 || !FrontEndMenuManager.field_78) {
            CFont::SetAlignment(ALIGN_LEFT);
            CFont::SetFontStyle(FONT_GOTHIC);
            CFont::SetScale(SCREEN_MULTIPLIER(1.8), SCREEN_MULTIPLIER(3.6f));
            CFont::SetOutlinePosition(2);
            CFont::SetColor(CRGBA(255, 255, 255, 255));
            CFont::SetDropColor(CRGBA(0, 0, 0, 255));
            CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(282.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(794.0f / 2), TheText.Get(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_szTitleName));
        }
    }

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_AUDIO_SETTINGS) {
        MobileFrontEnd::PrintRadioStationList();
    }

    // Actions
    if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_nActionType == 1)
    {
        static char* pText;
        CFont::SetFontStyle(FONT_SUBTITLES);
        CFont::SetAlignment(ALIGN_LEFT);
        CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7f));
        CFont::SetOutlinePosition(2);
        CFont::SetColor(CRGBA(255, 255, 255, 255));
        CFont::SetDropColor(CRGBA(0, 0, 0, 255));

        switch (FrontEndMenuManager.m_nCurrentMenuPage)
        {
        case 6:
        {
            pText = TheText.Get(FrontEndMenuManager.m_bMainMenuSwitch ? "FESZ_QQ" : MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_szName);
            break;
        }
        case 35:
        {
            pText = TheText.Get(FrontEndMenuManager.m_bMainMenuSwitch ? "FEQ_SRW" : MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_szName);
            break;
        }
        case 17:
        {
            if (FrontEndMobile.SlotValidation[FrontEndMenuManager.m_bSelectedSaveGame + 1]) {
                if (FrontEndMobile.SlotValidation[FrontEndMenuManager.m_bSelectedSaveGame + 1] != 2) {
                    pText = TheText.Get("FESZ_QC");
                }
                else {
                    pText = TheText.Get("FESZ_QO");
                }
            }
            break;
        }
        case 11:
        {
            pText = TheText.Get(FrontEndMenuManager.m_bMainMenuSwitch ? "FES_LCG" : MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_szName);
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

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_CONTROLS_VEHICLE_ONFOOT) {
        //DrawControllerScreenExtraText // Don't know if really used
    }

    for (unsigned int i = 0; i < 12; i++) {
        CFont::SetFontStyle(FONT_MENU);
        CFont::SetOutlinePosition(2);

        if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nActionType != 1 && MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_szName[0]) {
            const char* LeftColumn = nullptr;
            const char* RightColumn = nullptr;
            char ReservedSpace[64];

            if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nType >= MENU_ENTRY_SAVE_1 && MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nType <= MENU_ENTRY_SAVE_8) { 
                switch (FrontEndMobile.SlotValidation[i]) {
                case 0:
                    LeftColumn = plugin::CallAndReturn<const char*, 0x5D0F40>(i - 1);
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

            else if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nType == MENU_ENTRY_MISSIONPACK) {
            }

            else if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nType == MENU_ENTRY_JOYMOUSE) {
                LeftColumn = TheText.Get(FrontEndMenuManager.m_nController ? "FEJ_TIT" : "FEC_MOU");
            }

            else {
                LeftColumn = TheText.Get(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_szName);
            }

            CAERadioTrackManager RadioEntity;

            switch (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nActionType) {
            case 31:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bRadioAutoSelect ? "FEM_ON" : "FEM_OFF");
                break;
            case 32:
                RightColumn = RadioEntity.GetRadioStationName(FrontEndMenuManager.m_nRadioStation);
                break;
            case 33:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bMapLegend ? "FEM_ON" : "FEM_OFF");
                break;
            case 25:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bShowSubtitles ? "FEM_ON" : "FEM_OFF");
                break;
            case 26:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bWidescreenOn ? "FEM_ON" : "FEM_OFF");
                break;
            case 34:
                switch (FrontEndMenuManager.m_dwRadarMode) {
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
                switch (FrontEndMenuManager.m_bHudOn) {
                case 0:
                    RightColumn = TheText.Get("FEM_OFF");
                    FrontEndMenuManager.m_dwRadarMode = 2;
                    break;
                case 1:
                    RightColumn = TheText.Get("FEM_ON");
                    FrontEndMenuManager.m_dwRadarMode = 0;
                    break;
                }
                break;
            case 65:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bSavePhotos ? "FEM_ON" : "FEM_OFF");
                break;
            case 63:
                switch (FrontEndMenuManager.m_nRadioMode) {
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
                RightColumn = TheText.Get(FrontEndMenuManager.m_bFrameLimiterOn ? "FEM_ON" : "FEM_OFF");
                break;
            case 43:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bMipMapping ? "FEM_ON" : "FEM_OFF");
                break;
            case 64:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bTracksAutoScan ? "FEM_ON" : "FEM_OFF");
                break;
            case 46:
                RightColumn = TheText.Get(!FrontEndMenuManager.bInvertMouseY ? "FEM_ON" : "FEM_OFF");
                break;
            case 47:
                RightColumn = TheText.Get(FrontEndMenuManager.invertPadX1 ? "FEM_ON" : "FEM_OFF");
                break;
            case 48:
                RightColumn = TheText.Get(FrontEndMenuManager.invertPadY1 ? "FEM_ON" : "FEM_OFF");
                break;
            case 49:
                RightColumn = TheText.Get(FrontEndMenuManager.invertPadX2 ? "FEM_ON" : "FEM_OFF");
                break;
            case 50:
                RightColumn = TheText.Get(FrontEndMenuManager.invertPadY2 ? "FEM_ON" : "FEM_OFF");
                break;
            case 51:
                RightColumn = TheText.Get(FrontEndMenuManager.swapPadAxis1 ? "FEM_ON" : "FEM_OFF");
                break;
            case 52:
                RightColumn = TheText.Get(FrontEndMenuManager.swapPadAxis2 ? "FEM_ON" : "FEM_OFF");
                break;
            case 59:
                RightColumn = TheText.Get(CVehicle::m_bEnableMouseSteering ? "FEM_ON" : "FEM_OFF");
                break;
            case 60:
                RightColumn = TheText.Get(CVehicle::m_bEnableMouseFlying ? "FEM_ON" : "FEM_OFF");
                break;
            case 56:
            {
                const char* pszResolution = ((const char**(*)())0x745AF0)()[FrontEndMenuManager.m_dwResolution];

                if (!pszResolution)
                    pszResolution = "";

                strncpy(ReservedSpace, pszResolution, sizeof(ReservedSpace));
                RightColumn = ReservedSpace;
            }
            break;
            case 44:
                if (FrontEndMenuManager.m_dwAntiAliasingLevel <= 1)
                    RightColumn = TheText.Get("FEM_OFF");
                else {
                    switch (FrontEndMenuManager.m_dwAntiAliasingLevel)
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
            float f_rightPosX = SCREEN_COORD_CENTER_X - SCREEN_COORD(-1113.0f / 2);
            float fPosY = SCREEN_COORD_CENTER_Y - SCREEN_COORD(-MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_wPosnY) + (0.0f / 2);

            if (i == FrontEndMenuManager.m_dwSelectedMenuItem) {
                if (FrontEndMenuManager.m_nCurrentMenuPage != 5) {
                    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
                    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));
                    CSprite2d::DrawRect(CRect(f_leftPosX - SCREEN_COORD(25.0f / 2), fPosY - SCREEN_COORD(12.5f / 2), (f_leftPosX - SCREEN_COORD(25.0f / 2)) + SCREEN_MULTIPLIER(725.0f), (fPosY - SCREEN_COORD(12.5f / 2)) + SCREEN_MULTIPLIER(50.0f)), CRGBA(255, 255, 255, 50));
                    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
                }
            }

            CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7));
            if (FrontEndMenuManager.m_nCurrentMenuPage == 7 || FrontEndMenuManager.m_nCurrentMenuPage == 9 || FrontEndMenuManager.m_nCurrentMenuPage == 10 || FrontEndMenuManager.m_nCurrentMenuPage == 16) {
                float width = CFont::GetStringWidth((char*)LeftColumn, true, false);

                if (width > SCREEN_COORD(690.0f))
                    CFont::SetScale(SCREEN_MULTIPLIER(0.9f * SCREEN_COORD(690.0f) / width), SCREEN_MULTIPLIER(1.7f));
            }

            // Print left column
            CFont::SetDropColor(CRGBA(0, 0, 0, 255));
            CFont::SetColor(CRGBA(255, 255, 255, 255));
            CFont::SetAlignment(ALIGN_LEFT);
            CFont::PrintString(f_leftPosX, fPosY, (char*)LeftColumn);

            // Print right column
            if (RightColumn) {
                float width = CFont::GetStringWidth((char*)RightColumn, true, false);

                if (width > SCREEN_COORD(312.0f))
                    CFont::SetScale(SCREEN_MULTIPLIER(0.8f * SCREEN_COORD(312.0f) / width), SCREEN_MULTIPLIER(1.7f));

                CFont::SetAlignment(ALIGN_RIGHT);
                CFont::PrintString(f_rightPosX, fPosY, (char*)RightColumn);
            }

            // Sliders
            float sliderposX = SCREEN_COORD_CENTER_X - SCREEN_COORD(-430.0f * 900 / 720 / 2);
            float sliderposY = SCREEN_COORD_CENTER_Y - SCREEN_COORD(-MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_wPosnY) + (15.0f * 900 / 720 / 2);

            switch (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nActionType)
            {
            case 27:
            {
                // Brightness
                DisplaySlider(sliderposX, sliderposY, SCREEN_MULTIPLIER(228 * 900 / 720), SCREEN_MULTIPLIER(16.0f * 900 / 720), FrontEndMenuManager.m_dwBrightness * 1.0f / 282.0f);
                break;
            }
            case 28:
            {
                // Radio Volume
                DisplaySlider(sliderposX, sliderposY, SCREEN_MULTIPLIER(228 * 900 / 720), SCREEN_MULTIPLIER(16.0f * 900 / 720), FrontEndMenuManager.m_nRadioVolume * 1.0f / 64.0f);
                break;
            }
            case 29:
            {
                // SFX Volume
                DisplaySlider(sliderposX, sliderposY, SCREEN_MULTIPLIER(228 * 900 / 720), SCREEN_MULTIPLIER(16.0f * 900 / 720), FrontEndMenuManager.m_nSfxVolume * 1.0f / 64.0f);
                break;
            }
            case 61:
            {
                // Draw Distance
                DisplaySlider(sliderposX, sliderposY, SCREEN_MULTIPLIER(228 * 900 / 720), SCREEN_MULTIPLIER(16.0f * 900 / 720), (FrontEndMenuManager.m_fDrawDistance - 0.922f) * 1.0f / 0.876f);
                break;
            }
            case 62:
            {
                // Mouse Sensitivity
                DisplaySlider(sliderposX, sliderposY, SCREEN_MULTIPLIER(228 * 900 / 720), SCREEN_MULTIPLIER(16.0f * 900 / 720), (CCamera::m_fMouseAccelHorzntl - 0.0003125f) * 1.0f / 0.0049f);
                break;
            }
            }
        }
    }
}

void __fastcall MobileFrontEnd::ProcessMobileMenuOptions(void *ecx0, int, signed char nArrowsInput, bool *bReturn, bool bEnterInput) {
    switch (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_dwSelectedMenuItem].m_nActionType)
    {
    case 2:
        *bReturn = true;
        return;
    case 25:
        FrontEndMenuManager.m_bShowSubtitles = FrontEndMenuManager.m_bShowSubtitles == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 33:
        FrontEndMenuManager.m_bMapLegend = FrontEndMenuManager.m_bMapLegend == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 26:
        FrontEndMenuManager.m_bWidescreenOn = FrontEndMenuManager.m_bWidescreenOn == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 35:
        FrontEndMenuManager.m_bHudOn = FrontEndMenuManager.m_bHudOn == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 23:
        FrontEndMenuManager.field_31 = FrontEndMenuManager.field_31 == false;
        return;
    case 31:
        FrontEndMenuManager.m_bRadioAutoSelect = FrontEndMenuManager.m_bRadioAutoSelect == false;
        ((char(__stdcall *)(char))0x506F80)(FrontEndMenuManager.m_bRadioAutoSelect);
        FrontEndMenuManager.SaveSettings();
        return;
    case 21:
        if (bEnterInput)
        {
            *bReturn = true;
            return;
        }

        if (nArrowsInput >= 0)
        {
            if (FrontEndMenuManager.field_0)
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

                FrontEndMenuManager.field_0 = true;
            }
        }
        else
        {
            if (FrontEndMenuManager.field_0)
            {
                if (FrontEndMenuManager.m_fStatsScrollSpeed != 0.0f)
                    FrontEndMenuManager.m_fStatsScrollSpeed = 0.0f;
                FrontEndMenuManager.field_0 = false;
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
            if (++FrontEndMenuManager.m_dwRadarMode > 2)
                FrontEndMenuManager.m_dwRadarMode = 0;
        }
        else
        {
            if (FrontEndMenuManager.m_dwRadarMode)
                --FrontEndMenuManager.m_dwRadarMode;
            else
                FrontEndMenuManager.m_dwRadarMode = 2;
        }
        FrontEndMenuManager.SaveSettings();
        return;
    case 3:
    case 4:
    case 5:
        FrontEndMenuManager.SwitchToNewScreen(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_dwSelectedMenuItem].m_nTargetMenu);
        return;
    case 11:
        // TODO: Do
        return;
    case 10:
        FrontEndMenuManager.ProcessMissionPackNewGame();
        return;
    case 13:
        if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_dwSelectedMenuItem].m_nType >= MENU_ENTRY_SAVE_1 && MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_dwSelectedMenuItem].m_nType <= MENU_ENTRY_SAVE_8)
        {
            FrontEndMenuManager.m_bSelectedSaveGame = FrontEndMenuManager.m_dwSelectedMenuItem - 1;
            if (FrontEndMenuManager.m_nCurrentMenuPage == 9)
            {
                if (FrontEndMobile.SlotValidation[FrontEndMenuManager.m_dwSelectedMenuItem] != 1 && FrontEndMobile.SlotValidation[FrontEndMenuManager.m_dwSelectedMenuItem] != 2)
                    FrontEndMenuManager.SwitchToNewScreen(11);
            }
            else if (FrontEndMenuManager.m_nCurrentMenuPage == 10)
            {
               if (FrontEndMobile.SlotValidation[FrontEndMenuManager.m_dwSelectedMenuItem] != 1)
                    FrontEndMenuManager.SwitchToNewScreen(12);
            }
        }
        return;
    case 18:
        if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_dwSelectedMenuItem].m_nType >= MENU_ENTRY_SAVE_1 && MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_dwSelectedMenuItem].m_nType <= MENU_ENTRY_SAVE_8)
        {
            FrontEndMenuManager.m_bSelectedSaveGame = FrontEndMenuManager.m_dwSelectedMenuItem - 1;
            FrontEndMenuManager.SwitchToNewScreen(17);
        }
        return;
    case 12:
        *(char*)0xB72910 = FrontEndMenuManager.field_160;
        FrontEndMenuManager.DoSettingsBeforeStartingAGame();
        return;
    case 14:
        *(char*)0xB72910 = 0;
        FrontEndMenuManager.DoSettingsBeforeStartingAGame();
        FrontEndMenuManager.m_bDontDrawFrontEnd = true;
        return;
    case 15:
        FrontEndMenuManager.m_bDontDrawFrontEnd = true;
        return;
    case 46:
        FrontEndMenuManager.bInvertMouseY = FrontEndMenuManager.bInvertMouseY == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 47:
        FrontEndMenuManager.invertPadX1 = FrontEndMenuManager.invertPadX1 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 48:
        FrontEndMenuManager.invertPadY1 = FrontEndMenuManager.invertPadY1 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 49:
        FrontEndMenuManager.invertPadX2 = FrontEndMenuManager.invertPadX2 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 50:
        FrontEndMenuManager.invertPadY2 = FrontEndMenuManager.invertPadY2 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 51:
        FrontEndMenuManager.swapPadAxis1 = FrontEndMenuManager.swapPadAxis1 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 52:
        FrontEndMenuManager.swapPadAxis2 = FrontEndMenuManager.swapPadAxis2 == false;
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
        FrontEndMenuManager.m_bFrameLimiterOn = FrontEndMenuManager.m_bFrameLimiterOn == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 64:
        FrontEndMenuManager.m_bTracksAutoScan = FrontEndMenuManager.m_bTracksAutoScan == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 65:
        FrontEndMenuManager.m_bSavePhotos = FrontEndMenuManager.m_bSavePhotos == false;
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
            if (FrontEndMenuManager.m_dwResolution != FrontEndMenuManager.m_dwAppliedResolution)
            {
                FrontEndMenuManager.m_dwAppliedResolution = FrontEndMenuManager.m_dwResolution;
                ((void(*)(int))0x745C70)(FrontEndMenuManager.m_dwAppliedResolution);

                FrontEndMenuManager.m_bDrawMouse = true;
                FrontEndMenuManager.SaveSettings();
            }
        }
        else
        {
            char** pVideoModes = ((char**(*)())0x745AF0)();
            int nNumVideoModes = RwEngineGetNumVideoModes();

            if (nArrowsInput > 0)
            {
                int		nCurrentVidMode = FrontEndMenuManager.m_dwResolution + 1;

                if (nCurrentVidMode >= nNumVideoModes)
                    nCurrentVidMode = 0;

                while (!pVideoModes[nCurrentVidMode])
                {
                    ++nCurrentVidMode;

                    if (nCurrentVidMode >= nNumVideoModes)
                        nCurrentVidMode = 0;
                }

                FrontEndMenuManager.m_dwResolution = nCurrentVidMode;
            }
            else
            {
                int nCurrentVidMode = FrontEndMenuManager.m_dwResolution - 1;

                if (nCurrentVidMode < 0)
                    nCurrentVidMode = nNumVideoModes - 1;

                while (!pVideoModes[nCurrentVidMode])
                {
                    --nCurrentVidMode;

                    if (nCurrentVidMode < 0)
                        nCurrentVidMode = nNumVideoModes - 1;
                }

                FrontEndMenuManager.m_dwResolution = nCurrentVidMode;
            }
        }
        return;
    case 44:
        if (bEnterInput)
        {
            if (FrontEndMenuManager.m_dwAntiAliasingLevel != FrontEndMenuManager.m_dwAppliedAntiAliasingLevel)
            {
                FrontEndMenuManager.m_dwAppliedAntiAliasingLevel = FrontEndMenuManager.m_dwAntiAliasingLevel;

                RwD3D9ChangeMultiSamplingLevels(FrontEndMenuManager.m_dwAppliedAntiAliasingLevel);
                ((void(*)(int))0x745C70)(FrontEndMenuManager.m_dwAppliedResolution);
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
                int nCurrentMode = FrontEndMenuManager.m_dwAntiAliasingLevel + 1;

                if (nCurrentMode > nNumMultiSamplingModes)
                    nCurrentMode = 1;

                FrontEndMenuManager.m_dwAntiAliasingLevel = nCurrentMode;
            }
            else
            {
                int nCurrentMode = FrontEndMenuManager.m_dwAntiAliasingLevel - 1;

                if (nCurrentMode <= 0)
                    nCurrentMode = nNumMultiSamplingModes;

                FrontEndMenuManager.m_dwAntiAliasingLevel = nCurrentMode;
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
            if (++FrontEndMenuManager.m_nRadioMode > 2)
                FrontEndMenuManager.m_nRadioMode = 0;
        }
        else
        {
            if (FrontEndMenuManager.m_nRadioMode)
                --FrontEndMenuManager.m_nRadioMode;
            else
                FrontEndMenuManager.m_nRadioMode = 2;
        }
        FrontEndMenuManager.SaveSettings();
        return;
    case 54:
        FrontEndMenuManager.m_bDontDrawFrontEnd = true;
        return;
    case 57:
        FrontEndMenuManager.SetDefaultPreferences((eMenuPage)MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[2].m_nTargetMenu);

        if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[2].m_nTargetMenu == 36)
            plugin::CallAndReturn<char, 0x531F20>();

        FrontEndMenuManager.SaveSettings();
        FrontEndMenuManager.SwitchToNewScreen(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[2].m_nTargetMenu);
        return;
    case 7:
        FrontEndMenuManager.SwitchToNewScreen(FrontEndMenuManager.m_nController == 1 ? 40 : 39);
        return;
    case 8:
        FrontEndMenuManager.field_B7 = false;
        FrontEndMenuManager.SwitchToNewScreen(38);
        FrontEndMenuManager.field_90 = 0;
        return;
    case 9:
        FrontEndMenuManager.field_B7 = true;
        FrontEndMenuManager.SwitchToNewScreen(38);
        FrontEndMenuManager.field_90 = 0;
        return;
    case 45:
        FrontEndMenuManager.field_1B14 = 1;
        FrontEndMenuManager.field_1B09 = 1;
        FrontEndMenuManager.field_1B08 = 1;
        FrontEndMenuManager.field_1B0C = FrontEndMenuManager.m_dwSelectedMenuItem;
        FrontEndMenuManager.field_F0 = FrontEndMenuManager.field_36[2];
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
        if (FrontEndMenuManager.m_nLanguage != 0)
        {
            FrontEndMenuManager.m_nLanguage = 0;
            FrontEndMenuManager.field_EB = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 38:
        if (FrontEndMenuManager.m_nLanguage != 1)
        {
            FrontEndMenuManager.m_nLanguage = 1;
            FrontEndMenuManager.field_EB = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 39:
        if (FrontEndMenuManager.m_nLanguage != 2)
        {
            FrontEndMenuManager.m_nLanguage = 2;
            FrontEndMenuManager.field_EB = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 40:
        if (FrontEndMenuManager.m_nLanguage != 3)
        {
            FrontEndMenuManager.m_nLanguage = 3;
            FrontEndMenuManager.field_EB = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 41:
        if (FrontEndMenuManager.m_nLanguage != 4)
        {
            FrontEndMenuManager.m_nLanguage = 4;
            FrontEndMenuManager.field_EB = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
        // Net
    case 100:
        return;
    }
}

void MobileFrontEnd::PrintRadioStationList()
{
    signed int v2 = 1;
    int savedAlpha;
    float fPosX = SCREEN_COORD_CENTER_X - SCREEN_COORD(282.5f / 2);
    float fPosY = SCREEN_COORD_CENTER_Y - SCREEN_COORD(-150.0f / 2);
    float spacing = SCREEN_COORD(0.625f);
    float size = SCREEN_MULTIPLIER(58.125f);

    do
    {
        if (FrontEndMenuManager.m_nRadioStation == v2) {
            RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));
            CSprite2d::DrawRect(CRect((fPosX - SCREEN_COORD(2.0f)) + (spacing), fPosY - SCREEN_COORD(2.0f), (fPosX - SCREEN_COORD(2.0f)) + (spacing) + (size + SCREEN_COORD(4.0f)), fPosY - SCREEN_COORD(2.0f) + (size + SCREEN_COORD(4.0f))), CRGBA(255, 255, 255, 100));
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
        }

        FrontEndMenuManager.m_apTextures[v2].Draw(CRect(fPosX + (spacing), fPosY, fPosX + (spacing) + (size), fPosY + (size)), CRGBA(255, 255, 255, FrontEndMenuManager.m_nRadioStation == v2 ? 255 : 50));

        if (FrontEndMenuManager.m_nRadioStation == v2) {
            RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));
            CSprite2d::DrawRect(CRect((fPosX - SCREEN_COORD(2.0f)) + (spacing), fPosY - SCREEN_COORD(2.0f), (fPosX - SCREEN_COORD(2.0f)) + (spacing) + (size + SCREEN_COORD(4.0f)), fPosY - SCREEN_COORD(2.0f) + (size + SCREEN_COORD(4.0f))), 
                CRGBA(255, 255, 255, 50), CRGBA(255, 255, 255, 50),
                CRGBA(255, 255, 255, 0), CRGBA(255, 255, 255, 0));
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
        }

        ++v2;
        spacing += (size);
    } while (v2 < 13);
}

void MobileFrontEnd::DisplaySlider(float x, float y, float width, float height, float progress) {
    // filled_texture
    DrawTexturedProgressBar(x, y, width, height, progress, 0);

    // percentage
    static char text[4];
    static float percentage;
    percentage = progress * 100.0f;
    sprintf(text, "%d%%", (int)percentage);

    CFont::SetWrapx(SCREEN_WIDTH);
    CFont::SetRightJustifyWrap(0.0f);
    CFont::SetOutlinePosition(0);
    CFont::SetFontStyle(FONT_SUBTITLES);
    CFont::SetScale(height * 0.026f * 900 / 720, height * 0.045f * 900 / 720);
    static float text_x;
    float fTextAlpha;
    float fTextAlpha2;

    if (percentage > 80.0f)
        fTextAlpha = 10.0f * 900 / 720 * (percentage);
    else
        fTextAlpha = 0.0f;

    if (percentage > 80.0f * 900 / 720)
        fTextAlpha2 = -10.0f * 900 / 720 * (percentage);
    else
        fTextAlpha2 = 200.0f * 900 / 720;

    CFont::SetAlignment(ALIGN_LEFT);
    CFont::SetDropColor(CRGBA(0, 0, 0, static_cast<BYTE>(fTextAlpha)));
    CFont::SetColor(CRGBA(0, 0, 0, static_cast<BYTE>(fTextAlpha)));
    CFont::PrintString(x + SCREEN_COORD(3.0f * 900 / 720), y, text);

    CFont::SetAlignment(ALIGN_RIGHT);
    CFont::SetDropColor(CRGBA(0, 0, 0, static_cast<BYTE>(fTextAlpha2)));
    CFont::SetColor(CRGBA(255, 255, 255, static_cast<BYTE>(fTextAlpha2)));
    CFont::PrintString(x + width - SCREEN_COORD(3.0f * 900 / 720), y, text);

    // white nub
    //mobileTex.m_nSliderSprite[2].Draw(SCREEN_COORD(14.0f * 900 / 720) + (x - SCREEN_COORD(20.0f * 900 / 720)) + (width - SCREEN_COORD(8.0f * 900 / 720)) * (progress), y - SCREEN_COORD(3.0f * 900 / 720), SCREEN_MULTIPLIER(20.0f * 900 / 720), SCREEN_MULTIPLIER(20.0f * 900 / 720), CRGBA(255, 255, 255, 255));
}

void MobileFrontEnd::DrawTexturedProgressBar(float x, float y, float width, float height, float progress, float deltaProgress)
{
    // progress value is 0.0 - 100.0
    if (progress >= 100.0f)
        progress = 100.0f;
    else {
        CSprite2d::DrawRect(CRect((int)(x)-0.5f, (int)(y)-0.5f, (int)(x + width) - 0.5f, (int)(y + height) - 0.5f),
            CRGBA(0, 0, 0, 200));
    }
    if (progress > 0.0f) {
        CSprite2d::DrawRect(CRect((int)(x)-0.5f, (int)(y)-0.5f, (int)(x + width * (progress)) - 0.5f,
            (int)(y + height) - 0.5f), CRGBA(153, 203, 153, 250));
        //mobileTex.menu_texture[15].Draw(CRect((x), (y), (x + (width) * (progress / 100.0f)), ((y) + (height))), CRGBA(255, 255, 255, 255));
    }
}

void MobileFrontEnd::DrawStatsSlider(float x, float y, unsigned short width, unsigned char height, float percentage, signed char,
    unsigned char, unsigned char, CRGBA, CRGBA)
{
    float progress = percentage / 100.0f;
    CSprite2d temporarySprite;
    // empty
    temporarySprite.m_pTexture = m_menuSliderTxd.GetTexture(MENU_SLIDER_EMPTY);
    temporarySprite.Draw(CRect(x, y, x + width, y + height), CRGBA(255, 255, 255, 255));
    // full
    temporarySprite.m_pTexture = m_menuSliderTxd.GetTexture(MENU_SLIDER_FULL);
    temporarySprite.Draw(CRect(x, y, x + width * progress, y + height), CRGBA(255, 255, 255, 255),
        0.0f, 1.0f, progress, 1.0f, 0.0f, 0.0f, progress, 0.0f);
    // nub
    //temporarySprite.m_pTexture = m_menuSliderTxd.GetTexture(MENU_SLIDER_NUB);
    //if (progress > 0.5f)
    //    temporarySprite.Draw(CRect(x, y, x + width, y + height), CRGBA(255, 255, 255, 255));
    //else
    //    temporarySprite.Draw(CRect(x, y, x + width, y + height), CRGBA(255, 255, 255, 255));
    temporarySprite.m_pTexture = nullptr;

    static char text[12];
    sprintf(text, "%d%%", static_cast<int>(percentage));
    CFont::SetWrapx(SCREEN_WIDTH);
    CFont::SetRightJustifyWrap(0.0f);
    CFont::SetOutlinePosition(0);
    CFont::SetFontStyle(FONT_SUBTITLES);
    CFont::SetScale(height * 0.035f, height * 0.05f);
    if (percentage < 90.0) {
        CFont::SetAlignment(ALIGN_RIGHT);
        CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
        CFont::PrintString(x + width, y, text);
    }
    if (percentage > 70.0f) {
        CFont::SetAlignment(ALIGN_LEFT);
        CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_BLACK, 255));
        CFont::PrintString(x, y, text);
    }
    CFont::SetFontStyle(FONT_MENU);
}