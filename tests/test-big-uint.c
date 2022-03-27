#include "big-uint.h"
#include "testing-logger.h"

#include <string.h>

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

void test_big_uint_parse() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();

    // Test 1
    const char str1[] = "0x12345678";
    const uint32_t expected1[] = { 0x12345678 };
    uint32_t res1[1];

    big_uint_parse(res1, str1, 1);

    expect(tester, expected1[0] == res1[0]);

    // Test 2
    const char str2[] = "0x87654321_12345678";
    const uint32_t expected2[] = { 0x12345678, 0x87654321 };
    uint32_t res2[2];

    big_uint_parse(res2, str2, 2);

    expect(tester, expected2[0] == res2[0]);
    expect(tester, expected2[1] == res2[1]);

    // Test 3
    const char str3[] = "0x00000000_00000000";
    const uint32_t expected3[] = { 0x00000000, 0x00000000 };
    uint32_t res3[2];

    big_uint_parse(res3, str3, 2);

    expect(tester, expected3[0] == res3[0]);
    expect(tester, expected3[1] == res3[1]);

    // Test 4
    const char str4[] = "0x0_00011000_00022000";
    const uint32_t expected4[] = { 0x00022000, 0x00011000, 0x00000000 };
    uint32_t res4[3];

    big_uint_parse(res4, str4, 3);

    expect(tester, expected4[0] == res4[0]);
    expect(tester, expected4[1] == res4[1]);
    expect(tester, expected4[2] == res4[2]);

    // Test 5 - should only copy 2 digits
    const char str5[] = "0x1_00011000_00022000";
    const uint32_t expected5[] = { 0x00022000, 0x00011000, 0x00000000 };
    uint32_t res5[3] = { 0 };

    big_uint_parse(res5, str5, 2);

    expect(tester, expected5[0] == res5[0]);
    expect(tester, expected5[1] == res5[1]);
    expect(tester, expected5[2] == res5[2]);

    log_tests(tester);
}

void test_big_uint_load() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t res;

    // Test 1
    const uint32_t expected1[] = { 0x12345678 };
    
    big_uint_load(&res, "0x12345678");

    expect(tester, res.arr[0] == expected1[0]);
    expect(tester, res.len == 1);

    // Test 2
    const uint32_t expected2[] = { 0x12345678, 0x87654321 };

    big_uint_load(&res, "0x87654321_12345678");

    expect(tester, res.arr[0] == expected2[0]);
    expect(tester, res.arr[1] == expected2[1]);
    expect(tester, res.len == 2);

    // Test 3
    const uint32_t expected3[] = { 0x00000000, 0x00000000 };

    big_uint_load(&res, "0x00000000_00000000");

    expect(tester, res.arr[0] == expected3[0]);
    expect(tester, res.arr[1] == expected3[1]);
    expect(tester, res.len == 2);

    // Test 4
    const uint32_t expected4[] = { 0x00022000, 0x00011000, 0x00000000 };

    big_uint_load(&res, "0x0_00011000_00022000");

    expect(tester, res.arr[0] == expected4[0]);
    expect(tester, res.arr[1] == expected4[1]);
    expect(tester, res.arr[2] == expected4[2]);
    expect(tester, res.len == 3);

    log_tests(tester);
}

void test_big_uint_sprint() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t value;

    // 0 digit number
    big_uint_load(&value, "0x0");
    char str1[1] = { 0 };
    big_uint_sprint(str1, &value);

    expect(tester, !strcmp(str1, "00000000"));

    // 1 digit number
    big_uint_load(&value, "0x12345678");
    char str2[9] = { 0 };
    big_uint_sprint(str2, &value);

    expect(tester, !strcmp(str2, "12345678"));

    // 2 digit number
    big_uint_load(&value, "0x12345678_87654321");
    char str3[18] = { 0 };
    big_uint_sprint(str3, &value);

    expect(tester, !strcmp(str3, "12345678 87654321"));

    // all 0s
    big_uint_load(&value, "0x00000000_00000000");
    char str4[18] = { 0 };
    big_uint_sprint(str4, &value);

    expect(tester, !strcmp(str4, "00000000 00000000"));

    log_tests(tester);
}

void test_big_uint_equals() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t b;

    big_uint_load(&a, "0x10");
    big_uint_load(&b, "0x10");

    expect(tester, big_uint_equals(&a, &b));

    big_uint_load(&a, "0x0_00000010");
    big_uint_load(&b, "0x10");

    expect(tester, big_uint_equals(&a, &b));

    big_uint_load(&a, "0x10_20000000_ff03abcd");
    big_uint_load(&b, "0x10_20000000_ff03abcd");

    expect(tester, big_uint_equals(&a, &b));

    big_uint_load(&a, "0x10_20000000_ff03abcd");
    big_uint_load(&b, "0x10_20000000_ff03abce");

    expect(tester, !big_uint_equals(&a, &b));

    log_tests(tester);
}

int main() {
    test_big_uint_init();
    test_big_uint_count_limbs();
    test_big_uint_parse();
    test_big_uint_load();
    test_big_uint_sprint();
    test_big_uint_equals();

    return 0;
}
