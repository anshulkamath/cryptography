#include "ecdsa.h"

#include "big-uint.h"
#include "testing-logger.h"
#include "mod.h"
#include "point.h"
#include "ec.h"

#include <string.h>
#include <stdlib.h>

// global constants based off of seed value
const char *PR_KEY = "0x100f3325_b1ebd6ad_5e235b0b_2f2230a8_19c4668f_879b30ab_0590b0fd_4ee2b354";
const char *PU_KEY[2] = {
    "0x64e2cd45_1f884ed1_3884f479_acecb747_82b82b6b_1db2b539_78f4cd9d_a2f52c70",
    "0xd52e5696_1533c272_3e8912a4_81067817_a6097457_a324c81a_e10e7848_0c6b1820"
};
const char *M_HASH = "0xc7be1ed9_02fb8dd4_d48997c6_452f5d7e_509fbcdb_e2808b16_bcf4edce_4c07d14e";

void test_ecdsa_sign() {
    testing_logger_t *tester = create_tester();
    big_uint_t pr_key, m_hash, k;
    point_t res, exp;
    ec_t ec;
    srand(3);

    // this is the k-value using the given seed
    big_uint_load(&k, "0x9917cdb8_0ae04183_8e358811_4733c9fc_a6a619d6_cbe9c900_875888fc_f5d38d7f");

    char *signature[2] = {
        "0x87c23a8e_aa371b46_f5c4d752_684f45f9_beeab8cb_f1651864_92ca6ce5_98210b00",
        "0x1f30414e_aa5549d7_8d8d430b_343633c9_f8213101_229b6101_9335007f_7239b6c5"
    };

    // initializing public/private key and ec
    big_uint_load(&pr_key, PR_KEY);
    big_uint_load(&m_hash, M_HASH);
    ec_create(&ec, SECP256k1);

    point_create(&res, SECP256k1_SIZE);
    point_load(&exp, signature[0], signature[1]);

    ecdsa_sign(&res, &m_hash, &pr_key, &ec);

    expect(tester, point_equals(&res, &exp));

    log_tests(tester);
}

void test_ecdsa_verify() {
    testing_logger_t *tester = create_tester();
    big_uint_t pr_key, m_hash, bad_m_hash;
    point_t pu_key, bad_pu_key;
    point_t sig, exp;
    ec_t ec;
    srand(3); // use same random numbers as signature

    // initializing public/private key and ec
    big_uint_load(&pr_key, PR_KEY);
    big_uint_load(&m_hash, M_HASH);
    big_uint_load(&bad_m_hash, "0xf69bff44_070ba35d_7169196b_a0095425_979d9634_6a31486b_507b4a3f_77bd356d");
    point_load(&pu_key, PU_KEY[0], PU_KEY[1]);
    point_load(&bad_pu_key,
        "0xd7da18e28d6463ea9b7e93402aec0e122b76a669e04ad12f5f4b913f772751ef",
        "0x30b2258b85b729c8df9dda0cd1a5aa20ead6e416644fc6e75fbc327be89ead17"
    );
    ec_create(&ec, SECP256k1);

    point_create(&sig, SECP256k1_SIZE);
    ecdsa_sign(&sig, &m_hash, &pr_key, &ec);

    // should verify with the real public key
    expect(tester, ecdsa_verify(&sig, &m_hash, &pu_key, &ec));

    // should not verify with a different public key
    expect(tester, !ecdsa_verify(&sig, &m_hash, &bad_pu_key, &ec));

    // should not verify with a different message
    expect(tester, !ecdsa_verify(&sig, &bad_m_hash, &pu_key, &ec));

    // should not verify with a different signature
    expect(tester, !ecdsa_verify(ec.g, &m_hash, &pu_key, &ec));

    log_tests(tester);
}

int main() {
    test_ecdsa_sign();
    test_ecdsa_verify();

    return 0;
}
