#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408910..0x004089BF: PlayerManager_ConstructRetail
// Naked body preserves the retail register/stack ABI.

// 0x0041AED0..0x0041AF88: FUN_0041aed0
// Naked body preserves the retail register/stack ABI.
// BLOCKED: closest_byte_count=185/185; first_diff=none (retail assembly baseline);
// residual_class=compiler-generated SEH registration/vector-constructor frame and
// EBX-held pair passed to the private installer;
// variants_tested=Ghidra pseudocode and caller ABI inspection; no source-only
// candidate accepted; next_lever=co-compile the real StageEntry caller with the
// installer in schema-2 native LTCG.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041aed0_0041aed0() {
    __asm {
    L_0041aed0:
        push 0FFFFFFFFh
    L_0041aed2:
        push 46580Bh
    L_0041aed7:
        mov eax,dword ptr fs:[0]
    L_0041aedd:
        push eax
    L_0041aede:
        mov dword ptr fs:[0],esp
    L_0041aee5:
        push ecx
    L_0041aee6:
        push esi
    L_0041aee7:
        push 21CEC0h
    L_0041aeec:
        call asm_operator_new_00452493
    L_0041aef1:
        mov esi,eax
    L_0041aef3:
        add esp,4
    L_0041aef6:
        mov dword ptr [esp+4],esi
    L_0041aefa:
        test esi,esi
    L_0041aefc:
        mov dword ptr [esp+10h],0
    L_0041af04:
        je short L_0041af3b
    L_0041af06:
        push edi
    L_0041af07:
        push 41AD60h
    L_0041af0c:
        push 41ACF0h
    L_0041af11:
        push 896h
    L_0041af16:
        push 3F0h
    L_0041af1b:
        lea eax,[esi+14h]
    L_0041af1e:
        push eax
    L_0041af1f:
        call asm_eh_vector_constructor_iterator_0045252d
    L_0041af24:
        xor eax,eax
    L_0041af26:
        mov ecx,873B0h
    L_0041af2b:
        mov edi,esi
    L_0041af2d:
        rep stosd
    L_0041af2f:
        or dword ptr [esi],2
    L_0041af32:
        mov dword ptr [data_00477818],esi
    L_0041af38:
        pop edi
    L_0041af39:
        jmp short L_0041af3d
    L_0041af3b:
        xor esi,esi
    L_0041af3d:
        push ebx
    L_0041af3e:
        mov ebx,esi
    L_0041af40:
        mov dword ptr [esp+14h],0FFFFFFFFh
    L_0041af48:
        call asm_Recovery_InstallPairClearFlags_0041ad90
    L_0041af4d:
        test eax,eax
    L_0041af4f:
        pop ebx
    L_0041af50:
        je short L_0041af77
    L_0041af52:
        test esi,esi
    L_0041af54:
        je short L_0041af65
    L_0041af56:
        push esi
    L_0041af57:
        call asm_FUN_0041adf0_0041adf0
    L_0041af5c:
        push esi
    L_0041af5d:
        call asm_free_004524a1
    L_0041af62:
        add esp,4
    L_0041af65:
        xor eax,eax
    L_0041af67:
        pop esi
    L_0041af68:
        mov ecx,dword ptr [esp+4]
    L_0041af6c:
        mov dword ptr fs:[0],ecx
    L_0041af73:
        add esp,10h
    L_0041af76:
        ret
    L_0041af77:
        mov ecx,dword ptr [esp+8]
    L_0041af7b:
        mov eax,esi
    L_0041af7d:
        pop esi
    L_0041af7e:
        mov dword ptr fs:[0],ecx
    L_0041af85:
        add esp,10h
    L_0041af88:
        ret
    }
}
