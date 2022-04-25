// this file contains parameters for secp256k1 elliptic curve
#include <stdint.h>
#include "point.h"

const uint32_t SECP256K1_SIZE = 8;

// initializing global variables for curve secp256k1
const char *SECP256K1_P =
    "0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f";

const char *SECP256K1_A =
    "0x0000000000000000000000000000000000000000000000000000000000000000";

const char *SECP256K1_B =
    "0x0000000000000000000000000000000000000000000000000000000000000007";

const char *SECP256K1_X =
    "0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798";

const char *SECP256K1_Y =
    "0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8";

const char *SECP256K1_N =
    "0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141";
