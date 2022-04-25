#include "ec.h"

#include "big-uint.h"
#include "mod.h"

void ec_init(ec_t *dest, const big_uint_t *a, const big_uint_t *b, const mod_t *mod_p, const mod_t *mod_n, const point_t *g) {
    dest->a = a;
    dest->b = b;
    dest->mod_p = mod_p;
    dest->mod_n = mod_n;
    dest->g = g;
}
