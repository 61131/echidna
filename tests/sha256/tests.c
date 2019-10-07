#include <stdio.h>
#include <string.h>

#include <munit/munit.h>

#include <sha256.h>


static void
_test_sha256_generate(char *Data, size_t Length, char *Digest) {
    SHA256 sDigest;
    char *pPtr, sBuffer[32];
    int nIndex;

    sha256_initialise(&sDigest);
    sha256_update(&sDigest, Data, Length);
    sha256_final(&sDigest, sBuffer);

    pPtr = Digest;
    for(nIndex = 0; nIndex < sizeof(sBuffer); ++nIndex)
        pPtr += sprintf(pPtr, "%02x", (sBuffer[nIndex] & 0xff));
}


MunitResult
test_sha256_generate(const MunitParameter Parameters[], void *Fixture) {
    SHA256 sDigest;
    char sBuffer[32], sStr[65];
    char *pPtr;
    int nIndex;

    //  "abc" (24 bits)
    _test_sha256_generate("abc", 3, sStr);
    munit_assert_string_equal(sStr, "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");

    //  "" (0 bits)
    _test_sha256_generate("", 0, sStr);
    munit_assert_string_equal(sStr, "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");

    //  "abc..opq" (448 bits)
    _test_sha256_generate("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 56, sStr);
    munit_assert_string_equal(sStr, "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");

    //  "abc..stu" (896 bits)
    _test_sha256_generate("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", 112, sStr);
    munit_assert_string_equal(sStr, "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1");

    //  "a" x 1000000 (8000000 bits)
    sha256_initialise(&sDigest);
    for(nIndex = 0; nIndex < 1000000; ++nIndex)
        sha256_update(&sDigest, "a", 1);
    sha256_final(&sDigest, sBuffer);
    pPtr = sStr;
    for(nIndex = 0; nIndex < sizeof(sBuffer); ++nIndex)
        pPtr += sprintf(pPtr, "%02x", (sBuffer[nIndex] & 0xff));
    munit_assert_string_equal(sStr, "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0");

    return MUNIT_OK;
}
