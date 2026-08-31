#include QMK_KEYBOARD_H
#include "pointing_device.h"
#include "keymap_japanese.h"
#include "onemoretime.h"

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
    KILL_E,
    KILL_H,
    OMT
};

//Declare Alias Mod Tap
#define SFT_F LSFT_T(KC_F)
#define SFT_J RSFT_T(KC_J)
#define SFT_F3 LSFT_T(KC_F3)
#define SFT_FIND RSFT_T(KC_NO)

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

#define FNC_ALL LT(_FNC, KC_NO)

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
    DT_CM_BTN3,
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
    [DT_CM_BTN3] = COMBO(dt_cm_combo, MS_BTN3),
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
        XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,   KC_U,     KC_I,    KC_O,    KC_P, XXXXXXX,
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
        XXXXXXX, C(KC_W), C(KC_G),  KC_TAB, C(KC_H), C(KC_T),                    MS_BTN1, MS_BTN2,   KC_UP, C(KC_O),   KC_F2, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX, FNC_ALL, C(KC_S),  KC_DEL,SFT_FIND,  KC_ESC,                    KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT,MO(_FNC), XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX,CTL_UNDO, ALT_CUT, C(KC_C), C(KC_V), C(KC_Y),                    C(KC_N), KC_PGDN,     OMT,  ALT_UP, KC_RCTL,XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                    XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______, XXXXXXX
    //                           `--------+--------+--------'                  `--------+--------+--------'
    ),

    [_FNC] = LAYOUT_split_3x6_3_2(
    //,-----------------------------------------------------|                  |-----------------------------------------------------.
        XXXXXXX, _______,  KC_F12,S(KC_TAB),  KC_F3, C(KC_K),                    QK_BOOT, _______,  PG_TOP, KC_RSFT, _______, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX, _______,  KC_F11,  KILL_E,  SFT_F3,  KC_ESC,                     KILL_H, KC_HOME,  PG_BTM,  KC_END, _______, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX,  CTL_F1,  ALT_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,  GUI_F8,  ALT_F9, CTL_F10, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                    XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______, XXXXXXX
    //                           `--------+--------+--------'                  `--------+--------+--------'
    ),

    [_MOUSE] = LAYOUT_split_3x6_3_2(
    //,-----------------------------------------------------|                  |-----------------------------------------------------.
        XXXXXXX, _______, _______, _______, _______, _______,                    MS_BTN1, MS_BTN2, _______, _______, _______, XXXXXXX,
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
typedef struct {
    uint8_t  layer;
    uint16_t tap_keycode;
    uint16_t pressed_at;
    bool     down;
    bool     interrupted;
} thumb_key_state_t;

static thumb_key_state_t cmd_thumb = {
    .layer       = _CMD,
    .tap_keycode = KC_SPC,
};

static thumb_key_state_t num_thumb = {
    .layer       = _NUM,
    .tap_keycode = KC_ENT,
};

static bool thumb_shift_on    = false;
static bool thumb_shift_added = false;

// 両親指のレイヤを解除し、Shift同時押し状態を開始する。
static void start_thumb_shift(void) {
    layer_off(_CMD);
    layer_off(_NUM);
    cmd_thumb.interrupted = true;
    num_thumb.interrupted = true;
    thumb_shift_on        = true;

    if (!(get_mods() & MOD_MASK_SHIFT)) {
        add_mods(MOD_BIT(KC_LSFT));
        thumb_shift_added = true;
        send_keyboard_report();
    }
}

// Shift同時押し状態を終了し、残っている親指のレイヤを有効にする。
static void stop_thumb_shift(void) {
    if (thumb_shift_added) {
        del_mods(MOD_BIT(KC_LSFT));
        send_keyboard_report();
        thumb_shift_added = false;
    }

    thumb_shift_on = false;

    if (cmd_thumb.down) {
        layer_on(cmd_thumb.layer);
    } else if (num_thumb.down) {
        layer_on(num_thumb.layer);
    }
}

// OneMoreTimeへ押下イベントとしてキーコードを記録する。
static void omt_record_key(uint16_t keycode) {
    keyrecord_t fake_record = {0};
    fake_record.event.pressed = true;
    one_more_time_record(keycode, &fake_record);
}

// キーをタップし、同じキーコードをOneMoreTimeへ記録する。
static void tap_and_record(uint16_t keycode) {
    tap_code16(keycode);
    omt_record_key(keycode);
}

// 現在位置から行頭または行末までを選択して削除する。
static void delete_to_line_edge(uint16_t edge_keycode) {
    tap_and_record(S(edge_keycode));
    tap_and_record(KC_DEL);
}

// 親指キーの押下・解放、レイヤ切替、タップ送信を共通処理する。
static void process_thumb_key(thumb_key_state_t *thumb, thumb_key_state_t *other, keyrecord_t *record) {
    if (record->event.pressed) {
        thumb->down        = true;
        thumb->pressed_at  = record->event.time;
        thumb->interrupted = false;

        if (other->down) {
            start_thumb_shift();
        } else {
            layer_on(thumb->layer);
        }
        return;
    }

    thumb->down = false;
    layer_off(thumb->layer);

    if (thumb_shift_on) {
        stop_thumb_shift();
    }

    if (!thumb->interrupted && timer_elapsed(thumb->pressed_at) < TAPPING_TERM) {
        tap_code(thumb->tap_keycode);
        omt_record_key(thumb->tap_keycode);
    }
}

// 入力キーをOneMoreTimeで再生可能な最終キーコードへ変換する。
static bool omt_resolve_keycode(uint16_t keycode, keyrecord_t *record, uint16_t *resolved) {
    if (IS_MOUSEKEY(keycode)) {
        return false;
    }

    switch (keycode) {
        case SFT_FIND:
        case ALT_CUT:
        case CTL_UNDO:
        case FNC_ALL:
            return false;
    }

    if (IS_QK_MOD_TAP(keycode)) {
        if (!record->tap.count) {
            return false;
        }
        keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_LAYER_TAP(keycode)) {
        if (!record->tap.count) {
            return false;
        }
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (!IS_QK_BASIC(keycode) && !IS_QK_MODS(keycode)) {
        return false;
    }

    if (is_modifier_key(keycode)) {
        return false;
    }

    uint8_t mods = get_mods() | get_weak_mods();
#ifndef NO_ACTION_ONESHOT
    mods |= get_oneshot_mods();
#endif

    if (mods & MOD_MASK_SHIFT) {
        switch (keycode) {
            case JP_MINS:
                *resolved = JP_UNDS;
                return true;
            case JP_QUOT:
                *resolved = JP_DQUO;
                return true;
            case JP_SCLN:
                *resolved = JP_COLN;
                return true;
            case JP_TILD:
                *resolved = JP_GRV;
                return true;
            case JP_YEN:
                *resolved = JP_PIPE;
                return true;
        }

        keycode = S(keycode);
    }

    *resolved = keycode;
    return true;
}

// キーイベントを処理し、レイヤ制御、独自キー、OneMoreTime記録を行う。
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // 親指キーと同時に別のキーを使った場合は、親指キーのタップを抑制する。
    if (record->event.pressed && keycode != CMD_SPC && keycode != NUM_ENT) {
        if (cmd_thumb.down) {
            cmd_thumb.interrupted = true;
        }
        if (num_thumb.down) {
            num_thumb.interrupted = true;
        }
    }

    if (record->event.pressed) {
        uint16_t resolved;
        if (omt_resolve_keycode(keycode, record, &resolved)) {
            omt_record_key(resolved);
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
        case CMD_SPC:
            process_thumb_key(&cmd_thumb, &num_thumb, record);
            return false;

        case NUM_ENT:
            process_thumb_key(&num_thumb, &cmd_thumb, record);
            return false;

        case SFT_FIND:{
            if (record->tap.count && record->event.pressed) {
                tap_and_record(C(KC_F));
                return false;
            }
            return true;
        }

        case ALT_CUT:{
            if (record->tap.count && record->event.pressed){
                tap_and_record(C(KC_X));
                return false;
            }
            return true;
        }

        case CTL_UNDO:{
            if (record->tap.count && record->event.pressed){
                tap_and_record(C(KC_Z));
                return false;
            }
            return true;
        }
        
        case FNC_ALL:{
            if (record->tap.count && record->event.pressed){
                tap_and_record(C(KC_A));
                return false;
            }
            return true;
        }

        case KILL_E:{
            if (record->event.pressed){
                delete_to_line_edge(KC_END);
            }
            return false;
        }

        case KILL_H:{
            if (record->event.pressed){
                delete_to_line_edge(KC_HOME);
            }
            return false;
        }

        default:
            return true;

    }
}


float h_acm = 0.0;
float v_acm = 0.0;

// トラックボール入力を回転補正し、レイヤに応じてカーソル移動またはスクロールへ変換する。
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

// Auto Mouseで使用するレイヤを設定し、機能を有効化する。
void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);
    set_auto_mouse_enable(true);
}

// エンコーダーの回転を垂直または水平スクロールへ変換する。
bool encoder_update_user(uint8_t index, bool clockwise) {
    (void)index;

    uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    if (layer == _CMD) {
        tap_code(clockwise ? MS_WHLR : MS_WHLL);
    } else {
        tap_code(clockwise ? MS_WHLD : MS_WHLU);
    }

    return false;
}