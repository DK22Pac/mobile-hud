#include "MobileProgressBar.h"
#include "Utility.h"
#include "plugin.h"
#include "CSprite2d.h"
#include "CFont.h"

using namespace plugin;

void MobileProgressBar::InstallPatches() {
    patch::RedirectJump(0x728640, MyDrawProgressBar);
}

void MobileProgressBar::MyDrawProgressBar(float x, float y, unsigned short width, unsigned char height, float progress, signed char progressAdd,
    unsigned char drawPercentage, unsigned char drawBlackBorder, CRGBA color, CRGBA addColor)
{
    if (drawBlackBorder) {
        CSprite2d::DrawRect(CRect((int)(x - 1) - 0.5f, (int)(y - 1) - 0.5f, (int)(x + width + 1) - 0.5f,
            (int)(y + height + 1) - 0.5f), CRGBA(0, 0, 0, 255));
    }
    DrawProgressBarWithProgressDelta_BilinearOffset(x, y, width, height, progress, color, progressAdd, addColor);
    if (drawPercentage) {
        static char text[12];
        sprintf(text, "%d%%", (int)progress);
        CFont::SetWrapx(SCREEN_WIDTH);
        CFont::SetRightJustifyWrap(0.0f);
        CFont::SetColor(CRGBA(0, 0, 0, color.a));
        CFont::SetEdge(0);
        CFont::SetFontStyle(FONT_SUBTITLES);
        CFont::SetScale(height * 0.035f, height * 0.05f);
        float text_x = x + width * progress / 100.0f;
        if (progress > 50.0)
            CFont::SetOrientation(ALIGN_RIGHT);
        else {
            CFont::SetOrientation(ALIGN_LEFT);
            text_x += 5.0f;
        }
        CFont::PrintString(text_x, y, text);
    }
}
