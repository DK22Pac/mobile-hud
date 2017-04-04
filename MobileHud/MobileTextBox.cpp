#include "MobileTextBox.h"
#include "Utility.h"
#include "Settings.h"
#include "plugin.h"
#include "game_sa\CFont.h"
#include "game_sa\CMessages.h"
#include "game_sa\CText.h"
#include "game_sa\common.h"
#include "game_sa\CSprite2d.h"
#include "game_sa\CTimer.h"
#include "game_sa\CHudColours.h"
#include "game_sa\CMenuManager.h"
#include "game_sa\CHud.h"
#include "game_sa\CCamera.h"
#include "game_sa\CCutsceneMgr.h"
#include "game_sa\CGarages.h"

void MobileTextBox::InstallPatches() {
	plugin::patch::RedirectCall(0x573EF4, MyHelpBox_DrawBox);
	plugin::patch::RedirectCall(0x71A7EE, MyHelpBox_DrawBox);
	plugin::patch::RedirectCall(0x58FCFA, MyHelpBox_Draw);
}

void MobileTextBox::MyHelpBox_DrawBox(CRect const& rect, CRGBA const& color) {
	unsigned int savedShade;
	unsigned int savedAlpha;
	RwRenderStateGet(rwRENDERSTATESHADEMODE, &savedShade);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void *>(rwSHADEMODEGOURAUD));
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));
	CSprite2d::DrawRect(CRect(BilinearOffset(rect.m_fLeft - settings.fTextBoxBorderSize), BilinearOffset(rect.m_fBottom - settings.fTextBoxBorderSize),
		BilinearOffset(rect.m_fRight + settings.fTextBoxBorderSize), BilinearOffset(rect.m_fTop + settings.fTextBoxBorderSize)),
		CRGBA(color.red, color.green, color.blue, 130), CRGBA(color.red, color.green, color.blue, 130), 
		CRGBA(color.red, color.green, color.blue, 255), CRGBA(color.red, color.green, color.blue, 255));
	RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void *>(savedShade));
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
}

float MobileTextBox::GetHelpBoxXShift() {
	if(settings.bRadarTop && FrontEndMenuManager.drawRadarOrMap != 2) {
        CVehicle *vehicle = FindPlayerVehicle(-1, 0);
		if(vehicle && vehicle->m_wModelIndex != MODEL_VORTEX && (vehicle->m_dwVehicleSubClass == VEHICLE_PLANE || vehicle->m_dwVehicleSubClass == VEHICLE_HELI))
			return settings.fTextBoxPosnXWithRadarAndPlane;
		else if(FindPlayerPed(-1) && FindPlayerPed(-1)->m_aWeapons[FindPlayerPed(-1)->m_nActiveWeaponSlot].m_Type == WEAPON_PARACHUTE)
			return settings.fTextBoxPosnXWithRadarAndPlane;
		else return settings.fTextBoxPosnXWithRadar;
	}
	else return settings.vecTextBoxPosn.x;
}

void MobileTextBox::MyHelpBox_Draw() {
	if(CHud::m_pHelpMessage[0]) {
		if(!CMessages::StringCompare(CHud::m_pHelpMessage, CHud::m_pLastHelpMessage, 400)) {
			switch (CHud::m_nHelpMessageState) {
			case 0: // STATE_FREE_TO_USE
                CHud::m_nHelpMessageState = 2; // STATE_FADE_OUT
                CHud::m_nHelpMessageTimer = 0;
                CHud::m_nHelpMessageFadeTimer = 0;
				CMessages::StringCopy(CHud::m_pHelpMessageToPrint, CHud::m_pHelpMessage, 400);
				CFont::SetAlignment(ALIGN_LEFT);
				CFont::SetJustify(false);
				CFont::SetWrapx(SCREEN_COORD(GetHelpBoxXShift() + settings.fTextBoxWidth - settings.fTextBoxBorderSize) - 4.0f);
				CFont::SetFontStyle(FONT_SUBTITLES);
				CFont::SetBackground(true, true);
				CFont::SetDropShadowPosition(0);
                CFont::SetScale(SCREEN_MULTIPLIER(settings.vecTextBoxFontScale.x), SCREEN_MULTIPLIER(settings.vecTextBoxFontScale.y));
                CHud::m_fHelpMessageNumLines = CFont::GetNumberLinesNoPrint(SCREEN_COORD(GetHelpBoxXShift() + settings.fTextBoxBorderSize) + 4.0f,
                    SCREEN_COORD(settings.vecTextBoxPosn.y), CHud::m_pHelpMessageToPrint) + 3;
				CFont::SetWrapx(SCREEN_WIDTH);
                plugin::CallMethod<0x506EA0>(0xB6BC90, 32, 0.0f, 1.0f);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
                CHud::m_nHelpMessageState = 4; // STATE_REPLACE
                CHud::m_nHelpMessageTimer = 5;
				break;
			default:
				break;
			}
			CMessages::StringCopy(CHud::m_pLastHelpMessage, CHud::m_pHelpMessage, 400);
		}
		float alpha = 200.0f;
		if(CHud::m_nHelpMessageState) {
			switch(CHud::m_nHelpMessageState) {
			case 2: // STATE_FADE_OUT
				if(!TheCamera.m_bWideScreenOn) {
                    CHud::m_nHelpMessageFadeTimer += 2 * (CTimer::ms_fTimeStep * 0.02f * 1000.0f);
					if(CHud::m_nHelpMessageFadeTimer > 0) {
                        CHud::m_nHelpMessageFadeTimer = 0;
                        CHud::m_nHelpMessageState = 1; // STATE_IDLE
					}
					alpha = CHud::m_nHelpMessageFadeTimer * 0.001f * 200.0f;
				}
				break;
			case 3: // STATE_FADE_IN
                CHud::m_nHelpMessageFadeTimer -= 2 * (CTimer::ms_fTimeStep * 0.02f * 1000.0f);
				if(CHud::m_nHelpMessageFadeTimer < 0 || TheCamera.m_bWideScreenOn) {
                    CHud::m_nHelpMessageFadeTimer = 0;
                    CHud::m_nHelpMessageState = 0; // STATE_FREE_TO_USE
				}
				alpha = CHud::m_nHelpMessageFadeTimer * 0.001f * 200.0f;
				break;
			case 4: // STATE_REPLACE
                CHud::m_nHelpMessageFadeTimer -= 2 * (CTimer::ms_fTimeStep * 0.02f * 1000.0f);
				if(CHud::m_nHelpMessageFadeTimer < 0) {
                    CHud::m_nHelpMessageFadeTimer = 0;
                    CHud::m_nHelpMessageState = 2; // FADE_OUT
					CMessages::StringCopy(CHud::m_pHelpMessageToPrint, CHud::m_pLastHelpMessage, 400);
				}
				alpha = CHud::m_nHelpMessageFadeTimer * 0.001f * 200.0f;
				break;
			case 1: // STATE_IDLE
				alpha = 200.0;
                CHud::m_nHelpMessageFadeTimer = 600;
				if(!CHud::m_bHelpMessagePermanent) {
					if(CHud::m_nHelpMessageTimer > CHud::m_fHelpMessageNumLines * 1000.0f || CHud::m_bHelpMessageQuick && CHud::m_nHelpMessageTimer > 3000) {
                        CHud::m_nHelpMessageState = 3; // STATE_FADE_IN
                        CHud::m_nHelpMessageFadeTimer = 600;
					}
				}
				break;
			default:
				break;
			}
			if(!CCutsceneMgr::ms_running) {
                CHud::m_nHelpMessageTimer += (CTimer::ms_fTimeStep * 0.02f * 1000.0f);
				CFont::SetAlphaFade(alpha);
				CFont::SetProp(true);
				CFont::SetScale(SCREEN_MULTIPLIER(settings.vecTextBoxFontScale.x), SCREEN_MULTIPLIER(settings.vecTextBoxFontScale.y));
				if(CHud::m_nHelpMessageStatId) {
					if(TheCamera.m_bWideScreenOn) {
						CFont::SetAlphaFade(255.0f);
						return;
					}
					if(CHud::m_nHelpMessageStatId >= 10) {
						if(CHud::m_nHelpMessageStatId >= 100)
							sprintf(gString, "STAT%d", CHud::m_nHelpMessageStatId);
						else
							sprintf(gString, "STAT0%d", CHud::m_nHelpMessageStatId);
					}
					else
						sprintf(gString, "STAT00%d", CHud::m_nHelpMessageStatId);
					CFont::SetAlignment(ALIGN_LEFT);
					CFont::SetJustify(false);
					CFont::SetWrapx(RsGlobal.maximumWidth);
					CFont::SetFontStyle(FONT_SUBTITLES);
					CFont::SetBackground(true, true);
					CFont::SetDropShadowPosition(0);
					CFont::SetBackgroundColor(CRGBA(0, 0, 0, alpha));
					CFont::SetColor(CRGBA(255, 255, 255, 255));
					float posX = CFont::GetStringWidth(TheText.Get(gString), 1, 0) + SCREEN_COORD(GetHelpBoxXShift() + settings.fTextBoxBorderSize) + 4.0f;
					CFont::SetWrapx(SCREEN_COORD(settings.fTextBoxWidthWithProgressBar) + posX + 4.0f);
					CFont::PrintString(SCREEN_COORD(GetHelpBoxXShift() + settings.fTextBoxBorderSize) + 4.0f, SCREEN_COORD(settings.vecTextBoxPosn.y), TheText.Get(gString));
                    float progress = 0.0f;
                    if (CHud::m_nHelpMessageStatId == 336)
                        progress = plugin::CallMethodAndReturn<unsigned int, 0x5F6AA0>(0xC09928 + FindPlayerPed(-1)->m_pPlayerData->m_dwPlayerGroup * 0x2D4);
                    else
                        progress = plugin::CallAndReturn<float, 0x558E40>(CHud::m_nHelpMessageStatId);
					if(CHud::m_pHelpMessageToPrint[0] == '+') {
						DrawProgressBarWithProgressDelta_BilinearOffset(posX + SCREEN_COORD(10.0f), SCREEN_COORD(5.0f * 0.6f) +
                            SCREEN_COORD(settings.vecTextBoxPosn.y + settings.fTextBoxProgressBarYShift), SCREEN_COORD(settings.vecTextBoxProgressBarSize.x),
                            SCREEN_COORD(settings.vecTextBoxProgressBarSize.y), fmaxf((1.0f / CHud::m_nHelpMessageMaxStatValue) * progress * 100.0f, 2.0f),
							HudColour.GetRGB(HUD_COLOUR_WHITE, alpha), fmaxf((1.0f / CHud::m_nHelpMessageMaxStatValue) * CHud::m_fHelpMessageStatUpdateValue * 100.0f, 3.0f),
							HudColour.GetRGB(HUD_COLOUR_GREEN, alpha));
						CFont::SetBackground(false, false);
						CFont::PrintString(posX + SCREEN_COORD(settings.fTextBoxPlusMinTextXShift), SCREEN_COORD(settings.vecTextBoxPosn.y), CHud::m_pHelpMessageToPrint);
					}
					else {
						DrawProgressBarWithProgressDelta_BilinearOffset(posX + SCREEN_COORD(10.0f), SCREEN_COORD(5.0f * 0.6f) +
                            SCREEN_COORD(settings.vecTextBoxPosn.y + settings.fTextBoxProgressBarYShift), SCREEN_COORD(settings.vecTextBoxProgressBarSize.x),
                            SCREEN_COORD(settings.vecTextBoxProgressBarSize.y), fmaxf(1.0f / CHud::m_nHelpMessageMaxStatValue * progress * 100.0f, 2.0f),
							HudColour.GetRGB(HUD_COLOUR_WHITE, alpha), fmaxf((1.0f / CHud::m_nHelpMessageMaxStatValue) * CHud::m_fHelpMessageStatUpdateValue * 100.0f, 3.0f),
							HudColour.GetRGB(HUD_COLOUR_RED, alpha));
						CFont::SetBackground(false, false);
						CFont::PrintString(posX + SCREEN_COORD(settings.fTextBoxPlusMinTextXShift), SCREEN_COORD(settings.vecTextBoxPosn.y), CHud::m_pHelpMessageToPrint);
					}
				}
				else {
					if(CHud::m_BigMessage[0][0] || CHud::m_BigMessage[4][0] || CGarages::MessageIDString[0]) {
						CFont::SetAlphaFade(255.0f);
						return;
					}
					CFont::SetAlignment(ALIGN_LEFT);
					CFont::SetJustify(false);
					if (CHud::m_fHelpMessageBoxWidth == 200.0f)
						CFont::SetWrapx(SCREEN_COORD(GetHelpBoxXShift() + settings.fTextBoxWidth - settings.fTextBoxBorderSize) - 4.0f);
					else
						CFont::SetWrapx(SCREEN_COORD(GetHelpBoxXShift() + (CHud::m_fHelpMessageBoxWidth - settings.fTextBoxBorderSize)) - 4.0f);
					CFont::SetFontStyle(FONT_SUBTITLES);
					CFont::SetBackground(true, true);
					CFont::SetDropShadowPosition(0);
					CFont::SetBackgroundColor(CRGBA(0, 0, 0, alpha));
					CFont::SetColor(CRGBA(255, 255, 255, 255));
					int baseY = 0;
					if(TheCamera.m_bWideScreenOn && !FrontEndMenuManager.m_bWidescreenOn)
						baseY = 56;
					CFont::PrintString(SCREEN_COORD(GetHelpBoxXShift() + settings.fTextBoxBorderSize) + 4.0f,
                        SCREEN_COORD(baseY * 0.6f) + SCREEN_COORD(settings.vecTextBoxPosn.y), CHud::m_pHelpMessageToPrint);
				}
				CFont::SetWrapx(RsGlobal.maximumWidth);
				CFont::SetAlphaFade(255.0f);
				return;
			}
		}
	}
	else
        CHud::m_nHelpMessageState = 0;
}