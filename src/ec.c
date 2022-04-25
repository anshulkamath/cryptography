#include "ec.h"

#include "big-uint.h"
#include "mod.h"
#include <string.h>

void ec_init(ec_t *dest, const big_uint_t *a, const big_uint_t *b, const mod_t *mod_p, const mod_t *mod_n, const point_t *g) {
    dest->a = a;
    dest->b = b;
    dest->mod_p = mod_p;
    dest->mod_n = mod_n;
    dest->g = g;
}

uint8_t ec_is_inv(const point_t *p1, const point_t *p2, const ec_t *ec) {
    point_t exp_p2;
    point_copyi(&exp_p2, p1);

    mod_neg(exp_p2.y, p1->y, ec->mod_p);
    return point_equals(&exp_p2, p2);
}

void ec_add(point_t *res, const point_t *p1, const point_t *p2, const ec_t *ec) {
    // if either coordinate is 0, return the other
    if (point_is_identity(p1)) {
        point_copy(res, p2);
        return;
    }

    if (point_is_identity(p2)) {
        point_copy(res, p1);
        return;
    }

    // if the coordinate are additive inverses, return identity
    if (ec_is_inv(p1, p2, ec)) {
        point_copy(res, point_get_identity());
        return;
    }

    // calculate sum
    const mod_t *mod = ec->mod_p;

    big_uint_t lambda, x, y, temp1, temp2;
    big_uint_create(&lambda, mod->p->len);
    big_uint_create(&x, mod->p->len);
    big_uint_create(&y, mod->p->len);
    big_uint_create(&temp1, mod->p->len);
    big_uint_create(&temp2, mod->p->len);

    // if the points are equal, use the tangent line
    // otherwise, use the line between the points
    if (point_equals(p1, p2)) {
        // 3 * x1 * x1 + a
        mod_mult(&temp1, p1->x, p1->x, mod);
        mod_multi(&temp1, &temp1, 3, mod);
        mod_add(&temp1, &temp1, ec->a, mod);

        // (2 * y1)^{-1}
        mod_multi(&temp2, p1->y, 2, mod);
        mod_inv(&temp2, &temp2, mod);

        // lambda = (3 * x1 * x1 + a) / (2 * y1)
        mod_mult(&lambda, &temp1, &temp2, mod);
    } else {
        // (y2 - y1)
        mod_sub(&temp1, p2->y, p1->y, mod);

        // (x2 - x1)^{-1}
        mod_sub(&temp2, p2->x, p1->x, mod);
        mod_inv(&temp2, &temp2, mod);

        // lambda = (y2 - y1) / (x2 - x1)
        mod_mult(&lambda, &temp1, &temp2, mod);
    }

    // x = lambda^2 - x2 - x1
    mod_mult(&x, &lambda, &lambda, mod);
    mod_sub(&x, &x, p2->x, mod);
    mod_sub(&x, &x, p1->x, mod);

    // y = lambda * (x1 - x3) - y1
    mod_sub(&y, p1->x, &x, mod);
    mod_mult(&y, &lambda, &y, mod);
    mod_sub(&y, &y, p1->y, mod);

    // copy the point
    big_uint_copy(res->x, &x);
    big_uint_copy(res->y, &y);
}

