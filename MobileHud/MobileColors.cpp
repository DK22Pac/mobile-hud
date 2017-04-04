#include "MobileColors.h"
#include "plugin.h"
#include "game_sa\CHudColours.h"

void MobileColors::Read() {
	plugin::config_file config(PLUGIN_PATH("MobileHud\\hudcolor.dat"));
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
    HudColour.SetRGBAValue(HUD_COLOUR_RED, HudRed.red, HudRed.green, HudRed.blue, HudRed.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_GREEN, HudGreen.red, HudGreen.green, HudGreen.blue, HudGreen.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_BLUEDARK, HudBluedark.red, HudBluedark.green, HudBluedark.blue, HudBluedark.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_BLUELIGHT, HudBluelight.red, HudBluelight.green, HudBluelight.blue, HudBluelight.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_WHITE, HudWhite.red, HudWhite.green, HudWhite.blue, HudWhite.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_BLACK, HudBlack.red, HudBlack.green, HudBlack.blue, HudBlack.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_ORANGE, HudOrange.red, HudOrange.green, HudOrange.blue, HudOrange.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_PURPLE, HudPurple.red, HudPurple.green, HudPurple.blue, HudPurple.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_GREY, HudGrey.red, HudGrey.green, HudGrey.blue, HudGrey.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_REDDARK, HudReddark.red, HudReddark.green, HudReddark.blue, HudReddark.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_GREENDARK, HudGreendark.red, HudGreendark.green, HudGreendark.blue, HudGreendark.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_ORANGELIGHT, HudOrangelight.red, HudOrangelight.green, HudOrangelight.blue, HudOrangelight.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_GREYDARK, HudGreydark.red, HudGreydark.green, HudGreydark.blue, HudGreydark.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_BLUE, HudBlue.red, HudBlue.green, HudBlue.blue, HudBlue.alpha);
    HudColour.SetRGBAValue(HUD_COLOUR_YELLOW, HudYellow.red, HudYellow.green, HudYellow.blue, HudYellow.alpha);
}