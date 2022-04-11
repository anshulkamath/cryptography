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

void mod_sub(big_uint_t *res, const big_uint_t *a, const big_uint_t *b, const big_uint_t *p) {
	big_uint_sub(res, a, b);

	// if we are above the prime, calculate the corresponding residue class
	if (big_uint_cmp(res, p) > 0) {
		big_uint_add(res, res, p);
		return;
	}

	big_uint_add(res, res, &ZERO);
}

/* Performs Barrett reduction and populates the given mod_t struct */
void _barrett_reduction(mod_t *res) {
	uint32_t k = big_uint_log2(res->p, LOG_2_LIMB) + 1;
	res->k = k;

	big_uint_t temp, quo;
	big_uint_create(&temp, 2 * k + 1);
	big_uint_create(&quo, 2 * k + 1);

	temp.arr[2 * k] = 1;

	big_uint_div(&quo, NULL, &temp, res->p);
	big_uint_copy(res->r, &quo);
}

void mod_init(mod_t *res, const big_uint_t *p, big_uint_t *r) {
	res->p = p;
	res->r = r;

	_barrett_reduction(res);
}

void mod_mult(big_uint_t *res, const big_uint_t *a, const big_uint_t *b, const mod_t *mod) {
	// totla number of limbs in any intermediate product
	uint32_t prod_len = 
		2 * (a->len > b->len ? a->len : b->len) + 
		mod->r->len + 
		mod->p->len;
	
	// create var to hold intermediate product
	big_uint_t x, temp;
	big_uint_create(&x, prod_len);
	big_uint_create(&temp, prod_len);

	big_uint_mult(&x, a, b);
	big_uint_mult(&temp, &x, mod->r);
	big_uint_shr(&temp, &temp, 2 * mod->k, LOG_2_LIMB);
	big_uint_mult(&temp, &temp, mod->p);
	big_uint_sub(&x, &x, &temp);

	if (big_uint_cmp(&x, mod->p) > 0)
		big_uint_sub(&x, &x, mod->p);

	big_uint_copy(res, &x);
}
