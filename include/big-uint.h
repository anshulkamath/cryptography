/**
 * Welcome to the anshulkamath's big unsigned integer library!
 * This file includes the definitions for our library, but here are some
 * important notes:
 *   - this library is written in little endian (big endian support tbd)
 *   - we use the term `limbs` to refer to the number of digits in a big uint
 *   - all operations are constant time with respect to the number of limbs
 */

#ifndef BIG_UINT_H
#define BIG_UINT_H

#include <stdint.h>

// Macros

/**
 * @brief Loads a given big uint with the number given by the string
 *        representation `num`
 * 
 * @param dest  The destination big uint
 * @param num   The (hex) string representation of the number to load
 */
#define big_uint_load(dest, num) _BU_HELPER_1(dest, num, __COUNTER__)

#define _BU_HELPER_1(dest, num, count) \
    _BU_HELPER_2(dest, num, CONCAT(_rsize, count), CONCAT(_rarr, count))

#define _BU_HELPER_2(dest, num, s_id, a_id)  \
    uint64_t s_id = big_uint_count_limbs(num); \
    uint32_t a_id[s_id]; \
    big_uint_parse(a_id, num, s_id); \
    big_uint_init(dest, a_id, s_id);

#define CONCAT(a, b) a ## b

// alias for big_uint_print_helper to allow passing of literal big_uint_t
#define big_uint_print(x) big_uint_print_helper(&x)

// Interface

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

/**
 * @brief Given a (hex) string representation of a big uint, returns the number
 *        of limbs needed to represent it. Includes all leading 0s.
 * 
 * TODO: Extend functionality to base 2, 8, 10
 * 
 * @param num A string of the number
 * @return uint64_t 
 */
uint64_t big_uint_count_limbs(const char *num);

/**
 * @brief Creates an array of uint32_ts from a (hex) string representation
 * 
 * @param dest  Where to store the resulting big uint
 * @param arr   Where to store our big integer
 * @param num   A string that represents our big integer
 * @param len   The number of limbs in our big integer
 */
void big_uint_parse(uint32_t *dest, const char *num, uint64_t len);

/**
 * @brief Writes the hex representation of the given value to the given char*
 * 
 * @param dest  Where to store the string representation
 * @param value A pointer to the big-uint
 */
void big_uint_sprint(char *dest, const big_uint_t *value);

/**
 * @brief Prints out the hex representation of the big integer in big endian.
 * NOTE:  Prefer calling big_uint_print() instead of this function
 * TODO:  Add support for little endianness
 * 
 * @param value The big integer to print
 */
void big_uint_print_helper(const big_uint_t *value);

/**
 * @brief Returns true if and only if the two big uints are equal
 * 
 * @param a Pointer to the first big uint to compare
 * @param b Pointer to the second big uint to compare
 * @return int
 */
uint8_t big_uint_equals(const big_uint_t *a, const big_uint_t *b);

#endif
