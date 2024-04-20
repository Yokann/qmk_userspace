#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _LOWER = 1,
    _RAISE = 2,
    _ADJUST = 3
};

enum tap_dance {
    TD_RSFT, // tap for right shift, double for caps lock
    TH_ENT //  tap for enter, hold for gui
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_split_3x6_3(
             KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                           KC_Y,     KC_U,     KC_I,     KC_O,      KC_P,     KC_BSPC,
            KC_LCTL,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                           KC_H,     KC_J,     KC_K,     KC_L,   KC_SCLN,     KC_QUOT,
            KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                           KC_N,     KC_M,  KC_COMM,   KC_DOT,   KC_SLSH, TD(TD_RSFT),
                                                    KC_LALT,    MO(1), KC_SPC,      TD(TH_ENT), MO(2),  KC_RALT
    ),
	[_LOWER] = LAYOUT_split_3x6_3(
             KC_TAB,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                           KC_6,     KC_7,     KC_8,     KC_9,     KC_0, KC_BSPC,
            KC_LCTL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PGUP,                        KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,  KC_HOME,  KC_END,
            KC_LSFT,  KC_PSCR,   KC_CUT,  KC_COPY,  KC_PSTE,  KC_PGDN,                        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_DEL,
                                                    KC_LALT,  _______, KC_SPC,       KC_ENT,    MO(3),  KC_RALT
    ),
	[_RAISE] = LAYOUT_split_3x6_3(
             KC_TAB,  KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,                        KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_BSPC,
            KC_LCTL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                        KC_MINS,   KC_EQL,  KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_GRV,
            KC_LSFT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                    KC_LALT,    MO(3), KC_SPC,       KC_ENT,  _______,  KC_RALT
    ),
	[_ADJUST] = LAYOUT_split_3x6_3(
              KC_F1,    KC_F2,    KC_F3,   KC_F4,     KC_F5,    KC_F6,                          KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,
            RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  XXXXXXX,  XXXXXXX,                        KC_MRWD,  KC_MPLY,  KC_MFFD,  KC_VOLU,  XXXXXXX,  XXXXXXX,
            RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  XXXXXXX,  CM_TOGG,                        XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_VOLD,  XXXXXXX,  XXXXXXX,
                                                    KC_LALT,  _______, KC_SPC,       KC_ENT,  _______,  KC_RALT
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

/**
* Combo
*/

const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};

combo_t key_combos[] = {
    COMBO(jk_combo, KC_ESC),
    COMBO(kl_combo, KC_GT),
};

/**
* Tap Dance Hold section
*/

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} td_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    tap_dance_action_t *action;

    switch (keycode) {
        // list all tap dance keycodes with tap-hold configurations
        case TD(TH_ENT):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                td_tap_hold_t *tap_hold = (td_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}

void td_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    td_tap_hold_t *tap_hold = (td_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void td_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    td_tap_hold_t *tap_hold = (td_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, td_tap_hold_finished, td_tap_hold_reset}, .user_data = (void *)&((td_tap_hold_t){tap, hold, 0}), }

/**
* Tapdance common
*/
tap_dance_action_t tap_dance_actions[] = {
    [TD_RSFT] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
    [TH_ENT]  = ACTION_TAP_DANCE_TAP_HOLD(KC_ENT, KC_LGUI)
};
