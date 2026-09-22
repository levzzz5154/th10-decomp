#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (H2901): Ghidra confirms an exact 63-byte span at 0x0043A5C0 with
// no function boundary, incoming xrefs, or outgoing xrefs.  The retail ABI is
// private: ECX supplies the device identifier, ESI supplies the destination
// string, and the body uses the stack-cookie global at 0x00473660 plus the
// indirect API slot at 0x00466294.  A standalone __fastcall declaration can
// provide ECX but not ESI (its second argument is EDX). variants_tested=ABI
// feasibility inspection and no-reference caller search; no candidate source
// was retained because the required ECX/ESI pair is not expressible. next_lever
// =a real caller or native LTCG cluster that preserves ESI as the destination;
// absent that context, keep the exact overlay.
// closest_byte_count=63/63 (existing overlay); first_diff=N/A for overlay;
// residual_class=private-ABI ECX/ESI register pair.
// 0x0043A5C0..0x0043A5FE: FUN_0043a5c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a5c0_0043a5c0() {
    __asm {
    L_0043a5c0:
        sub esp,38h
    L_0043a5c3:
        mov eax,dword ptr [data_00473660]
    L_0043a5c8:
        xor eax,esp
    L_0043a5ca:
        mov dword ptr [esp+34h],eax
    L_0043a5ce:
        push 34h
    L_0043a5d0:
        lea eax,[esp+4]
    L_0043a5d4:
        push eax
    L_0043a5d5:
        push ecx
    L_0043a5d6:
        call dword ptr [data_00466294]
    L_0043a5dc:
        lea eax,[esp+8]
    L_0043a5e0:
        mov edx,esi
    L_0043a5e2:
        mov ecx,eax
    L_0043a5e4:
        sub edx,ecx
    L_0043a5e6:
        mov cl,byte ptr [eax]
    L_0043a5e8:
        mov byte ptr [edx+eax],cl
    L_0043a5eb:
        inc eax
    L_0043a5ec:
        test cl,cl
    L_0043a5ee:
        jne short L_0043a5e6
    L_0043a5f0:
        mov ecx,dword ptr [esp+34h]
    L_0043a5f4:
        xor ecx,esp
    L_0043a5f6:
        call asm_security_check_cookie_00458ea5
    L_0043a5fb:
        add esp,38h
    L_0043a5fe:
        ret
    }
}
