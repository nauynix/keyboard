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
#include <Kaleidoscope-CharShift.h>
using namespace kaleidoscope::plugin::LEDFunctionalColor;

enum
{
    PRIMARY,
    NUMPAD,
    FUNCTION,
}; // layers

enum
{
    F11
}; // macros

const macro_t *macroAction(uint8_t macroIndex, KeyEvent &event)
{
    if (macroIndex == F11)
    {
        if (!keyToggledOff(event.state))
            return MACRO_NONE;
        return MACRO(T(F11));
    }

    return MACRO_NONE;
}

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
#define Key_Underscore LSHIFT(Key_Minus)
#define Key_QMARK LSHIFT(Key_Slash)
#define Key_PIPE LSHIFT(Key_Backslash)

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
    switch (tapDanceIndex)
    {
    case LPB:
        if (tapDanceAction == kaleidoscope::plugin::TapDance::Hold)
        {
            return tapDanceActionKeys(tapCount, tapDanceAction, Key_LCB);
        }
        else
        {
            return tapDanceActionKeys(tapCount, tapDanceAction,
                                      Key_LeftParen,
                                      Key_LeftBracket);
        }
    case RPB:
        if (tapDanceAction == kaleidoscope::plugin::TapDance::Hold)
        {
            return tapDanceActionKeys(tapCount, tapDanceAction, Key_RCB);
        }
        else
        {
            return tapDanceActionKeys(tapCount, tapDanceAction,
                                      Key_RightParen,
                                      Key_RightBracket);
        }
    case COPY:
        if (tapDanceAction == kaleidoscope::plugin::TapDance::Hold)
        {
            return tapDanceActionKeys(tapCount, tapDanceAction, LCTRL(Key_V));
        }
        else
        {
            return tapDanceActionKeys(tapCount, tapDanceAction,
                                      LCTRL(Key_C),
                                      LCTRL(Key_X));
        }
    }
}

// clang-format off

KEYMAPS(

  [PRIMARY] = KEYMAP_STACKED
  (M(F11),          Key_QMARK,      Key_Underscore, Key_AT    , Key_HASH,   Key_DOLLR,  TD(COPY),
   Key_Backtick,    Key_Quote,      Key_Comma,      Key_Period, Key_P,      Key_Y,      TD(LPB),
   Key_Tab,         Key_A,          Key_O,          Key_E,      Key_U,      Key_I,
   Key_Slash,   Key_Semicolon,  Key_Q,          Key_J,      Key_K,      Key_X,      ___,

   OSM(LeftControl), Key_Backspace,  OSM(LeftShift),  Key_Escape,
   OSL(FUNCTION),

   ___,     ___,        Key_PRCNT,  Key_CARET,  Key_AND,    Key_PIPE,Key_STAR, 
   TD(RPB), Key_F,      Key_G,      Key_C,      Key_R,      Key_L,   Key_Backslash,
            Key_D,      Key_H,      Key_T,      Key_N,      Key_S,   Key_Equals,
   ___,     Key_B,      Key_M,      Key_W,      Key_V,      Key_Z,   Key_Minus,

   Key_LeftGui, CS(0),  CS(1),   OSM(LeftAlt),
   OSL(NUMPAD)),


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
  (___, Key_F1, Key_F2,     Key_F3,         Key_F4,         Key_F5, Key_ScrollLock,
   ___, ___, ___,           Key_UpArrow,    ___,            ___,    ___,
   ___, ___, Key_LeftArrow, Key_DownArrow,  Key_RightArrow, ___,
   ___, ___, ___,           ___,            ___,            ___,    ___,
   ___, ___, ___,           ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, ___,                      Key_UpArrow,              ___,             ___,              Key_F12,
                               ___,                    Key_LeftArrow,            Key_DownArrow,            Key_RightArrow,  ___,              ___,
   Key_PcApplication,          Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             ___,              ___,
   ___, ___, ___, ___,
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
    FC_MAP_COLOR(defaultColor, cyan)
    // FC_MAP_COLOR(modifier, cyan)
    // FC_MAP_COLOR(alpha, cyan)
};

KALEIDOSCOPE_INIT_PLUGINS(
    // The boot greeting effect pulses the LED button for 10 seconds after the
    // keyboard is first connected
    BootGreetingEffect,

    // LEDControl provides support for other LED modes
    LEDControl,

    funColor,

    Macros,

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
    CharShift,
    TapDance);

void setup()
{
    // First, call Kaleidoscope's internal setup function
    Kaleidoscope.setup();

    // Set the hue of the boot greeting effect to something that will result in a
    // nice green color.
    BootGreetingEffect.hue = 85;

    LEDOff.activate();

    FC_SET_THEME(funColor, myTheme);

    CS_KEYS(
        kaleidoscope::plugin::CharShift::KeyPair(Key_Enter, Key_EXCLM),
        kaleidoscope::plugin::CharShift::KeyPair(Key_Spacebar, Key_Equals), 
    );
}

void loop()
{
    Kaleidoscope.loop();
}