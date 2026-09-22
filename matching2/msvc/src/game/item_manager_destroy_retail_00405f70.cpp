// BLOCKED (D3404): closest_byte_count=0/236; first_diff=0x00405F70;
// residual_class=SEH registration/unregistration frame, __stdcall cleanup,
// critical-section function-pointer globals, and the +0x3e0b50 archive-owner
// layout crossing the AnimationManager removal call.
// variants_tested=live Ghidra decompilation plus callers 0x00406060,
// 0x0040A1A0, and 0x00417C80, helper chain 0x00449F60/0x004493E0/0x004525FF,
// and typed readable MSVC 13.10 candidate (197/236 extent).
// next_lever=schema2 native-LTCG over the real callers, this body, scheduler
// remove, animation-resource removal, and EH vector destructor; preserve the
// FS:[0] frame and RET 4.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405F70..0x0040605B: ItemManager_DestroyRetail
// Naked body preserves the retail register/stack ABI.

// 0x00405F70..0x0040605B: ItemManager_DestroyRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ItemManager_DestroyRetail_00405f70() {
    __asm {
    L_00405f70:
        mov eax,dword ptr fs:[0]
    L_00405f76:
        push 0FFFFFFFFh
    L_00405f78:
        push 46553Ch
    L_00405f7d:
        push eax
    L_00405f7e:
        mov dword ptr fs:[0],esp
    L_00405f85:
        push ebx
    L_00405f86:
        push ebp
    L_00405f87:
        push esi
    L_00405f88:
        push edi
    L_00405f89:
        mov dword ptr [esp+18h],0
    L_00405f91:
        mov eax,dword ptr [esp+20h]
    L_00405f95:
        mov esi,dword ptr [eax+8]
    L_00405f98:
        test esi,esi
    L_00405f9a:
        mov edi,dword ptr [data_00491be4]
    L_00405fa0:
        mov ebx,dword ptr [data_004660b0]
    L_00405fa6:
        mov ebp,dword ptr [data_004660b4]
    L_00405fac:
        je short L_00405fd1
    L_00405fae:
        push 492274h
    L_00405fb3:
        call ebx
    L_00405fb5:
        inc byte ptr [data_0049231c]
    L_00405fbb:
        mov ecx,esi
    L_00405fbd:
        mov edx,edi
    L_00405fbf:
        call asm_Scheduler_Remove_00449f60
    L_00405fc4:
        push 492274h
    L_00405fc9:
        call ebp
    L_00405fcb:
        dec byte ptr [data_0049231c]
    L_00405fd1:
        mov ecx,dword ptr [esp+20h]
    L_00405fd5:
        mov esi,dword ptr [ecx+0Ch]
    L_00405fd8:
        test esi,esi
    L_00405fda:
        mov edi,dword ptr [data_00491be4]
    L_00405fe0:
        je short L_00406005
    L_00405fe2:
        push 492274h
    L_00405fe7:
        call ebx
    L_00405fe9:
        inc byte ptr [data_0049231c]
    L_00405fef:
        mov ecx,esi
    L_00405ff1:
        mov edx,edi
    L_00405ff3:
        call asm_Scheduler_Remove_00449f60
    L_00405ff8:
        push 492274h
    L_00405ffd:
        call ebp
    L_00405fff:
        dec byte ptr [data_0049231c]
    L_00406005:
        mov edx,dword ptr [esp+20h]
    L_00406009:
        mov edx,dword ptr [edx+3E0B50h]
    L_0040600f:
        mov eax,dword ptr [data_00491c10]
    L_00406014:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_00406019:
        push 405DE0h
    L_0040601e:
        mov dword ptr [esp+1Ch],0FFFFFFFFh
    L_00406026:
        mov eax,dword ptr [esp+24h]
    L_0040602a:
        push 7D1h
    L_0040602f:
        push 7F0h
    L_00406034:
        add eax,60h
    L_00406037:
        push eax
    L_00406038:
        mov dword ptr [data_004776f0],0
    L_00406042:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00406047:
        mov ecx,dword ptr [esp+10h]
    L_0040604b:
        pop edi
    L_0040604c:
        pop esi
    L_0040604d:
        pop ebp
    L_0040604e:
        mov dword ptr fs:[0],ecx
    L_00406055:
        pop ebx
    L_00406056:
        add esp,0Ch
    L_00406059:
        ret 4
    }
}
