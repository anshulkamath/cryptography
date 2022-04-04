#include "big-uint.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************/
/*       BIG UINT INITIALIZATION        */
/****************************************/

void big_uint_init(big_uint_t *dest, uint32_t *arr, uint16_t len) {
    dest->arr = arr;
    dest->len = len;
}

// returns 1 if and only if `c` is a hex character
static uint8_t is_hex_digit(char c) {
    return      c < 48 
            || (c > 57 && c < 97) 
            ||  c > 102;
}

uint16_t big_uint_count_limbs(const char *num) {
    uint16_t len = strlen(num);
    uint16_t counter = len;
    
    const uint8_t MAX_IDX = 7;  // should be size of (base / 2) - 1
    
    int8_t ind = MAX_IDX; 
    uint16_t digits = 0;

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

void big_uint_parse(uint32_t *dest, const char *num, uint16_t size) {
    uint16_t len = strlen(num);
    uint16_t counter = len;
    
    const uint8_t MAX_IDX = 7;  // should be (base / 2) - 1
    
    // using string library, so must 0 terminate
    char buf[MAX_IDX + 2];
    buf[MAX_IDX + 1] = 0;
    
    int8_t ind = 7;
    uint16_t digit = 0;

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

void big_uint_copy(big_uint_t *dest, const big_uint_t *src) {
    for (uint16_t i = 0; i < dest->len; i++)
        dest->arr[i] = i < src->len ? src->arr[i] : 0;
}

/****************************************/
/*           PRINT OPERATIONS           */
/****************************************/

void big_uint_sprint(char *dest, const big_uint_t *value) {
    uint16_t len = value->len;
    const uint32_t *arr = value->arr;

    for (uint16_t i = len - 1; i < len; i--) {
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
    
    uint16_t len_a = a->len;
    uint16_t len_b = b->len;

    uint16_t max = len_a > len_b ? len_a : len_b;
    uint16_t min = max == len_a ? len_b : len_a;
    
    uint8_t res = 1;  // use res to maintain constant time for fixed length

    for (uint16_t i = 0; i < max; i++) {
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
    uint16_t len_a = a->len;
    uint16_t len_b = b->len;

    uint16_t max = len_a > len_b ? len_a : len_b;
    uint16_t min = max == len_a ? len_b : len_a;

    int8_t res = 0;  // use res to maintain constant time for fixed length

    for (uint16_t i = max - 1; i < max; i--) {
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
    for (uint16_t i = 0; i < a->len; i++) {
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

    for (uint16_t i = 0; i < result->len; i++) {
        a_val = i < a->len ? a->arr[i] : 0;
        b_val = i < b->len ? b->arr[i] : 0;

        result->arr[i] = a_val | b_val;
    }
}

void big_uint_and(big_uint_t *result, const big_uint_t *a, const big_uint_t *b) {
    uint32_t a_val = 0;
    uint32_t b_val = 0;

    for (uint16_t i = 0; i < result->len; i++) {
        a_val = i < a->len ? a->arr[i] : 0;
        b_val = i < b->len ? b->arr[i] : 0;

        result->arr[i] = a_val & b_val;
    }
}

void big_uint_xor(big_uint_t *result, const big_uint_t *a, const big_uint_t *b) {
    uint32_t a_val = 0;
    uint32_t b_val = 0;

    for (uint16_t i = 0; i < result->len; i++) {
        a_val = i < a->len ? a->arr[i] : 0;
        b_val = i < b->len ? b->arr[i] : 0;

        result->arr[i] = a_val ^ b_val;
    }
}

void big_uint_shr(big_uint_t *result, const big_uint_t *x, uint32_t n, uint8_t shift_t) {
    // calculate how many bits to shift
    uint32_t total_bits = n * !shift_t + n * shift_t * UINT_BITS;
    uint16_t limbs = total_bits / UINT_BITS;
    uint16_t bits  = total_bits % UINT_BITS;

    // prevent overshifting
    if (total_bits >= result->len * UINT_BITS) {
        memset(result->arr, 0, result->len * UINT_SIZE);
        return;
    }
    
    // temporary variable to allow for operator assignment
    uint32_t res[result->len];
    
    // move offset x limb in result array, shift to account for sub-limb shifts
    uint32_t shift = 0;
    for (uint16_t i = result->len - 1; i < result->len; i--) {
        uint32_t elem = (i + limbs) < x->len ? x->arr[i + limbs] : 0;
        res[i] = shift | (elem >> bits);
        shift = (elem << (UINT_BITS - bits)) * !!bits;
    }

    // copy the result into the destination
    memcpy(result->arr, res, result->len * UINT_SIZE);    
}

void big_uint_shl(big_uint_t *result, const big_uint_t *x, uint32_t n, uint8_t shift_t) {
    // calculate how many bits to shift
    uint32_t total_bits = n * !shift_t + n * shift_t * UINT_BITS;
    uint16_t limbs = total_bits / UINT_BITS;
    uint16_t bits  = total_bits % UINT_BITS;

    // prevent overshifting
    if (total_bits >= result->len * UINT_BITS) {
        memset(result->arr, 0, result->len * UINT_SIZE);
        return;
    }

    uint32_t res[result->len];
    
    // move offset x limb in result array, shift to account for sub-limb shifts
    uint32_t shift = 0, elem;
    for (uint16_t i = 0; i < result->len; i++) {
        // must cast due to integral promotion
        elem = (uint16_t) (i - limbs) < x->len ? x->arr[i - limbs] : 0;
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
    
    for (uint16_t i = 0; i < result->len; i++) {
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

    for (uint16_t i = 0; i < result->len; i++) {
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
    for (uint16_t i = 0; i < result->len; i++) {
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
    for (uint16_t i = 0; i < result->len; i++) {
        // if out of range for a or b, use 0 instead
        a_val = a->arr[i];
        b_val = b->arr[i];
        c_val = a_val - b_val - underflow;

        result->arr[i] = c_val & (~1ull >> UINT_BITS);
        underflow = !!(c_val >> UINT_BITS);
    }
}

/* returns the i-th bit of x */
static uint8_t _get_bit(const big_uint_t *x, uint16_t i) {
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

    for (uint16_t i = 0; i < a->len; i++) {
        overflow = 0;
        for (uint16_t j = 0; j < b->len; j++) {
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
    for (uint16_t i = 0; i < c->len; i++) {
        val = res[i] + carry;
        c->arr[i] = val;
        carry = val >> UINT_BITS;
    }
}

void big_uint_div(big_uint_t *q, big_uint_t *r, const big_uint_t *u, const big_uint_t *v) {
    uint64_t len = q->len > r->len ? u->len : v->len;
    
    big_uint_t quo_t;
    big_uint_t rem_t;
    big_uint_t zero_t;

    big_uint_create(&quo_t, len);
    big_uint_create(&rem_t, len);
    big_uint_create(&zero_t, len);

    // if divide by 0, do nothing
    if (big_uint_is_zero(v)) {
        return;
    }

    const uint32_t NUM_BITS = UINT_BITS * len;
    for (uint16_t i = NUM_BITS - 1; i < NUM_BITS ; i--) {
        // q <<= 1
        big_uint_shl(&quo_t, &quo_t, 1, SHIFT_BIT);

        // (r <<= 1) |= (u >> i) & 0b1
        big_uint_shl(&rem_t, &rem_t, 1, SHIFT_BIT);
        rem_t.arr[0] |= _get_bit(u, i);

        if (big_uint_cmp(&rem_t, v) < 0) {
            // add to keep constant time
            big_uint_add(&rem_t, &rem_t, &zero_t);
            continue;
        }

        // q |= 1
        quo_t.arr[0] |= 1;

        // r -= v
        big_uint_sub(&rem_t, &rem_t, v);
    }

    big_uint_copy(q, &quo_t);
    big_uint_copy(r, &rem_t);
}

static uint32_t _log2_bit(const big_uint_t *x) {
    uint32_t curr = 0;
    uint32_t res  = 0;
    for (uint16_t i = 0; i < x->len; i++) {
        curr = x->arr[i];
        for (uint16_t j = 0; j < UINT_BITS; j++) {
            if (curr >> j) res = (i * UINT_BITS + j);
        }
    }

    return res;
}

static uint32_t _log2_limb(const big_uint_t *x) {
    uint32_t res = 0;
    for (uint16_t i = 0; i < x->len; i++) {
        if (x->arr[i]) res = i;
    }

    return res;
}

uint32_t big_uint_log2(const big_uint_t *x, uint8_t log_t) {
    if (log_t)  return _log2_limb(x);
    else        return _log2_bit(x);
}

static void _big_uint_gcd_helper(big_uint_t *d, const big_uint_t *a, const big_uint_t *b, uint16_t len) {
    big_uint_t quotient, remainder;
    big_uint_create(&quotient, len);
    big_uint_create(&remainder, len);

    big_uint_div(&quotient, &remainder, a, b);

    if (big_uint_is_zero(&remainder)) {
        big_uint_copy(d, b);
        return;
    }

    _big_uint_gcd_helper(d, b, &remainder, len);
}

void big_uint_gcd(big_uint_t *d, const big_uint_t *a, const big_uint_t *b) {
    big_uint_t max, min;
    uint16_t len = a->len > b->len ? a->len : b->len;

    big_uint_create(&max, len);
    big_uint_create(&min, len);

    int8_t cmp = big_uint_cmp(a, b);
    big_uint_copy(&max, cmp >= 0 ? a : b);
    big_uint_copy(&min, cmp < 0 ? a : b);

    _big_uint_gcd_helper(d, &max, &min, len);
}

static void _big_uint_gcd_extended_helper(big_uint_t *x, big_uint_t *y, const big_uint_t *a, const big_uint_t *b, uint16_t len) {
    big_uint_t quotient, remainder;
    big_uint_create(&quotient, len);
    big_uint_create(&remainder, len);

    big_uint_div(&quotient, &remainder, a, b);

    // base case: if the remainder is 0, initialize x = 0, y = 1
    if (big_uint_is_zero(&remainder)) {
        memset(x->arr, 0, x->len * UINT_SIZE);
        y->arr[0] = 1;
        return;
    }

    // get x, y values from successive definition
    _big_uint_gcd_extended_helper(x, y, b, &remainder, len);

    big_uint_t temp;
    big_uint_create(&temp, len);

    // calculate temp = x - (y * quotient)
    big_uint_mult(&temp, y, &quotient);
    big_uint_sub(&temp, x, &temp);

    // x_new = y_old
    big_uint_copy(x, y);
    
    // y_new = temp
    big_uint_copy(y, &temp);
}

void big_uint_gcd_extended(big_uint_t *x, big_uint_t *y, const big_uint_t *a, const big_uint_t *b) {
    big_uint_t max, min;
    uint16_t len = a->len > b->len ? a->len : b->len;

    big_uint_create(&max, len);
    big_uint_create(&min, len);

    // ensure that a > b when algorithm starts
    int8_t cmp = big_uint_cmp(a, b);
    big_uint_copy(&max, cmp >= 0 ? a : b);
    big_uint_copy(&min, cmp < 0 ? a : b);

    _big_uint_gcd_extended_helper(x, y, &max, &min, len);
}
