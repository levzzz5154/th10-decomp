#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004391F0..0x004392DB: FUN_004391f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004391f0_004391f0() {
    __asm {
    L_004391f0:
        sub esp,104h
    L_004391f6:
        mov eax,dword ptr [data_00473660]
    L_004391fb:
        xor eax,esp
    L_004391fd:
        push 0
    L_004391ff:
        push 0
    L_00439201:
        push 0
    L_00439203:
        mov dword ptr [esp+10Ch],eax
    L_0043920a:
        mov eax,dword ptr [data_00491c30]
    L_0043920f:
        mov ecx,dword ptr [eax]
    L_00439211:
        push 0
    L_00439213:
        push eax
    L_00439214:
        call dword ptr [ecx+44h]
    L_00439217:
        test eax,eax
    L_00439219:
        jge short L_00439244
    L_0043921b:
        mov eax,dword ptr [data_00491c10]
    L_00439220:
        call asm_DestroyEntityList_00438a30
    L_00439225:
        mov eax,dword ptr [data_00491c30]
    L_0043922a:
        mov edx,dword ptr [eax]
    L_0043922c:
        push 491D0Ch
    L_00439231:
        push eax
    L_00439232:
        call dword ptr [edx+40h]
    L_00439235:
        call asm_FUN_00439d20_00439d20
    L_0043923a:
        mov dword ptr [data_00491fd4],2
    L_00439244:
        push esi
    L_00439245:
        mov esi,dword ptr [data_00491c10]
    L_0043924b:
        call asm_FUN_00438a60_00438a60
    L_00439250:
        mov eax,dword ptr [data_00474e36]
    L_00439255:
        test ah,8
    L_00439258:
        je short L_004392c6
    L_0043925a:
        push 46F6E4h
    L_0043925f:
        call asm_FUN_00452abc_00452abc
    L_00439264:
        add esp,4
    L_00439267:
        xor esi,esi
    L_00439269:
        lea esp,[esp+force_disp32_zero]
    L_00439270:
        push esi
    L_00439271:
        lea eax,[esp+8]
    L_00439275:
        push 46F6D0h
    L_0043927a:
        push eax
    L_0043927b:
        call asm_sprintf_00452ae8
    L_00439280:
        add esp,0Ch
    L_00439283:
        lea ecx,[esp+4]
    L_00439287:
        push ecx
    L_00439288:
        call asm_File_ProbeExists_0044b4d0
    L_0043928d:
        test eax,eax
    L_0043928f:
        je short L_004392b0
    L_00439291:
        inc esi
    L_00439292:
        cmp esi,3E8h
    L_00439298:
        jl short L_00439270
    L_0043929a:
        pop esi
    L_0043929b:
        mov ecx,dword ptr [esp+100h]
    L_004392a2:
        xor ecx,esp
    L_004392a4:
        call asm_security_check_cookie_00458ea5
    L_004392a9:
        add esp,104h
    L_004392af:
        ret
    L_004392b0:
        cmp esi,3E8h
    L_004392b6:
        jge short L_004392c6
    L_004392b8:
        lea eax,[esp+4]
    L_004392bc:
        mov esi,491C28h
    L_004392c1:
        call asm_FUN_00420670_00420670
    L_004392c6:
        mov ecx,dword ptr [esp+104h]
    L_004392cd:
        pop esi
    L_004392ce:
        xor ecx,esp
    L_004392d0:
        call asm_security_check_cookie_00458ea5
    L_004392d5:
        add esp,104h
    L_004392db:
        ret
    }
}
