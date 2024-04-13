#include QMK_KEYBOARD_H
#include "config.h"

#define ENCODER_NB_CONFIGS 4
#define ALL_MODS 0xFF
#define NB_LAYERS 3

typedef struct{
    uint8_t mod_mask; // Mask when a modifier is enabled
    uint16_t CW; // Clockwise
    uint16_t ACW; // Anti-Clockwise
}encoder_config_t;


extern const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const encoder_config_t encoder_layers[NB_LAYERS][NUM_ENCODERS][ENCODER_NB_CONFIGS];