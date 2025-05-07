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
I primarily build and use keyboard firmware in a MacOS environment. Therefore, when using the keyboard in Windows/Linux environments, there may be issues such as reverse mouse wheel scrolling or different shortcut behaviors. Please keep this in mind.

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
10. Partial screen capture with FN3 + 6
11. Partial screen capture and copy with FN3 + 7
12. Full screen capture with FN3 + 8
13. Full screen capture and copy with FN3 + 9

## Build Instructions
For detailed build instructions, please check the [QMK Documentation](https://docs.qmk.fm/#/).

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Note
For Korean documentation, please refer to [README-KR.md](README-KR.md).
