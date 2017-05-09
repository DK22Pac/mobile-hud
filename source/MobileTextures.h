#pragma once
// plugin-sdk
#include <plugin.h>
#include "game_sa\CSprite2d.h"
#include "game_sa\CTxdStore.h"

// MobileMenu
#include "MobileLoadingScreen.h"

class MobileTextures {
public:
    CSprite2d m_aSplashes[6];
    CSprite2d m_nBackgroundSprite[1];
    CSprite2d m_nMenuChar[12];
    CSprite2d m_nMenuSprite[19];
    CSprite2d m_nSliderSprite[3];
    CSprite2d m_nMenuMain[4];

public:
    static void Initialise();
};

extern MobileTextures mobileTex;
