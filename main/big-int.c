#include "big-uint.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage() {
    fprintf(stdout, "Usage: big-int [num1] [+|-|x|/] [num2]\n");
}

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
    
    char q_str[9 * u.len];
    char r_str[9 * v.len];

    big_uint_load(&u, u_str);
    big_uint_load(&v, v_str);
    big_uint_create(&q, u.len);
    big_uint_create(&r, v.len);

    big_uint_div(&q, &r, &u, &v);
    
    big_uint_spprint(q_str, &q);
    big_uint_spprint(r_str, &r);

    fprintf(stdout, "%s / %s = %s remainder %s\n", u_str, v_str, q_str, r_str);
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

    usage();

    return 1;
}
