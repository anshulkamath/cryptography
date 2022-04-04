#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "big-uint.h"

#define GRN     "\x1b[32m"
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define CYAN    "\x1b[36m"

big_uint_t A;
big_uint_t B;
big_uint_t C;
big_uint_t D;

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
            printf(GRN"[%s]"RESET": "RED"%lu\n"RESET, name, ops);
            break;
        }
    }
}

void benchmark_big_uint_equals() { big_uint_equals(&A, &B); }

void benchmark_big_uint_cmp() { big_uint_cmp(&A, &B); }

void benchmark_big_uint_max() { big_uint_max(&A, &B); }

void benchmark_big_uint_min() { big_uint_min(&A, &B); }

void benchmark_big_uint_is_zero() { big_uint_is_zero(&A); }

void benchmark_big_uint_or() { big_uint_or(&C, &A, &B); }

void benchmark_big_uint_and() { big_uint_and(&C, &A, &B); }

void benchmark_big_uint_xor() { big_uint_xor(&C, &A, &B); }

void benchmark_big_uint_shr() { big_uint_shr(&C, &A, 48, LOG_2_BIT); }

void benchmark_big_uint_shl() { big_uint_shl(&C, &A, 48, LOG_2_BIT); }

void benchmark_big_uint_add() { big_uint_add(&C, &A, &B); }

void benchmark_big_uint_sub() { big_uint_sub(&C, &A, &B); }

void benchmark_big_uint_mult() { big_uint_mult(&C, &A, &B); }

void benchmark_big_uint_div() { big_uint_div(&C, &D, &A, &B); }

void benchmark_big_uint_gcd() { big_uint_gcd(&C, &A, &B); }

void benchmark_big_uint_gcd_extended() { big_uint_gcd_extended(&D, &C, &A, &B); }

int main() {
    // initialize global variables
    big_uint_load(&A, "0x6409b613_c5e7c7e9_27f9d2c4_1b56af5e_a49ec282_77c71eb1_2223a2cf_f01135d7");
    big_uint_load(&B, "0x1a74c20e_80b9aa12_2b748f72_3ad25ba0_6018dd1d_7933c61d_3df4ec16_860c5a0f");
    big_uint_load(&C, "0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000");
    big_uint_load(&D, "0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000");

    // arithmetic benchmark
    printf(CYAN"\nRunning benchmarks on arithmetic operations (ops/sec):\n"RESET);
    BENCHMARK(benchmark_big_uint_equals, NULL, 100);
    BENCHMARK(benchmark_big_uint_cmp, NULL, 100);
    BENCHMARK(benchmark_big_uint_max, NULL, 100);
    BENCHMARK(benchmark_big_uint_min, NULL, 100);
    BENCHMARK(benchmark_big_uint_is_zero, NULL, 100);
    BENCHMARK(benchmark_big_uint_or, NULL, 100);
    BENCHMARK(benchmark_big_uint_and, NULL, 100);
    BENCHMARK(benchmark_big_uint_xor, NULL, 100);
    BENCHMARK(benchmark_big_uint_shl, NULL, 100);
    BENCHMARK(benchmark_big_uint_shr, NULL, 100);
    BENCHMARK(benchmark_big_uint_add, NULL, 100);
    BENCHMARK(benchmark_big_uint_sub, NULL, 100);
    BENCHMARK(benchmark_big_uint_mult, NULL, 100);
    BENCHMARK(benchmark_big_uint_div, NULL, 100);
    BENCHMARK(benchmark_big_uint_gcd, NULL, 100);
    BENCHMARK(benchmark_big_uint_gcd_extended, NULL, 100);

    printf("\n");
    return 0;
}
