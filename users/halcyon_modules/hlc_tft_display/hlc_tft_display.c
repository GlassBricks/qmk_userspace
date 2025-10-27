// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "color.h"
#include "keycode_config.h"
#include "keycodes.h"
#include "quantum.h"
#include "halcyon.h"
#include "hlc_tft_display.h"

#include "qp_surface.h"

// Fonts mono2
#include "graphics/fonts/Retron2000-27.qff.h"
#include "graphics/fonts/Retron2000-underline-27.qff.h"
#include "timer.h"

#include <stdint.h>

static painter_font_handle_t Retron27;
static painter_font_handle_t Retron27_underline;
// static painter_image_handle_t layer_number;
backlight_config_t backlight_config;

static uint16_t lcd_surface_fb[135 * 240];

int color_value = 0;

painter_device_t lcd;
painter_device_t lcd_surface;

led_t last_led_usb_state = {0};

extern const char *const layer_names[6 + 1];
extern HSV               layer_colors[6 + 1];
extern const uint8_t     num_layers;

extern char      status_message_1[8];
extern char      status_message_2[8];
extern int32_t   status_message_time;
extern const int status_message_duration;
extern HSV       status_message_color;

extern void check_status_changes(void);

uint16_t get_line_height(uint8_t row) {
    return 5 + (row) * (Retron27->line_height + 5);
}

bool caps_word_changed = false;
bool caps_word_state   = false;
void caps_word_set_user(bool active) {
    caps_word_changed = true;
    caps_word_state   = active;
}


extern bool sentence_case_changed;
extern bool is_sentence_case_primed(void);

void update_display(void) {
    static bool first_run = false;

    static int32_t last_status_message_update = 0;

    if (!first_run) {
        // Load fonts
        Retron27                   = qp_load_font_mem(font_Retron2000_27);
        Retron27_underline         = qp_load_font_mem(font_Retron2000_underline_27);
        first_run                  = true;
        last_status_message_update = timer_read32();
    }

    bool layer_changed;
    {
        // set to ~0 to force update first time
        static layer_state_t last_layer_state = ~0;
        layer_changed                         = last_layer_state != layer_state;
        last_layer_state                      = layer_state;
    }

    bool ctrl_gui_swap = keymap_config.swap_lctl_lgui;
    bool ctrl_gui_swap_changed;
    {
        static bool last_ctrl_gui_swapped = false;
        ctrl_gui_swap_changed             = last_ctrl_gui_swapped != ctrl_gui_swap;
        last_ctrl_gui_swapped             = ctrl_gui_swap;
    }

    uint8_t mod_keys = get_mods() | get_oneshot_mods();
    bool    mod_keys_changed;
    {
        static uint8_t last_mod_keys = ~0;
        mod_keys_changed             = last_mod_keys != mod_keys;
        last_mod_keys                = mod_keys;
    }

    bool status_message_dim = timer_elapsed32(status_message_time) >= status_message_duration;
    bool status_message_dim_changed;
    {
        static bool last_status_message_dim = true;
        status_message_dim_changed          = last_status_message_dim != status_message_dim;
        last_status_message_dim             = status_message_dim;
    }

    if (layer_changed) {
        uint8_t layer = get_highest_layer(layer_state | default_layer_state);
        qp_rect(lcd_surface, 5, 5, 135, 5 + Retron27->line_height, HSV_BLACK, true);
        if (layer < num_layers) {
            HSV color = layer_colors[layer];
            qp_drawtext_recolor(lcd_surface, 5, 5, Retron27_underline, layer_names[layer], color.h, color.s, color.v, HSV_BLACK);
        } else {
            qp_drawtext_recolor(lcd_surface, 5, 5, Retron27_underline, "Undef", HSV_WHITE, HSV_BLACK);
        }
    }

    if (mod_keys_changed || ctrl_gui_swap_changed) {
        static const uint8_t modBits[4]   = {MOD_BIT(KC_LGUI), MOD_BIT(KC_LALT), MOD_BIT(KC_LSFT), MOD_BIT(KC_LCTL)};
        static const HSV     modColors[4] = {{HSV_GREEN}, {HSV_MAGENTA}, {HSV_YELLOW}, {HSV_CYAN}};
        static const HSV     modInactive  = {0, 0, 20};
        static const char   *modChars     = "MASC";
        static const uint8_t text_width   = 20;
        for (uint8_t i = 0; i < 4; i++) {
            uint8_t modIndex;
            if (ctrl_gui_swap && (i == 0 || i == 3)) {
                modIndex = 3 - i; // swap ctrl and gui
            } else {
                modIndex = i;
            }
            const uint8_t modBit    = modBits[modIndex];
            HSV           color     = (mod_keys & modBit) ? modColors[modIndex] : modInactive;
            bool          isOneshot = get_oneshot_mods() & modBit;

            char text[2] = " ";
            text[0]      = modChars[modIndex];
            qp_drawtext_recolor(lcd_surface, 5 + i * text_width, get_line_height(1), isOneshot ? Retron27_underline : Retron27, text, color.h, color.s, color.v, HSV_BLACK);
        }
    }

    if (caps_word_changed || sentence_case_changed) {
        if (caps_word_state) {
            qp_drawtext_recolor(lcd_surface, 5, get_line_height(2), Retron27, "C Word", HSV_TURQUOISE, HSV_BLACK);
        } else if (is_sentence_case_primed()) {
            qp_drawtext_recolor(lcd_surface, 5, get_line_height(2), Retron27, "...A", HSV_TURQUOISE, HSV_BLACK);
        } else {
            qp_rect(lcd_surface, 5, get_line_height(2), 135, get_line_height(2) + Retron27->line_height, HSV_BLACK, true);
        }
        sentence_case_changed = false;
        caps_word_changed     = false;
    }

    if (ctrl_gui_swap_changed) {
        if (ctrl_gui_swap) {
            qp_drawtext_recolor(lcd_surface, 5, get_line_height(3), Retron27, "Cm Swap", HSV_TURQUOISE, HSV_BLACK);
        } else {
            qp_rect(lcd_surface, 5, get_line_height(3), 135, get_line_height(3) + Retron27->line_height, HSV_BLACK, true);
        }
    }

    check_status_changes();
    if (status_message_dim_changed || last_status_message_update - status_message_time < 0) {
        qp_rect(lcd_surface, 5, get_line_height(5), 135, get_line_height(7), HSV_BLACK, true);
        uint8_t line1v = status_message_dim ? 20 : 255;
        uint8_t line2v = status_message_dim ? 20 : status_message_color.v;
        qp_drawtext_recolor(lcd_surface, 5, get_line_height(5), Retron27, status_message_1, 0, 0, line1v, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, 5, get_line_height(6), Retron27, status_message_2, status_message_color.h, status_message_color.s, line2v, HSV_BLACK);
        last_status_message_update = timer_read32();
    }
}

// Quantum function
void suspend_power_down_kb(void) {
    qp_power(lcd, false);
    suspend_power_down_user();
}

// Quantum function
void suspend_wakeup_init_kb(void) {
    qp_power(lcd, true);
    suspend_wakeup_init_user();
}

// Called from halcyon.c
bool module_post_init_kb(void) {
    setPinOutput(LCD_RST_PIN);
    writePinHigh(LCD_RST_PIN);

    // Initialise the LCD
    lcd = qp_st7789_make_spi_device(LCD_WIDTH, LCD_HEIGHT, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, LCD_SPI_MODE);
    qp_init(lcd, LCD_ROTATION);
    qp_set_viewport_offsets(lcd, LCD_OFFSET_X, LCD_OFFSET_Y);

    // Initialise surface
    lcd_surface = qp_make_rgb565_surface(LCD_WIDTH, LCD_HEIGHT, lcd_surface_fb);
    qp_init(lcd_surface, LCD_ROTATION);

    // Turn on the LCD and clear the display
    qp_power(lcd, true);
    qp_rect(lcd, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, HSV_BLACK, true);
    qp_flush(lcd);

    // Turn on backlight
    backlight_enable();

    if (!module_post_init_user()) {
        return false;
    }

    return true;
}

// Called from halcyon.c
bool display_module_housekeeping_task_kb(bool second_display) {
    if (!display_module_housekeeping_task_user(second_display)) {
        return false;
    }

    // Update display information (layers, numlock, etc.)
    update_display();

    // Move surface to lcd
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);

    return true;
}
