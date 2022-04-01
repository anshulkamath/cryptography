#include "big-uint.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************/
/*       BIG UINT INITIALIZATION        */
/****************************************/

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

/****************************************/
/*           PRINT OPERATIONS           */
/****************************************/

void big_uint_sprint(char *dest, const big_uint_t *value) {
    uint64_t len = value->len;
    const uint32_t *arr = value->arr;

    for (uint64_t i = len - 1; i < len; i--) {
        if (i == len - 1) sprintf(&dest[0], "%08x", arr[i]);
        else              sprintf(&dest[9 * (len - 1 - i) - 1], " %08x", arr[i]);
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
        res &= !(
                (i >= len_a && b->arr[i] != 0) ||
                (i >= len_b && a->arr[i] != 0) ||
                (i < min && a->arr[i] != b->arr[i])
            );
    }

    return res;
}

/****************************************/
/*        COMPARISON OPERATIONS         */
/****************************************/

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

uint8_t big_uint_is_zero(const big_uint_t *a) {
    uint8_t res = 1;
    for (uint64_t i = 0; i < a->len; i++) {
        res &= a->arr[i] == 0;
    }

    return res;
}

/****************************************/
/*          BITWISE OPERATIONS          */
/****************************************/

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
    uint64_t total_bits = n * !shift_t + n * shift_t * UINT_BITS;
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
    uint64_t total_bits = n * !shift_t + n * shift_t * UINT_BITS;
    uint64_t limbs = total_bits / UINT_BITS;
    uint64_t bits  = total_bits % UINT_BITS;

    // prevent overshifting
    if (total_bits >= result->len * UINT_BITS) {
        memset(result->arr, 0, result->len * UINT_SIZE);
        return;
    }

    uint32_t res[result->len];
    
    // move offset x limb in result array, shift to account for sub-limb shifts
    uint32_t shift = 0, elem;
    for (uint64_t i = 0; i < result->len; i++) {
        elem = (i - limbs) < x->len ? x->arr[i - limbs] : 0;
        res[i] = (elem << bits) | shift;
        shift = (elem >> (UINT_BITS - bits)) * !!bits;
    }

    memcpy(result->arr, res, result->len * UINT_SIZE);
}

/****************************************/
/*    ARITHMETIC OPERATIONS HELPERS     */
/****************************************/

/* performs addition for different length integers */
static void _big_uint_add_diff(big_uint_t *result, const big_uint_t *a, const big_uint_t *b) {
    uint64_t a_val, b_val, c_val;
    uint64_t overflow = 0;
    
    for (uint64_t i = 0; i < result->len; i++) {
        a_val = i < a->len ? a->arr[i] : 0;
        b_val = i < b->len ? b->arr[i] : 0;
        c_val = a_val + b_val + overflow;

        result->arr[i] = c_val & (~1ull >> UINT_BITS);
        overflow = !!(c_val >> UINT_BITS);
    }
}

/* performs addition for same length integers */
static void _big_uint_add_same(big_uint_t *result, const big_uint_t *a, const big_uint_t *b) {
    uint64_t a_val, b_val, c_val;
    uint64_t overflow = 0;

    for (uint64_t i = 0; i < result->len; i++) {
        a_val = a->arr[i];
        b_val = b->arr[i];
        c_val = a_val + b_val + overflow;

        result->arr[i] = c_val & (~1ull >> UINT_BITS);
        overflow = !!(c_val >> UINT_BITS);
    }
}

/* performs subtraction for different length integers */
static void _big_uint_sub_diff(big_uint_t *result, const big_uint_t *a, const big_uint_t *b) {
    uint64_t a_val, b_val, c_val;
    uint64_t underflow = 0;
    
    // allow for different length integers to be subtracted
    for (uint64_t i = 0; i < result->len; i++) {
        // if out of range for a or b, use 0 instead
        a_val = i < a->len ? a->arr[i] : 0;
        b_val = i < b->len ? b->arr[i] : 0;
        c_val = a_val - b_val - underflow;

        result->arr[i] = c_val & (~1ull >> UINT_BITS);
        underflow = !!(c_val >> UINT_BITS);
    }
}

/* performs subtraction for same length integers */
static void _big_uint_sub_same(big_uint_t *result, const big_uint_t *a, const big_uint_t *b) {
    uint64_t a_val, b_val, c_val;
    uint64_t underflow = 0;

    // allow for different length integers to be subtracted
    for (uint64_t i = 0; i < result->len; i++) {
        // if out of range for a or b, use 0 instead
        a_val = a->arr[i];
        b_val = b->arr[i];
        c_val = a_val - b_val - underflow;

        result->arr[i] = c_val & (~1ull >> UINT_BITS);
        underflow = !!(c_val >> UINT_BITS);
    }
}

/* returns the i-th bit of x */
static uint8_t _get_bit(big_uint_t *x, uint64_t i) {
    uint64_t limb = i / UINT_BITS;
    uint8_t  bit  = i % UINT_BITS;

    if (i > x->len * UINT_BITS) return 0;

    return (x->arr[limb] >> bit) & 1;
}

/****************************************/
/*        ARITHMETIC OPERATIONS         */
/****************************************/

void big_uint_add(big_uint_t *c, const big_uint_t *a, const big_uint_t *b) {
    // offers small optimization if integers are same length
    if (a->len == b->len) {
        _big_uint_add_same(c, a, b);
        return;
    } 

    // allow for different length integers to be summed
    _big_uint_add_diff(c, a, b);
}

void big_uint_sub(big_uint_t *c, const big_uint_t *a, const big_uint_t *b) {
    // offers small optimization if integers are same length
    if (a->len == b->len) {
        _big_uint_sub_same(c, a, b);
        return;
    }

    // allow for different length integers to be subtracted
    _big_uint_sub_diff(c, a, b);
}

void big_uint_mult(big_uint_t *c, const big_uint_t *a, const big_uint_t *b) {
    uint64_t a_val, b_val, product, overflow;

    uint64_t res[c->len];
    memset(res, 0, c->len * D_UINT_SIZE);

    for (uint64_t i = 0; i < a->len; i++) {
        overflow = 0;
        for (uint64_t j = 0; j < b->len; j++) {
            // do not write outside of c
            if (i + j >= c->len) break;

            a_val = a->arr[i];
            b_val = b->arr[j];
            product = a_val * b_val;

            // store lower 32 bits of product in current limb
            res[i + j] += product & (~1ull >> UINT_BITS);
            
            // add overflow from previous partial product
            res[i + j] += overflow;

            // store upper 32 bits (overflow) of product in next limb
            overflow = product >> UINT_BITS;
        }

        // if c can store the previous overflow, put it in
        if (i + b->len < c->len)
            res[i + b->len] += overflow;
    }

    // if c can store the previous overflow, put it in
    if (a->len + b->len < c->len)
        res[a->len + b->len] += overflow;

    // flatten array of `uint64_t`s into `uint32_t`s, accounting for overflow
    uint64_t val, carry = 0;
    for (uint64_t i = 0; i < c->len; i++) {
        val = res[i] + carry;
        c->arr[i] = val;
        carry = val >> UINT_BITS;
    }
}

void big_uint_div(big_uint_t *q, big_uint_t *r, big_uint_t *u, big_uint_t *v) {
    uint64_t len = q->len > r->len ? u->len : v->len;
    uint32_t q_cpy[len];
    uint32_t r_cpy[len];
    uint32_t zero[len];

    big_uint_t quo_t;
    memset(q_cpy, 0, len * UINT_SIZE);
    big_uint_init(&quo_t, q_cpy, len);

    big_uint_t rem_t;
    memset(r_cpy, 0, len * UINT_SIZE);
    big_uint_init(&rem_t, r_cpy, len);

    big_uint_t zero_t;
    memset(zero, 0, len * UINT_SIZE);
    big_uint_init(&zero_t, zero, len);

    // if divide by 0, do nothing
    if (big_uint_is_zero(v)) {
        return;
    }

    const uint64_t NUM_BITS = UINT_BITS * len;
    for (uint64_t i = NUM_BITS - 1; i < NUM_BITS ; i--) {
        // q <<= 1
        big_uint_shl(&quo_t, &quo_t, 1, SHIFT_BIT);

        // (r <<= 1) |= (u >> i) & 0b1
        big_uint_shl(&rem_t, &rem_t, 1, SHIFT_BIT);
        r_cpy[0] |= _get_bit(u, i);

        if (big_uint_cmp(&rem_t, v) < 0) {
            // add to keep constant time
            big_uint_add(&rem_t, &rem_t, &zero_t);
            continue;
        }

        // q |= 1
        q_cpy[0] |= 1;

        // r -= v
        big_uint_sub(&rem_t, &rem_t, v);
    }

    memcpy(q->arr, q_cpy, q->len * UINT_SIZE);
    memcpy(r->arr, r_cpy, r->len * UINT_SIZE);
}
