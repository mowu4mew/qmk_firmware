#include QMK_KEYBOARD_H
#include "pointing_device.h"
#include "keymap_japanese.h"
#include "onemoretime.h"

// レイヤー定義。
enum layer_names {
    _QWERTY = 0,
    _NUM,
    _CMD,
    _FNC,
    _MOUSE,
};

// カスタムキーコード定義。
enum custom_keycodes {
    CMD_SPC = SAFE_RANGE,
    NUM_ENT,
    KILL_E,
    KILL_H,
    OMT,
};

// トラックボールの回転角、移動速度、スクロール速度、レポート上限。
#define TRACKBALL_ROTATION_RADIANS (-45.0 * (M_PI / 180.0))
#define CURSOR_GAIN               3
#define FINE_CURSOR_DIVISOR       3
#define SCROLL_DIVISOR            6.0
#define REPORT_LIMIT              127

// Mod-Tapエイリアス。
#define SFT_F       LSFT_T(KC_F)
#define SFT_J       RSFT_T(KC_J)
#define SFT_F3      LSFT_T(KC_F3)
#define SFT_FIND    RSFT_T(KC_NO)

#define CTL_Z       LCTL_T(KC_Z)
#define CTL_SLSH    RCTL_T(JP_SLSH)
#define CTL_1       LCTL_T(KC_1)
#define CTL_0       RCTL_T(KC_0)
#define CTL_UNDO    LCTL_T(KC_NO)
#define CTL_F1      LCTL_T(KC_F1)
#define CTL_F10     RCTL_T(KC_F10)

#define ALT_X       LALT_T(KC_X)
#define ALT_DOT     RALT_T(JP_DOT)
#define ALT_2       LALT_T(KC_2)
#define ALT_9       RALT_T(KC_9)
#define ALT_UP      RALT_T(KC_PGUP)
#define ALT_CUT     RALT_T(KC_X)
#define ALT_F2      LALT_T(KC_F2)
#define ALT_F9      RALT_T(KC_F9)

#define GUI_COM     RGUI_T(JP_COMM)
#define GUI_8       RGUI_T(KC_8)
#define GUI_F8      RGUI_T(KC_F8)

#define FNC_ALL     LT(_FNC, KC_NO)

// ショートカットエイリアス。
#define PRINT_SCREEN G(S(KC_S))
#define PAGE_TOP     C(KC_HOME)
#define PAGE_BOTTOM  C(KC_END)

// コンボ定義。
enum combo_names {
    COMBO_DESKTOP_RIGHT,
    COMBO_DESKTOP_LEFT,
    COMBO_HENKAN,
    COMBO_MUHENKAN,
    COMBO_TAB,
    COMBO_ARROW_TAB,
    COMBO_ESCAPE,
    COMBO_DELETE_ESCAPE,
    COMBO_MOUSE_BUTTON_3,
    COMBO_PRINT_SCREEN,
};

const uint16_t PROGMEM desktop_right_combo[]    = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM desktop_left_combo[]     = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM henkan_combo[]           = {KC_L, KC_K, COMBO_END};
const uint16_t PROGMEM muhenkan_combo[]         = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM tab_combo[]              = {KC_K, KC_J, COMBO_END};
const uint16_t PROGMEM arrow_tab_combo[]        = {KC_DOWN, KC_LEFT, COMBO_END};
const uint16_t PROGMEM escape_combo[]           = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM delete_escape_combo[]    = {KC_DEL, SFT_FIND, COMBO_END};
const uint16_t PROGMEM mouse_button_3_combo[]   = {ALT_DOT, GUI_COM, COMBO_END};
const uint16_t PROGMEM print_screen_combo[]     = {ALT_X, KC_C, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [COMBO_DESKTOP_RIGHT]   = COMBO(desktop_right_combo, C(G(KC_RIGHT))),
    [COMBO_DESKTOP_LEFT]    = COMBO(desktop_left_combo, C(G(KC_LEFT))),
    [COMBO_HENKAN]          = COMBO(henkan_combo, JP_HENK),
    [COMBO_MUHENKAN]        = COMBO(muhenkan_combo, JP_MHEN),
    [COMBO_TAB]             = COMBO(tab_combo, KC_TAB),
    [COMBO_ARROW_TAB]       = COMBO(arrow_tab_combo, KC_TAB),
    [COMBO_ESCAPE]          = COMBO(escape_combo, KC_ESC),
    [COMBO_DELETE_ESCAPE]   = COMBO(delete_escape_combo, KC_ESC),
    [COMBO_MOUSE_BUTTON_3]  = COMBO(mouse_button_3_combo, MS_BTN3),
    [COMBO_PRINT_SCREEN]    = COMBO(print_screen_combo, PRINT_SCREEN),
};

// 日本語配列向けShiftオーバーライド。
const key_override_t underscore_shift_override      = ko_make_basic(MOD_MASK_SHIFT, JP_MINS, JP_UNDS);
const key_override_t double_quote_shift_override    = ko_make_basic(MOD_MASK_SHIFT, JP_QUOT, JP_DQUO);
const key_override_t colon_shift_override           = ko_make_basic(MOD_MASK_SHIFT, JP_SCLN, JP_COLN);
const key_override_t grave_shift_override           = ko_make_basic(MOD_MASK_SHIFT, JP_TILD, JP_GRV);
const key_override_t pipe_shift_override            = ko_make_basic(MOD_MASK_SHIFT, JP_YEN, JP_PIPE);

const key_override_t *key_overrides[] = {
    &underscore_shift_override,
    &double_quote_shift_override,
    &colon_shift_override,
    &grave_shift_override,
    &pipe_shift_override,
    NULL,
};

// キーマップ定義。
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
        XXXXXXX, FNC_ALL, C(KC_S),  KC_DEL, SFT_FIND,  KC_ESC,                  KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, MO(_FNC), XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX, CTL_UNDO, ALT_CUT, C(KC_C), C(KC_V), C(KC_Y),                   C(KC_N), KC_PGDN,     OMT,  ALT_UP, KC_RCTL, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
                                    XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______, XXXXXXX
    //                           `--------+--------+--------'                  `--------+--------+--------'
    ),

    [_FNC] = LAYOUT_split_3x6_3_2(
    //,-----------------------------------------------------|                  |-----------------------------------------------------.
        XXXXXXX, _______,  KC_F12, S(KC_TAB), KC_F3, C(KC_K),                    QK_BOOT, _______, PAGE_TOP, KC_RSFT, _______, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------|
        XXXXXXX, _______,  KC_F11,  KILL_E,  SFT_F3,  KC_ESC,                     KILL_H, KC_HOME, PAGE_BOTTOM, KC_END, _______, XXXXXXX,
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
                                    XXXXXXX, _______, XXXXXXX,                    XXXXXXX, _______, XXXXXXX
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

static bool thumb_shift_on = false;

// 両親指のレイヤを解除し、Shift同時押し状態を開始する。
static void start_thumb_shift(void) {
    layer_off(_CMD);
    layer_off(_NUM);
    cmd_thumb.interrupted = true;
    num_thumb.interrupted = true;
    thumb_shift_on        = true;
    add_weak_mods(MOD_BIT(KC_LSFT));
    send_keyboard_report();
}

// Shift同時押し状態を終了し、残っている親指のレイヤを有効にする。
static void stop_thumb_shift(void) {
    del_weak_mods(MOD_BIT(KC_LSFT));
    send_keyboard_report();
    thumb_shift_on = false;

    if (cmd_thumb.down) {
        layer_on(cmd_thumb.layer);
    } else if (num_thumb.down) {
        layer_on(num_thumb.layer);
    }
}

// キーをタップし、同じキーコードをOneMoreTimeへ記録する。
static void tap_and_record(uint16_t keycode) {
    tap_code16(keycode);
    one_more_time_record(keycode);
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
        one_more_time_record(thumb->tap_keycode);
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

    if (IS_MODIFIER_KEYCODE(keycode)) {
        return false;
    }

    uint8_t mods = get_mods() | get_weak_mods();
#ifndef NO_ACTION_ONESHOT
    mods |= get_oneshot_mods();
#endif

    if (mods & MOD_MASK_SHIFT) {
        switch (keycode) {
            case JP_MINS:
                keycode = JP_UNDS;
                break;
            case JP_QUOT:
                keycode = JP_DQUO;
                break;
            case JP_SCLN:
                keycode = JP_COLN;
                break;
            case JP_TILD:
                keycode = JP_GRV;
                break;
            case JP_YEN:
                keycode = JP_PIPE;
                break;
            default:
                keycode |= QK_LSFT;
                break;
        }
    }

    if (mods & MOD_MASK_CTRL) {
        keycode |= QK_LCTL;
    }
    if (mods & MOD_MASK_ALT) {
        keycode |= QK_LALT;
    }
    if (mods & MOD_MASK_GUI) {
        keycode |= QK_LGUI;
    }

    *resolved = keycode;
    return true;
}

// Mod-Tap/Layer-Tapのタップ時に指定キーを送信・記録する。
static bool process_macro_tap(keyrecord_t *record, uint16_t keycode) {
    if (record->tap.count && record->event.pressed) {
        tap_and_record(keycode);
        return false;
    }

    return true;
}

// QMKがキー押下前にクリアする親指ShiftのWeak Modsを復元する。
bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    (void)keycode;
    (void)record;

    if (thumb_shift_on) {
        add_weak_mods(MOD_BIT(KC_LSFT));
    }

    return true;
}

// 現在位置から行頭または行末までを選択して削除する。
static void delete_to_line_edge(uint16_t edge_keycode) {
    tap_and_record(S(edge_keycode));
    tap_and_record(KC_DEL);
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
            one_more_time_record(resolved);
        }
    }

    switch (keycode) {
        case OMT:
            if (record->event.pressed) {
                one_more_time_play();
            }
            return false;

        case CMD_SPC:
            process_thumb_key(&cmd_thumb, &num_thumb, record);
            return false;

        case NUM_ENT:
            process_thumb_key(&num_thumb, &cmd_thumb, record);
            return false;

        case JP_MINS:
            if (!thumb_shift_on) {
                return true;
            }
            if (record->event.pressed) {
                tap_code16(JP_UNDS);
            }
            return false;

        case SFT_FIND:
            return process_macro_tap(record, C(KC_F));

        case ALT_CUT:
            return process_macro_tap(record, C(KC_X));

        case CTL_UNDO:
            return process_macro_tap(record, C(KC_Z));

        case FNC_ALL:
            return process_macro_tap(record, C(KC_A));

        case KILL_E:
        case KILL_H:
            if (record->event.pressed) {
                delete_to_line_edge(keycode == KILL_E ? KC_END : KC_HOME);
            }
            return false;

        default:
            return true;
    }
}

static float horizontal_scroll_accumulator = 0.0;
static float vertical_scroll_accumulator   = 0.0;

// マウスレポートの範囲に値を制限する。
static int8_t clamp_report_value(int16_t value) {
    if (value > REPORT_LIMIT) {
        return REPORT_LIMIT;
    }
    if (value < -REPORT_LIMIT) {
        return -REPORT_LIMIT;
    }
    return (int8_t)value;
}

// センサー座標をキーボードの取り付け角度に合わせて回転する。
static void rotate_trackball(int8_t x, int8_t y, int16_t *rotated_x, int16_t *rotated_y) {
    *rotated_x = x * cos(TRACKBALL_ROTATION_RADIANS) - y * sin(TRACKBALL_ROTATION_RADIANS);
    *rotated_y = x * sin(TRACKBALL_ROTATION_RADIANS) + y * cos(TRACKBALL_ROTATION_RADIANS);
}

// 蓄積したスクロール量から今回送信できる量を取り出す。
static int8_t consume_scroll(float *accumulator, int8_t current) {
    int16_t requested = (int16_t)*accumulator;
    int8_t  result    = clamp_report_value((int16_t)current + requested);
    *accumulator -= result - current;
    return result;
}

// 回転後の移動量を主軸だけのスクロールへ変換する。
static report_mouse_t apply_scroll(report_mouse_t report, int16_t x, int16_t y) {
    if (abs(x) > abs(y)) {
        y = 0;
    } else {
        x = 0;
    }

    horizontal_scroll_accumulator -= (float)x / SCROLL_DIVISOR;
    vertical_scroll_accumulator   -= (float)y / SCROLL_DIVISOR;
    report.h = consume_scroll(&horizontal_scroll_accumulator, report.h);
    report.v = consume_scroll(&vertical_scroll_accumulator, report.v);
    report.x = 0;
    report.y = 0;
    return report;
}

// 回転後の移動量へ速度調整を適用する。
static report_mouse_t apply_cursor(report_mouse_t report, int16_t x, int16_t y) {
    int16_t adjusted_x = x * CURSOR_GAIN;
    int16_t adjusted_y = y * CURSOR_GAIN;

    if (layer_state_is(_CMD)) {
        adjusted_x /= FINE_CURSOR_DIVISOR;
        adjusted_y /= FINE_CURSOR_DIVISOR;
    }

    report.x = clamp_report_value(adjusted_x);
    report.y = clamp_report_value(adjusted_y);
    return report;
}

// トラックボール入力を回転補正し、レイヤに応じてカーソル移動またはスクロールへ変換する。
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    int16_t rotated_x;
    int16_t rotated_y;
    rotate_trackball(mouse_report.x, mouse_report.y, &rotated_x, &rotated_y);

    if (layer_state_is(_NUM)) {
        mouse_report = apply_scroll(mouse_report, rotated_x, rotated_y);
    } else {
        mouse_report = apply_cursor(mouse_report, rotated_x, rotated_y);
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