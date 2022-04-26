#include "ecdsa.h"

#include "big-uint.h"
#include "mod.h"
#include "point.h"
#include "ec.h"

#include <stdio.h>
#include <string.h>

void ecdsa_sign(point_t *res, const big_uint_t *m_hash, const big_uint_t *pr_key, const ec_t *ec) {
    uint32_t l_p = big_uint_log2(ec->mod_p->p, LOG_2_BIT) + 1;
    uint32_t l_m = big_uint_log2(m_hash, LOG_2_BIT) + 1;
    const uint32_t SIZE = ec->mod_p->p->len;

    big_uint_t z;
    big_uint_create(&z, SIZE);
    assert(l_m >= l_p);
    big_uint_shr(&z, m_hash, l_m - l_p, SHIFT_BIT);

    big_uint_t *r = NULL;
    big_uint_t s, temp;
    big_uint_create(&temp, SIZE);
    big_uint_create(&s, SIZE);

    // create an intermediate buffer for k (the private key)
    big_uint_t k;
    big_uint_create(&k, SIZE);

    point_t temp_pt;
    point_create(&temp_pt, SIZE);

    while ((r == NULL || big_uint_is_zero(r)) || big_uint_is_zero(&s)) {
        // generate a cryptographically secure k
        big_uint_rand(&k);

        // r = [kG]_x
        ec_mult(&temp_pt, &k, ec->g, ec);
        r = temp_pt.x;

        // s = (z + r * pr_key) % n
        mod_mult(&s, r, pr_key, ec->mod_n);
        mod_add(&s, &s, &z, ec->mod_n);

        // s = k^{-1} * s
        mod_inv(&temp, &k, ec->mod_n);
        mod_mult(&s, &s, &temp, ec->mod_n);
    }

    point_t res_int;
    point_init(&res_int, r, &s);
    point_copy(res, &res_int);    
}
