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
		res.r->len == res.k + 1
	);

	// Test 2
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_13b13b13_b13b13b1");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == res.k + 1
	);

	// Test 3
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000000_13b13b13_b13b13b1");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == res.k + 1
	);

	// Test 4
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp_r, "0x00000000_00000000_00000004_32b56f64_2c6cf995");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == res.k + 1
	);

	// Test 5
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000004_32b56f64_2c6cf995");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == res.k + 1
	);

	// Test 6
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000004_32b56f64_2c6cf995");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == res.k + 1
	);

	// Test 7
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000000_00000000_00000004_32b56f64_2c6cf995");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == res.k + 1
	);

	// Test 8
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp_r, "0x00000000_00000000_00000002_39e4f021_bb40ef66");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == res.k + 1
	);

	// Test 9
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000002_39e4f021_bb40ef66");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == res.k + 1
	);

	// Test 10
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000002_39e4f021_bb40ef66");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == res.k + 1
	);

	// Test 11
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp_r, "0x00000000_00000000_00000000_00000000_00000000_00000000_00000002_39e4f021_bb40ef66");

	mod_create(&res, &p);

	expect(tester, 
		res.p == &p &&
		big_uint_equals(res.r, &exp_r) &&
		res.r->len == res.k + 1
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
	big_uint_t exp, res;
	mod_t mod;

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
	big_uint_t exp, res;
	mod_t mod;

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

	// Test 14c
	// Operator assignment
	big_uint_load(&a, "0x00000008");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x0000000c");
	mod_create(&mod, &p);

	mod_mult(&a, &a, &a, &mod);

	expect(tester, big_uint_equals(&a, &exp));

	// Test 15a
	// Operator assignment
	big_uint_load(&a, "0x1e1c88fd_5d2f470d");
	big_uint_load(&b, "0x3637528e_459e888f");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x000bcd03_480eed22");
	mod_create(&mod, &p);

	mod_mult(&a, &a, &b, &mod);

	expect(tester, big_uint_equals(&a, &exp));

	// Test 16a
	// Operator assignment
	big_uint_load(&a, "0x32ffd03d_4eac98d6");
	big_uint_load(&b, "0x10b08fbe_966a4759");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x21be38c2_06b2a976");
	mod_create(&mod, &p);

	mod_mult(&b, &a, &b, &mod);

	expect(tester, big_uint_equals(&b, &exp));

	// Test 17c
	// Operator assignment
	big_uint_load(&a, "0x39e326aa_7204fa0c");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x0685b086_9a27f3df");
	mod_create(&mod, &p);

	mod_mult(&a, &a, &a, &mod);

	expect(tester, big_uint_equals(&a, &exp));

	// Test 18a
	// Operator assignment
	big_uint_load(&a, "0x53c617eb_0a826695");
	big_uint_load(&b, "0x1174a0d9_d3b07116");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x0211b23c_85a7e52e");
	mod_create(&mod, &p);

	mod_mult(&a, &a, &b, &mod);

	expect(tester, big_uint_equals(&a, &exp));

	// Test 19a
	// Operator assignment
	big_uint_load(&a, "0x3ebebe3e_179030da");
	big_uint_load(&b, "0x3eefe734_4d84e990");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x106f1228_80ace0ab");
	mod_create(&mod, &p);

	mod_mult(&b, &a, &b, &mod);

	expect(tester, big_uint_equals(&b, &exp));

	// Test 20c
	// Operator assignment
	big_uint_load(&a, "0x12840ea1_66daa365");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x128931a5_a45edbc7");
	mod_create(&mod, &p);

	mod_mult(&a, &a, &a, &mod);

	expect(tester, big_uint_equals(&a, &exp));

	log_tests(tester);
}

void test_mod_exp() {
	testing_logger_t *tester = create_tester();
	big_uint_t x, n, p;
	big_uint_t res, exp;
	mod_t mod;

	// Test 1
	big_uint_load(&x, "0x00000009");
	big_uint_load(&n, "0x00000008");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000003");
	big_uint_load(&res, "0x00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 2
	big_uint_load(&x, "0x00000000_00000007");
	big_uint_load(&n, "0x00000000_0000000c");
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000001");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 3
	big_uint_load(&x, "0x00000000_00000000_00000005");
	big_uint_load(&n, "0x00000000_00000000_00000005");
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000000_00000005");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 4
	big_uint_load(&x, "0x0fa33630_d643f4fa");
	big_uint_load(&n, "0x2d9b8ebf_3497553c");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x365fe7d2_14819e09");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 5
	big_uint_load(&x, "0x00000000_34d597f2_37cd6452");
	big_uint_load(&n, "0x00000000_03487978_bf7d1d57");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_0aa97b96_d71d6118");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 6
	big_uint_load(&x, "0x00000000_2d92d626_4d16a0e0");
	big_uint_load(&n, "0x00000000_1522f08c_ef4faec1");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_1861a50f_1a1724aa");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 7
	big_uint_load(&x, "0x00000000_00000000_2f4ac31e_e7b810a9");
	big_uint_load(&n, "0x00000000_00000000_20ae3839_1de4d5a8");
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_00000000_185b2160_b9201a2e");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 8
	big_uint_load(&x, "0x05a351c3_15d46419");
	big_uint_load(&n, "0x3bc8996b_16d8e80e");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x6e65ab35_3f131251");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 9
	big_uint_load(&x, "0x00000000_34ef13b6_0d657518");
	big_uint_load(&n, "0x00000000_2dfdbe64_21e8769f");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_65a6ee15_b1e7cc14");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 10
	big_uint_load(&x, "0x00000000_2afb0672_fb634c5d");
	big_uint_load(&n, "0x00000000_14a3b0c2_cc1bd7a8");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_54c239c8_4e02ace6");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 11
	big_uint_load(&x, "0x00000000_00000000_2e98e02c_086ea93f");
	big_uint_load(&n, "0x00000000_00000000_5d9ef5b8_85dcf64c");
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_00000000_60fc9564_eefa2917");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 12a
	// Operator assignment
	big_uint_load(&x, "0x0000000a");
	big_uint_load(&n, "0x00000009");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x0000000c");
	mod_create(&mod, &p);

	mod_exp(&x, &x, &n, &mod);

	expect(tester, big_uint_equals(&x, &exp));

	// Test 13a
	// Operator assignment
	big_uint_load(&x, "0x26ec1dce_a8d65389");
	big_uint_load(&n, "0x291ac5d3_1f19f2ea");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x156f4d31_a5b59cbb");
	mod_create(&mod, &p);

	mod_exp(&x, &x, &n, &mod);

	expect(tester, big_uint_equals(&x, &exp));

	// Test 14a
	// Operator assignment
	big_uint_load(&x, "0x70293815_5351d2c1");
	big_uint_load(&n, "0x014893db_3d388ad8");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x22f1ea50_c2da3f27");
	mod_create(&mod, &p);

	mod_exp(&x, &x, &n, &mod);

	expect(tester, big_uint_equals(&x, &exp));

	log_tests(tester);
}

void test_mod_inv() {
	testing_logger_t *tester = create_tester();
	big_uint_t x, p;
	big_uint_t res, exp;
	mod_t mod;

	// Test 1
	big_uint_load(&x, "0x00000007");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000002");
	big_uint_load(&res, "0x00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 2
	big_uint_load(&x, "0x00000000_00000003");
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000009");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 3
	big_uint_load(&x, "0x00000000_00000000_0000000a");
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000000_00000004");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 4
	big_uint_load(&x, "0x01c9f446_d00bea89");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x097b4b47_ab8f189c");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 5
	big_uint_load(&x, "0x00000000_03434130_b232a312");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_35c0a633_d163a9a7");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 6
	big_uint_load(&x, "0x00000000_10ff0c63_46c0c17f");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_034c1b6b_6dfe0758");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 7
	big_uint_load(&x, "0x00000000_00000000_1751ad47_1c108de9");
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_00000000_1e296d58_29b4c27e");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 8
	big_uint_load(&x, "0x0aa6814a_133e735d");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x18df88ec_5e5af136");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 9
	big_uint_load(&x, "0x00000000_2c6fcd31_39fcd7f1");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_52660294_7b6efce9");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 10
	big_uint_load(&x, "0x00000000_14070fa7_d35f9534");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_5452fc05_a9ea3659");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 11
	big_uint_load(&x, "0x00000000_00000000_51944067_5b2c233b");
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_00000000_11c81c3c_5c1b7a98");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	log_tests(tester);
}

void test_mod_neg() {
	testing_logger_t *tester = create_tester();
	big_uint_t x, p;
	big_uint_t res, exp;
	mod_t mod;

	// Test 1
	big_uint_load(&x, "0x00000004");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000009");
	big_uint_load(&res, "0x00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 2
	big_uint_load(&x, "0x00000000_0000000b");
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000002");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 3
	big_uint_load(&x, "0x00000000_00000000_0000000a");
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000000_00000003");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 4
	big_uint_load(&x, "0x23acb67c_9eb70c14");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x194e3abe_ad87a80b");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 5
	big_uint_load(&x, "0x00000000_2448e3de_2c1bfe22");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_18b20d5d_2022b5fd");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 6
	big_uint_load(&x, "0x00000000_360ffaf0_674c6bda");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_06eaf64a_e4f24845");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 7
	big_uint_load(&x, "0x00000000_00000000_210dcce3_8e2ae831");
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_00000000_1bed2457_be13cbee");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 8
	big_uint_load(&x, "0x0297c0d6_9aff956c");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x70676b31_ad236579");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 9
	big_uint_load(&x, "0x00000000_1bd598e6_889657b0");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_57299321_bf8ca335");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 10
	big_uint_load(&x, "0x00000000_5ecc0a42_a7cf7c70");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_143321c5_a0537e75");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 11
	big_uint_load(&x, "0x00000000_00000000_16d9bd17_b3d4c202");
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_00000000_5c256ef0_944e38e3");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 12
	big_uint_load(&x, "0x00000007");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000006");
	mod_create(&mod, &p);

	mod_neg(&x, &x, &mod);

	expect(tester, big_uint_equals(&x, &exp));

	// Test 13
	big_uint_load(&x, "0x36cb49e9_90e2fd5a");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x062fa751_bb5bb6c5");
	mod_create(&mod, &p);

	mod_neg(&x, &x, &mod);

	expect(tester, big_uint_equals(&x, &exp));

	// Test 14
	big_uint_load(&x, "0x27e1b5b0_fe778f3b");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x4b1d7657_49ab6baa");
	mod_create(&mod, &p);

	mod_neg(&x, &x, &mod);

	expect(tester, big_uint_equals(&x, &exp));

	log_tests(tester);
}

void test_mod_sqrt() {
	testing_logger_t *tester = create_tester();
	big_uint_t x, p;
	big_uint_t res, exp;
	mod_t mod;

	// Test 1
	big_uint_load(&x, "0x00000004");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x0000000b");
	big_uint_load(&res, "0x00000000");
	mod_create(&mod, &p);

	mod_sqrt(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// // Test 2
	// big_uint_load(&x, "0x00000000_00000001");
	// big_uint_load(&p, "0x00000000_0000000d");
	// big_uint_load(&exp, "0x00000000_00000001");
	// big_uint_load(&res, "0x00000000_00000000");
	// mod_create(&mod, &p);

	// mod_sqrt(&res, &x, &mod);

	// expect(tester, big_uint_equals(&res, &exp));

	// // Test 3
	// big_uint_load(&x, "0x00000000_00000000_0000000c");
	// big_uint_load(&p, "0x00000000_00000000_0000000d");
	// big_uint_load(&exp, "0x00000000_00000000_00000008");
	// big_uint_load(&res, "0x00000000_00000000_00000000");
	// mod_create(&mod, &p);

	// mod_sqrt(&res, &x, &mod);

	// expect(tester, big_uint_equals(&res, &exp));

	// // Test 4
	// big_uint_load(&x, "0x387a838f_28e44471");
	// big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	// big_uint_load(&exp, "0x303f068a_8fa4a613");
	// big_uint_load(&res, "0x00000000_00000000");
	// mod_create(&mod, &p);

	// mod_sqrt(&res, &x, &mod);

	// expect(tester, big_uint_equals(&res, &exp));

	// // Test 5
	// big_uint_load(&x, "0x00000000_04b421eb_482c6006");
	// big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	// big_uint_load(&exp, "0x00000000_2026882a_f384c481");
	// big_uint_load(&res, "0x00000000_00000000_00000000");
	// mod_create(&mod, &p);

	// mod_sqrt(&res, &x, &mod);

	// expect(tester, big_uint_equals(&res, &exp));

	// // Test 6
	// big_uint_load(&x, "0x00000000_33a3d9bd_0c616656");
	// big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	// big_uint_load(&exp, "0x00000000_1323ad4d_5d6bb78b");
	// big_uint_load(&res, "0x00000000_00000000_00000000");
	// mod_create(&mod, &p);

	// mod_sqrt(&res, &x, &mod);

	// expect(tester, big_uint_equals(&res, &exp));

	// // Test 7
	// big_uint_load(&x, "0x00000000_00000000_298b134e_4bf34588");
	// big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	// big_uint_load(&exp, "0x00000000_00000000_1b3984cf_e4ffd746");
	// big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	// mod_create(&mod, &p);

	// mod_sqrt(&res, &x, &mod);

	// expect(tester, big_uint_equals(&res, &exp));

	// // Test 8
	// big_uint_load(&x, "0x2fa707a6_d6d4803b");
	// big_uint_load(&p, "0x72ff2c08_4822fae5");
	// big_uint_load(&exp, "0x3114b009_f42042ef");
	// big_uint_load(&res, "0x00000000_00000000");
	// mod_create(&mod, &p);

	// mod_sqrt(&res, &x, &mod);

	// expect(tester, big_uint_equals(&res, &exp));

	// // Test 9
	// big_uint_load(&x, "0x00000000_56ab4592_6b39930e");
	// big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	// big_uint_load(&exp, "0x00000000_3b3aa7ed_5e7a2da2");
	// big_uint_load(&res, "0x00000000_00000000_00000000");
	// mod_create(&mod, &p);

	// mod_sqrt(&res, &x, &mod);

	// expect(tester, big_uint_equals(&res, &exp));

	// // Test 10
	// big_uint_load(&x, "0x00000000_4a9ce7cf_4e476632");
	// big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	// big_uint_load(&exp, "0x00000000_1b246238_e93303ed");
	// big_uint_load(&res, "0x00000000_00000000_00000000");
	// mod_create(&mod, &p);

	// mod_sqrt(&res, &x, &mod);

	// expect(tester, big_uint_equals(&res, &exp));

	// // Test 11
	// big_uint_load(&x, "0x00000000_00000000_638119fb_5f68686f");
	// big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	// big_uint_load(&exp, "0x00000000_00000000_44cedf60_0c98e691");
	// big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	// mod_create(&mod, &p);

	// mod_sqrt(&res, &x, &mod);

	// expect(tester, big_uint_equals(&res, &exp));

	// // Test 12
	// big_uint_load(&x, "0x0000000c");
	// big_uint_load(&p, "0x0000000d");
	// big_uint_load(&exp, "0x00000008");
	// mod_create(&mod, &p);

	// mod_sqrt(&x, &x, &mod);

	// expect(tester, big_uint_equals(&x, &exp));

	// // Test 13
	// big_uint_load(&x, "0x20e2b14b_b90ee4a5");
	// big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	// big_uint_load(&exp, "0x06167169_a5cbfee6");
	// mod_create(&mod, &p);

	// mod_sqrt(&x, &x, &mod);

	// expect(tester, big_uint_equals(&x, &exp));

	// // Test 14
	// big_uint_load(&x, "0x5e9dc23a_977cd30f");
	// big_uint_load(&p, "0x72ff2c08_4822fae5");
	// big_uint_load(&exp, "0x496339da_c15439b2");
	// mod_create(&mod, &p);

	// mod_sqrt(&x, &x, &mod);

	// expect(tester, big_uint_equals(&x, &exp));

	log_tests(tester);
}

int main() {
	// Calling all tests:
	test_mod_init();
	test_mod_big_uint();
	test_mod_add();
	test_mod_sub();
	test_mod_mult();
	test_mod_exp();
	test_mod_inv();
	test_mod_neg();
	test_mod_sqrt();

	return 1;
}
