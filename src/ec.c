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

uint8_t ec_is_inv(const ec_t *ec, const point_t *p1, const point_t *p2) {
    point_t exp_p2;
    point_copy(&exp_p2, p1);

    mod_neg(exp_p2.y, p1->y, ec->mod_p);
    return point_equals(&exp_p2, p2);
}
