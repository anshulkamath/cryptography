#include "big-uint.h"
#include "testing-logger.h"

void test_big_uint_init() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t res;

    // Test 1
    uint32_t arr1[] = { 0x00000001 };
    big_uint_init(&res, arr1, 1);

    expect(tester, res.arr == arr1);
    expect(tester, res.len == 1);

    // Test 2
    uint32_t arr2[] = { 0x00000001, 0x00000000 };
    big_uint_init(&res, arr2, 2);

    expect(tester, res.arr == arr2);
    expect(tester, res.len == 2);

    log_tests(tester);
}

void test_big_uint_count_limbs() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();

    // variable length numbers test
    expect(tester, big_uint_count_limbs("0x0") == 1);
    expect(tester, big_uint_count_limbs("0x12345678") == 1);
    expect(tester, big_uint_count_limbs("0x123456789") == 2);
    expect(tester, big_uint_count_limbs("0x123456782345678") == 2);
    expect(tester, big_uint_count_limbs("0x12345678123456789") == 3);
    expect(tester, big_uint_count_limbs("0x00000000000000000") == 3);

    // various delimeters test
    expect(tester, big_uint_count_limbs("0x1 2 3 4 5 6 7 8") == 1);
    expect(tester, big_uint_count_limbs("0x0_12345678") == 2);
    expect(tester, big_uint_count_limbs("0x1_23456789") == 2);
    expect(tester, big_uint_count_limbs("0x87654321_12345678") == 2);
    expect(tester, big_uint_count_limbs("0x87654321_12345678") == 2);
    expect(tester, big_uint_count_limbs("0x0_87654321_12345678") == 3);

    log_tests(tester);
}

int main() {
    test_big_uint_init();
    test_big_uint_count_limbs();

    return 0;
}
