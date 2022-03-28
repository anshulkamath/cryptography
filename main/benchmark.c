#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "big-uint.h"

void benchmark_big_uint_add() {
    clock_t start = clock();
    int count = 0;
    big_uint_t a;
    big_uint_t b;
    big_uint_t c;

    big_uint_load(&a, "0x"
        "12341234_12341234_12341234_12341234_"
        "12341234_12341234_12341234_12341234_"
    );

    big_uint_load(&b, "0x"
        "56785678_56785678_56785678_56785678_"
        "56785678_56785678_56785678_56785678_"
    );

    big_uint_load(&c, "0x"
        "00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000"
    );

    while(clock() - start < CLOCKS_PER_SEC) {
        big_uint_add(&c, &a, &b);
        count += 1;
    }

    printf("big_uint_add: %d\n", count);
}

void benchmark_big_uint_sub() {
    clock_t start = clock();
    int count = 0;
    big_uint_t a;
    big_uint_t b;
    big_uint_t c;

    big_uint_load(&a, "0x"
        "12341234_12341234_12341234_12341234_"
        "12341234_12341234_12341234_12341234_"
    );

    big_uint_load(&b, "0x"
        "56785678_56785678_56785678_56785678_"
        "56785678_56785678_56785678_56785678_"
    );

    while(clock() - start < CLOCKS_PER_SEC) {
        big_uint_sub(&c, &a, &b);
        count += 1;
    }

    printf("big_uint_sub: %d\n", count);
}

void benchmark_big_uint_mult() {
    clock_t start = clock();
    int count = 0;
    big_uint_t a;
    big_uint_t b;
    big_uint_t c;

    big_uint_load(&a, "0x"
        "12341234_12341234_12341234_12341234_"
        "12341234_12341234_12341234_12341234_"
    );

    big_uint_load(&b, "0x"
        "56785678_56785678_56785678_56785678_"
        "56785678_56785678_56785678_56785678_"
    );

    while(clock() - start < CLOCKS_PER_SEC) {
        big_uint_mult(&c, &a, &b);
        count += 1;
    }

    printf("big_uint_mult: %d\n", count);
}

int main() {
    benchmark_big_uint_add();
    benchmark_big_uint_sub();
    benchmark_big_uint_mult();

    return 0;
}
