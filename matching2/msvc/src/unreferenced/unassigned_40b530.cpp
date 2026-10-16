#include <string.h>
#include "../../build_support/include/asm_symbols.hpp"

struct SmallState {
    unsigned int flags;
    unsigned int reserved_004[9];
    __declspec(noinline) void Initialize();
};

#pragma code_seg(".text$01init")
__declspec(noinline) void SmallState::Initialize() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    *reinterpret_cast<SmallState**>(&g_ending) = this;
}
#pragma code_seg()
