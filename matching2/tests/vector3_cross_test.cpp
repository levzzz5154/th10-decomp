// Test for the FUN_00421b90 reconstruction (Vector3_Cross).
//
// Verifies canonical cross-product results, the no-op for null
// pointers, and that aliasing ``out`` with ``left`` or ``right``
// behaves correctly (the readable body captures scalars first).

#include "th10/math/vector3_cross.hpp"

#include <cassert>


static void TestCanonicalBasis() {
    Vector3 out;
    Vector3 x = {1.0f, 0.0f, 0.0f};
    Vector3 y = {0.0f, 1.0f, 0.0f};
    Vector3 z = {0.0f, 0.0f, 1.0f};

    Vector3_Cross(&out, &x, &y);
    assert(out.x == 0.0f && out.y == 0.0f && out.z == 1.0f);

    Vector3_Cross(&out, &y, &z);
    assert(out.x == 1.0f && out.y == 0.0f && out.z == 0.0f);

    Vector3_Cross(&out, &z, &x);
    assert(out.x == 0.0f && out.y == 1.0f && out.z == 0.0f);
}

static void TestNegationOrder() {
    // x x y = -z
    Vector3 out;
    Vector3 x = {1.0f, 0.0f, 0.0f};
    Vector3 y = {0.0f, 1.0f, 0.0f};
    Vector3_Cross(&out, &y, &x);
    assert(out.x == 0.0f && out.y == 0.0f && out.z == -1.0f);
}

static void TestArbitraryValues() {
    Vector3 out;
    Vector3 a = {1.0f, 2.0f, 3.0f};
    Vector3 b = {4.0f, 5.0f, 6.0f};
    Vector3_Cross(&out, &a, &b);
    // a x b = (2*6 - 3*5, 3*4 - 1*6, 1*5 - 2*4) = (-3, 6, -3)
    assert(out.x == -3.0f);
    assert(out.y == 6.0f);
    assert(out.z == -3.0f);
}

static void TestNullIsNoOp() {
    Vector3 v = {1.0f, 2.0f, 3.0f};
    Vector3_Cross(0, &v, &v);
    Vector3_Cross(&v, 0, &v);
    Vector3_Cross(&v, &v, 0);
    // Unchanged.
    assert(v.x == 1.0f && v.y == 2.0f && v.z == 3.0f);
}

static void TestAliasOutWithLeft() {
    Vector3 a = {1.0f, 2.0f, 3.0f};
    Vector3 b = {4.0f, 5.0f, 6.0f};
    Vector3_Cross(&a, &a, &b);
    // Cross captured the original a first.
    assert(a.x == -3.0f);
    assert(a.y == 6.0f);
    assert(a.z == -3.0f);
}

static void TestAliasOutWithRight() {
    Vector3 a = {1.0f, 2.0f, 3.0f};
    Vector3 b = {4.0f, 5.0f, 6.0f};
    Vector3_Cross(&b, &a, &b);
    assert(b.x == -3.0f);
    assert(b.y == 6.0f);
    assert(b.z == -3.0f);
}

int main() {
    TestCanonicalBasis();
    TestNegationOrder();
    TestArbitraryValues();
    TestNullIsNoOp();
    TestAliasOutWithLeft();
    TestAliasOutWithRight();
    return 0;
}