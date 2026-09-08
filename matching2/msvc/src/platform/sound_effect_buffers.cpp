#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043DB60..0x0043DBD8: FUN_0043db60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043db60_0043db60() {
    __asm {
    L_0043db60:
        or eax,0FFFFFFFFh
    L_0043db63:
        mov dword ptr [ebx+620h],eax
    L_0043db69:
        mov dword ptr [ebx+624h],eax
    L_0043db6f:
        mov dword ptr [ebx+628h],eax
    L_0043db75:
        mov dword ptr [ebx+62Ch],eax
    L_0043db7b:
        mov dword ptr [ebx+630h],eax
    L_0043db81:
        mov dword ptr [ebx+634h],eax
    L_0043db87:
        mov dword ptr [ebx+638h],eax
    L_0043db8d:
        mov dword ptr [ebx+63Ch],eax
    L_0043db93:
        mov dword ptr [ebx+640h],eax
    L_0043db99:
        mov dword ptr [ebx+644h],eax
    L_0043db9f:
        push esi
    L_0043dba0:
        mov dword ptr [ebx+648h],eax
    L_0043dba6:
        mov esi,492590h
    L_0043dbab:
        mov dword ptr [ebx+64Ch],eax
    L_0043dbb1:
        call asm_Platform_StopSoundWorkersRetail_0043cc40
    L_0043dbb6:
        mov eax,dword ptr [ebx+610h]
    L_0043dbbc:
        test eax,eax
    L_0043dbbe:
        jne short L_0043dbc5
    L_0043dbc0:
        or eax,0FFFFFFFFh
    L_0043dbc3:
        pop esi
    L_0043dbc4:
        ret
    L_0043dbc5:
        cmp dword ptr [ebx],0
    L_0043dbc8:
        je asm_target_0043dc83
    L_0043dbce:
        push edi
    L_0043dbcf:
        lea edi,[ebx+208h]
    L_0043dbd5:
        xor esi,esi
    L_0043dbd7:
        TH10_REL8(0xeb, 0x0043dbd7, VA_asm_FUN_0043db60_part_0043dbe0)
    }
}

// 0x0043DBE0..0x0043DC86: FUN_0043db60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043db60_part_0043dbe0() {
    __asm {
    L_0043dbe0:
        mov edx,dword ptr [esi+4749C8h]
    L_0043dbe6:
        mov edx,dword ptr [ebx+edx*4+8]
    L_0043dbea:
        mov eax,dword ptr [ebx]
    L_0043dbec:
        mov ecx,dword ptr [eax]
    L_0043dbee:
        push edi
    L_0043dbef:
        push edx
    L_0043dbf0:
        push eax
    L_0043dbf1:
        call dword ptr [ecx+14h]
    L_0043dbf4:
        mov eax,dword ptr [edi]
    L_0043dbf6:
        mov ecx,dword ptr [eax]
    L_0043dbf8:
        push 0
    L_0043dbfa:
        push eax
    L_0043dbfb:
        call dword ptr [ecx+34h]
    L_0043dbfe:
        movsx ecx,word ptr [esi+4749CCh]
    L_0043dc05:
        mov eax,dword ptr [edi]
    L_0043dc07:
        mov edx,dword ptr [eax]
    L_0043dc09:
        push ecx
    L_0043dc0a:
        push eax
    L_0043dc0b:
        call dword ptr [edx+3Ch]
    L_0043dc0e:
        add esi,8
    L_0043dc11:
        add edi,4
    L_0043dc14:
        cmp esi,178h
    L_0043dc1a:
        jb short L_0043dbe0
    L_0043dc1c:
        movsx edx,byte ptr [data_00491d68]
    L_0043dc23:
        mov dword ptr [ebx+52C4h],edx
    L_0043dc29:
        movsx eax,byte ptr [data_00491d69]
    L_0043dc30:
        test eax,eax
    L_0043dc32:
        mov dword ptr [ebx+52C8h],eax
    L_0043dc38:
        pop edi
    L_0043dc39:
        je short L_0043dc79
    L_0043dc3b:
        fild dword ptr [ebx+52C4h]
    L_0043dc41:
        fmul dword ptr [data_00470b00]
    L_0043dc47:
        fsubr dword ptr [data_00470afc]
    L_0043dc4d:
        fld st(0)
    L_0043dc4f:
        fmulp st(1),st
    L_0043dc51:
        fld st(0)
    L_0043dc53:
        fmul st,st(1)
    L_0043dc55:
        fsubr dword ptr [data_00470afc]
    L_0043dc5b:
        fmul dword ptr [data_00470b80]
    L_0043dc61:
        call asm_FUN_00463b2c_00463b2c
    L_0043dc66:
        fstp st(0)
    L_0043dc68:
        mov ecx,0FFFFEC78h
    L_0043dc6d:
        sub ecx,eax
    L_0043dc6f:
        mov dword ptr [ebx+52CCh],ecx
    L_0043dc75:
        xor eax,eax
    L_0043dc77:
        pop esi
    L_0043dc78:
        ret
    L_0043dc79:
        mov dword ptr [ebx+52CCh],0FFFFD8F0h
    L_0043dc83:
        xor eax,eax
    L_0043dc85:
        pop esi
    L_0043dc86:
        ret
    }
}
