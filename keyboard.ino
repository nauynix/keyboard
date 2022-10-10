// -*- mode: c++ -*-
// Copyright 2016-2022 Keyboardio, inc. <jesse@keyboard.io>
// Xinyuan's Model100 Sketch
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-LEDEffect-BootGreeting.h"
#include "Kaleidoscope-LED-Palette-Theme.h"
#include "Kaleidoscope-Colormap.h"
#include "Kaleidoscope-IdleLEDs.h"
#include "Kaleidoscope-HostPowerManagement.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include <Kaleidoscope-LED-ActiveModColor.h>
#include <Kaleidoscope-TapDance.h>
#include <Kaleidoscope-Unicode.h>
#include "Kaleidoscope-LEDEffect-FunctionalColor.h"
kaleidoscope::plugin::LEDFunctionalColor::FunctionalColor funColor;

enum
{
    PRIMARY,
    NUMPAD,
    FUNCTION,
}; // layers

#define Key_EXCLM LSHIFT(Key_1)
#define Key_AT LSHIFT(Key_2)
#define Key_HASH LSHIFT(Key_3)
#define Key_DOLLR LSHIFT(Key_4)
#define Key_PRCNT LSHIFT(Key_5)
#define Key_CARET LSHIFT(Key_6)
#define Key_AND LSHIFT(Key_7)
#define Key_STAR LSHIFT(Key_8)
#define Key_LCB LSHIFT(Key_LeftBracket)
#define Key_RCB LSHIFT(Key_RightBracket)
#define Key_Plus LSHIFT(Key_Equals)
#define Key_QMARK LSHIFT(Key_Slash)

enum
{
    PBS,   // Pipe backslash
    EQP,   // =/+
    LPB,   // (/[
    RPB,   // )/]
    COLON, // :/;
    MNP,   // Media Next/Play
    VOLD,  // Vol +/-
    AQ,    // '/"
    CLT,   // ,/<
    MUS,   // -/_
    BTT,   // `/~
    PGT,   // ./>
    COPY,  // Ctrl-c,v,x
};

void tapDanceAction(uint8_t tapDanceIndex, KeyAddr key_addr, uint8_t tapCount, kaleidoscope::plugin::TapDance::ActionType tapDanceAction)
{
    // if (tapDanceAction == kaleidoscope::plugin::TapDance::Release)
    //     xinyuan::TapDance::cancelOneShot = true;

    switch (tapDanceIndex)
    {
    case PBS:
        return tapDanceActionKeys(tapCount, tapDanceAction,
                                  Key_Pipe,
                                  Key_Backslash);
    case LPB:
        return tapDanceActionKeys(tapCount, tapDanceAction,
                                  Key_LeftParen,
                                  Key_LeftBracket,
                                  Key_LCB);
    case RPB:
        return tapDanceActionKeys(tapCount, tapDanceAction,
                                  Key_RightParen,
                                  Key_RightBracket,
                                  Key_RCB);

    case MNP:
        return tapDanceActionKeys(tapCount, tapDanceAction,
                                  Consumer_ScanNextTrack,
                                  Consumer_ScanPreviousTrack);

    case VOLD:
        return tapDanceActionKeys(tapCount, tapDanceAction,
                                  Consumer_VolumeDecrement,
                                  Consumer_VolumeIncrement,
                                  Key_Mute);

    case COPY:
        return tapDanceActionKeys(tapCount, tapDanceAction,
                                  LCTRL(Key_C),
                                  LCTRL(Key_V),
                                  LCTRL(Key_X));
    }
}

// Colors names of the EGA palette, for convenient use in colormaps. Should
// match the palette definition below. Optional, one can just use the indexes
// directly, too.
enum
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GRAY,
    DARK_GRAY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE
};

// Define an EGA palette. Conveniently, that's exactly 16 colors, just like the
// limit of LEDPaletteTheme.
PALETTE(
    CRGB(0x00, 0x00, 0x00), // [0x0] black
    CRGB(0x00, 0x00, 0xaa), // [0x1] blue
    CRGB(0x00, 0xaa, 0x00), // [0x2] green
    CRGB(0x00, 0xaa, 0xaa), // [0x3] cyan
    CRGB(0xaa, 0x00, 0x00), // [0x4] red
    CRGB(0xaa, 0x00, 0xaa), // [0x5] magenta
    CRGB(0xaa, 0x55, 0x00), // [0x6] brown
    CRGB(0xaa, 0xaa, 0xaa), // [0x7] light gray
    CRGB(0x55, 0x55, 0x55), // [0x8] dark gray
    CRGB(0x55, 0x55, 0xff), // [0x9] bright blue
    CRGB(0x55, 0xff, 0x55), // [0xa] bright green
    CRGB(0x55, 0xff, 0xff), // [0xb] bright cyan
    CRGB(0xff, 0x55, 0x55), // [0xc] bright red
    CRGB(0xff, 0x55, 0xff), // [0xd] bright magenta
    CRGB(0xff, 0xff, 0x55), // [0xe] yellow
    CRGB(0xff, 0xff, 0xff)  // [0xf] white
)

// clang-format off

KEYMAPS(

  [PRIMARY] = KEYMAP_STACKED
  (Key_F11,         ___,            Key_EXCLM,      Key_AT    , Key_HASH,   Key_DOLLR,  TD(COPY),
   Key_Backtick,    Key_Quote,      Key_Comma,      Key_Period, Key_P,      Key_Y,      TD(LPB),
   Key_Tab,         Key_A,          Key_O,          Key_E,      Key_U,      Key_I,
   TD(VOLD),        Key_Semicolon,  Key_Q,          Key_J,      Key_K,      Key_X,      Key_Slash,

   OSM(LeftControl), Key_Backspace,  OSM(LeftShift),  Key_Escape,
   ShiftToLayer(FUNCTION),

   ___,         Key_PRCNT,  Key_CARET,Key_AND,Key_STAR, ___,     ___,
   TD(RPB),     Key_F,      Key_G, Key_C,   Key_R,      Key_L,      Key_Backslash,
                Key_D,      Key_H, Key_T,   Key_N,      Key_S,      Key_Equals,
   Key_Minus,   Key_B,      Key_M, Key_W,   Key_V,      Key_Z,      ___,

   ___,         Key_Enter,  Key_Spacebar,   OSM(LeftAlt),
   ShiftToLayer(NUMPAD)),


  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   ___,  ___,  ___  , ___  , ___  , ___, ___,
   ___,  ___,  Key_1, Key_2, Key_3, ___, ___,
         Key_0,Key_4, Key_5, Key_6, ___, ___,
   ___,  ___,  Key_7, Key_8, Key_9, ___, ___,
   ___, ___, ___, ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           Key_CapsLock,
   Key_Tab,  ___,              Key_mouseUp, ___,        Key_mouseBtnR, Key_mouseWarpEnd, Key_mouseWarpNE,
   Key_Home, Key_mouseL,       Key_mouseDn, Key_mouseR, Key_mouseBtnL, Key_mouseWarpNW,
   Key_End,  Key_PrintScreen,  Key_Insert,  ___,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseWarpSE,
   ___, Key_Delete, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_UpArrow,              Key_LeftBracket, Key_RightBracket, Key_F12,
                               ___,                    Key_LeftArrow,            Key_DownArrow,            Key_RightArrow,  ___,              ___,
   Key_PcApplication,          Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   ___, ___, Key_Enter, ___,
   ___)
)

COLORMAPS(
    [0] = COLORMAP_STACKED
    (MAGENTA,   BLACK, GREEN, GREEN, GREEN, GREEN, BLUE,
     RED, CYAN,  CYAN,  CYAN,  CYAN,  CYAN,  YELLOW,
     RED,    CYAN,  CYAN,  CYAN,  CYAN,  CYAN,
     BROWN,   CYAN,  CYAN,  CYAN,  CYAN,  CYAN,  RED,

     BLUE, YELLOW, MAGENTA, WHITE,
     BLACK,

     BLACK,  GREEN, GREEN, GREEN, GREEN, BLACK, BLACK,
     YELLOW, CYAN,  CYAN,  CYAN,  CYAN,  CYAN,  RED,
             CYAN,  CYAN,  CYAN,  CYAN,  CYAN,  RED,
     RED,    CYAN,  CYAN,  CYAN,  CYAN,  CYAN,   BLACK,

     WHITE, MAGENTA,YELLOW, BLUE,
     BLACK),
)

/* Re-enable astyle's indent enforcement */
// clang-format on

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event)
{
    switch (event)
    {
    case kaleidoscope::plugin::HostPowerManagement::Suspend:
        LEDControl.disable();
        break;
    case kaleidoscope::plugin::HostPowerManagement::Resume:
        LEDControl.enable();
        break;
    case kaleidoscope::plugin::HostPowerManagement::Sleep:
        break;
    }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event)
{
    toggleLedsOnSuspendResume(event);
}

KALEIDOSCOPE_INIT_PLUGINS(
    EEPROMSettings,
    EEPROMKeymap,
    Focus,
    FocusSettingsCommand,
    FocusEEPROMCommand,

    // The boot greeting effect pulses the LED button for 10 seconds after the
    // keyboard is first connected
    BootGreetingEffect,

    // LEDControl provides support for other LED modes
    LEDControl,

    // The LED Palette Theme plugin provides a shared palette for other plugins,
    // like Colormap below
    LEDPaletteTheme,

    // The Colormap effect makes it possible to set up per-layer colormaps
    ColormapEffect,

    // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
    MouseKeys,

    // The HostPowerManagement plugin allows us to turn LEDs off when then host
    // goes to sleep, and resume them when it wakes up.
    HostPowerManagement,

    // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
    // held" functionality for layer keys.
    OneShot,
    EscapeOneShot,
    EscapeOneShotConfig,

    // Turns LEDs off after a configurable amount of idle time.
    IdleLEDs,
    PersistentIdleLEDs,

    ActiveModColorEffect,
    TapDance,

    funColor);

void setup()
{
    // First, call Kaleidoscope's internal setup function
    Kaleidoscope.setup();

    // Set the hue of the boot greeting effect to something that will result in a
    // nice green color.
    BootGreetingEffect.hue = 85;

    LEDOff.activate();

    // To make the keymap editable without flashing new firmware, we store
    // additional layers in EEPROM. For now, we reserve space for eight layers. If
    // one wants to use these layers, just set the default layer to one in EEPROM,
    // by using the `settings.defaultLayer` Focus command, or by using the
    // `keymap.onlyCustom` command to use EEPROM layers only.
    EEPROMKeymap.setup(8);

    // We need to tell the Colormap plugin how many layers we want to have custom
    // maps for. To make things simple, we set it to eight layers, which is how
    // many editable layers we have (see above).
    ColormapEffect.max_layers(1);
    ColormapEffect.activate();
    DefaultColormap.setup();
}

void loop()
{
    Kaleidoscope.loop();
}