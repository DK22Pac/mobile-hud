#include "MobileColors.h"
#include "plugin.h"
#include "CHudColours.h"

using namespace plugin;

void MobileColors::Read() {
    config_file config(PLUGIN_PATH("MobileHud\\hudcolor.dat"));
    CRGBA HudRed         = config["HUD_COLOUR_RED"        ].asRGBA(CRGBA(255,  38,  41, 255));
    CRGBA HudGreen       = config["HUD_COLOUR_GREEN"      ].asRGBA(CRGBA( 82, 157,  67, 255));
    CRGBA HudBluedark    = config["HUD_COLOUR_BLUEDARK"   ].asRGBA(CRGBA( 50,  60, 127, 255));
    CRGBA HudBluelight   = config["HUD_COLOUR_BLUELIGHT"  ].asRGBA(CRGBA(172, 203, 241, 255));
    CRGBA HudWhite       = config["HUD_COLOUR_WHITE"      ].asRGBA(CRGBA(255, 255, 255, 255));
    CRGBA HudBlack       = config["HUD_COLOUR_BLACK"      ].asRGBA(CRGBA(  0,   0,   0, 255));
    CRGBA HudOrange      = config["HUD_COLOUR_ORANGE"     ].asRGBA(CRGBA(215, 146,  24, 255));
    CRGBA HudPurple      = config["HUD_COLOUR_PURPLE"     ].asRGBA(CRGBA(168, 110, 252, 255));
    CRGBA HudGrey        = config["HUD_COLOUR_GREY"       ].asRGBA(CRGBA(150, 150, 150, 255));
    CRGBA HudReddark     = config["HUD_COLOUR_REDDARK"    ].asRGBA(CRGBA(104,  15,  17, 255));
    CRGBA HudGreendark   = config["HUD_COLOUR_GREENDARK"  ].asRGBA(CRGBA( 38,  71,  31, 255));
    CRGBA HudOrangelight = config["HUD_COLOUR_ORANGELIGHT"].asRGBA(CRGBA(226, 192,  99, 255));
    CRGBA HudGreydark    = config["HUD_COLOUR_GREYDARK"   ].asRGBA(CRGBA( 74,  90, 107, 255));
    CRGBA HudBlue        = config["HUD_COLOUR_BLUE"       ].asRGBA(CRGBA( 20,  25, 200, 255));
    CRGBA HudYellow      = config["HUD_COLOUR_YELLOW"     ].asRGBA(CRGBA(255, 255,   0, 255));
    HudColour.SetRGBAValue(HUD_COLOUR_RED, HudRed.r, HudRed.g, HudRed.b, HudRed.a);
    HudColour.SetRGBAValue(HUD_COLOUR_GREEN, HudGreen.r, HudGreen.g, HudGreen.b, HudGreen.a);
    HudColour.SetRGBAValue(HUD_COLOUR_BLUEDARK, HudBluedark.r, HudBluedark.g, HudBluedark.b, HudBluedark.a);
    HudColour.SetRGBAValue(HUD_COLOUR_BLUELIGHT, HudBluelight.r, HudBluelight.g, HudBluelight.b, HudBluelight.a);
    HudColour.SetRGBAValue(HUD_COLOUR_WHITE, HudWhite.r, HudWhite.g, HudWhite.b, HudWhite.a);
    HudColour.SetRGBAValue(HUD_COLOUR_BLACK, HudBlack.r, HudBlack.g, HudBlack.b, HudBlack.a);
    HudColour.SetRGBAValue(HUD_COLOUR_ORANGE, HudOrange.r, HudOrange.g, HudOrange.b, HudOrange.a);
    HudColour.SetRGBAValue(HUD_COLOUR_PURPLE, HudPurple.r, HudPurple.g, HudPurple.b, HudPurple.a);
    HudColour.SetRGBAValue(HUD_COLOUR_GREY, HudGrey.r, HudGrey.g, HudGrey.b, HudGrey.a);
    HudColour.SetRGBAValue(HUD_COLOUR_REDDARK, HudReddark.r, HudReddark.g, HudReddark.b, HudReddark.a);
    HudColour.SetRGBAValue(HUD_COLOUR_GREENDARK, HudGreendark.r, HudGreendark.g, HudGreendark.b, HudGreendark.a);
    HudColour.SetRGBAValue(HUD_COLOUR_ORANGELIGHT, HudOrangelight.r, HudOrangelight.g, HudOrangelight.b, HudOrangelight.a);
    HudColour.SetRGBAValue(HUD_COLOUR_GREYDARK, HudGreydark.r, HudGreydark.g, HudGreydark.b, HudGreydark.a);
    HudColour.SetRGBAValue(HUD_COLOUR_BLUE, HudBlue.r, HudBlue.g, HudBlue.b, HudBlue.a);
    HudColour.SetRGBAValue(HUD_COLOUR_YELLOW, HudYellow.r, HudYellow.g, HudYellow.b, HudYellow.a);
}
