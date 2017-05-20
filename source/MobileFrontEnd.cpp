#include "MobileFrontEnd.h"
#include "game_sa\CHudColours.h"

MobileTexDictionary MobileFrontEnd::m_menuSliderTxd;

void MobileFrontEnd::InstallPatches() {
    plugin::patch::RedirectCall(0x574F54, DrawStatsSlider);
}

void MobileFrontEnd::Setup() {
    m_menuSliderTxd.Init(PLUGIN_PATH("MobileHud\\menu_slider.txd"));
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