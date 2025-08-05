// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "bootloader.h"
#include "debug.h"
#include "rgblight.h"

#include QMK_KEYBOARD_H

// Layers
#define L_DEFAULT   0
#define L_FUNCTIONS 1

// Special keys
#define K_BOOT1     KC_P3
#define K_BOOT2     KC_P0


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ # │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │Ent│
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ 0 │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_numpad_3x4(
        KC_P7,   KC_P8,   KC_P9,   KC_HASH,
        KC_P4,   KC_P5,   KC_P6,   KC_PENT,
        KC_P1,   KC_P2,   KC_P3,   KC_P0
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
//
void keyboard_post_init_user() {
    debug_enable = true;
//     // rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINDROPS);
//     // rgb_matrix_set_color_all(0, 255, 0);
//
    rgblight_sethsv_noeeprom(85, 255, 255);
    rgblight_setrgb_at(0, 0, 255,0);
}

static bool is_bootloader_active = false;
static uint16_t bootloader_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {
        if (keycode == K_BOOT1 || keycode == K_BOOT2) {
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
