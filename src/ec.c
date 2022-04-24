#include "ec.h"

#include <assert.h>
#include "big-uint.h"

void point_init(point_t *res, big_uint_t *x, big_uint_t *y) {
    // ensure that x and y have the same number of limbs to simplify point rep.
    assert(x->len == y->len);
    
    res->x = x;
    res->y = y;
}
