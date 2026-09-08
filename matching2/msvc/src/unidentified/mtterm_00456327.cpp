#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456327..0x00456343: __mtterm
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_mtterm_00456327() {
    __asm {
    L_00456327:
        mov eax,dword ptr [data_00473390]
    L_0045632c:
        cmp eax,0FFFFFFFFh
    L_0045632f:
        je short L_0045633f
    L_00456331:
        push eax
    L_00456332:
        call dword ptr [data_00477380]
    L_00456338:
        or dword ptr [data_00473390],0FFFFFFFFh
    L_0045633f:
        jmp asm_mtdeletelocks_00453aea
    }
}
