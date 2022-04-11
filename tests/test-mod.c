#include "mod.h"

#include "big-uint.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "testing-logger.h"

void test_mod_init() {
	testing_logger_t *tester = create_tester();
	big_uint_t p;
	big_uint_t exp_r;
	mod_t res;

	// Test 1
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp_r, "0x00000000_13b13b13_b13b13b1");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == 2 * res.k + 1
	);

	// Test 2
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_13b13b13_b13b13b1");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == 2 * res.k + 1
	);

	// Test 3
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000000_13b13b13_b13b13b1");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == 2 * res.k + 1
	);

	// Test 4
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp_r, "0x00000000_00000000_00000004_32b56f64_2c6cf995");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == 2 * res.k + 1
	);

	// Test 5
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000004_32b56f64_2c6cf995");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == 2 * res.k + 1
	);

	// Test 6
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000004_32b56f64_2c6cf995");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == 2 * res.k + 1
	);

	// Test 7
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000000_00000000_00000004_32b56f64_2c6cf995");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == 2 * res.k + 1
	);

	// Test 8
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp_r, "0x00000000_00000000_00000002_39e4f021_bb40ef66");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == 2 * res.k + 1
	);

	// Test 9
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000002_39e4f021_bb40ef66");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == 2 * res.k + 1
	);

	// Test 10
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000002_39e4f021_bb40ef66");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == 2 * res.k + 1
	);

	// Test 11
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000000_00000000_00000002_39e4f021_bb40ef66");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == 2 * res.k + 1
	);

	log_tests(tester);
}

void test_mod_big_uint() {
	testing_logger_t *tester = create_tester();
	big_uint_t a, p;
	big_uint_t exp, res; mod_t mod;

	// Test 1
	big_uint_load(&a, "0xc386bbc4");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000006");
	big_uint_load(&res, "0x00000000");
	mod_create(&mod, &p);

	mod_big_uint(&res, &a, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 2
	big_uint_load(&a, "0x1e2feb89_414c343c");
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000008");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_big_uint(&res, &a, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 3
	big_uint_load(&a, "0x35bf992d_c9e9c616_612e7696");
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000000_0000000c");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_big_uint(&res, &a, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 4
	big_uint_load(&a, "0x63ca828d_d5f4b3b2");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x26cf9152_89b5ff93");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_big_uint(&res, &a, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 5
	big_uint_load(&a, "0xc4647159_c324c985_9b810e76");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_07881c97_401b0619");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_big_uint(&res, &a, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 6
	big_uint_load(&a, "0x51431193_e6c3f339_1a2b8f1f");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_30be2a1b_5e721204");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_big_uint(&res, &a, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 7
	big_uint_load(&a, "0x8a9a021e_a648a7dd_06839eb9_05b6e6e3");
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_00000000_0ee451e6_7971d668");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_big_uint(&res, &a, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 8
	big_uint_load(&a, "0xe1988ad9_f06c144a");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x6e995ed1_a8491965");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_big_uint(&res, &a, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 9
	big_uint_load(&a, "0xf8130c42_37730edf_afbd67f9");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_49802c63_62b9fd71");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_big_uint(&res, &a, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 10
	big_uint_load(&a, "0x8712b8bc_076f3787_b9d179e0");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_5c43303f_a8844e23");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_big_uint(&res, &a, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 11
	big_uint_load(&a, "0xad45f23d_3b1a11df_587fd280_3bab6c39");
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_00000000_419a03ab_2c50ed86");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_big_uint(&res, &a, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	log_tests(tester);
}

void test_mod_add() {
	testing_logger_t *tester = create_tester();
	big_uint_t a, b, p;
	big_uint_t exp, res; mod_t mod;

	// Test 1
	big_uint_load(&a, "0x00000008");
	big_uint_load(&b, "0x00000002");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x0000000a");
	big_uint_load(&res, "0x00000000");
	mod_create(&mod, &p);

	mod_add(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 2
	big_uint_load(&a, "0x00000000_00000009");
	big_uint_load(&b, "0x00000000_00000006");
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000002");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_add(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 3
	big_uint_load(&a, "0x00000000_00000000_0000000b");
	big_uint_load(&b, "0x00000000_00000000_00000003");
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000000_00000001");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_add(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 4
	big_uint_load(&a, "0x1531dba6_d9a9056f");
	big_uint_load(&b, "0x00fa4545_70594719");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x162c20ec_4a024c88");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_add(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 5
	big_uint_load(&a, "0x00000000_1761d93a_15aca0a2");
	big_uint_load(&b, "0x00000000_23c88a71_587d96ff");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_3b2a63ab_6e2a37a1");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_add(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 6
	big_uint_load(&a, "0x00000000_24489e86_b96a983e");
	big_uint_load(&b, "0x00000000_1ba0bdd3_f70fa630");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_02ee6b1f_643b8a4f");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_add(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 7
	big_uint_load(&a, "0x00000000_00000000_377a29a2_cccaa39b");
	big_uint_load(&b, "0x00000000_00000000_0e7d83b5_b7ca57e2");
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_00000000_08fcbc1d_3856475e");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_add(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 8
	big_uint_load(&a, "0x1aee108e_49c87f15");
	big_uint_load(&b, "0x6bb9d044_33068226");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x13a8b4ca_34ac0656");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_add(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 9
	big_uint_load(&a, "0x00000000_28d8c9e3_5c8117b3");
	big_uint_load(&b, "0x00000000_054a42fe_fb12c0f0");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_2e230ce2_5793d8a3");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_add(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 10
	big_uint_load(&a, "0x00000000_3008c6e5_3287b533");
	big_uint_load(&b, "0x00000000_48874bdd_d0f7ba17");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_0590e6ba_bb5c7465");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_add(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 11
	big_uint_load(&a, "0x00000000_00000000_53585734_e6df845a");
	big_uint_load(&b, "0x00000000_00000000_0e56e9db_03e8846e");
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_00000000_61af410f_eac808c8");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_add(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	log_tests(tester);
}

void test_mod_sub() {
	testing_logger_t *tester = create_tester();
	big_uint_t a, b, p;
	big_uint_t exp, res; mod_t mod;

	// Test 1
	big_uint_load(&a, "0x00000000");
	big_uint_load(&b, "0x0000000a");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000003");
	big_uint_load(&res, "0x00000000");
	mod_create(&mod, &p);

	mod_sub(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 2
	big_uint_load(&a, "0x00000000_00000006");
	big_uint_load(&b, "0x00000000_0000000c");
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000007");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_sub(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 3
	big_uint_load(&a, "0x00000000_00000000_00000007");
	big_uint_load(&b, "0x00000000_00000000_00000001");
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000000_00000006");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sub(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 4
	big_uint_load(&a, "0x3c4e1d70_32db813f");
	big_uint_load(&b, "0x39e9622d_dbe9eb3c");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x0264bb42_56f19603");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_sub(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 5
	big_uint_load(&a, "0x00000000_06137097_6d354a3a");
	big_uint_load(&b, "0x00000000_15300f57_0fedb4d8");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_2dde527b_a9864981");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sub(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 6
	big_uint_load(&a, "0x00000000_2a2cf1bc_037bfc22");
	big_uint_load(&b, "0x00000000_1d4a0f70_594b4417");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_0ce2e24b_aa30b80b");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sub(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 7
	big_uint_load(&a, "0x00000000_00000000_1206ec84_55bcab48");
	big_uint_load(&b, "0x00000000_00000000_1facb676_08fc35fe");
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_00000000_2f552749_98ff2969");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sub(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 8
	big_uint_load(&a, "0x0c250a03_e023033d");
	big_uint_load(&b, "0x11ca2ae3_8fe6d25e");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x6d5a0b28_985f2bc4");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_sub(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 9
	big_uint_load(&a, "0x00000000_2dfbfdb1_defa5f21");
	big_uint_load(&b, "0x00000000_6c61d9a6_fc8a0649");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_34995013_2a9353bd");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sub(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 10
	big_uint_load(&a, "0x00000000_04f06966_95e5722f");
	big_uint_load(&b, "0x00000000_4c8f6d94_2aad363b");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_2b6027da_b35b36d9");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sub(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 11
	big_uint_load(&a, "0x00000000_00000000_5ffbbd9a_bedc204c");
	big_uint_load(&b, "0x00000000_00000000_2006cc6a_c1230093");
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_00000000_3ff4f12f_fdb91fb9");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sub(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	log_tests(tester);
}

void test_mod_mult() {
	testing_logger_t *tester = create_tester();
	big_uint_t a, b, p;
	big_uint_t exp, res;
	mod_t mod;

	// Test 1
	big_uint_load(&a, "0x00000003");
	big_uint_load(&b, "0x0000000a");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000004");
	big_uint_load(&res, "0x00000000");
	mod_create(&mod, &p);

	mod_mult(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 2
	big_uint_load(&a, "0x00000000_00000007");
	big_uint_load(&b, "0x00000000_00000003");
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000008");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_mult(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 3
	big_uint_load(&a, "0x00000000_00000000_00000005");
	big_uint_load(&b, "0x00000000_00000000_00000009");
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000000_00000006");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_mult(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 4
	big_uint_load(&a, "0x0fd229d7_50b9169b");
	big_uint_load(&b, "0x2b711343_220d672b");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x2bfea46b_2a04608d");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_mult(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 5
	big_uint_load(&a, "0x00000000_085d8597_859937c4");
	big_uint_load(&b, "0x00000000_0252c228_2e6c6735");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_008e862f_9dc7fe4b");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_mult(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 6
	big_uint_load(&a, "0x00000000_04d7ee10_885d26e6");
	big_uint_load(&b, "0x00000000_2e3afc03_b27c3735");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_0e4e6cb3_fb58d6ed");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_mult(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 7
	big_uint_load(&a, "0x00000000_00000000_069b0316_81d24604");
	big_uint_load(&b, "0x00000000_00000000_2086ccd2_9f820d6b");
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_00000000_177590f0_22d2fd5c");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_mult(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 8
	big_uint_load(&a, "0x297a21d7_6bc78bf5");
	big_uint_load(&b, "0x301ba988_0a3efb80");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x4cceb8e3_a2cd6fc9");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_mult(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 9
	big_uint_load(&a, "0x00000000_67dd4e30_e02acd3b");
	big_uint_load(&b, "0x00000000_3e859b93_a2743a06");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_46163aa6_7cc90739");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_mult(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 10
	big_uint_load(&a, "0x00000000_69ccbf03_e15253e0");
	big_uint_load(&b, "0x00000000_4393b6e9_368d7999");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_199c211a_9a6a8d05");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_mult(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 11
	big_uint_load(&a, "0x00000000_00000000_185ce898_5d508b67");
	big_uint_load(&b, "0x00000000_00000000_05bc51e1_4cbe9d72");
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_00000000_0385a208_13d42405");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_mult(&res, &a, &b, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 12a
	// Operator assignment
	big_uint_load(&a, "0x0000000c");
	big_uint_load(&b, "0x0000000a");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000003");
	mod_create(&mod, &p);

	mod_mult(&a, &a, &b, &mod);

	expect(tester, big_uint_equals(&a, &exp));

	// Test 13a
	// Operator assignment
	big_uint_load(&a, "0x00000001");
	big_uint_load(&b, "0x00000008");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000008");
	mod_create(&mod, &p);

	mod_mult(&b, &a, &b, &mod);

	expect(tester, big_uint_equals(&b, &exp));

	// Test 14a
	// Operator assignment
	big_uint_load(&a, "0x1c823d9e_74b31bfb");
	big_uint_load(&b, "0x32e33b79_2bb2c64e");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x2681f5e3_3a046890");
	mod_create(&mod, &p);

	mod_mult(&a, &a, &b, &mod);

	expect(tester, big_uint_equals(&a, &exp));

	// Test 15a
	// Operator assignment
	big_uint_load(&a, "0x11b1a79a_e8f6188f");
	big_uint_load(&b, "0x2f7818b5_df8dbd9b");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x37c03da0_c4fcf0bb");
	mod_create(&mod, &p);

	mod_mult(&b, &a, &b, &mod);

	expect(tester, big_uint_equals(&b, &exp));

	// Test 16a
	// Operator assignment
	big_uint_load(&a, "0x47e1a38b_d1ea0418");
	big_uint_load(&b, "0x5c47577b_3f12d68e");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x2eab600b_49a1380f");
	mod_create(&mod, &p);

	mod_mult(&a, &a, &b, &mod);

	expect(tester, big_uint_equals(&a, &exp));

	// Test 17a
	// Operator assignment
	big_uint_load(&a, "0x0a826695_4e896a65");
	big_uint_load(&b, "0x4dd83958_b39b989c");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x3acfbfda_1e039f78");
	mod_create(&mod, &p);

	mod_mult(&b, &a, &b, &mod);

	expect(tester, big_uint_equals(&b, &exp));

	log_tests(tester);
}

int main() {
	// Calling all tests:
	test_mod_init();
	test_mod_big_uint();
	test_mod_add();
	test_mod_sub();
	test_mod_mult();

	return 1;
}
