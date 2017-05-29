#pragma once
#include "MobileLoadingScreen.h"
#include "plugin.h"
#include "game_sa\CSprite2d.h"

enum eMenuSliderTexture {
    MENU_SLIDER_NUB,
    MENU_SLIDER_FULL,
    MENU_SLIDER_EMPTY
};

enum eLoadScreenTexture {
    MOBILESCREEN_0,
    MOBILESCREEN_1,
    MOBILESCREEN_2,
    MOBILESCREEN_3,
    MOBILESCREEN_4,
    MOBILESCREEN_5,
    MOBILESCREEN_6,
    ROCKSTAR,
    LEGALSCREEN
};

enum eMenuBackgroundTexture {
    MENU_CHAR_0,
    MENU_CHAR_1,
    MENU_CHAR_2,
    MENU_CHAR_3,
    MENU_CHAR_4,
    MENU_CHAR_5,
    MENU_CHAR_6,
    MENU_CHAR_7,
    MENU_CHAR_8,
    MENU_BGMAP,
    MENU_MAINMASK
};

class MobileTexDictionary {
    friend class MobileTxdStorage;
    char m_szPath[MAX_PATH];
    RwTexDictionary *m_pRwTexDictionary;
    std::vector<RwTexture *> m_textures;
    int m_nLastUsedTime;
    bool m_bInitialised;

    void Load();
    void Unload();
    void AddToStorage();
public:
    MobileTexDictionary();
    void Init(char *path);
    RwTexture *GetTexture(unsigned int id = 0);
};

class MobileTxdStorage {
    std::vector<MobileTexDictionary *> m_txds;
    static const int LOAD_UNLOAD_TIME = 3000;
public:
    static MobileTxdStorage &Instance();
    void Process();
    void AddTxd(MobileTexDictionary *txd);
    void Shutdown();
};

class MobileTextures {
public:
    CSprite2d m_menuSlider;
    CSprite2d m_aSplashes[6];
    CSprite2d m_nBackgroundSprite;

    static MobileTexDictionary m_menuSliderTxd, m_aSplashesTxd, m_nBackgroundSpriteTxd;

public:
    static void Setup();
};

extern MobileTextures mobileTex;