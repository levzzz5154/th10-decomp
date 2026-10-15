#include "../build_support/include/asm_encoding.hpp"

typedef void* (__stdcall* D3DXMatrixLookAtLHFn_00452194)(
    void* out, const void* eye, const void* at, const void* up);
extern "C" D3DXMatrixLookAtLHFn_00452194 data_004662ec;

// 0x00452194..0x00452199: imported D3DXMatrixLookAtLH tail thunk.
extern "C" void* __stdcall asm_D3DXMatrixLookAtLH_00452194(
    void* out, const void* eye, const void* at, const void* up) {
    return data_004662ec(out, eye, at, up);
}
