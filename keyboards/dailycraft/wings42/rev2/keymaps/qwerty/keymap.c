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
#define PG_TOP C(KC_HOME)     //go page top
#define PG_BTM C(KC_END)      //go page bottom
#define S_ENT S(KC_ENT)       //shift + enter

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
      XXXXXXX,    QUIT, C(KC_W),  KC_TAB, C(KC_H), C(KC_T),                      MBTN1,   MBTN2,   KC_UP, KC_PGUP,   KC_F2, XXXXXXX,
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
      XXXXXXX, _______, _______,   KC_F9,   KC_F8, _______,                    _______,    SCRL, _______, _______, _______, XXXXXXX,
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
static uint16_t ctl_all_pressed_time = 0;
static uint16_t sft_find_pressed_time = 0;

enum key_state ctl_all_state = RELEASED;

// ===== Thumb LT + Delayed Cross-QWERTY+Shift (simple, 0-base) =====

#define THUMB_SHIFT_TERM 100   // cross-hold / 両ホールド：QWERTY+Shiftになる遅延

static bool cmd_consumed = false; // その押下サイクルで tap を出さない
static bool num_consumed = false;

// 物理押下状態
static bool cmd_down = false;
static bool num_down = false;

// 押下開始時刻
static uint16_t cmd_time = 0;
static uint16_t num_time = 0;

// 押下開始時にQWERTYがトップだったか（LT判定に使う）
static bool cmd_started_in_qwerty = false;
static bool num_started_in_qwerty = false;

// 親指ホールドで有効化しているレイヤ（モメンタリ）
static bool cmd_layer_on = false; // CMD_SPC hold -> _CMD
static bool num_layer_on = false; // NUM_ENT hold -> _NUM

// QWERTY+Shiftモードの発生源
typedef enum {
    QS_NONE = 0,
    QS_FROM_CMD,        // _CMD中に NUM_ENT hold
    QS_FROM_NUM,        // _NUM中に CMD_SPC hold
    QS_BOTH_IN_QWERTY   // QWERTY中に 両方hold
} qshift_src_t;

static bool qshift_on = false;
static qshift_src_t qshift_src = QS_NONE;

// 現在トップがQWERTYか（default含む）
static inline bool top_is_qwerty(void) {
    return get_highest_layer(layer_state | default_layer_state) == _QWERTY;
}
static bool qshift_added_shift = false;

static inline void qshift_start(qshift_src_t src) {
    if (qshift_on) return;

    qshift_on = true;
    qshift_src = src;

    layer_off(_CMD);
    layer_off(_NUM);

    // もともとShiftが入っていなければ、ここで追加する
    if (!(get_mods() & MOD_BIT(KC_LSFT))) {
        add_mods(MOD_BIT(KC_LSFT));
        qshift_added_shift = true;
        send_keyboard_report();
    } else {
        qshift_added_shift = false;
    }

    // consumed処理は今のままでOK
    switch (src) {
        case QS_BOTH_IN_QWERTY: cmd_consumed = true; num_consumed = true; break;
        case QS_FROM_CMD:       num_consumed = true; break;
        case QS_FROM_NUM:       cmd_consumed = true; break;
        default: break;
    }
}

static inline void qshift_stop(void) {
    if (!qshift_on) return;

    // qshiftが追加した分だけ戻す（他のShiftを巻き込まない）
    if (qshift_added_shift) {
        del_mods(MOD_BIT(KC_LSFT));
        send_keyboard_report();
        qshift_added_shift = false;
    }

    qshift_on  = false;
    qshift_src = QS_NONE;

    layer_off(_CMD);
    layer_off(_NUM);
    cmd_layer_on = false;
    num_layer_on = false;

    if (cmd_down && !num_down) { layer_on(_CMD); cmd_layer_on = true; }
    else if (num_down && !cmd_down) { layer_on(_NUM); num_layer_on = true; }

    send_keyboard_report();
}

// 毎scanで更新：LT遅延レイヤON、cross/両ホールド遅延Shift
static void thumb_update(void) {

    // すでにQWERTY+Shiftモードなら、ここでは何もしない
    if (qshift_on) return;

    bool both_down = cmd_down && num_down;

    // --- ① QWERTY中に両方hold -> QWERTY+Shift ---
    // 両方とも「押し始めがQWERTY」だったときだけ発動
    if (both_down && cmd_started_in_qwerty && num_started_in_qwerty) {

        // ★2本目に押した時刻（後から押された方）からの経過で判定
        uint16_t second_press_time = (cmd_time > num_time) ? cmd_time : num_time;

        if (timer_elapsed(second_press_time) >= THUMB_SHIFT_TERM) {
            qshift_start(QS_BOTH_IN_QWERTY);
        }
        return;
    }
    // --- ② cross-hold：_CMD中にNUM_ENT hold -> QWERTY+Shift（遅延） ---
    if (cmd_layer_on && cmd_down && num_down &&
        timer_elapsed(num_time) >= THUMB_SHIFT_TERM) {
        qshift_start(QS_FROM_CMD);
        return;
    }

    // --- ② cross-hold：_NUM中にCMD_SPC hold -> QWERTY+Shift（遅延） ---
    if (num_layer_on && num_down && cmd_down &&
        timer_elapsed(cmd_time) >= THUMB_SHIFT_TERM) {
        qshift_start(QS_FROM_NUM);
        return;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    report_mouse_t currentReport = {};

    // ★親指が押されている間に他キーが押されたら、tap（Space/Enter）を出さない
    if (record->event.pressed) {
        if (cmd_down && keycode != CMD_SPC && keycode != NUM_ENT) {
            cmd_consumed = true;
        }
        if (num_down && keycode != CMD_SPC && keycode != NUM_ENT) {
            num_consumed = true;
        }
    }

    switch (keycode) {
        case CMD_SPC: {
            if (record->event.pressed) {
                cmd_down = true;
                cmd_time = record->event.time;
                cmd_started_in_qwerty = top_is_qwerty();
                cmd_consumed = false;

                // ★ここが肝：押した瞬間に_CMDをON（Hの1打目に間に合わせる）
                if (cmd_started_in_qwerty && !qshift_on) {
                    layer_on(_CMD);
                    cmd_layer_on = true;
                }

                return false;
            } else {
                cmd_down = false;

                // QWERTY+Shift中なら復帰はqshift_stopへ
                if (qshift_on) {
                    qshift_stop();
                }

                // 自分のホールドレイヤが残っていたらOFF
                if (cmd_layer_on) {
                    layer_off(_CMD);
                    cmd_layer_on = false;
                    // “ホールド扱い”だったなら tap(SPC) を抑制
                    // ※ただし tap 判定でスペースを出す場合は cmd_consumed を使う
                }

                // ★tap：Space（消費されていない & タップ時間内のみ）
                if (!cmd_consumed && timer_elapsed(cmd_time) < TAPPING_TERM) {
                    tap_code(KC_SPC);
                }

                return false;
            }
        }

        case NUM_ENT: {
            if (record->event.pressed) {
                num_down = true;
                num_time = record->event.time;
                num_started_in_qwerty = top_is_qwerty();
                num_consumed = false;

                // ★ここが肝：押した瞬間に_NUMをON（1打目取りこぼし防止）
                if (num_started_in_qwerty && !qshift_on) {
                    layer_on(_NUM);
                    num_layer_on = true;
                    // 早めに反映したい場合は次も有効（お好み）
                    // send_keyboard_report();
                }

                return false;
            } else {
                num_down = false;

                // QWERTY+Shift中なら復帰はqshift_stopへ
                if (qshift_on) {
                    qshift_stop();
                }

                // 自分のホールドレイヤが残っていたらOFF
                if (num_layer_on) {
                    layer_off(_NUM);
                    num_layer_on = false;
                    // ホールド扱いならtap(ENT)抑制は num_consumed で制御
                }

                // ★tap：Enter（消費されていない & タップ時間内のみ）
                if (!num_consumed && timer_elapsed(num_time) < TAPPING_TERM) {
                    tap_code(KC_ENT);
                }

                return false;
            }
        }

        case CTL_ALL:{
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
        }

        case SFT_FIND:{
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
        }

        case KILL_E:{
            if(record->event.pressed){
                tap_code16(S(KC_END));
                tap_code(KC_DEL);
            }
            return false;
        }

        case KILL_H:{
            if(record->event.pressed){
            tap_code16(S(KC_HOME));
            tap_code(KC_DEL);
            }
            return false;
        }

        case INS_L:{
            if(record->event.pressed){
            SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_ENT) SS_TAP(X_UP));
            }
            return false;
        }
            
        case MBTN1:{
            currentReport = pointing_device_get_report();
            if (record->event.pressed) {
            currentReport.buttons |= MOUSE_BTN1;
            }else {
            currentReport.buttons &= ~MOUSE_BTN1;
            }
            pointing_device_set_report(currentReport);
            return false;
        }

        case MBTN2:{
            currentReport = pointing_device_get_report();
            if (record->event.pressed) {
            currentReport.buttons |= MOUSE_BTN2;
            }else {
            currentReport.buttons &= ~MOUSE_BTN2;
            }
            pointing_device_set_report(currentReport);
            return false;
        }

        case MBTN3:{
            currentReport = pointing_device_get_report();
            if (record->event.pressed) {
            currentReport.buttons |= MOUSE_BTN3;
            }else {
            currentReport.buttons &= ~MOUSE_BTN3;
            }
            pointing_device_set_report(currentReport);
            return false;
        }

        case SCRL:{
            if (record->event.pressed){
            is_scroll_mode = true;
            }else{
            is_scroll_mode = false;
            }
            return false;
        }
        // ===== 保険：CMD親指押下中の取りこぼし対策（ただし qshift / Shift中は除外）=====
        case KC_D:
        case KC_X:
        case KC_C:
        case SFT_V: {
            if (record->event.pressed) {
                // ★qshift中（= QWERTY+Shiftモード）は「文字入力優先」なので変換しない
                // ★また、物理Shift/他Shiftが入っている時も変換しない（X/C/Vを打てるように）
                bool shift_active = (get_mods() & MOD_MASK_SHIFT) != 0;

                if (cmd_down && !qshift_on && !shift_active) {
                    cmd_consumed = true;  // Space誤爆抑制
                    switch (keycode) {
                        case KC_D: tap_code16(C(KC_V)); break;
                        case KC_X: tap_code16(C(KC_X)); break;
                        case KC_C: tap_code16(C(KC_C)); break;
                        case SFT_V: tap_code16(C(KC_V)); break;
                    }
                    return false; // 文字のx/c/vは送らない
                }
            }
            return true;
        }

        default:{
            return true;
        }
    }
}

  void matrix_scan_user(void) {
    // 既存のCTL_ALLホールド処理
    if (ctl_all_state == PRESSED && timer_elapsed(ctl_all_pressed_time) > TAPPING_TERM) {
        register_code(KC_LCTL);
        ctl_all_state = HOLDEN;
    }
    thumb_update();
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

//layer_state_t layer_state_set_user(layer_state_t state){
    //switch(get_highest_layer(state)){
    //  case _NUM:
    //    is_scroll_mode = true;
    //    break;
    //  default:
    //    is_scroll_mode = false;
    //    break;
    //}
    //return state;
//}
layer_state_t layer_state_set_user(layer_state_t state) {
    // 最上位ではなく「NUMレイヤが有効かどうか」で判定する
    // Auto Mouse Layer が上に載っても、NUMがONの限りスクロールを維持できる
    is_scroll_mode = layer_state_cmp(state, _NUM);
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