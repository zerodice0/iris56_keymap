# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

This is a custom QMK firmware keymap for the **Keebio Iris Rev7** split keyboard, optimized for macOS. The keymap implements a 5-layer system with layer switching via thumb keys (LEFT_UNDER/RIGHT_UNDER), tri-layer activation, and macOS-specific shortcuts.

## Architecture & Design

### Layer System
The firmware uses **5 keyboard layers** controlled through custom keycodes and tri-layer logic:

| Layer | Name | Purpose | Trigger |
|-------|------|---------|---------|
| 0 | `_BASIC` | Default QWERTY layout | Base |
| 1 | `_LEFT_UNDER` | Number pad, arrows, symbols | Hold LEFT_UNDER thumb key |
| 2 | `_RIGHT_UNDER` | Function keys, media, RGB | Hold RIGHT_UNDER thumb key |
| 3 | `_BOTH_UNDER` | System commands (tri-layer) | Hold both LEFT_UNDER + RIGHT_UNDER |
| 4 | `_LEFT_UP` | Mouse control, macOS navigation | MO(4) from BASIC layer |

**Key Design Pattern**: Layers 1 & 2 activate independently via the thumb keys. When BOTH are held simultaneously, layer 3 automatically activates via `update_tri_layer()` logic in the `process_record_user()` function (keymap.c:119, 129).

### macOS-Specific Features

Custom key constants provide common macOS shortcuts (defined at top of keymap.c):

- **Screen capture shortcuts**: `KC_SG3/4/5`, `KC_SGC3/4` (Shift+Cmd+3/4/5 variants)
- **Browser navigation**: `GO_BACK` (Cmd+[), `GO_FORWARD` (Cmd+])
- **Finder navigation**: `GO_UPPER` (Cmd+↑), `GO_LOWER` (Cmd+↓)
- **Emoji picker**: `KC_EMOJI` (Cmd+Ctrl+Space)
- **Alt+Cmd combo**: `KC_AG` (one-shot modifier)

### Key Implementation Details

**File Structure**: Single `keymap.c` file containing:
- Layer definitions as `const uint16_t PROGMEM keymaps[][]` array
- Custom keycode enum (BASIC, LEFT_UNDER, RIGHT_UNDER, BOTH_UNDER, LEFT_UP)
- `process_record_user()` function implementing layer switching logic

**Layer Switching Logic** (keymap.c:108-146):
- LEFT_UNDER/RIGHT_UNDER keycodes trigger `layer_on()`/`layer_off()`
- Both call `update_tri_layer()` to check for simultaneous activation
- BOTH_UNDER has simpler direct layer toggle (no tri-layer check)

## Building & Testing

### Build Command
```bash
qmk compile -kb keebio/iris/rev7 -km zerodice0
```

### Flash Firmware
```bash
qmk flash -kb keebio/iris/rev7 -km zerodice0
```
(Enter bootloader mode by pressing the reset button on the keyboard)

### Test Specific Features
- **Layer switching**: Hold thumb keys and check if correct layer activates
- **Tri-layer**: Hold both thumb keys simultaneously, verify layer 3 activates
- **Macros**: Test custom keycodes (screenshot captures, browser navigation)
- **macOS integration**: Verify shortcuts work correctly in macOS environment

## Common Development Tasks

### Adding a New Custom Keycode

1. Add enum entry in the `custom_keycodes` enum (around line 13):
   ```c
   enum custom_keycodes {
     BASIC = SAFE_RANGE,
     MY_NEW_KEY,  // Add here
   };
   ```

2. Define the macro result as a `const uint16_t` near top (after line 21)

3. Handle in `process_record_user()` switch statement (add case around line 109)

4. Add to appropriate keymap layer

### Modifying a Layer

Edit the corresponding `[_LAYER_NAME] = LAYOUT(...)` block. Maintain visual alignment using comments for row separators. Reference QMK keycode documentation for available keys.

### Testing macOS Compatibility

Firmware is macOS-optimized. Test on Windows/Linux may show:
- Reversed mouse wheel scrolling
- Different behavior for Cmd/Ctrl/Alt key combinations
- Incompatible keycodes (e.g., mission control, launchpad)

## Important Notes

- **Repository Context**: This is a custom keymap within the larger QMK firmware repository. Full QMK documentation is at https://docs.qmk.fm/
- **macOS Focus**: Primary development and testing is on macOS. Windows/Linux usage may require keycode adjustments
- **No External Dependencies**: Pure C code with QMK framework only; no special build tools needed beyond `qmk cli`
- **Persistent Configuration**: Use rules.mk and config.h files (if present in this directory) to enable features like MOUSEKEY_ENABLE or VIA_ENABLE
