/**
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <https://unlicense.org>
 */
#include <stdint.h>
#include <string.h>
#include "onemoretime.h"

#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif


#ifndef ONE_MORE_TIME_BUFFER_SIZE
#  ifdef ONE_MORE_TIME_TEST
#    define ONE_MORE_TIME_BUFFER_SIZE 6
#  else
#    define ONE_MORE_TIME_BUFFER_SIZE 32
#  endif
#endif

// ring buffer
static uint16_t one_more_time_buffer[ONE_MORE_TIME_BUFFER_SIZE];
static uint8_t one_more_time_buffer_index = 0;
/*
#ifdef CONSOLE_ENABLE
static void one_more_time_dump(void) {
    uprintf("  idx=%u\n", one_more_time_buffer_index);

    for (int i=0; i<ONE_MORE_TIME_BUFFER_SIZE; i++) {
        uprintf("  i=%u keycode=%d %c\n",
            i,
            one_more_time_buffer[i],
            (one_more_time_buffer_index-1 == i) ? '*' : ' ');
    }
}
#endif
*/
void one_more_time_record(uint16_t keycode) {
#ifdef CONSOLE_ENABLE
    uprintf("record key=%u\n", keycode);
#endif

    one_more_time_buffer[one_more_time_buffer_index] = keycode;
    one_more_time_buffer_index = (one_more_time_buffer_index + 1) % ONE_MORE_TIME_BUFFER_SIZE;
}

static bool is_duplicated(int length) {
    for (int offset = 0; offset < length; offset++) {
        int recent = one_more_time_buffer_index - 1 - offset;
        if (recent < 0) {
            recent += ONE_MORE_TIME_BUFFER_SIZE;
        }
        int previous = one_more_time_buffer_index - 1 - length - offset;
        if (previous < 0) {
            previous += ONE_MORE_TIME_BUFFER_SIZE;
        }
        bool result = one_more_time_buffer[recent] == one_more_time_buffer[previous];
#ifdef CONSOLE_ENABLE
        uprintf("length=%d offset=%d recent=%d previous=%d result=%d\n", length, offset, recent, previous, result ? 1 : 0);
#endif
        if (!result) {
            return false;
        }
    }
    return true;
}

static int16_t check_duplication(void) {
    for (int length = ONE_MORE_TIME_BUFFER_SIZE / 2; length > 0; length--) {
        if (is_duplicated(length)) {
            return length;
        }
    }
    return -1; // no dups
}

bool one_more_time_play(void) {
    int16_t length = check_duplication();

#ifdef CONSOLE_ENABLE
    uprintf("Play: length=%d\n", length);
#endif

    if (length < 0) {
        return false;
    }

    for (int offset = length - 1; offset >= 0; offset--) {
        int index = one_more_time_buffer_index - 1 - offset;
        if (index < 0) {
            index += ONE_MORE_TIME_BUFFER_SIZE;
        }
#ifdef CONSOLE_ENABLE
        uprintf("play: key=%d\n", one_more_time_buffer[index]);
#endif
        tap_code16(one_more_time_buffer[index]);
    }

    return true;
}

#ifdef ONE_MORE_TIME_TEST

#include <stdio.h>
#include <assert.h>

void clear_mods(void) {
}

uint8_t get_mods() {
    return 0;
}

void set_mods(uint8_t mods) {
}

void register_code(uint8_t keycode) {
    printf("  reigster=%d\n", keycode);
}

void unregister_code(uint8_t keycode) {
    printf("  unreigster=%d\n", keycode);
}

void run_test(uint16_t test_sequence[], int sequence_length, int expected_result) {
    for (int i = 0; i < sequence_length; i++) {
        one_more_time_record(test_sequence[i]);
    }
    int length = check_duplication();
    printf("length=%d\n", length);
    assert(length == expected_result);

    one_more_time_play();
}

#define TEST(x, e) run_test((x), sizeof((x)) / sizeof((x)[0]), (e))

void test_one_more_time_play() {
    uint16_t test_sequence1[] = { KC_A, KC_B, KC_C, KC_A, KC_B, KC_C };
    TEST(test_sequence1, 3);

    uint16_t test_sequence2[] = { KC_E, KC_A, KC_B, KC_C, KC_A, KC_B, KC_C };
    TEST(test_sequence2, 3);

    uint16_t test_sequence3[] = { KC_E, KC_N, KC_B, KC_C, KC_B, KC_C };
    TEST(test_sequence3, 2);

    uint16_t test_sequence4[] = { C(KC_B), C(KC_C), C(KC_B), C(KC_C) };
    TEST(test_sequence4, 2);

    uint16_t test_sequence6[] = { KC_A, KC_B, KC_C, KC_A, KC_Z, KC_Z };
    TEST(test_sequence6, 1);

}


int main() {
    test_one_more_time_play();

    printf("OK\n");
    return 0;

}
#endif // ONE_MORE_TIME_TEST

