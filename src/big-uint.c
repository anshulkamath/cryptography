#include "big-uint.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void big_uint_init(big_uint_t *dest, uint32_t *arr, uint64_t len) {
    dest->arr = arr;
    dest->len = len;
}
