// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "action_layer.h"
#include "bootloader.h"
#include "debug.h"
#include "keycodes.h"
#include "rgblight.h"

#include QMK_KEYBOARD_H

// Layers
enum eLayers {
    L_NUMPAD,
    L_SYMBOLS,
    L_FUNCTIONS,
    L_SPECIAL,
};

// Special keys
#define K_BOOT1     KC_3
#define K_BOOT2     KC_0


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │Esc│
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │Ent│
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ 0 │
     * └───┴───┴───┴───┘
     */
    [L_NUMPAD] = LAYOUT_numpad_3x4(
        KC_7,   KC_8,   KC_9,   LT(L_SYMBOLS,KC_ESC),
        KC_4,   KC_5,   KC_6,   LT(L_FUNCTIONS,KC_ENT),
        KC_1,   KC_2,   KC_3,   LT(L_SPECIAL,KC_0)
    ),
    /*
     * ┌───┬───┬───┬───┐
     * │ & │ * │ ( │   │
     * ├───┼───┼───┼───┤
     * │ $ │ % │ ^ │BSP│
     * ├───┼───┼───┼───┤
     * │ ! │ @ │ # │ ) │
     * └───┴───┴───┴───┘
     */
    [L_SYMBOLS] = LAYOUT_numpad_3x4(
        S(KC_7),   S(KC_8),   S(KC_9),   _______,
        S(KC_4),   S(KC_5),   S(KC_6),   KC_BACKSPACE,
        S(KC_1),   S(KC_2),   S(KC_3),   S(KC_0)
    ),
    /*
     * ┌───┬───┬───┬───┐
     * │F1 │F2 │F3 │F4 │
     * ├───┼───┼───┼───┤
     * │F5 │F6 │F7 │   │
     * ├───┼───┼───┼───┤
     * │F8 │F9 │F10│F11│
     * └───┴───┴───┴───┘
     */
    [L_FUNCTIONS] = LAYOUT_numpad_3x4(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,
        KC_F5,   KC_F6,   KC_F7,   _______,
        KC_F8,   KC_F9,   KC_F10,   KC_F11
    ),
    /*
     * ┌───┬───┬───┬───┐
     * │BTL│UP │   │   │
     * ├───┼───┼───┼───┤
     * │LFT│DWN│RGT│   │
     * ├───┼───┼───┼───┤
     * │   │   │   │   │
     * └───┴───┴───┴───┘
     */
    [L_SPECIAL] = LAYOUT_numpad_3x4(
        QK_BOOTLOADER,   KC_UP,   _______,   _______,
        KC_LEFT,   KC_DOWN,   KC_RIGHT,   _______,
        _______,   _______,   _______,   _______
    )
};

void matrix_init_user() {
    // eeconfig_init();
    // rgblight_init();
    // rgblight_enable_noeeprom();
    // rgblight_sethsv_noeeprom(120, 255, 255);
    // rgblight_setrgb(0, 255, 0);
    // eeconfig_force_flush_rgb_matrix();
    // rgb_matrix_enable_noeeprom();
    // rgb_matrix_set_flags(RGB_MATRIX_SOLID_COLOR);
    // rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
}

static void rgb_config_numpad(void) {
    rgblight_setrgb_at(0, 0, 255,4);
    rgblight_setrgb_at(0, 0, 255,11);

    const uint8_t GREEN_KEYS[] = {
        0, 1, 2, 3, 5, 6, 7, 8, 9, 10,
    };

    uint8_t i = 0;

    for (i = 0; i < sizeof(GREEN_KEYS); i++) {
        rgblight_setrgb_at(0, 255, 0,GREEN_KEYS[i]);
    }
}

static void rgb_config_symbols(void) {
    rgblight_setrgb_at(0, 0, 0,11);

    const uint8_t WHITE_KEYS[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    };

    uint8_t i = 0;

    for (i = 0; i < sizeof(WHITE_KEYS); i++) {
        rgblight_setrgb_at(255, 255, 255,WHITE_KEYS[i]);
    }
}

static void rgb_config_functions(void) {
    rgblight_setrgb_at(0, 0, 0,4);

    const uint8_t BLUE_KEYS[] = {
        0, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11
    };

    uint8_t i = 0;

    for (i = 0; i < sizeof(BLUE_KEYS); i++) {
        rgblight_setrgb_at(0, 255, 0,BLUE_KEYS[i]);
    }
}

static void rgb_config_specials(void) {
    rgblight_setrgb_at(255, 0, 0,8);

    const uint8_t OFF_KEYS[] = {
        0, 1, 2, 3, 4, 10, 11
    };
    const uint8_t ORANGE_KEYS[] = {
        5, 6, 7, 9
    };

    uint8_t i = 0;

    for (i = 0; i < sizeof(OFF_KEYS); i++) {
        rgblight_setrgb_at(0, 0, 0,OFF_KEYS[i]);
    }

    for (i = 0; i < sizeof(ORANGE_KEYS); i++) {
        rgblight_setrgb_at(255, 100, 0,ORANGE_KEYS[i]);
    }
}

void keyboard_post_init_user() {
    debug_enable = true;
    rgb_config_numpad();
//     // rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINDROPS);
//     // rgb_matrix_set_color_all(0, 255, 0);
//
    // rgblight_sethsv_noeeprom(85, 255, 255);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case L_SYMBOLS:
            rgb_config_symbols();
        break;
        case L_FUNCTIONS:
            rgb_config_functions();
        break;
        case L_SPECIAL:
            rgb_config_specials();
        break;
        default:
            rgb_config_numpad();
        break;
    }

    return state;
}

static bool is_bootloader_active = false;
static uint16_t bootloader_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {
        if (keycode == QK_BOOTLOADER) {
            rgblight_sethsv_noeeprom(0, 255, 255);
            dprintf("\nBOOTLOADER MODE\n");
            if (is_bootloader_active) {
                return false;
            }
            is_bootloader_active = true;
            bootloader_timer = 10;
        }
    } else {
        is_bootloader_active = false;
    }

    return !is_bootloader_active;
}

void matrix_scan_user(void) {
    if (is_bootloader_active) {
        if (bootloader_timer > 0) {
            bootloader_timer--;
        } else {
            bootloader_jump();
        }
    }
}
