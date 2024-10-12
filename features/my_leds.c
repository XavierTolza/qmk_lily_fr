#include "my_leds.h"
#include "print.h"

// Are we in home mode (no layer enabled & an animation is displayed)
uint8_t home_mode=1;


void reset_leds(void){
    // Init the leds
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_DEFAULT_MODE);
    rgblight_set_speed_noeeprom(150);
    rgblight_set();
    home_mode=1;
#endif
}