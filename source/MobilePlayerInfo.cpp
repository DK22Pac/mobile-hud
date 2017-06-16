#include "MobilePlayerInfo.h"
#include "Settings.h"
#include "Utility.h"
#include "plugin.h"
#include "game_sa\CHudColours.h"
#include "game_sa\CWorld.h"
#include "game_sa\CStats.h"
#include "game_sa\common.h"
#include "game_sa\CSprite.h"
#include "game_sa\CFont.h"
#include "game_sa\CHud.h"
#include "game_sa\CTimer.h"
#include "game_sa\CTxdStore.h"
#include "game_sa\CModelInfo.h"
#include "game_sa\CKeyGen.h"
#include "game_sa\CDarkel.h"
#include <math.h>

unsigned int MobilePlayerInfo::m_CurrentStar;

void MobilePlayerInfo::InstallPatches() {
    static float shadowOffsetMp = 0.0009765625f;
    plugin::patch::SetPointer(0x719D7C + 2, &shadowOffsetMp);
    plugin::patch::SetPointer(0x719D94 + 2, &shadowOffsetMp);
    plugin::patch::SetPointer(0x719DB5 + 2, &shadowOffsetMp);
    plugin::patch::SetPointer(0x719DD1 + 2, &shadowOffsetMp);
    plugin::patch::SetPointer(0x719DF2 + 2, &shadowOffsetMp);
    plugin::patch::SetPointer(0x719E0E + 2, &shadowOffsetMp);
    plugin::patch::SetPointer(0x719E2F + 2, &shadowOffsetMp);
    plugin::patch::SetPointer(0x719E4B + 2, &shadowOffsetMp);
    plugin::patch::SetPointer(0x719E6F + 2, &shadowOffsetMp);
    plugin::patch::SetPointer(0x719E97 + 2, &shadowOffsetMp);
    plugin::patch::SetPointer(0x719EBF + 2, &shadowOffsetMp);
    plugin::patch::SetPointer(0x719EE3 + 2, &shadowOffsetMp);
    plugin::patch::SetUInt(0x719D90, 0xC17048);
    plugin::patch::SetUInt(0x719DCD, 0xC17048);
    plugin::patch::SetUInt(0x719E0A, 0xC17048);
    plugin::patch::SetUInt(0x719E47, 0xC17048);
    plugin::patch::SetUInt(0x719E63, 0xC17048);
    plugin::patch::SetUInt(0x719E8B, 0xC17048);
    plugin::patch::RedirectJump(0x58D7D0, MyDrawWeaponIcon);
    plugin::patch::RedirectJump(0x5893B0, MyDrawWeaponAmmo);
    plugin::patch::RedirectCall(0x58EB4E, MySetClockScale);
    plugin::patch::RedirectCall(0x58EC21, MyDrawClock);
    plugin::patch::RedirectCall(0x58F56B, MySetMoneyScale);
    plugin::patch::RedirectCall(0x58F607, MyDrawMoney);
    plugin::patch::RedirectJump(0x589270, MyDrawHealth);
    plugin::patch::RedirectJump(0x5890A0, MyDrawArmor);
    plugin::patch::RedirectJump(0x589190, MyDrawBreath);
    plugin::patch::RedirectCall(0x58DD42, MyStoreCurrentStar);
    plugin::patch::RedirectCall(0x58DFD3, MyDrawWantedLevel);
    strcpy(reinterpret_cast<char *>(0x866C8C), "$-%d");
    strcpy(reinterpret_cast<char *>(0x866C94), "$%d");
}

void MobilePlayerInfo::MyDrawWeaponIcon(CPed *player, int, int, float alpha) {
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, reinterpret_cast<void *>(rwFILTERLINEAR));
    int weapModel = CWeaponInfo::GetWeaponInfo((eWeaponType)player->m_aWeapons[player->m_nActiveWeaponSlot].m_nType, 1)->m_nModelId1;
    if (weapModel <= 0) {
        float baseY = 0.0f;
        if (player == CWorld::Players[1].m_pPed)
            baseY = settings.fSecondPlayerOffsetY;
        CHud::Sprites[HUDSPRITE_FIST].Draw(CRect(SCREEN_COORD_RIGHT(settings.vecWeaponIconPosn.x), SCREEN_COORD(baseY + settings.vecWeaponIconPosn.y),
            SCREEN_COORD_RIGHT(settings.vecWeaponIconPosn.x) + SCREEN_COORD(settings.vecWeaponIconScale.x),
            SCREEN_COORD(baseY + settings.vecWeaponIconPosn.y + settings.vecWeaponIconScale.y)), CRGBA(255, 255, 255, alpha));
    }
    else {
        CBaseModelInfo *model = CModelInfo::GetModelInfo(weapModel);
        TxdDef *txd = CTxdStore::ms_pTxdPool->GetAt(model->m_nTxdIndex);
        if (txd && txd->m_pRwDictionary) {
            RwTexture *iconTex = RwTexDictionaryFindHashNamedTexture(txd->m_pRwDictionary, CKeyGen::AppendStringToKey(model->m_nKey, "ICON"));
            if (iconTex) {
                RwRenderStateSet(rwRENDERSTATEZTESTENABLE, 0);
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER, iconTex->raster);
                float baseY = 0.0f;
                if (player == CWorld::Players[1].m_pPed)
                    baseY = settings.fSecondPlayerOffsetY;
                CSprite::RenderOneXLUSprite(SCREEN_COORD_RIGHT(settings.vecWeaponIconPosn.x) + SCREEN_COORD(settings.vecWeaponIconScale.x / 2),
                    SCREEN_COORD(baseY + settings.vecWeaponIconPosn.y + settings.vecWeaponIconScale.y / 2), 1.0f, SCREEN_COORD(settings.vecWeaponIconScale.x / 2),
                    SCREEN_COORD(settings.vecWeaponIconScale.y / 2), 255, 255, 255, alpha, 1.0f, 255, 0, 0);
                RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
            }
        }
    }
}

void MobilePlayerInfo::MyDrawWeaponAmmo(CPed *player, int, int, float alpha) {
    unsigned int ammoInClip = player->m_aWeapons[player->m_nActiveWeaponSlot].m_nAmmoInClip;
    unsigned int totalAmmo = player->m_aWeapons[player->m_nActiveWeaponSlot].m_nTotalAmmo;
    eWeaponType wepType = (eWeaponType)player->m_aWeapons[player->m_nActiveWeaponSlot].m_nType;
    unsigned short maxAmmoInClip = CWeaponInfo::GetWeaponInfo(wepType, player->GetWeaponSkill())->m_nAmmoClip;
    if (maxAmmoInClip <= 1 || maxAmmoInClip >= 1000)
        sprintf(gString, "%d", totalAmmo);
    else {
        if (wepType == WEAPON_FTHROWER) {
            unsigned int total = 9999;
            if ((totalAmmo - ammoInClip) / 10 <= 9999)
                total = (totalAmmo - ammoInClip) / 10;
            sprintf(gString, "%d-%d", total, ammoInClip / 10);
        }
        else {
            unsigned int total = totalAmmo - ammoInClip;
            if (totalAmmo - ammoInClip > 9999)
                total = 9999;
            sprintf(gString, "%d-%d", total, ammoInClip);
        }
    }
    CFont::SetBackground(false, false);
    CFont::SetScale(SCREEN_MULTIPLIER(settings.vecWeaponAmmoScale.x), SCREEN_MULTIPLIER(settings.vecWeaponAmmoScale.y));
    CFont::SetAlignment(ALIGN_CENTER);
    CFont::SetCentreSize(SCREEN_WIDTH);
    CFont::SetProp(true);
    CFont::SetOutlinePosition(2);
    CFont::SetDropColor(CRGBA(0, 0, 0, 255));
    CFont::SetFontStyle(FONT_SUBTITLES);
    if ((totalAmmo - ammoInClip) >= 9999
        || CDarkel::FrenzyOnGoing()
        || wepType == WEAPON_UNARMED
        || wepType == WEAPON_DETONATOR
        || wepType >= WEAPON_DILDO1 && wepType < WEAPON_GRENADE
        || wepType == WEAPON_PARACHUTE
        || CWeaponInfo::GetWeaponInfo(wepType, 1)->m_nWeaponFire == 5
        || CWeaponInfo::GetWeaponInfo(wepType, 1)->m_nSlot <= 1)
    {
        CFont::SetOutlinePosition(0);
    }
    else {
        CFont::SetColor(HudColour.GetRGBA(HUD_COLOUR_WHITE));
        float baseY = 0.0f;
        if (player == CWorld::Players[1].m_pPed)
            baseY = settings.fSecondPlayerOffsetY;
        CFont::PrintString(SCREEN_COORD_RIGHT(settings.vecWeaponAmmoPosn.x), SCREEN_COORD(baseY + settings.vecWeaponAmmoPosn.y), gString);
        CFont::SetOutlinePosition(0);
    }
}

void MobilePlayerInfo::MySetClockScale(float scaleX, float scaleY) {
    CFont::SetScale(SCREEN_MULTIPLIER(settings.vecClockScale.x), SCREEN_MULTIPLIER(settings.vecClockScale.y));
}

void MobilePlayerInfo::MyDrawClock(float x, float y, char *text) {
    CFont::PrintString(SCREEN_COORD_RIGHT(settings.vecClockPosn.x), SCREEN_COORD(settings.vecClockPosn.y), text);
}

void MobilePlayerInfo::MySetMoneyScale(float scaleX, float scaleY) {
    CFont::SetScale(SCREEN_MULTIPLIER(settings.vecMoneyScale.x), SCREEN_MULTIPLIER(settings.vecMoneyScale.y));
}

void MobilePlayerInfo::MyDrawMoney(float x, float y, char *text) {
    CFont::PrintString(SCREEN_COORD_RIGHT(settings.vecMoneyPosn.x), SCREEN_COORD(settings.vecMoneyPosn.y), text);
}

void MobilePlayerInfo::MyDrawHealth(int playerId, int, int) {
    if (CHud::m_ItemToFlash != 4 || CTimer::m_FrameCounter & 8) {
        if (CWorld::Players[playerId].m_pPed->m_fHealth >= 10 || CTimer::m_FrameCounter & 8) {
            float barSize = static_cast<float>(CWorld::Players[playerId].m_bMaxHealth) / CStats::GetFatAndMuscleModifier((eStatModAbilities)10);
            if (barSize > 1.0f)
                barSize = 1.0f;
            float progress = CWorld::Players[playerId].m_pPed->m_fHealth / static_cast<float>(CWorld::Players[playerId].m_bMaxHealth);
            if (progress > 1.0f)
                progress = 1.0f;
            float positionY = settings.vecHealthPosn.y;
            if (playerId == 1)
                positionY += settings.fSecondPlayerOffsetY;
            DrawProgressBar_BilinearOffset_RightAlign(SCREEN_COORD_RIGHT(settings.vecHealthPosn.x), SCREEN_COORD(positionY),
                SCREEN_COORD(settings.vecHealthScale.x) * barSize, SCREEN_COORD(settings.vecHealthScale.y), progress, 1.0f,
                HudColour.GetRGBA(HUD_COLOUR_RED), CRGBA(0, 0, 0, 255));
        }
    }
}

void MobilePlayerInfo::MyDrawArmor(int playerId, int, int) {
    if ((CHud::m_ItemToFlash != 3 || CTimer::m_FrameCounter & 8) && CWorld::Players[playerId].m_pPed->m_fArmour > 1.0) {
        float progress = CWorld::Players[playerId].m_pPed->m_fArmour / static_cast<float>(CWorld::Players[playerId].m_bMaxArmour);
        if (progress > 1.0f)
            progress = 1.0f;
        float positionY = settings.vecArmorPosn.y;
        if (playerId == 1)
            positionY += settings.fSecondPlayerOffsetY;
        DrawProgressBar_BilinearOffset_RightAlign(SCREEN_COORD_RIGHT(settings.vecArmorPosn.x), SCREEN_COORD(positionY),
            SCREEN_COORD(settings.vecArmorScale.x), SCREEN_COORD(settings.vecArmorScale.y), progress, 1.0f,
            HudColour.GetRGBA(HUD_COLOUR_WHITE), CRGBA(0, 0, 0, 255));
    }
}

void MobilePlayerInfo::MyDrawBreath(int playerId, int, int) {
    if (CHud::m_ItemToFlash != 10 || CTimer::m_FrameCounter & 8) {
        float progress = CWorld::Players[playerId].m_pPed->m_pPlayerData->m_fBreath / CStats::GetFatAndMuscleModifier(STAT_MOD_AIR_IN_LUNG);
        if (progress > 1.0f)
            progress = 1.0f;
        float positionY = settings.vecBreathPosn.y;
        if (playerId == 1)
            positionY += settings.fSecondPlayerOffsetY;
        DrawProgressBar_BilinearOffset_RightAlign(SCREEN_COORD_RIGHT(settings.vecBreathPosn.x), SCREEN_COORD(positionY),
            SCREEN_COORD(settings.vecBreathScale.x), SCREEN_COORD(settings.vecBreathScale.y), progress, 1.0f,
            HudColour.GetRGBA(HUD_COLOUR_BLUELIGHT), CRGBA(0, 0, 0, 255));
    }
}

__declspec(naked) void MobilePlayerInfo::MyStoreCurrentStar(short) {
    __asm mov m_CurrentStar, edi
    __asm retn
}

void MobilePlayerInfo::MyDrawWantedLevel(float x, float y, char *text) {
    if (FindPlayerPed(-1)->m_pPlayerData->m_pWanted->m_nWantedLevel > m_CurrentStar)
        CFont::SetOutlinePosition(2);
    else
        CFont::SetOutlinePosition(0);
    CFont::SetScale(SCREEN_MULTIPLIER(settings.vecWantedLevelStarScale.x), SCREEN_MULTIPLIER(settings.vecWantedLevelStarScale.y));
    CFont::PrintString(SCREEN_COORD_MAX_X - SCREEN_COORD(settings.vecWantedLevelPosn.x) - SCREEN_COORD(settings.fWantedLevelStarSpace) * m_CurrentStar,
        SCREEN_COORD(settings.vecWantedLevelPosn.y), text);
}