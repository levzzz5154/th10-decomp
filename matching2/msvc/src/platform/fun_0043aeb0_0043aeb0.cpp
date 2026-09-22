#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438AD0..0x0043900C: GameMain
// Naked body preserves the retail register/stack ABI.
// BLOCKED (D3403): closest_byte_count=2/79; first_diff=0x0043AEB0
// residual_class=private_ESI_EDX_abi_and_import_call_shape; the readable
// standalone candidate compiled to a 91-byte ECX/stack-entry body and only
// preserved the two zero-result bytes in the retail prefix. variants_tested=
// live Ghidra decompile plus a typed MidiHeader/free/import C++ candidate
// through the MSVC 13.10 probe; native-LTCG schema2 requires the two real
// callers (0x0043AE20 and 0x0043B110) in one cluster. next_lever=co-compile
// those callers and this callee with native LTCG, retaining EDX manager and
// ESI MIDIHDR register allocation and validating the import thunk binding.

// 0x0043AEB0..0x0043AEFE: FUN_0043aeb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043aeb0_0043aeb0() {
    __asm {
    L_0043aeb0:
        xor eax,eax
    L_0043aeb2:
        lea ecx,[edx+14h]
    L_0043aeb5:
        cmp dword ptr [ecx],esi
    L_0043aeb7:
        je short L_0043aec6
    L_0043aeb9:
        inc eax
    L_0043aeba:
        add ecx,4
    L_0043aebd:
        cmp eax,20h
    L_0043aec0:
        jl short L_0043aeb5
    L_0043aec2:
        or eax,0FFFFFFFFh
    L_0043aec5:
        ret
    L_0043aec6:
        push 40h
    L_0043aec8:
        mov dword ptr [edx+eax*4+14h],0
    L_0043aed0:
        mov eax,dword ptr [edx+13Ch]
    L_0043aed6:
        push esi
    L_0043aed7:
        push eax
    L_0043aed8:
        call dword ptr [data_00466284]
    L_0043aede:
        mov eax,dword ptr [esi]
    L_0043aee0:
        test eax,eax
    L_0043aee2:
        je short L_0043aef3
    L_0043aee4:
        push eax
    L_0043aee5:
        call asm_free_00452422
    L_0043aeea:
        add esp,4
    L_0043aeed:
        mov dword ptr [esi],0
    L_0043aef3:
        push esi
    L_0043aef4:
        call asm_free_00452422
    L_0043aef9:
        add esp,4
    L_0043aefc:
        xor eax,eax
    L_0043aefe:
        ret
    }
}
