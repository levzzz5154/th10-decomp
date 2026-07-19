// Test for the FUN_00442050 reconstruction (EntityColorSlot_Init).
//
// Mirrors entity_movement_slot_test.cpp: verifies the lazy init/re-arm
// sequence, the byte-to-word zero extension, and the 24-byte zero
// block at +0x1d4..+0x1e8.

#include "th10/game/entity_color_slot.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>


uint32_t DAT_00476f78 = 0;


static void TestFirstCallLazyInit() {
    uint8_t slot[0x210] = {};
    uint8_t origin[3] = {10, 20, 30};
    uint8_t target[3] = {40, 50, 60};

    EntityColorSlot_Init(slot, origin, target, 0x11223344u, 0xFE);

    assert(*reinterpret_cast<uint32_t*>(slot + 0x200) == 0x11223344u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x204) == 0xFEu);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1bc) == 40u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1c0) == 50u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1c4) == 60u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1c8) == 10u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1cc) == 20u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1d0) == 30u);

    // 24-byte zero block at +0x1d4..+0x1e8 inclusive (7 words).
    for (unsigned int offset = 0x1d4; offset <= 0x1e8; offset += 4) {
        assert(*reinterpret_cast<uint32_t*>(slot + offset) == 0u);
    }

    // Lazy-init: bit-0 flag set, time scale pointer stored truncated,
    // state re-armed to 0xffffffff.
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1fc) & 1u);
    assert(*reinterpret_cast<int32_t*>(slot + 0x1ec) ==
           static_cast<int32_t>(0xffffffff));
    assert(*reinterpret_cast<int32_t*>(slot + 0x1f0) == 0);
    assert(*reinterpret_cast<int32_t*>(slot + 0x1f4) == 0);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1f8) ==
           static_cast<uint32_t>(
               reinterpret_cast<uintptr_t>(&DAT_00476f78)));
}

static void TestSecondCallPreservesLazyInitButReArms() {
    uint8_t slot[0x210] = {};
    uint8_t origin[3] = {1, 2, 3};
    uint8_t target[3] = {4, 5, 6};
    *reinterpret_cast<uint32_t*>(slot + 0x1f8) = 0xCAFEF00Du;
    *reinterpret_cast<uint32_t*>(slot + 0x1fc) = 1u;  // bit-0 armed

    EntityColorSlot_Init(slot, origin, target, 0x5555u, 0);

    assert(*reinterpret_cast<uint32_t*>(slot + 0x200) == 0x5555u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x204) == 0u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1bc) == 4u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1c0) == 5u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1c4) == 6u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1c8) == 1u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1cc) == 2u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1d0) == 3u);

    assert(*reinterpret_cast<uint32_t*>(slot + 0x1fc) == 1u);
    assert(*reinterpret_cast<uint32_t*>(slot + 0x1f8) == 0xCAFEF00Du);
    assert(*reinterpret_cast<int32_t*>(slot + 0x1ec) ==
           static_cast<int32_t>(0xffffffff));
    assert(*reinterpret_cast<int32_t*>(slot + 0x1f0) == 0);
    assert(*reinterpret_cast<int32_t*>(slot + 0x1f4) == 0);
}

static void TestNullSlotIsNoOp() {
    uint8_t origin[3] = {};
    uint8_t target[3] = {};
    EntityColorSlot_Init(0, origin, target, 0xFFFFFFFFu, 0xFF);
}

int main() {
    TestFirstCallLazyInit();
    TestSecondCallPreservesLazyInitButReArms();
    TestNullSlotIsNoOp();
    return 0;
}