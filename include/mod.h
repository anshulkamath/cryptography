/**
 * @file mod.h
 * @author Anshul Kamath
 * @brief A modular arithmetic library
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MOD_H
#define MOD_H

#include "big-uint.h"
#include <stdint.h>

/**
 * @brief Takes in a big integer `x` and puts `x mod p` into res
 * 
 * @param res Where to store the resulting mod
 * @param x   Pointer to the integer to mod
 * @param p   Pointer to the prime to mod by
 */
void mod_big_uint(big_uint_t *res, const big_uint_t *x, const big_uint_t *p);

/**
 * @brief Takes in big integers `a` and `b` and stores `a + b mod p` in `res`
 * 
 * @param res Where to store the sum
 * @param a   Pointer to the first big int to add
 * @param b   Pointer to the second big int to add
 * @param p   Pointer to the prime to mod by
 */
void mod_add(big_uint_t *res, const big_uint_t *a, const big_uint_t *b, const big_uint_t *p);

#endif
