#pragma once
#include <plugin.h>
#include "game_sa\common.h"
#include "game_sa\CMenuManager.h"
#include "MobileFrontEnd.h"
#include "Utility.h"

struct MyMenuPageButton {
    unsigned char m_nActionType; // Unknown if signed or signed, but it does only '==' comparisions, so it's safe to use unsigned (moar numbers)
    char m_szName[8];
    char m_nType;
    short m_nTargetMenu;
    short m_nPosnX;
    short m_nPosnY;
    char m_nAlign;
};

VALIDATE_SIZE(MyMenuPageButton, 0x12);

struct MyMenuPage {
    char m_szTitleName[8];
    char m_nPrevMenu;
    char m_nStartingButton;
    MyMenuPageButton m_aButtons[12];
};

VALIDATE_SIZE(MyMenuPage, 0xE2);

class MobileMenuPage {
public:
    static void InstallPatches();

public:
    static MyMenuPage PagesMenu[];
};