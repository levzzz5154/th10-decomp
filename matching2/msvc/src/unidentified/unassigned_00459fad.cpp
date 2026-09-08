#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459FAD..0x0045A098: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00459fad() {
    __asm {
    L_00459fad:
        mov eax,dword ptr [data_004991e0]
    L_00459fb2:
        test eax,eax
    L_00459fb4:
        push esi
    L_00459fb5:
        push 14h
    L_00459fb7:
        pop esi
    L_00459fb8:
        jne short L_00459fc1
    L_00459fba:
        mov eax,200h
    L_00459fbf:
        jmp short L_00459fc7
    L_00459fc1:
        cmp eax,esi
    L_00459fc3:
        jge short L_00459fcc
    L_00459fc5:
        mov eax,esi
    L_00459fc7:
        mov dword ptr [data_004991e0],eax
    L_00459fcc:
        push 4
    L_00459fce:
        push eax
    L_00459fcf:
        call asm_FUN_0045794d_0045794d
    L_00459fd4:
        test eax,eax
    L_00459fd6:
        pop ecx
    L_00459fd7:
        pop ecx
    L_00459fd8:
        mov dword ptr [data_004981d4],eax
    L_00459fdd:
        jne short L_00459ffd
    L_00459fdf:
        push 4
    L_00459fe1:
        push esi
    L_00459fe2:
        mov dword ptr [data_004991e0],esi
    L_00459fe8:
        call asm_FUN_0045794d_0045794d
    L_00459fed:
        test eax,eax
    L_00459fef:
        pop ecx
    L_00459ff0:
        pop ecx
    L_00459ff1:
        mov dword ptr [data_004981d4],eax
    L_00459ff6:
        jne short L_00459ffd
    L_00459ff8:
        push 1Ah
    L_00459ffa:
        pop eax
    L_00459ffb:
        pop esi
    L_00459ffc:
        ret
    L_00459ffd:
        xor edx,edx
    L_00459fff:
        mov ecx,473740h
    L_0045a004:
        jmp short L_0045a00b
    L_0045a006:
        mov eax,dword ptr [data_004981d4]
    L_0045a00b:
        mov dword ptr [edx+eax],ecx
    L_0045a00e:
        add ecx,20h
    L_0045a011:
        add edx,4
    L_0045a014:
        cmp ecx,4739C0h
    L_0045a01a:
        jl short L_0045a006
    L_0045a01c:
        xor ecx,ecx
    L_0045a01e:
        mov edx,473750h
    L_0045a023:
        mov esi,ecx
    L_0045a025:
        mov eax,ecx
    L_0045a027:
        and eax,1Fh
    L_0045a02a:
        sar esi,5
    L_0045a02d:
        mov esi,dword ptr [esi*4+499200h]
    L_0045a034:
        lea eax,[eax+eax*8]
    L_0045a037:
        mov eax,dword ptr [esi+eax*4]
    L_0045a03a:
        cmp eax,0FFFFFFFFh
    L_0045a03d:
        je short L_0045a043
    L_0045a03f:
        test eax,eax
    L_0045a041:
        jne short L_0045a046
    L_0045a043:
        or dword ptr [edx],0FFFFFFFFh
    L_0045a046:
        add edx,20h
    L_0045a049:
        inc ecx
    L_0045a04a:
        cmp edx,4737B0h
    L_0045a050:
        jl short L_0045a023
    L_0045a052:
        xor eax,eax
    L_0045a054:
        pop esi
    L_0045a055:
        ret
    L_0045a056:
        call asm_flushall_0045fda6
    L_0045a05b:
        cmp byte ptr [data_004774a8],0
    L_0045a062:
        je short L_0045a069
    L_0045a064:
        jmp asm_target_0045fb5b
    L_0045a069:
        ret
    L_0045a06a:
        mov eax,dword ptr [esp+4]
    L_0045a06e:
        mov ecx,473740h
    L_0045a073:
        cmp eax,ecx
    L_0045a075:
        jb short L_0045a08e
    L_0045a077:
        cmp eax,4739A0h
    L_0045a07c:
        ja short L_0045a08e
    L_0045a07e:
        sub eax,ecx
    L_0045a080:
        sar eax,5
    L_0045a083:
        add eax,10h
    L_0045a086:
        push eax
    L_0045a087:
        call asm_lock_00453c0c
    L_0045a08c:
        pop ecx
    L_0045a08d:
        ret
    L_0045a08e:
        add eax,20h
    L_0045a091:
        push eax
    L_0045a092:
        call dword ptr [data_004660b0]
    L_0045a098:
        ret
    }
}
