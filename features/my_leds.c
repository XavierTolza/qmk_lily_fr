#include "my_leds.h"
#include "print.h"

// Are we in home mode (no layer enabled & an animation is displayed)
uint8_t home_mode=1;

void reset_leds(void){
    // Init the leds
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_DEFAULT_MODE);
    rgblight_set_speed_noeeprom(150);
    rgblight_set();
    home_mode=1;
}
#ifdef CUSTOM_RGB_LAYERS

void rgb_handle_layer_callback(layer_state_t state){
    uprintf("Handle layer %d\n",state);
    uint16_t rgb_layer_index;
    unsigned int mods = get_mods();
    unsigned int enabled;
    uint8_t key_index;
    uint8_t leds_has_been_reset=0;

    rgb_layout_t layout;
    for(rgb_layer_index=0;rgb_layer_index<NB_RGB_LAYOUTS;rgb_layer_index++){
        layout = rgb_layout[rgb_layer_index];
        enabled = (state==layout.layer) && ((layout.mod_mask & mods) || (layout.mod_mask == ALL_MODS));
        if(enabled){
            if(!leds_has_been_reset){
                print("Shutdown the matrix\n");
                rgblight_enable_noeeprom();
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                rgblight_setrgb(0,0,0);
                leds_has_been_reset=1;
            }
            uprintf("RGB layout %d is enabled, activating leds ",rgb_layer_index);
            for(key_index=0;key_index<layout.nb_keys;key_index++){
                uprintf("%d",layout.keys[key_index]);
                rgblight_setrgb_at(layout.r, layout.g, layout.b, layout.keys[key_index]);
            }
            print("\n");
        }else{
            uprintf("Layer %d is not active\n",layout.layer);
        }
    }
    if(leds_has_been_reset){
        // At least one layer is active
        print("One layer is active, saving changes\n");;
        rgblight_set();
        home_mode=0;
    }
    else if (!home_mode)
    {
        print("Going back to RGB home mode\n");;
        // We need to activate home layout since all layers have been disabled
        reset_leds();
    }
    
}
#endif