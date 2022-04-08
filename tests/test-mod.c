#include "mod.h"

#include "big-uint.h"
#include <stdlib.h>
#include <stdio.h>
#include "testing-logger.h"

void test_mod_big_uint() {
	testing_logger_t *tester = create_tester();
	big_uint_t a, p;
	big_uint_t exp, res;

	// Test 1
	big_uint_load(&a, "0xc386bbc4");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000006");
	big_uint_load(&res, "0x00000000");

	mod_big_uint(&res, &a, &p);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 2
	big_uint_load(&a, "0x1e2feb89_414c343c");
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000008");
	big_uint_load(&res, "0x00000000_00000000");

	mod_big_uint(&res, &a, &p);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 3
	big_uint_load(&a, "0x35bf992d_c9e9c616_612e7696");
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000000_0000000c");
	big_uint_load(&res, "0x00000000_00000000_00000000");

	mod_big_uint(&res, &a, &p);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 4
	big_uint_load(&a, "0x63ca828d_d5f4b3b2");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x26cf9152_89b5ff93");
	big_uint_load(&res, "0x00000000_00000000");

	mod_big_uint(&res, &a, &p);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 5
	big_uint_load(&a, "0xc4647159_c324c985_9b810e76");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_07881c97_401b0619");
	big_uint_load(&res, "0x00000000_00000000_00000000");

	mod_big_uint(&res, &a, &p);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 6
	big_uint_load(&a, "0x51431193_e6c3f339_1a2b8f1f");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_30be2a1b_5e721204");
	big_uint_load(&res, "0x00000000_00000000_00000000");

	mod_big_uint(&res, &a, &p);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 7
	big_uint_load(&a, "0x8a9a021e_a648a7dd_06839eb9_05b6e6e3");
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_00000000_0ee451e6_7971d668");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");

	mod_big_uint(&res, &a, &p);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 8
	big_uint_load(&a, "0xe1988ad9_f06c144a");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x6e995ed1_a8491965");
	big_uint_load(&res, "0x00000000_00000000");

	mod_big_uint(&res, &a, &p);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 9
	big_uint_load(&a, "0xf8130c42_37730edf_afbd67f9");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_49802c63_62b9fd71");
	big_uint_load(&res, "0x00000000_00000000_00000000");

	mod_big_uint(&res, &a, &p);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 10
	big_uint_load(&a, "0x8712b8bc_076f3787_b9d179e0");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_5c43303f_a8844e23");
	big_uint_load(&res, "0x00000000_00000000_00000000");

	mod_big_uint(&res, &a, &p);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 11
	big_uint_load(&a, "0xad45f23d_3b1a11df_587fd280_3bab6c39");
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_00000000_419a03ab_2c50ed86");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");

	mod_big_uint(&res, &a, &p);

	expect(tester, big_uint_equals(&res, &exp));

	log_tests(tester);
}

int main() {
	// Calling all tests:
	test_mod_big_uint();

	return 1;
}
