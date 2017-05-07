// mobile-hud
#include "MobileSubtitles.h"

void MobileSubtitles::InstallPatches() {
	plugin::patch::RedirectCall(0x58C68A, DrawSubtitles);
}

void MobileSubtitles::DrawSubtitles(float x, float y, char *str) {
	CFont::SetBackground(0, 0);
	CFont::SetAlignment(ALIGN_CENTER);
	CFont::SetProp(true);
	CFont::SetJustify(false);
	CFont::SetColor(CRGBA(255, 255, 255, 255));
	CFont::SetFontStyle(FONT_SUBTITLES);
	CFont::SetOutlinePosition(2);
	CFont::SetCentreSize(SCREEN_WIDTH + SCREEN_COORD(-350));
	CFont::SetScale(SCREEN_MULTIPLIER(settings.vecSubtitlesScale.x), SCREEN_MULTIPLIER(settings.vecSubtitlesScale.y));

	if (TheCamera.m_bWideScreenOn)
		CFont::PrintStringFromBottom(SCREEN_COORD_CENTER_LEFT(0.0f), SCREEN_COORD_BOTTOM(settings.fSubtitlesWidePosnY), str);
	else
		CFont::PrintStringFromBottom(SCREEN_COORD_CENTER_LEFT(0.0f), SCREEN_COORD_BOTTOM(settings.fSubtitlesPosnY), str);

}