#include QMK_KEYBOARD_H
#include "keymap_french.h" 
#include "features/my_leds.h"
#include "features/encoders.h"

enum layer_number {
    _BASE = 0,
    _SPECIAL=1,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* BASE
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | ESC  |   1! |  2@  |  3#  |  4$  |  5%  |                    |  6^  |  7&  |  8*  |  9(  |  0)  |BSpace|
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   A  |   Z  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | DEL  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |LShift|   Q  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   M  | altf4|
     * |------+------+------+------+------+------|  Meh  |    | Hyper |------+------+------+------+------+------|
     * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |  ;:  |   .  |  -_  |  =+  |RCTRL |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   |LCtrl | LGUI | LAlt | / Enter /       \Space \  | RAlt | RGUI | LCtrl|
     *                   |      |      |      |/       /         \  L1  \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */
    [_BASE] = LAYOUT(
        KC_ESC, FR_1, FR_2, FR_3, FR_4, FR_5,                       FR_6, FR_7, FR_8, FR_9, FR_0, KC_BSPC,
        KC_TAB, FR_A, FR_Z, FR_E, FR_R, FR_T,                       FR_Y, FR_U, FR_I, FR_O, FR_P, KC_DEL,
        KC_LSFT, FR_Q, FR_S, FR_D, FR_F, FR_G,                     FR_H, FR_J, FR_K, FR_L, FR_M, KC_LSFT,
        KC_LCTL, FR_W, FR_X, FR_C, FR_V, FR_B, KC_MEH,              KC_HYPR, FR_N, FR_SCLN, FR_DOT, FR_MINS, KC_EQUAL,LALT(KC_F4),
                KC_LCTL, KC_LGUI, KC_LALT, LT(_SPECIAL, KC_ENT),    LT(_SPECIAL, KC_SPACE), KC_RALT, KC_RGUI, KC_LCTL
        ),

    /* SPECIAL
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  | F9   | F10  | TG(2)|
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |   ~  |   /  |   {  |   }  |   %  |                    |      |      |  Up  |   '  |   "  |   `  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |   €  |   \  |   (  |   )  |   @  |-------.    ,-------| Home | Left | Down |Right | End  |      |
     * |------+------+------+------+------+------| PgDo  |    | PgUp  |------+------+------+------+------+------|
     * |      |   $  |   |  |   [  |   ]  |   #  |-------|    |-------|   -  |   +  |   =  |   *  |   !  |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   |      |   <  |   >  | /       /       \      \  |      |      |      |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */
    [_SPECIAL] = LAYOUT(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                     KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, TG(2),
        _______, FR_TILD, FR_SLSH, FR_LCBR, FR_RCBR, FR_PERC,                           _______, _______, KC_UP, FR_QUOT, FR_DQUO, FR_GRV,
        _______, FR_EURO, FR_BSLS, FR_LPRN, FR_RPRN, FR_AT,                              KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,
        _______, _______, FR_DLR, FR_PIPE, FR_LBRC, FR_RBRC, FR_HASH, KC_PGDN,         KC_PGUP, FR_MINS, FR_PLUS, FR_EQL, FR_ASTR, FR_EXLM, _______,
                _______, FR_SUP2, FR_RABK, _______,                                     _______, _______, _______, _______
    )};

#if defined(ENCODER_ENABLE)
const encoder_config_t encoder_layers[NB_LAYERS][NUM_ENCODERS][ENCODER_NB_CONFIGS]={
    {{{ALL_MODS,LCTL(FR_Y),LCTL(FR_Z)}},{{ALL_MODS, KC_WH_D,KC_WH_U}}},
    {{{ALL_MODS,LCTL(FR_Y),LCTL(FR_Z)}},{{ALL_MODS, KC_PGDN,KC_PGUP}}},
};
#endif // defined(ENCODER_ENABLE)

const rgb_layout_t rgb_layout[NB_RGB_LAYOUTS]={
    {_SPECIAL,ALL_MODS,RGB_GOLD,5,{1,2,3,4,5}}
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_SPECIAL, KC_SPACE):
        case LT(_SPECIAL, KC_ENT):
            return 200;
        
        default:
            return TAPPING_TERM;
    }
}

// Turn off Liatris LED
void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}

void keyboard_post_init_user(void) {
    reset_leds();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgb_handle_layer_callback(state);
    return state;
}






