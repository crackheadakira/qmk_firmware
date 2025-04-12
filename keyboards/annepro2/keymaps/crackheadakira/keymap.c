/* Copyright 2021 OpenAnnePro community
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "annepro2.h"
#include "ap2_led.h"
#include "color.h"
#include "keyboard.h"
#include "keycodes.h"
#include QMK_KEYBOARD_H

enum { TD_BSLS_RSFT };

enum keycodes { DEFAULT_COLOR = SAFE_RANGE, RED, PURPLE };

enum anne_pro_layers {
    BASE,
    FN1,
    COLOR,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_BSLS_RSFT] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_RSFT),
};

// clang-format off
// Key symbols are based on QMK. Use them to remap your keyboard
/*
* Layer BASE
* ,-----------------------------------------------------------------------------------------.
* | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | Caps    |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |       Up       |
* |-----------------------------------------------------------------------------------------+
* | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  Left |  Down | Right |
* \-----------------------------------------------------------------------------------------/
*/
 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [BASE] = LAYOUT_60_ansi( /* Base */
    KC_ESC,           KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6,   KC_7, KC_8, KC_9,    KC_0,             KC_MINS,          KC_EQL,        KC_BSPC,
    KC_TAB,           KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y,   KC_U, KC_I, KC_O,    KC_P,             KC_LBRC,          KC_RBRC,       TD(TD_BSLS_RSFT),
    LT(FN1, KC_CAPS), KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H,   KC_J, KC_K, KC_L,    KC_SCLN,          KC_QUOT,          KC_ENT,
    KC_LSFT,                   KC_Z,    KC_X, KC_C, KC_V, KC_B,   KC_N, KC_M, KC_COMM, KC_DOT,           KC_SLSH,          KC_UP,
    KC_LCTL,          KC_LGUI, KC_LALT,                   KC_SPC,             KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
),
  /*
  * Layer FN1
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    | BACK|PAUSE|NEXT |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      | ARR |  0  | LEDON | LEDOFF |NXTPR|  n  |  m  | RSHFT |INSRT| DEL |   Up    |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  Left |  Down | Right |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [FN1] = LAYOUT_60_ansi( /* FN1 */
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_HOME, KC_END,  _______,
    _______, KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,  KC_P7,    KC_P8,   KC_P9, KC_PGUP, KC_PGDN, _______,
    _______, KC_NUBS, KC_P0,   KC_AP_LED_ON,  KC_AP_LED_OFF, _______, _______,  OSL(COLOR), _______, KC_INS,  KC_DEL,  _______,
    _______, _______, _______,                            _______,                   _______, _______, _______, _______
),
 [COLOR] = LAYOUT_60_ansi( /* FN1 */
    _______, DEFAULT_COLOR, RED, PURPLE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                           _______,              _______, _______, _______, _______
),
};
// clang-format on

struct hsv_t color_config = {222, 255, 255};

const struct hsv_t color_lookup[] = {
    [DEFAULT_COLOR] = {222, 255, 255},
    [RED] = {0, 255, 255},
    [PURPLE] = {183, 255, 255},
};

void keyboard_post_init_user(void) {
    ap2_led_enable();

    rgb_matrix_mode(1);
    rgb_matrix_sethsv(color_config.h, color_config.s, color_config.v);
}

bool led_update_user(led_t leds) {
    if (leds.caps_lock) {
        // set HSV to a darker hue of the current color 255;
        rgb_matrix_sethsv((color_config.h - 16) % 255, color_config.s, color_config.v);
    } else {
        rgb_matrix_sethsv(color_config.h, color_config.s, color_config.v);
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DEFAULT_COLOR:
            if (record->event.pressed) {
                rgb_matrix_mode(1);

                color_config = (struct hsv_t){222, 255, 255};
                rgb_matrix_sethsv(color_config.h, color_config.s, color_config.v);
            }
            return false;

        case RED:
            if (record->event.pressed) {
                rgb_matrix_mode(1);
                color_config = (struct hsv_t){0, 255, 255};
                rgb_matrix_sethsv(color_config.h, color_config.s, color_config.v);
            }
            return false;

        case PURPLE:
            if (record->event.pressed) {
                rgb_matrix_mode(1);
                color_config = (struct hsv_t){183, 255, 255};
                rgb_matrix_sethsv(color_config.h, color_config.s, color_config.v);
            }
            return false;

        default:
            return true; // Process all other keycodes normally
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == 1) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED && keymap_key_to_keycode(layer, (keypos_t){col, row}) > KC_TRNS) {
                    const RGB rgb = hsv_to_rgb(color_config);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if (index >= led_min && index < led_max && index != NO_LED && keymap_key_to_keycode(layer, (keypos_t){col, row}) == KC_TRNS) {
                    rgb_matrix_set_color(index, 0, 0, 0);
                }
            }
        }
    }
    return false;
}

bool rgb_matrix_indicators_user(void) {
    uint8_t layer = biton32(layer_state);
    switch (layer) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            rgb_matrix_set_color_all(0, 0, 0);    // rest of keys blank/black
            rgb_matrix_set_color(1, 255, 0, 200); // DEFAULT_COLOR, 1
            rgb_matrix_set_color(2, 255, 0, 0);   // RED,           2
            rgb_matrix_set_color(3, 77, 0, 255);  // PUPRLE,        3
            break;
    }
    return true;
}