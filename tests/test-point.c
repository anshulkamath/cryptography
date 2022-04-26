#include "point.h"

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

void test_point_load() {
    testing_logger_t *tester = create_tester();
    big_uint_t exp_x, exp_y;
    point_t res;

    big_uint_load(&exp_x, "0x12345678");
    big_uint_load(&exp_y, "0x87654321");
    point_load(&res, "0x12345678", "0x87654321");

    expect(tester, big_uint_equals(res.x, &exp_x));
    expect(tester, big_uint_equals(res.y, &exp_y));

    log_tests(tester);
}

void test_point_equals() {
    testing_logger_t *tester = create_tester();
    point_t p1, p2;

    // should be equal
    point_load(&p1, "0x12345678", "0x87654321");
    point_load(&p2, "0x12345678", "0x87654321");
    expect(tester, point_equals(&p1, &p2));
    
    // should not be equal
    point_load(&p2, "0x87654321", "0x12345678");
    expect(tester, !point_equals(&p1, &p2));

    log_tests(tester);
}

void test_point_create() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    point_t res;

    point_create(&res, 8);

    expect(tester, 
        big_uint_is_zero(res.x) &&
        big_uint_is_zero(res.y) && 
        res.x->len == 8 && 
        res.y->len == 8
    );

    log_tests(tester);
}

void test_point_copy() {
	// Define variables to be tested with
    testing_logger_t *tester = create_tester();
    point_t p;
	point_t res, exp;

    point_load(&p, "0x1", "0x2");
    point_create(&res, 1);
    point_copy(&res, &p);

    expect(tester, point_equals(&res, &p));

    point_load(&p, "0x12345678_87654321", "0x12345678_87654321");
    point_load(&exp, "0x87654321", "0x87654321");
    point_create(&res, 1);
    point_copy(&res, &p);

    expect(tester, point_equals(&res, &exp));

    point_load(&p, "0x0", "0x0");
    point_load(&exp, "0x00000000_00000000", "0x00000000_00000000");
    point_load(&res, "0x12345678_87654321", "0x12345678_87654321");
    point_copy(&res, &p);

    expect(tester, point_equals(&res, &exp));

    log_tests(tester);
}

void test_point_copyi() {
	// Define variables to be tested with
    testing_logger_t *tester = create_tester();
    point_t p;
	point_t res;

    point_load(&p, "0x1", "0x2");
    point_copyi(&res, &p);

    expect(tester, point_equals(&res, &p));

    log_tests(tester);
}


void test_point_is_identity() {
    testing_logger_t *tester = create_tester();
    point_t p;

    // should be equal
    point_load(&p, "0x0", "0x0");
    expect(tester, point_is_identity(&p));
    
    // should not be equal
    point_load(&p, "0x1", "0x0");
    expect(tester, !point_is_identity(&p));

    point_load(&p, "0x0", "0x1");
    expect(tester, !point_is_identity(&p));

    point_load(&p, "0x1", "0x1");
    expect(tester, !point_is_identity(&p));

    log_tests(tester);
}

void test_point_get_identity() {
    testing_logger_t *tester = create_tester();
    
    expect(tester, point_is_identity(point_get_identity()));

    log_tests(tester);
}

int main() {
    test_point_init();
    test_point_load();
    test_point_equals();
    test_point_create();
    test_point_copy();
    test_point_copyi();
    test_point_is_identity();
    test_point_get_identity();

    return 0;
}
