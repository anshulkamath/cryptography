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

void mod_mult_bench(big_uint_t *res, const big_uint_t *a, const big_uint_t *b, const mod_t *mod, time_t arr[7]) {
	// create var to hold intermediate product
	big_uint_t x, temp1, temp2, temp3;
	big_uint_create(&x, 2 * mod->k);
	big_uint_create(&temp1, 3 * mod->k + 1);
	big_uint_create(&temp2, mod->k + 1);
	big_uint_create(&temp3, 2 * mod->k + 1);

	// benchmarking vars
	time_t start;

	// calculate res = x - floor(xr / p) * p
	start = clock();
	big_uint_mult(&x, a, b);
	arr[0] += clock() - start;

	start = clock();
	big_uint_mult(&temp1, &x, mod->r);
	arr[1] += clock() - start;

	start = clock();
	big_uint_shr(&temp2, &temp1, 2 * mod->k, LOG_2_LIMB);
	arr[2] += clock() - start;

	start = clock();
	big_uint_mult(&temp3, &temp2, mod->p);
	arr[3] += clock() - start;

	start = clock();
	big_uint_sub(res, &x, &temp3);
	arr[4] += clock() - start;
	
	// subtract mod->p from res iff res > mod->p
	start = clock();
	big_uint_choose(&temp3, mod->p, big_uint_cmp(res, mod->p) > 0);
	arr[5] += clock() - start;

	start = clock();
	big_uint_sub(res, res, &temp3);
	arr[6] += clock() - start;
}
