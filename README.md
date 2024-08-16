### Deprecated because of chrysalis. Access chrysalis.keyboard.io instead

# keyboard
Keyboardio Model100 firmware
This is a [Dvorak][dvorak]-inspired layout, with some changes here and there, to make it more suited for programming, and for a non-traditional keyboard.
![image](https://user-images.githubusercontent.com/20250559/192150492-983646fe-f65b-4d7e-8816-df294f83c393.png)


* Keys with blue front-prints are activated by tapping or holding the left palm key (also colored blue).
* Keys with red front-prints are activated by tapping or holding the right palm key (also colored red).
* The `Alt`, `Control`, `Shift` modifiers are all [one-shot][kaleidoscope:oneshot], and so are the two palm keys.
* The LED colors are governed by the [Colormap][kaleidoscope:colormap] plugin for the most part:
  - By default, the modifiers and palm keys are highlighted with different colors.
  - On different layers, the keys that have changed behaviour, are colored differently.
  - When a modifier is active, the [LED-ActiveModColor][kaleidoscope:led-activemodcolor] plugin turns it white.
  - One can also switch LEDs off.
* The top row was inspired by [Programmer Dvorak][dvorak:prg], but the symbols are arranged so that the most used ones are easier to access. The numbers are available in a numpad-like layout on a separate layer.
* The `R0C6` and `R0C9` keys are to control `tmux` and `screen`, and are dependent on my tmux setup.
* The `R1C6` and `R1C9` keys are [tap-dance][kaleidoscope:tap-dance] keys. Tapped once, they input `[{`/`}]` (without and with `Shift`, respectively). Tapped twice, they input `(`/`)`. Tapped three times, they input Japanese brackets, `「`/`」`.
* The `LEAD` keys is a [leader key][kaleidoscope:leader], with the following sequences built-in:
  - `LEAD u` starts the [symbolic unicode input](#symbolic-unicode-input) method.
  - `LEAD s` does a lot of magic to type a shruggy: `¯ \_(ツ )_/¯`.
  - `LEAD LEAD` switches to the next LED mode.
  - `LEAD r` inputs `Right Alt`, my `Compose` key of choice.
* The `R2C6` key is also a [tap-dance][kaleidoscope:tap-dance] key, which inputs `:` on a single tap, `;` otherwise.
* The `R0C0` key acts as `F11`, but triggers only on release. This is so that it can be held to go into programmable mode when re-flashing, without sending way too many `F11` held events.
* There are a few other actions one can trigger with [magic combos][kaleidoscope:magic-combos]:
  - `PALMS + AD`: Switch to the [ADORE](#adore-layer) layer.
* We are also using [mouse keys][kaleidoscope:mouse-keys], and [macros][kaleidoscope:macros] for some of the features.
* The keyboard can also communicate with the host bidirectionally, thanks to the [FocusSerial][kaleidoscope:focusserial] plugin. See [Chrysalis][chrysalis] for a simple client.

  [dvorak:prg]: http://www.kaufmann.no/roland/dvorak/
  [kaleidoscope:oneshot]:  https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-OneShot.html
  [kaleidoscope:colormap]: https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-Colormap.html
  [kaleidoscope:led-activemodcolor]: https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-LED-ActiveModColor.html
  [kaleidoscope:tap-dance]: https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-TapDance.html
  [kaleidoscope:leader]: https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-Leader.html
  [kaleidoscope:magic-combos]: https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-MagicCombo.html
  [kaleidoscope:mouse-keys]: https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-MouseKeys.html
  [kaleidoscope:macros]: https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-Macros.html
  [kaleidoscope:focusserial]: https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-FocusSerial.html
  [chrysalis]: https://github.com/keyboardio/Chrysalis
  
  
<a id="license"></a>
# License

The code is released under the terms of the GNU GPL, version 3 or later. See the
COPYING file for details.
