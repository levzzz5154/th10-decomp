#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420100..0x004201AD: FUN_00420100
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00420100_00420100() {
    __asm {
    L_00420100:
        sub esp,88h
    L_00420106:
        mov eax,dword ptr [data_00473660]
    L_0042010b:
        xor eax,esp
    L_0042010d:
        mov dword ptr [esp+84h],eax
    L_00420114:
        push edi
    L_00420115:
        mov eax,46E000h
    L_0042011a:
        mov ecx,497990h
    L_0042011f:
        call asm_DatArchive_Open_00434c30
    L_00420124:
        test al,al
    L_00420126:
        je short L_00420183
    L_00420128:
        push 61h
    L_0042012a:
        push 100h
    L_0042012f:
        lea eax,[esp+10h]
    L_00420133:
        push 46DFF0h
    L_00420138:
        push eax
    L_00420139:
        call asm_sprintf_00452ae8
    L_0042013e:
        add esp,10h
    L_00420141:
        push 0
    L_00420143:
        lea ecx,[esp+8]
    L_00420147:
        push ecx
    L_00420148:
        lea eax,[esp+10h]
    L_0042014c:
        call asm_FUN_0044b360_0044b360
    L_00420151:
        test eax,eax
    L_00420153:
        mov edx,dword ptr [esp+4]
    L_00420157:
        mov dword ptr [data_0049238c],eax
    L_0042015c:
        mov dword ptr [data_00492388],edx
    L_00420162:
        jne short L_0042016b
    L_00420164:
        push 46DFC8h
    L_00420169:
        jmp short L_00420188
    L_0042016b:
        xor eax,eax
    L_0042016d:
        pop edi
    L_0042016e:
        mov ecx,dword ptr [esp+84h]
    L_00420175:
        xor ecx,esp
    L_00420177:
        call asm_security_check_cookie_00458ea5
    L_0042017c:
        add esp,88h
    L_00420182:
        ret
    L_00420183:
        push 46DFA0h
    L_00420188:
        mov edi,474F70h
    L_0042018d:
        call asm_TextLog_AppendLine_0044b8e0
    L_00420192:
        mov ecx,dword ptr [esp+8Ch]
    L_00420199:
        add esp,4
    L_0042019c:
        pop edi
    L_0042019d:
        xor ecx,esp
    L_0042019f:
        or eax,0FFFFFFFFh
    L_004201a2:
        call asm_security_check_cookie_00458ea5
    L_004201a7:
        add esp,88h
    L_004201ad:
        ret
    }
}
