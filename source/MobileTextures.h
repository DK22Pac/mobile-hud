#pragma once
#include "MobileLoadingScreen.h"
#include "plugin.h"
#include "game_sa\CSprite2d.h"

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