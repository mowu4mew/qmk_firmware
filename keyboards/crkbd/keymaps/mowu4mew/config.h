#pragma once

#define MASTER_RIGHT
#define NO_MUSIC_MODE
#define LAYER_STATE_16BIT
//#define PAW3204_SCLK_PIN D0
//#define PAW3204_SDIO_PIN D1

#define COMBO_COUNT 7
#define COMBO_TERM 10

#define TAPPING_TERM 220
#define TAPPING_TERM_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define RETRO_TAPPING_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT
#



//#define LEADER_PER_KEY_TIMING
//#define LEADER_TIMEOUT 500

//#define HOLD_ON_OTHER_KEY_PRESS   //MTキー長押し先離し&次キー後離しでMTキーtap判定
//#define TAPPING_FORCE_HOLD        //MTキー長押しでもTリピートしない。
//#define PERMISSIVE_HOLD           //MTキーホールド判定前に次キーtapでもmod有効
//#define RETRO_TAPPING             //MTキー長押し離しでtap
//#define TAPPING_TOGGLE 1          //tt(layer)を使用するとき用

//#undef LOCKING_SUPPORT_ENABLEf
//#undef LOCKING_RESYHC_ENABLE
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_TAPPING

//#define LAYER_STATE_8BIT
