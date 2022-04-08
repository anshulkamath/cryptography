#include "mod.h"
#include "big-uint.h"

#include <stdint.h>
#include <string.h>

void mod_big_uint(big_uint_t *res, const big_uint_t *x, const big_uint_t *p) {
	big_uint_t q;
	big_uint_create(&q, x->len);

	big_uint_div(&q, res, x, p);
}
