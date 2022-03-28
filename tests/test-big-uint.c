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

    expect(tester, big_uint_equals(&a, &a));
    expect(tester, big_uint_equals(&b, &b));

    log_tests(tester);
}

void test_big_uint_cmp() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t b;

    big_uint_load(&a, "0x00000000");
    big_uint_load(&b, "0x00000000");

    expect(tester, big_uint_cmp(&a, &b) == 0);

    big_uint_load(&a, "0x12345678");
    big_uint_load(&b, "0xffffffff");

    expect(tester, big_uint_cmp(&a, &b) == -1);

    big_uint_load(&a, "0xffffffff");
    big_uint_load(&b, "0xfffffffe");

    expect(tester, big_uint_cmp(&a, &b) == 1);

    big_uint_load(&a, "0x00000000_12345678");
    big_uint_load(&b, "0x00000000_ffffffff");

    expect(tester, big_uint_cmp(&a, &b) == -1);

    big_uint_load(&a, "0x00000000_12345678");
    big_uint_load(&b, "0xffffffff");

    expect(tester, big_uint_cmp(&a, &b) == -1);

    big_uint_load(&a, "0xffffffff_fffffffe");
    big_uint_load(&b, "0xffffffff_ffffffff");

    expect(tester, big_uint_cmp(&a, &b) == -1);

    big_uint_load(&a, "0xffffffff_ffffffff_ffffffff_fffffffe");
    big_uint_load(&b, "0xffffffff_ffffffff_ffffffff_ffffffff");

    expect(tester, big_uint_cmp(&a, &b) == -1);

    big_uint_load(&a, "0xffffffff_ffffffff_ffffffff_fffffffe");
    big_uint_load(&b, "0x00000000_00000000_00000000_ffffffff");

    expect(tester, big_uint_cmp(&a, &b) == 1);

    big_uint_load(&a, "0x00000000_00000000_00000000_00000002");
    big_uint_load(&b, "0x00000000_00000000_00000000_00000001");

    expect(tester, big_uint_cmp(&a, &b) == 1);

    big_uint_load(&a, "0x00000000_00000000_00000000_00000001");
    big_uint_load(&b, "0x00000000_00000000_00000000_00000001");

    expect(tester, big_uint_cmp(&a, &b) == 0);

    log_tests(tester);
}

void test_big_uint_max() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t b;
    big_uint_t res;

    big_uint_load(&a, "0x00000000");
    big_uint_load(&b, "0x00000000");

    res = big_uint_max(&a, &b);

    expect(tester, big_uint_equals(&a, &res));

    big_uint_load(&a, "0x12345678");
    big_uint_load(&b, "0xffffffff");

    res = big_uint_max(&a, &b);

    expect(tester, big_uint_equals(&b, &res));

    big_uint_load(&a, "0xffffffff");
    big_uint_load(&b, "0xfffffffe");

    res = big_uint_max(&a, &b);

    expect(tester, big_uint_equals(&a, &res));

    big_uint_load(&a, "0x00000000_12345678");
    big_uint_load(&b, "0x00000000_ffffffff");

    res = big_uint_max(&a, &b);

    expect(tester, big_uint_equals(&b, &res));

    big_uint_load(&a, "0x00000000_12345678");
    big_uint_load(&b, "0xffffffff");

    res = big_uint_max(&a, &b);

    expect(tester, big_uint_equals(&b, &res));

    big_uint_load(&a, "0xffffffff_fffffffe");
    big_uint_load(&b, "0xffffffff_ffffffff");

    res = big_uint_max(&a, &b);

    expect(tester, big_uint_equals(&b, &res));

    big_uint_load(&a, "0xffffffff_ffffffff_ffffffff_fffffffe");
    big_uint_load(&b, "0xffffffff_ffffffff_ffffffff_ffffffff");

    res = big_uint_max(&a, &b);

    expect(tester, big_uint_equals(&b, &res));

    big_uint_load(&a, "0xffffffff_ffffffff_ffffffff_fffffffe");
    big_uint_load(&b, "0x00000000_00000000_00000000_ffffffff");

    res = big_uint_max(&a, &b);

    expect(tester, big_uint_equals(&a, &res));

    big_uint_load(&a, "0x00000000_00000000_00000000_00000002");
    big_uint_load(&b, "0x00000000_00000000_00000000_00000001");

    res = big_uint_max(&a, &b);

    expect(tester, big_uint_equals(&a, &res));

    big_uint_load(&a, "0x00000000_00000000_00000000_00000001");
    big_uint_load(&b, "0x00000000_00000000_00000000_00000001");

    res = big_uint_max(&a, &b);

    expect(tester, big_uint_equals(&a, &res));

    log_tests(tester);
}

void test_big_uint_min() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t b;
    big_uint_t res;

    big_uint_load(&a, "0x00000000");
    big_uint_load(&b, "0x00000000");

    res = big_uint_min(&a, &b);

    expect(tester, big_uint_equals(&a, &res));

    big_uint_load(&a, "0x12345678");
    big_uint_load(&b, "0xffffffff");

    res = big_uint_min(&a, &b);

    expect(tester, big_uint_equals(&a, &res));

    big_uint_load(&a, "0xffffffff");
    big_uint_load(&b, "0xfffffffe");

    res = big_uint_min(&a, &b);

    expect(tester, big_uint_equals(&b, &res));

    big_uint_load(&a, "0x00000000_12345678");
    big_uint_load(&b, "0x00000000_ffffffff");

    res = big_uint_min(&a, &b);

    expect(tester, big_uint_equals(&a, &res));

    big_uint_load(&a, "0x00000000_12345678");
    big_uint_load(&b, "0xffffffff");

    res = big_uint_min(&a, &b);

    expect(tester, big_uint_equals(&a, &res));

    big_uint_load(&a, "0xffffffff_fffffffe");
    big_uint_load(&b, "0xffffffff_ffffffff");

    res = big_uint_min(&a, &b);

    expect(tester, big_uint_equals(&a, &res));

    big_uint_load(&a, "0xffffffff_ffffffff_ffffffff_fffffffe");
    big_uint_load(&b, "0xffffffff_ffffffff_ffffffff_ffffffff");

    res = big_uint_min(&a, &b);

    expect(tester, big_uint_equals(&a, &res));

    big_uint_load(&a, "0xffffffff_ffffffff_ffffffff_fffffffe");
    big_uint_load(&b, "0x00000000_00000000_00000000_ffffffff");

    res = big_uint_min(&a, &b);

    expect(tester, big_uint_equals(&b, &res));

    big_uint_load(&a, "0x00000000_00000000_00000000_00000002");
    big_uint_load(&b, "0x00000000_00000000_00000000_00000001");

    res = big_uint_min(&a, &b);

    expect(tester, big_uint_equals(&b, &res));

    big_uint_load(&a, "0x00000000_00000000_00000000_00000001");
    big_uint_load(&b, "0x00000000_00000000_00000000_00000001");

    res = big_uint_max(&a, &b);

    expect(tester, big_uint_equals(&a, &res));

    log_tests(tester);
}

void test_big_uint_or() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t b;
    big_uint_t exp;
    big_uint_t res;

    // Single digit test (no carry, no underflow)
    big_uint_load(&a, "0x11110000");
    big_uint_load(&b, "0x00002222");
    big_uint_load(&exp, "0x11112222");
    big_uint_load(&res, "0x00000000");
    big_uint_or(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0xffffffff");
    big_uint_load(&b, "0x00000000");
    big_uint_load(&exp, "0xffffffff");
    big_uint_load(&res, "0x00000000");
    big_uint_or(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0x00000000");
    big_uint_load(&b, "0xffffffff");
    big_uint_load(&exp, "0xffffffff");
    big_uint_load(&res, "0x00000000");
    big_uint_or(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0xffffffff_00000000");
    big_uint_load(&b, "0x00000000_ffffffff");
    big_uint_load(&exp, "0xffffffff_ffffffff");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_or(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0xffff0000_ffff0000");
    big_uint_load(&b,  "0x0000ffff");
    big_uint_load(&exp, "0xffff0000_ffffffff");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_or(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0x12345678_12345678");
    big_uint_load(&b, "0x12345678_12345678");
    big_uint_load(&exp, "0x12345678_12345678");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_or(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // arg1 or-equals
    big_uint_load(&a, "0xffff0000_ffff0000");
    big_uint_load(&b, "0x0000ffff_0000ffff");
    big_uint_load(&exp, "0xffffffff_ffffffff");
    big_uint_or(&a, &a, &b);

    expect(tester, big_uint_equals(&a, &exp));

    // arg2 or-equals
    big_uint_load(&a, "0xffff0000_ffff0000");
    big_uint_load(&b, "0x0000ffff_0000ffff");
    big_uint_load(&exp, "0xffffffff_ffffffff");
    big_uint_or(&b, &a, &b);

    expect(tester, big_uint_equals(&b, &exp));

    // different sizes
    big_uint_load(&a, "0xffffffff_00000000");
    big_uint_load(&b, "0x00000000_12345678");
    big_uint_load(&exp, "0x12345678");
    big_uint_load(&res, "0x00000000");
    big_uint_or(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    log_tests(tester);
}

void test_big_uint_and() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t b;
    big_uint_t exp;
    big_uint_t res;

    // Single digit test (no carry, no underflow)
    big_uint_load(&a, "0x11110000");
    big_uint_load(&b, "0x00002222");
    big_uint_load(&exp, "0x00000000");
    big_uint_load(&res, "0x11111111");
    big_uint_and(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0xffffffff");
    big_uint_load(&b, "0x0000ffff");
    big_uint_load(&exp, "0x0000ffff");
    big_uint_load(&res, "0x00000000");
    big_uint_and(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0x0000ffff");
    big_uint_load(&b, "0xffffffff");
    big_uint_load(&exp, "0x0000ffff");
    big_uint_load(&res, "0x00000000");
    big_uint_and(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0xffffffff_00000000");
    big_uint_load(&b, "0x0000ffff_ffff0000");
    big_uint_load(&exp, "0x0000ffff_00000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_and(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0xffff0000_ffff0000");
    big_uint_load(&b,  "0x00ffff00");
    big_uint_load(&exp, "0x00000000_00ff0000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_and(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0x12345678_12345678");
    big_uint_load(&b, "0x12345678_12345678");
    big_uint_load(&exp, "0x12345678_12345678");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_and(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // arg1 and-equals
    big_uint_load(&a, "0xffff0000_ffff0000");
    big_uint_load(&b, "0x0000ffff_0000ffff");
    big_uint_load(&exp, "0x00000000_00000000");
    big_uint_and(&a, &a, &b);

    expect(tester, big_uint_equals(&a, &exp));

    // arg2 and-equals
    big_uint_load(&a, "0xffff0000_ffff0000");
    big_uint_load(&b, "0x0000ffff_0000ffff");
    big_uint_load(&exp, "0x00000000_00000000");
    big_uint_and(&b, &a, &b);

    expect(tester, big_uint_equals(&b, &exp));

    // different sizes
    big_uint_load(&a, "0xffffffff_12345678");
    big_uint_load(&b, "0x00000000_12345678");
    big_uint_load(&exp, "0x12345678");
    big_uint_load(&res, "0x00000000");
    big_uint_and(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    log_tests(tester);
}

void test_big_uint_xor() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t b;
    big_uint_t exp;
    big_uint_t res;

    // Single digit test (no carry, no underflow)
    big_uint_load(&a, "0xffff0000");
    big_uint_load(&b, "0x0000ffff");
    big_uint_load(&exp, "0xffffffff");
    big_uint_load(&res, "0x00000000");
    big_uint_xor(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0xffffffff");
    big_uint_load(&b, "0x00000000");
    big_uint_load(&exp, "0xffffffff");
    big_uint_load(&res, "0x00000000");
    big_uint_xor(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0x00000000");
    big_uint_load(&b, "0x00000000");
    big_uint_load(&exp, "0x00000000");
    big_uint_load(&res, "0xffffffff");
    big_uint_xor(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0xffffffff_00000000");
    big_uint_load(&b, "0x00000000_ffffffff");
    big_uint_load(&exp, "0xffffffff_ffffffff");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_xor(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0xffff0000_ffffffff");
    big_uint_load(&b, "0xffffffff_0000ffff");
    big_uint_load(&exp, "0x0000ffff_ffff0000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_xor(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0x12345678_12345678");
    big_uint_load(&b, "0x12345678_12345678");
    big_uint_load(&exp, "0x00000000_00000000");
    big_uint_load(&res, "0xffffffff_ffffffff");
    big_uint_xor(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // arg1 xor-equals
    big_uint_load(&a, "0xffff0000_ffffffff");
    big_uint_load(&b, "0xffffffff_0000ffff");
    big_uint_load(&exp, "0x0000ffff_ffff0000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_xor(&a, &a, &b);

    expect(tester, big_uint_equals(&a, &exp));

    // arg2 xor-equals
    big_uint_load(&a, "0xffff0000_ffffffff");
    big_uint_load(&b, "0xffffffff_0000ffff");
    big_uint_load(&exp, "0x0000ffff_ffff0000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_xor(&b, &a, &b);

    expect(tester, big_uint_equals(&b, &exp));

    // different sizes
    big_uint_load(&a, "0xffffffff_12340000");
    big_uint_load(&b, "0x00000000_12345678");
    big_uint_load(&exp, "0x00005678");
    big_uint_load(&res, "0x00000000");
    big_uint_xor(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    log_tests(tester);
}

void test_big_uint_shr() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t x;
    big_uint_t exp;
    big_uint_t res;

    // Test 1 - shift to 0
    big_uint_load(&x, "0x00000001");
    big_uint_load(&exp, "0x00000000");
    big_uint_load(&res, "0xffffffff");

    big_uint_shr(&res, &x, 1, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

    big_uint_shr(&res, &x, 1, SHIFT_LIMB);
    expect(tester, big_uint_equals(&res, &exp));

    // Test 2 - normal shift
    big_uint_load(&x, "0x00001000");
    big_uint_load(&exp, "0x00000010");
    big_uint_load(&res, "0xffffffff");

    big_uint_shr(&res, &x, 8, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

    // Test 3 - partial shift across boundary
    big_uint_load(&x, "0x0000000f_00000000");
    big_uint_load(&exp, "0x00000003_c0000000");
    big_uint_load(&res, "0x00000000_00000000");

    big_uint_shr(&res, &x, 2, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&exp, "0x00000000_0000000f");
    big_uint_shr(&res, &x, 1, SHIFT_LIMB);
    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&exp, "0x00000000_00000007");
    big_uint_shr(&res, &x, 33, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

    // Test 4 - overshift should be 0
    big_uint_load(&x, "0x12345678_12345678");
    big_uint_load(&exp, "0x00000000_00000000");
    big_uint_load(&res, "0xffffffff_ffffffff");

    big_uint_shr(&res, &x, 100, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

    big_uint_shr(&res, &x, 5, SHIFT_LIMB);
    expect(tester, big_uint_equals(&res, &exp));

    // Test 5 - no shift
    big_uint_load(&x, "0x12345678_12345678");
    big_uint_load(&exp, "0x12345678_12345678");
    big_uint_load(&res, "0xffffffff_ffffffff");

    big_uint_shr(&res, &x, 0, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&res, "0xffffffff_ffffffff");
    big_uint_shr(&res, &x, 0, SHIFT_LIMB);
    expect(tester, big_uint_equals(&res, &exp));

    // Test 6 - operator assignment
    big_uint_load(&x, "0x0000000f_00000000");
    big_uint_load(&exp, "0x00000003_c0000000");
    big_uint_shr(&x, &x, 2, SHIFT_BIT);
    expect(tester, big_uint_equals(&x, &exp));

    big_uint_load(&x, "0x0000000f_00000000");
    big_uint_load(&exp, "0x00000000_0000000f");
    big_uint_shr(&x, &x, 1, SHIFT_LIMB);
    expect(tester, big_uint_equals(&x, &exp));

    log_tests(tester);
}

void test_big_uint_shl() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t x;
    big_uint_t exp;
    big_uint_t res;

    // Test 1 - left shift by 1 digit and limb
    big_uint_load(&x, "0x00000001");
    big_uint_load(&exp, "0x00000002");
    big_uint_load(&res, "0xffffffff");

    big_uint_shl(&res, &x, 1, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&exp, "0x00000000");
    big_uint_shl(&res, &x, 1, SHIFT_LIMB);
    expect(tester, big_uint_equals(&res, &exp));

    // Test 2 - normal shift
    big_uint_load(&x, "0x00001000");
    big_uint_load(&exp, "0x00100000");
    big_uint_load(&res, "0xffffffff");

    big_uint_shl(&res, &x, 8, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

    // Test 3a - partial shift across boundary
    big_uint_load(&x, "0x0000000f_00000000");
    big_uint_load(&exp, "0x0000003c_00000000");
    big_uint_load(&res, "0x00000000_00000000");

    big_uint_shl(&res, &x, 2, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

    // Test 3b
    big_uint_load(&x, "0x00000000_0000000f");
    big_uint_load(&exp, "0x0000000f_00000000");
    big_uint_shl(&res, &x, 1, SHIFT_LIMB);
    expect(tester, big_uint_equals(&res, &exp));

    // Test 3c
    big_uint_load(&x, "0x00000000_0f000000");
    big_uint_load(&exp, "0x1e000000_00000000");
    big_uint_shl(&res, &x, 33, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

    // Test 4 - overshift should be 0
    big_uint_load(&x, "0x12345678_12345678");
    big_uint_load(&exp, "0x00000000_00000000");
    big_uint_load(&res, "0xffffffff_ffffffff");

    big_uint_shl(&res, &x, 100, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

    big_uint_shl(&res, &x, 5, SHIFT_LIMB);
    expect(tester, big_uint_equals(&res, &exp));

    // Test 5 - no shift
    big_uint_load(&x, "0x12345678_12345678");
    big_uint_load(&exp, "0x12345678_12345678");
    big_uint_load(&res, "0xffffffff_ffffffff");

    big_uint_shl(&res, &x, 0, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&res, "0xffffffff_ffffffff");
    big_uint_shl(&res, &x, 0, SHIFT_LIMB);
    expect(tester, big_uint_equals(&res, &exp));

    // Test 6 - operator assignment
    big_uint_load(&x, "0x0000000f_00000000");
    big_uint_load(&exp, "0x0000003c_00000000");
    big_uint_shl(&x, &x, 2, SHIFT_BIT);
    expect(tester, big_uint_equals(&x, &exp));

    big_uint_load(&x, "0x0000000f_0000000f");
    big_uint_load(&exp, "0x0000000f_00000000");
    big_uint_shl(&x, &x, 1, SHIFT_LIMB);
    expect(tester, big_uint_equals(&x, &exp));

    log_tests(tester);
}

void test_big_uint_add() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t b;
    big_uint_t exp;
    big_uint_t res;

    // Single digit test (no carry, no overflow)
    big_uint_load(&a, "0x00000010");
    big_uint_load(&b, "0x00000020");
    big_uint_load(&exp, "0x00000030");
    big_uint_load(&res, "0x00000000");
    big_uint_add(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (no carry, no overflow)
    big_uint_load(&a, "0x00000025_00000012");
    big_uint_load(&b, "0x00000030_00000015");
    big_uint_load(&exp, "0x00000055_00000027");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_add(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (no carry, no overflow)
    big_uint_load(&a, "0x00000025_000000ff");
    big_uint_load(&b, "0x00000030_00000015");
    big_uint_load(&exp, "0x00000055_00000114");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_add(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (carry, no overflow)
    big_uint_load(&a, "0x00000025_ff000000");
    big_uint_load(&b, "0x00000030_15000000");
    big_uint_load(&exp, "0x00000056_14000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_add(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

     // Multiple digit test (carry, overflow)
    big_uint_load(&a, "0x00000000_ffff0000_ffffffff");
    big_uint_load(&b, "0x00000000_0000ffff_00000001");
    big_uint_load(&exp, "0x00000001_00000000_00000000");
    big_uint_load(&res, "0x00000000_00000000_00000000");
    big_uint_add(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (no carry, overflow)
    big_uint_load(&a, "0xf0000000_00000000");
    big_uint_load(&b, "0x10000000_00000000");
    big_uint_load(&exp, "0x00000000_00000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_add(&res, &a, &b); 

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (carry, overflow)
    big_uint_load(&a, "0xf0000000_f0000000");
    big_uint_load(&b, "0x10000000_f0000000");
    big_uint_load(&exp, "0x00000001_e0000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_add(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0x000031bc_9abbed10");
    big_uint_load(&b, "0x00000000_00000000");
    big_uint_load(&exp, "0x000031bc_9abbed10");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_add(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Misc.
    big_uint_load(&a, "0x00000000_00000000_000031bc_9abbed10");
    big_uint_load(&b, "0x00000000_00000000_00000000_00000000");
    big_uint_load(&exp, "0x00000000_00000000_000031bc_9abbed10");
    big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
    big_uint_add(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Doubling variable by adding itself
    big_uint_load(&a, "0x000031bc_9abbed10");
    big_uint_load(&exp, "0x00006379_3577da20");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_add(&res, &a, &a);

    expect(tester, big_uint_equals(&res, &exp));

    // operator assignment
    big_uint_load(&a, "0x00000000_ffff0000_ffffffff");
    big_uint_load(&b, "0x00000000_0000ffff_00000001");
    big_uint_load(&exp, "0x00000001_00000000_00000000");
    big_uint_load(&res, "0x00000000_00000000_00000000");
    big_uint_add(&a, &a, &b);

    expect(tester, big_uint_equals(&a, &exp));
    
    big_uint_load(&a, "0x00000000_ffff0000_ffffffff");
    big_uint_load(&b, "0x00000000_0000ffff_00000001");
    big_uint_load(&exp, "0x00000001_00000000_00000000");
    big_uint_load(&res, "0x00000000_00000000_00000000");
    big_uint_add(&b, &a, &b);

    expect(tester, big_uint_equals(&b, &exp));

    // different lengths
    big_uint_load(&a, "0x00000025_000000ff");
    big_uint_load(&b, "0x00000015");
    big_uint_load(&exp, "0x00000025_00000114");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_add(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0x00000025_000000ff");
    big_uint_load(&b, "0x00000030_00000015");
    big_uint_load(&exp, "0x00000114");
    big_uint_load(&res, "0x00000000");
    big_uint_add(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));
    
    log_tests(tester);
}

int main() {
    test_big_uint_init();
    test_big_uint_count_limbs();
    test_big_uint_parse();
    test_big_uint_load();

    test_big_uint_sprint();
    test_big_uint_equals();
    
    test_big_uint_cmp();
    test_big_uint_max();
    test_big_uint_min();
    
    test_big_uint_or();
    test_big_uint_and();
    test_big_uint_xor();

    test_big_uint_shr();
    test_big_uint_shl();

    test_big_uint_add();

    return 0;
}
