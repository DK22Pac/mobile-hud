#pragma once

class MobileStatsBox {
public:
    static void InstallPatches();
    static void DrawVitalStats();
    static void DrawRect(CRect const& rect, bool bFading, CRGBA const& color);

private:
    static void DrawRect(float x, float y, float width, float height, bool bFading, CRGBA const &color) {
        DrawRect(CRect(x, y, x + width, y + height), bFading, (color));
    }
};