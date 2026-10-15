#include <string.h>
#include "asm_symbols.hpp"

struct SmallState_0040B530 {
    unsigned int flags;
    unsigned int reserved_004[9];
    __declspec(noinline) void Initialize();
};

#pragma code_seg(".text$01init")
__declspec(noinline) void SmallState_0040B530::Initialize() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    *reinterpret_cast<SmallState_0040B530**>(&data_00477700) = this;
}
#pragma code_seg()
