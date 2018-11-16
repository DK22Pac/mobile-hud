#include "MobileMissionTimers.h"
#include "Settings.h"
#include "Utility.h"
#include "plugin.h"
#include "CWorld.h"
#include "CHud.h"
#include "CFont.h"
#include "CUserDisplay.h"
#include "CGarages.h"
#include "CTimer.h"
#include "CText.h"
#include "CHudColours.h"

using namespace plugin;

void MobileMissionTimers::InstallPatches() {
    patch::RedirectCall(0x58FBEE, MyDrawMissionTimers);
}

void MobileMissionTimers::MyDrawMissionTimers() {
    if ((!CHud::m_BigMessage[4][0] || CHud::bScriptForceDisplayWithCounters) && !CGarages::MessageIDString[0]) {
        unsigned int savedShade;
        unsigned int savedAlpha;
        RwRenderStateGet(rwRENDERSTATESHADEMODE, &savedShade);
        RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void *>(rwSHADEMODEGOURAUD));
        RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));
        float baseY = 0.0f;
        if (!settings.bMissionTimersTop) {
            baseY = SCREEN_COORD_CENTER_Y - SCREEN_COORD(settings.vecMissionTimersBoxSize.y * 5) - 4;
            float compValue = SCREEN_COORD(settings.fMissionTimersBoxPosnMinY);
            if (CWorld::Players[1].m_pPed)
                compValue = SCREEN_COORD(settings.fMissionTimersBoxPosnMinY2P);
            if (baseY < compValue)
                baseY = compValue;
        }
        else
            baseY = SCREEN_COORD(settings.fMissionTimersTopPosnY);
        CFont::SetProportional(true);
        CFont::SetBackground(false, false);
        CFont::SetRightJustifyWrap(0.0);
        CFont::SetFontStyle(FONT_MENU);
        CFont::SetWrapx(SCREEN_WIDTH);
        if (CWorld::Players[1].m_pPed && !CUserDisplay::OnscnTimer.m_Clock.m_bEnabled)
            TimerMainCounterWasDisplayed = 0;
        for (int i = 0; i < 4; ++i) {
            if (!CUserDisplay::OnscnTimer.m_aCounters[i].m_bEnabled)
                TimerCounterWasDisplayed[i] = 0;
        }
        if (CUserDisplay::OnscnTimer.m_bDisplay == 1) {
            if (CUserDisplay::OnscnTimer.m_Clock.m_bEnabled == 1) { // Draw Clock
                short timerState = TimerMainCounterHideState;
                if (!TimerMainCounterWasDisplayed) {
                    timerState = 1;
                    TimerMainCounterHideState = 1;
                }
                TimerMainCounterWasDisplayed = 1;
                if (timerState) {
                    TimerMainCounterHideState++;
                    if (TimerMainCounterHideState > 20)
                        TimerMainCounterHideState = 0;
                }
                float alpha = 1.0f;
                if (TimerMainCounterHideState > 0)
                    alpha = static_cast<float>(TimerMainCounterHideState) / 20.0f;
                float x1, x2;
                if (settings.bMissionTimersTop) {
                    x1 = SCREEN_COORD_CENTER_LEFT(settings.vecMissionTimersBoxSize.x / 2.0f);
                    x2 = SCREEN_COORD_CENTER_RIGHT(settings.vecMissionTimersBoxSize.x / 2.0f);
                }
                else {
                    x1 = SCREEN_COORD_RIGHT(settings.fMissionTimersBoxPosnX + settings.vecMissionTimersBoxSize.x);
                    x2 = SCREEN_COORD_RIGHT(settings.fMissionTimersBoxPosnX);
                }
                CSprite2d::DrawRect(CRect(BilinearOffset(x1), BilinearOffset(baseY), BilinearOffset(x2),
                    BilinearOffset(baseY + SCREEN_COORD(settings.vecMissionTimersBoxSize.y))),
                    CRGBA(0, 0, 0, alpha * 130), CRGBA(0, 0, 0, alpha * 130), CRGBA(0, 0, 0, alpha * 255), CRGBA(0, 0, 0, alpha * 255));
                CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_BLUELIGHT, alpha * 255));
                CFont::SetEdge(1);
                CFont::SetDropColor(CRGBA(0, 0, 0, alpha * 255));
                CFont::SetOrientation(ALIGN_RIGHT);
                CFont::SetScale(SCREEN_MULTIPLIER(settings.vecMissionTimersTextScale.x), SCREEN_MULTIPLIER(settings.vecMissionTimersTextScale.y));
                if (settings.bMissionTimersTop)
                    x1 = SCREEN_COORD_CENTER_RIGHT(settings.vecMissionTimersBoxSize.x / 2.0f - settings.fMissionTimersTextValueOffsetX);
                else
                    x1 = SCREEN_COORD_RIGHT(settings.fMissionTimersBoxPosnX + settings.fMissionTimersTextValueOffsetX);
                CFont::PrintString(x1, baseY + SCREEN_COORD(settings.fMissionTimersTextOffsetY), CUserDisplay::OnscnTimer.m_Clock.m_szDisplayedText);
                if (CUserDisplay::OnscnTimer.m_Clock.m_szDescriptionTextKey[0]) {
                    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, alpha * 255));
                    CFont::SetEdge(0);
                    CFont::SetOrientation(ALIGN_LEFT);
                    CFont::SetScale(SCREEN_MULTIPLIER(settings.vecMissionTimersTextScale.x), SCREEN_MULTIPLIER(settings.vecMissionTimersTextScale.y));
                    float width = CFont::GetStringWidth(TheText.Get(CUserDisplay::OnscnTimer.m_Clock.m_szDescriptionTextKey), true, false);
                    if (width > SCREEN_COORD(settings.fMissionTimersTextMaxWidth))
                        CFont::SetScale(SCREEN_MULTIPLIER(settings.vecMissionTimersTextScale.x * SCREEN_COORD(settings.fMissionTimersTextMaxWidth) / width), SCREEN_MULTIPLIER(settings.vecMissionTimersTextScale.y));
                    if (settings.bMissionTimersTop)
                        x1 = SCREEN_COORD_CENTER_LEFT(settings.vecMissionTimersBoxSize.x / 2.0f - settings.fMissionTimersTextDescriptionOffsetX);
                    else
                        x1 = SCREEN_COORD_RIGHT(settings.fMissionTimersBoxPosnX + settings.vecMissionTimersBoxSize.x - settings.fMissionTimersTextDescriptionOffsetX);
                    CFont::PrintString(x1, baseY + SCREEN_COORD(settings.fMissionTimersTextOffsetY),
                        TheText.Get(CUserDisplay::OnscnTimer.m_Clock.m_szDescriptionTextKey));
                }
                baseY += SCREEN_COORD(settings.vecMissionTimersBoxSize.y);
            }
            for (int i = 0; i < 4; ++i) { // Draw counters
                if (CUserDisplay::OnscnTimer.m_aCounters[i].m_bEnabled == 1) {
                    if (!TimerCounterWasDisplayed[i])
                        TimerCounterHideState[i] = 1;
                    TimerCounterWasDisplayed[i] = 1;
                    if (TimerCounterHideState[i] != 0) {
                        TimerCounterHideState[i]++;
                        if (TimerCounterHideState[i] > 20)
                            TimerCounterHideState[i] = 0;
                    }
                    float alpha = 1.0f;
                    if (TimerCounterHideState[i] > 0)
                        alpha = static_cast<float>(TimerCounterHideState[i]) / 20.0f;
                    float boxY = settings.vecMissionTimersBoxSize.y * i;
                    float x1, x2;
                    if (settings.bMissionTimersTop) {
                        x1 = SCREEN_COORD_CENTER_LEFT(settings.vecMissionTimersBoxSize.x / 2.0f);
                        x2 = SCREEN_COORD_CENTER_RIGHT(settings.vecMissionTimersBoxSize.x / 2.0f);
                    }
                    else {
                        x1 = SCREEN_COORD_RIGHT(settings.fMissionTimersBoxPosnX + settings.vecMissionTimersBoxSize.x);
                        x2 = SCREEN_COORD_RIGHT(settings.fMissionTimersBoxPosnX);
                    }
                    CSprite2d::DrawRect(CRect(BilinearOffset(x1), BilinearOffset(baseY + SCREEN_COORD(boxY) + i + 1), BilinearOffset(x2),
                        BilinearOffset(baseY + SCREEN_COORD(boxY + settings.vecMissionTimersBoxSize.y) + i + 1)),
                        CRGBA(0, 0, 0, alpha * 130), CRGBA(0, 0, 0, alpha * 130), CRGBA(0, 0, 0, alpha * 255), CRGBA(0, 0, 0, alpha * 255));
                    if (CUserDisplay::OnscnTimer.m_aCounters[i].m_nType == 1) {
                        if (settings.bMissionTimersTop)
                            x1 = SCREEN_COORD_CENTER_RIGHT(settings.vecMissionTimersBoxSize.x / 2.0f - settings.vecMissionTimersProgressBarOffset.x - settings.vecMissionTimersProgressBarSize.x);
                        else
                            x1 = SCREEN_COORD_RIGHT(settings.fMissionTimersBoxPosnX + settings.vecMissionTimersProgressBarOffset.x + settings.vecMissionTimersProgressBarSize.x);
                        CSprite2d::DrawBarChart(x1, baseY + SCREEN_COORD(boxY + settings.vecMissionTimersProgressBarOffset.y) + i + 1,
                            SCREEN_COORD(settings.vecMissionTimersProgressBarSize.x), SCREEN_COORD(settings.vecMissionTimersProgressBarSize.y),
                            static_cast<float>(atoi(CUserDisplay::OnscnTimer.m_aCounters[i].m_szDisplayedText)), 0, 0, 1,
                            HudColour.GetRGB(CUserDisplay::OnscnTimer.m_aCounters[i].m_nColourId, alpha * 255), CRGBA(0, 0, 0, 0));
                    }
                    else {
                        CFont::SetColor(HudColour.GetRGB(CUserDisplay::OnscnTimer.m_aCounters[i].m_nColourId, alpha * 255));
                        CFont::SetEdge(1);
                        CFont::SetDropColor(CRGBA(0, 0, 0, alpha * 255));
                        CFont::SetOrientation(ALIGN_RIGHT);
                        CFont::SetScale(SCREEN_MULTIPLIER(settings.vecMissionTimersTextScale.x), SCREEN_MULTIPLIER(settings.vecMissionTimersTextScale.y));
                        if (settings.bMissionTimersTop)
                            x1 = SCREEN_COORD_CENTER_RIGHT(settings.vecMissionTimersBoxSize.x / 2.0f - settings.fMissionTimersTextValueOffsetX);
                        else
                            x1 = SCREEN_COORD_RIGHT(settings.fMissionTimersBoxPosnX + settings.fMissionTimersTextValueOffsetX);
                        CFont::PrintString(x1, baseY + SCREEN_COORD(boxY + settings.fMissionTimersTextOffsetY) + i + 1,
                            CUserDisplay::OnscnTimer.m_aCounters[i].m_szDisplayedText);
                    }
                    if (CUserDisplay::OnscnTimer.m_aCounters[i].m_szDescriptionTextKey) {
                        CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, alpha * 255));
                        CFont::SetEdge(0);
                        CFont::SetOrientation(ALIGN_LEFT);
                        CFont::SetScale(SCREEN_MULTIPLIER(settings.vecMissionTimersTextScale.x), SCREEN_MULTIPLIER(settings.vecMissionTimersTextScale.y));
                        float width = CFont::GetStringWidth(TheText.Get(CUserDisplay::OnscnTimer.m_aCounters[i].m_szDescriptionTextKey), true, false);
                        if (width > SCREEN_COORD(settings.fMissionTimersTextMaxWidth)) {
                            float multiplier = SCREEN_COORD(settings.fMissionTimersTextMaxWidth) / width;
                            CFont::SetScale(SCREEN_MULTIPLIER(settings.vecMissionTimersTextScale.x * multiplier), SCREEN_MULTIPLIER(settings.vecMissionTimersTextScale.y));
                        }
                        if (settings.bMissionTimersTop)
                            x1 = SCREEN_COORD_CENTER_LEFT(settings.vecMissionTimersBoxSize.x / 2.0f - settings.fMissionTimersTextDescriptionOffsetX);
                        else
                            x1 = SCREEN_COORD_RIGHT(settings.fMissionTimersBoxPosnX + settings.vecMissionTimersBoxSize.x - settings.fMissionTimersTextDescriptionOffsetX);
                        CFont::PrintString(x1, baseY + SCREEN_COORD(boxY + settings.fMissionTimersTextOffsetY) + i + 1,
                            TheText.Get(CUserDisplay::OnscnTimer.m_aCounters[i].m_szDescriptionTextKey));
                    }
                }
            }
        }
        RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void *>(savedShade));
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
    }
}
