#include "big-uint.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void big_add(char *a_str, char *b_str) {
    big_uint_t res, a, b;

    big_uint_load(&a, a_str);
    big_uint_load(&b, b_str);
    
    uint16_t max_len = a.len > b.len ? a.len : b.len;
    big_uint_create(&res, max_len + 1);

    big_uint_add(&res, &a, &b);
    
    big_uint_pprint(&res);
}

void big_sub(char *a_str, char *b_str) {
    big_uint_t res, a, b;

    big_uint_load(&a, a_str);
    big_uint_load(&b, b_str);

    uint16_t max_len = a.len > b.len ? a.len : b.len;
    big_uint_create(&res, max_len + 1);

    big_uint_sub(&res, &a, &b);

    big_uint_pprint(&res);
}

void big_mult(char *a_str, char *b_str) {
    big_uint_t res, a, b;

    big_uint_load(&a, a_str);
    big_uint_load(&b, b_str);
    big_uint_create(&res, a.len + b.len);

    big_uint_mult(&res, &a, &b);
    
    big_uint_pprint(&res);
}

void big_div(char *u_str, char *v_str) {
    big_uint_t q, r, u, v;
    uint32_t len = u.len + v.len;
    
    char q_str[len + 3];
    q_str[0] = '0';
    q_str[1] = 'x';
    q_str[len + 2] = 0;
    
    char r_str[len + 3];
    r_str[0] = '0';
    r_str[1] = 'x';
    r_str[len + 2] = 0;

    big_uint_load(&u, u_str);
    big_uint_load(&v, v_str);
    big_uint_create(&q, len);
    big_uint_create(&r, len);

    big_uint_div(&q, &r, &u, &v);
    
    big_uint_spprint(&q_str[2], &q);
    big_uint_spprint(&r_str[2], &r);
    
    fprintf(stdout, "%s / %s = %s remainder %s", u_str, v_str, q_str, r_str);
}

int well_formatted(char *argv[]) {
    char op = argv[2][0];
    char *num1 = argv[1];
    char *num2 = argv[3];

    switch (op) {
        case '+':
            big_add(num1, num2);
            break;
        case '-':
            big_sub(num1, num2);
            break;
        case 'x':
            big_mult(num1, num2);
            break;
        case '/':
            big_div(num1, num2);
            break;
        default:
            fprintf(stderr, 
                "Unknown operator `%c`. "
                "Please try again with `+`, `-`, `*`, or `/`.\n",
                op
            );
            return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc == 4)
        return well_formatted(argv);

    return 0;
}
