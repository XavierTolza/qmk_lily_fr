#include "encoders.h"
#include "keymap_french.h" 
#include "print.h"

bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer,layer_enabled,conf_index;
    unsigned int mods = get_mods();
    unsigned int enabled;


    for (layer=0;layer<NB_LAYERS;layer++){
        uprintf("Looping layer %d over %d\n", layer, NB_LAYERS);
        layer_enabled = IS_LAYER_ON(layer);
        if(layer_enabled){
            print("Layer enabled!\n");
            for (conf_index=0;conf_index<ENCODER_NB_CONFIGS;conf_index++){
                encoder_config_t conf = encoder_layers[layer][index][conf_index];
                uprintf("Config %d: mask %d\n",conf_index,conf.mod_mask);
                enabled = (conf.mod_mask & mods) || (conf.mod_mask == ALL_MODS);
                if(enabled){
                    print("Enabled! ");
                    if(clockwise){
                        uprintf("Going clockwise: %d\n",conf.CW);
                        tap_code16(conf.CW);
                    }
                    else{
                        uprintf("Going ANTI clockwise: %d\n",conf.ACW);
                        tap_code16(conf.ACW);

                    }

                }
            }
            break;
        }
    }
    /*
    alt_enabled = IS_LAYER_ON(_SPECIAL);
    // 0 is left-half encoder,
    // 1 is right-half encoder
    if (index == 0) {
        // Ctrl Z/Y
        if (clockwise) {
            tap_code16(LCTL(FR_Y));
        } else {
            tap_code16(LCTL(FR_Z));
        }
    } else if (index == 1) {
        // Wheel up/down
        if (clockwise) {
            if (alt_enabled){
                tap_code16(KC_PGDN);
            }
            else{
                tap_code16(KC_WH_D);
            }
        } else {
            if (alt_enabled){
                tap_code16(KC_PGUP);
            }
            else{
                tap_code16(KC_WH_U);
            }
        }
    }*/
    return true;
}