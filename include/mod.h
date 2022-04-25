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

/****************************************/
/*            HELPER MACROS             */
/****************************************/

#define _MOD_HELPER_1(dest, p, count) \
    _MOD_HELPER_2(dest, p, CONCAT(_r, count));

#define _MOD_HELPER_2(dest, p, r_id) \
    big_uint_t r_id; \
    big_uint_create(&r_id, (big_uint_log2(p, LOG_2_LIMB) + 1) + 1); \
    mod_init(dest, p, &r_id);

#define _MOD_HELPER_3(res, num, imm, mod, func, count) \
    _MOD_HELPER_4(res, num, imm, mod, func, CONCAT(_imm, count))

#define _MOD_HELPER_4(res, num, imm, mod, func, imm_id) \
    big_uint_t imm_id; \
    big_uint_loadi(&imm_id, imm, 1); \
    func(res, num, &imm_id, mod);

/****************************************/
/*               MACROS                 */
/****************************************/

#define mod_create(dest, p) \
    _MOD_HELPER_1(dest, p, __COUNTER__)

#define mod_addi(res, num, imm, mod) \
    _MOD_HELPER_3(res, num, imm, mod, mod_add, __COUNTER__)

#define mod_subi(res, num, imm, mod) \
    _MOD_HELPER_3(res, num, imm, mod, mod_sub, __COUNTER__)

#define mod_multi(res, num, imm, mod) \
    _MOD_HELPER_3(res, num, imm, mod, mod_mult, __COUNTER__)

#define mod_expi(res, num, imm, mod) \
    _MOD_HELPER_3(res, num, imm, mod, mod_exp, __COUNTER__)

/****************************************/
/*              INTERFACE               */
/****************************************/

typedef struct mod {
    const big_uint_t *p;  // pointer to the prime number
    big_uint_t *r;        // r-value in barrett reduction
    uint32_t    k;        // k-value in barrett reduction
} mod_t;

/****************************************/
/*                STUBS                 */
/****************************************/

/**
 * @brief Creates a mod type with the precomputed factor `r` using Barrett Reduction
 * 
 * @param res Where to store the resulting mod type
 * @param p   Pointer to the prime `p`
 * @param r   Pointer to the precomputed factor `r`
 */
void mod_init(mod_t *res, const big_uint_t *p, big_uint_t *r);

/**
 * @brief Returns true if and only if the two mod types are equal
 * 
 * @param m1 Pointer to the first mod type to compare
 * @param m2 Pointer to the second mod type to compare
 * @return uint8_t 
 */
uint8_t mod_equals(const mod_t *m1, const mod_t *m2);

/**
 * @brief Takes in a big integer `x` and puts `x mod p` into res
 * 
 * @param res Where to store the resulting mod
 * @param x   Pointer to the integer to mod
 * @param mod Pointer to the mod struct with the prime to mod by
 */
void mod_big_uint(big_uint_t *res, const big_uint_t *x, const mod_t *mod);

/**
 * @brief Takes in big integers `a` and `b` and stores `a + b mod p` in `res`
 * 
 * @param res Where to store the sum
 * @param a   Pointer to the first big int to add
 * @param b   Pointer to the second big int to add
 * @param mod Pointer to the mod struct with the prime to mod by
 */
void mod_add(big_uint_t *res, const big_uint_t *a, const big_uint_t *b, const mod_t *mod);

/**
 * @brief Takes in big integers `a` and `b` and stores `a - b mod p` in `res`
 * 
 * @param res Where to store the difference
 * @param a   Pointer to the first big int to from
 * @param b   Pointer to the second big int to subtract
 * @param mod Pointer to the mod struct with the prime to mod by
 */
void mod_sub(big_uint_t *res, const big_uint_t *a, const big_uint_t *b, const mod_t *mod);

/**
 * @brief Computes `a * b mod p` and stores the result in `res`
 * 
 * @param res Where to store the resulting product
 * @param a   Pointer to the first number to multiply
 * @param b   Pointer to the second number to multiply
 * @param mod Pointer to the mod type that contains the Barrett precomputed factor for `p`
 */
void mod_mult(big_uint_t *res, const big_uint_t *a, const big_uint_t *b, const mod_t *mod);

/**
 * @brief Computes `x^n (mod p)` and stores the result in `res`
 * 
 * @param res Where to store the resulting exponent
 * @param x   Pointer to the base of the exponent
 * @param n   Pointer to the power by which to raise the base
 * @param mod Pointer to the mod type that contains the Barrett precomputed factor for `p`
 */
void mod_exp(big_uint_t *res, const big_uint_t *x, const big_uint_t *n, const mod_t *mod);

/**
 * @brief Computes `x^{-1} (mod p)` and stores the result in `res.`
 *        Does so using the special case of Euler's Theorem (Fermat's Little Theorem),
 *        which states that
 *                 a^p = a (mod p)   and implies   a^{p-2} = a^{-1} (mod p)
 * 
 * @param res Where to store the resulting exponent
 * @param x   Pointer to the base of the exponent (the number we are trying to invert)
 * @param mod Pointer to the mod type that contains the Barrett precomputed factor for `p`
 */
void mod_inv(big_uint_t *res, const big_uint_t *x, const mod_t *mod);

/**
 * @brief Computes the additive inverse `-x (mod p)` and stores the result in `res.`
 * 
 * @param res Where to store the resulting pointer
 * @param x   Pointer to the number we are trying to find the additive inverse of
 * @param mod Pointer to the mod type that contains the Barrett precomputed factor for `p`
 */
void mod_neg(big_uint_t *res, const big_uint_t *x, const mod_t *mod);

/**
 * @brief Computes the modular square root `res^2 = x (mod p)` and stores the result in `res.`
 * 
 * @param res Where to store the resulting pointer
 * @param x   Pointer to the number we are trying to find the square root of
 * @param mod Pointer to the mod type that contains the Barrett precomputed factor for `p`
 */
void mod_sqrt(big_uint_t *res, const big_uint_t *x, const mod_t *mod);

#endif
