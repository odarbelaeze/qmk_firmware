/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,           KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS,
        RALT_T(KC_ESC),  KC_A, KC_S, KC_D, KC_F, KC_G,           KC_H, KC_J, KC_K, KC_L, KC_SCLN, RALT_T(KC_QUOT),
        KC_LSFT, LCTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B,          KC_N, KC_M, KC_COMM, KC_DOT, RCTL_T(KC_SLSH), KC_RSFT,

        KC_LGUI, LT(_RAISE ,KC_BSPC), KC_SPC, KC_TAB, LT(_LOWER,KC_ENT), KC_RALT
    ),
    [_LOWER] = LAYOUT_split_3x6_3(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                 KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
        KC_DEL,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,           KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_PIPE,
        KC_LSFT, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,         KC_NO,   KC_UNDS, KC_PLUS, KC_RBRC, KC_LBRC, KC_BSLS,

        KC_TRNS, MO(_ADJUST), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_RAISE] = LAYOUT_split_3x6_3(
        KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,           KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS,
        KC_DEL,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                  KC_F6,   KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE,
        KC_LSFT, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,                KC_F12,  KC_UNDS, KC_PLUS, KC_RBRC, KC_LBRC, KC_BSLS,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_ADJUST), KC_TRNS
    ),
    [_ADJUST] = LAYOUT_split_3x6_3(
        RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};


#ifdef OLED_DRIVER_ENABLE
void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Ups"), false);
    }

    oled_write_P(PSTR("Property of the chino\n"), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }

    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();  // Renders a static logo
        oled_scroll_left();  // Turns on scrolling
    }
}
#endif

