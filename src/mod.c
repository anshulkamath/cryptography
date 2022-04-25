#include "mod.h"
#include "big-uint.h"

#include <assert.h>
#include <stdint.h>
#include <string.h>

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

uint8_t mod_equals(const mod_t *m1, const mod_t *m2) {
	return 
		big_uint_equals(m1->p, m2->p) && 
		big_uint_equals(m1->r, m2->r) && 
		m1->k == m2->k;
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
	
	big_uint_sub(res, res, big_uint_get_zero());
}

void mod_sub(big_uint_t *res, const big_uint_t *a, const big_uint_t *b, const mod_t *mod) {
	big_uint_sub(res, a, b);

	// if we are above the prime, calculate the corresponding residue class
	if (big_uint_cmp(res, mod->p) > 0) {
		big_uint_add(res, res, mod->p);
		return;
	}

	big_uint_add(res, res, big_uint_get_zero());
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
	big_uint_sub(res, mod->p, x);
}

static uint8_t _check_euler_criterion(const big_uint_t *x, const mod_t *mod) {
	big_uint_t x_i, p_i, one;
	big_uint_create(&x_i, x->len);
	big_uint_create(&p_i, mod->p->len);
	big_uint_loadi(&one, 1, mod->p->len);

	// (p - 1) // 2
	big_uint_subi(&p_i, mod->p, 1);
	big_uint_shr(&p_i, &p_i, 1, LOG_2_BIT);

	// x^{(p - 1) // 2}
	mod_exp(&x_i, x, &p_i, mod);

	return big_uint_equals(&p_i, &one);
}

static void _simple_sqrt_case(big_uint_t *res, const big_uint_t *x, const mod_t *mod) {
	big_uint_t p_i;
	big_uint_create(&p_i, mod->p->len);

	// (p + 1) // 4
	big_uint_addi(&p_i, mod->p, 1);
	big_uint_shr(&p_i, &p_i, 2, LOG_2_BIT);

	// x^{(p + 1) // 4}
	mod_exp(res, x, &p_i, mod);
}

/* returns the 0-indexed position of the first significant bit of x */
/* example: f(0b0110101101000) = 3 */
static uint32_t _get_first_sig_bit(big_uint_t *res) {
	assert(!big_uint_is_zero(res));
	
	for (uint32_t i = 0; i < res->len; i++) {
		if (res->arr[i] == 0) continue;

		for (int32_t j = 0; j < UINT_BITS; j++) {
			if ((res->arr[i] >> j) & 1)
				return i * UINT_BITS + j;
		}
	}

	return UINT_BITS * res->len;
}

void mod_sqrt(big_uint_t *res, const big_uint_t *n, const mod_t *mod) {
	big_uint_t one;
	big_uint_loadi(&one, 1, mod->p->len);

	big_uint_t two;
	big_uint_loadi(&two, 2, mod->p->len);

	// check simple cases
	if (_check_euler_criterion(n, mod)) {
		big_uint_copy(res, big_uint_get_zero());
		return;
	}
	else if (big_uint_is_zero(n)) {
		big_uint_copy(res, big_uint_get_zero());
		return;
	}
	else if (big_uint_equals(mod->p, &two)) {
		big_uint_copy(res, mod->p);
		return;
	}
	else if (mod->p->arr[0] % 4 == 3) {
		_simple_sqrt_case(res, n, mod);
		return;
	}

	// store p - 1
	big_uint_t p_i, q;
	big_uint_create(&q, mod->p->len);
	big_uint_create(&p_i, mod->p->len);
	big_uint_subi(&p_i, mod->p, 1);

	// calculate `(p - 1) = Q * 2^s = Q << s`
	uint32_t s = _get_first_sig_bit(&p_i);
	big_uint_shr(&q, &p_i, s, LOG_2_BIT);

	// find the square root of n
	big_uint_t a;
	big_uint_loadi(&a, 2, 1);
	while (_check_euler_criterion(&a, mod))	++a.arr[0];	// TODO: this may need to be updated

	// defining variables for loop
	big_uint_t x, t, b, g, temp;
	uint32_t r, m;
	big_uint_create(&x, mod->p->len);
	big_uint_create(&t, mod->p->len);
	big_uint_create(&b, mod->p->len);
	big_uint_create(&g, mod->p->len);
	big_uint_create(&temp, mod->p->len);

	big_uint_addi(&temp, &q, 1);
	big_uint_shr(&temp, &temp, 1, LOG_2_BIT);
	
	// initializing variables
	mod_exp(&x, n, &temp, mod);
	mod_exp(&b, n, &q, mod);
	mod_exp(&g, &a, &q, mod);
	r = s;

	while (1) {
		big_uint_copy(&t, &b);

		for (m = 0; m < r; m++) {
			// no solution exists
			if (big_uint_equals(&t, &one))
				break;
			
			mod_mult(&t, &t, &t, mod);
		}

		// if m == 0, then copy the x (the solution) to result
		if (m == 0) {
			big_uint_copy(res, &x);
			return;
		}

		// update variables for next loop iteration
		big_uint_shl(&temp, &one, r - m - 1, LOG_2_BIT);
		mod_exp(&temp, &g, &temp, mod);		
		mod_mult(&g, &temp, &temp, mod);
		mod_mult(&x, &x, &temp, mod);
		mod_mult(&b, &b, &g, mod);
		r = m;
	}

	// if we break, then reset res
	big_uint_create(res, res->len);
}
