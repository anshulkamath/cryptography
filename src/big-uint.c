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
    
    uint8_t res = 1;  // use res to maintain constant time for fixed length

    for (uint64_t i = 0; i < max; i++) {
        if ((i >= len_a && b->arr[i] != 0) ||
            (i >= len_b && a->arr[i] != 0) ||
            (i < min && a->arr[i] != b->arr[i]))
            res = 0;
    }

    return res;
}

int8_t big_uint_cmp(const big_uint_t *a, const big_uint_t *b) {
    uint64_t len_a = a->len;
    uint64_t len_b = b->len;

    uint64_t max = len_a > len_b ? len_a : len_b;
    uint64_t min = max == len_a ? len_b : len_a;

    int8_t res = 0;  // use res to maintain constant time for fixed length

    for (uint64_t i = max - 1; i < max; i--) {
        // if the comparison has already been determined, continue
        if (res) continue;

        // a has more (non-zero) limbs
        else if (i >= len_b && a->arr[i] != 0)
            res = 1;

        // b has more (non-zero) limbs
        else if (i >= len_a && b->arr[i] != 0)
            res = -1;
        
        // corresponding limb is different between a and b
        else if (i < min && a->arr[i] != b->arr[i])
            res = a->arr[i] > b->arr[i] ? 1 : -1;
    }

    return res;
}

big_uint_t big_uint_max(const big_uint_t *a, const big_uint_t *b) {
    return big_uint_cmp(a, b) >= 0 ? *a : *b;
}

big_uint_t big_uint_min(const big_uint_t *a, const big_uint_t *b) {
    return big_uint_cmp(a, b) <= 0 ? *a : *b;
}

void big_uint_or(big_uint_t *result, const big_uint_t *a, const big_uint_t *b) {
    uint32_t a_val = 0;
    uint32_t b_val = 0;

    for (uint64_t i = 0; i < result->len; i++) {
        a_val = i < a->len ? a->arr[i] : 0;
        b_val = i < b->len ? b->arr[i] : 0;

        result->arr[i] = a_val | b_val;
    }
}

void big_uint_and(big_uint_t *result, const big_uint_t *a, const big_uint_t *b) {
    uint32_t a_val = 0;
    uint32_t b_val = 0;

    for (uint64_t i = 0; i < result->len; i++) {
        a_val = i < a->len ? a->arr[i] : 0;
        b_val = i < b->len ? b->arr[i] : 0;

        result->arr[i] = a_val & b_val;
    }
}

void big_uint_xor(big_uint_t *result, const big_uint_t *a, const big_uint_t *b) {
    uint32_t a_val = 0;
    uint32_t b_val = 0;

    for (uint64_t i = 0; i < result->len; i++) {
        a_val = i < a->len ? a->arr[i] : 0;
        b_val = i < b->len ? b->arr[i] : 0;

        result->arr[i] = a_val ^ b_val;
    }
}

void big_uint_shr(big_uint_t *result, const big_uint_t *x, uint64_t n, uint8_t shift_t) {
    // calculate how many bits to shift
    uint64_t total_bits = n * (1 - shift_t) + n * shift_t * UINT_BITS;
    uint64_t limbs = total_bits / UINT_BITS;
    uint64_t bits  = total_bits % UINT_BITS;

    // prevent overshifting
    if (total_bits >= result->len * UINT_BITS) {
        memset(result->arr, 0, result->len * UINT_SIZE);
        return;
    }
    
    // temporary variable to allow for operator assignment
    uint32_t res[result->len];
    
    // move offset x limb in result array, shift to account for sub-limb shifts
    uint32_t shift = 0;
    for (uint64_t i = result->len - 1; i < result->len; i--) {
        uint32_t elem = (i + limbs) < x->len ? x->arr[i + limbs] : 0;
        res[i] = shift | (elem >> bits);
        shift = (elem << (UINT_BITS - bits)) * !!bits;
    }

    // copy the result into the destination
    memcpy(result->arr, res, result->len * UINT_SIZE);    
}

void big_uint_shl(big_uint_t *result, const big_uint_t *x, uint64_t n, uint8_t shift_t) {
    // calculate how many bits to shift
    uint64_t total_bits = n * (1 - shift_t) + n * shift_t * UINT_BITS;
    uint64_t limbs = total_bits / UINT_BITS;
    uint64_t bits  = total_bits % UINT_BITS;

    // prevent overshifting
    if (total_bits >= result->len * UINT_BITS) {
        memset(result->arr, 0, result->len * UINT_SIZE);
        return;
    }
    
    // move offset x limb in result array, shift to account for sub-limb shifts
    uint32_t shift = 0;
    for (uint64_t i = result->len - 1; i < result->len; i--) {
        uint32_t elem = (i - limbs) < x->len ? x->arr[i - limbs] : 0;
        result->arr[i] = (elem << bits) | shift;
        shift = (elem >> (UINT_BITS - bits)) * !!bits;
    }
}

void big_uint_add(big_uint_t *result, const big_uint_t *a, const big_uint_t *b) {
    uint32_t a_val, b_val;
    uint8_t carry = 0;

    // optimize out conditionals for same length big integers
    if (a->len == b->len) {
        for (uint64_t i = 0; i < result->len; i++) {
            a_val = a->arr[i];
            b_val = b->arr[i];
            
            result->arr[i] = a_val + b_val + carry;
            carry = ((uint64_t) a_val + b_val + carry) > UINT32_MAX;
        }

        return;
    }

    // allow for different length integers to be summed
    for (uint64_t i = 0; i < result->len; i++) {
        a_val = i < a->len ? a->arr[i] : 0;
        b_val = i < b->len ? b->arr[i] : 0;

        result->arr[i] = a_val + b_val + carry;
        carry = ((uint64_t) a_val + b_val + carry) > UINT32_MAX;
    }
}

void big_uint_sub(big_uint_t *result, const big_uint_t *a, const big_uint_t *b) {
    uint32_t a_val, b_val;
    uint8_t carry = 0;

    // optimize out conditionals for same length big integers
    if (a->len == b->len) {
        for (uint64_t i = 0; i < result->len; i++) {
            a_val = a->arr[i];
            b_val = b->arr[i];

            result->arr[i] = a_val - b_val - carry;
            carry =(uint64_t) a_val - b_val - carry > UINT32_MAX;
        }

        return;
    }

    // allow for different length integers to be summed
    for (uint64_t i = 0; i < result->len; i++) {
        a_val = i < a->len ? a->arr[i] : 0;
        b_val = i < b->len ? b->arr[i] : 0;

        result->arr[i] = a_val - b_val - carry;
        carry =(uint64_t) a_val - b_val - carry > UINT32_MAX;
    }
}

void big_uint_mult(big_uint_t *result, const big_uint_t *a, const big_uint_t *b) {
    uint64_t a_val, b_val, product;

    uint32_t res[result->len];
    memset(res, 0, result->len * UINT_SIZE);

    for (uint64_t i = 0; i < a->len; i++) {
        for (uint64_t j = 0; j < b->len; j++) {
            // do not write outside of result
            if (i + j >= result->len) break;

            a_val = a->arr[i];
            b_val = b->arr[j];
            product = a_val * b_val;

            // store lower 32 bits of product in current limb
            res[i + j] += product & (~1ll >> UINT_BITS);

            // store upper 32 bits of product in next limb (if within range)
            if (i + j + 1 < result->len)
                res[i + j + 1] += product >> UINT_BITS;
        }
    }

    // copy the result to our destination
    memcpy(result->arr, res, result->len * UINT_SIZE);
}
