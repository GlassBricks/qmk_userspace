// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <quantum.h>

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

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // Volume up/down
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return false;
}
#endif

// key configure stuff
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case NUM_BLS:
            return true;
        default:
            return false;
    }
}

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

// RGB
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

    ctrl_hue  = light_blue,
    shift_hue = lemon,
    alt_hue   = mag_red,
    super_hue = lime,

    base_hue = light_blue,
    sym_hue  = yellow,
    ext_hue  = light_blue,
    num_hue  = purple,
    yay_hue  = orange,
    fun_hue  = dark_blue,
    adj_hue  = magenta,
};

#define _US(hue) {hue, 220, 255}

HSV layer_colors[_MAX + 1] = {
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

    HSV layer_hsv = layer_colors[layer];

    RGB layer_color  = hsv_to_rgb((HSV){layer_hsv.h, layer_hsv.s, rgb_matrix_config.hsv.v});
    RGB top_color    = layer_color;
    RGB bottom_color = color_add(layer_color, mods_color);

    for (int i = 0; i < sizeof(top_underglow) / sizeof(top_underglow[0]); i++) {
        rgb_matrix_set_color(top_underglow[i], top_color.r, top_color.g, top_color.b);
    }

    for (int i = 0; i < sizeof(bottom_underglow) / sizeof(bottom_underglow[0]); i++) {
        rgb_matrix_set_color(bottom_underglow[i], bottom_color.r, bottom_color.g, bottom_color.b);
    }

    return false;
}

// Status message
char      status_message_1[8];
char      status_message_2[8];
int32_t   status_message_time     = 0;
const int status_message_duration = 5000;
HSV       status_message_color    = {HSV_WHITE};

#define set_status_message(a, ...)                                         \
    {                                                                      \
        snprintf(status_message_1, sizeof(status_message_1), a);           \
        snprintf(status_message_2, sizeof(status_message_2), __VA_ARGS__); \
        status_message_time = timer_read32();                              \
    }

rgb_config_t prev_rgb_config;

void set_status_to_rgb_color(void) {
    status_message_color = rgb_matrix_config.hsv;
    status_message_color.v += 100;
}

void check_status_changes(void) {
    static bool first_update = true;
    if(first_update) {
        prev_rgb_config = rgb_matrix_config;
        first_update = false;
    }
    if (memcmp(&prev_rgb_config, &rgb_matrix_config, sizeof(rgb_config_t)) == 0) {
        return;
    }

    if (prev_rgb_config.enable != rgb_matrix_config.enable) {
        if (rgb_matrix_config.enable) {
            set_status_message("RGB:", "ON");
            status_message_color = rgb_matrix_config.hsv;
        } else {
            set_status_message("RGB:", "OFF");
            HSV color = {0, 0, 50};
            status_message_color = color;
        }
    } else if (prev_rgb_config.mode != rgb_matrix_config.mode) {
        set_status_message("Mode:", "%d", rgb_matrix_config.mode);
        set_status_to_rgb_color();
    } else if (prev_rgb_config.hsv.h != rgb_matrix_config.hsv.h) {
        set_status_message("Hue", "%d", rgb_matrix_config.hsv.h);
        status_message_color = rgb_matrix_config.hsv;
        set_status_to_rgb_color();
    } else if (prev_rgb_config.hsv.s != rgb_matrix_config.hsv.s) {
        set_status_message("Sat", "%d", rgb_matrix_config.hsv.s);
        set_status_to_rgb_color();
    } else if (prev_rgb_config.hsv.v != rgb_matrix_config.hsv.v) {
        set_status_message("Val", "%d", rgb_matrix_config.hsv.v);
        status_message_color = rgb_matrix_config.hsv;
    } else if (prev_rgb_config.speed != rgb_matrix_config.speed) {
        set_status_message("Speed", "%d", rgb_matrix_config.speed);
        status_message_color = rgb_matrix_config.hsv;
    }
    prev_rgb_config = rgb_matrix_config;
}
