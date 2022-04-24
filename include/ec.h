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

#ifndef EC_H
#define EC_H

#include "big-uint.h"
#include "mod.h"
#include "point.h"

typedef struct {
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

#endif
