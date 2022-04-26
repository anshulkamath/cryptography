#include "ecdsa.h"

#include "big-uint.h"
#include "testing-logger.h"
#include "mod.h"
#include "point.h"
#include "ec.h"

#include <string.h>
#include <stdlib.h>

/**
 * public key: (0x0963e7dc_fec19aaa_32446bad_f19221c8_24bce996_81f48f16_9455b950_3f09fd4d, 0x01f85933_949531b4_78465896_a985d699_d660337b_813b9dfb_1201a1a3_6a122cff)
 * private key: 0xe09fb3bc_1963c23b_366e58d9_5128a2c6_51577720_01e14020_c795dc31_de3cee74
 */

void test_ecdsa_sign() {
    testing_logger_t *tester = create_tester();
    big_uint_t pr_key, m_hash;
    point_t res, exp;
    ec_t ec;
    srand(3);

    // initializing public/private key and ec
    big_uint_load(&pr_key, "0xe09fb3bc_1963c23b_366e58d9_5128a2c6_51577720_01e14020_c795dc31_de3cee74");
    big_uint_load(&m_hash, "0xc7be1ed9_02fb8dd4_d48997c6_452f5d7e_509fbcdb_e2808b16_bcf4edce_4c07d14e");
    ec_create(&ec, SECP256k1);

    point_create(&res, SECP256k1_SIZE);

    point_load(&exp, 
        "0x87c23a8e_aa371b46_f5c4d752_684f45f9_beeab8cb_f1651864_92ca6ce5_98210b00", 
        "0x22945038_e3a7824e_328ea3e8_d0b82786_cc3a6dd9_884d0852_fd52f6d2_5a2afbb2"
    );

    ecdsa_sign(&res, &m_hash, &pr_key, &ec);

    expect(tester, point_equals(&res, &exp));

    log_tests(tester);
}

int main() {
    test_ecdsa_sign();

    return 0;
}
