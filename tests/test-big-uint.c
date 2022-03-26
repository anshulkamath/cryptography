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

int main() {
    test_big_uint_init();

    return 0;
}
