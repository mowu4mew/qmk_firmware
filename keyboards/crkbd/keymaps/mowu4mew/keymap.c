#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

//Declare layers
enum layer_number {
  _QWERTY = 0,
  _NUM,
  _CMD,
  _FNC,
};

//Declare custum keycodes
enum custom_keycodes {
  INS_L = SAFE_RANGE,
  KILL_L,
  CTL_ALL,
  SFT_PST,
  CMD_SPC,
  NUM_ENT,
  MBTN1,          //Left click
  MBTN2,          //Right click
  MBTN3           //Center click
};

//Declare Alias Mod Tap Layer NOB Layer
#define MT_FNC_H LT(_FNC, KC_H)       //hold:"Function"   tap:"F"

//Declare Alias Mod Tap QWERTY Layer
#define MT_CTL_A LCTL_T(KC_A)
#define MT_CTL_MIN RCTL_T(JP_MINS)
#define MT_ALT_L LALT_T(KC_L)
#define MT_ALT_S RALT_T(KC_S)
#define MT_GUI_D LGUI_T(KC_D)
#define MT_GUI_K RGUI_T(KC_K)
#define MT_SFT_V LSFT_T(KC_V)
#define MT_SFT_M RSFT_T(KC_M)

//Declare Alias Mod Tap NUM Layer
#define MT_SFT_TD LSFT_T(JP_TILD)        //hold:"SHIFT"        tap"~" JP_TILD
#define MT_SFT_YN RSFT_T(JP_YEN)           //hold:"SHIFT"        tap"\" JP_YEN

//Declare Alias Mod Tap CMD Layer
#define MT_SFT_HM LSFT_T(KC_HOME)        //hold:"GUI"        tap"."

//Declare Alias Short Cut CMD Layer
#define MC_PRTSN G(S(KC_S))           //print screen
#define MC_LOCK G(KC_L)               //Lock

//Declare Alias Layer Tap CMD Layer
#define MT_FNC_PU LT(_FNC, KC_PGUP)    //hold:"Function"   tap:"Page Up"

//Declare COMBO
enum combos{
  LK_HENK,
  SD_MHEN,
  KJ_TAB,
  DL_TAB,
  DF_ESC,
  DOT_COLON_MBTN3,
  OI_LOCK
};

const uint16_t PROGMEM lk_combo[] = {MT_ALT_L, MT_GUI_K ,COMBO_END};
const uint16_t PROGMEM sd_combo[] = {MT_ALT_S, MT_GUI_D, COMBO_END};
const uint16_t PROGMEM kj_combo[] = {MT_GUI_K, KC_J, COMBO_END};
const uint16_t PROGMEM dl_combo[] = {KC_DOWN, KC_LEFT, COMBO_END};
const uint16_t PROGMEM df_combo[] = {MT_GUI_D, KC_F, COMBO_END};
const uint16_t PROGMEM dc_combo[] = {JP_DOT, JP_COMM, COMBO_END};
const uint16_t PROGMEM oi_combo[] = {KC_O, KC_I, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [LK_HENK] = COMBO(lk_combo, JP_HENK),
  [SD_MHEN] = COMBO(sd_combo, JP_MHEN),
  [KJ_TAB] = COMBO(kj_combo, KC_TAB),
  [DL_TAB] = COMBO(dl_combo, KC_TAB),
  [DF_ESC] = COMBO(df_combo, KC_ESC),
  [DOT_COLON_MBTN3] = COMBO(dc_combo, KC_BTN3),
  [OI_LOCK] = COMBO(oi_combo, MC_LOCK)
};


//Override
const key_override_t undssft_key_override = ko_make_basic(MOD_MASK_SHIFT, MT_CTL_MIN, JP_UNDS);	//_[SHIFT & JP_MINS]
const key_override_t dquosft_key_override = ko_make_basic(MOD_MASK_SHIFT, JP_QUOT, JP_DQUO);    //"[SHIFT & JP_QUOT]
const key_override_t colnsft_key_override = ko_make_basic(MOD_MASK_SHIFT, JP_SCLN, JP_COLN);    //:[SHIFT & JP_SCLN]
const key_override_t tildsft_key_override = ko_make_basic(MOD_MASK_SHIFT, JP_TILD, JP_GRV);     //`[SHIFT & JP_TILD]
const key_override_t yensft_key_override = ko_make_basic(MOD_MASK_SHIFT, JP_YEN, JP_PIPE);      //\[SHIFT & JP_YEN]

const key_override_t **key_overrides = (const key_override_t *[]){
  &undssft_key_override,
  &dquosft_key_override,
  &colnsft_key_override,
  &tildsft_key_override,
  &yensft_key_override,
  NULL
};

//Declare tap-dance
enum tapdances{
  TD_Q_ESC
};

tap_dance_action_t tap_dance_actions[] = {
[TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |------------------------------------------------------.
      XXXXXXX,TD(TD_Q_ESC),KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,   KC_U,     KC_I,    KC_O,    KC_P, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX,MT_CTL_A,MT_ALT_S,MT_GUI_D,    KC_F,    KC_G,    MT_FNC_H,    KC_J,MT_GUI_K,MT_ALT_L,MT_CTL_MIN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    KC_X,    KC_C,MT_SFT_V,    KC_B,        KC_N,MT_SFT_M, JP_COMM,   JP_DOT, JP_SLSH,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------/   \--------+--------+--------+---------+--------+--------'
                                 XXXXXXX, CMD_SPC, XXXXXXX,     XXXXXXX, NUM_ENT, XXXXXXX
  //                           `--------+--------+--------'   `--------+--------+---------'
  ),

  [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |------------------------------------------------------.
      XXXXXXX, JP_EXLM,   JP_AT, JP_HASH, JP_DLR,  JP_PERC,     JP_CIRC, JP_AMPR, JP_ASTR, JP_PLUS,  JP_EQL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       XXXXXXX, JP_TILD, JP_QUOT, JP_LBRC, KC_LSFT, JP_LPRN,    JP_RPRN, KC_RSFT, JP_RBRC, JP_SCLN,  JP_YEN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------/   \--------+--------+--------+---------+--------+--------'
                                 XXXXXXX, _______,XXXXXXX,      XXXXXXX, _______, XXXXXXX
  //                           `--------+--------+--------'   `--------+--------+---------'
  ),

  [_CMD] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       XXXXXXX,A(KC_F4), C(KC_W),  KILL_L,MC_PRTSN, C(KC_T),    KC_BTN1, KC_BTN2,   KC_UP,   INS_L,   KC_F2, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, CTL_ALL, C(KC_S),  KC_DEL, C(KC_F), C(KC_H),     KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT,MT_FNC_PU,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_Z), C(KC_X), C(KC_C), SFT_PST, C(KC_Y),     C(KC_N),MT_SFT_HM, KC_TAB,  KC_END, KC_PGDN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, _______, XXXXXXX,     XXXXXXX, _______, XXXXXXX
  //                           `--------+--------+--------'   `--------+--------+---------'
  ),

  [_FNC] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       XXXXXXX, DM_RSTP, DM_REC1, DM_PLY1,  KC_F11,  KC_F12,     EE_CLR, QK_BOOT, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     XXXXXXX, KC_HOME, KC_PGDN,  KC_END, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, _______, XXXXXXX,     XXXXXXX, _______, XXXXXXX
  //                           `--------+--------+--------'   `--------+--------+--------'
  ),

};

//tap & hold setting
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch(keycode){
    case MT_GUI_D:
      return 250;   //短くするとホールドになりやすい。長いとタップになりやすい。
    case MT_GUI_K:
      return 250;
    case MT_SFT_V:
      return 250;
    case MT_SFT_M:
      return 250;
    case MT_CTL_A:
      return 250;
    case MT_CTL_MIN:
      return 250;
    case MT_ALT_S:
      return 250;
    case MT_ALT_L:
      return 250;
    case MT_SFT_TD:
      return 250;
    case MT_SFT_YN:
      return 250;
    case MT_SFT_HM:
      return 250;
    case MT_FNC_H:
      return 250;
    case MT_FNC_PU:
      return 250;
    case CTL_ALL:
      return 400;
    case SFT_PST:
      return 400;
    case TD_Q_ESC:
      return 60;   //短くするとタップになりやすい、長いとダブルタップになりやすい
    default:
      return TAPPING_TERM;
  }
}

//MTキー長押し先離し&2キー後離しでMTキーtap判定
bool get_hold_on_other_key(uint16_t keycode, keyrecord_t *record){
  switch(keycode){
    case ALT_T(KC_Y):
      return true;
    case CTL_T(KC_K):
      return true;
    default:
      return false;
  }
}

//MTキー長押し離しでtap
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record){
  switch(keycode){
    default:
      return false;
  }
}

///MTキーホールド判定前に次キーtapでもmod有効
bool get_permissive_hold_per_key(uint16_t keycode,keyrecord_t *record){
    switch(keycode){
        default:
            return false;
    }
}

#define HOLDING_TERM 160  //この時間以上押されるとホールド判定
#define DEAD_ZONE_TERM 50   //この時間以下は不感帯
#define ALPHA_NUM_TERM 100   //この時間以下ならalpha 以上ならnum

static bool is_cmd_spc_pressed = false;
static bool is_num_ent_pressed = false;
static uint32_t ctl_all_pressed_time = 0;
static uint32_t sft_pst_pressed_time = 0;
static uint32_t cmd_spc_pressed_time = 0;
static uint32_t num_ent_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

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

        if(timer_elapsed(num_ent_pressed_time) < HOLDING_TERM){
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

    case SFT_PST:
      if(record->event.pressed){
        sft_pst_pressed_time = record->event.time;
        register_code(KC_LSFT);
      }else{
        unregister_code(KC_LSFT);
        if(timer_elapsed(sft_pst_pressed_time) < TAPPING_TERM){
          SEND_STRING(SS_LCTL(SS_TAP(X_V)));
        }
      }
      return false;
      break;

    case KILL_L:
      if(record->event.pressed){
        SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT) SS_TAP(X_DEL));
      }
      return false;
      break;

    case INS_L:
      if(record->event.pressed){
        SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_ENT) SS_TAP(X_UP));
      }
      return false;
      break;

    default:
      return true;

  }
}

