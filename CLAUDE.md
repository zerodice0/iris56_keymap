# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

**IMPORTANT - Repository Structure:**
- This directory (`keyboards/keebio/iris/keymaps/zerodice0`) is managed as a **separate Git repository**
- Repository URL: https://github.com/zerodice0/iris56_keymap
- Parent QMK firmware repository: `/Users/zerodice0/qmk_firmware` (or `/Users/zerodice0/workspace/qmk_firmware`)
- The parent QMK repository has this directory excluded in its `.gitignore`
- **All Git operations should target THIS repository (iris56_keymap), not the parent QMK repository**

This is a custom QMK firmware keymap for the **Keebio Iris Rev7** split keyboard, supporting **macOS, Windows, Linux, and iOS** with automatic OS detection and adaptation. The keymap implements a 5-layer system with layer switching via thumb keys (LEFT_UNDER/RIGHT_UNDER), tri-layer activation, and OS-agnostic shortcuts.

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

### OS-Agnostic Features

**Multi-OS Support with Automatic Detection:**
- Firmware detects OS on connection (macOS, Windows, Linux, iOS)
- Keyboard shortcuts automatically adapt to the detected OS
- All custom keycodes work consistently across operating systems

**OS-Agnostic Custom Keycodes** (defined at top of keymap.c):

- **Screenshot shortcuts**: `SC_FULL`, `SC_AREA`, `SC_MENU`, `SC_CLIP_FULL`, `SC_CLIP_AREA`
  - Automatically use Cmd+Shift (macOS), Win+Shift+S (Windows), or PrtScn variants (Linux)
- **Language switching**: `LANG_SW`
  - macOS: Ctrl+Space | iOS: Caps Lock | Windows: Right Alt | Linux: Shift+Space
- **Mouse wheel direction**: `MW_RIGHT`, `MW_UP`, `MW_DOWN`, `MW_LEFT`
  - Automatically adapts to OS scrolling conventions (natural vs reversed)
- **Browser navigation**: `GO_BACK` (Cmd+[), `GO_FORWARD` (Cmd+])
- **Finder navigation**: `GO_UPPER` (Cmd+↑), `GO_LOWER` (Cmd+↓)
- **Emoji picker**: `KC_EMOJI` (Cmd+Ctrl+Space)
- **Alt+Cmd combo**: `KC_AG` (one-shot modifier)

**Backward Compatibility:**
- Legacy keycodes (`KC_SG3`, `KC_SG4`, etc.) still supported via `#define` aliases

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

### Testing Multi-OS Compatibility

Firmware automatically adapts to detected OS (macOS, Windows, Linux, iOS):

**What to Test:**
- **OS Detection**: Verify RGB lighting shows correct color on connection (see `os_detection_task()` in keymap.c)
- **Screenshot shortcuts**: Test SC_* keycodes produce correct OS-specific behavior
- **Language switching**: Verify LANG_SW uses appropriate shortcut for each OS
- **Mouse wheel**: Check MW_* directions match OS scrolling conventions (natural on macOS/iOS, reversed on Windows/Linux)
- **Continuous key press**: Hold down custom keycodes to verify repeated events (screenshot, mouse wheel, etc.)

**OS-Specific Behavior:**
- macOS: Cmd-based shortcuts, natural scrolling, Ctrl+Space language switch
- iOS: Same as macOS except Caps Lock for language switching
- Windows: Win-based shortcuts, reversed scrolling, Right Alt language switch
- Linux: PrtScn-based screenshots, reversed scrolling, Shift+Space language switch

## Important Notes

- **Repository Management**: This is a **separate Git repository** (iris56_keymap), not part of the QMK firmware repository
- **Multi-OS Support**: Firmware supports macOS, Windows, Linux, and iOS with automatic OS detection and shortcut adaptation
- **QMK Framework**: Full QMK documentation is at https://docs.qmk.fm/
- **No External Dependencies**: Pure C code with QMK framework only; no special build tools needed beyond `qmk cli`
- **Persistent Configuration**: Use rules.mk and config.h files to enable features like MOUSEKEY_ENABLE, RGB_MATRIX_ENABLE, or OS_DETECTION_ENABLE
- **Firmware Size**: Current build uses 28,228/28,672 bytes (98.45%, 444 bytes free) - monitor size when adding features
- **Private Documentation**: `release_notes/` and `.claude/` directories are excluded from version control (see .gitignore)
