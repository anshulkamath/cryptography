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

void test_point_equals() {
    testing_logger_t *tester = create_tester();
    point_t p1, p2;

    // should be equal
    point_create(&p1, "0x12345678", "0x87654321");
    point_create(&p2, "0x12345678", "0x87654321");
    expect(tester, point_equals(&p1, &p2));
    
    // should not be equal
    point_create(&p2, "0x87654321", "0x12345678");
    expect(tester, !point_equals(&p1, &p2));

    log_tests(tester);
}

void test_point_is_identity() {
    testing_logger_t *tester = create_tester();
    point_t p;

    // should be equal
    point_create(&p, "0x0", "0x0");
    expect(tester, point_is_identity(&p));
    
    // should not be equal
    point_create(&p, "0x1", "0x0");
    expect(tester, !point_is_identity(&p));

    point_create(&p, "0x0", "0x1");
    expect(tester, !point_is_identity(&p));

    point_create(&p, "0x1", "0x1");
    expect(tester, !point_is_identity(&p));

    log_tests(tester);
}

int main() {
    test_point_init();
    test_point_create();
    test_point_equals();
    test_point_is_identity();

    return 0;
}
