#include "MobileSubtitles.h"
#include "plugin.h"
#include "game_sa\CFont.h"

void MobileSubtitles::InstallPatches() {
	plugin::patch::RedirectCall(0x58C307, MySetSubtitlesOutlinePosition);
}

void MobileSubtitles::MySetSubtitlesOutlinePosition(short size) {
	CFont::SetOutlinePosition(2);
}