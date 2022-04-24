#include "point.h"

#include <assert.h>
#include "big-uint.h"
#include <stdio.h>

void point_init(point_t *dest, big_uint_t *x, big_uint_t *y) {
    // ensure that x and y have the same number of limbs to simplify point rep.
    assert(x->len == y->len);
    dest->x = x; dest->y = y;
}

void point_print(const point_t *pt) {
    printf("Point located at %p:\n", (void *) pt);
    printf("\tx = ");
    big_uint_print(pt->x);
    printf("\ty = ");
    big_uint_print(pt->y);
}

uint8_t point_equals(const point_t *p1, const point_t *p2) {
    return big_uint_equals(p1->x, p2->x) && big_uint_equals(p1->y, p2->y);
}

uint8_t point_is_identity(const point_t *p) {
    return big_uint_is_zero(p->x) && big_uint_is_zero(p->y);
}
