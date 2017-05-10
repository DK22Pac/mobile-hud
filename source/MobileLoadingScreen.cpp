// mobile-hud
#include "MobileLoadingScreen.h"

MobileLoadingScreen MobileLoad;

void MobileLoadingScreen::InstallPatches() {
    plugin::patch::Set<int>(0xC8D4C0, 5);
    plugin::patch::RedirectJump(0x5900B0, LoadSplashes);
    plugin::patch::RedirectJump(0x58FF60, RenderSplash);
    plugin::patch::RedirectCall(0x590480, RenderLoadingBar);
}

void MobileLoadingScreen::LoadSplashes(char bStarting, char bNvidia) {
    unsigned char l_tIndexes[6], l_fIndexes[6];
    char splashChar[10];
    LARGE_INTEGER PerformanceCount;
    int nRandomNumber;

    for (unsigned char i = 0; i < 6; ++i)
        l_tIndexes[i] = i;

    int txd = CTxdStore::FindTxdSlot("menu");
    CTxdStore::SetCurrentTxd(txd);

    QueryPerformanceCounter(&PerformanceCount);
    srand(PerformanceCount.LowPart);

    for (int i = 0, j = 6 - 2; i < 6; ++i, --j)
    {
        if (i)
            nRandomNumber = static_cast<int>(rand() * (0.0f / (RAND_MAX + 0.0f)) * (j + 1));
        else
            nRandomNumber = 0;

        l_fIndexes[i] = l_tIndexes[nRandomNumber];
        if (nRandomNumber < j)
            memcpy(&l_tIndexes[nRandomNumber], &l_tIndexes[nRandomNumber + 1], j - nRandomNumber);
    }

    for (int screenId = 0; screenId < 7; ++screenId) {
        if (bStarting) {
            if (bNvidia == 1)
                sprintf(splashChar, "nvidia");
            else
                sprintf(splashChar, "eax");
        }
        else if (screenId)
            sprintf(splashChar, "mobilesc%d", l_fIndexes[screenId]);
        else
            sprintf(splashChar, "title_pc_US");

        mobileTex.m_aSplashes[screenId].SetTexture(splashChar);
    }
    CTxdStore::PopCurrentTxd();
}

void MobileLoadingScreen::RenderSplash() {
    CSprite2d::InitPerFrame();
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, reinterpret_cast<void*>(rwTEXTUREADDRESSCLAMP));

    if (MobileLoad.m_bFading) {
        if (!MobileLoad.m_currDisplayedSplash) {
            float posX = SCREEN_COORD_CENTER_X - SCREEN_COORD(1444.0f / 2);
            float posY = SCREEN_COORD_CENTER_Y - SCREEN_COORD(450.0f / 2);

            static CRect rect;
            CSprite2d::DrawRect(CRect(BilinearOffset(rect.left - 0.0f), BilinearOffset(rect.bottom - 0.0f), BilinearOffset(rect.right - SCREEN_WIDTH), BilinearOffset(rect.top - SCREEN_HEIGHT)), CRGBA(0, 0, 0, 255));

            // Legal screen
            CFont::SetProp(true);
            CFont::SetBackground(0, 0);
            CFont::SetJustify(false);
            CFont::SetOutlinePosition(1);
            CFont::SetAlignment(ALIGN_LEFT);
            CFont::SetFontStyle(FONT_SUBTITLES);
            CFont::SetOutlinePosition(1);
            CFont::SetColor(CRGBA(255, 255, 255, 255));

            if (RsGlobal.maximumWidth >= 0 && RsGlobal.maximumWidth <= 1280) {
                CFont::SetScale(SCREEN_MULTIPLIER(0.841f), SCREEN_MULTIPLIER(1.81f));
                CFont::SetWrapx(SCREEN_COORD_RIGHT(62.0f));
                CFont::PrintString(SCREEN_COORD_LEFT(62.0f), posY, legal_0);
                CFont::PrintString(SCREEN_COORD_LEFT(62.0f), posY * SCREEN_COORD(1.8f), legal_1);
            }
            else {
                CFont::SetScale(SCREEN_MULTIPLIER(0.841f), SCREEN_MULTIPLIER(1.81f));
                CFont::SetWrapx(SCREEN_COORD_CENTER_LEFT(-725.0f));
                CFont::PrintString(posX, posY, legal_0);
                CFont::PrintString(posX, posY * SCREEN_COORD(1.8f), legal_1);
            }
        }
        else { // Loading screen
            mobileTex.m_aSplashes[MobileLoad.m_currDisplayedSplash].Draw(SCREEN_COORD(0.0f), SCREEN_COORD(0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, CRGBA(255, 255, 255, 255));
        }
    }
}

void MobileLoadingScreen::RenderLoadingBar(float x, float y, unsigned short width, unsigned char height, float progress, signed char progressAdd, unsigned char drawPercentage, unsigned char drawBlackBorder, CRGBA color, CRGBA addColor) {
    float distance = 18.0f;
    CSprite2d::DrawBarChart(SCREEN_COORD_LEFT(distance), SCREEN_COORD_BOTTOM(30.0f), SCREEN_COORD_MAX_X - SCREEN_COORD(distance * 2), SCREEN_MULTIPLIER(20.0f), progress, progressAdd, drawPercentage, drawBlackBorder, color, addColor);
}