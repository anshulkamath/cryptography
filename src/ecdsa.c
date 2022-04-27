#include "ecdsa.h"

#include "big-uint.h"
#include "mod.h"
#include "point.h"
#include "ec.h"

#include <stdio.h>
#include <string.h>

void ecdsa_sign(point_t *res, const big_uint_t *m_hash, const big_uint_t *pr_key, const ec_t *ec) {
    const uint32_t SIZE = ec->mod_p->p->len;
    uint32_t l_p = big_uint_log2(ec->mod_p->p, LOG_2_BIT) + 1;
    uint32_t l_m = big_uint_log2(m_hash, LOG_2_BIT) + 1;

    big_uint_t z;
    big_uint_create(&z, SIZE);
    assert(l_m >= l_p);
    big_uint_shr(&z, m_hash, l_m - l_p, SHIFT_BIT);

    big_uint_t *r = NULL;
    big_uint_t s, temp;
    big_uint_create(&temp, SIZE);
    big_uint_create(&s, SIZE);

    // create an intermediate buffer for k
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

uint32_t ecdsa_verify(const point_t *signature, const big_uint_t *m_hash, const point_t *pu_key, const ec_t *ec) {
    if (point_is_identity(pu_key) || !ec_is_on_curve(pu_key, ec))
        return 0;

    const big_uint_t *n = ec->mod_n->p;
    
    point_t temp1, temp2;
    point_create(&temp1, pu_key->x->len);
    point_create(&temp2, pu_key->x->len);
    ec_mult(&temp1, n, pu_key, ec);

    // if the public key is not in the subgroup
    if (!point_is_identity(&temp1))
        return 0;

    big_uint_t *r = signature->x, *s = signature->y;
    if (big_uint_cmp(r, n) > 0 ||
        big_uint_cmp(s, n) > 0 ||
        big_uint_is_zero(r) ||
        big_uint_is_zero(s)
    ) return 0;

    const uint32_t SIZE = ec->mod_p->p->len;
    uint32_t l_p = big_uint_log2(ec->mod_p->p, LOG_2_BIT) + 1;
    uint32_t l_m = big_uint_log2(m_hash, LOG_2_BIT) + 1;

    big_uint_t z;
    big_uint_create(&z, SIZE);
    assert(l_m >= l_p);
    big_uint_shr(&z, m_hash, l_m - l_p, SHIFT_BIT);

    big_uint_t s_inv, u1, u2;
    big_uint_create(&s_inv, s->len);
    big_uint_create(&u1, s->len);
    big_uint_create(&u2, s->len);

    mod_inv(&s_inv, s, ec->mod_n);
    mod_mult(&u1, &z, &s_inv, ec->mod_n);
    mod_mult(&u2, r, &s_inv, ec->mod_n);

    ec_mult(&temp1, &u1, ec->g, ec);
    ec_mult(&temp2, &u2, pu_key, ec);
    ec_add(&temp1, &temp1, &temp2, ec);

    if (point_is_identity(&temp1)) return 0;

    return big_uint_equals(r, temp1.x);
}
