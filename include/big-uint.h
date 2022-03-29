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

/****************************************/
/*            HELPER MACROS             */
/****************************************/

#define _BU_HELPER_1(dest, num, count) \
    _BU_HELPER_2(dest, num, CONCAT(_rsize, count), CONCAT(_rarr, count))

#define _BU_HELPER_2(dest, num, s_id, a_id)  \
    uint64_t s_id = big_uint_count_limbs(num); \
    uint32_t a_id[s_id]; \
    big_uint_parse(a_id, num, s_id); \
    big_uint_init(dest, a_id, s_id);

#define CONCAT(a, b) a ## b

/****************************************/
/*                MACROS                */
/****************************************/

/**
 * @brief Loads a given big uint with the number given by the string
 *        representation `num`
 * 
 * @param dest  The destination big uint
 * @param num   The (hex) string representation of the number to load
 */
#define big_uint_load(dest, num) _BU_HELPER_1(dest, num, __COUNTER__)

// alias for big_uint_print_helper to allow passing of literal big_uint_t
#define big_uint_print(x) big_uint_print_helper(&x)

/****************************************/
/*               CONSTANTS              */
/****************************************/

#define UINT_SIZE   sizeof(uint32_t)
#define UINT_BITS   32
#define D_UINT_SIZE sizeof(uint64_t)
#define D_UINT_BITS 64
#define SHIFT_BIT   0
#define SHIFT_LIMB  1

/****************************************/
/*              INTERFACE               */
/****************************************/

typedef struct big_uint_t {
    uint32_t   *arr;  // a pointer to the big integer
    uint64_t    len;  // the number of limbs in the big integer
} big_uint_t;

/****************************************/
/*       BIG UINT INITIALIZATION        */
/****************************************/

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

/****************************************/
/*           PRINT OPERATIONS           */
/****************************************/

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

/****************************************/
/*        COMPARISON OPERATIONS         */
/****************************************/

/**
 * @brief Returns true if and only if the two big uints are equal
 * 
 * @param a Pointer to the first big uint to compare
 * @param b Pointer to the second big uint to compare
 * @return int
 */
uint8_t big_uint_equals(const big_uint_t *a, const big_uint_t *b);

/**
 * @brief Computes a > b. Returns 1, 0, or -1 if a > b, a == b, or a < b,
 *        respectively
 * 
 * @param a Pointer to the first big uint to compare
 * @param b Pointer to the second big uint to compare
 * @return uint8_t 
 */
int8_t big_uint_cmp(const big_uint_t *a, const big_uint_t *b);

/**
 * @brief Returns a struct-copy of max(a, b).
 *        In the event of equality, defers to a.
 * 
 * @param a Pointer to the first big uint to compare
 * @param b Pointer to the second big uint to compare
 * @return uint8_t 
 */
big_uint_t big_uint_max(const big_uint_t *a, const big_uint_t *b);

/**
 * @brief Returns a struct-copy of min(a, b).
 *        In the event of equality, defers to a.
 * 
 * @param a Pointer to the first big uint to compare
 * @param b Pointer to the second big uint to compare
 * @return uint8_t 
 */
big_uint_t big_uint_min(const big_uint_t *a, const big_uint_t *b);

/****************************************/
/*          BITWISE OPERATIONS          */
/****************************************/

/**
 * @brief Performs a bitwise OR operation on `a` and `b` and stores the result in result
 * NOTE:  Big integer should already be initialized to use this function
 * 
 * @param res Where the result is stored
 * @param a   The first number to OR
 * @param b   The second number to OR
 */
void big_uint_or(big_uint_t *result, const big_uint_t *a, const big_uint_t *b);

/**
 * @brief Performs a bitwise AND operation on `a` and `b` and stores the result in result
 * NOTE:  Big integer should already be initialized to use this function
 * 
 * @param res Where the result is stored
 * @param a   The first number to AND
 * @param b   The second number to AND
 */
void big_uint_and(big_uint_t *result, const big_uint_t *a, const big_uint_t *b);

/**
 * @brief Performs a bitwise XOR operation on `a` and `b` and stores the result in result
 * NOTE:  Big integer should already be initialized to use this function
 * 
 * @param res Where the result is stored
 * @param a   The first number to XOR
 * @param b   The second number to XOR
 */
void big_uint_xor(big_uint_t *result, const big_uint_t *a, const big_uint_t *b);

/**
 * @brief Performs a right shift on the big uint `x` by `n.`
 *        Can either shift by limbs or bits (determined by shift_t argument)
 * 
 * @param result    Where to store the result of the shift
 * @param x         The big uinteger `x` to shift
 * @param n         The big uinteger `n` to shift by
 * @param shift_t   The type of shift (eitherr SHIFT_BIT [0] or SHIFT_LIMB [1])
 */
void big_uint_shr(big_uint_t *result, const big_uint_t *x, uint64_t n, uint8_t shift_t);

/**
 * @brief Performs a left shift on the big uint `x` by `n.`
 *        Can either shift by limbs or bits (determined by shift_t argument)
 * 
 * @param result    Where to store the result of the shift
 * @param x         The big uinteger `x` to shift
 * @param n         The big uinteger `n` to shift by
 * @param shift_t   The type of shift (either SHIFT_BIT [0] or SHIFT_LIMB [1])
 */
void big_uint_shl(big_uint_t *result, const big_uint_t *x, uint64_t n, uint8_t shift_t);

/****************************************/
/*        ARITHMETIC OPERATIONS         */
/****************************************/

/**
 * @brief Computes a + b and stores the sum in `c`
 * NOTE:  We only retain the limbs of the sum that fit within c
 * 
 * @param c Where to store the sum
 * @param a      The first number to add
 * @param b      The second number to add
 */
void big_uint_add(big_uint_t *c, const big_uint_t *a, const big_uint_t *b);

/**
 * @brief Computes a - b and stores the difference in `c`
 * NOTE:  We only retain the limbs of the difference that fit within c
 * 
 * @param c Where to store the difference
 * @param a The first number to subtract
 * @param b The amount to subtract from the first
 */
void big_uint_sub(big_uint_t *c, const big_uint_t *a, const big_uint_t *b);

/**
 * @brief Computes a * b and stores the product in `c`
 * NOTE:  We only retain the limbs of the product that fit within c
 * 
 * @param c Where to store the product
 * @param a The first number to multiply
 * @param b The second number to multiply
 */
void big_uint_mult(big_uint_t *c, const big_uint_t *a, const big_uint_t *b);

#endif
