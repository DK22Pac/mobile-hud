#include "Settings.h"
#include "plugin.h"

using namespace plugin;

Settings settings;

void Settings::Read() {
    config_file config(PLUGIN_PATH("MobileHud\\mobileHud.dat"));

    bEnableColors                         = config["ENABLE_COLORS"                          ].asBool(true);
    bEnablePlayerInfo                     = config["ENABLE_PLAYER_INFO"                     ].asBool(true);
    bEnableRadar                          = config["ENABLE_RADAR"                           ].asBool(true);
    bEnableSubtitles                      = config["ENABLE_SUBTITLES"                       ].asBool(true);
    bEnableRadioNames                     = config["ENABLE_RADIO_NAMES"                     ].asBool(true);
    bEnableAreaNames                      = config["ENABLE_AREA_NAMES"                      ].asBool(true);
    bEnableVehicleNames                   = config["ENABLE_VEHICLE_NAMES"                   ].asBool(true);
    bEnableStatsBox                       = config["ENABLE_STATS_BOX"                       ].asBool(true);
    bEnableTextBox                        = config["ENABLE_TEXT_BOX"                        ].asBool(true);
    bEnableTimers                         = config["ENABLE_TIMERS"                          ].asBool(true);
    bEnableProgressBars                   = config["ENABLE_PROGRESS_BARS"                   ].asBool(true);
    bEnableMenuSystem                     = config["ENABLE_MENU_SYSTEM"                     ].asBool(true);
    bEnableLoadingScreens                 = config["ENABLE_LOADING_SCREENS"                 ].asBool(true);
    bEnableMenuPages                      = config["ENABLE_MENU_PAGES"                      ].asBool(true);
    bEnableFrontends                      = config["ENABLE_FRONTEND"                        ].asBool(true);

    bRadarTop                             = config["RADAR_TOP"                              ].asBool(true);
    vecWeaponIconPosn                     = config["WEAPON_ICON_POSN"                       ].asVec2d(CVector2D(141.0f, 20.0f));
    vecWeaponIconScale                    = config["WEAPON_ICON_SCALE"                      ].asVec2d(CVector2D(124.0f, 124.0f));
    vecWeaponAmmoPosn                     = config["WEAPON_AMMO_POSN"                       ].asVec2d(CVector2D(79.0f, 132.0f));
    vecWeaponAmmoScale                    = config["WEAPON_AMMO_SCALE"                      ].asVec2d(CVector2D(0.85f, 1.6f));
    vecClockPosn                          = config["CLOCK_POSN"                             ].asVec2d(CVector2D(153.0f, 29.0f));
    vecClockScale                         = config["CLOCK_SCALE"                            ].asVec2d(CVector2D(1.0f, 1.9f));
    vecMoneyPosn                          = config["MONEY_POSN"                             ].asVec2d(CVector2D(153.0f, 66.0f));
    vecMoneyScale                         = config["MONEY_SCALE"                            ].asVec2d(CVector2D(0.9f, 1.7f));
    vecHealthPosn                         = config["HEALTH_POSN"                            ].asVec2d(CVector2D(156.0f, 106.0f));
    vecHealthScale                        = config["HEALTH_SCALE"                           ].asVec2d(CVector2D(170.0f, 13.0f));
    vecArmorPosn                          = config["ARMOR_POSN"                             ].asVec2d(CVector2D(156.0f, 127.0f));
    vecArmorScale                         = config["ARMOR_SCALE"                            ].asVec2d(CVector2D(170.0f, 13.0f));
    vecBreathPosn                         = config["BREATH_POSN"                            ].asVec2d(CVector2D(156.0f, 148.0f));
    vecBreathScale                        = config["BREATH_SCALE"                           ].asVec2d(CVector2D(170.0f, 13.0f));
    vecWantedLevelPosn                    = config["WANTED_LEVEL_POSN"                      ].asVec2d(CVector2D(18.0f, 162.0f));
    vecWantedLevelStarScale               = config["WANTED_LEVEL_STAR_SCALE"                ].asVec2d(CVector2D(1.2f, 2.3f));
    fWantedLevelStarSpace                 = config["WANTED_LEVEL_STAR_SPACE"                ].asFloat(46.0f);
    fSecondPlayerOffsetY                  = config["SECOND_PLAYER_OFFSET_Y"                 ].asFloat(190.0f);
    vecRadarPosn                          = config["RADAR_POSN"                             ].asVec2d(CVector2D(105.0f, 130.0f));
    fRadarWidthHalf                       = config["RADAR_WIDTH_HALF"                       ].asFloat(93.0f);
    fRadarHeightHalf                      = config["RADAR_HEIGHT_HALF"                      ].asFloat(93.0f);
    fRadarBorderWidthHalf                 = config["RADAR_BORDER_WIDTH_HALF"                ].asFloat(96.0f);
    fRadarBorderHeightHalf                = config["RADAR_BORDER_HEIGHT_HALF"               ].asFloat(96.0f);
    vecPlaneRadarPosn                     = config["PLANE_RADAR_POSN"                       ].asVec2d(CVector2D(222.0f, 67.0f));
    vecPlaneRadarSize                     = config["PLANE_RADAR_SIZE"                       ].asVec2d(CVector2D(14.0f, 145.0f));
    vecPlaneRadarLightPartPosn            = config["PLANE_RADAR_LIGHT_PART_POSN"            ].asVec2d(CVector2D(225.0f, 70.0f));
    vecPlaneRadarLightPartSize            = config["PLANE_RADAR_LIGHT_PART_SIZE"            ].asVec2d(CVector2D(8.0f, 139.0f));
    bRadioNameTop                         = config["RADIO_NAME_TOP"                         ].asBool(false);
    fRadioNameTopPosnY                    = config["RADIO_NAME_TOP_POSN_Y"                  ].asFloat(5.0f);
    vecRadioNamePosn                      = config["RADIO_NAME_POSN"                        ].asVec2d(CVector2D(20.0f, 37.0f));
    vecRadioNameScale                     = config["RADIO_NAME_SCALE"                       ].asVec2d(CVector2D(0.8f, 1.5f));
    vecTextBoxPosn                        = config["TEXT_BOX_POSN"                          ].asVec2d(CVector2D(25.0f, 40.0f));
    fTextBoxPosnXWithRadar                = config["TEXT_BOX_POSN_X_WITH_RADAR"             ].asFloat(231.0f);
    fTextBoxPosnXWithRadarAndPlane        = config["TEXT_BOX_POSN_X_WITH_RADAR_AND_PLANE"   ].asFloat(259.0f);
    vecTextBoxFontScale                   = config["TEXT_BOX_FONT_SCALE"                    ].asVec2d(CVector2D(0.7f, 1.5f));
    fTextBoxWidth                         = config["TEXT_BOX_WIDTH"                         ].asFloat(421.0f);
    fTextBoxBorderSize                    = config["TEXT_BOX_BORDER_SIZE"                   ].asFloat(-5.0f);
    vecTextBoxProgressBarSize             = config["TEXT_BOX_PROGRESS_BAR_SIZE"             ].asVec2d(CVector2D(140.0f, 20.0f));
    fTextBoxProgressBarYShift             = config["TEXT_BOX_PROGRESS_BAR_Y_SHIFT"          ].asFloat(3.0f);
    fTextBoxWidthWithProgressBar          = config["TEXT_BOX_WIDTH_WITH_PROGRESS_BAR"       ].asFloat(164.0f);
    fTextBoxPlusMinTextXShift             = config["TEXT_BOX_PLUS_MIN_TEXT_X_SHIFT"         ].asFloat(152.0f);
    vecTextBoxTextPosnWhenMenuEnabled     = config["TEXT_BOX_TEXT_POSN_WHEN_MENU_ENABLED"   ].asVec2d(CVector2D(18.0f, 10.0f));
    fTextBoxHeightWhenMenuEnabled         = config["TEXT_BOX_HEIGHT_WHEN_MENU_ENABLED"      ].asFloat(55.0f);
    bMissionTimersTop                     = config["MISSIONTIMERS_TOP"                      ].asBool(true);
    fMissionTimersTopPosnY                = config["MISSIONTIMERS_TOP_POSN_Y"               ].asFloat(36.0f);
    fMissionTimersBoxPosnX                = config["MISSIONTIMERS_BOX_POSN_X"               ].asFloat(20.0f);
    fMissionTimersBoxPosnMinY             = config["MISSIONTIMERS_BOX_POSN_MIN_Y"           ].asFloat(230.0f);
    fMissionTimersBoxPosnMinY2P           = config["MISSIONTIMERS_BOX_POSN_MIN_Y_2P"        ].asFloat(380.0f);
    vecMissionTimersBoxSize               = config["MISSIONTIMERS_BOX_SIZE"                 ].asVec2d(CVector2D(240.0f, 37.0f));
    vecMissionTimersTextScale             = config["MISSIONTIMERS_TEXT_SCALE"               ].asVec2d(CVector2D(0.7f, 1.3f));
    fMissionTimersTextMaxWidth            = config["MISSIONTIMERS_TEXT_MAX_WIDTH"           ].asFloat(128.0f);
    fMissionTimersTextOffsetY             = config["MISSIONTIMERS_TEXT_OFFSET_Y"            ].asFloat(6.0f);
    fMissionTimersTextDescriptionOffsetX  = config["MISSIONTIMERS_TEXT_DESCRIPTION_OFFSET_X"].asFloat(8.0f);
    fMissionTimersTextValueOffsetX        = config["MISSIONTIMERS_TEXT_VALUE_OFFSET_X"      ].asFloat(8.0f);
    vecMissionTimersProgressBarOffset     = config["MISSIONTIMERS_PROGRESSBAR_OFFSET"       ].asVec2d(CVector2D(6.0f, 11.0f));
    vecMissionTimersProgressBarSize       = config["MISSIONTIMERS_PROGRESSBAR_SIZE"         ].asVec2d(CVector2D(92.0f, 18.0f));
    fSubtitlesPosnY                       = config["SUBTITLES_POSN_Y"                       ].asFloat(60.0f);
    fSubtitlesWidePosnY                   = config["SUBTITLES_WIDESCREEN_POSN_Y"            ].asFloat(5.0f);
    vecSubtitlesScale                     = config["SUBTITLES_SCALE"                        ].asVec2d(CVector2D(1.0f, 1.9f));
    vecAreaNamePosn                       = config["AREA_NAME_POSN"                         ].asVec2d(CVector2D(25.0f, 50.0f));
    vecAreaNameScale                      = config["AREA_NAME_SCALE"                        ].asVec2d(CVector2D(1.1f, 2.1f));
    vecVehicleNamePosn                    = config["VEHICLE_NAME_POSN"                      ].asVec2d(CVector2D(25.0f, 40.0f));
    vecVehicleNameScale                   = config["VEHICLE_NAME_SCALE"                     ].asVec2d(CVector2D(0.8f, 1.6f));
    vecStatsBoxPosn                       = config["STATS_BOX_POSN"                         ].asVec2d(CVector2D(10.0f, 10.0f));

    iReloadKey                            = config["RELOAD_SETTINGS"                        ].asBool(false);
    
    if(iReloadKey)
        iReloadKey = config["RELOAD_SETTINGS"].asInt(-1);
}
