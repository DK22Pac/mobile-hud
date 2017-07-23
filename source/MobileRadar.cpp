#include "MobileRadar.h"
#include "Settings.h"
#include "Utility.h"
#include "plugin.h"
#include "game_sa\common.h"
#include "game_sa\CMenuManager.h"
#include "game_sa\CPad.h"

void MobileRadar::InstallPatches() {
    plugin::patch::RedirectCall(0x58AA25, MyDrawRadarCircle);
    plugin::patch::RedirectCall(0x58A551, MyDrawRadarPlane);
    plugin::patch::RedirectCall(0x58A649, MyDrawPlaneHeightBorder);
    plugin::patch::RedirectCall(0x58A77A, MyDrawPlaneHeight);
    plugin::patch::RedirectJump(0x583480, MyTransformRadarPointToScreenSpace);
    plugin::patch::Nop(0x58A818, 16);
    plugin::patch::Nop(0x58A8C2, 16);
    plugin::patch::Nop(0x58A96C, 16);
}

void MobileRadar::DrawRadarRectangle(CSprite2d *sprite, CRect const& rect, CRGBA const& color) {
    if (sprite) {
        if (settings.bRadarTop)
            sprite->Draw(rect, color);
        else
            sprite->Draw(CRect(rect.left, SCREEN_HEIGHT - rect.top, rect.right, SCREEN_HEIGHT - rect.bottom), color);
    }
    else {
        if (settings.bRadarTop)
            CSprite2d::DrawRect(rect, color);
        else
            CSprite2d::DrawRect(CRect(rect.left, SCREEN_HEIGHT - rect.top, rect.right, SCREEN_HEIGHT - rect.bottom), color);
    }
}

float SCREEN(float a)
{
    RwInt32 base;
    if (RsGlobal.maximumWidth <= RsGlobal.maximumHeight) {
        base = RsGlobal.maximumWidth;
    }
    else {
        base = RsGlobal.maximumHeight;
    }
    return a * (float)base / 900.0f;
    return a*(float)RsGlobal.maximumHeight / 900.0f;
}

void MobileRadar::MyTransformRadarPointToScreenSpace(CVector2D *out, CVector2D *in) {
    CPed *player = FindPlayerPed(-1);
    CPad *pad = CPad::GetPad(0);
    __asm push edx

    if (FrontEndMenuManager.drawRadarOrMap) {
        out->x = FrontEndMenuManager.m_fMapZoom * in->x + FrontEndMenuManager.m_fMapBaseX;
        out->y = FrontEndMenuManager.m_fMapBaseY - FrontEndMenuManager.m_fMapZoom * in->y;
    }
    else {
        if (settings.bRadarTop)
            out->x = SCREEN_COORD(settings.vecRadarPosn.x) + in->x * SCREEN_COORD(settings.fRadarWidthHalf);
        else
        if (!settings.IsStatsBoxOpen)
            out->x = SCREEN_COORD(settings.vecRadarPosn.x) + in->x * SCREEN_COORD(settings.fRadarWidthHalf);
        else
            out->x = SCREEN_COORD(settings.vecRadarPosn.x + 270.0f) + in->x * SCREEN_COORD(settings.fRadarWidthHalf);

        if (settings.bRadarTop)
            out->y = SCREEN_COORD(settings.vecRadarPosn.y) - in->y * SCREEN_COORD(settings.fRadarHeightHalf);
        else
            out->y = SCREEN_COORD_MAX_Y - SCREEN_COORD(settings.vecRadarPosn.y) - in->y * SCREEN_COORD(settings.fRadarHeightHalf);
    }

    __asm pop edx
}

void __fastcall MobileRadar::MyDrawRadarCircle(CSprite2d *sprite, int, CRect const &rect, CRGBA const &color) {
    CPed *player = FindPlayerPed(-1);
    CPad *pad = CPad::GetPad(0);

    if (settings.bRadarTop) {
        DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.vecRadarPosn.x - settings.fRadarBorderWidthHalf),
            SCREEN_COORD(settings.vecRadarPosn.y - settings.fRadarBorderHeightHalf),
            SCREEN_COORD(settings.vecRadarPosn.x),
            SCREEN_COORD(settings.vecRadarPosn.y)),
            CRGBA(255, 255, 255, 255));
        DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.vecRadarPosn.x + settings.fRadarBorderWidthHalf), SCREEN_COORD(settings.vecRadarPosn.y - settings.fRadarBorderHeightHalf),
            SCREEN_COORD(settings.vecRadarPosn.x), SCREEN_COORD(settings.vecRadarPosn.y)), CRGBA(255, 255, 255, 255));
        DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.vecRadarPosn.x - settings.fRadarBorderWidthHalf), SCREEN_COORD(settings.vecRadarPosn.y + settings.fRadarBorderHeightHalf),
            SCREEN_COORD(settings.vecRadarPosn.x), SCREEN_COORD(settings.vecRadarPosn.y)), CRGBA(255, 255, 255, 255));
        DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.vecRadarPosn.x + settings.fRadarBorderWidthHalf), SCREEN_COORD(settings.vecRadarPosn.y + settings.fRadarBorderHeightHalf),
            SCREEN_COORD(settings.vecRadarPosn.x), SCREEN_COORD(settings.vecRadarPosn.y)), CRGBA(255, 255, 255, 255));
    }
    else
    if (!settings.IsStatsBoxOpen) {
        DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.vecRadarPosn.x - settings.fRadarBorderWidthHalf),
            SCREEN_COORD(settings.vecRadarPosn.y - settings.fRadarBorderHeightHalf),
            SCREEN_COORD(settings.vecRadarPosn.x),
            SCREEN_COORD(settings.vecRadarPosn.y)),
            CRGBA(255, 255, 255, 255));
        DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.vecRadarPosn.x + settings.fRadarBorderWidthHalf), SCREEN_COORD(settings.vecRadarPosn.y - settings.fRadarBorderHeightHalf),
            SCREEN_COORD(settings.vecRadarPosn.x), SCREEN_COORD(settings.vecRadarPosn.y)), CRGBA(255, 255, 255, 255));
        DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.vecRadarPosn.x - settings.fRadarBorderWidthHalf), SCREEN_COORD(settings.vecRadarPosn.y + settings.fRadarBorderHeightHalf),
            SCREEN_COORD(settings.vecRadarPosn.x), SCREEN_COORD(settings.vecRadarPosn.y)), CRGBA(255, 255, 255, 255));
        DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.vecRadarPosn.x + settings.fRadarBorderWidthHalf), SCREEN_COORD(settings.vecRadarPosn.y + settings.fRadarBorderHeightHalf),
            SCREEN_COORD(settings.vecRadarPosn.x), SCREEN_COORD(settings.vecRadarPosn.y)), CRGBA(255, 255, 255, 255));
    }
    else {
        DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.vecRadarPosn.x + 270.0f - settings.fRadarBorderWidthHalf),
            SCREEN_COORD(settings.vecRadarPosn.y - settings.fRadarBorderHeightHalf),
            SCREEN_COORD(settings.vecRadarPosn.x + 270.0f),
            SCREEN_COORD(settings.vecRadarPosn.y)),
            CRGBA(255, 255, 255, 255));
        DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.vecRadarPosn.x + 270.0f + settings.fRadarBorderWidthHalf), SCREEN_COORD(settings.vecRadarPosn.y - settings.fRadarBorderHeightHalf),
            SCREEN_COORD(settings.vecRadarPosn.x + 270.0f), SCREEN_COORD(settings.vecRadarPosn.y)), CRGBA(255, 255, 255, 255));
        DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.vecRadarPosn.x + 270.0f - settings.fRadarBorderWidthHalf), SCREEN_COORD(settings.vecRadarPosn.y + settings.fRadarBorderHeightHalf),
            SCREEN_COORD(settings.vecRadarPosn.x + 270.0f), SCREEN_COORD(settings.vecRadarPosn.y)), CRGBA(255, 255, 255, 255));
        DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.vecRadarPosn.x + 270.0f + settings.fRadarBorderWidthHalf), SCREEN_COORD(settings.vecRadarPosn.y + settings.fRadarBorderHeightHalf),
            SCREEN_COORD(settings.vecRadarPosn.x + 270.0f), SCREEN_COORD(settings.vecRadarPosn.y)), CRGBA(255, 255, 255, 255));
    }
}

void __fastcall MobileRadar::MyDrawRadarPlane(CSprite2d *sprite, int, float x1, float y1, float x2, float y2, float x3,
    float y3, float x4, float y4, CRGBA const &color)
{
    CVector2D posn[4];
    posn[0].x = SCREEN_COORD(settings.vecRadarPosn.x) - SCREEN_COORD(settings.fRadarBorderWidthHalf);
    posn[0].y = SCREEN_COORD(settings.vecRadarPosn.y) + SCREEN_COORD(settings.fRadarBorderHeightHalf);
    posn[1].x = SCREEN_COORD(settings.vecRadarPosn.x) + SCREEN_COORD(settings.fRadarBorderWidthHalf);
    posn[1].y = SCREEN_COORD(settings.vecRadarPosn.y) + SCREEN_COORD(settings.fRadarBorderHeightHalf);
    posn[2].x = SCREEN_COORD(settings.vecRadarPosn.x) - SCREEN_COORD(settings.fRadarBorderWidthHalf);
    posn[2].y = SCREEN_COORD(settings.vecRadarPosn.y) - SCREEN_COORD(settings.fRadarBorderHeightHalf);
    posn[3].x = SCREEN_COORD(settings.vecRadarPosn.x) + SCREEN_COORD(settings.fRadarBorderWidthHalf);
    posn[3].y = SCREEN_COORD(settings.vecRadarPosn.y) - SCREEN_COORD(settings.fRadarBorderHeightHalf);
    CMatrix *planeMat = FindPlayerVehicle(-1, false)->m_matrix;
    float angle = atan2f(planeMat->at.z, -planeMat->right.z) - 1.57079632679f;
    RotateVertices(posn, 4, SCREEN_COORD(settings.vecRadarPosn.x), SCREEN_COORD(settings.vecRadarPosn.y), settings.bRadarTop ? angle : -angle);
    if (settings.bRadarTop)
        sprite->Draw(posn[0].x, posn[0].y, posn[1].x, posn[1].y, posn[2].x, posn[2].y, posn[3].x, posn[3].y, CRGBA(255, 255, 255, 255));
    else {
        sprite->Draw(posn[2].x, SCREEN_COORD_MAX_Y - posn[2].y - SCREEN_COORD(1.0f),
            posn[3].x, SCREEN_COORD_MAX_Y - posn[3].y - SCREEN_COORD(1.0f),
            posn[0].x, SCREEN_COORD_MAX_Y - posn[0].y - SCREEN_COORD(1.0f),
            posn[1].x, SCREEN_COORD_MAX_Y - posn[1].y - SCREEN_COORD(1.0f),
            CRGBA(255, 255, 255, 255));
    }
}

void MobileRadar::MyDrawPlaneHeightBorder(CRect const& rect, CRGBA const& color) {
    CPed *player = FindPlayerPed();
    CPad *pad = CPad::GetPad(0);
    if (settings.bRadarTop) {
        DrawRadarRectangle(NULL, CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x)), BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.y)),
            BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x) + SCREEN_COORD(settings.vecPlaneRadarSize.x)), BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.y)
                + SCREEN_COORD(settings.vecPlaneRadarSize.y))), CRGBA(0, 0, 0, 255));
        DrawRadarRectangle(NULL, CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x)),
            BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y)),
            BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.x)),
            BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y))), CRGBA(120, 120, 120, 255));
    }
    else {
        if (!settings.IsStatsBoxOpen) {
            DrawRadarRectangle(NULL, CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x)), BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.y)),
                BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x) + SCREEN_COORD(settings.vecPlaneRadarSize.x)), BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.y)
                    + SCREEN_COORD(settings.vecPlaneRadarSize.y))), CRGBA(0, 0, 0, 255));
            DrawRadarRectangle(NULL, CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x)),
                BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y)),
                BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.x)),
                BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y))), CRGBA(120, 120, 120, 255));
        }
        else {
            DrawRadarRectangle(NULL, CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x + 270.0f)), BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.y)),
                BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x + 270.0f) + SCREEN_COORD(settings.vecPlaneRadarSize.x)), BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.y)
                    + SCREEN_COORD(settings.vecPlaneRadarSize.y))), CRGBA(0, 0, 0, 255));
            DrawRadarRectangle(NULL, CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x + 270.0f)),
                BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y)),
                BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x + 270.0f) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.x)),
                BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y))), CRGBA(120, 120, 120, 255));
        }
    }
}

void MobileRadar::MyDrawPlaneHeight(CRect const& rect, CRGBA const& color) {
    float playerHeight = 0.0f;
    float blackLineBaseY = 0.0f;
    CPed *playa = FindPlayerPed();
    CPad *pad = CPad::GetPad(0);
    CVehicle *playaVeh = FindPlayerVehicle(-1, false);
    if (playaVeh)
        playerHeight = playaVeh->GetPosition().z;
    else if (playa)
        playerHeight = playa->GetPosition().z;
    if (playerHeight < 0.0f)
        playerHeight = 0.0f;
    else
        playerHeight /= 900.0f;
    if (playerHeight > 1.0f)
        playerHeight = 1.0f;
    if (playerHeight > 0.0f) {
        if (settings.bRadarTop) {
            CSprite2d::DrawRect(CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x)),
                BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y) * (1.0f - playerHeight)),
                BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.x)),
                BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y))), CRGBA(255, 255, 255, 255));
        }
        else {
            if (!pad->GetDisplayVitalStats(playa) || FindPlayerVehicle(-1, 0)) {
                CSprite2d::DrawRect(CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x)),
                    BilinearOffset(SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) -
                        SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y) * playerHeight),
                    BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.x)),
                    BilinearOffset(SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y))), CRGBA(255, 255, 255, 255));
            }
            else {
                CSprite2d::DrawRect(CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x + 270.0f)),
                    BilinearOffset(SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) -
                        SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y) * playerHeight),
                    BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x + 270.0f) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.x)),
                    BilinearOffset(SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y))), CRGBA(255, 255, 255, 255));
            }
        }
    }
    if (settings.bRadarTop) {
        blackLineBaseY = playerHeight * (settings.vecPlaneRadarLightPartSize.y) > 4.0f ?
            SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y) * (1.0f - playerHeight) :
            SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y) - SCREEN_COORD(4.0f);
        CSprite2d::DrawRect(CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x) - SCREEN_COORD(3.0f)), BilinearOffset(blackLineBaseY),
            BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x) + SCREEN_COORD(settings.vecPlaneRadarSize.x) + SCREEN_COORD(3.0f)),
            BilinearOffset(blackLineBaseY + SCREEN_COORD(4.0f))), CRGBA(0, 0, 0, 255));
    }
    else {
        if (!pad->GetDisplayVitalStats(playa) || FindPlayerVehicle(-1, 0)) {
            blackLineBaseY = playerHeight * (settings.vecPlaneRadarLightPartSize.y) > 4.0f ?
                SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) - SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y) * playerHeight :
                SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) - SCREEN_COORD(4.0f);
            CSprite2d::DrawRect(CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x) - SCREEN_COORD(3.0f)),
                BilinearOffset(blackLineBaseY), BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x) + SCREEN_COORD(settings.vecPlaneRadarSize.x) + SCREEN_COORD(3.0f)),
                BilinearOffset(blackLineBaseY + SCREEN_COORD(4.0f))), CRGBA(0, 0, 0, 255));
        }
        else {
            blackLineBaseY = playerHeight * (settings.vecPlaneRadarLightPartSize.y) > 4.0f ?
                SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) - SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y) * playerHeight :
                SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) - SCREEN_COORD(4.0f);
            CSprite2d::DrawRect(CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x + 270.0f) - SCREEN_COORD(3.0f)),
                BilinearOffset(blackLineBaseY), BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x + 270.0f) + SCREEN_COORD(settings.vecPlaneRadarSize.x) + SCREEN_COORD(3.0f)),
                BilinearOffset(blackLineBaseY + SCREEN_COORD(4.0f))), CRGBA(0, 0, 0, 255));
        }
    }
}