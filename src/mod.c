#include "mod.h"
#include "big-uint.h"

#include <stdint.h>
#include <string.h>

// constant zero
uint32_t ZERO_ARR[] = { 0 };
big_uint_t ZERO = { .arr = (uint32_t *) &ZERO_ARR, .len = 1 };

/* Performs Barrett reduction and populates the given mod_t struct */
void _barrett_reduction(mod_t *res) {
	uint32_t k = big_uint_log2(res->p, LOG_2_LIMB) + 1;
	res->k = k;

	big_uint_t temp, quo;
	big_uint_create(&temp, 2 * k + 1);
	big_uint_create(&quo, 2 * k + 1);

	temp.arr[2 * k] = 1;

	big_uint_div(res->r, NULL, &temp, res->p);
}

void mod_init(mod_t *res, const big_uint_t *p, big_uint_t *r) {
	res->p = p;
	res->r = r;

	_barrett_reduction(res);
}

void mod_big_uint(big_uint_t *res, const big_uint_t *x, const mod_t *mod) {
	big_uint_t q;
	big_uint_create(&q, x->len);

	big_uint_div(&q, res, x, mod->p);
}

void mod_add(big_uint_t *res, const big_uint_t *a, const big_uint_t *b, const mod_t *mod) {
	big_uint_add(res, a, b);

	// if we are above the prime, calculate the corresponding residue class
	if (big_uint_cmp(res, mod->p) > 0) {
		big_uint_sub(res, res, mod->p);
		return;
	}
	
	big_uint_sub(res, res, &ZERO);
}

void mod_sub(big_uint_t *res, const big_uint_t *a, const big_uint_t *b, const mod_t *mod) {
	big_uint_sub(res, a, b);

	// if we are above the prime, calculate the corresponding residue class
	if (big_uint_cmp(res, mod->p) > 0) {
		big_uint_add(res, res, mod->p);
		return;
	}

	big_uint_add(res, res, &ZERO);
}

void mod_mult(big_uint_t *res, const big_uint_t *a, const big_uint_t *b, const mod_t *mod) {
	// create var to hold intermediate product
	big_uint_t x, temp;
	big_uint_create(&x, 2 * mod->k);
	big_uint_create(&temp, 3 * mod->k + 1);

	// calculate t = x - floor(xr / p) * p
	big_uint_mult(&x, a, b);
	big_uint_mult(&temp, &x, mod->r);
	big_uint_shr(&temp, &temp, 2 * mod->k, LOG_2_LIMB);
	big_uint_mult(&temp, &temp, mod->p);
	big_uint_sub(res, &x, &temp);
	
	// subtract mod->p from res iff res > mod->p
	big_uint_choose(&temp, mod->p, big_uint_cmp(res, mod->p) > 0);
	big_uint_sub(res, res, &temp);
}
