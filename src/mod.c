#include "mod.h"
#include "big-uint.h"

#include <stdint.h>
#include <string.h>

// constant zero
uint32_t ZERO_ARR[] = { 0 };
big_uint_t ZERO = { .arr = (uint32_t *) &ZERO_ARR, .len = 1 };

void mod_big_uint(big_uint_t *res, const big_uint_t *x, const big_uint_t *p) {
	big_uint_t q;
	big_uint_create(&q, x->len);

	big_uint_div(&q, res, x, p);
}

void mod_add(big_uint_t *res, const big_uint_t *a, const big_uint_t *b, const big_uint_t *p) {
	big_uint_add(res, a, b);

	// if we are above the prime, calculate the corresponding residue class
	if (big_uint_cmp(res, p) > 0) {
		big_uint_sub(res, res, p);
		return;
	}
	
	big_uint_sub(res, res, &ZERO);
}
