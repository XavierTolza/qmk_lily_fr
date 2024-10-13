#include "my_leds.h"
#include "print.h"

void reset_leds(void)
{
    // Init the leds
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_DEFAULT_MODE);
    rgblight_set_speed_noeeprom(150);
    rgblight_set();
#endif
}