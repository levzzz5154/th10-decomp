// Tests for the ECL retail helper reconstructions.  These cover the
// resolvers, PRNG, wrap, and movement-init helpers used by the
// 0x0040E770 dispatcher.
#include "th10/script/ecl.hpp"

#include <cassert>
#include <cstring>

uint32_t DAT_00476f78 = 0x3F800000u;

namespace {

void TestResolveFloatAtCursor() {
    ECLInstruction instruction;
    std::memset(&instruction, 0, sizeof(instruction));
    uint8_t cursor[0x1040] = {};
    *(ECLInstruction**)(cursor + 8) = &instruction;
    *(int32_t*)(cursor + 0x100C) = 0x20;
    // Direct value: bit not set, return the encoded value.
    instruction.param_mask = 0;
    *reinterpret_cast<uint32_t*>(&instruction.operands[0]) = 0x3F800000u;
    assert(ECL_ResolveFloatAtCursor(cursor, 0, 1.5f) == 1.5f);
    // Local variable: bit set, value is a non-negative index.
    instruction.param_mask = 1;
    *reinterpret_cast<uint32_t*>(&instruction.operands[0]) = 0x40400000u;  // 3.0f as bits
    *(float*)(cursor + 0x20 + 8 + 3) = 7.5f;
    assert(ECL_ResolveFloatAtCursor(cursor, 0, 3.0f) == 7.5f);
}

void TestPrngFloat() {
    uint8_t state[8] = {};
    ECL_PrngSeed(state, 0x1234);
    const float first = ECL_PrngFloat(state);
    const float second = ECL_PrngFloat(state);
    assert(first != second);
    assert(first > -3.1415927f && first <= 3.1415927f);
    assert(second > -3.1415927f && second <= 3.1415927f);
    ECL_PrngSeed(state, 0x1234);
    assert(ECL_PrngFloat(state) == first);
}

void TestWrapValue() {
    float value = 5.0f;
    ECL_WrapValue(&value);
    assert(value < 3.1415927f && value > -3.1415927f);
    value = 8.0f;
    ECL_WrapValue(&value);
    assert(value < 3.1415927f && value > -3.1415927f);
    value = -5.0f;
    ECL_WrapValue(&value);
    assert(value < 3.1415927f && value > -3.1415927f);
    value = 0.0f;
    ECL_WrapValue(&value);
    assert(value == 0.0f);
}

void TestInitMovementRecord() {
    uint8_t record[0x40] = {};
    ECL_InitMovementRecord(record);
    assert(*reinterpret_cast<uint32_t*>(record + 0x30) & 1u);
    assert(*reinterpret_cast<uint32_t*>(record + 0x20) ==
           0xffffffffu);
    // Subsequent call: the flag stays set, so the lazy-init block is
    // skipped and only the runtime fields are reset.
    ECL_InitMovementRecord(record);
    assert(*reinterpret_cast<uint32_t*>(record + 0x30) & 1u);
    assert(*reinterpret_cast<uint32_t*>(record + 0x20) ==
           0xffffffffu);
}

void TestSetPositionZWithWrap() {
    uint8_t record[0x40] = {};
    ECL_SetPositionZWithWrap(record, 10.0f);
    const float wrapped = *reinterpret_cast<float*>(record + 0x1c);
    assert(wrapped < 3.1415927f && wrapped > -3.1415927f);
}

void TestActiveEntityList() {
    uint8_t manager[0x80] = {};
    const size_t count_offset = sizeof(void*) == 4 ? 0x60 : 0x68;
    uint8_t first[0x2518] = {};
    uint8_t second[0x2518] = {};
    *reinterpret_cast<int32_t*>(first + 0x116C + 0x54) = 41;
    *reinterpret_cast<int32_t*>(second + 0x116C + 0x54) = 42;
    ECL_AddToActiveList(manager, first);
    ECL_AddToActiveList(manager, second);
    assert(*reinterpret_cast<uint32_t*>(manager + count_offset) == 2);
    assert(ECL_FindByID(41) == first);
    assert(ECL_FindByID(42) == second);
    ECL_AddToActiveList(manager, first);
    assert(*reinterpret_cast<uint32_t*>(manager + count_offset) == 2);
    ECL_ReleaseByID(41);
    assert(ECL_FindByID(41) == nullptr);
    assert(*reinterpret_cast<uint32_t*>(manager + count_offset) == 1);
    assert(*reinterpret_cast<void**>(manager + 0x58) == second + 0x116C);
    ECL_ReleaseByID(42);
    assert(*reinterpret_cast<uint32_t*>(manager + count_offset) == 0);
    assert(*reinterpret_cast<void**>(manager + 0x58) == nullptr);
}

// The id word (node+0x54 = entity+0x11C0) is a retail record field that
// opcodes 0x119/0x11b rewrite; teardown must unlink by pointer identity, not
// by that id.  A spawn whose id was overwritten must still be releasable.
void TestReleaseEntityByPointer() {
    uint8_t manager[0x80] = {};
    const size_t count_offset = sizeof(void*) == 4 ? 0x60 : 0x68;
    uint8_t entity[0x2518] = {};
    *reinterpret_cast<int32_t*>(entity + 0x116C + 0x54) = 0x100000;
    ECL_AddToActiveList(manager, entity);
    assert(*reinterpret_cast<uint32_t*>(manager + count_offset) == 1);
    // 0x119/0x11b write the record field at entity+0x11C0, which is the
    // same word the node carries its id in; the id lookup no longer matches.
    *reinterpret_cast<int32_t*>(entity + 0x11C0) = 0x1234;
    assert(ECL_FindByID(0x100000) == nullptr);
    // Pointer-based release still finds the node and unlinks it.
    ECL_ReleaseEntity(entity);
    assert(*reinterpret_cast<uint32_t*>(manager + count_offset) == 0);
    assert(*reinterpret_cast<void**>(manager + 0x58) == nullptr);
}

}  // namespace

int main() {
    TestResolveFloatAtCursor();
    TestPrngFloat();
    TestWrapValue();
    TestInitMovementRecord();
    TestSetPositionZWithWrap();
    TestActiveEntityList();
    TestReleaseEntityByPointer();
    return 0;
}
