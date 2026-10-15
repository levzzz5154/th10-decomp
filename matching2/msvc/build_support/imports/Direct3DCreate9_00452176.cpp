#include "../build_support/include/asm_encoding.hpp"

typedef void* (__stdcall* Direct3DCreate9Import_00452176)(unsigned int sdk_version);
extern "C" Direct3DCreate9Import_00452176 imp_Direct3DCreate9;

// 0x00452176..0x0045217B: imported Direct3DCreate9 tail thunk.
extern "C" void* __stdcall Direct3DCreate9_00452176(unsigned int sdk_version) {
    return imp_Direct3DCreate9(sdk_version);
}
