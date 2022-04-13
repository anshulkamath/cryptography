#include "big-uint.h"
#include "testing-logger.h"

#include <stdio.h>
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

void test_big_uint_create() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t value;

    big_uint_create(&value, 1);

    expect(tester, value.len == 1);
    expect(tester, value.arr[0] == 0);

    big_uint_create(&value, 2);

    expect(tester, value.len == 2);
    expect(tester, value.arr[0] == 0);
    expect(tester, value.arr[1] == 0);

    log_tests(tester);
}

void test_big_uint_loadi() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t value;

    big_uint_loadi(&value, 2, 1);

    expect(tester, value.len == 1);
    expect(tester, value.arr[0] == 2);

    big_uint_loadi(&value, 1 << 20, 2);

    expect(tester, value.len == 2);
    expect(tester, value.arr[0] == 1 << 20);
    expect(tester, value.arr[1] == 0);

    log_tests(tester);
}

void test_big_uint_copy() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t value;
    big_uint_t copy;

    big_uint_load(&value, "0x12345678");
    big_uint_create(&copy, 1);
    big_uint_copy(&copy, &value);

    expect(tester, copy.arr[0] == value.arr[0]);

    big_uint_load(&value, "0x12345678_87654321");
    big_uint_create(&copy, 2);
    big_uint_copy(&copy, &value);

    expect(tester, copy.arr[0] == value.arr[0]);
    expect(tester, copy.arr[1] == value.arr[1]);

    big_uint_load(&value, "0x12345678_87654321");
    big_uint_create(&copy, 1);
    big_uint_copy(&copy, &value);

    expect(tester, copy.arr[0] == value.arr[0]);

    big_uint_load(&value, "0x12345678_87654321");
    big_uint_create(&copy, 3);
    big_uint_copy(&copy, &value);

    expect(tester, copy.arr[0] == value.arr[0]);
    expect(tester, copy.arr[1] == value.arr[1]);
    expect(tester, copy.arr[2] == 0);

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

    expect(tester, !strcmp(str3, "12345678_87654321"));

    // all 0s
    big_uint_load(&value, "0x00000000_00000000");
    char str4[18] = { 0 };
    big_uint_sprint(str4, &value);

    expect(tester, !strcmp(str4, "00000000_00000000"));

    log_tests(tester);
}


void test_big_uint_spprint() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t value;

    // 0 digit number
    big_uint_load(&value, "0x0");
    char str1[4] = { 0 };
    big_uint_spprint(str1, &value);

    expect(tester, !strcmp(str1, "0x0"));

    // 1 digit number
    big_uint_load(&value, "0x12345678");
    char str2[11] = { 0 };
    big_uint_spprint(str2, &value);

    expect(tester, !strcmp(str2, "0x12345678"));

    // 2 digit number
    big_uint_load(&value, "0x12345678_87654321");
    char str3[20] = { 0 };
    big_uint_spprint(str3, &value);

    expect(tester, !strcmp(str3, "0x12345678_87654321"));

    // all 0s
    big_uint_load(&value, "0x00000000_00000000");
    char str4[4] = { 0 };
    big_uint_spprint(str4, &value);

    expect(tester, !strcmp(str4, "0x0"));

    // leading 0s
    big_uint_load(&value, "0x0000000_12345678");
    char str5[11] = { 0 };
    big_uint_spprint(str5, &value);

    expect(tester, !strcmp(str5, "0x12345678"));

    big_uint_load(&value, "0x00000001_23456789");
    char str6[13] = { 0 };
    big_uint_spprint(str6, &value);

    expect(tester, !strcmp(str6, "0x1_23456789"));

    big_uint_load(&value, "0x00000000_00000001");
    char str7[2] = { 0 };
    big_uint_spprint(str7, &value);

    expect(tester, !strcmp(str7, "0x1"));

    // big buffer
    big_uint_load(&value, "0x00000000_00000001");
    char str8[100];
    big_uint_spprint(str8, &value);

    expect(tester, !strcmp(str8, "0x1"));

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

void test_big_uint_is_zero() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;

    big_uint_load(&a, "0x00000000");

    expect(tester, big_uint_is_zero(&a) == 1);

    big_uint_load(&a, "0x00000000_00000000");

    expect(tester, big_uint_is_zero(&a) == 1);

    big_uint_load(&a, "0x00010000");

    expect(tester, big_uint_is_zero(&a) == 0);

    big_uint_load(&a, "0x10000000_00000000");

    expect(tester, big_uint_is_zero(&a) == 0);

    log_tests(tester);
}

void test_big_uint_choose() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a, b;

    big_uint_load(&a, "0xffffffff");
    big_uint_load(&b, "0x12345678");

    big_uint_choose(&a, &b, 0);  // should put 0 in a
    expect(tester, big_uint_is_zero(&a));

    big_uint_choose(&a, &b, 1);  // should put b in a
    expect(tester, big_uint_equals(&a, &b));

    // dest has more limbs than val
    big_uint_load(&a, "0xffffffff_ffffffff");
    big_uint_load(&b, "0x12345678");

    big_uint_choose(&a, &b, 0);  // should put 0 in a
    expect(tester, big_uint_is_zero(&a));

    big_uint_choose(&a, &b, 1);  // should put b in a
    expect(tester, big_uint_equals(&a, &b));

    // val has more limbs than dest
    big_uint_load(&a, "0xffffffff");
    big_uint_load(&b, "0x12345678_12345678");

    big_uint_choose(&a, &b, 0);  // should put 0 in a
    expect(tester, big_uint_is_zero(&a));

    big_uint_choose(&a, &b, 1);  // should put b in a
    expect(tester, a.arr[0] == 0x12345678);

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

    // Test 7 - misc
    big_uint_load(&x, "0x00000004_80000000");
    big_uint_load(&exp, "0x00000000_90000000");
    big_uint_load(&res, "0xffffffff_ffffffff");

    big_uint_shr(&res, &x, 3, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

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
    big_uint_load(&res, "0x00000000_00000000");
    
    big_uint_shl(&res, &x, 1, SHIFT_LIMB);
    expect(tester, big_uint_equals(&res, &exp));

    // Test 3c
    big_uint_load(&x, "0x00000000_0f000000");
    big_uint_load(&exp, "0x1e000000_00000000");
    big_uint_load(&res, "0x00000000_00000000");
    
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

    // Test 7 - misc
    big_uint_load(&x, "0x00000000_90000000");
    big_uint_load(&exp, "0x00000004_80000000");
    big_uint_load(&res, "0xffffffff_ffffffff");

    big_uint_shl(&res, &x, 3, SHIFT_BIT);
    expect(tester, big_uint_equals(&res, &exp));

    log_tests(tester);
}

void test_big_uint_ori() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t exp;
    big_uint_t res;

    // Single digit test (no carry, no underflow)
    big_uint_load(&a, "0x11110000");
    big_uint_load(&exp, "0x11111111");
    big_uint_load(&res, "0x11111111");
    big_uint_ori(&res, &a, 0x00001111);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0xffffffff_0f0f0f0f");
    big_uint_load(&exp, "0xffffffff_ffffffff");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_ori(&res, &a, 0xf0f0f0f0);

    // arg1 and-equals
    big_uint_load(&a, "0xffffffff_0f0f0f0f");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_ori(&a, &a, 0xf0f0f0f0);

    expect(tester, big_uint_equals(&a, &exp));

    log_tests(tester);
}

void test_big_uint_andi() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t exp;
    big_uint_t res;

    // Single digit test (no carry, no underflow)
    big_uint_load(&a, "0x11110000");
    big_uint_load(&exp, "0x10100000");
    big_uint_load(&res, "0x11111111");
    big_uint_andi(&res, &a, 0x10101010);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0xffffffff_ffffffff");
    big_uint_load(&exp, "0x00000000_f0f0f0f0");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_andi(&res, &a, 0xf0f0f0f0);

    // arg1 and-equals
    big_uint_load(&a, "0xffffffff_ffffffff");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_andi(&a, &a, 0xf0f0f0f0);

    expect(tester, big_uint_equals(&a, &exp));

    log_tests(tester);
}

void test_big_uint_xori() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t exp;
    big_uint_t res;

    // Single digit test (no carry, no underflow)
    big_uint_load(&a, "0x11111111");
    big_uint_load(&exp, "0x11000011");
    big_uint_load(&res, "0x00000000");
    big_uint_xori(&res, &a, 0x00111100);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0xffffffff_ffffffff");
    big_uint_load(&exp, "0xffffffff_f0f0f0f0");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_xori(&res, &a, 0x0f0f0f0f);

    // arg1 and-equals
    big_uint_load(&a, "0xffffffff_ffffffff");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_xori(&a, &a, 0x0f0f0f0f);

    expect(tester, big_uint_equals(&a, &exp));

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

void test_big_uint_sub() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t b;
    big_uint_t exp;
    big_uint_t res;

    // Single digit test (no carry, no underflow)
    big_uint_load(&a, "0x00000020");
    big_uint_load(&b, "0x00000005");
    big_uint_load(&exp, "0x0000001b");
    big_uint_load(&res, "0x00000000");
    big_uint_sub(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Single digit test (no carry, underflow)
    big_uint_load(&a, "0x00000012");
    big_uint_load(&b, "0x00000015");
    big_uint_load(&exp, "0xfffffffd");
    big_uint_load(&res, "0x00000000");
    big_uint_sub(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (no carry, no underflow)
    big_uint_load(&a, "0x00000030_00000025");
    big_uint_load(&b, "0x00000025_00000015");
    big_uint_load(&exp, "0x0000000b_00000010");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_sub(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (carry, no underflow)
    big_uint_load(&a, "0x30000006_10000000");
    big_uint_load(&b, "0x20000005_50000000");
    big_uint_load(&exp, "0x10000000_c0000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_sub(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

     // Multiple digit test (no carry, underflow)
    big_uint_load(&a, "0x00000000_00000000");
    big_uint_load(&b, "0x00000000_00000001");
    big_uint_load(&exp, "0xffffffff_ffffffff");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_sub(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (no carry, underflow)
    big_uint_load(&a, "0x00000001_00000000");
    big_uint_load(&b, "0x00000050_00000000");
    big_uint_load(&exp, "0xffffffb1_00000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_sub(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (carry, underflow)
    big_uint_load(&a, "0x0000001_10000000");
    big_uint_load(&b, "0x00000000_f0000000");
    big_uint_load(&exp, "0x00000000_20000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_sub(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // operator assignment
    big_uint_load(&a, "0x00000000_00000000");
    big_uint_load(&b, "0x00000000_00000001");
    big_uint_load(&exp, "0xffffffff_ffffffff");
    big_uint_sub(&a, &a, &b);

    expect(tester, big_uint_equals(&a, &exp));

    big_uint_load(&a, "0x00000000_00000000");
    big_uint_load(&b, "0x00000000_00000001");
    big_uint_load(&exp, "0xffffffff_ffffffff");
    big_uint_sub(&b, &a, &b);

    expect(tester, big_uint_equals(&b, &exp));

    // different length test
    big_uint_load(&a, "0x00000000");
    big_uint_load(&b, "0x00000000_00000001");
    big_uint_load(&exp, "0xffffffff");
    big_uint_sub(&a, &a, &b);

    expect(tester, big_uint_equals(&a, &exp));

    big_uint_load(&a, "0x00000000");
    big_uint_load(&b, "0x00000000_00000001");
    big_uint_load(&exp, "0xffffffff_ffffffff");
    big_uint_sub(&b, &a, &b);

    expect(tester, big_uint_equals(&b, &exp));

    log_tests(tester);
}

void test_big_uint_mult() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t b;
    big_uint_t exp;
    big_uint_t res;

    // Single digit test (no carry, no overflow)
    big_uint_load(&a, "0x00000020");
    big_uint_load(&b, "0x00000005");
    big_uint_load(&exp, "0x000000a0");
    big_uint_load(&res, "0x00000000");
    big_uint_mult(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Single digit test (no carry, no overflow)
    big_uint_load(&a, "0x00000012");
    big_uint_load(&b, "0x00000015");
    big_uint_load(&exp, "0x0000017a");
    big_uint_load(&res, "0x00000000");
    big_uint_mult(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (no carry, no overflow)
    big_uint_load(&a, "0x00000030_00000025");
    big_uint_load(&b, "0x00000000_00000015");
    big_uint_load(&exp, "0x000003f0_00000309");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_mult(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (carry, no overflow)
    big_uint_load(&a, "0x00000000_10000000");
    big_uint_load(&b, "0x00000000_00000050");
    big_uint_load(&exp, "0x00000005_00000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_mult(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

     // Multiple digit test (no carry, overflow)
    big_uint_load(&a, "0x00020000_00000000");
    big_uint_load(&b, "0x00000000_00021112");
    big_uint_load(&exp, "0x22240000_00000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_mult(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (no carry, overflow)
    big_uint_load(&a, "0x00000025_00000000");
    big_uint_load(&b, "0x00000013_11000000");
    big_uint_load(&exp, "0x75000000_00000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_mult(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (carry, overflow)
    big_uint_load(&a, "0x00000000_10000000");
    big_uint_load(&b, "0x00001100_f0025000");
    big_uint_load(&exp, "0x0f002500_00000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_mult(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Misc. tests
    big_uint_load(&a, "0x00000000_31f596dc");
    big_uint_load(&b, "0x00000000_0000fedc");
    big_uint_load(&exp, "0x000031bc_9abbed10");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_mult(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // operator assignment
    big_uint_load(&a, "0x00000000_31f596dc");
    big_uint_load(&b, "0x00000000_0000fedc");
    big_uint_load(&exp, "0x000031bc_9abbed10");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_mult(&a, &a, &b);

    expect(tester, big_uint_equals(&a, &exp));

    // different lengths
    big_uint_load(&a, "0x00000000_31f596dc");
    big_uint_load(&b, "0x0000fedc");
    big_uint_load(&exp, "0x9abbed10");
    big_uint_mult(&b, &a, &b);

    expect(tester, big_uint_equals(&b, &exp));

    // different lengths
    big_uint_load(&a, "0x00000000_31f596dc");
    big_uint_load(&b, "0x0000fedc");
    big_uint_load(&exp, "0x000031bc_9abbed10");
    big_uint_mult(&a, &a, &b);

    expect(tester, big_uint_equals(&a, &exp));
    
    // cascading overflow
    big_uint_load(&a, "0x"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
    );
    big_uint_load(&b, "0x"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
    );
    big_uint_load(&exp, "0x"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff"
        "ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_ffffffff_fffffffe"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000001"
    );
    big_uint_load(&res, "0x"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
        "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
    );
    big_uint_mult(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // misc test
    big_uint_load(&a, "0x0fd229d7_50b9169b");
	big_uint_load(&b, "0x2b711343_220d672b");
	big_uint_load(&exp, "0x02af49fc_61d06471_d053c29c_c30e2909");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000_00000000");
	big_uint_mult(&res, &a, &b);

	expect(tester, big_uint_equals(&res, &exp));

    log_tests(tester);
}

void test_big_uint_div() {
    testing_logger_t *tester = create_tester();
    big_uint_t a, b;
    big_uint_t exp_q, exp_r;
    big_uint_t q, r;

    // Divide by 0 - do nothing
    big_uint_load(&a, "0x00000001");
    big_uint_load(&b, "0x00000000");
    big_uint_load(&exp_q, "0x00000000");
    big_uint_load(&exp_r, "0x000000000");
    big_uint_load(&q, "0x00000000");
    big_uint_load(&r, "0x00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // 1 digit division (no truncation)
    big_uint_load(&a, "0x00000010");
    big_uint_load(&b, "0x00000002");
    big_uint_load(&exp_q, "0x00000008");
    big_uint_load(&exp_r, "0x00000000");
    big_uint_load(&q, "0x00000000");
    big_uint_load(&r, "0x00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // padded 1 digit division (no truncation)
    big_uint_load(&a, "0x0000000_00000010");
    big_uint_load(&b, "0x0000000_00000002");
    big_uint_load(&exp_q, "0x00000000_00000008");
    big_uint_load(&exp_r, "0x00000000_00000000");
    big_uint_load(&q, "0x00000000_00000000");
    big_uint_load(&r, "0x00000000_00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // 1 digit division (truncation)
    big_uint_load(&a, "0x00000009");
    big_uint_load(&b, "0x00000002");
    big_uint_load(&exp_q, "0x00000004");
    big_uint_load(&exp_r, "0x00000001");
    big_uint_load(&q, "0x00000000");
    big_uint_load(&r, "0x00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // 1 digit number over itself
    big_uint_load(&a, "0x12345678");
    big_uint_load(&b, "0x12345678");
    big_uint_load(&exp_q, "0x00000001");
    big_uint_load(&exp_r, "0x00000000");
    big_uint_load(&q, "0x00000000");
    big_uint_load(&r, "0x00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // 2 digit division (no truncation)
    big_uint_load(&a, "0x00000009_00000000");
    big_uint_load(&b, "0x00000000_00000002");
    big_uint_load(&exp_q, "0x00000004_80000000");
    big_uint_load(&exp_r, "0x00000000_00000000");
    big_uint_load(&q, "0x00000000_00000000");
    big_uint_load(&r, "0x00000000_00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // 2 digit division (no truncation)
    big_uint_load(&a, "0x00000009_00000000");
    big_uint_load(&b, "0x00000000_00000020");
    big_uint_load(&exp_q, "0x00000000_48000000");
    big_uint_load(&exp_r, "0x00000000_00000000");
    big_uint_load(&q, "0x00000000_00000000");
    big_uint_load(&r, "0x00000000_00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // large number over itself
    big_uint_load(&a, "0xffffffff_ffffffff");
    big_uint_load(&b, "0xffffffff_ffffffff");
    big_uint_load(&exp_q, "0x00000000_00000001");
    big_uint_load(&exp_r, "0x00000000_00000000");
    big_uint_load(&q, "0x00000000_00000000");
    big_uint_load(&r, "0x00000000_00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));
    
    // large number over itself + 1
    big_uint_load(&a, "0xffffffff_fffffffe");
    big_uint_load(&b, "0xffffffff_ffffffff");
    big_uint_load(&exp_q, "0x00000000_00000000");
    big_uint_load(&exp_r, "0xffffffff_fffffffe");
    big_uint_load(&q, "0x00000000_00000000");
    big_uint_load(&r, "0x00000000_00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // large number over itself - 1
    big_uint_load(&a, "0xffffffff_ffffffff");
    big_uint_load(&b, "0xffffffff_fffffffe");
    big_uint_load(&exp_q, "0x00000000_00000001");
    big_uint_load(&exp_r, "0x00000000_00000001");
    big_uint_load(&q, "0x00000000_00000000");
    big_uint_load(&r, "0x00000000_00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // 3 digit number divided by 1 digit number
    big_uint_load(&a, "0x12345678_9abcdeff_ffffffff");
    big_uint_load(&b, "0x00000000_0000000_0000fedc");
    big_uint_load(&exp_q, "0x00001249_31f596dc_f30531ec");
    big_uint_load(&exp_r, "0x00000000_0000000_0000f12f");
    big_uint_load(&q, "0x00000000_00000000_00000000");
    big_uint_load(&r, "0x00000000_00000000_00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // random number
    big_uint_load(&a, "0x00efa9af_3619a918");
    big_uint_load(&b, "0x00000ee1_a8138dfe");
    big_uint_load(&exp_q, "0x00000000_0000101a");
    big_uint_load(&exp_r, "0x00000c42_eb3d5d4c");
    big_uint_load(&q, "0x00000000_00000000");
    big_uint_load(&r, "0x00000000_00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // forced 1 by 2
    big_uint_load(&a, "0x00100000_00000000");
    big_uint_load(&b, "0x00000000_f0000000"); 
    big_uint_load(&exp_q, "0x00000000_00111111");
    big_uint_load(&exp_r, "0x00000000_10000000");
    big_uint_load(&q, "0x00000000_00000000");
    big_uint_load(&r, "0x00000000_00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // misc test
    big_uint_load(&a, "0x41763a5f_991b4b60_84285b8e");
    big_uint_load(&b, "0x126d0ba2_278b1be0_1eb138e3");
    big_uint_load(&exp_q, "0x00000000_00000000_00000003");
    big_uint_load(&exp_r, "0x0a2f1779_2279f7c0_2814b0e5");
    big_uint_load(&q, "0x00000000_00000000_00000000");
    big_uint_load(&r, "0x00000000_00000000_00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // different lengths
    big_uint_load(&a, "0x12345678_9abcdeff_ffffffff");
    big_uint_load(&b, "0x0000fedc");
    big_uint_load(&exp_q, "0x00001249_31f596dc_f30531ec");
    big_uint_load(&exp_r, "0x0000f12f");
    big_uint_load(&q, "0x00000000_00000000_00000000");
    big_uint_load(&r, "0x00000000");
    big_uint_div(&q, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // throw away quotient
    big_uint_load(&a, "0x12345678_9abcdeff_ffffffff");
    big_uint_load(&b, "0x0000fedc");
    big_uint_load(&exp_q, "0x00000000_00000000_00000000");
    big_uint_load(&exp_r, "0x0000f12f");
    big_uint_load(&q, "0x00000000_00000000_00000000");
    big_uint_load(&r, "0x00000000");
    big_uint_div(NULL, &r, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    // throw away remainder
    big_uint_load(&a, "0x12345678_9abcdeff_ffffffff");
    big_uint_load(&b, "0x0000fedc");
    big_uint_load(&exp_q, "0x00001249_31f596dc_f30531ec");
    big_uint_load(&exp_r, "0x00000000");
    big_uint_load(&q, "0x00000000_00000000_00000000");
    big_uint_load(&r, "0x00000000");
    big_uint_div(&q, NULL, &a, &b);

    expect(tester, big_uint_equals(&q, &exp_q));
    expect(tester, big_uint_equals(&r, &exp_r));

    log_tests(tester);
}

void test_big_uint_addi() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t exp;
    big_uint_t res;

    // Single digit test (no carry, no overflow)
    big_uint_load(&a, "0x00000010");
    big_uint_load(&exp, "0x00000030");
    big_uint_load(&res, "0x00000000");
    big_uint_addi(&res, &a, 0x20);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0x00000001_80000000");
    big_uint_load(&exp, "0x00000002_00000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_addi(&res, &a, 0x80000000);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0x00000001_80000000");
    big_uint_load(&exp, "0x00000002_00000000");
    big_uint_addi(&a, &a, 0x80000000);

    expect(tester, big_uint_equals(&a, &exp));

    
    log_tests(tester);
}

void test_big_uint_subi() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t exp;
    big_uint_t res;

    big_uint_load(&a, "0x00000010");
    big_uint_load(&exp, "0x00000008");
    big_uint_load(&res, "0x00000000");
    big_uint_subi(&res, &a, 0x8);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0x00000002_00000000");
    big_uint_load(&exp, "0x00000001_80000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_subi(&res, &a, 0x80000000);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0x00000002_00000000");
    big_uint_load(&exp, "0x00000001_80000000");
    big_uint_subi(&a, &a, 0x80000000);

    expect(tester, big_uint_equals(&a, &exp));

    big_uint_load(&a, "0x00000000_00000000");
    big_uint_load(&exp, "0xffffffff_ffffffff");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_subi(&res, &a, 0x1);

    expect(tester, big_uint_equals(&res, &exp));
    
    log_tests(tester);
}

void test_big_uint_multi() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t a;
    big_uint_t exp;
    big_uint_t res;

    // Single digit test (no carry, no overflow)
    big_uint_load(&a, "0x00000020");
    big_uint_load(&exp, "0x000000a0");
    big_uint_load(&res, "0x00000000");
    big_uint_multi(&res, &a, 0x5);

    expect(tester, big_uint_equals(&res, &exp));

    // Single digit test (no carry, no overflow)
    big_uint_load(&a, "0x00000012");
    big_uint_load(&exp, "0x0000017a");
    big_uint_load(&res, "0x00000000");
    big_uint_multi(&res, &a, 0x15);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (no carry, no overflow)
    big_uint_load(&a, "0x00000030_00000025");
    big_uint_load(&exp, "0x000003f0_00000309");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_multi(&res, &a, 0x15);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (carry, no overflow)
    big_uint_load(&a, "0x00000000_10000000");
    big_uint_load(&exp, "0x00000005_00000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_multi(&res, &a, 0x50);

    expect(tester, big_uint_equals(&res, &exp));

     // Multiple digit test (no carry, overflow)
    big_uint_load(&a, "0x00020000_00000000");
    big_uint_load(&exp, "0x22240000_00000000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_multi(&res, &a, 0x21112);

    expect(tester, big_uint_equals(&res, &exp));

    // Misc. tests
    big_uint_load(&a, "0x00000000_31f596dc");
    big_uint_load(&exp, "0x000031bc_9abbed10");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_multi(&res, &a, 0xfedc);

    expect(tester, big_uint_equals(&res, &exp));

    // operator assignment
    big_uint_load(&a, "0x00000000_31f596dc");
    big_uint_load(&exp, "0x000031bc_9abbed10");
    big_uint_multi(&a, &a, 0xfedc);

    expect(tester, big_uint_equals(&a, &exp));
    
    log_tests(tester);
}

void test_big_uint_log2() {
     // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    big_uint_t x;
    uint32_t expected;

    // Log_2 bit tests
    // Test 1
    big_uint_load(&x, "0x00000001");
    expected = 0;

    expect(tester, big_uint_log2(&x, LOG_2_BIT) == expected);

    // Test 2
    big_uint_load(&x, "0x0000000f");
    expected = 3;

    expect(tester, big_uint_log2(&x, LOG_2_BIT) == expected);

    // Test 3
    big_uint_load(&x, "0x00000001_00000000");
    expected = 32;

    expect(tester, big_uint_log2(&x, LOG_2_BIT) == expected);

    // Test 4
    big_uint_load(&x, "0x10000001_10000000");
    expected = 60;

    expect(tester, big_uint_log2(&x, LOG_2_BIT) == expected);

    // Log_2 byte tests
    // Test 1
    big_uint_load(&x, "0x00000001");
    expected = 0;

    expect(tester, big_uint_log2(&x, LOG_2_LIMB) == expected);

    // Test 2
    big_uint_load(&x, "0x0000000f");
    expected = 0;

    expect(tester, big_uint_log2(&x, LOG_2_LIMB) == expected);

    // Test 3
    big_uint_load(&x, "0x00000001_00000000");
    expected = 1;

    expect(tester, big_uint_log2(&x, LOG_2_LIMB) == expected);

    // Test 4
    big_uint_load(&x, "0x00000000_10000001_10000000");
    expected = 1;

    expect(tester, big_uint_log2(&x, LOG_2_LIMB) == expected);

    log_tests(tester);
}

void test_big_uint_gcd() {
    testing_logger_t *tester = create_tester();
    big_uint_t a, b;
    big_uint_t exp, res;

    // relatively prime example
    big_uint_load(&a, "0x00000005");
    big_uint_load(&b, "0x00000007");
    big_uint_load(&exp, "0x00000001");
    big_uint_load(&res, "0x00000000");
    big_uint_gcd(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // non-relatively prime
    big_uint_load(&a, "0x00000012");
    big_uint_load(&b, "0x00000015");
    big_uint_load(&exp, "0x00000003");
    big_uint_load(&res, "0x00000000");
    big_uint_gcd(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // padded 0, non-relatively prime
    big_uint_load(&a, "0x00000000_8ab6d43d");
    big_uint_load(&b, "0x00000000_ab43d5eb");
    big_uint_load(&exp, "0x00000000_0000000b");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_gcd(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // multi-digit, non-relatively prime
    big_uint_load(&a, "0xffe352fa_8ab6d43d");
    big_uint_load(&b, "0xc78d5a01_ab43d5eb");
    big_uint_load(&exp, "0x00000000_00000007");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_gcd(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

     // Multiple digit test (no carry, overflow)
    big_uint_load(&a, "0x00020000_00010000");
    big_uint_load(&b, "0x00000000_02000000");
    big_uint_load(&exp, "0x00000000_00010000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_gcd(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (no carry, overflow)
    big_uint_load(&a, "0x00000025_00300000");
    big_uint_load(&b, "0x00000013_11000000");
    big_uint_load(&exp, "0x00000000_00100000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_gcd(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Multiple digit test (carry, overflow)
    big_uint_load(&a, "0x00000000_10000000");
    big_uint_load(&b, "0x00001100_f0025000");
    big_uint_load(&exp, "0x00000000_00001000");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_gcd(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // Misc. tests
    big_uint_load(&a, "0x00000000_31f596dc");
    big_uint_load(&b, "0x00000000_0000fedc");
    big_uint_load(&exp, "0x00000000_00000004");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_gcd(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    big_uint_load(&a, "0x000087b2_799af391");
    big_uint_load(&b, "0x0000a941_69aca1e3");
    big_uint_load(&exp, "0x00000000_00000001");
    big_uint_load(&res, "0x00000000_00000000");
    big_uint_gcd(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    // different lengths
    big_uint_load(&a, "0x00000000_10000000");
    big_uint_load(&b, "0x00001100_f0025000");
    big_uint_load(&exp, "0x00001000");
    big_uint_load(&res, "0x00000000");
    big_uint_gcd(&res, &a, &b);

    expect(tester, big_uint_equals(&res, &exp));

    log_tests(tester);
}

void test_big_uint_gcd_extended() {
	testing_logger_t *tester = create_tester();
    big_uint_t a, b;
	big_uint_t exp_x, exp_y;
    big_uint_t res_x, res_y;

	big_uint_load(&a, "0x0000008f");
	big_uint_load(&b, "0x000000ea");
	big_uint_load(&exp_x, "0xfffffffd");
	big_uint_load(&exp_y, "0x00000005");
    big_uint_load(&res_x, "0x00000000");
	big_uint_load(&res_y, "0x00000000");

	big_uint_gcd_extended(&res_x, &res_y, &a, &b);

	expect(tester, big_uint_equals(&res_x, &exp_x));
	expect(tester, big_uint_equals(&res_y, &exp_y));

	big_uint_load(&a, "0x2b487392");
	big_uint_load(&b, "0xd2c60104");
	big_uint_load(&exp_x, "0x0564f14f");
	big_uint_load(&exp_y, "0xe5bb484b");
    big_uint_load(&res_x, "0x00000000");
	big_uint_load(&res_y, "0x00000000");

    big_uint_gcd_extended(&res_x, &res_y, &a, &b);

	expect(tester, big_uint_equals(&res_x, &exp_x));
	expect(tester, big_uint_equals(&res_y, &exp_y));

	big_uint_load(&a, "0x00000000_30bfb01a");
	big_uint_load(&b, "0x00000000_987de21e");
	big_uint_load(&exp_x, "0xffffffff_f6bd5ebe");
	big_uint_load(&exp_y, "0x00000000_1cf7999b");
    big_uint_load(&res_x, "0x00000000_00000000");
	big_uint_load(&res_y, "0x00000000_00000000");

	big_uint_gcd_extended(&res_x, &res_y, &a, &b);

	expect(tester, big_uint_equals(&res_x, &exp_x));
	expect(tester, big_uint_equals(&res_y, &exp_y));

	big_uint_load(&a, "0x0e8b90bd_220b8c80");
	big_uint_load(&b, "0x6ec46fd6_e7ee1360");
	big_uint_load(&exp_x, "0x0021b929_43ebb88f");
	big_uint_load(&exp_y, "0xfeff2f07_f8541193");
    big_uint_load(&res_x, "0x00000000_00000000");
	big_uint_load(&res_y, "0x00000000_00000000");

	big_uint_gcd_extended(&res_x, &res_y, &a, &b);

	expect(tester, big_uint_equals(&res_x, &exp_x));
	expect(tester, big_uint_equals(&res_y, &exp_y));

	big_uint_load(&a, "0x00000000_cec6b8e4");
	big_uint_load(&b, "0x7bec5ab5_e87e8fcf");
	big_uint_load(&exp_x, "0xffffffff_f2e4bc35");
	big_uint_load(&exp_y, "0x07dad8bf_603c39da");
    big_uint_load(&res_x, "0x00000000_00000000");
	big_uint_load(&res_y, "0x00000000_00000000");

	big_uint_gcd_extended(&res_x, &res_y, &a, &b);

	expect(tester, big_uint_equals(&res_x, &exp_x));
	expect(tester, big_uint_equals(&res_y, &exp_y));

	big_uint_load(&a, "0x0ab1a3c2_f61a4999");
	big_uint_load(&b, "0x00000000_083a6d6c");
	big_uint_load(&exp_x, "0x00000000_0336ce65");
	big_uint_load(&exp_y, "0xfbd2a1ae_9bcddfcb");
    big_uint_load(&res_x, "0x00000000_00000000");
	big_uint_load(&res_y, "0x00000000_00000000");

	big_uint_gcd_extended(&res_x, &res_y, &a, &b);

	expect(tester, big_uint_equals(&res_x, &exp_x));
	expect(tester, big_uint_equals(&res_y, &exp_y));

	big_uint_load(&a, "0xd6cfbac0_f2dcfe01_ab2a4b8d");
	big_uint_load(&b, "0x41763a5f_991b4b60_84285b8e");
	big_uint_load(&exp_x, "0x016c1fa8_ee5ca7b3_8afa8433");
	big_uint_load(&exp_y, "0xfb552303_6be085f9_ea8238e3");
    big_uint_load(&res_x, "0x00000000_00000000_00000000");
	big_uint_load(&res_y, "0x00000000_00000000_00000000");

	big_uint_gcd_extended(&res_x, &res_y, &a, &b);

	expect(tester, big_uint_equals(&res_x, &exp_x));
	expect(tester, big_uint_equals(&res_y, &exp_y));

	big_uint_load(&a, "0x5eda613c_268411c6_987e7270");
	big_uint_load(&b, "0xc6f11378_4d56c2b4_a2799234");
	big_uint_load(&exp_x, "0xfd1ea5e9_3a87833e_0f5901bd");
	big_uint_load(&exp_y, "0x060a7f7c_08577482_d35e08b6");
    big_uint_load(&res_x, "0x00000000_00000000_00000000");
	big_uint_load(&res_y, "0x00000000_00000000_00000000");

	big_uint_gcd_extended(&res_x, &res_y, &a, &b);

	expect(tester, big_uint_equals(&res_x, &exp_x));
	expect(tester, big_uint_equals(&res_y, &exp_y));

	big_uint_load(&a, "0x00000000_00000000_2adaa46f");
	big_uint_load(&b, "0x00000000_daff9a2e_7f6758e3");
	big_uint_load(&exp_x, "0x00000000_00000000_09c35db4");
	big_uint_load(&exp_y, "0xffffffff_ce1b6a35_19c3216b");
    big_uint_load(&res_x, "0x00000000_00000000_00000000");
	big_uint_load(&res_y, "0x00000000_00000000_00000000");

	big_uint_gcd_extended(&res_x, &res_y, &a, &b);

	expect(tester, big_uint_equals(&res_x, &exp_x));
	expect(tester, big_uint_equals(&res_y, &exp_y));

	big_uint_load(&a, "0x00000000_00000000_fcb90859");
	big_uint_load(&b, "0x00000000_00000000_8221014d");
	big_uint_load(&exp_x, "0xffffffff_ffffffff_e5e6a3b3");
	big_uint_load(&exp_y, "0x00000000_00000000_32afd6de");
    big_uint_load(&res_x, "0x00000000_00000000_00000000");
	big_uint_load(&res_y, "0x00000000_00000000_00000000");

	big_uint_gcd_extended(&res_x, &res_y, &a, &b);

	expect(tester, big_uint_equals(&res_x, &exp_x));
	expect(tester, big_uint_equals(&res_y, &exp_y));

	log_tests(tester);
}

int main() {
    test_big_uint_init();
    test_big_uint_count_limbs();
    test_big_uint_parse();
    test_big_uint_load();
    test_big_uint_create();
    test_big_uint_loadi();
    test_big_uint_copy();

    test_big_uint_sprint();
    test_big_uint_spprint();

    test_big_uint_equals();
    test_big_uint_cmp();
    test_big_uint_max();
    test_big_uint_min();
    test_big_uint_is_zero();
    test_big_uint_choose();
    
    test_big_uint_or();
    test_big_uint_and();
    test_big_uint_xor();

    test_big_uint_shr();
    test_big_uint_shl();

    test_big_uint_andi();
    test_big_uint_ori();
    test_big_uint_xori();

    test_big_uint_add();
    test_big_uint_sub();
    test_big_uint_mult();
    test_big_uint_div();

    test_big_uint_addi();
    test_big_uint_subi();
    test_big_uint_multi();

    test_big_uint_log2();

    test_big_uint_gcd();
    test_big_uint_gcd_extended();

    return 0;
}
