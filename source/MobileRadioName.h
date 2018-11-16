#pragma once
#include "CFont.h"

class MobileRadioName {
public:
    static void InstallPatches();
    static void MySetRadioNameScale(float x, float y);
    static void MyDrawRadioName(float x, float y, char *name);
    static void MySetRadioNameAlignment(eFontAlignment alignment);
};
