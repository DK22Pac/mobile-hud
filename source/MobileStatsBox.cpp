#include "plugin.h"
#include "common.h"
#include "CClock.h"
#include "CFont.h"
#include "CHudColours.h"
#include "CMenuManager.h"
#include "CPad.h"
#include "CSprite2d.h"
#include "CStats.h"
#include "CText.h"
#include "MobileStatsBox.h"
#include "Settings.h"
#include "Utility.h"

using namespace plugin;

void MobileStatsBox::InstallPatches() {
    patch::Set<BYTE>(0x58FC2C, 0xEB);
    Events::drawHudEvent += DrawVitalStats;
}

void __cdecl MobileStatsBox::DrawVitalStats() {
    int CURWSKL;
    int CURWSKL_ALPHA;
    CPed *player = FindPlayerPed(-1);
    CPad *pad = CPad::GetPad(0);

    switch (CWeaponInfo::GetWeaponInfo((eWeaponType)player->m_aWeapons[player->m_nActiveWeaponSlot].m_nType, 1)->m_nModelId1) {
    case MODEL_COLT45:
        CURWSKL = 69;
        CURWSKL_ALPHA = 255;
        break;
    case MODEL_SILENCED:
        CURWSKL = 70;
        CURWSKL_ALPHA = 255;
        break;
    case MODEL_DESERT_EAGLE:
        CURWSKL = 71;
        CURWSKL_ALPHA = 255;
        break;
    case MODEL_CHROMEGUN:
        CURWSKL = 72;
        CURWSKL_ALPHA = 255;
        break;
    case MODEL_SAWNOFF:
        CURWSKL = 73;
        CURWSKL_ALPHA = 255;
        break;
    case MODEL_SHOTGSPA:
        CURWSKL = 74;
        CURWSKL_ALPHA = 255;
        break;
    case MODEL_MICRO_UZI:
        CURWSKL = 75;
        CURWSKL_ALPHA = 255;
        break;
    case MODEL_MP5LNG:
        CURWSKL = 76;
        CURWSKL_ALPHA = 255;
        break;
    case MODEL_AK47:
        CURWSKL = 77;
        CURWSKL_ALPHA = 255;
        break;
    case MODEL_M4:
        CURWSKL = 78;
        CURWSKL_ALPHA = 255;
        break;
    case MODEL_SNIPER:
        CURWSKL = 79;
        CURWSKL_ALPHA = 255;
        break;
    default:
        CURWSKL = -1;
        CURWSKL_ALPHA = 50;
        break;
    }

    CVector2D vecStatsBoxScale;
    vecStatsBoxScale.x = 260.0f;
    vecStatsBoxScale.y = 255.0f;

    if (!pad->GetDisplayVitalStats(player) || FindPlayerVehicle(-1, 0)) {
        // Set Statsbox is closed
        settings.IsStatsBoxOpen = 0;
    }
    else {
        // Set Statsbox is open
        settings.IsStatsBoxOpen = 1;

        // Window
        DrawRect(SCREEN_COORD(settings.vecStatsBoxPosn.x), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y), SCREEN_MULTIPLIER(vecStatsBoxScale.x), SCREEN_MULTIPLIER(vecStatsBoxScale.y), 1, CRGBA(0, 0, 0, 130));

        // Header
        CFont::SetProportional(true);
        CFont::SetOrientation(ALIGN_LEFT);
        CFont::SetFontStyle(FONT_GOTHIC);
        CFont::SetEdge(2);
        CFont::SetScale(SCREEN_MULTIPLIER(1.7f), SCREEN_MULTIPLIER(2.9f));
        float width = CFont::GetStringWidth(TheText.Get("FEH_STA"), true, false);
        if (width > SCREEN_MULTIPLIER(225.0f))
            CFont::SetScale(SCREEN_MULTIPLIER(1.7f * SCREEN_MULTIPLIER(225.0f) / width), SCREEN_MULTIPLIER(2.9f));
        CFont::SetColor(CRGBA(255, 255, 255, 225));
        CFont::SetDropColor(CRGBA(0, 0, 0, 255));
        CFont::PrintString(SCREEN_COORD(settings.vecStatsBoxPosn.x + 15.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y + 35.0f), TheText.Get("FEH_STA"));

        // Stats
        CFont::SetOrientation(ALIGN_LEFT);
        CFont::SetFontStyle(FONT_MENU);
        CFont::SetEdge(0);

        // RESPECT_TOTAL
        CFont::SetColor(CRGBA(255, 255, 255, 255));
        CFont::SetScale(SCREEN_MULTIPLIER(0.50f), SCREEN_MULTIPLIER(1.2f));
        CFont::PrintString(SCREEN_COORD(settings.vecStatsBoxPosn.x + 10.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 20.0f), TheText.Get("STAT068"));
        CSprite2d::DrawBarChart(SCREEN_COORD(settings.vecStatsBoxPosn.x + vecStatsBoxScale.x - 110.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 25.0f), SCREEN_MULTIPLIER(100.0f), SCREEN_MULTIPLIER(15.0f), CStats::GetStatValue(64) * 0.001 * 100.0, 0, 0, 0, HudColour.GetRGB(HUD_COLOUR_WHITE, 255), HudColour.GetRGB(HUD_COLOUR_WHITE, 255));

        // UNDERWATER_STAMINA
        CFont::SetColor(CRGBA(255, 255, 255, 255));
        CFont::SetScale(SCREEN_MULTIPLIER(0.35f), SCREEN_MULTIPLIER(1.2f));
        CFont::PrintString(SCREEN_COORD(settings.vecStatsBoxPosn.x + 10.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 20.0f - 30.0f), TheText.Get("STAT225"));
        CSprite2d::DrawBarChart(SCREEN_COORD(settings.vecStatsBoxPosn.x + vecStatsBoxScale.x - 110.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 25.0f - 30.0f), SCREEN_MULTIPLIER(100.0f), SCREEN_MULTIPLIER(15.0f), CStats::GetStatValue(225) * 0.001 * 100.0, 0, 0, 0, HudColour.GetRGB(HUD_COLOUR_WHITE, 255), HudColour.GetRGB(HUD_COLOUR_WHITE, 255));

        // WEAPON_SKILLS
        CFont::SetColor(CRGBA(255, 255, 255, CURWSKL_ALPHA));
        CFont::SetScale(SCREEN_MULTIPLIER(0.40f), SCREEN_MULTIPLIER(1.2f));
        CFont::PrintString(SCREEN_COORD(settings.vecStatsBoxPosn.x + 10.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 20.0f - 60.0f), TheText.Get("CURWSKL"));
        CSprite2d::DrawBarChart(SCREEN_COORD(settings.vecStatsBoxPosn.x + vecStatsBoxScale.x - 110.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 25.0f - 60.0f), SCREEN_MULTIPLIER(100.0f), SCREEN_MULTIPLIER(15.0f), CStats::GetStatValue(CURWSKL) * 0.001 * 100.0, 0, 0, 0, HudColour.GetRGB(HUD_COLOUR_WHITE, CURWSKL_ALPHA), HudColour.GetRGB(HUD_COLOUR_WHITE, CURWSKL_ALPHA));

        // STAMINA
        CFont::SetColor(CRGBA(255, 255, 255, 255));
        CFont::SetScale(SCREEN_MULTIPLIER(0.50f), SCREEN_MULTIPLIER(1.2f));
        CFont::PrintString(SCREEN_COORD(settings.vecStatsBoxPosn.x + 10.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 20.0f - 90.0f), TheText.Get("STAT022"));
        CSprite2d::DrawBarChart(SCREEN_COORD(settings.vecStatsBoxPosn.x + vecStatsBoxScale.x - 110.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 25.0f - 90.0f), SCREEN_MULTIPLIER(100.0f), SCREEN_MULTIPLIER(15.0f), CStats::GetStatValue(22) * 0.001 * 100.0, 0, 0, 0, HudColour.GetRGB(HUD_COLOUR_WHITE, 255), HudColour.GetRGB(HUD_COLOUR_WHITE, 255));

        // BODY_MUSCLE
        CFont::SetColor(CRGBA(255, 255, 255, 255));
        CFont::SetScale(SCREEN_MULTIPLIER(0.40f), SCREEN_MULTIPLIER(1.2f));
        CFont::PrintString(SCREEN_COORD(settings.vecStatsBoxPosn.x + 10.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 20.0f - 120.0f), TheText.Get("STAT023"));
        CSprite2d::DrawBarChart(SCREEN_COORD(settings.vecStatsBoxPosn.x + vecStatsBoxScale.x - 110.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 25.0f - 120.0f), SCREEN_MULTIPLIER(100.0f), SCREEN_MULTIPLIER(15.0f), CStats::GetStatValue(23) * 0.001 * 100.0, 0, 0, 0, HudColour.GetRGB(HUD_COLOUR_WHITE, 255), HudColour.GetRGB(HUD_COLOUR_WHITE, 255));

        // FAT
        CFont::SetColor(CRGBA(255, 255, 255, 255));
        CFont::SetScale(SCREEN_MULTIPLIER(0.50f), SCREEN_MULTIPLIER(1.2f));
        CFont::PrintString(SCREEN_COORD(settings.vecStatsBoxPosn.x + 10.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 20.0f - 150.0f), TheText.Get("STAT021"));
        CSprite2d::DrawBarChart(SCREEN_COORD(settings.vecStatsBoxPosn.x + vecStatsBoxScale.x - 110.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 25.0f - 150.0f), SCREEN_MULTIPLIER(100.0f), SCREEN_MULTIPLIER(15.0f), CStats::GetStatValue(21) * 0.001 * 100.0, 0, 0, 0, HudColour.GetRGB(HUD_COLOUR_WHITE, 255), HudColour.GetRGB(HUD_COLOUR_WHITE, 255));

        // SEX_APPEAL
        CFont::SetColor(CRGBA(255, 255, 255, 255));
        CFont::SetScale(SCREEN_MULTIPLIER(0.40f), SCREEN_MULTIPLIER(1.2f));
        CFont::PrintString(SCREEN_COORD(settings.vecStatsBoxPosn.x + 10.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 20.0f - 180.0f), TheText.Get("STAT025"));
        CSprite2d::DrawBarChart(SCREEN_COORD(settings.vecStatsBoxPosn.x + vecStatsBoxScale.x - 110.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 25.0f - 180.0f), SCREEN_MULTIPLIER(100.0f), SCREEN_MULTIPLIER(15.0f), CStats::GetStatValue(25) * 0.001 * 100.0, 0, 0, 0, HudColour.GetRGB(HUD_COLOUR_WHITE, 255), HudColour.GetRGB(HUD_COLOUR_WHITE, 255));

        // DAY
        CFont::SetOrientation(ALIGN_RIGHT);
        CFont::SetFontStyle(FONT_PRICEDOWN);
        CFont::SetColor(CRGBA(255, 255, 255, 255));
        CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.3f));
        sprintf(gString, "DAY_%d", CClock::CurrentDay);
        CFont::PrintString(SCREEN_COORD(settings.vecStatsBoxPosn.x + vecStatsBoxScale.x - 10.0f), SCREEN_COORD_BOTTOM(settings.vecStatsBoxPosn.y + vecStatsBoxScale.y - 20.0f - 205.0f), TheText.Get(gString));
    }
}

void MobileStatsBox::DrawRect(CRect const& rect, bool bFading, CRGBA const& color) {
    unsigned int savedShade;
    unsigned int savedAlpha;
    RwRenderStateGet(rwRENDERSTATESHADEMODE, &savedShade);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void *>(rwSHADEMODEGOURAUD));
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));
    if (bFading)
        CSprite2d::DrawRect(CRect(BilinearOffset(rect.left), BilinearOffset(rect.bottom),
            BilinearOffset(rect.right), BilinearOffset(rect.top)),
            color.ToRGB(), color, color.ToRGB(), color);
    else
        CSprite2d::DrawRect(CRect(BilinearOffset(rect.left), BilinearOffset(rect.bottom),
            BilinearOffset(rect.right), BilinearOffset(rect.top)), color);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void *>(savedShade));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
}
