# IRIS Keyboard zerodice0 Keymap Configuration
A firmware repository with additional key assignments based on the default keymap.

## Introduction to IRIS Keyboard
![IRIS Keyboard](https://keeb.io/cdn/shop/files/keyset-iris_1100x_8dba1734-1572-455b-aab2-1380992644e1.png?height=714&v=1707776710&width=952)
Iris is Keebio's most popular split keyboard that helps place your hands in a more natural position. Thousands of users have improved issues such as Repetitive Stress Injury (RSI), Carpal Tunnel Syndrome, and hypermobility through the Iris keyboard.
Iris comes in various versions, allowing users to choose a style that perfectly fits their individual needs.

You can purchase parts including the board, keycaps, and plates from [KEEB.IO](https://keeb.io/collections/all/products/iris). Since customs duties may apply for purchases over $150, it's recommended to buy only the essential parts (board and plates) from KEEB.IO and purchase keycaps and switches from AliExpress or other sources.

#### Parts to order from KEEB.IO
- PCB board
- Aluminum top/bottom plates (plate kit)
- Middle layer (optional)

#### Parts that can be ordered from AliExpress/Daiso, etc.
- Keycaps
- Switches
- Anti-slip rubber pads
- Keyboard link cable (C to C)

## Basic Keymap Setup
#### QMK Configurator
Simple keyboard settings can be configured using the [QMK Configurator](https://config.qmk.fm/#/keebio/iris/rev7/LAYOUT).

#### VIA
The default rules.mk file installed on the PCB board has the `VIA_ENABLE` option set to `FALSE`. Therefore, to use VIA, you need to download and install the appropriate firmware from [VIA Firmware](https://caniusevia.com/docs/download_firmware/) to enable key configuration using VIA.

## Keymap Configuration and QMK Firmware Build
The [QMK Firmware](https://github.com/qmk/qmk_firmware) repository explains how to configure keymaps and build QMK Firmware. You can change key assignments by modifying the `keymap.c` file and change settings by modifying the `rule.mk` file. The firmware installed on the PCB board by default does not have options such as `MOUSEKEY_ENABLE` for using mouse keys or `VIA_ENABLE` for using VIA. Therefore, to customize the keyboard to better suit your needs, it's recommended to learn how to build firmware using QMK Firmware.

## About the Firmware Distributed Through This Repository
This firmware supports **macOS, Windows, Linux, and iOS** with automatic keyboard shortcut adaptation. The firmware automatically detects your operating system and applies the appropriate shortcuts for screenshot capture, language switching, and mouse wheel direction.

The firmware follows the basic keymap installed on the PCB board and includes additional shortcut key assignments:
1. FN3 key assigned instead of HOME
2. CMD+OPT(ALT) keys assigned instead of END
3. Mission Control executed with FN1 + FN2 + 6
4. Launchpad executed with FN1 + FN2 + 7
5. Mouse cursor movement with FN3 + H,J,K,L
6. Mouse wheel scrolling with FN3 + N,M,<,>
7. Mouse button clicks with FN3 + Y,U,I,O
8. Navigate to previous/next page in CHROME with FN3 + P, DEL
9. Navigate to parent/child folder in FINDER with FN3 + ;, '
10. OS-agnostic screenshot shortcuts (adapts to your OS):
    - **SC_FULL** (FN3+8): Full screen capture
    - **SC_AREA** (FN3+6): Area selection capture
    - **SC_MENU** (FN3+9): Screenshot menu/options
    - **SC_CLIP_FULL** (FN3+Shift+8): Full screen to clipboard
    - **SC_CLIP_AREA** (FN3+7): Area selection to clipboard
11. Language switching with **LANG_SW** (FN1 + bottom-right): Adapts to OS input method
12. Mouse wheel direction (**MW_RIGHT/UP/DOWN/LEFT**) automatically adjusted per OS

## Multi-OS Compatibility

This firmware implements OS-aware keyboard shortcuts that automatically adapt to the detected operating system (macOS, Windows, Linux, iOS).

### Supported Features by OS

| Feature | macOS/iOS | Windows | Linux |
|---------|-----------|---------|-------|
| Screenshot shortcuts | ✅ Full support (Cmd+Shift+3/4/5) | ✅ Snipping Tool (Win+Shift+S) | ✅ PrtScn variants |
| Language switching | ✅ Ctrl+Space / Caps Lock | ✅ Right Alt | ✅ Shift+Space |
| Mouse wheel direction | ✅ Natural scrolling | ✅ Reversed scrolling | ✅ Reversed scrolling |
| Mouse control | ✅ Full support | ✅ Full support | ✅ Full support |

### OS-Specific Shortcuts

#### Screenshot Keycodes
- **SC_FULL**: Full screen capture
  - macOS: Cmd+Shift+3
  - Windows: Win+Shift+S (Snipping Tool)
  - Linux: PrtScn

- **SC_AREA**: Area selection
  - macOS: Cmd+Shift+4
  - Windows: Win+Shift+S
  - Linux: Shift+PrtScn

- **SC_MENU**: Screenshot menu/options
  - macOS: Cmd+Shift+5 (Screenshot menu)
  - Windows: Win+Shift+S
  - Linux: PrtScn

- **SC_CLIP_FULL**: Full screen to clipboard
  - macOS: Cmd+Ctrl+Shift+3
  - Windows: Win+Shift+S (saves to clipboard)
  - Linux: Ctrl+PrtScn

- **SC_CLIP_AREA**: Area selection to clipboard
  - macOS: Cmd+Ctrl+Shift+4
  - Windows: Win+Shift+S
  - Linux: Ctrl+Shift+PrtScn

#### Language Switching
- **LANG_SW**: OS-aware language/input switching
  - macOS: Ctrl+Space
  - iOS: Caps Lock
  - Windows: Right Alt (Language bar)
  - Linux: Shift+Space (IBus/Fcitx)

#### Mouse Wheel Direction
- **MW_RIGHT/UP/DOWN/LEFT**: Automatically adapts to OS scrolling conventions
  - macOS/iOS: Natural scrolling (wheel right = scroll right)
  - Windows/Linux: Reversed scrolling (wheel right = scroll left)

### How It Works

The firmware uses OS detection to automatically apply the correct shortcuts when you plug in the keyboard. If OS detection is not available, the firmware defaults to macOS shortcuts. All shortcuts provide continuous key press support - holding down a key will repeat the action (useful for mouse wheel scrolling with acceleration).

## Build Instructions
For detailed build instructions, please check the [QMK Documentation](https://docs.qmk.fm/#/).

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Note
For Korean documentation, please refer to [README-KR.md](README-KR.md).
