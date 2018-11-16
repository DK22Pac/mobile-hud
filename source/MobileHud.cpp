#include "plugin.h"
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
#include "MobileMenuSystem.h"
#include "MobileLoadingScreen.h"
#include "MobileTextures.h"
#include "MobileFrontEnd.h"
#include "MobileStatsBox.h"
#include "Settings.h"

using namespace plugin;

class MobileHud {
public:
    MobileHud() {
        Events::initRwEvent += [] {
            screen::SetBaseResolution(900.0f);
            settings.Read();
            MobileTextures::Setup();

            {
                if (settings.bEnableColors)         MobileColors::Read();
                if (settings.bEnablePlayerInfo)     MobilePlayerInfo::InstallPatches();
                if (settings.bEnableRadar)          MobileRadar::InstallPatches();
                if (settings.bEnableSubtitles)      MobileSubtitles::InstallPatches();
                if (settings.bEnableRadioNames)     MobileRadioName::InstallPatches();
                if (settings.bEnableAreaNames)      MobileAreaName::InstallPatches();
                if (settings.bEnableVehicleNames)   MobileVehicleName::InstallPatches();
                if (settings.bEnableStatsBox)       MobileStatsBox::InstallPatches();
                if (settings.bEnableTextBox)        MobileTextBox::InstallPatches();
                if (settings.bEnableTimers)         MobileMissionTimers::InstallPatches();
                if (settings.bEnableProgressBars)   MobileProgressBar::InstallPatches();
                if (settings.bEnableMenuSystem)     MobileMenuSystem::InstallPatches();
                if (settings.bEnableLoadingScreens) MobileLoadingScreen::InstallPatches();
                if (settings.bEnableMenuPages)      MobileMenuPage::InstallPatches();
                if (settings.bEnableFrontends)      MobileFrontEnd::InstallPatches();
            }

            if (settings.iReloadKey) {
                Events::gameProcessEvent += [] {
                    if (settings.iReloadKey != 0) {
                        if (settings.iReloadKey == -1 || KeyPressed(settings.iReloadKey))
                            settings.Read();
                    }
                };
            }
        };

        ThiscallEvent<AddressList<0x53C69C, H_CALL>, PRIORITY_AFTER, ArgPickNone, void(void *self, unsigned __int8 r, unsigned __int8 g, unsigned __int8 b, unsigned __int8 a)> InitialiseWhenRestarting;

        InitialiseWhenRestarting += [] {
            MobileLoadingScreen::DisplaySplash();
        };

        Events::shutdownRwEvent += [] {
            MobileTxdStorage::Instance().Shutdown();
        };

        CdeclEvent<AddressList<0x71982E, H_JUMP>, PRIORITY_BEFORE, ArgPickNone, void()> myProcessPerFrameEvent;

        myProcessPerFrameEvent += [] {
            MobileTxdStorage::Instance().Process();
        };
    }
} mobileHud;
