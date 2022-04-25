#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "big-uint.h"
#include "mod.h"
#include "point.h"
#include "ec.h"

#define GRN     "\x1b[32m"
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define CYAN    "\x1b[36m"

big_uint_t A;
big_uint_t B;
big_uint_t C;
big_uint_t D;
big_uint_t P;
big_uint_t K;

#define STRINGIFY(x) #x
#define BENCHMARK(func, aux, batch) benchmark(STRINGIFY(func), func, aux, batch)

void benchmark(const char *name, void (*func)(void*), void* aux, size_t batch) {
    size_t count = 0;

    time_t start = clock();
    while (1) {
        for (size_t i = 0; i < batch; i++) func(aux);
        time_t end = clock();
        count += batch;
        
        if (end - start > (long) CLOCKS_PER_SEC) {
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

void benchmark_mod_add(void *aux) { mod_add(&C, &A, &B, (mod_t*) aux); }

void benchmark_mod_sub(void *aux) { mod_sub(&C, &A, &B, (mod_t*) aux); }

void benchmark_mod_mult(void *aux) { mod_mult(&C, &A, &B, (mod_t*) aux); }

void benchmark_mod_exp(void *aux) { mod_exp(&C, &A, &B, (mod_t*) aux); }

void benchmark_mod_inv(void *aux) { mod_inv(&C, &A, (mod_t*) aux); }

void benchmark_mod_neg(void *aux) { mod_neg(&C, &A, (mod_t*) aux); }

void benchmark_mod_sqrt(void *aux) { mod_sqrt(&C, &A, (mod_t*) aux); }

void benchmark_ec_add(void *aux) { 
    static uint32_t resx_arr[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
    static uint32_t resy_arr[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
    static big_uint_t resx = { .arr = resx_arr, .len = 8 };
    static big_uint_t resy = { .arr = resy_arr, .len = 8 };
    static point_t res = { .x = &resx, .y = &resy };

    static uint32_t p1x_arr[] = { 0x79be667e, 0xf9dcbbac, 0x55a06295, 0xce870b07, 0x029bfcdb, 0x2dce28d9, 0x59f2815b, 0x16f81798 };
    static uint32_t p1y_arr[] = { 0x483ada77, 0x26a3c465, 0x5da4fbfc, 0x0e1108a8, 0xfd17b448, 0xa6855419, 0x9c47d08f, 0xfb10d4b8 };
    static big_uint_t p1x = { .arr = p1x_arr, .len = 8 };
    static big_uint_t p1y = { .arr = p1y_arr, .len = 8 };
    static point_t p1 = { .x = &p1x, .y = &p1y };

    static uint32_t p2x_arr[] = { 0xa5f09e63, 0x45ddb87d, 0xa81aa40a, 0x2b0b8c12, 0xf3b37f32, 0x870266c4, 0x4155d7ef, 0x28dd37ec };
    static uint32_t p2y_arr[] = { 0xf2a30d5b, 0x67839dae, 0xeab9356a, 0x0769bd56, 0x88ef1052, 0x5392ae7e, 0x6bd58c95, 0xbd133a7f };
    static big_uint_t p2x = { .arr = p2x_arr, .len = 8 };
    static big_uint_t p2y = { .arr = p2y_arr, .len = 8 };
    static point_t p2 = { .x = &p2x, .y = &p2y };

    ec_add(&res, &p1, &p2, (ec_t*) aux);
}

void benchmark_ec_double(void *aux) { 
    static uint32_t resx_arr[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
    static uint32_t resy_arr[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
    static big_uint_t resx = { .arr = resx_arr, .len = 8 };
    static big_uint_t resy = { .arr = resy_arr, .len = 8 };
    static point_t res = { .x = &resx, .y = &resy };

    static uint32_t px_arr[] = { 0x79be667e, 0xf9dcbbac, 0x55a06295, 0xce870b07, 0x029bfcdb, 0x2dce28d9, 0x59f2815b, 0x16f81798 };
    static uint32_t py_arr[] = { 0x483ada77, 0x26a3c465, 0x5da4fbfc, 0x0e1108a8, 0xfd17b448, 0xa6855419, 0x9c47d08f, 0xfb10d4b8 };
    static big_uint_t px = { .arr = px_arr, .len = 8 };
    static big_uint_t py = { .arr = py_arr, .len = 8 };
    static point_t p = { .x = &px, .y = &py };

    ec_add(&res, &p, &p, (ec_t*) aux);
}

void benchmark_ec_mult(void *aux) {
    static uint32_t resx_arr[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
    static uint32_t resy_arr[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
    static big_uint_t resx = { .arr = resx_arr, .len = 8 };
    static big_uint_t resy = { .arr = resy_arr, .len = 8 };
    static point_t res = { .x = &resx, .y = &resy };

    static uint32_t px_arr[] = { 0x79be667e, 0xf9dcbbac, 0x55a06295, 0xce870b07, 0x029bfcdb, 0x2dce28d9, 0x59f2815b, 0x16f81798 };
    static uint32_t py_arr[] = { 0x483ada77, 0x26a3c465, 0x5da4fbfc, 0x0e1108a8, 0xfd17b448, 0xa6855419, 0x9c47d08f, 0xfb10d4b8 };
    static big_uint_t px = { .arr = px_arr, .len = 8 };
    static big_uint_t py = { .arr = py_arr, .len = 8 };
    static point_t p = { .x = &px, .y = &py };

    ec_mult(&res, &K, &p, (ec_t*) aux);
}

int main() {
    // initialize global variables
    big_uint_load(&A, "0x6409b613_c5e7c7e9_27f9d2c4_1b56af5e_a49ec282_77c71eb1_2223a2cf_f01135d7");
    big_uint_load(&B, "0x1a74c20e_80b9aa12_2b748f72_3ad25ba0_6018dd1d_7933c61d_3df4ec16_860c5a0f");
    big_uint_load(&C, "0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000");
    big_uint_load(&D, "0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000");
    big_uint_load(&P, "0x8c307598_fd51fb73_2b33dddb_02ddc885_d3b78759_d6b1c165_b39bba8d_f4a5a691");
    big_uint_load(&K, "0x40000000_00000000_00000000_00000000_00000000_00000000_00000000_00000001");

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

    mod_t mod;
    mod_create(&mod, &P);

    BENCHMARK(benchmark_mod_add, &mod, 100);
    BENCHMARK(benchmark_mod_sub, &mod, 100);
    BENCHMARK(benchmark_mod_mult, &mod, 100);
    BENCHMARK(benchmark_mod_exp, &mod, 10);
    BENCHMARK(benchmark_mod_inv, &mod, 10);
    BENCHMARK(benchmark_mod_neg, &mod, 100);
    BENCHMARK(benchmark_mod_sqrt, &mod, 10);

    ec_t ec;
    ec_create(&ec, SECP256k1);

    BENCHMARK(benchmark_ec_add, &ec, 1);
    BENCHMARK(benchmark_ec_double, &ec, 1);
    BENCHMARK(benchmark_ec_mult, &ec, 1);

    printf("\n");
    return 0;
}
