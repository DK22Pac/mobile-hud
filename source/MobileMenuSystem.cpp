// mobile-hud
#include "MobileMenuSystem.h"

void MobileMenuSystem::InstallPatches() {
	plugin::patch::RedirectJump(0x580E00, DisplayStandardMenu);
}

void MobileMenuSystem::DisplayStandardMenu(unsigned char menuId, bool bBrightFont) {
	// Header
	CFont::SetProp(true);
	CFont::SetAlignment(ALIGN_LEFT);
	CFont::SetFontStyle(FONT_GOTHIC);
	CFont::SetOutlinePosition(2);
	CFont::SetScale(SCREEN_MULTIPLIER(3.5f), SCREEN_MULTIPLIER(6.5f));
	float width = CFont::GetStringWidth(TheText.Get(MenuNumber[menuId]->m_acTitle), true, false);
	if (width > SCREEN_MULTIPLIER(462.0f))
		CFont::SetScale(SCREEN_MULTIPLIER(3.5f * SCREEN_MULTIPLIER(462.0f) / width), SCREEN_MULTIPLIER(6.5f));
	CFont::SetColor(CRGBA(255, 255, 255, 225));
	CFont::PrintString(SCREEN_COORD_LEFT(15.5f), SCREEN_COORD_TOP(30.5f), TheText.Get(MenuNumber[menuId]->m_acTitle));

	// Background
	if (MenuNumber[menuId]->m_bColumnBackground) {
		DrawRect(SCREEN_COORD_LEFT(0.0f), SCREEN_COORD(0.0), SCREEN_MULTIPLIER(502.0f), SCREEN_HEIGHT, 1, CRGBA(0, 0, 0, 155));
	}

	if (MenuNumber[menuId]->m_nNumRows) {
		for (int i = 0; i < MenuNumber[menuId]->m_nNumColumns; i++) {
			float fMenu_PosX = SCREEN_COORD_LEFT(60.0f);
			float fMenu_PosY = SCREEN_COORD_TOP(225.0f);

            // Second Column position
            if (MenuNumber[menuId]->m_anColumnAlignment[i] == ALIGN_RIGHT || MenuNumber[menuId]->m_anColumnAlignment[i] == ALIGN_CENTER)
                fMenu_PosY += SCREEN_COORD_TOP(35.0f);

			for (int j = 0; j < MenuNumber[menuId]->m_nNumRows; j++) {
				if (MenuNumber[menuId]->m_aaacRowTitles[i][j][0]) {

                    // TODO: MenuNumber[menuId]->m_abColumnInteractive //

                    // Set colors
                    if (MenuNumber[menuId]->m_anColumnAlignment[i] == ALIGN_RIGHT || MenuNumber[menuId]->m_anColumnAlignment[i] == ALIGN_CENTER) {
                        CFont::SetColor(CRGBA(0, 120, 0, 255));
                    }
                    else {
                        CFont::SetColor(CRGBA(255, 255, 255, 255));

                        if (MenuNumber[menuId]->m_nSelectedRow == j) // Selected row marker
                            DrawRect(SCREEN_COORD_LEFT(3.0f), fMenu_PosY - SCREEN_COORD(20.0f), SCREEN_COORD(497.0f), SCREEN_COORD(80.0f), 0, CRGBA(255, 255, 255, 50));
                    }

                    // Insert numbers
					CMessages::InsertNumberInString(TheText.Get(MenuNumber[menuId]->m_aaacRowTitles[i][j]), MenuNumber[menuId]->m_aadwNumberInRowTitle[i][j], MenuNumber[menuId]->m_aadw2ndNumberInRowTitle[i][j], -1, -1, -1, -1, gString);
					CMessages::InsertPlayerControlKeysInString(gString);

					// Set and print
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