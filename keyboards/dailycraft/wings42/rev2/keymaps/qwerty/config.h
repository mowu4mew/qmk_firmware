#pragma once

#define MASTER_RIGHT
#define NO_MUSIC_MODE
#define NO_ACTION_ONESHOT
#define LAYER_STATE_8BIT   //layer 8まで
#define PAW3204_SCLK_PIN D0
#define PAW3204_SDIO_PIN D1

#define COMBO_COUNT 10
#define COMBO_TERM 12

#define TAPPING_TERM 185
#define TAPPING_TERM_PER_KEY

//#define PERMISSIVE_HOLD           //MTキーホールド判定前に次キーtapでもmod有効
//#define PERMISSIVE_HOLD_PER_KEY
//#define HOLD_ON_OTHER_KEY_PRESS   //MTキー長押し先離し&次キー後離しでMTキーtap判定
//#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
//#define TAPPING_FORCE_HOLD        //MTキー長押しでもTリピートしない。
//#define RETRO_TAPPING             //MTキー長押し離しでtap
//#define RETRO_TAPPING_PER_KEY
//#define TAPPING_TOGGLE 1          //tt(layer)を使用するとき用

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 3
#define AUTO_MOUSE_TIME 1200
#define AUTO_MOUSE_THRESHOLD 5

#define LAYER_LOCK_IDLE_TIMEOUT 10000  // Turn off after 10 seconds.

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

//#define LEADER_PER_KEY_TIMING
//#define LEADER_TIMEOUT 500

//#undef LOCKING_SUPPORT_ENABLEf
//#undef LOCKING_RESYHC_ENABLE
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_TAPPING

//#define LAYER_STATE_8BIT
