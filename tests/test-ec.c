#include "ec.h"

#include <string.h>
#include "big-uint.h"
#include "testing-logger.h"

void test_point_init() {
    testing_logger_t *tester = create_tester();
    big_uint_t x, y, exp_x, exp_y;
    point_t res;

    big_uint_load(&x, "0x12345678");
    big_uint_load(&y, "0x87654321");
    big_uint_load(&exp_x, "0x12345678");
    big_uint_load(&exp_y, "0x87654321");
    point_init(&res, &x, &y);

    expect(tester, big_uint_equals(res.x, &exp_x));
    expect(tester, big_uint_equals(res.y, &exp_y));

    log_tests(tester);
}

void test_point_create() {
    testing_logger_t *tester = create_tester();
    big_uint_t exp_x, exp_y;
    point_t res;

    big_uint_load(&exp_x, "0x12345678");
    big_uint_load(&exp_y, "0x87654321");
    point_create(&res, "0x12345678", "0x87654321");

    expect(tester, big_uint_equals(res.x, &exp_x));
    expect(tester, big_uint_equals(res.y, &exp_y));

    log_tests(tester);
}

int main() {
    test_point_init();
    test_point_create();

    return 0;
}
