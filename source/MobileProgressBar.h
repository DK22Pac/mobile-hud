#pragma once
#include "game_sa\CRGBA.h"

class MobileProgressBar {
public:
    static void InstallPatches();
    static void MyDrawProgressBar(float x, float y, unsigned short width, unsigned char height, float progress, signed char progressAdd,
        unsigned char drawPercentage, unsigned char drawBlackBorder, CRGBA color, CRGBA addColor);
};