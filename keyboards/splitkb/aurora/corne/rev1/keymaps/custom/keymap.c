#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _LOWER = 1,
    _RAISE = 2,
    _ADJUST = 3
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_split_3x6_3(
             KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                       KC_Y, KC_U,    KC_I,   KC_O,    KC_P, KC_BSPC,
            KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G,                       KC_H, KC_J,    KC_K,   KC_L, KC_SCLN, KC_QUOT,
            KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,  KC_ESC,
                                    KC_LGUI, MO(1), KC_SPC,     KC_ENT, MO(2), KC_RALT
    ),
	[_LOWER] = LAYOUT_split_3x6_3(
             KC_TAB,    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,  KC_8,    KC_9,    KC_0, KC_BSPC,
            KC_LCTL,   KC_NO,  KC_NO,   KC_NO,   KC_NO, KC_PGUP,                   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_HOME,  KC_END,
            KC_LSFT, KC_PSCR, KC_CUT, KC_COPY, KC_PSTE, KC_PGDN,                     KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,  KC_DEL,
                                               KC_LGUI, KC_TRNS, KC_SPC,     KC_ENT, MO(3), KC_RALT
    ),
	[_RAISE] = LAYOUT_split_3x6_3(
              KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
             KC_LCTL,   KC_NO, KC_NO,   KC_NO,  KC_NO,   KC_NO,                     KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
             KC_LSFT,   KC_NO, KC_NO,   KC_NO,  KC_NO,   KC_NO,                       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                              KC_LGUI,   MO(3), KC_SPC,     KC_ENT, KC_TRNS, KC_RALT
    ),
	[_ADJUST] = LAYOUT_split_3x6_3(
              KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_F5, KC_F6,                         KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_F11, KC_F12,
            RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_NO,                       KC_MRWD, KC_MPLY, KC_MFFD, KC_VOLU,  KC_NO,  KC_NO,
            RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO, KC_NO,                         KC_NO,   KC_NO,   KC_NO, KC_VOLD,  KC_NO,  KC_NO,
                                              KC_LGUI, KC_TRNS, KC_SPC,      KC_ENT, KC_TRNS, KC_RALT
    )
};
// clang-format on

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}


