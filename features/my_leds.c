#include "my_leds.h"
#include "print.h"

void reset_leds(void){
    // Init the leds
    rgblight_enable_noeeprom();
    rgblight_mode(RGBLIGHT_DEFAULT_MODE);
    rgblight_set_speed_noeeprom(150);
    rgblight_set();
}

void rgb_handle_layer_callback(layer_state_t state){
    uprintf("Handle layer %d\n",state);
    uint16_t rgb_layer_index;
    unsigned int mods = get_mods();
    unsigned int enabled;
    uint8_t key_index;

    rgb_layout_t layout;
    for(rgb_layer_index=0;rgb_layer_index<NB_RGB_LAYOUTS;rgb_layer_index++){
        uprintf("RGB layout %d\n",rgb_layer_index);
        layout = rgb_layout[rgb_layer_index];
        enabled = IS_LAYER_ON(layout.layer) && ((layout.mod_mask & mods) || (layout.mod_mask == ALL_MODS));
        if(enabled){
            print("ENABLED!\n");
            for(key_index=0;key_index<layout.nb_keys;key_index++){
                rgblight_setrgb_at(layout.r, layout.g, layout.b, layout.keys[key_index]);
            }
        }
    }
    rgblight_set();
}