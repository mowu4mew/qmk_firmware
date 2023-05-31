#include QMK_KEYBOARD_H

//Declare custum keyCodes
enum custom_keycodes {
    INS_L = SAFE_RANGE,           //Insert Line
    KILL_L,                       //Kill Line
};

//Alias
#define MC_TOV KEY_OVERRIDE_TOGGLE  //toggle override
#define MT_SSPC LSFT_T(KC_SPC)    //hold:"Shift" tap:"Space"
#define MT_NENT LT(2,KC_ENT)      //hold:"NMB" tap:"Enter"
#define MT_FK LT(4,KC_K)          //hold:"Function" tap:"K"
#define MT_FD LT(4,KC_D)          //hold:"Function" tap:"D"
#define MT_FT LT(4,KC_T)          //hold:"Function" tap:"T"
#define MT_FE LT(4,KC_E)          //hold:"Function" tap:"E"
#define MT_ME LT(3,KC_MHEN)  //hold:"EMACS" tap:"M-Henkan"
#define MT_HE LT(3,KC_HENK)  //hold:"EMACS" tap:"Henkan"

#define MC_PSC  LGUI(S(KC_S))     //Print screen
#define MC_DTR  LGUI(C(KC_RIGHT)) //Desk top move right
#define MC_DTL  LGUI(C(KC_LEFT))  //Desk top move left
#define MC_LCK  LGUI(KC_L)        //Screen Lock
#define MC_MIN  LGUI(KC_M)        //Window Minimize
#define MC_SRH  LGUI(KC_S)        //Search
#define MC_RUN  LGUI(KC_R)        //Run

#define JP_AT KC_LBRC             // @
#define JP_CIRC KC_EQL            // ^, ~
#define JP_COLN KC_QUOT           // :, *
#define JP_LBRC KC_RBRC           // [
#define JP_RBRC KC_NUHS           // ]
#define JP_LCBR LSFT(JP_LBRC)     // {
#define JP_RCBR LSFT(JP_RBRC)     // }
#define JP_LPRN LSFT(KC_8)        // (
#define JP_RPRN LSFT(KC_9)        // )
#define JP_QUOT LSFT(KC_7)        //',"
#define JP_AMPR LSFT(KC_6)        // &
#define JP_UNDS LSFT(KC_INT1)     //_
#define JP_PLUS LSFT(KC_SCLN)     // +
#define JP_EQL LSFT(KC_MINS)      // =
#define JP_ASTR LSFT(JP_COLN)     // *
#define JP_GRV LSFT(JP_AT)        //`
#define JP_PIPE LSFT(KC_INT3)     //|
#define JP_DQUO S(KC_2) 	  //"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |------------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_T,    KC_R,    KC_V,        KC_J,    KC_U,    KC_I,    KC_H,    KC_P, JP_QUOT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______,    KC_K,    KC_S,   MT_FD,    KC_N,    KC_G,        KC_F,    KC_A,   MT_FE,    KC_O,    KC_Y, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Z,    KC_X,    KC_C,    KC_M,    KC_B,     KC_MINS,    KC_L, KC_COMM,  KC_DOT, KC_SLSH,RCS_T(JP_PIPE),
  //|--------+--------+--------+--------+--------+--------/   \--------+--------+--------+---------+--------+--------'
                                 KC_LCTL,   MT_ME, MT_SSPC,     MT_NENT,   MT_HE, KC_RALT
  //                           `--------+--------+--------'   `--------+--------+---------'
  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |------------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MO(3),    KC_A,    KC_S,   MT_FD,    KC_F,    KC_G,        KC_H,    KC_J,   MT_FK,    KC_L, KC_SCLN, JP_QUOT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,RCS_T(JP_PIPE),
  //|--------+--------+--------+--------+--------+--------/   \--------+--------+--------+---------+--------+--------'
                                 KC_LCTL, KC_MHEN, MT_SSPC,     MT_NENT, KC_HENK,  KC_RALT
  //                           `--------+--------+--------'   `--------+--------+---------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       JP_GRV, KC_EXLM,   JP_AT, KC_HASH,  KC_DLR, KC_PERC,     JP_CIRC, JP_AMPR, JP_ASTR, JP_PLUS, KC_MINS, JP_DQUO,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, JP_COLN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  JP_EQL, JP_UNDS, JP_LPRN, JP_LCBR, JP_LBRC,     JP_RBRC, JP_RCBR, JP_RPRN,  KC_DOT, KC_SLSH, JP_PIPE,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,     _______, _______,   TO(4)
  //                           `--------+--------+--------'   `--------+--------+---------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       MC_SRH, XXXXXXX,   INS_L, XXXXXXX,  MC_PSC, XXXXXXX,      MC_RUN, KC_HOME, KC_TAB,S(KC_TAB),  KC_END,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, C(KC_A),  KILL_L,  KC_DEL, C(KC_F), C(KC_H),     KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_F2,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       MC_LCK, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_Y),  KC_MS_BTN3,  KC_ENT, KC_PGDN, KC_PGUP, C(KC_Z),  MC_MIN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 _______,  MC_DTL, _______,     _______,  MC_DTR, _______
  //                           `--------+--------+--------'   `--------+--------+--------'
  ),

  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
        RESET, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,      MC_DTL, KC_HOME,  KC_TAB,S(KC_TAB), KC_END,  MC_DTR,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_WH_L,A(KC_LEFT), KC_WH_D, KC_WH_U,A(KC_RIGHT),KC_WH_R,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      EEP_RST,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   XXXXXXX,RCS(KC_TAB),KC_PGDN,KC_PGUP,C(KC_TAB),  MC_MIN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX,  MC_MIN,  MC_MIN,  KC_MS_BTN1,KC_MS_BTN2, TO(1)
  //                           `--------+--------+--------'   `--------+--------+--------'
  ),

};

#ifdef OLED_DRIVER_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_QWERTY 2
#define L_NMB 4
#define L_EMACS 8
#define L_FN 16

void oled_render_layer_state(void) {
  oled_write_P(PSTR("Layer: "), false);
  switch (layer_state) {
    case L_BASE:
      oled_write_ln_P(PSTR("NOBIX"), false);
      break;
    case L_QWERTY:
      oled_write_ln_P(PSTR("QWERTY"), false);
      break;
    case L_NMB:
      oled_write_ln_P(PSTR("Number"), false);
      break;
    case L_EMACS:
      oled_write_ln_P(PSTR("Emacs"), false);
      break;
    case L_FN:
      oled_write_ln_P(PSTR("Function"), false);
      break;
    default:
      oled_write_ln_P(PSTR("Undefined"), false);
      break;
  }
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}

#endif // OLED_DRIVER_ENABLE


static bool SHIFT_PRESSED = false;
static bool EXCEPTIONALY_SHIFT_PRESSED = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
  }

  switch (keycode) {
    case MT_SSPC:
      if(record->event.pressed){
        SHIFT_PRESSED = true;
      }else{
        SHIFT_PRESSED = false;
      }
      break;

    case KILL_L:
      if(record->event.pressed){
        SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT) SS_TAP(X_DEL));
      }
      return false;
      break;

    case INS_L:
      if(record->event.pressed){
        SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_ENT));
      }
      return false;
      break;

    case RST_MOD:
      if(record->event.pressed){
          clear_keyboard();
          layer_move(0);
        }
      return false;
      break;

    default:
      if(SHIFT_PRESSED || EXCEPTIONALY_SHIFT_PRESSED){
        switch(keycode){
          case KC_MINS:
            if(record->event.pressed){
              register_code(KC_INT1);
              EXCEPTIONALY_SHIFT_PRESSED = true;
            }else{
              unregister_code(KC_LSFT);
              if(SHIFT_PRESSED){
                register_code(KC_LSFT);
              }
              EXCEPTIONALY_SHIFT_PRESSED =false;
            }
            return false;
            break;

          case KC_SCLN:
            if(record->event.pressed){
              unregister_code(KC_LSFT);
              register_code(KC_QUOT);
              EXCEPTIONALY_SHIFT_PRESSED = true;
            }else{
              unregister_code(KC_LSFT);
              if(SHIFT_PRESSED){
                register_code(KC_LSFT);
              }
              EXCEPTIONALY_SHIFT_PRESSED =false;
            }
            return false;
            break;

          case JP_QUOT:
            if(record->event.pressed){
              register_code(KC_2);
              EXCEPTIONALY_SHIFT_PRESSED = true;
            }else{
              unregister_code(KC_LSFT);
              if(SHIFT_PRESSED){
                register_code(KC_LSFT);
              }
              EXCEPTIONALY_SHIFT_PRESSED =false;
            }
            return false;
            break;

          case KC_ESC:
            if(record->event.pressed){
              register_code(KC_EQL);
              EXCEPTIONALY_SHIFT_PRESSED = true;
            }else{
              unregister_code(KC_LSFT);
              if(SHIFT_PRESSED){
                register_code(KC_LSFT);
              }
            EXCEPTIONALY_SHIFT_PRESSED = false;
            }
            return false;
            break;

        }
      }
    }
  return true;
}
