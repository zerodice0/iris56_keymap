// Copyright 2023 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdint.h>
#include QMK_KEYBOARD_H

#ifdef RGB_MATRIX_ENABLE
    #include "rgb_matrix.h"
#endif

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
};

const uint16_t KC_EMOJI = LGUI(LCTL(KC_SPACE));
const uint16_t KC_AG = OSM(MOD_LALT|MOD_LGUI);
const uint16_t KC_SG3 = LSG(KC_3); // SHIFT + GLOBAL, MacOS Capture Shortcut 
const uint16_t KC_SGC3 = LSG(LCTL(KC_3)); // SHIFT + CTRL + GLOBAL, MacOS Capture Shortcut
const uint16_t KC_SG4 = LSG(KC_4); // SHIFT + GLOBAL, MacOS Capture Shortcut(Select Area)
const uint16_t KC_SGC4 = LSG(LCTL(KC_4)); // SHIFT + CTRL + GLOBAL, MacOS Capture Shortcut(Select Area)
const uint16_t KC_SG5 = LSG(KC_5);

const uint16_t GO_BACK = LGUI(KC_LBRC); // Go Backward on MacOS Browser
const uint16_t GO_FORWARD = LGUI(KC_RBRC); // Go Forward on MacOS Browser
const uint16_t GO_UPPER = LGUI(KC_UP); // Go Upper on MacOS Finder
const uint16_t GO_LOWER = LGUI(KC_DOWN); // Go Lower on MacOS Finder

const uint16_t TAP_P = LGUI(KC_GRV);

// macOS-specific keycodes
#define KC_MCTL LGUI(KC_UP)   // Mission Control (Cmd+Up)
#define KC_LPAD LGUI(KC_SPC)  // Launchpad (Cmd+Space)

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
     KC_EMOJI,_______, _______, _______, KC_DOWN, KC_LCBR, KC_LPRN,          KC_RPRN, KC_RCBR, KC_P1,   KC_P2,   KC_P3,   KC_MINS, _______,
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
     _______, _______, _______, _______, _______, _______,                            KC_MCTL, KC_LPAD, _______, _______, _______, QK_BOOT,
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
     _______, _______, _______, _______, RM_TOGG, RM_NEXT,                            KC_SG4,  KC_SGC4, KC_SG3,  KC_SGC3, KC_SG5, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, RM_PREV, BL_STEP,                            MS_BTN1, MS_BTN2, MS_BTN3, MS_BTN4, GO_BACK, GO_FORWARD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     MS_BTN2, _______, _______, _______, RM_SPDU, _______,                            MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, GO_UPPER, GO_LOWER,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     MS_BTN1, _______, _______, _______, RM_SPDD, _______, _______,        _______, MS_WHLR, MS_WHLU, MS_WHLD, MS_WHLL, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
