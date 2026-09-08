#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463C0D..0x00463CBA: FUN_00463c0d
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00463c0d_00463c0d() {
    __asm {
    L_00463c0d:
        push edx
    L_00463c0e:
        wait
        fnstcw word ptr [esp]
    L_00463c12:
        je short L_00463c81
    L_00463c14:
        cmp word ptr [esp],27Fh
    L_00463c1a:
        je short L_00463c21
    L_00463c1c:
        call asm_FUN_00464f15_00464f15
    L_00463c21:
        cmp eax,3FF00000h
    L_00463c26:
        jae short L_00463c55
    L_00463c28:
        fld1
    L_00463c2a:
        fadd st,st(1)
    L_00463c2c:
        fld1
    L_00463c2e:
        fsub st,st(2)
    L_00463c30:
        fmulp st(1),st
    L_00463c32:
        fsqrt
    L_00463c34:
        fxch
    L_00463c36:
        fpatan
    L_00463c38:
        cmp dword ptr [data_00477384],0
    L_00463c3f:
        jne asm_FUN_00463c0d_part_00464f9e
    L_00463c45:
        mov edx,0Dh
    L_00463c4a:
        lea ecx,[data_00477060]
    L_00463c50:
        jmp asm_math_exit_00464fab
    L_00463c55:
        ja short L_00463c8f
    L_00463c57:
        mov eax,dword ptr [esp+0Ch]
    L_00463c5b:
        mov ecx,eax
    L_00463c5d:
        and eax,0FFFFFh
    L_00463c62:
        or eax,dword ptr [esp+8]
    L_00463c66:
        jne short L_00463c8f
    L_00463c68:
        and ecx,80000000h
    L_00463c6e:
        fstp st(0)
    L_00463c70:
        je short L_00463c76
    L_00463c72:
        fldpi
    L_00463c74:
        jmp short L_00463c38
    L_00463c76:
        fldz
    L_00463c78:
        jmp short L_00463c38
    L_00463c7a:
        call asm_FUN_00464f2c_00464f2c
    L_00463c7f:
        jmp short L_00463c9c
    L_00463c81:
        test eax,0FFFFFh
    L_00463c86:
        jne short L_00463c7a
    L_00463c88:
        cmp dword ptr [esp+8],0
    L_00463c8d:
        jne short L_00463c7a
    L_00463c8f:
        fstp st(0)
    L_00463c91:
        fld tbyte ptr [data_00477070]
    L_00463c97:
        mov eax,1
    L_00463c9c:
        cmp dword ptr [data_00477384],0
    L_00463ca3:
        jne asm_FUN_00463c0d_part_00464f9e
    L_00463ca9:
        mov edx,0Dh
    L_00463cae:
        lea ecx,[data_00477060]
    L_00463cb4:
        call asm_startOneArgErrorHandling_00464eb7
    L_00463cb9:
        pop edx
    L_00463cba:
        ret
    }
}

// 0x00464F9E..0x00464FAA: FUN_00463c0d
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00463c0d_part_00464f9e() {
    __asm {
    L_00464f9e:
        cmp word ptr [esp],27Fh
    L_00464fa4:
        je short L_00464fa9
    L_00464fa6:
        fldcw word ptr [esp]
    L_00464fa9:
        pop edx
    L_00464faa:
        ret
    }
}
