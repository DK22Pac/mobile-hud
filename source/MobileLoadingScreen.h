#pragma once
// plugin-sdk
#include <plugin.h>
#include "game_sa\CFont.h"
#include "game_sa\CTxdStore.h"

// mobile-hud
#include "MobileTextures.h"
#include "MobileText.h"
#include "MobileMenuSystem.h"
#include "Settings.h"
#include "Utility.h"

class MobileLoadingScreen {
public:
    int& m_lCurrentSprite = *(int*)0x8D093C;

public:
    static void InstallPatches();
    static void LoadSplashes(char bStarting, char bNvidia);
    static void RenderSplash();
    static void RenderLoadingBar(float x, float y, unsigned short width, unsigned char height, float progress, signed char progressAdd, unsigned char drawPercentage, unsigned char drawBlackBorder, CRGBA color, CRGBA addColor);
};

extern MobileLoadingScreen loadSc;