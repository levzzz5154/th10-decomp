#include "../build_support/include/asm_encoding.hpp"

// D3DXVec3Normalize is the two-pointer stdcall import entry used by the
// renderer.  Keeping the native calling convention gives MSVC 13.10 the
// original six-byte indirect tail jump and preserves the API's decorated
// symbol.
typedef void* (__stdcall *D3DXVec3NormalizeImport_0045217c)(
    void* out, const void* vector);

extern "C" D3DXVec3NormalizeImport_0045217c imp_D3DXVec3Normalize;

// 0x0045217C..0x00452181: D3DXVec3Normalize import thunk.
extern "C" void* __stdcall D3DXVec3Normalize(
    void* out, const void* vector) {
    return imp_D3DXVec3Normalize(out, vector);
}
