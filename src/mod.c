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
	big_uint_t x, temp1, temp2, temp3;
	big_uint_create(&x, 2 * mod->k);
	big_uint_create(&temp1, 3 * mod->k + 1);
	big_uint_create(&temp2, mod->k + 1);
	big_uint_create(&temp3, 2 * mod->k + 1);

	// calculate res = x - floor(xr / p) * p
	big_uint_mult(&x, a, b);
	big_uint_mult(&temp1, &x, mod->r);
	big_uint_shr(&temp2, &temp1, 2 * mod->k, LOG_2_LIMB);
	big_uint_mult(&temp3, &temp2, mod->p);
	big_uint_sub(res, &x, &temp3);
	
	// subtract mod->p from res iff res > mod->p
	big_uint_choose(&temp3, mod->p, big_uint_cmp(res, mod->p) > 0);
	big_uint_sub(res, res, &temp3);
}

void mod_exp(big_uint_t *res, const big_uint_t *x, const big_uint_t *n, const mod_t *mod) {
	big_uint_t x_res;
	big_uint_loadi(&x_res, 1, res->len);

	// square and multiply method: represent the exponent as a bit string
	// use square to shift the exponent left, and multiply by x to add
	//	one to the exponent.
	for (int32_t i = n->len - 1; i >= 0; i--) {
		uint32_t curr = n->arr[i];
		for (int32_t j = UINT_BITS - 1; j >= 0; j--) {
			// square every iteration
			mod_mult(&x_res, &x_res, &x_res, mod);

			// if this bit of the exponent is set, then multiply by x
			// to `add one` to the exponent
			if ((curr >> j) & 1)
				mod_mult(&x_res, &x_res, x, mod);
		}
	}

	memcpy(res->arr, x_res.arr, res->len * UINT_SIZE);
}

void mod_inv(big_uint_t *res, const big_uint_t *x, const mod_t *mod) {
	// store p - 2
	big_uint_t p_prime;
	big_uint_create(&p_prime, mod->p->len);
	big_uint_copy(&p_prime, mod->p);
	big_uint_subi(&p_prime, &p_prime, 2);

	mod_exp(res, x, &p_prime, mod);
}

void mod_neg(big_uint_t *res, const big_uint_t *x, const mod_t *mod) {
	mod_sub(res, &ZERO, x, mod);
}
