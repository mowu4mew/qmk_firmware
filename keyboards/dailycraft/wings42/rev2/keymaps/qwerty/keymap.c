#include QMK_KEYBOARD_H
#include "pointing_device.h"
#include "keymap_japanese.h"
#include "onemoretime.c"

// OneMoreTime interfaces (implementation is compiled separately)
void one_more_time_record(uint16_t keycode, keyrecord_t *record);
bool one_more_time_play(void);
bool is_modifier_key(uint16_t keycode);

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
    CMD_SPC = SAFE_RANGE,
    NUM_ENT,
    SFT_FIND,
    KILL_E,
    KILL_H,
    MBTN1,          //Left click
    MBTN2,          //Right click
    MBTN3,          //Center click
    OMT
};

//Declare Alias Mod Tap
#define SFT_F LSFT_T(KC_F)
#define SFT_J RSFT_T(KC_J)
#define SFT_F3 LSFT_T(KC_F3)

#define CTL_Z LCTL_T(KC_Z)
#define CTL_SLSH RCTL_T(JP_SLSH)
#define CTL_1 LCTL_T(KC_1)
#define CTL_0 RCTL_T(KC_0)
#define CTL_UNDO LCTL_T(KC_NO)
#define CTL_F1 LCTL_T(KC_F1)
#define CTL_F10 RCTL_T(KC_F10)

#define ALT_X LALT_T(KC_X)
#define ALT_DOT RALT_T(JP_DOT)
#define ALT_2 LALT_T(KC_2)
#define ALT_9 RALT_T(KC_9)
#define ALT_UP RALT_T(KC_PGUP)
#define ALT_CUT RALT_T(KC_X)
#define ALT_F2 LALT_T(KC_F2)
#define ALT_F9 RALT_T(KC_F9)

#define GUI_COM RGUI_T(JP_COMM)
#define GUI_8 RGUI_T(KC_8)
#define GUI_F8 RGUI_T(KC_F8)

#define FNC_Q LT(_FNC, KC_Q)
#define FNC_C_G LT(_FNC, KC_G)

//Declare Alias Short Cut
#define MCPRTSCR G(S(KC_S))     //print screen
#define PG_TOP C(KC_HOME)       //go page top
#define PG_BTM C(KC_END)        //go page bottom

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
const uint16_t PROGMEM dt_cm_combo[] = {ALT_DOT, GUI_COM, COMBO_END};
const uint16_t PROGMEM x_c_combo[] = {ALT_X, KC_C, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [I_O_DTRIGHT] = COMBO(i_o_combo, C(G(KC_RIGHT))),
    [W_E_DTLEFT] = COMBO(w_e_combo, C(G(KC_LEFT))),
    [L_K_HENK] = COMBO(l_k_combo, JP_HENK),
    [S_D_MHEN] = COMBO(s_d_combo, JP_MHEN),
    [K_J_TAB] = COMBO(k_j_combo, KC_TAB),
    [DWN_LFT_TAB] = COMBO(dwn_lft_combo, KC_TAB),
    [D_F_ESC] = COMBO(d_f_combo, KC_ESC),
    [DEL_FND_ESC] = COMBO(del_fnd_combo, KC_ESC),
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
        XXXXXXX,   FNC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,   KC_U,     KC_I,    KC_O,    KC_P, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX,    KC_A,    KC_S,    KC_D,   SFT_F,    KC_G,                       KC_H,   SFT_J,    KC_K,    KC_L, JP_MINS, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX,   CTL_Z,   ALT_X,    KC_C,    KC_V,    KC_B,                       KC_N,    KC_M, GUI_COM, ALT_DOT, CTL_SLSH, XXXXXXX,
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
        XXXXXXX,   CTL_1,   ALT_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,   GUI_8,   ALT_9,   CTL_0, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                    XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______, XXXXXXX
    //  	                       `--------+--------+--------'                  `--------+--------+--------'
    ),

    [_CMD] = LAYOUT_split_3x6_3_2(
    //,-----------------------------------------------------|                  |-----------------------------------------------------
        XXXXXXX, FNC_C_G, C(KC_W),  KC_TAB, C(KC_H), C(KC_T),                      MBTN1,   MBTN2,   KC_UP, C(KC_O),   KC_F2, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX, C(KC_A), C(KC_S),  KC_DEL,SFT_FIND,  KC_ESC,                    KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT,MO(_FNC), XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX,CTL_UNDO, ALT_CUT, C(KC_C), C(KC_V), C(KC_Y),                    C(KC_N), KC_PGDN,     OMT,  ALT_UP, KC_RCTL,XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                    XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______, XXXXXXX
    //                           `--------+--------+--------'                  `--------+--------+--------'
    ),
/*C(JP_COMM)*/
    [_FNC] = LAYOUT_split_3x6_3_2(
    //,-----------------------------------------------------|                  |-----------------------------------------------------.
        XXXXXXX, _______,   KC_F8,  KC_F11,   KC_F5, C(KC_K),                    QK_BOOT, _______,  PG_TOP, KC_RSFT, _______, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX,  KC_F11,  KC_F12,  KILL_E,  SFT_F3,     OMT,                     KILL_H, KC_HOME,  PG_BTM,  KC_END, _______, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX,  CTL_F1,  ALT_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,  GUI_F8,  ALT_F9, CTL_F10, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                    XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______, XXXXXXX
    //                           `--------+--------+--------'                  `--------+--------+--------'
    ),

    [_MOUSE] = LAYOUT_split_3x6_3_2(
    //,-----------------------------------------------------|                  |-----------------------------------------------------.
        XXXXXXX,MO(_FNC), _______, _______, _______, _______,                      MBTN1,   MBTN2, _______, _______, _______, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                    XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______,XXXXXXX
    //                           `--------+--------+--------'                  `--------+--------+--------'
    ),
};

// ===== Thumb (CMD/NUM) =====
// 物理押下状態
static bool cmd_down = false;
static bool num_down = false;
// リリース時のタップ可否を判定。
static bool cmd_consumed = false; 
static bool num_consumed = false;
// 押下開始時刻
static uint16_t cmd_time = 0;
static uint16_t num_time = 0;
// 押下開始時にQWERTY or MOUSE
static bool cmd_started_in_typing = false;
static bool num_started_in_typing = false;
// 親指ホールドで有効化しているレイヤ（モメンタリ）
static bool cmd_layer_on = false; // CMD_SPC hold -> _CMD
static bool num_layer_on = false; // NUM_ENT hold -> _NUM

// ===== qshift =====
static bool qshift_added_shift = false;
static bool qshift_on = false;

// ===== SFT_FIND =====
static uint16_t sft_find_pressed_time = 0;

// 「文字入力コンテキスト」判定：QWERTY もしくは AutoMouse で一時的に MOUSE が載っている状態
static inline bool is_typing_context(void) {
    uint8_t top = get_highest_layer(layer_state | default_layer_state);
    return (top == _QWERTY) || (top == _MOUSE);
}

static inline bool should_qshift_now(void) {
    // 「typingから入った親指レイヤ保持中は、2本押しで常にQWERTY+Shift」
    return cmd_down && num_down && cmd_started_in_typing && num_started_in_typing && !qshift_on;
}

static inline void qshift_start(void) {
    if (qshift_on) return;

    qshift_on = true;

    layer_off(_CMD);
    layer_off(_NUM);

    cmd_consumed = true;
    num_consumed = true;

    // もともとShiftが入っていなければ、ここで追加する
    if (!(get_mods() & MOD_BIT(KC_LSFT))) {
        add_mods(MOD_BIT(KC_LSFT));
        qshift_added_shift = true;
        send_keyboard_report();
    } else {
        qshift_added_shift = false;
    }

    cmd_layer_on = false;
    num_layer_on = false;
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
    //qshift_src = QS_NONE;

    layer_off(_CMD);
    layer_off(_NUM);
    cmd_layer_on = false;
    num_layer_on = false;

    if (cmd_down && !num_down) { 
        layer_on(_CMD); 
        cmd_layer_on = true; 
    } else if (num_down && !cmd_down) { 
        layer_on(_NUM); 
        num_layer_on = true; }

    send_keyboard_report();
}

static inline void mouse_button(uint8_t mask, bool pressed) {
    report_mouse_t r = pointing_device_get_report();
    if (pressed) {
        r.buttons |= mask;
    } else {
        r.buttons &= ~mask;
    }
    pointing_device_set_report(r);
}

static void omt_record_key(uint16_t keycode) {
    keyrecord_t fake_record = {0};
    fake_record.event.pressed = true;
    one_more_time_record(keycode, &fake_record);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // ★親指が押されている間に他キーが押されたら、tap（Space/Enter）を出さない
    if (record->event.pressed) {
        if (cmd_down && keycode != CMD_SPC && keycode != NUM_ENT) {
            cmd_consumed = true;
        }
        if (num_down && keycode != CMD_SPC && keycode != NUM_ENT) {
            num_consumed = true;
        }
    }

    // ===== OneMoreTime: 記録（押下のみ）=====
    // 安全のため：custom keycode(SAFE_RANGE〜)は除外
    // さらにレイヤ操作系は除外（必要なら後で広げる）
    /*
    if (record->event.pressed && keycode < SAFE_RANGE){
        one_more_time_record(keycode ,record);
    }
    
    if (record->event.pressed) {
        if (keycode == OMT || keycode == FNC_Q || keycode == CMD_SPC) {
            uprintf("OMT keycode=%u\n", keycode);
            // skip
        } else {
       
            // ここで record() する
            one_more_time_record(keycode, record);
        }
    }
    */
    if (record->event.pressed) {
        if (keycode < SAFE_RANGE && !is_modifier_key(keycode)) {

            uint8_t mods = get_mods();

            if ((mods & MOD_MASK_SHIFT) && keycode >= KC_A && keycode <= KC_Z) {
                omt_record_key(S(keycode));
            } else {
                omt_record_key(keycode);
            }
        }
    }

    // ===== OneMoreTime: 再生トリガ =====
    if (record->event.pressed && keycode == OMT) {
        if (one_more_time_play()) {
            return false; // 再生できたら OMT 自体は送らない
        }
        return false;     // 再生できなくても OMT は送らない（好みで true にしてもOK）
    }
    
    switch (keycode) {
        case CMD_SPC: {
            if (record->event.pressed) {
                cmd_down = true;
                cmd_time = record->event.time;
                cmd_started_in_typing = is_typing_context() || (num_down && num_started_in_typing);
                cmd_consumed = false;

                if (should_qshift_now()) {
                    qshift_start();
                    return false;
                }
     
                // ★ここが肝：押した瞬間に_CMDをON（Hの1打目に間に合わせる）
                if (!qshift_on) {
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
                    omt_record_key(KC_SPC);
                }

                return false;
            }
        }

        case NUM_ENT: {
            if (record->event.pressed) {
                num_down = true;
                num_time = record->event.time;
                num_started_in_typing = is_typing_context() || (cmd_down && cmd_started_in_typing);
                num_consumed = false;

                if (should_qshift_now()) {
                    qshift_start();
                    return false;
                }

                // ★ここが肝：押した瞬間に_NUMをON（1打目取りこぼし防止）
                if (!qshift_on) {
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
                    omt_record_key(KC_SPC);
                }

                return false;
            }
        }

        case SFT_FIND:{
            if (record->event.pressed){
                sft_find_pressed_time = record->event.time;
                register_code(KC_LSFT);
                one_more_time_record(KC_LSFT, record);
            }else{
                unregister_code(KC_LSFT);
                if(timer_elapsed(sft_find_pressed_time) < TAPPING_TERM){
                    SEND_STRING(SS_LCTL(SS_TAP(X_F)));
                }
            }
            return false;
        }

        case ALT_CUT:{
            if (record->tap.count && record->event.pressed){
                tap_code16(C(KC_X));
                omt_record_key(C(KC_X));
                return false;
            }
            return true;
        }

        case CTL_UNDO:{
            if (record->tap.count && record->event.pressed){
                tap_code16(C(KC_Z));
                return false;
            }
            return true;
        }
        
        case FNC_C_G:{
            if (record->tap.count && record->event.pressed){
                tap_code16(C(KC_G));
                return false;
            }
            return true;
        }

        case KILL_E:{
            if (record->event.pressed){
                tap_code16(S(KC_END));
                tap_code(KC_DEL);
            }
            return false;
        }

        case KILL_H:{
            if (record->event.pressed){
            tap_code16(S(KC_HOME));
            tap_code(KC_DEL);
            }
            return false;
        }

        case MBTN1:{
            mouse_button(MOUSE_BTN1, record->event.pressed);
            return false;
        }

        case MBTN2:{
            mouse_button(MOUSE_BTN2, record->event.pressed);
            return false;
        }

        case MBTN3:{
            mouse_button(MOUSE_BTN3, record->event.pressed);
            return false;
        }

        // ===== 保険：CMD親指押下中の取りこぼし対策（ただし qshift / Shift中は除外）=====
        case KC_D:
        case ALT_X:
        case KC_C:
        case KC_V: {
            if (record->event.pressed) {
                // ★qshift中（= QWERTY+Shiftモード）は「文字入力優先」なので変換しない
                // ★また、物理Shift/他Shiftが入っている時も変換しない（X/C/Vを打てるように）
                bool shift_active = (get_mods() & MOD_MASK_SHIFT) != 0;

                if (cmd_down && !qshift_on && !shift_active) {
                    cmd_consumed = true;  // Space誤爆抑制
                    switch (keycode) {
                        case KC_D:
                            tap_code16(C(KC_V));
                            omt_record_key(C(KC_V));
                            break;

                        case ALT_X:
                            tap_code16(C(KC_X));
                            omt_record_key(C(KC_X));
                            break;

                        case KC_C:
                            tap_code16(C(KC_C));
                            omt_record_key(C(KC_C));
                            break;

                        case KC_V:
                            tap_code16(C(KC_V));
                            omt_record_key(C(KC_V));
                            break;
                    }
                }
                return false; // 文字のx/c/vは送らない
            }
        }
        return true;
    

        default:{
            return true;
        }
    }
}


float h_acm = 0.0;
float v_acm = 0.0;

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {

    bool is_scroll_mode = layer_state_is(_NUM);

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
        int8_t base_gain = 3; //通常速度
        int8_t fine_div = 3;  //精密分数

        int16_t mx = x_rev * base_gain;
        int16_t my = y_rev * base_gain;

        if (layer_state_is(_CMD)){
            mx /= fine_div;
            my /= fine_div;
    
        }
        
        if (mx > 127) mx = 127;
        if (mx < -127) mx = -127;
        if (my > 127 ) my = 127;
        if (my < -127) my = -127;

        mouse_report.x = (int8_t)mx;
        mouse_report.y = (int8_t)my;
    }

    return pointing_device_task_user(mouse_report);
}

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);
    set_auto_mouse_enable(true);
}

bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record){
  switch(keycode){
    case MBTN1:
    case MBTN2:
    case MBTN3:
      return true;
    default:
      return false;
  }
  return is_mouse_record_user(keycode, record);
}

bool encoder_update_user(uint8_t index, bool clockwise) {

    uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    if (index == 0) { // First encoder 
        // _CMDの時：水平スクロール（ホイール左右）
        if (layer == _CMD){
            if (clockwise) {
                tap_code(MS_WHLR);//右へ
            } else {
                tap_code(MS_WHLL);//左へ
            }
            return false;
        }

        if (clockwise) {
            tap_code(MS_WHLD);
        } else {
            tap_code(MS_WHLU);
        }
    } else if (index == 1) { // Second encoder
        // _CMDの時：水平スクロール（ホイール左右）
        if (layer == _CMD){
            if (clockwise) {
                tap_code(MS_WHLR);//右へ
            } else {
                tap_code(MS_WHLL);//左へ
            }
            return false;
        }

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
