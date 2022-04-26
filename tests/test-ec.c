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

    big_uint_load(&exp_a, _SECP256k1_A);
    big_uint_load(&exp_b, _SECP256k1_B);
    big_uint_load(&exp_p, _SECP256k1_P);
    big_uint_load(&exp_n, _SECP256k1_N);
    mod_create(&exp_mod_p, &exp_p);
    mod_create(&exp_mod_n, &exp_n);
    point_create(&exp_g, _SECP256k1_X, _SECP256k1_Y);

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

	expect(tester, ec_is_inv(&p1, &p2, &ec) == res1);

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

	expect(tester, ec_is_inv(&p1, &p2, &ec) == res2);

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

	expect(tester, ec_is_inv(&p1, &p2, &ec) == res3);

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

	expect(tester, ec_is_inv(&p1, &p2, &ec) == res4);

	log_tests(tester);
}

void test_ec_add() {
	testing_logger_t *tester = create_tester();
	ec_t ec;
	point_t p1, p2;
	point_t res, exp;
	
	ec_create(&ec, SECP256k1);
	point_touch(&res, SECP256k1_SIZE);

	// Test 1
	point_create(&p1, 
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000",
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
	);
	point_create(&p2, 
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000",
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
	);
	point_create(&exp, 
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000",
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
	);
	ec_add(&res, &p1, &p2, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 2
	point_create(&p1, 
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000",
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
	);
	point_create(&p2, 
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	point_create(&exp, 
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	ec_add(&res, &p1, &p2, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 3
	point_create(&p1, 
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	point_create(&p2, 
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000",
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
	);
	point_create(&exp, 
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	ec_add(&res, &p1, &p2, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 4
	point_create(&p1, 
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	point_create(&p2, 
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	point_create(&exp, 
		"0xc6047f94_41ed7d6d_3045406e_95c07cd8_5c778e4b_8cef3ca7_abac09b9_5c709ee5",
		"0x1ae168fe_a63dc339_a3c58419_466ceaee_f7f63265_3266d0e1_236431a9_50cfe52a"
	);
	ec_add(&res, &p1, &p2, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 5
	point_create(&p1, 
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	point_create(&p2, 
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0xb7c52588_d95c3b9a_a25b0403_f1eef757_02e84bb7_597aabe6_63b82f6f_04ef2777"
	);
	point_create(&exp, 
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000",
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
	);
	ec_add(&res, &p1, &p2, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 6
	point_create(&p1, 
		"0xafbd67f9_619699cf_e1988ad9_f06c144a_025b413f_8a9a021e_a648a7dd_06839eba",
		"0x33763125_87a62b63_c23e8235_4e287e44_972ff92f_036cc3c1_553e3c04_95ce144f"
	);
	point_create(&p2, 
		"0xc381e88f_38c0c8fd_8712b8bc_076f3787_b9d179e0_6c0fd4f5_f8130c42_37730ee0",
		"0xea038ddd_39b4aecd_d41e8c29_a56e1b3f_8acf73eb_671f9625_b1b08aa5_0e8ed417"
	);
	point_create(&exp, 
		"0x5976f03e_c483f3fe_7a18da55_d317f55c_e1ccc3be_17b01328_50341f92_b2e62e65",
		"0x42394ccc_4816362a_33178773_32f111ae_765546b7_f4e5af84_d24461a3_8250f2d6"
	);
	ec_add(&res, &p1, &p2, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 7
	point_create(&p1, 
		"0x6a8ac4ba_05805975_ed2f89d9_4a2f20aa_f3c64af7_75a89294_c2cd789a_380208aa",
		"0xccc8d8fb_d6ea4202_d10c61f3_ad00acba_4b18fd47_e3122430_addc21ad_0804c289"
	);
	point_create(&p2, 
		"0x81f9c1f6_6c0f3459_f79b17ae_efba91fc_803468b6_b610a9f7_f9270f4e_b8b333a9",
		"0xb7923630_24c4d3da_65eea057_f1d21f73_ef2e6d66_891def91_ee77b919_1feb9512"
	);
	point_create(&exp, 
		"0xc8b579c7_e24056af_a1e3d356_b297973a_b279fade_f3ba69e7_ffc5124e_d52e9361",
		"0x6333213c_7425c76c_f50a820b_8dcee734_a82f1fea_7855ea97_3daecce0_f63edfb0"
	);
	ec_add(&res, &p1, &p2, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 8
	point_create(&p1, 
		"0x29e821a4_c74803e3_1ba16215_82283d15_a9ec0806_705fca16_1622bd79_5fec8990",
		"0x13eabece_392fa99b_45b1460e_ea15ed96_c23ef81f_5cda751b_7ad1f35e_2a922ead"
	);
	point_create(&p2, 
		"0x678a5aa3_3b6fe507_8c5fe8f8_dc3bf364_eb8ac8ce_8a245e6b_33138131_c541013e",
		"0x1f9b3eaa_b829ed4c_4853f26c_f8f92591_2d293dca_74888cb8_d3244fd3_c31c3050"
	);
	point_create(&exp, 
		"0x6acd33ff_7dc76532_464f5991_73cf6ca1_c33e63b3_7fa0d2e1_f9c76fc3_5e3df4d1",
		"0xb6aa2428_96011c85_37fbfbd3_07da39e8_0a740213_a95d66bb_c70f2511_5f9768bb"
	);
	ec_add(&res, &p1, &p2, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 9
	point_create(&p1, 
		"0xf320cd57_6d14475b_349aae90_8fb5262c_c7038069_84c81999_21167d8f_cf23cae9",
		"0x151c6f56_a5864f06_a2c7749f_0468e9e3_887a34d0_87e6d38c_996baedd_8b9c9ed3"
	);
	point_create(&p2, 
		"0x99901c04_75491bc3_54c56c9a_9cc9af4e_c9546b43_9f9d0129_8a449ebe_89d9bf03",
		"0x3a641141_514c6b7b_1cd7f671_ac2e39e5_a32e3837_be34be70_0835ad12_799ad7a4"
	);
	point_create(&exp, 
		"0xb555c0c7_675446f6_f264d16e_21f8402f_da41d8e2_df54ecea_ceb80683_cafebd79",
		"0xfd3b53a9_54f442b2_d8703af7_ac7eadcf_8b242d88_d7413a58_6e855de8_8dd5f491"
	);
	ec_add(&res, &p1, &p2, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 10
	point_create(&p1, 
		"0x2e47dc0e_959f3a51_8cfe5cd1_2d5db79b_a2a7ae1f_3ac7652c_cdf84404_07295e43",
		"0x948623ae_fa399e2d_2514e9bc_dc8748a8_68ddc416_96bc3b5a_aef7a97b_992126e7"
	);
	point_create(&p2, 
		"0xee52bdb6_d1020a15_d9ed17e3_cc0e95ee_8d103ed3_cc667e97_1773308c_dc6b13ac",
		"0x11b463cd_f7914171_d3def30e_5523d137_fe30ced9_11895699_de0c8851_bf33ab24"
	);
	point_create(&exp, 
		"0x5c05ab7d_b135f95e_f07185f7_5d4b0cfd_d30e8200_720b47da_246f6480_622a8ab0",
		"0xeea3819a_7ee66d85_90e20ec3_9db16cd2_ab6bdf8f_697eee59_9ad211f9_e1071f32"
	);
	ec_add(&res, &p1, &p2, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 11
	point_create(&p1, 
		"0x2adf559a_11cbc288_4a5012dc_582c18c9_2f429ce5_9ff3078f_cc1b0c3e_1c07724f",
		"0x07d006c1_aa99c36f_d669f3a5_a9130e46_65b590aa_c7cb8bd7_13445d87_374dbd5e"
	);
	point_create(&p2, 
		"0xa5f09e63_45ddb87d_a81aa40a_2b0b8c12_f3b37f32_870266c4_4155d7ef_28dd37ec",
		"0xf2a30d5b_67839dae_eab9356a_0769bd56_88ef1052_5392ae7e_6bd58c95_bd133a7f"
	);
	point_create(&exp, 
		"0x20547da7_3328fe5c_983a5e48_353cf14a_ae31770f_dbb8ba35_a3c950cb_d99e0c75",
		"0x4e355f99_7bf0751c_962cfd82_08107719_ed783adc_7aa458b9_ac1f8c75_086be8dd"
	);
	ec_add(&res, &p1, &p2, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 12
	point_create(&p1, 
		"0x1d3b993f_79490eab_7f1a355e_526eb523_b3df44a4_7467537a_4b63e0ef_b62ac1ff",
		"0x4c327bad_1939afe5_6c2ab124_fff35a05_976df104_ed7c89a2_81ce37b0_3d0857dc"
	);
	point_create(&p2, 
		"0x4227de21_3023580c_cbd3f5e0_6bc15385_57e54acc_62f5680c_4fdf8e1a_060cea64",
		"0xda17bc78_834584b7_6012afe5_ec30261b_de2a7c39_6c072cce_faaf4070_6af69d99"
	);
	point_create(&exp, 
		"0xa85096b7_1023627c_c8bef091_b1567239_6536126a_1c27320e_43498ce5_2830fbe4",
		"0x0d69bc7e_94e6b252_e1ef1886_6194b3ad_c08ca2ea_19cbcd2a_79a49811_9e6b9ff9"
	);
	ec_add(&res, &p1, &p2, &ec);

	expect(tester, point_equals(&res, &exp));

	log_tests(tester);
}

void test_ec_mult() {
	testing_logger_t *tester = create_tester();
	ec_t ec;
	big_uint_t k;
	point_t p;
	point_t res, exp;
	
	ec_create(&ec, SECP256k1);
	point_touch(&res, SECP256k1_SIZE);

	// Test 1
	big_uint_load(&k, "0x00000000");
	point_create(&p,
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	point_create(&exp,
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000",
		"0x00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000"
	);
	ec_mult(&res, &k, &p, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 2
	big_uint_load(&k, "0x00000001");
	point_create(&p,
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	point_create(&exp,
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	ec_mult(&res, &k, &p, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 3
	big_uint_load(&k, "0x00000002");
	point_create(&p,
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	point_create(&exp,
		"0xc6047f94_41ed7d6d_3045406e_95c07cd8_5c778e4b_8cef3ca7_abac09b9_5c709ee5",
		"0x1ae168fe_a63dc339_a3c58419_466ceaee_f7f63265_3266d0e1_236431a9_50cfe52a"
	);
	ec_mult(&res, &k, &p, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 4
	big_uint_load(&k, "0x00000059");
	point_create(&p,
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	point_create(&exp,
		"0xd3cc30ad_6b483e4b_c79ce2c9_dd8bc549_93e947eb_8df787b4_42943d3f_7b527eaf",
		"0x8b378a22_d827278d_89c5e9be_8f9508ae_3c2ad462_90358630_afb34db0_4eede0a4"
	);
	ec_mult(&res, &k, &p, &ec);

	expect(tester, point_equals(&res, &exp));

	// Test 5
	big_uint_load(&k, "0xf72f2bb8_3586fca7_fa0b8518_8296f5ea_baeb41a5_e65a8149_40e2a20a_1bd7ce74");
	point_create(&p,
		"0x79be667e_f9dcbbac_55a06295_ce870b07_029bfcdb_2dce28d9_59f2815b_16f81798",
		"0x483ada77_26a3c465_5da4fbfc_0e1108a8_fd17b448_a6855419_9c47d08f_fb10d4b8"
	);
	point_create(&exp,
		"0xfe5d83ca_5b2f7cc3_557195eb_00ebd930_c3543939_34ea60a1_681d4233_ae0b0cec",
		"0x5d34d224_b4e87eb9_ccf86bdc_fbb56969_e846da33_f5f896ca_7eb72160_86550e85"
	);
	ec_mult(&res, &k, &p, &ec);

	expect(tester, point_equals(&res, &exp));

	log_tests(tester);
}

void test_ec_keygen() {
	testing_logger_t *tester = create_tester();
	ec_t ec;
	point_t pu_key, exp_key;
	big_uint_t pr_key;

	ec_create(&ec, SECP256k1);
	point_touch(&pu_key, SECP256k1_SIZE);
	point_touch(&exp_key, SECP256k1_SIZE);
	big_uint_create(&pr_key, SECP256k1_SIZE);

	// Test 1
	ec_keygen(&pu_key, &pr_key, &ec);
	ec_mult(&exp_key, &pr_key, ec.g, &ec);
	expect(tester, point_equals(&pu_key, &exp_key));

	// Test 2
	ec_keygen(&pu_key, &pr_key, &ec);
	ec_mult(&exp_key, &pr_key, ec.g, &ec);
	expect(tester, point_equals(&pu_key, &exp_key));

	// Test 3
	ec_keygen(&pu_key, &pr_key, &ec);
	ec_mult(&exp_key, &pr_key, ec.g, &ec);
	expect(tester, point_equals(&pu_key, &exp_key));

	// Test 4
	ec_keygen(&pu_key, &pr_key, &ec);
	ec_mult(&exp_key, &pr_key, ec.g, &ec);
	expect(tester, point_equals(&pu_key, &exp_key));

	// Test 5
	ec_keygen(&pu_key, &pr_key, &ec);
	ec_mult(&exp_key, &pr_key, ec.g, &ec);
	expect(tester, point_equals(&pu_key, &exp_key));
	big_uint_print(&pr_key);
	point_print(&pu_key);
	printf("\n");

	log_tests(tester);
}

int main () {
    test_ec_init();
    test_ec_create();
    test_ec_is_inv();
	test_ec_add();
	test_ec_mult();
	test_ec_keygen();
    
    return 0;
}
