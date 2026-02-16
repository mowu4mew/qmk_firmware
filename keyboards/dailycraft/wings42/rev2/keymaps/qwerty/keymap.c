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
  CMD_SPC = SAFE_RANGE,
  NUM_ENT,
  CTL_ALL, 
  SFT_FIND,
  KILL_E,
  KILL_H,
  INS_L,
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

//Declare Alias Mod Tap
#define CTL_Z LCTL_T(KC_Z)
#define SFT_V LSFT_T(KC_V)
#define SFT_F LSFT_T(KC_F)
#define ALT_SLSH LALT_T(JP_SLSH)
#define GUI_DOT LGUI_T(JP_DOT)
#define MOUSE_Q LT(_MOUSE, KC_Q)
#define FNC_MINS LT(_FNC, JP_MINS)

//Declare Alias Short Cut
#define MCPRTSCR G(S(KC_S))   //print screen
#define QUIT A(KC_F4)         //apli quit
//#define RECVT G(ALT_SLSH)      //re convert ime
#define PG_TOP C(KC_HOME)     //go page top
#define PG_BTM C(KC_END)      //go page bottom
#define S_ENT S(KC_ENT)       //shift + enter

//Declare Alias Tapping Term
#define THUMB_LAYER_TERM 70  // まずは 120〜180 あたりで調整

//Declare COMBO
enum combos{
  I_O_DTRIGHT,
  W_E_DTLEFT,
  L_K_HENK,
  S_D_MHEN,
  K_J_TAB,
  DWN_LFT_TAB,
  D_F_ESC,
  DEL_FND_ESC,
  DT_CM_MBTN3,
  X_C_PRTSCN
};

const uint16_t PROGMEM i_o_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM w_e_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM l_k_combo[] = {KC_L, KC_K ,COMBO_END};
const uint16_t PROGMEM s_d_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM k_j_combo[] = {KC_K, KC_J, COMBO_END};
const uint16_t PROGMEM dwn_lft_combo[] = {KC_DOWN, KC_LEFT, COMBO_END};
const uint16_t PROGMEM d_f_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM del_fnd_combo[] = {KC_DEL, SFT_FIND, COMBO_END};
const uint16_t PROGMEM dt_cm_combo[] = {GUI_DOT, JP_COMM, COMBO_END};
const uint16_t PROGMEM x_c_combo[] = {KC_X, KC_C, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [I_O_DTRIGHT] = COMBO(i_o_combo, C(G(KC_RIGHT))),
  [W_E_DTLEFT] = COMBO(w_e_combo, C(G(KC_LEFT))),
  [L_K_HENK] = COMBO(l_k_combo, JP_HENK),
  [S_D_MHEN] = COMBO(s_d_combo, JP_MHEN),
  [K_J_TAB] = COMBO(k_j_combo, KC_TAB),
  [DWN_LFT_TAB] = COMBO(dwn_lft_combo, KC_TAB),
  [DEL_FND_ESC] = COMBO(del_fnd_combo, KC_ESC),
  [D_F_ESC] = COMBO(d_f_combo, KC_ESC),
  [DT_CM_MBTN3] = COMBO(dt_cm_combo, MBTN3),
  [X_C_PRTSCN] = COMBO(x_c_combo, MCPRTSCR)
};


//Override
const key_override_t undssft_key_override = ko_make_basic(MOD_MASK_SHIFT, JP_MINS, JP_UNDS);	//_[SHIFT & JP_MINS]
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


//keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------.
      XXXXXXX, MOUSE_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,   KC_U,     KC_I,    KC_O,    KC_P, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_A,    KC_S,    KC_D,   SFT_F,    KC_G,                       KC_H,    KC_J,    KC_K,    KC_L, JP_MINS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   CTL_Z,    KC_X,    KC_C,   SFT_V,    KC_B,                       KC_N,    KC_M, JP_COMM,  GUI_DOT,ALT_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, CMD_SPC, XXXXXXX,                    XXXXXXX, NUM_ENT, XXXXXXX
  //                           `--------+--------+--------'                  `--------+--------+--------'
  ),

  [_NUM] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------.
      XXXXXXX, JP_EXLM,   JP_AT, JP_HASH,  JP_DLR, JP_PERC,                    JP_CIRC, JP_AMPR, JP_ASTR, JP_PLUS,  JP_EQL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, JP_TILD, JP_QUOT, JP_LBRC, KC_LSFT, JP_LPRN,                    JP_RPRN, KC_RSFT, JP_RBRC, JP_SCLN,  JP_YEN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______, XXXXXXX
  //  	                       `--------+--------+--------'                  `--------+--------+--------'
  ),

  [_CMD] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------
      XXXXXXX,    QUIT, C(KC_W),  KC_TAB, C(KC_H), C(KC_K),                      MBTN1,   MBTN2,   KC_UP, KC_PGUP,   KC_F2, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, CTL_ALL, C(KC_S),  KC_DEL,SFT_FIND,  KC_ESC,                    KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT,MO(_FNC), XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_Y),                    C(KC_N), KC_PGDN,   INS_L, C(KC_K), KC_RALT,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______, XXXXXXX
  //                           `--------+--------+--------'                  `--------+--------+--------'
  ),

  [_MOUSE] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------.
      XXXXXXX, _______,  KC_F10,  KC_F11,   KC_F5, _______,                      MBTN1,   MBTN2, _______, _______, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, _______, _______,   KC_F9,   KC_F8, _______,                    _______, _______, _______, _______, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LCTL, _______, _______, KC_LSFT, _______,                    _______, _______, _______, KC_RGUI, KC_RALT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, _______, XXXXXXX,                    XXXXXXX,S(KC_ENT),XXXXXXX
  //                           `--------+--------+--------'                  `--------+--------+--------'
  ),

  [_FNC] = LAYOUT_split_3x6_3_2(
  //,-----------------------------------------------------|                  |-----------------------------------------------------.
      XXXXXXX,  KC_F11, KC_F12,S(KC_TAB),  KC_F13,  KC_F14,                     KC_F15, XXXXXXX,  PG_TOP, XXXXXXX, QK_BOOT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX, _______, _______,  KILL_E,   KC_F3, XXXXXXX,                     KILL_H, KC_HOME,  PG_BTM,  KC_END, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______, XXXXXXX
  //                           `--------+--------+--------'                  `--------+--------+--------'
  ),

};

static bool is_scroll_mode = false;
//static bool is_cmd_spc_pressed = false;
//static bool is_num_ent_pressed = false;
static uint16_t ctl_all_pressed_time = 0;
//static uint16_t alt_save_pressed_time = 0;
static uint16_t sft_find_pressed_time = 0;
//static uint16_t cmd_spc_pressed_time = 0;
//static uint16_t num_ent_pressed_time = 0;

//-----copilot

// --- Thumb state for CMD_SPC / NUM_ENT ---

static bool cmd_pressed = false;
static bool num_pressed = false;

static bool cmd_shift_token = false;  // CMD_SPC が Shift を保持中か
static bool num_shift_token = false;  // NUM_ENT が Shift を保持中か

static bool cmd_layer_active = false; // CMD_SPC により _CMD を ON 中か
static bool num_layer_active = false; // NUM_ENT により _NUM を ON 中か

static bool cmd_chorded = false;      // 押下期間中に chord(同時押し)に参加したか
static bool num_chorded = false;

static uint16_t cmd_time = 0;
static uint16_t num_time = 0;

// Shift 参照カウント（同時押しでも Shift が落ちないように）
static uint8_t shift_ref = 0;

static inline void shift_on_ref(void) {
    if (shift_ref == 0) {
        add_mods(MOD_BIT(KC_LSFT));
    }
    shift_ref++;
}

static inline void shift_off_ref(void) {
    if (shift_ref > 0) {
        shift_ref--;
        if (shift_ref == 0) {
            del_mods(MOD_BIT(KC_LSFT));
        }
    }
}

// 「押した瞬間の最前面が QWERTY か」を default_layer_state も込みで判定
static inline bool top_is_qwerty_now(void) {
    return get_highest_layer(layer_state | default_layer_state) == _QWERTY;
}

// 親指由来の Shift を全部落とす（昇格タイミングの 1文字目事故を潰す）
static inline void drop_all_thumb_shift(void) {
    if (cmd_shift_token) { cmd_shift_token = false; shift_off_ref(); }
    if (num_shift_token) { num_shift_token = false; shift_off_ref(); }

    // 念のため（環境により Shift が残るケース対策）
#ifndef NO_ACTION_ONESHOT
    clear_oneshot_mods();
#endif
    clear_weak_mods();
    send_keyboard_report();
}

// chord 成立時：QWERTY文字入力(Shift)へ強制的に寄せる
static inline void enter_chord_shift_mode(void) {
    // chord 参加フラグ（タップ誤送信防止）
    cmd_chorded = true;
    num_chorded = true;

    // _CMD/_NUM を落として QWERTY に寄せる（Aの要件）
    if (cmd_layer_active) { layer_off(_CMD); cmd_layer_active = false; }
    if (num_layer_active) { layer_off(_NUM); num_layer_active = false; }
    layer_off(_CMD);
    layer_off(_NUM);

    // Shift を両方のキーが保持する扱いにする（参照カウントが崩れないよう token 管理）
    if (!cmd_shift_token) { cmd_shift_token = true; shift_on_ref(); }
    if (!num_shift_token) { num_shift_token = true; shift_on_ref(); }

    send_keyboard_report();
}

// 長押し昇格（同時押し中は昇格しない）
static void promote_thumb_layers_now(void) {
    bool chord = cmd_pressed && num_pressed;

    // 両方押し中は Shift 維持（レイヤ昇格しない）
    if (chord) return;

    // CMD_SPC：単体長押し → _CMD
    if (cmd_pressed && !cmd_layer_active && timer_elapsed(cmd_time) >= THUMB_LAYER_TERM) {
        drop_all_thumb_shift();     // ★ Shift は落ちてOK（要件通り）
        layer_on(_CMD);
        cmd_layer_active = true;
    }

    // NUM_ENT：単体長押し → _NUM
    if (num_pressed && !num_layer_active && timer_elapsed(num_time) >= THUMB_LAYER_TERM) {
        drop_all_thumb_shift();     // ★ Shift は落ちてOK（要件通り）
        layer_on(_NUM);
        num_layer_active = true;
    }
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case CMD_SPC:
            case NUM_ENT:
                // 自分自身の押下はここで昇格させない
                break;
            default:
                // ★ 次キーが押された瞬間に、先に昇格を確定
                promote_thumb_layers_now();
                break;
        }
    }
    return true;
}


//-------copilot

enum key_state ctl_all_state = RELEASED;
//enum key_state alt_save_state = RELEASED;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    report_mouse_t currentReport = {};

  switch (keycode) {
    case CMD_SPC:
        if (record->event.pressed) {
            cmd_pressed = true;
            cmd_time = record->event.time;
            cmd_layer_active = false;
            cmd_chorded = false;

            // すでに NUM が押されているなら chord 開始：どのレイヤでも QWERTY+Shift へ
            if (num_pressed) {
                enter_chord_shift_mode();
                return false;
            }

            // chord でない単体開始：QWERTY中なら押下直後は Shift（即大文字）
            if (top_is_qwerty_now()) {
                cmd_shift_token = true;
                shift_on_ref();
                send_keyboard_report();
            } else {
                cmd_shift_token = false;
            }

        } else {
            cmd_pressed = false;

            // chord 状態が崩れた瞬間、残り側を即昇格させたい（要件：片方離したら残りレイヤへ）
            // ここで promote を呼ぶと、残り側が TAPPING_TERM を超えていれば即 _NUM/_CMD へ移行する
            // （このキーを離した直後、まだ num_pressed が true の場合）
            if (num_pressed) {
                // 自分の Shift は落としてOK（要件通り）
                if (cmd_shift_token) { cmd_shift_token = false; shift_off_ref(); }
                send_keyboard_report();
                promote_thumb_layers_now();
            }

            // _CMD を ON していたなら OFF（モメンタリ）
            if (cmd_layer_active) {
                layer_off(_CMD);
                cmd_layer_active = false;
            }

            // Shift を保持していたなら解除
            if (cmd_shift_token) {
                cmd_shift_token = false;
                shift_off_ref();
                send_keyboard_report();
            }

            // タップ判定：chord 参加していない & 長押し昇格していない & TAPPING_TERM未満
            if (!cmd_chorded && timer_elapsed(cmd_time) < TAPPING_TERM && !cmd_layer_active) {
                tap_code(KC_SPC);
            }
        }
        return false;

    case NUM_ENT:
        if (record->event.pressed) {
            num_pressed = true;
            num_time = record->event.time;
            num_layer_active = false;
            num_chorded = false;

            // すでに CMD が押されているなら chord 開始：どのレイヤでも QWERTY+Shift へ
            if (cmd_pressed) {
                enter_chord_shift_mode();
                return false;
            }

            // chord でない単体開始：QWERTY中なら押下直後は Shift（即大文字）
            if (top_is_qwerty_now()) {
                num_shift_token = true;
                shift_on_ref();
                send_keyboard_report();
            } else {
                num_shift_token = false;
            }

        } else {
            num_pressed = false;

            // chord 崩壊：残り側を即昇格
            if (cmd_pressed) {
                if (num_shift_token) { num_shift_token = false; shift_off_ref(); }
                send_keyboard_report();
                promote_thumb_layers_now();
            }

            // _NUM を ON していたなら OFF
            if (num_layer_active) {
                layer_off(_NUM);
                num_layer_active = false;
            }

            // Shift を保持していたなら解除
            if (num_shift_token) {
                num_shift_token = false;
                shift_off_ref();
                send_keyboard_report();
            }

            // タップ判定：chord 不参加 & 昇格なし & TAPPING_TERM未満
            if (!num_chorded && timer_elapsed(num_time) < TAPPING_TERM && !num_layer_active) {
                tap_code(KC_ENT);
            }
        }
        return false;
        
    case CTL_ALL:
      if(record->event.pressed){
        ctl_all_pressed_time = record->event.time;
        ctl_all_state = PRESSED;
      }else{
        switch(ctl_all_state){
          case PRESSED:
            SEND_STRING(SS_LCTL(SS_TAP(X_A)));
            break;
          case HOLDEN:
            unregister_code(KC_LCTL);
            break;
          case RELEASED:
            break;
        }
        ctl_all_state = RELEASED;
      }
      return false;
      
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

    case KILL_E:
      if(record->event.pressed){
        tap_code16(S(KC_END));
        tap_code(KC_DEL);
      }
      return false;

    case KILL_H:
      if(record->event.pressed){
        tap_code16(S(KC_HOME));
        tap_code(KC_DEL);
      }
      return false;
      
    case INS_L:
      if(record->event.pressed){
        SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_ENT) SS_TAP(X_UP));
      }
      return false;
      
    case MBTN1:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN1;
      }else {
        currentReport.buttons &= ~MOUSE_BTN1;
      }
      pointing_device_set_report(currentReport);
      return false;
      
    case MBTN2:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN2;
      }else {
        currentReport.buttons &= ~MOUSE_BTN2;
      }
      pointing_device_set_report(currentReport);
      return false;
      
    case MBTN3:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN3;
      }else {
        currentReport.buttons &= ~MOUSE_BTN3;
      }
      pointing_device_set_report(currentReport);
      return false;
      
    case SCRL:
      if (record->event.pressed){
        is_scroll_mode = true;
      }else{
        is_scroll_mode = false;
      }
      return false;
            
    default:
      
      return true;
  }
}

  void matrix_scan_user(void) {
    // 既存のCTL_ALLホールド処理
    if (ctl_all_state == PRESSED && timer_elapsed(ctl_all_pressed_time) > TAPPING_TERM) {
        register_code(KC_LCTL);
        ctl_all_state = HOLDEN;
    }
    promote_thumb_layers_now();
}


float h_acm = 0.0;
float v_acm = 0.0;

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {

    double rad = 45 * (M_PI / 180) * -1;
    int8_t x_rev =  + mouse_report.x * cos(rad) - mouse_report.y * sin(rad);
    int8_t y_rev =  + mouse_report.x * sin(rad) + mouse_report.y * cos(rad);

    if (is_scroll_mode) {
        if (abs(x_rev) > abs(y_rev)) {
            y_rev = 0;
        } else {
            x_rev = 0;
        }

        h_acm += (float)x_rev / 6.0;
        v_acm += (float)y_rev / 6.0;

        int8_t h_rev = h_acm;
        int8_t v_rev = v_acm;

        if (h_rev != 0) {
            if (mouse_report.h + h_rev > 127) {
                //h_rev = 127 - mouse_report.h;
                h_rev = -127 -mouse_report.h;
            } else if (mouse_report.h + h_rev < -127) {
                //h_rev = -127 - mouse_report.h;
                h_rev = 127 - mouse_report.h;
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
      is_scroll_mode = false;
      break;
  }
  return state;
}


void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);
    set_auto_mouse_enable(true);
}

bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record){
  switch(keycode){
    case MBTN1:
      return true;
    case MBTN2:
      return true;
    case MBTN3:
      return true;
    case SCRL:
      return true;
    default:
      return false;
  }
  return is_mouse_record_user(keycode, record);
}

/*
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index != 0) {
        return true;
    }

    layer_state_t layer = get_highest_layer(layer_state | default_layer_state);
    uint16_t keycode;
    if (clockwise) {
        switch (layer) {
            case 1:
                keycode = MS_WHLD;
                break;
            case 2:
                keycode = MS_WHLL;
                break;
            default:
                return true; // encoder_update_kbに任せる
        }
    } else { // counter clockwise
        switch (layer) {
            case 1:
                keycode = MS_WHLU;
                break;
            case 2:
                keycode = MS_WHLR;
                break;
            default:
                return true; // encoder_update_kbに任せる
        }
    }
    tap_code16_delay(keycode, 10);
    return false; // encoder_update_kbの処理をスキップ
}
*/
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // First encoder 
        if (clockwise) {
            tap_code(MS_WHLD);
        } else {
            tap_code(MS_WHLU);
        }
    } else if (index == 1) { // Second encoder
        if (clockwise) {
            tap_code(MS_WHLD);
        } else {
            tap_code(MS_WHLU);
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