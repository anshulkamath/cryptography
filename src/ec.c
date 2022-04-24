#include "ec.h"

#include <assert.h>
#include "big-uint.h"
#include <stdio.h>

void point_print(const point_t *pt) {
    printf("Point located at %p:\n", (void *) pt);
    printf("\tx = ");
    big_uint_print(pt->x);
    printf("\ty = ");
    big_uint_print(pt->y);
}
