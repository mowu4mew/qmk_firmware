#include QMK_KEYBOARD_H
#include "pointing_device.h"
#include "keymap_japanese.h"

//Declare layers
enum layer_number {
  _QWERTY = 0,
  _NUM,
  _CMD,
  _MOUSE,
  _FNC,
};

//Declare custum keycodes
enum custom_keycodes {
  INS_L = SAFE_RANGE,
  KILL_L,
  CTL_ALL,
  ALT_SAVE,
  SFT_FIND,
  CMD_SPC,
  NUM_ENT,
  MBTN1,          //Left click
  MBTN2,          //Right click
  MBTN3,          //Center click
  SCRL
};

//Declare key state
enum key_state{
  RELEASED,
  PRESSED,
  HOLDEN
};

//Declare Alias Mod Tap QWERTY Layer
#define CTL_A LCTL_T(KC_A)
#define CTL_MIN RCTL_T(JP_MINS)
#define ALT_S LALT_T(KC_S)
#define ALT_L RALT_T(KC_L)
#define GUI_G LGUI_T(KC_G)
#define GUI_H RGUI_T(KC_H)
#define SFT_F LSFT_T(KC_F)
#define SFT_J RSFT_T(KC_J)

//Declare Alias Short Cut
#define MCPRTSCR G(S(KC_S))   //print screen
#define QUIT A(KC_F4)         //apli quit
#define RECVT G(JP_SLSH)      //re convert ime
#define PG_TOP C(KC_HOME)     //go page top
#define PG_BTM C(KC_END)      //go page bottom

//Declare COMBO
enum combos{
  LK_HENK,
  SD_MHEN,
  KJ_TAB,
  DL_TAB,
  DF_ESC,
  DOT_COLON_MBTN3,
  WE_PRTSCN
};

const uint16_t PROGMEM lk_combo[] = {ALT_L, KC_K ,COMBO_END};
const uint16_t PROGMEM sd_combo[] = {ALT_S, KC_D, COMBO_END};
const uint16_t PROGMEM kj_combo[] = {KC_K, SFT_J, COMBO_END};
const uint16_t PROGMEM dl_combo[] = {KC_DOWN, KC_LEFT, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, SFT_F, COMBO_END};
const uint16_t PROGMEM dc_combo[] = {JP_DOT, JP_COMM, COMBO_END};
const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [LK_HENK] = COMBO(lk_combo, JP_HENK),
  [SD_MHEN] = COMBO(sd_combo, JP_MHEN),
  [KJ_TAB] = COMBO(kj_combo, KC_TAB),
  [DL_TAB] = COMBO(dl_combo, KC_TAB),
  [DF_ESC] = COMBO(df_combo, KC_ESC),
  [DOT_COLON_MBTN3] = COMBO(dc_combo, MBTN3),
  [WE_PRTSCN] = COMBO(we_combo, MCPRTSCR)
};


//Override
const key_override_t undssft_key_override = ko_make_basic(MOD_MASK_SHIFT, CTL_MIN, JP_UNDS);	//_[SHIFT & JP_MINS]

const key_override_t *key_overrides[] = {
  &undssft_key_override,
  NULL
};

//Declare tap-dance
enum tapdances{
  Q_ESC
};

tap_dance_action_t tap_dance_actions[] = {
[Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC)
};

//keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------.
     XXXXXXX,TD(Q_ESC),    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,   KC_U,     KC_I,    KC_O,    KC_P, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   CTL_A,   ALT_S,    KC_D,   SFT_F,   GUI_G,                      GUI_H,   SFT_J,    KC_K,   ALT_L, CTL_MIN,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                       KC_N,    KC_M, JP_COMM,  JP_DOT, JP_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 JP_MHEN, CMD_SPC, XXXXXXX,                 MO(_MOUSE), NUM_ENT, JP_HENK
  //                           `--------+--------+--------'                  `--------+--------+--------'
  ),

  [_NUM] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------.
      XXXXXXX, JP_EXLM,   JP_AT, JP_HASH, JP_DLR,  JP_PERC,                    JP_CIRC, JP_AMPR, JP_ASTR, JP_PLUS,  JP_EQL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, JP_TILD, JP_QUOT, JP_LBRC,MO(_FNC), JP_LPRN,                    JP_RPRN,MO(_FNC), JP_RBRC, JP_SCLN,  JP_YEN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 JP_MHEN, CMD_SPC, XXXXXXX,                 MO(_MOUSE), _______, JP_HENK
  //  	                       `--------+--------+--------'                  `--------+--------+--------'
  ),

  [_CMD] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------
      XXXXXXX,    QUIT, C(KC_W),  KC_TAB, C(KC_H), C(KC_T),                      MBTN1,   MBTN2,   KC_UP, KC_PGUP,   INS_L, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, CTL_ALL,ALT_SAVE,  KC_DEL,SFT_FIND,   KC_F5,                    KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT,MO(_FNC), XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_Y),                    C(KC_N), KC_PGDN,   KC_F2,  KC_ESC,   RECVT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 JP_MHEN, _______, XXXXXXX,                 MO(_MOUSE), NUM_ENT, JP_HENK
  //                           `--------+--------+--------'                  `--------+--------+--------'
  ),

  [_MOUSE] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------.
      XXXXXXX, _______, _______, _______, _______, _______,                      MBTN1,   MBTN2, _______, _______, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, _______, _______, _______, _______, _______,                       SCRL, KC_RSFT, KC_RCTL, _______, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, _______, _______, _______, _______, _______,                    C(KC_X), C(KC_C), C(KC_V), _______, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 JP_MHEN, CMD_SPC, XXXXXXX,                    _______, _______, JP_HENK
  //                           `--------+--------+--------'                  `--------+--------+--------'
  ),

  [_FNC] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------.
      XXXXXXX,  KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,                      KC_F9,  KC_F10,  PG_TOP, _______, QK_BOOT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_F1,   KC_F2,  KILL_L,   KC_F3,  KC_F11,                     KC_F12, KC_HOME,  PG_BTM,  KC_END, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  JP_GRV, JP_DQUO, JP_LCBR, _______, JP_LPRN,                    JP_RPRN, _______, JP_RCBR, JP_COLN, JP_PIPE, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 JP_MHEN, CMD_SPC, XXXXXXX,                 MO(_MOUSE), NUM_ENT, JP_HENK
  //                           `--------+--------+--------'                  `--------+--------+--------'
  ),

};

//tap & hold setting
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch(keycode){
    case CTL_A:
      return 250;//短くするとホールドになりやすい。長いとタップになりやすい。
    case CTL_MIN:
      return 250;
    case ALT_S:
      return 250;
    case ALT_L:
      return 250;
    case GUI_G:
      return 250;
    case GUI_H:
      return 250;
    case SFT_F:
      return 250;
    case SFT_J:
      return 250;
    case Q_ESC:
      return 60;   //短くするとタップになりやすい、長いとダブルタップになりやすい
    default:
      return TAPPING_TERM;
  }
}

#define HOLDING_TERM 160  //この時間以上押されるとホールド判定
#define DEAD_ZONE_TERM 50   //この時間以下は不感帯
#define ALPHA_NUM_TERM 100   //この時間以下ならalpha 以上ならnum

static bool is_scroll_mode;
static bool is_cmd_spc_pressed = false;
static bool is_num_ent_pressed = false;
static uint16_t ctl_all_pressed_time = 0;
static uint16_t alt_save_pressed_time = 0;
static uint16_t sft_find_pressed_time = 0;
static uint16_t cmd_spc_pressed_time = 0;
static uint16_t num_ent_pressed_time = 0;
static uint16_t ctl_min_pressed_time = 0;

enum key_state alt_save_state = RELEASED;
enum key_state ctl_min_state = RELEASED;


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  report_mouse_t currentReport = {};

  switch (keycode) {
    case CMD_SPC:
      if(record->event.pressed){
        cmd_spc_pressed_time = record->event.time;
        is_cmd_spc_pressed = true;
        layer_on(_CMD);
        update_tri_layer(_NUM, _CMD, _QWERTY);
        if(IS_LAYER_ON(_QWERTY)){
          layer_off(_CMD);
          layer_off(_NUM);
          register_code(KC_LSFT);
        }
      }else{
        is_cmd_spc_pressed = false;
        if(is_num_ent_pressed){
          layer_on(_NUM);
        }else{
          layer_off(_CMD);
        }
        unregister_code(KC_LSFT);

        if(timer_elapsed(cmd_spc_pressed_time) < HOLDING_TERM){
          tap_code(KC_SPC);
        }
      }
      return false;
      break;

    case NUM_ENT:
      if(record->event.pressed){
        num_ent_pressed_time = record->event.time;
        is_num_ent_pressed = true;
        layer_on(_NUM);
        update_tri_layer(_NUM, _CMD, _QWERTY);
        if(IS_LAYER_ON(_QWERTY)){
          layer_off(_CMD);
          layer_off(_NUM);
          register_code(KC_LSFT);
        }
      }else{
        is_num_ent_pressed = false;
        if(is_cmd_spc_pressed){
          layer_on(_CMD);
        }else{
          layer_off(_NUM);
        }
        unregister_code(KC_LSFT);

        if(timer_elapsed(num_ent_pressed_time) < TAPPING_TERM){
          tap_code(KC_ENT);
        }
      }
      return false;
      break;

     case CTL_ALL:
      if(record->event.pressed){
        ctl_all_pressed_time = record->event.time;
        register_code(KC_LCTL);
      }else{
        unregister_code(KC_LCTL);
        if(timer_elapsed(ctl_all_pressed_time) < TAPPING_TERM){
          SEND_STRING(SS_LCTL(SS_TAP(X_A)));
        }
      }
      return false;
      break;

    case ALT_SAVE:
      if(record->event.pressed){
        alt_save_pressed_time = record->event.time;
        alt_save_state = PRESSED;
      }else{
        switch (alt_save_state) {
          case PRESSED:
            SEND_STRING(SS_LCTL(SS_TAP(X_S)));
            break;
          case HOLDEN:
            unregister_code(KC_LALT);
            break;
          case RELEASED:
            break;
        }
        alt_save_state = RELEASED;
      }
      return false;
      break;

    case SFT_FIND:
      if(record->event.pressed){
        sft_find_pressed_time = record->event.time;
        register_code(KC_LSFT);
      }else{
        unregister_code(KC_LSFT);
        if(timer_elapsed(sft_find_pressed_time) < TAPPING_TERM){
          SEND_STRING(SS_LCTL(SS_TAP(X_F)));
        }
      }
      return false;
      break;

    case KILL_L:
      if(record->event.pressed){
        tap_code16(S(KC_END));
        tap_code(KC_DEL);
      }
      return false;
      break;

    case INS_L:
      if(record->event.pressed){
        SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_ENT) SS_TAP(X_UP));
      }
      return false;
      break;

    case MBTN1:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN1;
      }else {
        currentReport.buttons &= ~MOUSE_BTN1;
      }
      pointing_device_set_report(currentReport);
      return false;
      break;

    case MBTN2:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN2;
      }else {
        currentReport.buttons &= ~MOUSE_BTN2;
      }
      pointing_device_set_report(currentReport);
      return false;
      break;

    case MBTN3:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN3;
      }else {
        currentReport.buttons &= ~MOUSE_BTN3;
      }
      pointing_device_set_report(currentReport);
      return false;
      break;

    case SCRL:
      if (record->event.pressed){
        is_scroll_mode = true;
      }else{
        is_scroll_mode = false;
      }
      return false;
      break;
      
    case CTL_MIN:
      if(record->event.pressed){
        ctl_min_pressed_time = record->event.time;
        ctl_min_state = PRESSED;
      }else{
        if(ctl_min_state == HOLDEN){
          unregister_code(JP_MINS);
        }
        ctl_min_state = RELEASED;
      }
      
    default:
      if(alt_save_state == PRESSED){
        register_code(KC_LALT);
        alt_save_state = HOLDEN;
      }
      return true;
  }
}

void matrix_scan_user(void){
  if(ctl_min_state == PRESSED && timer_elapsed(ctl_min_pressed_time) > TAPPING_TERM){
    register_code(JP_MINS);
    ctl_min_state = HOLDEN;
  }
}

static int16_t h_acm = 0;
static int16_t v_acm = 0;

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {

    double rad = 45 * (M_PI / 180) * -1;
    int8_t x_rev =  + mouse_report.x * cos(rad) - mouse_report.y * sin(rad);
    int8_t y_rev =  + mouse_report.x * sin(rad) + mouse_report.y * cos(rad);

    if (is_scroll_mode) {
        // rock scroll direction
        if (abs(x_rev) > abs(y_rev)) {
            y_rev = 0;
        } else {
            x_rev = 0;
        }

        /* accumulate scroll
        h_acm += x_rev * cocot_config.scrl_inv;
        v_acm += y_rev * cocot_config.scrl_inv * -1;

        int8_t h_rev = h_acm >> scrl_div_array[cocot_config.scrl_div];
        int8_t v_rev = v_acm >> scrl_div_array[cocot_config.scrl_div];
        */
        // clear accumulated scroll on assignment

        h_acm += x_rev;
        v_acm += y_rev;

        int8_t h_rev = h_acm;
        int8_t v_rev = v_acm;

        if (h_rev != 0) {
            if (mouse_report.h + h_rev > 127) {
                h_rev = 127 - mouse_report.h;
            } else if (mouse_report.h + h_rev < -127) {
                h_rev = -127 - mouse_report.h;
            }
            mouse_report.h += h_rev;
            h_acm -= h_rev;
        }
        if (v_rev != 0) {
            if (mouse_report.v + v_rev > 127) {
                v_rev = 127 - mouse_report.v;
            } else if (mouse_report.v + v_rev < -127) {
                v_rev = -127 - mouse_report.v;
            }
            mouse_report.v += v_rev;
            v_acm -= v_rev;
        }

        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        mouse_report.x = x_rev;
        mouse_report.y = y_rev;
    }

    return pointing_device_task_user(mouse_report);
}

layer_state_t layer_state_set_user(layer_state_t state){
  switch(get_highest_layer(state)){
    case _NUM:
      is_scroll_mode = true;
      break;
    default:
      break;
  }
  return state;
}

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_FNC);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}

uint16_t keycode_config(uint16_t keycode) {
  return keycode;
}

uint8_t mod_config(uint8_t mod) {
  return mod;
}