#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>
#include <stdlib.h>

/** Constant defining the number of bits for a SHA-2 hash */
#define SHA256_BITS 256

/**
 * Helper function to print hash out
 * 
 * @param src   The hash to print
 * @param len   The number of elements in the hash array
 * @param dest  Where to store the string 
 * 
 * @returns A pointer to the destination for function chaining
*/
char* sha_string(uint32_t *src, size_t len, char *dest);

/**
 * @brief Takes in the byte data and encrypts it using SHA-2
 * 
 * @param hash A pointer to where the hash should be written
 * @param data The data to hash
 * @param length The length of the data
 */
void sha256(uint32_t *hash, const char *message, uint8_t length);

#undef SHA256_BITS
#endif
