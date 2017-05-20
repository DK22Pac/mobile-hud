#pragma once
#include <plugin.h>
#include "game_sa\common.h"
#include "game_sa\CMenuManager.h"
#include "MobileFrontEnd.h"
#include "Utility.h"

class MobileMenuPage {
public:
    static void InstallPatches();

public:
    static CMenuPage PagesMenu[];
};