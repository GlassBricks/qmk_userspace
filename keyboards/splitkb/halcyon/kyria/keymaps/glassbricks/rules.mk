# This adds module functionality to your keyboard (files found in users/halcyon_modules)
USER_NAME := halcyon_modules

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DEFAULT_MODE = RGB_MATRIX_TYPING_HEATMAP

ENCODER_ENABLE = yes

REPEAT_KEY_ENABLE = yes

NKRO_ENABLE = yes

COMBO_ENABLE = no
COMMAND_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_KEY_ENABLE = no

SRC += features/custom_shift_keys.c