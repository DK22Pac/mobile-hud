#include "MobileLoadingScreen.h"

MobileLoadingScreen MobileLoad;

void MobileLoadingScreen::InstallPatches() {
    plugin::patch::SetInt(0xC8D4C0, 5);
    plugin::patch::RedirectJump(0x5900B0, LoadSplashes);
    plugin::patch::RedirectJump(0x58FF60, RenderSplash);
    plugin::patch::RedirectCall(0x590480, RenderLoadingBar);
}

void MobileLoadingScreen::LoadSplashes(char bStarting, char bNvidia) {
    for (int screenId = 0; screenId < 7; ++screenId) {
        if (screenId == 0)
            mobileTex.m_aSplashes[screenId].m_pTexture = mobileTex.m_aSplashesTxd.GetTexture(MOBILESCREEN_0);
        if (screenId == 1)
            mobileTex.m_aSplashes[screenId].m_pTexture = mobileTex.m_aSplashesTxd.GetTexture(MOBILESCREEN_1);
        if (screenId == 2)
            mobileTex.m_aSplashes[screenId].m_pTexture = mobileTex.m_aSplashesTxd.GetTexture(MOBILESCREEN_2);
        if (screenId == 3)
            mobileTex.m_aSplashes[screenId].m_pTexture = mobileTex.m_aSplashesTxd.GetTexture(MOBILESCREEN_3);
        if (screenId == 4)
            mobileTex.m_aSplashes[screenId].m_pTexture = mobileTex.m_aSplashesTxd.GetTexture(MOBILESCREEN_4);
        if (screenId == 5)
            mobileTex.m_aSplashes[screenId].m_pTexture = mobileTex.m_aSplashesTxd.GetTexture(MOBILESCREEN_5);
        if (screenId == 6)
            mobileTex.m_aSplashes[screenId].m_pTexture = mobileTex.m_aSplashesTxd.GetTexture(MOBILESCREEN_6);
    }
}

int fPosX = (3000);

void MobileLoadingScreen::RenderSplash() {
    CSprite2d::InitPerFrame();

    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, reinterpret_cast<void*>(rwTEXTUREADDRESSCLAMP));

    CFont::SetProp(true);
    CFont::SetBackground(0, 0);
    CFont::SetJustify(false);
    CFont::SetOutlinePosition(1);
    CFont::SetAlignment(ALIGN_LEFT);
    CFont::SetFontStyle(FONT_SUBTITLES);
    CFont::SetOutlinePosition(1);
    CFont::SetColor(CRGBA(255, 255, 255, 255));

    if (fPosX > 0) fPosX -= 200;

    if (MobileLoad.m_bFading) {
        CSprite2d::DrawRect(CRect(BilinearOffset(0.0f), BilinearOffset(0.0f), BilinearOffset(0.0f + SCREEN_WIDTH), BilinearOffset(0.0f + SCREEN_HEIGHT)), CRGBA(0, 0, 0, 255));

        if (!MobileLoad.m_currDisplayedSplash) {
            CSprite2d::DrawRect(CRect(BilinearOffset(fPosX), BilinearOffset(0.0f), BilinearOffset(fPosX + SCREEN_WIDTH), BilinearOffset(0.0f + SCREEN_HEIGHT)), CRGBA(0, 0, 0, 255));

            // Legal screen
            if (RsGlobal.maximumWidth >= 0 && RsGlobal.maximumWidth <= 1280) {
                CFont::SetScale(SCREEN_MULTIPLIER(0.841f), SCREEN_MULTIPLIER(1.81f));
                CFont::SetWrapx(fPosX + SCREEN_COORD_RIGHT(62.0f));
                CFont::PrintString(fPosX + SCREEN_COORD_LEFT(62.0f), SCREEN_COORD_CENTER_Y - SCREEN_COORD(450.0f / 2), legal_0);
                CFont::PrintString(fPosX + SCREEN_COORD_LEFT(62.0f), SCREEN_COORD_CENTER_Y - SCREEN_COORD(0.0f / 2), legal_1);
            }
            else {
                CFont::SetScale(SCREEN_MULTIPLIER(0.841f), SCREEN_MULTIPLIER(1.81f));
                CFont::SetWrapx(fPosX + SCREEN_COORD_CENTER_LEFT(-725.0f));
                CFont::PrintString(fPosX + SCREEN_COORD_CENTER_X - SCREEN_COORD(1444.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(450.0f / 2), legal_0);
                CFont::PrintString(fPosX + SCREEN_COORD_CENTER_X - SCREEN_COORD(1444.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(0.0f / 2), legal_1);
            }
        }
        else { // Loading screen
            mobileTex.m_aSplashes[MobileLoad.m_currDisplayedSplash].Draw(SCREEN_COORD(0.0f), SCREEN_COORD(0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, CRGBA(255, 255, 255, 255));
        }
    }
}

void MobileLoadingScreen::DisplaySplash() {
    CSprite2d::InitPerFrame();

    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, reinterpret_cast<void*>(rwTEXTUREADDRESSCLAMP));

    mobileTex.m_aSplashes[4].m_pTexture = mobileTex.m_aSplashesTxd.GetTexture(MOBILESCREEN_4);
    mobileTex.m_aSplashes[4].Draw(CRect(SCREEN_COORD(0.0f), SCREEN_COORD(0.0f), SCREEN_COORD(0.0f) + SCREEN_WIDTH, SCREEN_COORD(0.0f) + SCREEN_HEIGHT), CRGBA(255, 255, 255, 255));
}

void MobileLoadingScreen::RenderLoadingBar(float x, float y, unsigned short width, unsigned char height, float progress, signed char progressAdd, unsigned char drawPercentage, unsigned char drawBlackBorder, CRGBA color, CRGBA addColor) {
    float distance = 18.0f;
    CSprite2d::DrawBarChart(SCREEN_COORD_LEFT(distance), SCREEN_COORD_BOTTOM(30.0f), SCREEN_COORD_MAX_X - SCREEN_COORD(distance * 2), SCREEN_MULTIPLIER(20.0f), progress, progressAdd, drawPercentage, drawBlackBorder, color, addColor);
}