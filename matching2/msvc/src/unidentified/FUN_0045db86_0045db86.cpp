#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045DB86..0x0045DBDA: FUN_0045db86
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045db86_0045db86() {
    __asm {
    L_0045db86:
        push ebp
    L_0045db87:
        mov ebp,esp
    L_0045db89:
        sub esp,10h
    L_0045db8c:
        mov eax,dword ptr [data_00473660]
    L_0045db91:
        mov ecx,dword ptr [ebp+10h]
    L_0045db94:
        push esi
    L_0045db95:
        mov esi,dword ptr [ebp+8]
    L_0045db98:
        push edi
    L_0045db99:
        xor edx,edx
    L_0045db9b:
        push edx
    L_0045db9c:
        push edx
    L_0045db9d:
        push edx
    L_0045db9e:
        push dword ptr [ebp+14h]
    L_0045dba1:
        xor eax,ebp
    L_0045dba3:
        mov dword ptr [ebp-4],eax
    L_0045dba6:
        mov eax,dword ptr [ebp+0Ch]
    L_0045dba9:
        push ecx
    L_0045dbaa:
        push eax
    L_0045dbab:
        lea eax,[ebp-10h]
    L_0045dbae:
        push eax
    L_0045dbaf:
        call asm_FUN_0045d746_0045d746
    L_0045dbb4:
        mov edi,eax
    L_0045dbb6:
        lea eax,[ebp-10h]
    L_0045dbb9:
        push esi
    L_0045dbba:
        push eax
    L_0045dbbb:
        call asm_ld12told_0045d5fa
    L_0045dbc0:
        add esp,24h
    L_0045dbc3:
        cmp eax,1
    L_0045dbc6:
        jne short L_0045dbcb
    L_0045dbc8:
        or edi,2
    L_0045dbcb:
        mov ecx,dword ptr [ebp-4]
    L_0045dbce:
        mov eax,edi
    L_0045dbd0:
        pop edi
    L_0045dbd1:
        xor ecx,ebp
    L_0045dbd3:
        pop esi
    L_0045dbd4:
        call asm_security_check_cookie_00458ea5
    L_0045dbd9:
        leave
    L_0045dbda:
        ret
    }
}
