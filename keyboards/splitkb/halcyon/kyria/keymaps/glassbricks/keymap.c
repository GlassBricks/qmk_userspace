// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H

#include <features/custom_shift_keys.h>

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
#define NUM_BLS LT(_NUM, KC_BSLS)

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
		KC_LCTL,	KC_Z,		KC_X,		KC_C,		KC_D,		KC_V,		KC_SPC, 	NUM_BLS,			MO(_EXT),	KC_UNDS,	KC_K,		KC_H,		KC_COMM,	KC_DOT,		KC_QUOT,	KC_ENT,
											KC_LGUI,	XXXXXXX,    KC_LSFT,	MO(_EXT),	QK_REP,			    FUN_NUM,	KC_SPC,		MO(_SYM),	KC_LALT,	MO(_ADJ),
                                            KC_MUTE,    KC_NO,      KC_NO,      KC_NO,      KC_NO,              KC_MUTE,     KC_NO,     KC_NO,      KC_NO,      KC_NO
	),
	[_SYM] = LAYOUT_split_3x6_5_hlc(
        _______,	KC_SCRL,	KC_LBRC,	KC_RBRC,	KC_PERC,	KC_AT,																KC_CIRC,	KC_PIPE,	KC_QUES,    KC_AMPR,	KC_SCLN,	_______,
        KC_BSPC,	KC_EXLM,	KC_MINS,	KC_PLUS,	KC_EQL,		KC_HASH,														    KC_TILD,	KC_COLN,	KC_LPRN,	KC_RPRN,	KC_RCBR,	_______,
        MO(_NUM),	KC_ASTR,	KC_LT,		KC_GT,		KC_SLSH,	KC_BSLS,	KC_UNDS,	_______,			_______,	_______,	KC_GRV,		KC_LCBR,	KC_DLR,		KC_DOT,		KC_DQUO,	_______,
                                            _______,	_______,	_______,	SPC_EXT,    _______,			_______,	_______,	_______,	_______,	_______,
                                            _______,    _______,    _______,    _______,    _______,            _______,    _______,    _______,    _______,    _______
    ),
	[_NUM] = LAYOUT_split_3x6_5_hlc(
		_______,	ALT_TO6,	KC_LBRC,	KC_RBRC,	KC_PERC,	KC_AT,																KC_CIRC,	KC_7,		KC_8,		KC_9,		_______,	_______,
		KC_BSPC,	KC_EXLM,	KC_MINS,	KC_PLUS,	KC_EQL,		KC_HASH,															KC_TILD,	KC_4,		KC_5,		KC_6,		KC_0,		_______,
		_______,	KC_ASTR,	KC_LT,		KC_GT,		KC_SLSH,	KC_BSLS,	_______,	_______,			_______,	_______,    KC_BSPC,    KC_1,		KC_2,		KC_3,		KC_COMM,	_______,
											_______,	_______,	_______,	SPC_EXT,    _______,			KC_DOT,	    _______,	_______, 	_______,	_______,
                                            _______,    _______,    _______,    _______,    _______,            _______,    _______,    _______,    _______,    _______
	),
	[_EXT] = LAYOUT_split_3x6_5_hlc(
		_______,	TO(_YAY),	KC_TAB,		XXXXXXX,	OSM_ALT,	XXXXXXX,									    					KC_PGUP,	KC_HOME,	KC_UP,		KC_END,		XXXXXXX,	_______,
		_______,	OSM_GUI,	OSM_ALT,	OSM_SFT,    OSM_CTL,	CTRL_A,										    					KC_PGDN,	KC_LEFT,	KC_DOWN,	KC_RGHT,	KC_DEL,		_______,
		MO(_FUN),	CTRL_Z,	    CTRL_X,  	CTRL_C,		KC_TAB,		CTRL_V,     _______,	_______,			_______,	_______,	_______,	KC_BSPC,	KC_APP,		KC_INS,		KC_PSCR,	_______,
                                            _______,	_______,	_______,	_______,	_______,			MO(_NUM),	_______,	_______,	_______,	_______,
                                            _______,    _______,    _______,    _______,    _______,            _______,    _______,    _______,    _______,    _______
	),
	[_FUN] = LAYOUT_split_3x6_5_hlc(
		_______,	_______,	KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_VOLU,											                _______,	KC_F7,		KC_F8,		KC_F9,		_______,	_______,
		_______,	OSM_GUI,    OSM_ALT,    OSM_SFT,    OSM_CTL,	KC_VOLD,												            KC_F11,	    KC_F4,		KC_F5,		KC_F6,		KC_F10,		_______,
		_______,	_______,	_______,	_______,	_______,	KC_MUTE,	_______,	_______,			_______,	_______,	KC_F12,	    KC_F1,		KC_F2,		KC_F3,		_______,	_______,
											_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,
                                            _______,    _______,    _______,    _______,    _______,            _______,    _______,    _______,    _______,    _______
	),
	[_ADJ] = LAYOUT_split_3x6_5_hlc(
		EE_CLR,		RGB_RMOD,	RGB_HUI,	RGB_SAI,	RGB_VAI,	_______,															KC_WH_U,	KC_BTN1,	KC_MS_U,	KC_BTN2,	KC_ACL0,	_______,
		_______,	RGB_MOD,	RGB_HUD,	RGB_SAD,	RGB_VAD,	RGB_TOG,															KC_WH_D,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_ACL1,	_______,
		_______,	_______,	_______,	RGB_SPD,	RGB_SPI,	_______,	_______,	_______,			_______,	_______,	_______,	KC_BTN4,	KC_BTN3,	KC_BTN5,	KC_ACL2,	_______,
											_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,
                                            _______,    _______,    _______,    _______,    _______,             _______,    _______,    _______,    _______,    _______
	),
	[_YAY] = LAYOUT_split_3x6_5_hlc(
		_______,	_______,	_______,	_______,	_______,	_______,															_______,	_______,	_______,	_______,	_______,	_______,
		KC_ESC,		_______,	_______,	_______,	_______,	_______,															_______,	_______,	_______,	_______,	_______,	_______,
		KC_LCTL,	_______,	_______,	_______,	_______,	_______,	KC_MINS,	KC_BSLS,			_______,	_______,	_______,    _______,   	_______,	_______,	_______,	CANCEL_6,
											TG(_YAY),  	TG(_YAY),	KC_LSFT,	KC_SPC,		KC_LALT,			MO(_FUN),   CANCEL_6,   CANCEL_6,   CANCEL_6,   CANCEL_6,
                                            _______,    _______,    _______,    _______,    _______,            _______,    _______,    _______,    _______,    _______
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

// custom key handling
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
            return false;
        }
        default:
            break;
    }

    // if in layer _YAY, and any left thumb keys + right side is pressed, disable layer 6 and repress as if in layer 0
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
