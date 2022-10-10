// -*- mode: c++ -*-
// Copyright 2016-2022 Keyboardio, inc. <jesse@keyboard.io>
// Xinyuan's Model100 Sketch
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-LEDEffect-BootGreeting.h"
#include "Kaleidoscope-IdleLEDs.h"
#include "Kaleidoscope-HostPowerManagement.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include <Kaleidoscope-LED-ActiveModColor.h>
#include <Kaleidoscope-TapDance.h>
#include "Kaleidoscope-LEDEffect-FunctionalColor.h"
using namespace kaleidoscope::plugin::LEDFunctionalColor;

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

FunctionalColor funColor(255, Fruit);

struct myTheme : public colorMapFruit
{
    // FC_MAP_COLOR(alpha, cyan)
};

KALEIDOSCOPE_INIT_PLUGINS(
    // The boot greeting effect pulses the LED button for 10 seconds after the
    // keyboard is first connected
    BootGreetingEffect,

    // LEDControl provides support for other LED modes
    LEDControl,

    funColor,

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

    ActiveModColorEffect,
    TapDance);

void setup()
{
    // First, call Kaleidoscope's internal setup function
    Kaleidoscope.setup();

    // Set the hue of the boot greeting effect to something that will result in a
    // nice green color.
    BootGreetingEffect.hue = 85;

    LEDOff.activate();

    // FC_SET_THEME(funColor, myTheme);
}

void loop()
{
    Kaleidoscope.loop();
}