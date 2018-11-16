#pragma once
#include "plugin.h"
#include "CFont.h"
#include "CTxdStore.h"
#include "CMenuManager.h"
#include "MobileTextures.h"
#include "MobileText.h"
#include "MobileMenuSystem.h"
#include "Utility.h"

class MobileLoadingScreen {
public:
    int& m_currDisplayedSplash = *(int*)0x8D093C;
    bool& m_bFading = *(bool*)0xBAB31C;

public:
    static void InstallPatches();
    static void LoadSplashes(char bStarting, char bNvidia);
    static void RenderSplash();
    static void DisplaySplash();
    static void RenderLoadingBar(float x, float y, unsigned short width, unsigned char height, float progress, signed char progressAdd, unsigned char drawPercentage, unsigned char drawBlackBorder, CRGBA color, CRGBA addColor);
};

extern MobileLoadingScreen MobileLoad;
