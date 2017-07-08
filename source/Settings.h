#pragma once
// plugin-sdk
#include <plugin.h>

// mobile-hud

class Settings {
public:
    bool      bEnableColors;
    bool      bEnablePlayerInfo;
    bool      bEnableRadar;
    bool      bEnableSubtitles;
    bool      bEnableRadioNames;
    bool      bEnableAreaNames;
    bool      bEnableVehicleNames;
    bool      bEnableStatsBox;
    bool      bEnableTextBox;
    bool      bEnableTimers;
    bool      bEnableProgressBars;
    bool      bEnableMenuSystem;
    bool      bEnableLoadingScreens;
    bool      bEnableMenuPages;
    bool      bEnableFrontends;

    bool      bRadarTop;
    CVector2D vecWeaponIconPosn;
    CVector2D vecWeaponIconScale;
    CVector2D vecWeaponAmmoPosn;
    CVector2D vecWeaponAmmoScale;
    CVector2D vecClockPosn;
    CVector2D vecClockScale;
    CVector2D vecMoneyPosn;
    CVector2D vecMoneyScale;
    CVector2D vecHealthPosn;
    CVector2D vecHealthScale;
    CVector2D vecArmorPosn;
    CVector2D vecArmorScale;
    CVector2D vecBreathPosn;
    CVector2D vecBreathScale;
    CVector2D vecWantedLevelPosn;
    CVector2D vecWantedLevelStarScale;
    float     fWantedLevelStarSpace;
    float     fSecondPlayerOffsetY;
    CVector2D vecRadarPosn;
    float     fRadarWidthHalf;
    float     fRadarHeightHalf;
    float     fRadarBorderWidthHalf;
    float     fRadarBorderHeightHalf;
    CVector2D vecPlaneRadarPosn;
    CVector2D vecPlaneRadarSize;
    CVector2D vecPlaneRadarLightPartPosn;
    CVector2D vecPlaneRadarLightPartSize;
    bool      bRadioNameTop;
    float     fRadioNameTopPosnY;
    CVector2D vecRadioNamePosn;
    CVector2D vecRadioNameScale;
    CVector2D vecTextBoxPosn;
    float     fTextBoxPosnXWithRadar;
    float     fTextBoxPosnXWithRadarAndPlane;
    CVector2D vecTextBoxFontScale;
    float     fTextBoxWidth;
    float     fTextBoxBorderSize;
    CVector2D vecTextBoxProgressBarSize;
    float     fTextBoxProgressBarYShift;
    float     fTextBoxWidthWithProgressBar;
    float     fTextBoxPlusMinTextXShift;
    CVector2D vecTextBoxTextPosnWhenMenuEnabled;
    float     fTextBoxHeightWhenMenuEnabled;
    bool      bMissionTimersTop;
    float     fMissionTimersTopPosnY;
    float     fMissionTimersBoxPosnX;
    float     fMissionTimersBoxPosnMinY;
    float     fMissionTimersBoxPosnMinY2P;
    CVector2D vecMissionTimersBoxSize;
    CVector2D vecMissionTimersTextScale;
    float     fMissionTimersTextMaxWidth;
    float     fMissionTimersTextOffsetY;
    float     fMissionTimersTextDescriptionOffsetX;
    float     fMissionTimersTextValueOffsetX;
    CVector2D vecMissionTimersProgressBarOffset;
    CVector2D vecMissionTimersProgressBarSize;

    float     fSubtitlesPosnY;
    float     fSubtitlesWidePosnY;
    CVector2D vecSubtitlesScale;
    CVector2D vecAreaNamePosn;
    CVector2D vecAreaNameScale;
    CVector2D vecVehicleNamePosn;
    CVector2D vecVehicleNameScale;

    CVector2D vecStatsBoxPosn;

    int       iReloadKey;

    void Read();
};

extern Settings settings;