#include "ec.h"
#include "secp256k1.c"

#include "big-uint.h"
#include "mod.h"
#include "point.h"
#include <string.h>
#include "testing-logger.h"

void test_ec_init() {
    testing_logger_t *tester = create_tester();
    big_uint_t a, b, p, n;
    mod_t mod_p, mod_n;
    point_t g;
    ec_t ec;

    big_uint_load(&a, "0x3");
    big_uint_load(&b, "0x5");
    big_uint_load(&p, "0xd");
    big_uint_load(&n, "0xd");
    mod_create(&mod_p, &p);
    mod_create(&mod_n, &n);
    point_create(&g, "0x1", "0x2");

    ec_init(&ec, &a, &b, &mod_p, &mod_n, &g);
    
    expect(tester, big_uint_equals(ec.a, &a));
    expect(tester, big_uint_equals(ec.b, &b));
    expect(tester, mod_equals(ec.mod_p, &mod_p));
    expect(tester, mod_equals(ec.mod_n, &mod_n));
    expect(tester, point_equals(ec.g, &g));

    log_tests(tester);
}

void test_ec_create() {
    testing_logger_t *tester = create_tester();
    big_uint_t exp_a, exp_b, exp_p, exp_n;
    mod_t exp_mod_p, exp_mod_n;
    point_t exp_g;
    ec_t ec;

    big_uint_load(&exp_a, SECP256K1_A);
    big_uint_load(&exp_b, SECP256K1_B);
    big_uint_load(&exp_p, SECP256K1_P);
    big_uint_load(&exp_n, SECP256K1_N);
    mod_create(&exp_mod_p, &exp_p);
    mod_create(&exp_mod_n, &exp_n);
    point_create(&exp_g, SECP256K1_X, SECP256K1_Y);

    // create secp256k1 instance
    ec_create(&ec, SECP_256K1);

    expect(tester, big_uint_equals(ec.a, &exp_a));
    expect(tester, big_uint_equals(ec.b, &exp_b));
    expect(tester, mod_equals(ec.mod_p, &exp_mod_p));
    expect(tester, mod_equals(ec.mod_n, &exp_mod_n));
    expect(tester, point_equals(ec.g, &exp_g));

    log_tests(tester);
}

int main () {
    test_ec_init();
    test_ec_create();
    
    return 0;
}
