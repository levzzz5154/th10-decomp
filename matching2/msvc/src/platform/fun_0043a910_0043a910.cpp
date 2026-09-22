// BLOCKED (D3801): closest_byte_count=0/156; first_diff=none (exact retail
// naked baseline; no readable candidate retained).
// residual_class=private EAX receiver despite the decompiler's __fastcall
// spelling, caller-preserved ESI/EDI state, and MIDI helper/import scheduling.
// variants_tested=live Ghidra decompilation at 0x0043A910 with callers
// GameMain xrefs 0x00438F29/0x00439082; typed receiver cleanup candidate;
// exact MSVC 13.10 naked baseline probe=156/156.
// next_lever=native-LTCG cluster joining GameMain, FUN_0043AE20,
// FUN_0043AA60 and the MIDI import slots; preserve the caller's EAX handoff.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A910..0x0043A9AB: FUN_0043a910
// Naked body preserves the retail register/stack ABI.
// 0x0043A910..0x0043A9AB: FUN_0043a910
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a910_0043a910() {
    __asm {
    L_0043a910:
        push ebx
    L_0043a911:
        push esi
    L_0043a912:
        mov esi,eax
    L_0043a914:
        push edi
    L_0043a915:
        mov edi,esi
    L_0043a917:
        mov dword ptr [esi],46F80Ch
    L_0043a91d:
        call asm_FUN_0043ae20_0043ae20
    L_0043a922:
        call asm_FUN_0043aa60_0043aa60
    L_0043a927:
        lea ebx,[esi+98h]
    L_0043a92d:
        mov edi,20h
    L_0043a932:
        mov eax,dword ptr [ebx]
    L_0043a934:
        test eax,eax
    L_0043a936:
        je short L_0043a947
    L_0043a938:
        push eax
    L_0043a939:
        call asm_free_00452422
    L_0043a93e:
        add esp,4
    L_0043a941:
        mov dword ptr [ebx],0
    L_0043a947:
        mov dword ptr [ebx],0
    L_0043a94d:
        add ebx,4
    L_0043a950:
        dec edi
    L_0043a951:
        jne short L_0043a932
    L_0043a953:
        mov eax,dword ptr [esi+13Ch]
    L_0043a959:
        test eax,eax
    L_0043a95b:
        je short L_0043a97b
    L_0043a95d:
        push eax
    L_0043a95e:
        call dword ptr [data_004662a8]
    L_0043a964:
        mov eax,dword ptr [esi+13Ch]
    L_0043a96a:
        push eax
    L_0043a96b:
        call dword ptr [data_004662a4]
    L_0043a971:
        mov dword ptr [esi+13Ch],0
    L_0043a97b:
        mov eax,dword ptr [esi+4]
    L_0043a97e:
        test eax,eax
    L_0043a980:
        mov dword ptr [esi],46F810h
    L_0043a986:
        je short L_0043a98f
    L_0043a988:
        push eax
    L_0043a989:
        call dword ptr [data_00466288]
    L_0043a98f:
        mov ecx,dword ptr [esi+8]
    L_0043a992:
        mov edi,dword ptr [data_00466274]
    L_0043a998:
        push ecx
    L_0043a999:
        call edi
    L_0043a99b:
        mov edx,dword ptr [esi+8]
    L_0043a99e:
        push edx
    L_0043a99f:
        mov dword ptr [esi+4],0
    L_0043a9a6:
        call edi
    L_0043a9a8:
        pop edi
    L_0043a9a9:
        pop esi
    L_0043a9aa:
        pop ebx
    L_0043a9ab:
        ret
    }
}
