#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED: closest_byte_count=129/268; first_diff=0x0042109B;
// residual_class=AnimationManager_Find consumes EDX context plus a stack id
// while ECX is ignored, with compiler-selected loop-tail padding;
// variants_tested=live Ghidra decompile/callers (0x00421070, 0x00417870)
// and MSVC 13.10 readable node/record candidate (268-byte extent, 129 matching
// bytes); next_lever=schema2 native-LTCG or a proven private-call declaration
// that preserves the retail EDX/stack split.

// 0x00421070..0x004210B8: FUN_00421070
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421070_00421070() {
    __asm {
    L_00421070:
        push ebp
    L_00421071:
        mov ebp,dword ptr [esp+8]
    L_00421075:
        mov eax,dword ptr [ebp+6FCh]
    L_0042107b:
        push esi
    L_0042107c:
        push edi
    L_0042107d:
        mov esi,1
    L_00421082:
        xor edi,edi
    L_00421084:
        cmp eax,esi
    L_00421086:
        jne asm_target_00421168
    L_0042108c:
        mov eax,dword ptr [data_00477824]
    L_00421091:
        push ebx
    L_00421092:
        mov ebx,dword ptr [data_00491c10]
    L_00421098:
        push eax
    L_00421099:
        mov edx,ebx
    L_0042109b:
        call asm_AnimationManager_Find_004491c0
    L_004210a0:
        cmp eax,edi
    L_004210a2:
        TH10_REL8(0x74, 0x004210a2, VA_asm_target_004210d0)
    L_004210a4:
        cmp dword ptr [eax+18h],edi
    L_004210a7:
        mov word ptr [eax+304h],si
    L_004210ae:
        TH10_REL8(0x75, 0x004210ae, VA_asm_target_004210d0)
    L_004210b0:
        mov eax,dword ptr [eax+14h]
    L_004210b3:
        cmp eax,edi
    L_004210b5:
        TH10_REL8(0x74, 0x004210b5, VA_asm_target_004210d0)
    L_004210b7:
        TH10_REL8(0xeb, 0x004210b7, VA_asm_FUN_00421070_part_004210c0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_004210c0:
        mov ecx,dword ptr [eax]
    L_004210c2:
        mov word ptr [ecx+304h],si
    L_004210c9:
        mov eax,dword ptr [eax+4]
    L_004210cc:
        cmp eax,edi
    L_004210ce:
        jne short L_004210c0
    L_004210d0:
        mov edx,dword ptr [data_00477828]
    L_004210d6:
        push edx
    L_004210d7:
        mov edx,ebx
    L_004210d9:
        call asm_AnimationManager_Find_004491c0
    L_004210de:
        cmp eax,edi
    L_004210e0:
        TH10_REL8(0x74, 0x004210e0, VA_asm_target_00421110)
    L_004210e2:
        cmp dword ptr [eax+18h],edi
    L_004210e5:
        mov word ptr [eax+304h],si
    L_004210ec:
        TH10_REL8(0x75, 0x004210ec, VA_asm_target_00421110)
    L_004210ee:
        mov eax,dword ptr [eax+14h]
    L_004210f1:
        cmp eax,edi
    L_004210f3:
        TH10_REL8(0x74, 0x004210f3, VA_asm_target_00421110)
    L_004210f5:
        TH10_REL8(0xeb, 0x004210f5, VA_asm_FUN_00421070_part_00421100)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xff

    L_00421100:
        mov ecx,dword ptr [eax]
    L_00421102:
        mov word ptr [ecx+304h],si
    L_00421109:
        mov eax,dword ptr [eax+4]
    L_0042110c:
        cmp eax,edi
    L_0042110e:
        jne short L_00421100
    L_00421110:
        mov edx,dword ptr [data_0047782c]
    L_00421116:
        push edx
    L_00421117:
        mov edx,ebx
    L_00421119:
        call asm_AnimationManager_Find_004491c0
    L_0042111e:
        cmp eax,edi
    L_00421120:
        pop ebx
    L_00421121:
        TH10_REL8(0x74, 0x00421121, VA_asm_target_00421150)
    L_00421123:
        cmp dword ptr [eax+18h],edi
    L_00421126:
        mov word ptr [eax+304h],si
    L_0042112d:
        TH10_REL8(0x75, 0x0042112d, VA_asm_target_00421150)
    L_0042112f:
        mov eax,dword ptr [eax+14h]
    L_00421132:
        cmp eax,edi
    L_00421134:
        TH10_REL8(0x74, 0x00421134, VA_asm_target_00421150)
    L_00421136:
        TH10_REL8(0xeb, 0x00421136, VA_asm_FUN_00421070_part_00421140)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_00421140:
        mov ecx,dword ptr [eax]
    L_00421142:
        mov word ptr [ecx+304h],si
    L_00421149:
        mov eax,dword ptr [eax+4]
    L_0042114c:
        cmp eax,edi
    L_0042114e:
        jne short L_00421140
    L_00421150:
        mov dword ptr [data_00477824],edi
    L_00421156:
        mov dword ptr [data_00477828],edi
    L_0042115c:
        mov dword ptr [data_0047782c],edi
    L_00421162:
        mov dword ptr [ebp+6FCh],edi
    L_00421168:
        cmp dword ptr [data_00491bec],edi
    L_0042116e:
        je short L_00421176
    L_00421170:
        mov dword ptr [data_00491bec],edi
    L_00421176:
        pop edi
    L_00421177:
        pop esi
    L_00421178:
        pop ebp
    L_00421179:
        ret 4
    }
}
