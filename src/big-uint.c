#include "big-uint.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void big_uint_init(big_uint_t *dest, uint32_t *arr, uint64_t len) {
    dest->arr = arr;
    dest->len = len;
}

// returns 1 if and only if `c` is a hex character
static uint8_t is_hex_digit(char c) {
    return      c < 48 
            || (c > 57 && c < 97) 
            ||  c > 102;
}

uint64_t big_uint_count_limbs(const char *num) {
    uint64_t len = strlen(num);
    uint64_t counter = len;
    
    const uint8_t MAX_IDX = 7;  // should be size of (base / 2) - 1
    
    int8_t ind = MAX_IDX; 
    uint64_t digits = 0;

    // digit counter loop
    while (counter > 1) {
        // if not valid number in ascii
        if (is_hex_digit(num[counter])) {
            --counter;
            continue;
        }

        if (ind < 0) {
            ind = MAX_IDX;
            ++digits;
        }
        --ind;
        --counter;
    }

    return digits + (ind < (int) MAX_IDX);
}

void big_uint_parse(uint32_t *dest, const char *num, uint64_t size) {
    uint64_t len = strlen(num);
    uint64_t counter = len;
    
    const uint8_t MAX_IDX = 7;  // should be (base / 2) - 1
    
    // using string library, so must 0 terminate
    char buf[MAX_IDX + 2];
    buf[MAX_IDX + 1] = 0;
    
    int8_t ind = 7;
    uint64_t digit = 0;

    // parsing loop
    while (counter > 1 && digit < size) {
        // if not valid number in ascii
        if (is_hex_digit(num[counter])) {
            --counter;
            continue;
        }

        // decrease index and counter together
        buf[ind--] = num[counter--];

        if (ind < 0) {
            ind = MAX_IDX;
            dest[digit++] = strtoul(buf, NULL, 16);
        }
    }
    
    if (ind < (int8_t) MAX_IDX) {
        dest[digit] = strtoul(&buf[ind + 1], NULL, 16);
    }
}

void big_uint_sprint(char *dest, const big_uint_t *value) {
    uint64_t len = value->len;
    const uint32_t *arr = value->arr;

    for (uint64_t i = len - 1; i < len; i--) {
        if (i == len - 1) sprintf(&dest[0], "%08x", arr[i]);
        else        sprintf(&dest[9 * (len - 1 - i) - 1], " %08x", arr[i]);
    }
}

void big_uint_print_helper(const big_uint_t *value) {
    char str[9 * value->len];
    big_uint_sprint(str, value);
    printf("%s\n", str);
}

uint8_t big_uint_equals(const big_uint_t *a, const big_uint_t *b) {
    // if they are the same pointer, they are the same
    if (a == b) return 1;

    // if they contain the same elements, they are the same
    if (a->arr == b->arr && a->len == b->len)
        return 1;
    
    uint64_t len_a = a->len;
    uint64_t len_b = b->len;

    uint64_t max = len_a > len_b ? len_a : len_b;
    uint64_t min = max == len_a ? len_b : len_a;
    
    uint64_t counter = 0;

    while (counter < max) {
        if ((counter >= len_a && b->arr[counter] != 0) ||
            (counter >= len_b && a->arr[counter] != 0) ||
            (counter < min && a->arr[counter] != b->arr[counter]))
            return 0;

        ++counter;
    }

    return 1;
}
