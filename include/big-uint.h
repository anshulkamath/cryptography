#ifndef BIG_UINT_H
#define BIG_UINT_H

#include <stdint.h>

/**
 * Welcome to the anshulkamath's big unsigned integer library!
 * This file includes the definitions for our library, but here are some
 * important notes:
 *   - this library is written in little endian (big endian support tbd)
 *   - we use the term `limbs` to refer to the number of digits in a big uint
 *   - all operations are constant time with respect to the number of limbs
 */

typedef struct big_uint_t {
    uint32_t   *arr;  // a pointer to the big integer
    uint64_t    len;  // the number of limbs in the big integer
} big_uint_t;

/**
 * @brief Initializes a big uint from an array and a length, storing the big uint
 *        in the provided big_uint_t
 * 
 * @param dest Where to store the big uint
 * @param arr  The address of the big uint
 * @param len  The number of limbs in our big uint
 */
void big_uint_init(big_uint_t *dest, uint32_t *arr, uint64_t len);


#endif
