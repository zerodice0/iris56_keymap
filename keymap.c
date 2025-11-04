// Copyright 2023 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdint.h>
#include QMK_KEYBOARD_H

#ifdef RGB_MATRIX_ENABLE
    #include "rgb_matrix.h"
#endif

/**
 * ============================================================================
 * OS-AGNOSTIC KEYBOARD SHORTCUTS
 * ============================================================================
 *
 * This keymap implements OS-aware keyboard shortcuts that automatically adapt
 * to the detected operating system (macOS, Windows, Linux).
 *
 * CUSTOM KEYCODES:
 * ---------------
 * SC_FULL      - Screenshot: Full screen
 *                macOS:   Cmd+Shift+3
 *                Windows: Win+Shift+S (Snipping Tool)
 *                Linux:   PrtScn
 *
 * SC_AREA      - Screenshot: Area selection
 *                macOS:   Cmd+Shift+4
 *                Windows: Win+Shift+S (Snipping Tool)
 *                Linux:   Shift+PrtScn
 *
 * SC_MENU      - Screenshot: Menu/Options
 *                macOS:   Cmd+Shift+5 (Screenshot menu)
 *                Windows: Win+Shift+S (Snipping Tool)
 *                Linux:   PrtScn
 *
 * SC_CLIP_FULL - Screenshot to clipboard: Full screen
 *                macOS:   Cmd+Ctrl+Shift+3
 *                Windows: Win+Shift+S (saves to clipboard)
 *                Linux:   Ctrl+PrtScn
 *
 * SC_CLIP_AREA - Screenshot to clipboard: Area selection
 *                macOS:   Cmd+Ctrl+Shift+4
 *                Windows: Win+Shift+S (saves to clipboard)
 *                Linux:   Ctrl+Shift+PrtScn
 *
 * LANG_SW      - Language/Input source switching
 *                macOS:   Ctrl+Space
 *                iOS:     Caps Lock
 *                Windows: Right Alt
 *                Linux:   Shift+Space
 *
 * MW_RIGHT     - Mouse wheel right
 *                macOS/iOS:   Wheel right
 *                Windows/Linux: Wheel left (reversed)
 *
 * MW_UP        - Mouse wheel up
 *                macOS/iOS:   Wheel up
 *                Windows/Linux: Wheel down (reversed)
 *
 * MW_DOWN      - Mouse wheel down
 *                macOS/iOS:   Wheel down
 *                Windows/Linux: Wheel up (reversed)
 *
 * MW_LEFT      - Mouse wheel left
 *                macOS/iOS:   Wheel left
 *                Windows/Linux: Wheel right (reversed)
 *
 * USAGE NOTES:
 * -----------
 * - OS detection happens automatically after USB connection
 * - RGB Matrix provides visual feedback (White=macOS, Blue=Windows, Green=Linux)
 * - If OS not detected, defaults to macOS shortcuts
 * - User can manually place these keycodes anywhere in their keymap
 *
 * MIGRATION FROM OLD SHORTCUTS:
 * ----------------------------
 * KC_SG3   -> SC_FULL       (Full screen screenshot)
 * KC_SG4   -> SC_AREA       (Area selection screenshot)
 * KC_SG5   -> SC_MENU       (Screenshot menu)
 * KC_SGC3  -> SC_CLIP_FULL  (Full screen to clipboard)
 * KC_SGC4  -> SC_CLIP_AREA  (Area to clipboard)
 *
 * ============================================================================
 */

#define _BASIC 0
#define _LEFT_UNDER 1
#define _RIGHT_UNDER 2
#define _BOTH_UNDER 3
#define _LEFT_UP 4

enum custom_keycodes {
  BASIC = SAFE_RANGE,
  LEFT_UNDER,
  RIGHT_UNDER,
  BOTH_UNDER,
  LEFT_UP,
  // OS-agnostic screenshot keycodes
  SC_FULL,      // Screenshot: Full screen capture
  SC_AREA,      // Screenshot: Area selection
  SC_MENU,      // Screenshot: Menu/Options (macOS only)
  SC_CLIP_FULL, // Screenshot to clipboard: Full screen
  SC_CLIP_AREA, // Screenshot to clipboard: Area selection
  // OS-agnostic language switching
  LANG_SW,      // Language/Input source switching
  // OS-agnostic mouse wheel keycodes
  MW_RIGHT,     // Mouse wheel right
  MW_UP,        // Mouse wheel up
  MW_DOWN,      // Mouse wheel down
  MW_LEFT,      // Mouse wheel left
};

// Legacy macOS-specific constants (kept for backward compatibility in keymap)
const uint16_t KC_EMOJI = LGUI(LCTL(KC_SPACE));
const uint16_t KC_AG = OSM(MOD_LALT|MOD_LGUI);

const uint16_t GO_BACK = LGUI(KC_LBRC); // Go Backward on MacOS Browser
const uint16_t GO_FORWARD = LGUI(KC_RBRC); // Go Forward on MacOS Browser
const uint16_t GO_UPPER = LGUI(KC_UP); // Go Upper on MacOS Finder
const uint16_t GO_LOWER = LGUI(KC_DOWN); // Go Lower on MacOS Finder

const uint16_t TAP_P = LGUI(KC_GRV);

// BACKWARD COMPATIBILITY: Old macOS-specific screenshot shortcuts
// These aliases map old keycodes to new OS-agnostic custom keycodes
// User can replace these in keymap with SC_* keycodes directly
#define KC_SG3  SC_FULL        // Full screen screenshot
#define KC_SG4  SC_AREA        // Area selection screenshot
#define KC_SG5  SC_MENU        // Screenshot menu
#define KC_SGC3 SC_CLIP_FULL   // Full screen to clipboard
#define KC_SGC4 SC_CLIP_AREA   // Area selection to clipboard

// OS detection variables for automatic mouse wheel direction adjustment
static os_variant_t current_os = OS_UNSURE;
static bool os_detected = false;

// ============================================================================
// OS-Agnostic Helper Functions
// ============================================================================
// These functions return the appropriate keycode for each OS

/**
 * get_screenshot_full - Full screen screenshot
 * macOS:   Cmd+Shift+3
 * Windows: Win+Shift+S (Snipping Tool)
 * Linux:   PrtScn
 */
uint16_t get_screenshot_full(void) {
    if (!os_detected) {
        return LSG(KC_3);  // Default to macOS
    }

    switch (current_os) {
        case OS_MACOS:
        case OS_IOS:
            return LSG(KC_3);  // Cmd+Shift+3
        case OS_WINDOWS:
            return G(S(KC_S));  // Win+Shift+S
        case OS_LINUX:
            return KC_PSCR;     // PrtScn
        default:
            return LSG(KC_3);   // Fallback to macOS
    }
}

/**
 * get_screenshot_area - Area selection screenshot
 * macOS:   Cmd+Shift+4
 * Windows: Win+Shift+S (Snipping Tool)
 * Linux:   Shift+PrtScn
 */
uint16_t get_screenshot_area(void) {
    if (!os_detected) {
        return LSG(KC_4);  // Default to macOS
    }

    switch (current_os) {
        case OS_MACOS:
        case OS_IOS:
            return LSG(KC_4);   // Cmd+Shift+4
        case OS_WINDOWS:
            return G(S(KC_S));  // Win+Shift+S (same as full screen)
        case OS_LINUX:
            return S(KC_PSCR);  // Shift+PrtScn
        default:
            return LSG(KC_4);   // Fallback to macOS
    }
}

/**
 * get_screenshot_menu - Screenshot menu/options
 * macOS:   Cmd+Shift+5 (Screenshot menu)
 * Windows: Not available (uses Snipping Tool)
 * Linux:   Not available
 */
uint16_t get_screenshot_menu(void) {
    if (!os_detected) {
        return LSG(KC_5);  // Default to macOS
    }

    switch (current_os) {
        case OS_MACOS:
        case OS_IOS:
            return LSG(KC_5);   // Cmd+Shift+5
        case OS_WINDOWS:
            return G(S(KC_S));  // Win+Shift+S (best alternative)
        case OS_LINUX:
            return KC_PSCR;     // PrtScn (best alternative)
        default:
            return LSG(KC_5);   // Fallback to macOS
    }
}

/**
 * get_screenshot_clip_full - Full screen screenshot to clipboard
 * macOS:   Cmd+Ctrl+Shift+3
 * Windows: Win+Shift+S (goes to clipboard by default)
 * Linux:   Ctrl+PrtScn
 */
uint16_t get_screenshot_clip_full(void) {
    if (!os_detected) {
        return LSG(LCTL(KC_3));  // Default to macOS
    }

    switch (current_os) {
        case OS_MACOS:
        case OS_IOS:
            return LSG(LCTL(KC_3));  // Cmd+Ctrl+Shift+3
        case OS_WINDOWS:
            return G(S(KC_S));       // Win+Shift+S
        case OS_LINUX:
            return C(KC_PSCR);       // Ctrl+PrtScn
        default:
            return LSG(LCTL(KC_3));  // Fallback to macOS
    }
}

/**
 * get_screenshot_clip_area - Area selection screenshot to clipboard
 * macOS:   Cmd+Ctrl+Shift+4
 * Windows: Win+Shift+S (goes to clipboard by default)
 * Linux:   Ctrl+Shift+PrtScn
 */
uint16_t get_screenshot_clip_area(void) {
    if (!os_detected) {
        return LSG(LCTL(KC_4));  // Default to macOS
    }

    switch (current_os) {
        case OS_MACOS:
        case OS_IOS:
            return LSG(LCTL(KC_4));  // Cmd+Ctrl+Shift+4
        case OS_WINDOWS:
            return G(S(KC_S));       // Win+Shift+S
        case OS_LINUX:
            return C(S(KC_PSCR));    // Ctrl+Shift+PrtScn
        default:
            return LSG(LCTL(KC_4));  // Fallback to macOS
    }
}

/**
 * get_language_switch - Language/Input source switching
 * macOS:   Ctrl+Space (Spotlight/Input switching)
 * Windows: Right Alt (Language bar)
 * Linux:   Left Shift + Space (common default)
 */
uint16_t get_language_switch(void) {
    if (!os_detected) {
        return LGUI(KC_SPC);  // Default to macOS
    }

    switch (current_os) {
        case OS_MACOS:
            return LCTL(KC_SPC);   // Ctrl+Space
        case OS_IOS:
            return KC_CAPS; // Caps Lock
        case OS_WINDOWS:
            return KC_RALT;      // Right Alt
        case OS_LINUX:
            return LSFT(KC_SPC);      // Left Shift + Space
        default:
            return LCTL(KC_SPC);   // Fallback to Ctrl+Space
    }
}

/**
 * get_mouse_wheel - Mouse wheel direction mapping
 * macOS/iOS: Natural scrolling (MS_WHLR, MS_WHLU, MS_WHLD, MS_WHLL)
 * Windows/Linux: Reversed scrolling (MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR)
 */
uint16_t get_mouse_wheel(uint16_t direction) {
    bool is_mac = (current_os == OS_MACOS || current_os == OS_IOS);

    switch (direction) {
        case MW_RIGHT:
            return is_mac ? MS_WHLR : MS_WHLL;
        case MW_UP:
            return is_mac ? MS_WHLU : MS_WHLD;
        case MW_DOWN:
            return is_mac ? MS_WHLD : MS_WHLU;
        case MW_LEFT:
            return is_mac ? MS_WHLL : MS_WHLR;
        default:
            return KC_NO;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASIC] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    MO(4),            KC_AG,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI, LEFT_UNDER,KC_ENT,              KC_SPC,   RIGHT_UNDER, KC_RALT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LEFT_UNDER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,  _______, KC_LEFT, KC_RGHT, KC_UP,   KC_LBRC,                            KC_RBRC, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_PIPE,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_EMOJI,_______, _______, _______, KC_DOWN, KC_LCBR, KC_LPRN,          KC_RPRN, KC_RCBR, KC_P1,   KC_P2,   KC_P3,   KC_MINS, LANG_SW,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, KC_DEL,                    KC_DEL,  _______, KC_P0
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_RIGHT_UNDER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     TAP_P, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_GRV,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_MPRV, KC_MNXT, KC_VOLU, KC_PGUP, KC_UNDS,                            KC_EQL,  KC_HOME, RM_HUEU, RM_SATU, RM_VALU, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, KC_PGDN, KC_MINS, KC_CAPS,          _______, KC_PLUS, KC_END,  RM_HUED, RM_SATD, RM_VALD, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_BOTH_UNDER] = LAYOUT(
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, QK_BOOT,
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_LPRN, KC_RPRN, KC_EQL,  KC_GT,   KC_LCBR, KC_RCBR,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RM_NEXT, _______, KC_MINS, KC_GT,   _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RM_NEXT, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LEFT_UP] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, RM_TOGG, RM_NEXT,                    SC_CLIP_AREA, SC_CLIP_FULL, SC_MENU, SC_AREA, SC_FULL, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, RM_PREV, BL_STEP,                            MS_BTN1, MS_BTN2, MS_BTN3, MS_BTN4, GO_BACK, GO_FORWARD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     MS_BTN2, _______, _______, _______, RM_SPDU, _______,                            MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, GO_UPPER, GO_LOWER,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     MS_BTN1, _______, _______, _______, RM_SPDD, _______, _______,        _______, MW_RIGHT, MW_UP, MW_DOWN, MW_LEFT, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // ========================================================================
    // OS-Agnostic Screenshot Keycodes
    // ========================================================================
    case SC_FULL:
      if (record->event.pressed) {
        register_code16(get_screenshot_full());
      } else {
        unregister_code16(get_screenshot_full());
      }
      return false;

    case SC_AREA:
      if (record->event.pressed) {
        register_code16(get_screenshot_area());
      } else {
        unregister_code16(get_screenshot_area());
      }
      return false;

    case SC_MENU:
      if (record->event.pressed) {
        register_code16(get_screenshot_menu());
      } else {
        unregister_code16(get_screenshot_menu());
      }
      return false;

    case SC_CLIP_FULL:
      if (record->event.pressed) {
        register_code16(get_screenshot_clip_full());
      } else {
        unregister_code16(get_screenshot_clip_full());
      }
      return false;

    case SC_CLIP_AREA:
      if (record->event.pressed) {
        register_code16(get_screenshot_clip_area());
      } else {
        unregister_code16(get_screenshot_clip_area());
      }
      return false;

    // ========================================================================
    // OS-Agnostic Language Switching
    // ========================================================================
    case LANG_SW:
      if (record->event.pressed) {
        register_code16(get_language_switch());
      } else {
        unregister_code16(get_language_switch());
      }
      return false;

    // ========================================================================
    // OS-Agnostic Mouse Wheel
    // ========================================================================
    case MW_RIGHT:
    case MW_UP:
    case MW_DOWN:
    case MW_LEFT:
      if (record->event.pressed) {
        register_code16(get_mouse_wheel(keycode));
      } else {
        unregister_code16(get_mouse_wheel(keycode));
      }
      return false;

    // ========================================================================
    // Layer Switching (existing code)
    // ========================================================================
    case BASIC:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_BASIC);
      }
      return false;
      break;
    case LEFT_UNDER:
      if (record->event.pressed) {
        layer_on(_LEFT_UNDER);
        update_tri_layer(_LEFT_UNDER, _RIGHT_UNDER, _BOTH_UNDER);
      } else {
        layer_off(_LEFT_UNDER);
        update_tri_layer(_LEFT_UNDER, _RIGHT_UNDER, _BOTH_UNDER);
      }
      return false;
      break;
    case RIGHT_UNDER:
      if (record->event.pressed) {
        layer_on(_RIGHT_UNDER);
        update_tri_layer(_LEFT_UNDER, _RIGHT_UNDER, _BOTH_UNDER);
      } else {
        layer_off(_RIGHT_UNDER);
        update_tri_layer(_LEFT_UNDER, _RIGHT_UNDER, _BOTH_UNDER);
      }
      return false;
      break;
    case BOTH_UNDER:
      if (record->event.pressed) {
        layer_on(_BOTH_UNDER);
      } else {
        layer_off(_BOTH_UNDER);
      }
      return false;
      break;
  }
  return true;
}

// OS detection callback - automatically invoked when OS is detected
bool process_detected_host_os_user(os_variant_t detected_os) {
    current_os = detected_os;
    os_detected = true;

    // Optional: Visual feedback via RGB Matrix
    #ifdef RGB_MATRIX_ENABLE
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            // White color for macOS/iOS
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(0, 0, 255);
            break;
        case OS_WINDOWS:
            // Blue color for Windows
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(170, 255, 255);
            break;
        case OS_LINUX:
            // Green color for Linux
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(85, 255, 255);
            break;
        default:
            // Yellow for unsure/unknown
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(43, 255, 255);
            break;
    }
    #endif

    return true;
}
