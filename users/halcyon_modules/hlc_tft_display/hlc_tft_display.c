// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "halcyon.h"
#include "hlc_tft_display.h"

#include "qp_surface.h"

// Fonts mono2
#include "graphics/fonts/Retron2000-27.qff.h"
#include "graphics/fonts/Retron2000-underline-27.qff.h"


static painter_font_handle_t Retron27;
static painter_font_handle_t Retron27_underline;
//static painter_image_handle_t layer_number;
backlight_config_t backlight_config;

static uint16_t lcd_surface_fb[135*240];

int color_value = 0;

painter_device_t lcd;
painter_device_t lcd_surface;

led_t last_led_usb_state = {0};
layer_state_t last_layer_state = {0};

#define GRID_WIDTH 27
#define GRID_HEIGHT 48
#define CELL_SIZE 4  // Cell size excluding outline
#define OUTLINE_SIZE 1

// Define the probability factor for initial alive cells
#define INITIAL_ALIVE_PROBABILITY 0.2  // 20% chance of being alive

const char* layer_names[7] = {
    "Base",
    "Sym",
    "Ext",
    "Num",
    "Game",
    "Fun",
    "Adj"
};

extern HSV layer_colors[7];

extern char      status_message_1[8];
extern char      status_message_2[8];
extern int32_t   status_message_time;
extern const int status_message_duration;
extern HSV       status_message_color;

extern void check_status_changes(void);

uint16_t get_line_height(uint8_t row) {
    return (row) * (Retron27->line_height + 5);
}


void update_display(void) {
    static bool first_run_layer = false;

    static int32_t last_status_message_update = 0;

    if( first_run_layer == false) {
        // Load fonts
        Retron27 = qp_load_font_mem(font_Retron2000_27);
        Retron27_underline = qp_load_font_mem(font_Retron2000_underline_27);
        last_status_message_update = timer_read32();
    }

//    if(last_led_usb_state.raw != host_keyboard_led_state().raw || first_run_led == false) {
//        led_t led_usb_state = host_keyboard_led_state();
//
//        led_usb_state.caps_lock   ? qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - Retron27->line_height * 3 - 15, Retron27_underline, caps,   HSV_CAPS_ON,   HSV_BLACK) : qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - Retron27->line_height * 3 - 15, Retron27, caps,   HSV_CAPS_OFF,   HSV_BLACK);
//        led_usb_state.num_lock    ? qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - Retron27->line_height * 2 - 10, Retron27_underline, num,    HSV_NUM_ON,    HSV_BLACK) : qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - Retron27->line_height * 2 - 10, Retron27, num,    HSV_NUM_OFF,    HSV_BLACK);
//        led_usb_state.scroll_lock ? qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - Retron27->line_height - 5,      Retron27_underline, scroll, HSV_SCROLL_ON, HSV_BLACK) : qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - Retron27->line_height - 5,      Retron27, scroll, HSV_SCROLL_OFF, HSV_BLACK);
//
//        last_led_usb_state = led_usb_state;
//        first_run_led = true;
//    }

    if(last_layer_state != layer_state || first_run_layer == false) {
        uint8_t layer = get_highest_layer(layer_state|default_layer_state);
        qp_rect(lcd_surface, 5, 5, 135, 5 + Retron27->line_height, HSV_BLACK, true);
        if (layer <= 6) {
            HSV color = layer_colors[layer];
            qp_drawtext_recolor(lcd_surface, 5, 5, Retron27_underline, layer_names[layer],
                                color.h, color.s, color.v, HSV_BLACK);
        } else {
            qp_drawtext_recolor(lcd_surface, 5, 5, Retron27_underline, "Undef", HSV_WHITE, HSV_BLACK);
        }
        last_layer_state = layer_state;
        first_run_layer = true;
    }

    static uint8_t last_mod_keys = ~0;
    uint8_t mod_keys = get_mods() | get_oneshot_mods();
    if(mod_keys != last_mod_keys) {
        static const uint8_t modBits[4] = {MOD_BIT(KC_LGUI), MOD_BIT(KC_LALT), MOD_BIT(KC_LSFT), MOD_BIT(KC_LCTL)};
        static const HSV modColors[4] = {{HSV_GREEN}, {HSV_MAGENTA}, {HSV_YELLOW}, {HSV_CYAN}};
        static const HSV modInactive = {0, 0, 20};
        static const char modChars[4] = "MASC";
        static const uint8_t text_width = 20;
        for(uint8_t i = 0; i < 4; i++) {
            HSV color = (mod_keys & modBits[i]) ? modColors[i] : modInactive;
            char text[2] = " ";
            text[0] = modChars[i];
            bool isOneshot = get_oneshot_mods() & modBits[i];
            qp_drawtext_recolor(lcd_surface, 5 + i * text_width, 5 + Retron27->line_height + 5,
                                isOneshot ? Retron27_underline : Retron27, text, color.h, color.s, color.v, HSV_BLACK);
        }
    }

    check_status_changes();
    static bool last_status_message_dim = true;
    bool status_message_dim = timer_elapsed32(status_message_time) >= status_message_duration;
    if(last_status_message_update - status_message_time < 0 || last_status_message_dim != status_message_dim) {
        qp_rect(lcd_surface, 5, 5 + get_line_height(4), 135, 5 + get_line_height(6), HSV_BLACK, true);
        uint8_t line1v = status_message_dim ? 20 : 255;
        uint8_t line2v = status_message_dim ? 20 : status_message_color.v;
        qp_drawtext_recolor(lcd_surface, 5, 5 + get_line_height(4), Retron27, status_message_1, 0, 0, line1v, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, 5, 5 + get_line_height(5), Retron27, status_message_2, status_message_color.h, status_message_color.s, line2v, HSV_BLACK);
        last_status_message_update = timer_read32();
        last_status_message_dim = status_message_dim;
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

    if(!module_post_init_user()) { return false; }

    return true;
}

// Called from halcyon.c
bool display_module_housekeeping_task_kb(bool second_display) {
    if(!display_module_housekeeping_task_user(second_display)) { return false; }

    // Update display information (layers, numlock, etc.)
    update_display();

    // Move surface to lcd
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);

    return true;
}
