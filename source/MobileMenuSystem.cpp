// mobile-hud
#include "MobileMenuSystem.h"

void MobileMenuSystem::InstallPatches() {
    plugin::patch::RedirectJump(0x580E00, DisplayStandardMenu);
}

void MobileMenuSystem::DisplayStandardMenu(unsigned char menuId, bool bBrightFont) {
    // Background
    if (MenuNumber[menuId]->m_bColumnBackground) {
        DrawRect(SCREEN_COORD_LEFT(0.0f), SCREEN_COORD(0.0), SCREEN_MULTIPLIER(502.0f), SCREEN_HEIGHT, 1, CRGBA(0, 0, 0, 130));
    }

    if (MenuNumber[menuId]->m_nNumRows) {
        for (int i = 0; i < MenuNumber[menuId]->m_nNumColumns; i++) {
            float fMenu_PosX = SCREEN_COORD_LEFT(60.0f);
            float fMenu_PosY = SCREEN_COORD_TOP(225.0f);
            float fAlpha;

            // Scroll up to 20 rows
            if (MenuNumber[menuId]->m_nSelectedRow >= 8 && MenuNumber[menuId]->m_nSelectedRow <= (MenuNumber[menuId]->m_nNumRows)) {
                if (MenuNumber[menuId]->m_nSelectedRow == 8)
                    fMenu_PosY -= SCREEN_COORD(80.0);
                if (MenuNumber[menuId]->m_nSelectedRow == 9)
                    fMenu_PosY -= SCREEN_COORD(80.0 * 2);
                if (MenuNumber[menuId]->m_nSelectedRow == 10)
                    fMenu_PosY -= SCREEN_COORD(80.0 * 3);
                if (MenuNumber[menuId]->m_nSelectedRow == 11)
                    fMenu_PosY -= SCREEN_COORD(80.0 * 4);
                if (MenuNumber[menuId]->m_nSelectedRow == 12)
                    fMenu_PosY -= SCREEN_COORD(80.0 * 5);
                if (MenuNumber[menuId]->m_nSelectedRow == 13)
                    fMenu_PosY -= SCREEN_COORD(80.0 * 6);
                if (MenuNumber[menuId]->m_nSelectedRow == 14)
                    fMenu_PosY -= SCREEN_COORD(80.0 * 7);
                if (MenuNumber[menuId]->m_nSelectedRow == 15)
                    fMenu_PosY -= SCREEN_COORD(80.0 * 8);
                if (MenuNumber[menuId]->m_nSelectedRow == 16)
                    fMenu_PosY -= SCREEN_COORD(80.0 * 9);
                if (MenuNumber[menuId]->m_nSelectedRow == 17)
                    fMenu_PosY -= SCREEN_COORD(80.0 * 10);
                if (MenuNumber[menuId]->m_nSelectedRow == 18)
                    fMenu_PosY -= SCREEN_COORD(80.0 * 11);
                if (MenuNumber[menuId]->m_nSelectedRow == 19)
                    fMenu_PosY -= SCREEN_COORD(80.0 * 12);
                if (MenuNumber[menuId]->m_nSelectedRow == 20)
                    fMenu_PosY -= SCREEN_COORD(80.0 * 13);
            }

            // Second Column position
            if (MenuNumber[menuId]->m_anColumnAlignment[i] == ALIGN_RIGHT || MenuNumber[menuId]->m_anColumnAlignment[i] == ALIGN_CENTER)
                fMenu_PosY += SCREEN_COORD_TOP(35.0f);

            for (int j = 0; j < MenuNumber[menuId]->m_nNumRows; j++) {
                if (MenuNumber[menuId]->m_aaacRowTitles[i][j][0]) {
                    int SelectMarker = MenuNumber[menuId]->m_nSelectedRow == j;

                    // TODO: MenuNumber[menuId]->m_abColumnInteractive //

                    // Scrolling row
                    if (fMenu_PosY < SCREEN_COORD_TOP(110.0f))
                        fAlpha = 0.0f;
                    else if (fMenu_PosY < SCREEN_COORD(225.0f))
                        fAlpha = 50.0f;
                    else
                        if (fMenu_PosY > SCREEN_COORD_BOTTOM(50.0f))
                            fAlpha = 50.0;
                        else
                            fAlpha = 255.0f;

                    // Set colors
                    if (MenuNumber[menuId]->m_anColumnAlignment[i] == ALIGN_RIGHT || MenuNumber[menuId]->m_anColumnAlignment[i] == ALIGN_CENTER) {
                        CFont::SetColor(CRGBA(0, 120, 0, static_cast<BYTE>(fAlpha)));
                        CFont::SetDropColor(CRGBA(0, 0, 0, static_cast<BYTE>(fAlpha)));
                    }
                    else {
                        CFont::SetColor(CRGBA(255, 255, 255, static_cast<BYTE>(fAlpha)));
                        CFont::SetDropColor(CRGBA(0, 0, 0, static_cast<BYTE>(fAlpha)));

                        if (SelectMarker) // Selected row marker
                            DrawRect(SCREEN_COORD_LEFT(3.0f), fMenu_PosY - SCREEN_COORD(20.0f), SCREEN_COORD(497.0f), SCREEN_COORD(80.0f), 0, CRGBA(255, 255, 255, 50));
                    }

                    // Insert numbers
                    CMessages::InsertNumberInString(TheText.Get(MenuNumber[menuId]->m_aaacRowTitles[i][j]), MenuNumber[menuId]->m_aadwNumberInRowTitle[i][j], MenuNumber[menuId]->m_aadw2ndNumberInRowTitle[i][j], -1, -1, -1, -1, gString);
                    CMessages::InsertPlayerControlKeysInString(gString);

                    // Set and print
                    CFont::SetProp(true);
                    CFont::SetAlignment(ALIGN_LEFT);
                    CFont::SetOutlinePosition(2);
                    CFont::SetFontStyle(FONT_MENU);

                    if (MenuNumber[menuId]->m_nNumColumns == 2) { // bottom
                        CFont::SetScale(SCREEN_MULTIPLIER(0.8f), SCREEN_MULTIPLIER(1.6f));
                        float width = CFont::GetStringWidth(gString, true, false);
                        if (width > SCREEN_MULTIPLIER(418.0f))
                            CFont::SetScale(SCREEN_MULTIPLIER(0.8f * SCREEN_MULTIPLIER(418.0f) / width), SCREEN_MULTIPLIER(1.6f));

                        CFont::PrintString(fMenu_PosX + SCREEN_COORD(30.0f), fMenu_PosY - SCREEN_COORD(15.0f), gString);
                    }
                    else { // top
                        CFont::SetScale(SCREEN_MULTIPLIER(1.0f), SCREEN_MULTIPLIER(2.0f));
                        float width = CFont::GetStringWidth(gString, true, false);
                        if (width > SCREEN_MULTIPLIER(418.0f))
                            CFont::SetScale(SCREEN_MULTIPLIER(1.0f * SCREEN_MULTIPLIER(418.0f) / width), SCREEN_MULTIPLIER(2.0f));

                        CFont::PrintString(fMenu_PosX, fMenu_PosY, gString);
                    }

                    // Spacing
                    fMenu_PosY += SCREEN_COORD_TOP(80.0f);
                }
            }
        }
    }

    // Header
    CFont::SetProp(true);
    CFont::SetAlignment(ALIGN_LEFT);
    CFont::SetFontStyle(FONT_GOTHIC);
    CFont::SetOutlinePosition(2);
    CFont::SetScale(SCREEN_MULTIPLIER(3.5f), SCREEN_MULTIPLIER(6.5f));
    float width = CFont::GetStringWidth(TheText.Get(MenuNumber[menuId]->m_acTitle), true, false);
    if (width > SCREEN_MULTIPLIER(464.0f))
        CFont::SetScale(SCREEN_MULTIPLIER(3.5f * SCREEN_MULTIPLIER(464.0f) / width), SCREEN_MULTIPLIER(6.5f));
    CFont::SetColor(CRGBA(255, 255, 255, 225));
    CFont::SetDropColor(CRGBA(0, 0, 0, 255));
    CFont::PrintString(SCREEN_COORD_LEFT(13.0f), SCREEN_COORD_TOP(30.5f), TheText.Get(MenuNumber[menuId]->m_acTitle));
}

void MobileMenuSystem::DrawRect(CRect const& rect, bool bFading, CRGBA const& color) {
    unsigned int savedShade;
    unsigned int savedAlpha;
    RwRenderStateGet(rwRENDERSTATESHADEMODE, &savedShade);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void *>(rwSHADEMODEGOURAUD));
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));
    if (bFading)
        CSprite2d::DrawRect(CRect(BilinearOffset(rect.left), BilinearOffset(rect.bottom),
            BilinearOffset(rect.right), BilinearOffset(rect.top)),
            CRGBA(color.red, color.green, color.blue, 255), CRGBA(color.red, color.green, color.blue, color.alpha),
            CRGBA(color.red, color.green, color.blue, 255), CRGBA(color.red, color.green, color.blue, color.alpha));
    else
        CSprite2d::DrawRect(CRect(BilinearOffset(rect.left), BilinearOffset(rect.bottom),
            BilinearOffset(rect.right), BilinearOffset(rect.top)), color);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void *>(savedShade));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
}