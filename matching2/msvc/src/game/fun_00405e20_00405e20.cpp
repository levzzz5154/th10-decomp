#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED (D3706): closest_byte_count=12/154; first_diff=0x00405E20
// residual_class=private EBX receiver and scheduler callback ABI; the typed
// readable candidate emitted 154 bytes versus the 163-byte retail body.
// variants_tested=live Ghidra decompile plus BulletManager readable member
// candidate under MSVC 13.10; exact assembly baseline was restored.
// next_lever=schema-2 native-LTCG cluster over real caller 00406060, this
// loader, callback factories, and both scheduler registration callees.

// 0x00402720..0x0040284F: FUN_00402720
// Naked body preserves the retail register/stack ABI.

// 0x00405E20..0x00405EC2: FUN_00405e20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405e20_00405e20() {
    __asm {
    L_00405e20:
        mov edx,dword ptr [data_00491c10]
    L_00405e26:
        push 46CD88h
    L_00405e2b:
        mov ecx,7
    L_00405e30:
        call asm_Recovery_LoadCachedResource_00447280
    L_00405e35:
        test eax,eax
    L_00405e37:
        mov dword ptr [ebx+3E0B50h],eax
    L_00405e3d:
        jne short L_00405e55
    L_00405e3f:
        push 46CD54h
    L_00405e44:
        mov ecx,474F70h
    L_00405e49:
        call asm_TextLog_Append_0044b810
    L_00405e4e:
        add esp,4
    L_00405e51:
        or eax,0FFFFFFFFh
    L_00405e54:
        ret
    L_00405e55:
        push esi
    L_00405e56:
        push edi
    L_00405e57:
        lea eax,[ebx+60h]
    L_00405e5a:
        push 406770h
    L_00405e5f:
        mov dword ptr [ebx+10h],eax
    L_00405e62:
        mov word ptr [ebx+3E07A6h],5
    L_00405e6b:
        call asm_SchedulerCallback_Create_00449ed0
    L_00405e70:
        mov ecx,dword ptr [data_00491be4]
    L_00405e76:
        mov esi,eax
    L_00405e78:
        mov eax,dword ptr [esi+4]
    L_00405e7b:
        and eax,0FFFFFFFDh
    L_00405e7e:
        push ecx
    L_00405e7f:
        mov edi,14h
    L_00405e84:
        mov dword ptr [esi+20h],ebx
    L_00405e87:
        mov dword ptr [esi+4],eax
    L_00405e8a:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_00405e8f:
        push 4067A0h
    L_00405e94:
        mov dword ptr [ebx+8],esi
    L_00405e97:
        call asm_SchedulerCallback_Create_00449ed0
    L_00405e9c:
        mov edx,dword ptr [data_00491be4]
    L_00405ea2:
        mov esi,eax
    L_00405ea4:
        mov ecx,dword ptr [esi+4]
    L_00405ea7:
        and ecx,0FFFFFFFDh
    L_00405eaa:
        push edx
    L_00405eab:
        mov edi,1Dh
    L_00405eb0:
        mov dword ptr [esi+20h],ebx
    L_00405eb3:
        mov dword ptr [esi+4],ecx
    L_00405eb6:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00405ebb:
        pop edi
    L_00405ebc:
        mov dword ptr [ebx+0Ch],esi
    L_00405ebf:
        xor eax,eax
    L_00405ec1:
        pop esi
    L_00405ec2:
        ret
    }
}
