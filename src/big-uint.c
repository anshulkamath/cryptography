#include "big-uint.h"

#include <stdint.h>
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