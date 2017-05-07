#include "Utility.h"
#include "game_sa\CSprite2d.h"
#include <math.h>

void RotateVertices(CVector2D *rect, unsigned int numVerts, float x, float y, float angle) {
    float xold, yold;
    // angle /= 57.2957795;
    float _cos = cosf(angle);
    float _sin = sinf(angle);
    for (unsigned int i = 0; i < numVerts; i++) {
        xold = rect[i].x;
        yold = rect[i].y;
        rect[i].x = x + (xold - x) * _cos + (yold - y) * _sin;
        rect[i].y = y - (xold - x) * _sin + (yold - y) * _cos;
    }
}

float BilinearOffset(float coord) {
    return static_cast<float>(static_cast<int>(coord)) - 0.5f;
}

void DrawProgressBar_BilinearOffset_RightAlign(float x, float y, float width, float height, float progress, float borderSize,
    CRGBA const &color, CRGBA const &borderColor)
{
    // progress value is 0.0 - 1.0
    CSprite2d::DrawRect(CRect((int)(x - width - borderSize) - 0.5f, (int)(y - borderSize) - 0.5f, (int)(x + borderSize) - 0.5f,
        (int)(y + height + borderSize) - 0.5f), borderColor);
    if (progress < 1.0f)
        CSprite2d::DrawRect(CRect((int)(x - width) - 0.5f, (int)(y)-0.5f, (int)(x)-0.5f, (int)(y + height) - 0.5f),
            CRGBA(color.red, color.green, color.blue, color.alpha / 2));
    CSprite2d::DrawRect(CRect((int)(x - width) - 0.5f, (int)(y)-0.5f, (int)(x - width * (1.0 - progress)) - 0.5f,
        (int)(y + height) - 0.5f), color);
}

void DrawProgressBarWithProgressDelta_BilinearOffset(float x, float y, float width, float height, float progress,
    CRGBA const &color, float deltaProgress, CRGBA const &deltaColor)
{
    // progress value is 0.0 - 100.0
    if (progress >= 100.0f)
        progress = 100.0f;
    else {
        CSprite2d::DrawRect(CRect((int)(x)-0.5f, (int)(y)-0.5f, (int)(x + width) - 0.5f, (int)(y + height) - 0.5f),
            CRGBA(color.red, color.green, color.blue, color.alpha / 2));
    }
    if (progress > 0.0f) {
        CSprite2d::DrawRect(CRect((int)(x)-0.5f, (int)(y)-0.5f, (int)(x + width * (progress / 100.f)) - 0.5f,
            (int)(y + height) - 0.5f), color);
    }
    if (deltaProgress > 0.0f) {
        if (deltaProgress > 100.0f)
            deltaProgress = 100.0f;
        CSprite2d::DrawRect(CRect((int)(x + width * (progress / 100.f) - deltaProgress / 100.0f * width) - 0.5f, (int)(y)-0.5f,
            (int)(x + width * (progress / 100.f)) - 0.5f, (int)(y + height) - 0.5f), deltaColor);
    }
}