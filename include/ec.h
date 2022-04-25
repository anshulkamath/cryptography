/**
 * @file ec.h
 * @author Anshul Kamath
 * @brief Library for (Weierstrauss) elliptic curves
 * @version 0.1
 * @date 2022-04-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * This file contains an implementation of the Weierstrauss elliptic curve.
 * The equation of this curve is given by:
 *      { (x, y) \in F_q^2 | y^2 = x^3 + ax + b mod q, 4a^3 + 27b^2 != 0 }
 * 
 * We have pre-defined the following curves, which can be instantiated using
 * the ec_create macro:
 *  - secp256k1
 */

#ifndef EC_H
#define EC_H

#include "big-uint.h"
#include "mod.h"
#include "point.h"

/****************************************/
/*            HELPER MACROS             */
/****************************************/

#define _EC_HELPER_1(dest, curve) \
    _EC_HELPER_2(dest, \
        CONCAT(curve, _A), CONCAT(curve, _B), \
        CONCAT(curve, _P), CONCAT(curve, _N), \
        CONCAT(curve, _X), CONCAT(curve, _Y),\
        __COUNTER__ \
    )

#define _EC_HELPER_2(dest, a_var, b_var, p_var, n_var, x_var, y_var, count) \
    _EC_HELPER_3(dest, \
        CONCAT(_ec_a, count), a_var, \
        CONCAT(_ec_b, count), b_var, \
        CONCAT(_ec_mod_p, count), CONCAT(_ec_p, count), p_var, \
        CONCAT(_ec_mod_n, count), CONCAT(_ec_n, count), n_var, \
        CONCAT(_ec_pt, count), x_var, y_var \
    )

#define _EC_HELPER_3(dest, a_id, a_var, b_id, b_var, p_id, p_iid, p_var, n_id, n_iid, n_var, g_id, x_var, y_var) \
    big_uint_t a_id, b_id, p_iid, n_iid; \
    mod_t p_id, n_id; \
    point_t g_id; \
    big_uint_load(&a_id, a_var); \
    big_uint_load(&b_id, b_var); \
    big_uint_load(&p_iid, p_var); \
    big_uint_load(&n_iid, n_var); \
    mod_create(&p_id, &p_iid); \
    mod_create(&n_id, &n_iid); \
    point_create(&g_id, x_var, y_var); \
    ec_init(dest, &a_id, &b_id, &p_id, &n_id, &g_id);

/****************************************/
/*            INIT FUNCTIONS            */
/****************************************/

#define ec_create(dest, curve) \
    _EC_HELPER_1(dest, curve)

/****************************************/
/*              CONSTANTS               */
/****************************************/

#define SECP256k1       _SECP256k1  // prefix of constants in file
#define SECP256k1_SIZE           8  // number of limbs in constants

/****************************************/
/*              INTERFACE               */
/****************************************/

typedef struct ec {
    const big_uint_t *a;  // curve parameter a
    const big_uint_t *b;  // curve parameter b
    const mod_t  *mod_p;  // prime of the finite field
    const mod_t  *mod_n;  // order of the generator point
    const point_t    *g;  // generator point
} ec_t;

/**
 * @brief Initializes an elliptic curve using the given parameters
 * 
 * @param dest  Where to store the elliptic curve
 * @param a     Pointer to the curve parameter a
 * @param b     Pointer to the curve parameter b
 * @param mod_p Pointer to the mod type of the curve prime p
 * @param mod_n Pointer to the mod type of the curve's generator point order `n`
 * @param g     Pointer to the generator point of the curve `g`
 */
void ec_init(ec_t *dest, const big_uint_t *a, const big_uint_t *b, const mod_t *mod_p, const mod_t *mod_n, const point_t *g);

/**
 * @brief Returns true if and only if p1 and p2 are inverses on the given curve
 * 
 * @param ec The curve to use to determine if p1 and p2 are inverses
 * @param p1 The first point to compare
 * @param p2 The second point to compare
 * @return uint8_t 
 */
uint8_t ec_is_inv(const point_t *p1, const point_t *p2, const ec_t *ec);

#endif
