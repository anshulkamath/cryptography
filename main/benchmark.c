#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "big-uint.h"

big_uint_t A;
big_uint_t B;
big_uint_t C;

#define STRINGIFY(x) #x
#define BENCHMARK(func, aux, batch) benchmark(STRINGIFY(func), func, aux, batch)

void benchmark(const char *name, void (*func)(void*), void* aux, size_t batch) {
    size_t count = 0;

    time_t start = clock();
    while (1) {
        for (size_t i = 0; i < batch; i++) func(aux);
        time_t end = clock();
        count += batch;
        
        if (end - start > CLOCKS_PER_SEC) {
            size_t ops = count * CLOCKS_PER_SEC / (end - start);
            printf("%s: %lu\n", name, ops);
            break;
        }
    }
}

void benchmark_big_uint_add() {
    big_uint_add(&C, &A, &B);
}

void benchmark_big_uint_sub() {
    big_uint_sub(&C, &A, &B);
}

void benchmark_big_uint_mult() {
    big_uint_mult(&C, &A, &B);
}

int main() {
    // initialize global variables
    big_uint_load(&A, "0x6409b613_c5e7c7e9_27f9d2c4_1b56af5e_a49ec282_77c71eb1_2223a2cf_f01135d7");
    big_uint_load(&B, "0x1a74c20e_80b9aa12_2b748f72_3ad25ba0_6018dd1d_7933c61d_3df4ec16_860c5a0f");
    big_uint_load(&C, "0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000");

    // arithmetic benchmark
    printf("Running benchmarks on arithmetic operations:")
    BENCHMARK(benchmark_big_uint_add, NULL, 100);
    BENCHMARK(benchmark_big_uint_sub, NULL, 100);
    BENCHMARK(benchmark_big_uint_mult, NULL, 100);

    printf("\n");
    return 0;
}
