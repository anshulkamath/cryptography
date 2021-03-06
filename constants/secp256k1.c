#ifndef SECP256K1_CONSTANTS
#define SECP256K1_CONSTANTS

// this file contains parameters for secp256k1 elliptic curve
#include <stdint.h>

// initializing global variables for curve secp256k1
static const char *_SECP256k1_P =
    "0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f";

static const char *_SECP256k1_A =
    "0x0000000000000000000000000000000000000000000000000000000000000000";

static const char *_SECP256k1_B =
    "0x0000000000000000000000000000000000000000000000000000000000000007";

static const char *_SECP256k1_X =
    "0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798";

static const char *_SECP256k1_Y =
    "0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8";

static const char *_SECP256k1_N =
    "0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141";

#endif
