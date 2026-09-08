#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452332..0x00452421: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00452332() {
    __asm {
    L_00452332:
        jmp dword ptr [data_00466264]
    L_00452338:
        jmp dword ptr [data_00466260]
    L_0045233e:
        jmp dword ptr [data_0046625c]
    L_00452344:
        jmp dword ptr [data_00466258]
    L_0045234a:
        jmp dword ptr [data_00466254]
    L_00452350:
        jmp dword ptr [data_00466250]
    L_00452356:
        jmp dword ptr [data_0046624c]
    L_0045235c:
        jmp dword ptr [data_00466248]
    L_00452362:
        jmp dword ptr [data_00466244]
    L_00452368:
        jmp dword ptr [data_00466240]
    L_0045236e:
        jmp dword ptr [data_0046623c]
    L_00452374:
        jmp dword ptr [data_00466238]
    L_0045237a:
        jmp dword ptr [data_00466234]
    L_00452380:
        jmp dword ptr [data_00466230]
    L_00452386:
        jmp dword ptr [data_0046622c]
    L_0045238c:
        jmp dword ptr [data_00466228]
    L_00452392:
        jmp dword ptr [data_004661f0]
    L_00452398:
        jmp dword ptr [data_00466224]
    L_0045239e:
        jmp dword ptr [data_00466220]
    L_004523a4:
        jmp dword ptr [data_0046621c]
    L_004523aa:
        jmp dword ptr [data_00466218]
    L_004523b0:
        jmp dword ptr [data_00466214]
    L_004523b6:
        jmp dword ptr [data_00466210]
    L_004523bc:
        jmp dword ptr [data_0046620c]
    L_004523c2:
        jmp dword ptr [data_00466208]
    L_004523c8:
        jmp dword ptr [data_00466204]
    L_004523ce:
        jmp dword ptr [data_00466200]
    L_004523d4:
        jmp dword ptr [data_00466034]
    L_004523da:
        jmp dword ptr [data_00466030]
    L_004523e0:
        jmp dword ptr [data_0046602c]
    L_004523e6:
        jmp dword ptr [data_00466028]
    L_004523ec:
        jmp dword ptr [data_00466024]
    L_004523f2:
        jmp dword ptr [data_00466020]
    L_004523f8:
        jmp dword ptr [data_0046601c]
    L_004523fe:
        jmp dword ptr [data_00466018]
    L_00452404:
        jmp dword ptr [data_00466014]
    L_0045240a:
        jmp dword ptr [data_00466010]
    L_00452410:
        jmp dword ptr [data_00466304]
    L_00452416:
        jmp dword ptr [data_00466300]
    L_0045241c:
        jmp dword ptr [data_00466308]
    }
}
