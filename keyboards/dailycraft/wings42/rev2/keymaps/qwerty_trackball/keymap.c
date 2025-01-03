#include QMK_KEYBOARD_H
#include "pointing_device.h"
#include "keymap_japanese.h"

//ref takash
#include QMK_KEYBOARD_H
#include <stdio.h>

/////////////////////////////
/// miniZoneの実装 ここから ///
////////////////////////////

enum custom_keycodes {
    KC_MY_BTN1 = SAFE_RANGE,
    KC_MY_BTN2,
    KC_MY_BTN3,
    KC_MY_SCR,
    KC_TO_CLICKABLE_INC,
    KC_TO_CLICKABLE_DEC,
    KC_SCROLL_DIR_V,
    KC_SCROLL_DIR_H,
};


enum click_state {
    NONE = 0,
    WAITING,    // マウスレイヤーが有効になるのを待つ。 Wait for mouse layer to activate.
    CLICKABLE,  // マウスレイヤー有効になりクリック入力が取れる。 Mouse layer is enabled to take click input.
    CLICKING,   // クリック中。 Clicking.
    SCROLLING   // スクロール中。 Scrolling.
};

typedef union {
  uint32_t raw;
  struct {
    // int16_t to_clickable_time; // // この秒数(千分の一秒)、WAITING状態ならクリックレイヤーが有効になる。  For this number of seconds (milliseconds), if in WAITING state, the click layer is activated.
    int16_t to_clickable_movement;
    bool mouse_scroll_v_reverse;
    bool mouse_scroll_h_reverse;
  };
} user_config_t;

user_config_t user_config;

enum click_state state;     // 現在のクリック入力受付の状態 Current click input reception status
uint16_t click_timer;       // タイマー。状態に応じて時間で判定する。 Timer. Time to determine the state of the system.

// uint16_t to_clickable_time = 50;   // この秒数(千分の一秒)、WAITING状態ならクリックレイヤーが有効になる。  For this number of seconds (milliseconds), if in WAITING state, the click layer is activated.
uint16_t to_reset_time = 1000; // この秒数(千分の一秒)、CLICKABLE状態ならクリックレイヤーが無効になる。 For this number of seconds (milliseconds), the click layer is disabled if in CLICKABLE state.

const uint16_t click_layer = 8;   // マウス入力が可能になった際に有効になるレイヤー。Layers enabled when mouse input is enabled

int16_t scroll_v_mouse_interval_counter;   // 垂直スクロールの入力をカウントする。　Counting Vertical Scroll Inputs
int16_t scroll_h_mouse_interval_counter;   // 水平スクロールの入力をカウントする。  Counts horizontal scrolling inputs.

int16_t scroll_v_threshold = 50;    // この閾値を超える度に垂直スクロールが実行される。 Vertical scrolling is performed each time this threshold is exceeded.
int16_t scroll_h_threshold = 50;    // この閾値を超える度に水平スクロールが実行される。 Each time this threshold is exceeded, horizontal scrolling is performed.

int16_t after_click_lock_movement = 0;      // クリック入力後の移動量を測定する変数。 Variable that measures the amount of movement after a click input.

int16_t mouse_record_threshold = 30;    // ポインターの動きを一時的に記録するフレーム数。 Number of frames in which the pointer movement is temporarily recorded.
int16_t mouse_move_count_ratio = 5;     // ポインターの動きを再生する際の移動フレームの係数。 The coefficient of the moving frame when replaying the pointer movement.

const uint16_t ignore_disable_mouse_layer_keys[] = {KC_LGUI, KC_LCTL};   // この配列で指定されたキーはマウスレイヤー中に押下してもマウスレイヤーを解除しない

int16_t mouse_movement;

void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.to_clickable_movement = 50;
    user_config.mouse_scroll_v_reverse = false;
    user_config.mouse_scroll_h_reverse = false;
    eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
}

// クリック用のレイヤーを有効にする。　Enable layers for clicks
void enable_click_layer(void) {
    layer_on(click_layer);
    click_timer = timer_read();
    state = CLICKABLE;
}

// クリック用のレイヤーを無効にする。 Disable layers for clicks.
void disable_click_layer(void) {
    state = NONE;
    layer_off(click_layer);
    scroll_v_mouse_interval_counter = 0;
    scroll_h_mouse_interval_counter = 0;
}

// 自前の絶対数を返す関数。 Functions that return absolute numbers.
int16_t my_abs(int16_t num) {
    if (num < 0) {
        num = -num;
    }

    return num;
}

// 自前の符号を返す関数。 Function to return the sign.
int16_t mmouse_move_y_sign(int16_t num) {
    if (num < 0) {
        return -1;
    }

    return 1;
}

// 現在クリックが可能な状態か。 Is it currently clickable?
bool is_clickable_mode(void) {
    return state == CLICKABLE || state == CLICKING || state == SCROLLING;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    
    switch (keycode) {
        case KC_MY_BTN1:
        case KC_MY_BTN2:
        case KC_MY_BTN3:
        {
            report_mouse_t currentReport = pointing_device_get_report();

            // どこのビットを対象にするか。 Which bits are to be targeted?
            uint8_t btn = 1 << (keycode - KC_MY_BTN1);
            
            if (record->event.pressed) {
                // ビットORは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットのどちらかが「1」の場合に「1」にします。
                // Bit OR compares bits in the same position on the left and right sides of the operator and sets them to "1" if either of both bits is "1".
                currentReport.buttons |= btn;
                state = CLICKING;
                after_click_lock_movement = 30;
            } else {
                // ビットANDは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットが共に「1」の場合だけ「1」にします。
                // Bit AND compares the bits in the same position on the left and right sides of the operator and sets them to "1" only if both bits are "1" together.
                currentReport.buttons &= ~btn;
            }

            enable_click_layer();

            pointing_device_set_report(currentReport);
            pointing_device_send();
            return false;
        }

        case KC_MY_SCR:
            if (record->event.pressed) {
                state = SCROLLING;
            } else {
                enable_click_layer();   // スクロールキーを離した時に再度クリックレイヤーを有効にする。 Enable click layer again when the scroll key is released.
            }
         return false;
        
        case KC_TO_CLICKABLE_INC:
            if (record->event.pressed) {
                user_config.to_clickable_movement += 5; // user_config.to_clickable_time += 10;
                eeconfig_update_user(user_config.raw);
            }
            return false;

        case KC_TO_CLICKABLE_DEC:
            if (record->event.pressed) {

                user_config.to_clickable_movement -= 5; // user_config.to_clickable_time -= 10;

                if (user_config.to_clickable_movement < 5)
                {
                    user_config.to_clickable_movement = 5;
                }

                // if (user_config.to_clickable_time < 10) {
                //     user_config.to_clickable_time = 10;
                // }

                eeconfig_update_user(user_config.raw);
            }
            return false;
        
        case KC_SCROLL_DIR_V:
            if (record->event.pressed) {
                user_config.mouse_scroll_v_reverse = !user_config.mouse_scroll_v_reverse;
                eeconfig_update_user(user_config.raw);
            }
            return false;
        
        case KC_SCROLL_DIR_H:
            if (record->event.pressed) {
                user_config.mouse_scroll_h_reverse = !user_config.mouse_scroll_h_reverse;
                eeconfig_update_user(user_config.raw);
            }
            return false;

         default:
            if  (record->event.pressed) {
                
                if (state == CLICKING || state == SCROLLING)
                {
                    enable_click_layer();
                    return false;
                }
                
                for (int i = 0; i < sizeof(ignore_disable_mouse_layer_keys) / sizeof(ignore_disable_mouse_layer_keys[0]); i++)
                {
                    if (keycode == ignore_disable_mouse_layer_keys[i])
                    {
                        enable_click_layer();
                        return true;
                    }
                }

                disable_click_layer();
            }
        
    }
   
    return true;
}


report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    int16_t current_x = mouse_report.x;
    int16_t current_y = mouse_report.y;
    int16_t current_h = 0;
    int16_t current_v = 0;

    if (current_x != 0 || current_y != 0) {
        
        switch (state) {
            case CLICKABLE:
                click_timer = timer_read();
                break;

            case CLICKING:
                after_click_lock_movement -= my_abs(current_x) + my_abs(current_y);

                if (after_click_lock_movement > 0) {
                    current_x = 0;
                    current_y = 0;
                }

                break;

            case SCROLLING:
            {
                int8_t rep_v = 0;
                int8_t rep_h = 0;

                // 垂直スクロールの方の感度を高める。 Increase sensitivity toward vertical scrolling.
                if (my_abs(current_y) * 2 > my_abs(current_x)) {

                    scroll_v_mouse_interval_counter += current_y;
                    while (my_abs(scroll_v_mouse_interval_counter) > scroll_v_threshold) {
                        if (scroll_v_mouse_interval_counter < 0) {
                            scroll_v_mouse_interval_counter += scroll_v_threshold;
                            rep_v += scroll_v_threshold;
                        } else {
                            scroll_v_mouse_interval_counter -= scroll_v_threshold;
                            rep_v -= scroll_v_threshold;
                        }
                        
                    }
                } else {

                    scroll_h_mouse_interval_counter += current_x;

                    while (my_abs(scroll_h_mouse_interval_counter) > scroll_h_threshold) {
                        if (scroll_h_mouse_interval_counter < 0) {
                            scroll_h_mouse_interval_counter += scroll_h_threshold;
                            rep_h += scroll_h_threshold;
                        } else {
                            scroll_h_mouse_interval_counter -= scroll_h_threshold;
                            rep_h -= scroll_h_threshold;
                        }
                    }
                }

                current_h = rep_h / scroll_h_threshold * (user_config.mouse_scroll_h_reverse ? -1 : 1);
                current_v = -rep_v / scroll_v_threshold * (user_config.mouse_scroll_v_reverse ? -1 : 1);
                current_x = 0;
                current_y = 0;
            }
                break;

            case WAITING:
                /*
                if (timer_elapsed(click_timer) > user_config.to_clickable_time) {
                    enable_click_layer();
                }
                */

                mouse_movement += my_abs(current_x) + my_abs(current_y);

                if (mouse_movement >= user_config.to_clickable_movement)
                {
                    mouse_movement = 0;
                    enable_click_layer();
                }
                break;

            default:
                click_timer = timer_read();
                state = WAITING;
                mouse_movement = 0;
        }
    }
    else
    {
        switch (state) {
            case CLICKING:
            case SCROLLING:

                break;

            case CLICKABLE:
                if (timer_elapsed(click_timer) > to_reset_time) {
                    disable_click_layer();
                }
                break;

             case WAITING:
                if (timer_elapsed(click_timer) > 50) {
                    mouse_movement = 0;
                    state = NONE;
                }
                break;

            default:
                mouse_movement = 0;
                state = NONE;
        }
    }

    mouse_report.x = current_x;
    mouse_report.y = current_y;
    mouse_report.h = current_h;
    mouse_report.v = current_v;

    return mouse_report;
}


//reftakashi end


//Declare layers
enum layer_number {
  _QWERTY = 0,
  _NUM,
  _CMD,
  _FNC,
  _MOUSE,
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
  MBTN3,          //Center click
  SCRL
};

//Declare Alias Mod Tap Layer QWERTY Layer
#define MT_FNC_H LT(_FNC, KC_H)       //hold:"Function"   tap:"F"

//Declare Alias Mod Tap QWERTY Layer
#define MT_CTL_A LCTL_T(KC_A)
//#define MT_CTL_MIN RCTL_T(JP_MINS)
#define MT_ALT_S LALT_T(KC_S)
#define MT_ALT_L RALT_T(KC_L)
#define MT_GUI_D LGUI_T(KC_D)
#define MT_GUI_K RGUI_T(KC_K)
#define MT_SFT_V LSFT_T(KC_V)
#define MT_SFT_M RSFT_T(KC_M)
#define MT_CMD_MIN LT(_CMD, JP_MINS)

//Declare Alias Mod Tap NUM Layer
#define MT_SFT_TD LSFT_T(JP_TILD)        //hold:"SHIFT"        tap"~" JP_TILD
#define MT_SFT_YN RSFT_T(JP_YEN)           //hold:"SHIFT"        tap"\" JP_YEN

//Declare Alias Mod Tap CMD Layer
#define MT_SFT_PD LSFT_T(KC_PGDN)        //hold:"SHIFT"        tap"Page Down"

//Declare Alias Short Cut CMD Layer
#define MCPRTSCR G(S(KC_S))           //print screen
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
  OI_LOCK,
  WE_PRTSCN
};

const uint16_t PROGMEM lk_combo[] = {MT_ALT_L, MT_GUI_K ,COMBO_END};
const uint16_t PROGMEM sd_combo[] = {MT_ALT_S, MT_GUI_D, COMBO_END};
const uint16_t PROGMEM kj_combo[] = {MT_GUI_K, KC_J, COMBO_END};
const uint16_t PROGMEM dl_combo[] = {KC_DOWN, KC_LEFT, COMBO_END};
const uint16_t PROGMEM df_combo[] = {MT_GUI_D, KC_F, COMBO_END};
const uint16_t PROGMEM dc_combo[] = {JP_DOT, JP_COMM, COMBO_END};
const uint16_t PROGMEM oi_combo[] = {KC_O, KC_I, COMBO_END};
const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [LK_HENK] = COMBO(lk_combo, JP_HENK),
  [SD_MHEN] = COMBO(sd_combo, JP_MHEN),
  [KJ_TAB] = COMBO(kj_combo, KC_TAB),
  [DL_TAB] = COMBO(dl_combo, KC_TAB),
  [DF_ESC] = COMBO(df_combo, KC_ESC),
  [DOT_COLON_MBTN3] = COMBO(dc_combo, MBTN3),
  [OI_LOCK] = COMBO(oi_combo, MC_LOCK),
  [WE_PRTSCN] = COMBO(we_combo, MCPRTSCR)
};


//Override
const key_override_t undssft_key_override = ko_make_basic(MOD_MASK_SHIFT, MT_CMD_MIN, JP_UNDS);	//_[SHIFT & JP_MINS]
const key_override_t dquosft_key_override = ko_make_basic(MOD_MASK_SHIFT, JP_QUOT, JP_DQUO);    //"[SHIFT & JP_QUOT]
const key_override_t colnsft_key_override = ko_make_basic(MOD_MASK_SHIFT, JP_SCLN, JP_COLN);    //:[SHIFT & JP_SCLN]
const key_override_t tildsft_key_override = ko_make_basic(MOD_MASK_SHIFT, JP_TILD, JP_GRV);     //`[SHIFT & JP_TILD]
const key_override_t yensft_key_override = ko_make_basic(MOD_MASK_SHIFT, JP_YEN, JP_PIPE);      //\[SHIFT & JP_YEN]

const key_override_t *key_overrides[] = {
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

//keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------.
      XXXXXXX,TD(TD_Q_ESC), KC_W,   KC_E,    KC_R,    KC_T,                       KC_Y,   KC_U,     KC_I,    KC_O,    KC_P, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,MT_CTL_A,MT_ALT_S,MT_GUI_D,    KC_F,    KC_G,                   MT_FNC_H,   KC_J,MT_GUI_K,MT_ALT_L,MT_CMD_MIN,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    KC_X,    KC_C,MT_SFT_V,    KC_B,                       KC_N,MT_SFT_M, JP_COMM,  JP_DOT, JP_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, CMD_SPC, XXXXXXX,                    XXXXXXX, NUM_ENT, XXXXXXX
  //                           `--------+--------+--------'                  `--------+--------+--------'
  ),

  [_NUM] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------.
      XXXXXXX, JP_EXLM,   JP_AT, JP_HASH, JP_DLR,  JP_PERC,                    JP_CIRC, JP_AMPR, JP_ASTR, JP_PLUS,  JP_EQL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, JP_TILD, JP_QUOT, JP_LBRC, KC_LSFT, JP_LPRN,                    JP_RPRN, KC_RSFT, JP_RBRC, JP_SCLN,  JP_YEN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, _______,XXXXXXX,                    XXXXXXX, _______, XXXXXXX
  //  	                       `--------+--------+--------'                  `--------+--------+--------'
  ),

  [_CMD] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------
      XXXXXXX,A(KC_F4), C(KC_W),  KILL_L, C(KC_H), C(KC_T),                      MBTN1,   MBTN2,   KC_UP, KC_PGUP,   KC_F2, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, CTL_ALL, C(KC_S),  KC_DEL, C(KC_F),   KC_F3,                    KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT,MO(_FNC), XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_Z), C(KC_X), C(KC_C), SFT_PST, C(KC_Y),                    C(KC_N),MT_SFT_PD, KC_TAB,   INS_L,G(JP_SLSH), XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______, XXXXXXX
  //                           `--------+--------+--------'                  `--------+--------+--------'
  ),

    [_FNC] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_F11,  KC_F12,                    EE_CLR, QK_BOOT,C(KC_HOME),KC_PGUP, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                    XXXXXXX, KC_HOME,C(KC_END), KC_END, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                    XXXXXXX, KC_PGDN,S(KC_TAB),XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______, XXXXXXX
  //                           `--------+--------+--------'                  `--------+--------+--------'
  ),

  [_MOUSE] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      MBTN1,   MBTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______, XXXXXXX
  //                           `--------+--------+--------'                  `--------+--------+--------'
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
    case MT_CMD_MIN:
      return 250;
    case MT_ALT_S:
      return 250;
    case MT_ALT_L:
      return 250;
    case MT_SFT_TD:
      return 250;
    case MT_SFT_YN:
      return 250;
    case MT_SFT_PD:
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

static bool is_scroll_mode;
static bool is_cmd_spc_pressed = false;
static bool is_num_ent_pressed = false;
static uint32_t ctl_all_pressed_time = 0;
static uint32_t sft_pst_pressed_time = 0;
static uint32_t cmd_spc_pressed_time = 0;
static uint32_t num_ent_pressed_time = 0;

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

    default:
      return true;
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
    case _FNC:
      is_scroll_mode = false;
      break;
    default:
      is_scroll_mode = false;
      break;
  }
  return state;
}

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);
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
