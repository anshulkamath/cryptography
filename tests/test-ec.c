#include "ec.h"

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

int main () {
    test_ec_init();
    
    return 0;
}
