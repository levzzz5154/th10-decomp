// Test for the FUN_0041ab70 reconstruction
// (EntityMovementSlot_Init).
//
// The slot lives inside an entity VM cursor/structure at offsets
// 0x180..0x1bc.  The helper's contract:
//   - 0x1b4 / 0x1b8 : store the source value and zero-extended mode
//   - 0x180 / 0x184 : copy the 8 bytes at ``target`` (a 2-float pair)
//   - 0x188 / 0x18c : copy the 8 bytes at ``origin`` (a 2-float pair)
//   - first call additionally lazy-initializes the 0x1a0 record state
//     to 0xfff0bdc1, arms the time scale pointer at +0x1ac, and sets the
//     bit-0 flag at +0x1b0
//   - every call (including the first) resets +0x1a4/+0x1a8 to zero and
//     the state word at +0x1a0 to 0xffffffff

#include "th10/game/entity_movement_slot.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>


// Shared script-time scale, defined at file scope so the
// ``extern uint32_t DAT_00476f78`` reference in entity_movement_slot.cpp
// resolves to this test fixture.
uint32_t DAT_00476f78 = 0;


static void TestFirstCallLazyInit() {
    uint8_t slot[0x1c0] = {};
    float origin[2] = {1.0f, 2.0f};
    float target[2] = {3.0f, 4.0f};
    EntityMovementSlot_Init(slot, origin, target, 0x77AABBCCu, 5);

    assert(*reinterpret_cast<uint32_t*>(slot + 0x1b4) == 0x77AABBCCu);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1b8) == 5u);
    assert(*reinterpret_cast<float*>(slot + 0x180) == 3.0f);
    assert(*reinterpret_cast<float*>(slot + 0x184) == 4.0f);
    assert(*reinterpret_cast<float*>(slot + 0x188) == 1.0f);
    assert(*reinterpret_cast<float*>(slot + 0x18c) == 2.0f);

    // First call: state at +0x1a0 was 0, bit-0 flag set, now re-armed
    // to 0xffffffff.  Time scale pointer at +0x1ac points at the
    // DAT_00476f78 symbol seen by the helper (stored as a 32-bit
    // truncation on 64-bit hosts to match the retail slot layout).
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1b0) & 1u);
    assert(*reinterpret_cast<int32_t*>(slot + 0x1a0) ==
           static_cast<int32_t>(0xffffffff));
    assert(*reinterpret_cast<int32_t*>(slot + 0x1a4) == 0);
    assert(*reinterpret_cast<int32_t*>(slot + 0x1a8) == 0);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1ac) ==
           static_cast<uint32_t>(
               reinterpret_cast<uintptr_t>(&DAT_00476f78)));
}

static void TestSecondCallPreservesLazyInitButReArms() {
    uint8_t slot[0x1c0] = {};
    float origin[2] = {10.0f, 20.0f};
    float target[2] = {30.0f, 40.0f};
    // Pre-populate the lazy-init words so the second call skips them.
    // On 32-bit retail the time scale pointer at +0x1ac is 4 bytes; on
    // 64-bit a real pointer write would overflow into +0x1b0.  Mirror
    // the retail 32-bit layout by using a uint32_t sentinel.
    *reinterpret_cast<uint32_t*>(slot + 0x1ac) = 0xCAFEF00Du;
    *reinterpret_cast<uint32_t*>(slot + 0x1b0) = 1u;  // bit-0 already armed

    EntityMovementSlot_Init(slot, origin, target, 0x1234u, 0);

    // Origin/target/source/mode: updated on every call.
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1b4) == 0x1234u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1b8) == 0u);
    assert(*reinterpret_cast<float*>(slot + 0x180) == 30.0f);
    assert(*reinterpret_cast<float*>(slot + 0x184) == 40.0f);
    assert(*reinterpret_cast<float*>(slot + 0x188) == 10.0f);
    assert(*reinterpret_cast<float*>(slot + 0x18c) == 20.0f);

    // Lazy-init is skipped; the (32-bit encoded) time scale sentinel
    // and the bit-0 flag remain untouched.
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1b0) == 1u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1ac) == 0xCAFEF00Du);

    // State word is still re-armed to 0xffffffff on every call.
    assert(*reinterpret_cast<int32_t*>(slot + 0x1a0) ==
           static_cast<int32_t>(0xffffffff));
    assert(*reinterpret_cast<int32_t*>(slot + 0x1a4) == 0);
    assert(*reinterpret_cast<int32_t*>(slot + 0x1a8) == 0);
}

static void TestNullSlotIsNoOp() {
    float origin[2] = {};
    float target[2] = {};
    EntityMovementSlot_Init(0, origin, target, 0xFFFFFFFFu, 0xFF);
}

int main() {
    TestFirstCallLazyInit();
    TestSecondCallPreservesLazyInitButReArms();
    TestNullSlotIsNoOp();
    return 0;
}