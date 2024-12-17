/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#include QMK_KEYBOARD_H
#include "transactions.h"
#include "stdio.h"
#include "string.h"
#include "quantum_keycodes.h"
#include "keymap_introspection.h"
#include "features/custom_shift_keys.h"

// layout

enum layers { _BASE = 0, _SYM, _EXT, _NUM, _YAY, _FUN, _ADJ, _MAX = _ADJ };

#define OSM_GUI OSM(MOD_LGUI)
#define OSM_ALT OSM(MOD_LALT)
#define OSM_SFT OSM(MOD_LSFT)
#define OSM_CTL OSM(MOD_LCTL)

#define CTRL_A LCTL(KC_A)
#define CTRL_Z LCTL(KC_Z)
#define CTRL_X LCTL(KC_X)
#define CTRL_C LCTL(KC_C)
#define CTRL_V LCTL(KC_V)

#define SPC_EXT LT(_EXT, KC_SPC)

enum custom_keycodes {
    CANCEL_6 = QK_USER,
    ALT_TO6,
    FUN_NUM,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT_split_3x6_5_hlc(
		KC_TAB,		KC_Q,		KC_W,		KC_F,		KC_P,		KC_B,															    KC_J,		KC_L,		KC_U,		KC_Y,		KC_SCLN,	KC_MUTE,
		KC_ESC,		KC_A,		KC_R,		KC_S,		KC_T,		KC_G,														   		KC_M,		KC_N,		KC_E,		KC_I,		KC_O,		KC_MINS,
		KC_LCTL,	KC_Z,		KC_X,		KC_C,		KC_D,		KC_V,		KC_SPC, 	KC_BSLS,			MO(_EXT),	KC_UNDS,	KC_K,		KC_H,		KC_COMM,	KC_DOT,		KC_QUOT,	KC_ENT,
											KC_LGUI,	XXXXXXX,    KC_LSFT,	MO(_EXT),	MO(_NUM),			FUN_NUM,	KC_SPC,		MO(_SYM),	KC_LALT,	MO(_ADJ)
	),
	[_SYM] = LAYOUT_split_3x6_5_hlc(
        _______,	KC_SCRL,	KC_LBRC,	KC_RBRC,	KC_PERC,	KC_AT,																KC_CIRC,	KC_PIPE,	KC_QUES,    KC_AMPR,	KC_SCLN,	_______,
        KC_BSPC,	KC_EXLM,	KC_MINS,	KC_PLUS,	KC_EQL,		KC_HASH,														    KC_TILD,	KC_COLN,	KC_LPRN,	KC_RPRN,	KC_RCBR,	MC_0,
        MO(_NUM),	KC_ASTR,	KC_LT,		KC_GT,		KC_SLSH,	KC_BSLS,	KC_UNDS,	_______,			_______,	_______,	KC_GRV,		KC_LCBR,	KC_DLR,		KC_DOT,		KC_DQUO,	_______,
                                            _______,	_______,	_______,	SPC_EXT,    _______,			_______,	_______,	_______,	_______,	_______
    ),
	[_NUM] = LAYOUT_split_3x6_5_hlc(
		_______,	ALT_TO6,	KC_LBRC,	KC_RBRC,	KC_PERC,	KC_AT,																KC_CIRC,	KC_7,		KC_8,		KC_9,		_______,	_______,
		KC_BSPC,	KC_EXLM,	KC_MINS,	KC_PLUS,	KC_EQL,		KC_HASH,															KC_TILD,	KC_4,		KC_5,		KC_6,		KC_0,		_______,
		_______,	KC_ASTR,	KC_LT,		KC_GT,		KC_SLSH,	KC_BSLS,	_______,	_______,			_______,	_______,    KC_BSPC,    KC_1,		KC_2,		KC_3,		KC_COMM,	_______,
											_______,	_______,	_______,	SPC_EXT,    _______,			KC_DOT,	    _______,	_______, 	_______,	_______
	),
	[_EXT] = LAYOUT_split_3x6_5_hlc(
		_______,	TO(_YAY),	KC_TAB,		XXXXXXX,	OSM_ALT,	XXXXXXX,									    					KC_PGUP,	KC_HOME,	KC_UP,		KC_END,		XXXXXXX,	_______,
		_______,	OSM_GUI,	OSM_ALT,	OSM_SFT,    OSM_CTL,	CTRL_A,										    					KC_PGDN,	KC_LEFT,	KC_DOWN,	KC_RGHT,	KC_DEL,		_______,
		MO(_FUN),	CTRL_Z,	    CTRL_X,  	CTRL_C,		KC_TAB,		CTRL_V,     _______,	_______,			_______,	_______,	_______,	KC_BSPC,	KC_APP,		KC_INS,		KC_PSCR,	_______,
                                            _______,	_______,	_______,	_______,	_______,			MO(_NUM),	_______,	_______,	_______,	_______
	),
	[_FUN] = LAYOUT_split_3x6_5_hlc(
		_______,	_______,	KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_VOLU,											                _______,	KC_F7,		KC_F8,		KC_F9,		_______,	_______,
		_______,	OSM_GUI,    OSM_ALT,    OSM_SFT,    OSM_CTL,	KC_VOLD,												            KC_F11,	    KC_F4,		KC_F5,		KC_F6,		KC_F10,		_______,
		_______,	_______,	_______,	_______,	_______,	KC_MUTE,	_______,	_______,			_______,	_______,	KC_F12,	    KC_F1,		KC_F2,		KC_F3,		_______,	_______,
											_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______
	),
	[_ADJ] = LAYOUT_split_3x6_5_hlc(
		EE_CLR,		RGB_RMOD,	RGB_HUI,	RGB_SAI,	RGB_VAI,	_______,															KC_WH_U,	KC_BTN1,	KC_MS_U,	KC_BTN2,	KC_ACL0,	_______,
		_______,	RGB_MOD,	RGB_HUD,	RGB_SAD,	RGB_VAD,	RGB_TOG,															KC_WH_D,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_ACL1,	_______,
		_______,	_______,	_______,	RGB_SPD,	RGB_SPI,	_______,	_______,	_______,			_______,	_______,	_______,	KC_BTN4,	KC_BTN3,	KC_BTN5,	KC_ACL2,	_______,
											_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______
	),
	[_YAY] = LAYOUT_split_3x6_5_hlc(
		_______,	_______,	_______,	_______,	_______,	_______,															_______,	_______,	_______,	_______,	_______,	_______,
		KC_ESC,		_______,	_______,	_______,	_______,	_______,															_______,	_______,	_______,	_______,	_______,	_______,
		KC_LCTL,	_______,	_______,	_______,	_______,	_______,	KC_MINS,	KC_BSLS,			XXXXXXX,	_______,	_______,    _______,   	_______,	_______,	_______,	CANCEL_6,
											TG(_YAY),  	TG(_YAY),	KC_LSFT,	KC_SPC,		KC_LALT,			MO(_FUN),   CANCEL_6,   CANCEL_6,   CANCEL_6,   CANCEL_6
	),
};


// disable shift
const custom_shift_key_t custom_shift_keys[20] = {
    {KC_GRAVE, KC_GRAVE},
    {KC_1, KC_1},
    {KC_2, KC_2},
    {KC_3, KC_3},
    {KC_4, KC_4},
    {KC_5, KC_5},
    {KC_6, KC_6},
    {KC_7, KC_7},
    {KC_8, KC_8},
    {KC_9, KC_9},
    {KC_0, KC_0},
    {KC_MINUS, KC_MINUS},
    {KC_EQUAL, KC_EQUAL},
    {KC_LBRC, KC_LBRC},
    {KC_RBRC, KC_RBRC},
    {KC_BSLS, KC_BSLS},
    {KC_SCLN, KC_SCLN},
    {KC_COMMA, KC_COMMA},
    {KC_DOT, KC_DOT},
    {KC_SLASH, KC_SLASH},
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);
// clang-format on

// oled

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

char      status_message[30];
int32_t   status_message_time     = 0;
const int STATUS_MESSAGE_DURATION = 5000; // 5 seconds

#    define set_status_message(...)                                        \
        {                                                                  \
            snprintf(status_message, sizeof(status_message), __VA_ARGS__); \
            status_message_time = timer_read32();                          \
        }
// typedef union {
//     uint32_t raw;
//     struct PACKED {
//         uint8_t     enable : 2;
//         uint8_t     mode : 6;
//         HSV         hsv;
//         uint8_t     speed; // EECONFIG needs to be increased to support this
//         led_flags_t flags;
//     };
// } rgb_config_t;
// rgb_config_t rgb_matrix_config;

rgb_config_t prev_rgb_config;

void check_status_changes(void) {
    if (memcmp(&prev_rgb_config, &rgb_matrix_config, sizeof(rgb_config_t)) == 0) {
        return;
    }

    if (prev_rgb_config.enable != rgb_matrix_config.enable) {
        if (rgb_matrix_config.enable) {
            set_status_message("RGB: ON");
        } else {
            set_status_message("RGB: OFF");
        }
    } else if (prev_rgb_config.mode != rgb_matrix_config.mode) {
        set_status_message("RGB mode: %d", rgb_matrix_config.mode);
    } else if (prev_rgb_config.hsv.h != rgb_matrix_config.hsv.h) {
        set_status_message("RGB hue: %d", rgb_matrix_config.hsv.h);
    } else if (prev_rgb_config.hsv.s != rgb_matrix_config.hsv.s) {
        set_status_message("RGB sat: %d", rgb_matrix_config.hsv.s);
    } else if (prev_rgb_config.hsv.v != rgb_matrix_config.hsv.v) {
        set_status_message("RGB val: %d", rgb_matrix_config.hsv.v);
    } else if (prev_rgb_config.speed != rgb_matrix_config.speed) {
        set_status_message("RGB speed: %d", rgb_matrix_config.speed);
    }
    // ignore flags
    prev_rgb_config = rgb_matrix_config;
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        check_status_changes();
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on
        oled_write_P(qmk_logo, false);

        // Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _BASE:
                oled_write_P(PSTR("Base\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case _NUM:
                oled_write_P(PSTR("Num\n"), false);
                break;
            case _EXT:
                oled_write_P(PSTR("Ext\n"), false);
                break;
            case _FUN:
                oled_write_P(PSTR("Fun\n"), false);
                break;
            case _ADJ:
                oled_write_P(PSTR("ADJ\n"), false);
                break;
            case _YAY:
                oled_write_P(PSTR("Yay\n"), false);
                break;
            default:
                oled_write_P(PSTR("???\n"), false);
        }

        // LED Status
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);

        oled_write_P(PSTR("\n"), false);

        // status message
        if (timer_elapsed32(status_message_time) < STATUS_MESSAGE_DURATION) {
            oled_write_ln(status_message, false);
        } else {
            oled_write_ln(PSTR(""), false);
        }
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
             0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
             0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
             0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
             0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
             0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
             0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif

// encoder

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // scroll up/down
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    } else if (index == 1) {
        // Volume up/down
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}
#endif

// data sync

typedef struct last_change_key_t {
    int8_t osm[4];
    int8_t layer[7];
} last_change_key_t;

last_change_key_t last_change_keys;
bool              last_change_keys_changed = false;

void last_layer_sync_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const last_change_key_t* data = (const last_change_key_t*)in_data;

    memcpy(&last_change_keys, data, sizeof(last_change_keys));
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(LAST_LAYER_SYNC, last_layer_sync_slave_handler);

    for (int i = 0; i < 4; i++) {
        last_change_keys.osm[i] = -1;
    }
    for (int i = 0; i < 7; i++) {
        last_change_keys.layer[i] = -1;
    }

    prev_rgb_config = rgb_matrix_config;

#ifdef ACTION_DEBUG
    debug_enable = true;
#endif
}

void housekeeping_task_user(void) {
    if (!is_keyboard_master()) return;

    static uint32_t last_sync = 0;
    // if (send_if_condition(LAST_LAYER_SYNC, &last_sync, last_change_keys_changed, &last_change_keys, sizeof(last_change_keys))) {
    if (timer_elapsed32(last_sync) >= 100 || last_change_keys_changed) {
        bool ok = transaction_rpc_send(LAST_LAYER_SYNC, sizeof(last_change_keys), &last_change_keys);
        if (ok) {
            last_sync                = timer_read32();
            last_change_keys_changed = false;
        }
    }
}

void set_last_osm_key(uint8_t index, uint8_t key) {
    if (last_change_keys.osm[index] != key) {
        last_change_keys_changed    = true;
        last_change_keys.osm[index] = key;
    }
}

void set_last_layer_key(uint8_t index, uint8_t key) {
    if (last_change_keys.layer[index] != key) {
        last_change_keys_changed      = true;
        last_change_keys.layer[index] = key;
    }
}

bool in_fake_keypress = false;

void fake_keypress(uint8_t row, uint8_t col, bool pressed) {
    keyevent_t fake_event = {
        .time    = 0,
        .type    = KEY_EVENT,
        .pressed = pressed,
        .key     = (keypos_t){.row = row, .col = col},
    };
    keyrecord_t key  = {.event = fake_event};
    in_fake_keypress = true;
    process_record(&key);
    in_fake_keypress = false;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case CANCEL_6: {
            if (record->event.pressed) layer_off(_YAY);
            return true;
        }
        case ALT_TO6: {
            if (record->event.pressed) {
                bool alt_pressed = matrix_is_on(3, 0);
                if (alt_pressed) fake_keypress(3, 0, false);
                layer_move(_YAY);
                if (alt_pressed) fake_keypress(3, 0, true);
            }
            return false;
        }
        case FUN_NUM: {
            static uint8_t mo_layer = 0;
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    mo_layer = _NUM;
                } else {
                    mo_layer = _FUN;
                }
                layer_on(mo_layer);
            } else {
                layer_off(mo_layer);
            }
            uint8_t row   = record->event.key.row;
            uint8_t col   = record->event.key.col;
            uint8_t index = g_led_config.matrix_co[row][col];
            set_last_layer_key(mo_layer, index);
            return false;
        }
        // check for normal modifiers
        case KC_LEFT_CTRL ... KC_RIGHT_GUI:
            if (record->event.pressed) {
                uint8_t row     = record->event.key.row;
                uint8_t col     = record->event.key.col;
                uint8_t index   = g_led_config.matrix_co[row][col];
                uint8_t mod_num = keycode & 3;
                set_last_osm_key(mod_num, index);
                break;
            }
        // check for osm
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            if (record->event.pressed) {
                uint8_t row   = record->event.key.row;
                uint8_t col   = record->event.key.col;
                uint8_t index = g_led_config.matrix_co[row][col];
                for (uint8_t i = 0, b = 1; i < 4; i++, b <<= 1) {
                    if (keycode & b) {
                        set_last_osm_key(i, index);
                    }
                }
                break;
            }
        // check for MO
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            if (record->event.pressed) {
                uint8_t layer = QK_MOMENTARY_GET_LAYER(keycode);
                uint8_t row   = record->event.key.row;
                uint8_t col   = record->event.key.col;
                uint8_t index = g_led_config.matrix_co[row][col];
                set_last_layer_key(layer, index);
                break;
            }

        // check for LT
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (record->event.pressed) {
                uint8_t layer = QK_LAYER_TAP_GET_LAYER(keycode);
                uint8_t row   = record->event.key.row;
                uint8_t col   = record->event.key.col;
                uint8_t index = g_led_config.matrix_co[row][col];
                set_last_layer_key(layer, index);
                break;
            }

        default:
            break;
    }

    // if in layer 6, and any left thumb keys + right side is pressed, disable layer 6 and repress as if in layer 0
    if (record->event.pressed && !in_fake_keypress && get_highest_layer(layer_state) == _YAY // in layer
        && matrix_get_row(3)                                                                 // left thumb keys
        && record->event.key.row >= 4                                                        // right side
    ) {
        // un press all keys in earlier rows
        for (uint8_t row = 0; row <= record->event.key.row; row++) {
            uint8_t currentRow = matrix_get_row(row);
            uint8_t max_col    = row == record->event.key.row ? record->event.key.col : matrix_cols();
            for (uint8_t col = 0; col < max_col; col++) {
                if (row == record->event.key.row && col == record->event.key.col) break;
                if ((currentRow & (1 << col)) != 0) {
                    fake_keypress(row, col, false);
                }
            }
        }

        // super common exception (ext+h == bspc), tap an extra backspace
        if (keycode == KC_H && matrix_is_on(3, 5)) {
            tap_code(KC_BSPC);
        }

        layer_off(_YAY);

        // do left half represses from bottom to top (so thumb keys are pressed first)
        for (int row = 3; row >= 0; row--) {
            uint8_t currentRow = matrix_get_row(row);
            for (uint8_t col = 0; col < matrix_cols(); col++) {
                if ((currentRow & (1 << col)) != 0) fake_keypress(row, col, true);
            }
        }

        // right half in normal order
        for (int row = 4; row <= record->event.key.row; row++) {
            uint8_t currentRow = matrix_get_row(row);
            uint8_t max_col    = row == record->event.key.row ? record->event.key.col : matrix_cols();
            for (uint8_t col = 0; col < max_col; col++) {
                if ((currentRow & (1 << col)) != 0) fake_keypress(row, col, true);
            }
        }
        return true;
    }
    return true;
}
// just color, not brightness
typedef struct {
    uint8_t h, s;
} HS;

// hues
enum {
    mag_red    = 250,
    red        = 0,
    orange     = 30 * 17 / 24,
    lemon      = 40 * 17 / 24,
    yellow     = 60 * 17 / 24,
    gyellow    = 70 * 17 / 24,
    lime       = 80 * 17 / 24,
    green      = 100 * 17 / 24,
    mint_green = 110 * 17 / 24,
    blue_green = 150 * 17 / 24,
    light_blue = 160 * 17 / 24,
    dark_blue  = 240 * 17 / 24,
    magenta    = 280 * 17 / 24,
    purple     = 300 * 17 / 24,
    ctrl_hue   = green,
    shift_hue  = lemon,
    alt_hue    = mag_red,
    super_hue  = light_blue,
    base_hue   = light_blue,
    sym_hue    = yellow,
    num_hue    = purple,
    ext_hue    = light_blue,
    fun_hue    = dark_blue,
    adj_hue    = magenta,
    yay_hue    = orange,

    cancel_hue = mag_red,
};

#define _US(hue) \
    { hue, 170 }
#define _SS(hue) \
    { hue, 240 }
#define _NONE \
    { light_blue, 40 }
#define _SPC \
    { mint_green, 200 }

HS row_color_normal[12] = {
    _US(super_hue), _NONE, _US(shift_hue), _US(ext_hue), _US(num_hue), _US(fun_hue), _SPC, _US(sym_hue), _US(alt_hue), _US(adj_hue),
};
HS fun_num_shift_color = _US(num_hue);

HS row_color_yay[12] = {_SS(cancel_hue), _SS(cancel_hue), _US(shift_hue), _SPC, _US(alt_hue), _SS(orange), _SS(orange), _SS(orange), _SS(cancel_hue), _SS(cancel_hue)};

HS layer_colors[_MAX + 1] = {
    [_BASE] = _US(base_hue), [_SYM] = _US(sym_hue), [_NUM] = _US(num_hue), [_EXT] = _US(ext_hue), [_FUN] = _US(fun_hue), [_ADJ] = _US(adj_hue), [_YAY] = _US(yay_hue),
};

const uint8_t mod_hues[] = {ctrl_hue, shift_hue, alt_hue, super_hue};

RGB color_add(RGB a, RGB b) {
    RGB c;
    c.r = MIN(a.r + b.r, 255);
    c.g = MIN(a.g + b.g, 255);
    c.b = MIN(a.b + b.b, 255);
    return c;
}

const uint8_t top_underglow[]    = {0, 1, 2, 3, 31, 32, 33, 34};
const uint8_t bottom_underglow[] = {4, 5, 35, 36};
const uint8_t lower_row[12]      = {10, 9, 8, 7, 6, 37, 38, 39, 40, 41};

// bool rgb_matrix_indicators_user(uint8_t led_min, uint8_t led_max) {
bool rgb_matrix_indicators_user(void) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    if (layer > _MAX) return false;

    uint8_t mods = get_mods() | get_oneshot_mods();

    RGB mods_color = {0, 0, 0};
    if (mods) {
        int     pop_count = __builtin_popcount(mods);
        uint8_t v         = rgb_matrix_config.hsv.v / pop_count;
        if (mods & MOD_MASK_SHIFT) {
            mods_color = color_add(mods_color, hsv_to_rgb((HSV){shift_hue, 255, v}));
        }
        if (mods & MOD_MASK_CTRL) {
            mods_color = color_add(mods_color, hsv_to_rgb((HSV){ctrl_hue, 255, v}));
        }
        if (mods & MOD_MASK_ALT) {
            mods_color = color_add(mods_color, hsv_to_rgb((HSV){alt_hue, 255, v}));
        }
        if (mods & MOD_MASK_GUI) {
            mods_color = color_add(mods_color, hsv_to_rgb((HSV){super_hue, 255, v}));
        }
    }

    HS layer_hsv = layer_colors[layer];

    RGB layer_color  = hsv_to_rgb((HSV){layer_hsv.h, layer_hsv.s, rgb_matrix_config.hsv.v});
    RGB top_color    = layer_color;
    RGB bottom_color = color_add(layer_color, mods_color);

    for (int i = 0; i < sizeof(top_underglow) / sizeof(top_underglow[0]); i++) {
        rgb_matrix_set_color(top_underglow[i], top_color.r, top_color.g, top_color.b);
    }

    for (int i = 0; i < sizeof(bottom_underglow) / sizeof(bottom_underglow[0]); i++) {
        rgb_matrix_set_color(bottom_underglow[i], bottom_color.r, bottom_color.g, bottom_color.b);
    }

    HS* row_colors = layer == _YAY ? row_color_yay : row_color_normal;
    for (int i = 0; i < 12; ++i) {
        HS curColor = row_colors[i];
        if (i == 5 && get_mods() & MOD_MASK_SHIFT) {
            curColor = fun_num_shift_color;
        }
        RGB color = hsv_to_rgb((HSV){curColor.h, curColor.s, rgb_matrix_config.hsv.v});
        rgb_matrix_set_color(lower_row[i], color.r, color.g, color.b);
    }

    // highlight mod keys
    for (int i = 0, b = 1; i < 4; i++, b <<= 1) {
        if (b & mods) {
            int8_t index = last_change_keys.osm[i];
            if (index != -1) {
                RGB color = hsv_to_rgb((HSV){mod_hues[i], 255, rgb_matrix_config.hsv.v + 50});
                rgb_matrix_set_color(index, color.r, color.g, color.b);
            }
        }
    }

    // highlight layer key
    if (layer != 0) {
        int8_t index = last_change_keys.layer[layer];
        if (index != -1) {
            RGB color = hsv_to_rgb((HSV){layer_colors[layer].h, 255, rgb_matrix_config.hsv.v + 50});
            rgb_matrix_set_color(index, color.r, color.g, color.b);
        }
    }

    return false;
}
