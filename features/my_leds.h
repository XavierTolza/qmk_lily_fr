#include QMK_KEYBOARD_H
#include "config.h"

#define NB_KEYS_PER_lAYOUT 10
#define NB_RGB_LAYOUTS 10
#define ALL_MODS 0xFF

typedef struct {
    uint8_t layer;
    unsigned int mod_mask;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t nb_keys;
    uint8_t keys[NB_KEYS_PER_lAYOUT];
} rgb_layout_t;

void reset_leds(void);
void rgb_handle_layer_callback(layer_state_t state);

extern const rgb_layout_t rgb_layout[NB_RGB_LAYOUTS];