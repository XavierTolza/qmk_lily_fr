#include QMK_KEYBOARD_H
#include "keymap_french.h"
#include "features/my_leds.h"
#include "features/encoders.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

#define NB_CUSTOM_MODIFIERS 10

enum layer_number
{
    _BASE = 0,
    _SPECIAL = 1,
};

enum my_keycodes
{
    VSCODE = SAFE_RANGE,
    GIT,
    AI,
    DEBUG
};

const uint16_t keycodes_equivalent[] = {FR_V, FR_G, FR_I, FR_D};

uint16_t last_custom_pressed;
uint8_t nb_custom_pressed = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* BASE
     * ,-----------------------------------------.                                ,-----------------------------------------.
     * | ESC  |   1! |  2@  |  3#  |  4$  |  5%  |                                |  6^  |  7&  |  8*  |  9(  |  0)  |BSpace|
     * |------+------+------+------+------+------|                                |------+------+------+------+------+------|
     * | Tab  |   A  |   Z  |   E  |   R  |   T  |                                |   Y  |   U  |   I  |   O  |   P  | DEL  |
     * |------+------+------+------+------+------|                                |------+------+------+------+------+------|
     * |LShift|   Q  |   S  |   D  |   F  |   G  |-------.  WLup    PGup  ,-------|   H  |   J  |   K  |   L  |   M  | DEBUG|
     * |------+------+------+------+------+------| click |  WLdn    PGdn  | PSCR  |------+------+------+------+------+------|
     * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------|                |-------|   N  |  ,?  |  ;.  |  :/  |  !§  |  AI  |
     * `-----------------------------------------/       /                 \      \-----------------------------------------'
     *                   |      | LGUI | LAlt | / Enter /                   \Space \  |  L1  | GIT  |VSCODE|
     *                   |      |      |      |/       /                     \      \ |      |      |      |
     *                   `----------------------------'                       '------''--------------------'
     */
    [_BASE] = LAYOUT(
        KC_ESC, FR_AMPR, FR_EACU, FR_DQUO, FR_QUOT, FR_LPRN, FR_MINS, FR_EGRV, FR_UNDS, FR_CCED, FR_AGRV, KC_BSPC,
        KC_TAB, FR_A, FR_Z, FR_E, FR_R, FR_T, FR_Y, FR_U, FR_I, FR_O, FR_P, KC_DEL,
        LSFT_T(FR_LPRN), FR_Q, FR_S, FR_D, FR_F, FR_G, FR_H, FR_J, FR_K, FR_L, FR_M, DEBUG,
        KC_LCTL, FR_W, FR_X, FR_C, FR_V, FR_B, KC_BTN1, KC_PSCR, FR_N, FR_COMM, FR_SCLN, FR_COLN, FR_EXLM, AI,
        KC_NO, KC_LGUI, KC_LALT, KC_ENT, KC_SPACE, MO(_SPECIAL), GIT, VSCODE),

    /* SPECIAL
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | F12  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  | F9   | F10  | F11  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |   ~  |   /  |   {  |   }  |   %  |                    |      |      |  Up  |   '  |   "  |   `  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |   €  |   \  |   (  |   )  |   @  |-------.    ,-------| Home | Left | Down |Right | End  |      |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * |      |   $  |   |  |   [  |   ]  |   #  |-------|    |-------|   -  |   +  |   =  |   *  |   !  |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   |      |   <  |   >  | /       /       \      \  |      |      |      |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */
    [_SPECIAL] = LAYOUT(
        KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
        KC_NO, FR_TILD, FR_SLSH, FR_LCBR, FR_RCBR, FR_PERC, KC_NO, KC_NO, KC_UP, FR_QUOT, FR_DQUO, FR_GRV,
        KC_NO, FR_EURO, FR_BSLS, FR_LPRN, FR_RPRN, FR_AT, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, KC_NO,
        KC_NO, FR_DLR, FR_PIPE, FR_LBRC, FR_RBRC, FR_HASH, KC_NO, KC_NO, FR_MINS, FR_PLUS, FR_EQL, FR_ASTR, FR_EXLM, KC_NO,
        KC_NO, FR_LABK, FR_RABK, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)};

#if defined(ENCODER_ENABLE)
const encoder_config_t encoder_layers[NB_LAYERS][NUM_ENCODERS][ENCODER_NB_CONFIGS] = {
    {{{ALL_MODS, KC_WH_U, KC_WH_D}}, {{ALL_MODS, KC_PGUP, KC_PGDN}}},
    {{{ALL_MODS, KC_NO, KC_NO}}, {{ALL_MODS, KC_NO, KC_NO}}},
};
#endif // defined(ENCODER_ENABLE)

// Turn off Liatris LED
void keyboard_pre_init_user(void)
{
    // Set our LED pin as output
    setPinOutput(24);
    // Turn the LED off
    // (Due to technical reasons, high is off and low is on)
    writePinHigh(24);
}

void keyboard_post_init_user(void)
{
    reset_leds();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    const bool pressed = record->event.pressed;
    if (keycode > SAFE_RANGE)
    {
        const uint8_t offset = keycode - SAFE_RANGE;
        // Record is modifier is pressed
        last_custom_pressed = keycodes_equivalent[offset];
        nb_custom_pressed += pressed ? 1 : -1;
        return false;
    }
    else if (nb_custom_pressed > 0)
    {
        // Process key chords
        tap_code16(LALT(last_custom_pressed));
        tap_code(keycode);
        return false;
    }
    return true;
}
