#include "th10/types.hpp"

// 0x00405130..0x00405140: copy a three-dword block.

struct TripleWordBlock {
    uint32_t values[3];

    __declspec(noinline) void Assign(const TripleWordBlock& other);
};

#pragma code_seg(".text$01copy3")
void TripleWordBlock::Assign(const TripleWordBlock& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
    values[2] = other.values[2];
}
#pragma code_seg()
