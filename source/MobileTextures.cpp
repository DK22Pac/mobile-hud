#include "MobileTextures.h"
#include "game_sa\CTxdStore.h"
#include "game_sa\CFileLoader.h"
#include "game_sa\CTimer.h"

void MobileTexDictionary::Load() {
    if (!m_pRwTexDictionary) {
        m_pRwTexDictionary = CFileLoader::LoadTexDictionary(m_szPath);
        if (m_pRwTexDictionary) {
            RwTexDictionaryForAllTextures(m_pRwTexDictionary, [](RwTexture *tex, void *data) {
                reinterpret_cast<std::vector<RwTexture *> *>(data)->push_back(tex);
                return tex;
            }, &m_textures);
        }
        m_nLastUsedTime = CTimer::m_snTimeInMillisecondsNonClipped;
    }
}

void MobileTexDictionary::Unload() {
    if (m_pRwTexDictionary) {
        RwTexDictionaryDestroy(m_pRwTexDictionary);
        m_pRwTexDictionary = nullptr;
        m_textures.clear();
    }
}

void MobileTexDictionary::AddToStorage() {
    MobileTxdStorage::Instance().AddTxd(this);
}

MobileTexDictionary::MobileTexDictionary() {
    m_szPath[0] = '\0';
    m_bInitialised = false;
    m_nLastUsedTime = 0;
}

void MobileTexDictionary::Init(char *path) {
    strcpy(m_szPath, path);
    m_pRwTexDictionary = nullptr;
    m_bInitialised = true;
    AddToStorage();
}

RwTexture *MobileTexDictionary::GetTexture(unsigned int id) {
    if (m_bInitialised) {
        Load();
        if (m_textures.size() > id) {
            m_nLastUsedTime = CTimer::m_snTimeInMillisecondsNonClipped;
            return m_textures[id];
        }
    }
    return nullptr;
}

void MobileTxdStorage::Process() {
    for (auto txd : m_txds) {
        if (CTimer::m_snTimeInMilliseconds - txd->m_nLastUsedTime > LOAD_UNLOAD_TIME)
            txd->Unload();
    }
}

void MobileTxdStorage::AddTxd(MobileTexDictionary *txd) {
    m_txds.push_back(txd);
}

void MobileTxdStorage::Shutdown() {
    for (auto txd : m_txds) {
        txd->Unload();
    }
}

MobileTxdStorage &MobileTxdStorage::Instance() {
    static MobileTxdStorage storage;
    return storage;
}

MobileTextures mobileTex;

void MobileTextures::Initialise() {
    int txd = CTxdStore::AddTxdSlot("menu");
    CTxdStore::LoadTxd(txd, PLUGIN_PATH("MobileHud\\menu.txd"));
    CTxdStore::AddRef(txd);
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(txd);

    mobileTex.m_nBackgroundSprite[0].SetTexture("menu_bgmap");

    mobileTex.m_nMenuChar[0].SetTexture("menu_char0");
    mobileTex.m_nMenuChar[1].SetTexture("menu_char1");
    mobileTex.m_nMenuChar[2].SetTexture("menu_char2");
    mobileTex.m_nMenuChar[3].SetTexture("menu_char3");
    mobileTex.m_nMenuChar[4].SetTexture("menu_char4");
    mobileTex.m_nMenuChar[6].SetTexture("menu_char5");
    mobileTex.m_nMenuChar[7].SetTexture("menu_char6");
    mobileTex.m_nMenuChar[10].SetTexture("menu_char7");
    mobileTex.m_nMenuChar[11].SetTexture("menu_char8");

    mobileTex.m_nMenuSprite[0].SetTexture("menu_mainbriefs");
    mobileTex.m_nMenuSprite[1].SetTexture("menu_mainhelp");
    mobileTex.m_nMenuSprite[2].SetTexture("menu_mainmask");
    mobileTex.m_nMenuSprite[3].SetTexture("menu_mainplay");
    mobileTex.m_nMenuSprite[4].SetTexture("menu_mainpresents");
    mobileTex.m_nMenuSprite[5].SetTexture("menu_mainsettings");
    mobileTex.m_nMenuSprite[6].SetTexture("menu_mainstats");
    mobileTex.m_nMenuSprite[7].SetTexture("menu_selector");
    mobileTex.m_nMenuSprite[8].SetTexture("menu_smalllogo");
    mobileTex.m_nMenuSprite[9].SetTexture("menu_adjback");
    mobileTex.m_nMenuSprite[10].SetTexture("menu_adjback2");
    mobileTex.m_nMenuSprite[11].SetTexture("menu_mainaudio");
    mobileTex.m_nMenuSprite[12].SetTexture("menu_maincontrols");
    mobileTex.m_nMenuSprite[13].SetTexture("menu_maindelete");
    mobileTex.m_nMenuSprite[14].SetTexture("menu_maindisplay");
    mobileTex.m_nMenuSprite[15].SetTexture("menu_mainlanguage");
    mobileTex.m_nMenuSprite[16].SetTexture("menu_mainquit");
    mobileTex.m_nMenuSprite[17].SetTexture("menu_mainresume");
    mobileTex.m_nMenuSprite[18].SetTexture("menu_mainsave");

    mobileTex.m_nSliderSprite[0].SetTexture("menu_sliderempty");
    mobileTex.m_nSliderSprite[1].SetTexture("menu_sliderfull");
    mobileTex.m_nSliderSprite[2].SetTexture("menu_slidernub");

    mobileTex.m_nMenuMain[0].SetTexture("menu_main1");
    mobileTex.m_nMenuMain[1].SetTexture("menu_main2");
    mobileTex.m_nMenuMain[2].SetTexture("menu_main3");
    mobileTex.m_nMenuMain[3].SetTexture("menu_main4");

    CTxdStore::PopCurrentTxd();
}