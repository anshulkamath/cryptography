#include "ec.h"
#include "secp256k1.c"

#include "big-uint.h"
#include "mod.h"
#include "point.h"
#include <string.h>
#include "testing-logger.h"

void test_ec_init() {
    testing_logger_t *tester = create_tester();
    big_uint_t a, b, p, n;
    mod_t mod_p, mod_n;
    point_t g;
    ec_t ec;

    big_uint_load(&a, "0x3");
    big_uint_load(&b, "0x5");
    big_uint_load(&p, "0xd");
    big_uint_load(&n, "0xd");
    mod_create(&mod_p, &p);
    mod_create(&mod_n, &n);
    point_create(&g, "0x1", "0x2");

    ec_init(&ec, &a, &b, &mod_p, &mod_n, &g);
    
    expect(tester, big_uint_equals(ec.a, &a));
    expect(tester, big_uint_equals(ec.b, &b));
    expect(tester, mod_equals(ec.mod_p, &mod_p));
    expect(tester, mod_equals(ec.mod_n, &mod_n));
    expect(tester, point_equals(ec.g, &g));

    log_tests(tester);
}

void test_ec_create() {
    testing_logger_t *tester = create_tester();
    big_uint_t exp_a, exp_b, exp_p, exp_n;
    mod_t exp_mod_p, exp_mod_n;
    point_t exp_g;
    ec_t ec;

    big_uint_load(&exp_a, SECP256K1_A);
    big_uint_load(&exp_b, SECP256K1_B);
    big_uint_load(&exp_p, SECP256K1_P);
    big_uint_load(&exp_n, SECP256K1_N);
    mod_create(&exp_mod_p, &exp_p);
    mod_create(&exp_mod_n, &exp_n);
    point_create(&exp_g, SECP256K1_X, SECP256K1_Y);

    // create secp256k1 instance
    ec_create(&ec, SECP256k1);

    expect(tester, big_uint_equals(ec.a, &exp_a));
    expect(tester, big_uint_equals(ec.b, &exp_b));
    expect(tester, mod_equals(ec.mod_p, &exp_mod_p));
    expect(tester, mod_equals(ec.mod_n, &exp_mod_n));
    expect(tester, point_equals(ec.g, &exp_g));

    log_tests(tester);
}

void test_ec_is_inv() {
	testing_logger_t *tester = create_tester();
	ec_t ec;
	point_t p1, p2;
	
	ec_create(&ec, SECP256k1);

	// Test 1
	point_create(&p1, 
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	point_create(&p2, 
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0xb7c52588_d95c3b9a_a25b0403_f1eef757_02e84bb7_597aabe6_63b82f6f_04ef2777"
	);
	uint8_t res1 = 1;

	expect(tester, ec_is_inv(&ec, &p1, &p2) == res1);

	// Test 2
	point_create(&p1, 
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	point_create(&p2, 
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000",
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
	);
	uint8_t res2 = 0;

	expect(tester, ec_is_inv(&ec, &p1, &p2) == res2);

	// Test 3
	point_create(&p1, 
		"0x1e2feb89_414c343c_1027c4d1_c386bbc4_cd613e30_d8f16adf_91b7584a_2265b1f6",
		"0x2762a80b_aa354f16_98a6101f_5fb8f56f_d2524af4_e2f05b67_ae8fab0e_01783e35"
	);
	point_create(&p2, 
		"0x1e2feb89_414c343c_1027c4d1_c386bbc4_cd613e30_d8f16adf_91b7584a_2265b1f6",
		"0xd89d57f4_55cab0e9_6759efe0_a0470a90_2dadb50b_1d0fa498_517054f0_fe87bdfa"
	);
	uint8_t res3 = 1;

	expect(tester, ec_is_inv(&ec, &p1, &p2) == res3);

	// Test 4
	point_create(&p1, 
		"0x35bf992d_c9e9c616_612e7696_a6cecc1b_78e51061_7311d8a3_c2ce6f44_7ed4d57c",
		"0x8cc5702d_1ca20bee_3c959f22_2a0b77a6_b70fbb4c_9939bf2c_82fdd6ff_7d35968a"
	);
	point_create(&p2, 
		"0x35bf992d_c9e9c616_612e7696_a6cecc1b_78e51061_7311d8a3_c2ce6f44_7ed4d57c",
		"0x733a8fd2_e35df411_c36a60dd_d5f48859_48f044b3_66c640d3_7d0228ff_82ca65a5"
	);
	uint8_t res4 = 1;

	expect(tester, ec_is_inv(&ec, &p1, &p2) == res4);

	log_tests(tester);
}

int main () {
    test_ec_init();
    test_ec_create();
    test_ec_is_inv();
    
    return 0;
}
