#include "../../build_support/include/asm_symbols.hpp"

// 0x00421450..0x00421472: delete seven critical sections in the state.
extern "C" unsigned char imp_DeleteCriticalSection;
typedef void (__stdcall *DeleteCriticalSectionFn)(void *);

#pragma code_seg(".text$01target")
extern "C" __declspec(noinline) void __cdecl asm_FUN_00421450_00421450(
        void *state) {
    DeleteCriticalSectionFn destroy =
        *(DeleteCriticalSectionFn *)&imp_DeleteCriticalSection;
    unsigned char *critical_section = (unsigned char *)state + 0x64c;
    for (int index = 0; index != 7; ++index) {
        destroy(critical_section);
        critical_section += 0x18;
    }
}
#pragma code_seg()
