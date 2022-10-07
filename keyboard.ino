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
#include "Kaleidoscope-NumPad.h"
#include "Kaleidoscope-LEDEffect-BootGreeting.h"
#include "Kaleidoscope-LEDEffect-SolidColor.h"
#include "Kaleidoscope-LEDEffect-Breathe.h"
#include "Kaleidoscope-LEDEffect-Chase.h"
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LED-Stalker.h"
#include "Kaleidoscope-LED-AlphaSquare.h"
#include "Kaleidoscope-LED-Palette-Theme.h"
#include "Kaleidoscope-Colormap.h"
#include "Kaleidoscope-IdleLEDs.h"
#include "Kaleidoscope-HardwareTestMode.h"
#include "Kaleidoscope-HostPowerManagement.h"
#include "Kaleidoscope-MagicCombo.h"
#include "Kaleidoscope-USB-Quirks.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-DynamicMacros.h"
#include <Kaleidoscope-LED-ActiveModColor.h>
#include <Kaleidoscope-TapDance.h>
#include <Kaleidoscope-Unicode.h>

/** This 'enum' is a list of all the macros used by the Model 100's firmware
 * The names aren't particularly important. What is important is that each
 * is unique.
 *
 * These are the names of your macros. They'll be used in two places.
 * The first is in your keymap definitions. There, you'll use the syntax
 * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
 *
 * The second usage is in the 'switch' statement in the `macroAction` function.
 * That switch statement actually runs the code associated with a macro when
 * a macro key is pressed.
 */

enum
{
    MACRO_VERSION_INFO,
    MACRO_ANY,
};

enum
{
    PRIMARY,
    NUMPAD,
    FUNCTION,
}; // layers

#define Key_AT LSHIFT(Key_2)
#define Key_STAR LSHIFT(Key_8)
#define Key_DOLLR LSHIFT(Key_4)
#define Key_CARET LSHIFT(Key_6)
#define Key_PRCNT LSHIFT(Key_5)
#define Key_EXCLM LSHIFT(Key_1)
#define Key_HASH LSHIFT(Key_3)
#define Key_AND LSHIFT(Key_7)
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
    }
}

// clang-format off

KEYMAPS(

  [PRIMARY] = KEYMAP_STACKED
  (Key_F11,         ___,            Key_EXCLM,      Key_AT    , Key_HASH,   Key_DOLLR,  ___,
   Key_Backtick,    Key_Quote,      Key_Comma,      Key_Period, Key_P,      Key_Y,      TD(LPB),
   Key_Tab,         Key_A,          Key_O,          Key_E,      Key_U,      Key_I,
   TD(VOLD),        Key_Slash,      Key_Q,          Key_J,      Key_K,      Key_X,      Key_Semicolon,

   OSM(LeftControl), Key_Backspace,  OSM(LeftShift),  Key_Escape,
   ShiftToLayer(FUNCTION),

   ___,         Key_PRCNT,  Key_CARET,Key_AND,Key_STAR, ___,     ___,
   TD(RPB),     Key_F,      Key_G, Key_C,   Key_R,      Key_L,      Key_Backslash,
                Key_D,      Key_H, Key_T,   Key_N,      Key_S,      Key_Equals,
   Key_Minus,   Key_B,      Key_M, Key_W,   Key_V,      Key_Z,      ___,
   Key_Tab,         Key_Enter,  Key_Spacebar,   OSM(LeftAlt),
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
) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// clang-format on



// Colors names of the EGA palette, for convenient use in colormaps. Should
// match the palette definition below. Optional, one can just use the indexes
// directly, too.
enum {
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
    CRGB(0x00, 0x00, 0x00),  // [0x0] black
    CRGB(0x00, 0x00, 0xaa),  // [0x1] blue
    CRGB(0x00, 0xaa, 0x00),  // [0x2] green
    CRGB(0x00, 0xaa, 0xaa),  // [0x3] cyan
    CRGB(0xaa, 0x00, 0x00),  // [0x4] red
    CRGB(0xaa, 0x00, 0xaa),  // [0x5] magenta
    CRGB(0xaa, 0x55, 0x00),  // [0x6] brown
    CRGB(0xaa, 0xaa, 0xaa),  // [0x7] light gray
    CRGB(0x55, 0x55, 0x55),  // [0x8] dark gray
    CRGB(0x55, 0x55, 0xff),  // [0x9] bright blue
    CRGB(0x55, 0xff, 0x55),  // [0xa] bright green
    CRGB(0x55, 0xff, 0xff),  // [0xb] bright cyan
    CRGB(0xff, 0x55, 0x55),  // [0xc] bright red
    CRGB(0xff, 0x55, 0xff),  // [0xd] bright magenta
    CRGB(0xff, 0xff, 0x55),  // [0xe] yellow
    CRGB(0xff, 0xff, 0xff)   // [0xf] white
)

COLORMAPS(
    [0] = COLORMAP_STACKED
    (BLACK,   GREEN, GREEN, GREEN, GREEN, GREEN, BLUE,
     MAGENTA, CYAN,  CYAN,  CYAN,  CYAN,  CYAN,  RED,
     BROWN,   CYAN,  CYAN,  CYAN,  CYAN,  CYAN,
     BROWN,   CYAN,  CYAN,  CYAN,  CYAN,  CYAN,  RED,

     LIGHT_GRAY, RED, LIGHT_GRAY, LIGHT_GRAY,
     BLACK,

     BLACK,      BRIGHT_GREEN, BRIGHT_GREEN, BRIGHT_GREEN, BRIGHT_GREEN, BRIGHT_GREEN, BLACK,
     BRIGHT_RED, BRIGHT_CYAN,  BRIGHT_CYAN,  BRIGHT_CYAN,  BRIGHT_CYAN,  BRIGHT_CYAN,  YELLOW,
                 BRIGHT_CYAN,  BRIGHT_CYAN,  BRIGHT_CYAN,  BRIGHT_CYAN,  BRIGHT_RED,   BRIGHT_RED,
     BLACK,      BRIGHT_CYAN,  BRIGHT_CYAN,  BRIGHT_RED,   BRIGHT_RED,   BRIGHT_RED,   BRIGHT_RED,

     DARK_GRAY, BRIGHT_RED, DARK_GRAY, DARK_GRAY,
     BLACK)
)

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t key_state)
{
    if (keyToggledOn(key_state))
    {
        Macros.type(PSTR("Keyboardio Model 100 - Kaleidoscope "));
        Macros.type(PSTR(BUILD_INFORMATION));
    }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(KeyEvent &event)
{
    if (keyToggledOn(event.state))
    {
        event.key.setKeyCode(Key_A.getKeyCode() + (uint8_t)(millis() % 36));
        event.key.setFlags(0);
    }
}

/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.
    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.
    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.
 */

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event)
{
    switch (macro_id)
    {

    case MACRO_VERSION_INFO:
        versionInfoMacro(event.state);
        break;

    case MACRO_ANY:
        anyKeyMacro(event);
        break;
    }
    return MACRO_NONE;
}

// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 100.

static kaleidoscope::plugin::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::plugin::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::plugin::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::plugin::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::plugin::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::plugin::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::plugin::LEDSolidColor solidViolet(130, 0, 120);

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

/** This 'enum' is a list of all the magic combos used by the Model 100's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum
{
    // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
    // mode.
    COMBO_TOGGLE_NKRO_MODE,
    // Enter test mode
    COMBO_ENTER_TEST_MODE
};

/** Wrappers, to be used by MagicCombo. **/

/**
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index)
{
    USBQuirks.toggleKeyboardProtocol();
}

/**
 *  This enters the hardware test mode
 */
static void enterHardwareTestMode(uint8_t combo_index)
{
    HardwareTestMode.runTests();
}

/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = {R3C6, R2C6, R3C7}},
                 {.action = enterHardwareTestMode,
                  // Left Fn + Prog + LED
                  .keys = {R3C6, R0C0, R0C6}});

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
    // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
    // editable keymap in EEPROM.
    EEPROMSettings,
    EEPROMKeymap,

    // Focus allows bi-directional communication with the host, and is the
    // interface through which the keymap in EEPROM can be edited.
    Focus,

    // FocusSettingsCommand adds a few Focus commands, intended to aid in
    // changing some settings of the keyboard, such as the default layer (via the
    // `settings.defaultLayer` command)
    FocusSettingsCommand,

    // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
    // both debugging, and in backing up one's EEPROM contents.
    FocusEEPROMCommand,

    // The boot greeting effect pulses the LED button for 10 seconds after the
    // keyboard is first connected
    BootGreetingEffect,

    // The hardware test mode, which can be invoked by tapping Prog, LED and the
    // left Fn button at the same time.
    HardwareTestMode,

    // LEDControl provides support for other LED modes
    LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    LEDOff,

    // The rainbow effect changes the color of all of the keyboard's keys at the same time
    // running through all the colors of the rainbow.
    LEDRainbowEffect,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    LEDRainbowWaveEffect,

    // The chase effect follows the adventure of a blue pixel which chases a red pixel across
    // your keyboard. Spoiler: the blue pixel never catches the red pixel
    LEDChaseEffect,

    // These static effects turn your keyboard's LEDs a variety of colors
    solidRed,
    solidOrange,
    solidYellow,
    solidGreen,
    solidBlue,
    solidIndigo,
    solidViolet,

    // The breathe effect slowly pulses all of the LEDs on your keyboard
    LEDBreatheEffect,

    // The AlphaSquare effect prints each character you type, using your
    // keyboard's LEDs as a display
    AlphaSquareEffect,

    // The stalker effect lights up the keys you've pressed recently
    StalkerEffect,

    // The LED Palette Theme plugin provides a shared palette for other plugins,
    // like Colormap below
    LEDPaletteTheme,

    // The Colormap effect makes it possible to set up per-layer colormaps
    ColormapEffect,

    // The numpad plugin is responsible for lighting up the 'numpad' mode
    // with a custom LED effect
    NumPad,

    // The macros plugin adds support for macros
    Macros,

    // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
    MouseKeys,

    // The HostPowerManagement plugin allows us to turn LEDs off when then host
    // goes to sleep, and resume them when it wakes up.
    HostPowerManagement,

    // The MagicCombo plugin lets you use key combinations to trigger custom
    // actions - a bit like Macros, but triggered by pressing multiple keys at the
    // same time.
    MagicCombo,

    // The USBQuirks plugin lets you do some things with USB that we aren't
    // comfortable - or able - to do automatically, but can be useful
    // nevertheless. Such as toggling the key report protocol between Boot (used
    // by BIOSes) and Report (NKRO).
    USBQuirks,

    // The Qukeys plugin enables the "Secondary action" functionality in
    // Chrysalis. Keys with secondary actions will have their primary action
    // performed when tapped, but the secondary action when held.
    Qukeys,

    // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
    // held" functionality for layer keys.
    OneShot,
    EscapeOneShot,
    EscapeOneShotConfig,

    // Turns LEDs off after a configurable amount of idle time.
    IdleLEDs,
    PersistentIdleLEDs,

    // Enables dynamic, Chrysalis-editable macros.
    DynamicMacros,

    ActiveModColorEffect,
    TapDance);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup()
{
    // First, call Kaleidoscope's internal setup function
    Kaleidoscope.setup();

    // Set the hue of the boot greeting effect to something that will result in a
    // nice green color.
    BootGreetingEffect.hue = 85;

    // While we hope to improve this in the future, the NumPad plugin
    // needs to be explicitly told which keymap layer is your numpad layer
    NumPad.numPadLayer = NUMPAD;

    // We configure the AlphaSquare effect to use RED letters
    AlphaSquare.color = CRGB(255, 0, 0);

    // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
    // This draws more than 500mA, but looks much nicer than a dimmer effect
    LEDRainbowEffect.brightness(255);
    LEDRainbowWaveEffect.brightness(255);

    // Set the action key the test mode should listen for to Left Fn
    HardwareTestMode.setActionKey(R3C6);

    // The LED Stalker mode has a few effects. The one we like is called
    // 'BlazingTrail'. For details on other options, see
    // https://github.com/keyboardio/Kaleidoscope/blob/master/docs/plugins/LED-Stalker.md
    StalkerEffect.variant = STALKER(BlazingTrail);

    // We want to make sure that the firmware starts with LED effects off
    // This avoids over-taxing devices that don't have a lot of power to share
    // with USB devices
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
    ColormapEffect.max_layers(8);
    ColormapEffect.activate();    
    DefaultColormap.setup();

    // For Dynamic Macros, we need to reserve storage space for the editable
    // macros. A kilobyte is a reasonable default.
    DynamicMacros.reserve_storage(1024);
}

/** loop is the second of the standard Arduino sketch functions.
 * As you might expect, it runs in a loop, never exiting.
 *
 * For Kaleidoscope-based keyboard firmware, you usually just want to
 * call Kaleidoscope.loop(); and not do anything custom here.
 */

void loop()
{
    Kaleidoscope.loop();
}