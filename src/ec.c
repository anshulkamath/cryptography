#include "ec.h"

#include "big-uint.h"
#include "mod.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

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

void ec_mult(point_t *res, const big_uint_t *k, const point_t *pt, const ec_t *ec) {
    point_t res_int;
    point_create(&res_int, res->x->len);
    point_copy(&res_int, point_get_identity());
    
    for (int32_t i = k->len - 1; i >= 0; i--) {
        for (int32_t j = UINT_BITS - 1; j >= 0; --j) {
            // double the point each iteration
            ec_add(&res_int, &res_int, &res_int, ec);

            // if the bit is set here, add the point
            if ((k->arr[i] >> j) & 1)
                ec_add(&res_int, &res_int, pt, ec);
        }
    }

    point_copy(res, &res_int);
}

void ec_keygen(point_t *pu_key, big_uint_t *pr_key, const ec_t *ec) {
    #if DEBUG
    // FOR DEBUGGING PURPOSES ONLY:
    srand(1);
    #endif

    const uint16_t SIZE = pr_key->len;
    const uint16_t BYTES_PER_UINT = 8;
    
    // use /dev/urandom to generate cryptographically-secure, random numbers
    FILE *file = fopen("/dev/urandom", "r");

    if (file == NULL) {
        fprintf(stderr, "Error while opening /dev/urandom");
        return;
    }

    // create an intermediate buffer for k (the private key)
    uint32_t k_arr[SIZE];

    for (uint32_t i = 0; i < SIZE; i++) {
        #if DEBUG
        k_arr[i] = (rand() & 0xff) << 24 | (rand() & 0xff) << 16 | (rand() & 0xff) << 8 | (rand() & 0xff);
        #else
        if (fread(&k_arr[i], sizeof(uint32_t), 1, file) != 1) {
            fprintf(stderr, "Error while generating random private key.\n");
            return;
        }
        #endif
    }

    // copy the randomly generated integer to the private key
    big_uint_t k;
    big_uint_init(&k, k_arr, SIZE);
    mod_sub(pr_key, &k, big_uint_get_zero(), ec->mod_p);
    
    // generate the public key using the private key
    ec_mult(pu_key, pr_key, ec->g, ec);
}
