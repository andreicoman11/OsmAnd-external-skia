#include "Test.h"
#include "SkBitSet.h"

static void TestBitSet(skiatest::Reporter* reporter) {
    SkBitSet set0(65536);
    REPORTER_ASSERT(reporter, set0.isBitSet(0) == false);
    REPORTER_ASSERT(reporter, set0.isBitSet(32767) == false);
    REPORTER_ASSERT(reporter, set0.isBitSet(65535) == false);

    SkBitSet set1(65536);
    REPORTER_ASSERT(reporter, set0 == set1);

    set0.setBit(22, true);
    REPORTER_ASSERT(reporter, set0.isBitSet(22) == true);
    set0.setBit(24, true);
    REPORTER_ASSERT(reporter, set0.isBitSet(24) == true);
    set0.setBit(35, true);  // on a different DWORD
    REPORTER_ASSERT(reporter, set0.isBitSet(35) == true);
    set0.setBit(22, false);
    REPORTER_ASSERT(reporter, set0.isBitSet(22) == false);
    REPORTER_ASSERT(reporter, set0.isBitSet(24) == true);
    REPORTER_ASSERT(reporter, set0.isBitSet(35) == true);

    set1.setBit(12345, true);
    set1.orBits(set0);
    REPORTER_ASSERT(reporter, set0.isBitSet(12345) == false);
    REPORTER_ASSERT(reporter, set1.isBitSet(12345) == true);
    REPORTER_ASSERT(reporter, set1.isBitSet(22) == false);
    REPORTER_ASSERT(reporter, set1.isBitSet(24) == true);
    REPORTER_ASSERT(reporter, set0.isBitSet(35) == true);
    REPORTER_ASSERT(reporter, set1 != set0);

    set1.clearAll();
    REPORTER_ASSERT(reporter, set0.isBitSet(12345) == false);
    REPORTER_ASSERT(reporter, set1.isBitSet(12345) == false);
    REPORTER_ASSERT(reporter, set1.isBitSet(22) == false);
    REPORTER_ASSERT(reporter, set1.isBitSet(24) == false);
    REPORTER_ASSERT(reporter, set1.isBitSet(35) == false);

    set1.orBits(set0);
    REPORTER_ASSERT(reporter, set1 == set0);

    SkBitSet set2(1);
    SkBitSet set3(1);
    SkBitSet set4(4);
    SkBitSet set5(33);

    REPORTER_ASSERT(reporter, set2 == set3);
    REPORTER_ASSERT(reporter, set2 != set4);
    REPORTER_ASSERT(reporter, set2 != set5);

    set2.setBit(0, true);
    REPORTER_ASSERT(reporter, set2 != set5);
    set5.setBit(0, true);
    REPORTER_ASSERT(reporter, set2 != set5);
    REPORTER_ASSERT(reporter, set2 != set3);
    set3.setBit(0, true);
    REPORTER_ASSERT(reporter, set2 == set3);
    set3.clearAll();
    set3 = set2;
    set2 = set2;
    REPORTER_ASSERT(reporter, set2 == set3);
}

#include "TestClassDef.h"
DEFINE_TESTCLASS("BitSet", BitSetTest, TestBitSet)
