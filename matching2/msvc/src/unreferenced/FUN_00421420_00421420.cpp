#include "../../build_support/include/asm_symbols.hpp"

// 0x00421420..0x00421442: initialize seven critical sections in the state.
extern "C" unsigned char imp_InitializeCriticalSection;
typedef void (__stdcall *InitializeCriticalSectionFn_00421420)(void *);

#pragma code_seg(".text$01target")
extern "C" __declspec(noinline) void __cdecl asm_FUN_00421420_00421420(
        void *state) {
    InitializeCriticalSectionFn_00421420 initialize =
        *(InitializeCriticalSectionFn_00421420 *)&imp_InitializeCriticalSection;
    unsigned char *critical_section = (unsigned char *)state + 0x64c;
    for (int index = 0; index != 7; ++index) {
        initialize(critical_section);
        critical_section += 0x18;
    }
}
#pragma code_seg()
