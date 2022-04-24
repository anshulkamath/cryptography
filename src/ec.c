#include "ec.h"

#include <assert.h>
#include "big-uint.h"
#include <stdio.h>

void point_init(point_t *res, big_uint_t *x, big_uint_t *y) {
    // ensure that x and y have the same number of limbs to simplify point rep.
    assert(x->len == y->len);
    
    res->x = x;
    res->y = y;
}

void point_print(const point_t *pt) {
    printf("Point located at %p:\n", (void *) pt);
    printf("\tx = ");
    big_uint_print(pt->x);
    printf("\ty = ");
    big_uint_print(pt->y);
}
