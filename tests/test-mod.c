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

void test_mod_exp() {
	testing_logger_t *tester = create_tester();
	big_uint_t x, n, p;
	big_uint_t res, exp;
	mod_t mod;

	// Test 1
	big_uint_load(&x, "0x00000008");
	big_uint_load(&n, "0x00000004");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000001");
	big_uint_load(&res, "0x00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 2
	big_uint_load(&x, "0x00000000_00000004");
	big_uint_load(&n, "0x00000000_00000005");
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp, "0x00000000_0000000a");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 3
	big_uint_load(&x, "0x00000000_00000000_0000000a");
	big_uint_load(&n, "0x00000000_00000000_0000000c");
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000000_00000001");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 4
	big_uint_load(&x, "0x24fe23c8_f81a73cc");
	big_uint_load(&n, "0x045078a2_c3768f0f");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x377d3ae1_f6fd591f");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 5
	big_uint_load(&x, "0x00000000_0b720033_239f108c");
	big_uint_load(&n, "0x00000000_39ef56ad_1cd40184");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_068ef9a6_2de39238");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 6
	big_uint_load(&x, "0x00000000_0108031f_03f161e2");
	big_uint_load(&n, "0x00000000_238ef8a0_0719d671");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_2024305e_9e503fec");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 7
	big_uint_load(&x, "0x00000000_00000000_33850486_0efd220e");
	big_uint_load(&n, "0x00000000_00000000_1ac678d8_ea1695ce");
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_00000000_25c0b21b_33565359");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 8
	big_uint_load(&x, "0x420a4323_2be893f4");
	big_uint_load(&n, "0x6317fed7_1d2a4cb5");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x2eab9d7b_f7c19af2");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 9
	big_uint_load(&x, "0x00000000_6ab76b1e_0cd311de");
	big_uint_load(&n, "0x00000000_6b8fdf15_60f89a06");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_075de947_90c3bf40");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 10
	big_uint_load(&x, "0x00000000_47eaf205_f1c31001");
	big_uint_load(&n, "0x00000000_52ddbb24_8c35ddd6");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_6cf558eb_482ee859");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 11
	big_uint_load(&x, "0x00000000_00000000_2142fbbd_64a1f040");
	big_uint_load(&n, "0x00000000_00000000_4f093df5_af3e5dbf");
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_00000000_6ab002dc_d6250eed");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_exp(&res, &x, &n, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 12a
	// Operator assignment
	big_uint_load(&x, "0x00000006");
	big_uint_load(&n, "0x0000000a");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000004");
	mod_create(&mod, &p);

	mod_exp(&x, &x, &n, &mod);

	expect(tester, big_uint_equals(&x, &exp));

	// Test 13a
	// Operator assignment
	big_uint_load(&x, "0x216788a0_9460293b");
	big_uint_load(&n, "0x34fd616f_279a8cd0");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x15aa555c_36e2df4f");
	mod_create(&mod, &p);

	mod_exp(&x, &x, &n, &mod);

	expect(tester, big_uint_equals(&x, &exp));

	// Test 14a
	// Operator assignment
	big_uint_load(&x, "0x3e4c3dd4_0455ccc6");
	big_uint_load(&n, "0x342f22ba_e20cea4a");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x67a065fa_a8c5d5a3");
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
	big_uint_load(&x, "0x00000008");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000005");
	big_uint_load(&res, "0x00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 2
	big_uint_load(&x, "0x00000000_00000004");
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp, "0x00000000_0000000a");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 3
	big_uint_load(&x, "0x00000000_00000000_00000009");
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000000_00000003");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 4
	big_uint_load(&x, "0x1151ede8_dd3fccef");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x18ccb6b8_220d84b3");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 5
	big_uint_load(&x, "0x00000000_35c832db_e4da6f81");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_3784c062_22093e71");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 6
	big_uint_load(&x, "0x00000000_3ad812cb_5b3a2a6e");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_259c8967_614846e7");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 7
	big_uint_load(&x, "0x00000000_00000000_22705a48_86ee8c1b");
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_00000000_0cc27c7d_8fc86ec0");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 8
	big_uint_load(&x, "0x02fceea4_99e75f55");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x514fe566_655409fd");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 9
	big_uint_load(&x, "0x00000000_5931cc1b_de2bacb0");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_54d79891_05010fe8");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 10
	big_uint_load(&x, "0x00000000_3edecd5b_b0a7c881");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_2bdcbd40_f5d145e1");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_inv(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 11
	big_uint_load(&x, "0x00000000_00000000_5395d075_9c0531cd");
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_00000000_348e3193_5fb0a534");
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
	big_uint_load(&x, "0x00000009");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000004");
	big_uint_load(&res, "0x00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 2
	big_uint_load(&x, "0x00000000_00000005");
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000008");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 3
	big_uint_load(&x, "0x00000000_00000000_00000000");
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000000_00000000");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 4
	big_uint_load(&x, "0x05628748_943ec25a");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x379869f2_b7fff1c5");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 5
	big_uint_load(&x, "0x00000000_1579a9e4_4db996de");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_27814756_fe851d41");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 6
	big_uint_load(&x, "0x00000000_0541a562_549d94d2");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_37b94bd8_f7a11f4d");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 7
	big_uint_load(&x, "0x00000000_00000000_25a9a138_276a4baf");
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_00000000_17515003_24d46870");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 8
	big_uint_load(&x, "0x189ea7cb_e2ddba8b");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x5a60843c_6545405a");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 9
	big_uint_load(&x, "0x00000000_282b6dc8_b7b47614");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_4ad3be3f_906e84d1");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 10
	big_uint_load(&x, "0x00000000_216fc72f_ee466e6c");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_518f64d8_59dc8c79");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 11
	big_uint_load(&x, "0x00000000_00000000_041406c3_72555a97");
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_00000000_6eeb2544_d5cda04e");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_neg(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 12
	big_uint_load(&x, "0x0000000c");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000001");
	mod_create(&mod, &p);

	mod_neg(&x, &x, &mod);

	expect(tester, big_uint_equals(&x, &exp));

	// Test 13
	big_uint_load(&x, "0x1fb7f628_00375c0d");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x1d42fb13_4c075812");
	mod_create(&mod, &p);

	mod_neg(&x, &x, &mod);

	expect(tester, big_uint_equals(&x, &exp));

	// Test 14
	big_uint_load(&x, "0x0016ad61_6fa9bf73");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x72e87ea6_d8793b72");
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
	big_uint_load(&x, "0x0000000c");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000008");
	big_uint_load(&res, "0x00000000");
	mod_create(&mod, &p);

	mod_sqrt(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 2
	big_uint_load(&x, "0x00000000_0000000a");
	big_uint_load(&p, "0x00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000007");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_sqrt(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 3
	big_uint_load(&x, "0x00000000_00000000_00000009");
	big_uint_load(&p, "0x00000000_00000000_0000000d");
	big_uint_load(&exp, "0x00000000_00000000_00000003");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sqrt(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 4
	big_uint_load(&x, "0x2a941d6b_b4f51a8d");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x149a5d62_9bb64dce");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_sqrt(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 5
	big_uint_load(&x, "0x00000000_1782f68e_64527936");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_279e1246_ff47947c");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sqrt(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 6
	big_uint_load(&x, "0x00000000_19350f30_770606bb");
	big_uint_load(&p, "0x00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_01df3319_50dcae52");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sqrt(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 7
	big_uint_load(&x, "0x00000000_00000000_303de3af_9ce6ff8e");
	big_uint_load(&p, "0x00000000_00000000_3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x00000000_00000000_0aa7859c_dc35f915");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sqrt(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 8
	big_uint_load(&x, "0x0096f336_76cde342");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x2713ab78_937069bb");
	big_uint_load(&res, "0x00000000_00000000");
	mod_create(&mod, &p);

	mod_sqrt(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 9
	big_uint_load(&x, "0x00000000_4fdd1fa7_4af1c5b2");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_3931c101_acdd748d");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sqrt(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 10
	big_uint_load(&x, "0x00000000_1881684f_e719c704");
	big_uint_load(&p, "0x00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_55c03cba_3e46e8c7");
	big_uint_load(&res, "0x00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sqrt(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 11
	big_uint_load(&x, "0x00000000_00000000_1ffc5613_0f5bbba6");
	big_uint_load(&p, "0x00000000_00000000_72ff2c08_4822fae5");
	big_uint_load(&exp, "0x00000000_00000000_60b8d919_dffe9f49");
	big_uint_load(&res, "0x00000000_00000000_00000000_00000000");
	mod_create(&mod, &p);

	mod_sqrt(&res, &x, &mod);

	expect(tester, big_uint_equals(&res, &exp));

	// Test 12
	big_uint_load(&x, "0x0000000c");
	big_uint_load(&p, "0x0000000d");
	big_uint_load(&exp, "0x00000008");
	mod_create(&mod, &p);

	mod_sqrt(&x, &x, &mod);

	expect(tester, big_uint_equals(&x, &exp));

	// Test 13
	big_uint_load(&x, "0x1e9b499a_bde3f288");
	big_uint_load(&p, "0x3cfaf13b_4c3eb41f");
	big_uint_load(&exp, "0x118e99d7_d033b031");
	mod_create(&mod, &p);

	mod_sqrt(&x, &x, &mod);

	expect(tester, big_uint_equals(&x, &exp));

	// Test 14
	big_uint_load(&x, "0x4fb13182_b10ac280");
	big_uint_load(&p, "0x72ff2c08_4822fae5");
	big_uint_load(&exp, "0x67609eba_c57e39b7");
	mod_create(&mod, &p);

	mod_sqrt(&x, &x, &mod);

	expect(tester, big_uint_equals(&x, &exp));

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
