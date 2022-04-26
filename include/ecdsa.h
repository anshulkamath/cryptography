/**
 * @file ecdsa.h
 * @author Anshul Kamath
 * @brief Implementation of ECDSA using our libraries
 * @version 0.1
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ECDSA_H
#define ECDSA_H

#include "big-uint.h"
#include "mod.h"
#include "point.h"
#include "ec.h"

/**
 * @brief Signs a given hashed message `m_hash` using the given private key and elliptic curve
 * 
 * @param res    Where to store the resulting point
 * @param m_hash The hashed message to sign
 * @param pr_key The private key used to encrypt the message
 * @param ec     The elliptic curve instance to use
 */
void ecdsa_sign(point_t *res, const big_uint_t *m_hash, const big_uint_t *pr_key, const ec_t *ec);

#endif
