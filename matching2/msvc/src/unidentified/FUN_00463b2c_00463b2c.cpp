#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463B2C..0x00463BA0: __ftol2, the VC x87 floating-to-integer helper.
// Its private entry consumes the value already in ST(0), takes no stack
// argument, and returns the 64-bit result in EDX:EAX. It uses FISTP followed
// by a residual-sign correction to move the rounded integer toward zero;
// zero and the INT64_MIN/invalid-conversion bit pattern bypass that correction.
// A normal C++ parameter cannot describe the incoming ST(0) state, so this
// body remains assembly until its callers and helper ABI can be migrated too.
extern "C" __declspec(naked) void __cdecl asm_FUN_00463b2c_00463b2c() {
    __asm {
    L_00463b2c:
        push ebp
    L_00463b2d:
        mov ebp,esp
    L_00463b2f:
        sub esp,20h
    L_00463b32:
        and esp,0FFFFFFF0h
    L_00463b35:
        fld st(0)
    L_00463b37:
        fst dword ptr [esp+18h]
    L_00463b3b:
        fistp qword ptr [esp+10h]
    L_00463b3f:
        fild qword ptr [esp+10h]
    L_00463b43:
        mov edx,dword ptr [esp+18h]
    L_00463b47:
        mov eax,dword ptr [esp+10h]
    L_00463b4b:
        test eax,eax
    L_00463b4d:
        je short L_00463b8b
    L_00463b4f:
        fsubp st(1),st
    L_00463b51:
        test edx,edx
    L_00463b53:
        jns short L_00463b73
    L_00463b55:
        fstp dword ptr [esp]
    L_00463b58:
        mov ecx,dword ptr [esp]
    L_00463b5b:
        xor ecx,80000000h
    L_00463b61:
        add ecx,7FFFFFFFh
    L_00463b67:
        adc eax,0
    L_00463b6a:
        mov edx,dword ptr [esp+14h]
    L_00463b6e:
        adc edx,0
    L_00463b71:
        jmp short L_00463b9f
    L_00463b73:
        fstp dword ptr [esp]
    L_00463b76:
        mov ecx,dword ptr [esp]
    L_00463b79:
        add ecx,7FFFFFFFh
    L_00463b7f:
        sbb eax,0
    L_00463b82:
        mov edx,dword ptr [esp+14h]
    L_00463b86:
        sbb edx,0
    L_00463b89:
        jmp short L_00463b9f
    L_00463b8b:
        mov edx,dword ptr [esp+14h]
    L_00463b8f:
        test edx,7FFFFFFFh
    L_00463b95:
        jne short L_00463b4f
    L_00463b97:
        fstp dword ptr [esp+18h]
    L_00463b9b:
        fstp dword ptr [esp+18h]
    L_00463b9f:
        leave
    L_00463ba0:
        ret
    }
}
