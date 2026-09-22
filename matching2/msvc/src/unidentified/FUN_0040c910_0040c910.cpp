// 0x0040C910: store the private EAX value into the object at offset zero.
// Native MSVC LTCG supplies the value in EAX and the object in ECX.
struct ObjectAccessor_0040c910 {
    int field_000;
    __declspec(noinline) int StoreValue(int value);
};
typedef char ObjectAccessor_0040c910_size_must_fit[
    sizeof(ObjectAccessor_0040c910) == 4 ? 1 : -1];

#pragma code_seg(".text$01accessor0040c910")
int ObjectAccessor_0040c910::StoreValue(int value) {
    field_000 = value;
    return value;
}
#pragma code_seg()
// Legacy fixed-address owner retained until the semantic region manifest is
// cut over to ObjectAccessor_0040c910::StoreValue.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c910_0040c910() {
    __asm {
        mov dword ptr [ecx],eax
        ret
    }
}
