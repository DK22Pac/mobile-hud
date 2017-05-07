// plugin-sdk
#include <plugin.h>

// mobile-hud
#include "MobilePlayerInfo.h"
#include "MobileRadar.h"
#include "MobileColors.h"
#include "MobileSubtitles.h"
#include "MobileRadioName.h"
#include "MobileTextBox.h"
#include "MobileMissionTimers.h"
#include "MobileProgressBar.h"
#include "MobileAreaName.h"
#include "MobileVehicleName.h"
#include "Settings.h"

using namespace plugin;

class MobileHud {
public:
    MobileHud() {
        Events::initRwEvent += [] {
            screen::SetBaseResolution(900.0f);
            settings.Read();
            MobileColors::Read();
            MobilePlayerInfo::InstallPatches();
            MobileRadar::InstallPatches();
            MobileSubtitles::InstallPatches();
            MobileRadioName::InstallPatches();
            MobileTextBox::InstallPatches();
            MobileMissionTimers::InstallPatches();
            MobileProgressBar::InstallPatches();
			MobileAreaName::InstallPatches();
			MobileVehicleName::InstallPatches();

            if (settings.iReloadKey) {
                Events::gameProcessEvent += [] {
                    if (settings.iReloadKey != 0) {
                        if (settings.iReloadKey == -1 || KeyPressed(settings.iReloadKey))
                            settings.Read();
                    }
                };
            }
        };
    }
} mobileHud;