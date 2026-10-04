// The retail wrapper remains exact (550/550 bytes). The complete readable
// candidate in ecl_child_pair.cpp emits 549 bytes with 416 differing bytes
// including extent; it is an unselected anchor, not a recovered implementation.
// Its 142-byte SpawnChild caller is recovered and byte exact. Ghidra confirms a private
// EAX VM receiver, two stack arguments (source VM/frame and operand index),
// and RET 8. The real callers are the 0x0044E1A0 dispatcher and
// 0x004500D0 SpawnChild; the latter creates the child VM/list node and passes
// that new VM in EAX. The function reads typed operands from the source
// operand table, initializes the child value stack, and resolves its script
// label. See ecl_vm_start_child_0044df70_cluster.md for caller and helper ABI
// evidence; ecl_child_home_controls_0044df70_2026_10_04.md records later
// parameter-home and branch controls. Keep the exact wrapper until the full
// caller/resolver cluster yields a byte-exact readable body.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF70..0x0044E195: EclVm_StartChildRetail
extern "C" __declspec(naked) void __cdecl asm_EclVm_StartChildRetail_0044df70() {
    __asm {
    L_0044df70:
        sub esp,10h
    L_0044df73:
        mov edx,dword ptr [esp+18h]
    L_0044df77:
        push ebx
    L_0044df78:
        push ebp
    L_0044df79:
        push esi
    L_0044df7a:
        push edi
    L_0044df7b:
        mov edi,dword ptr [esp+24h]
    L_0044df7f:
        add edi,4
    L_0044df82:
        mov esi,eax
    L_0044df84:
        mov eax,dword ptr [edi]
    L_0044df86:
        mov ecx,dword ptr [eax+10h]
    L_0044df89:
        mov eax,dword ptr [esi+1008h]
    L_0044df8f:
        lea ebp,[ecx+edx*4+4]
    L_0044df93:
        xor edx,edx
    L_0044df95:
        test eax,eax
    L_0044df97:
        mov dword ptr [esp+14h],edx
    L_0044df9b:
        mov dword ptr [esp+1Ch],eax
    L_0044df9f:
        lea ecx,[eax+8]
    L_0044dfa2:
        jne short L_0044dfc1
    L_0044dfa4:
        mov ecx,eax
    L_0044dfa6:
        lea ebx,[ecx+4]
    L_0044dfa9:
        cmp ebx,1000h
    L_0044dfaf:
        jge short L_0044dfbc
    L_0044dfb1:
        mov dword ptr [ecx+esi+8],edx
    L_0044dfb5:
        add dword ptr [esi+1008h],4
    L_0044dfbc:
        mov ecx,0Ch
    L_0044dfc1:
        mov edx,dword ptr [edi]
    L_0044dfc3:
        mov ebx,dword ptr [esp+28h]
    L_0044dfc7:
        movzx edx,byte ptr [edx+0Bh]
    L_0044dfcb:
        inc ebx
    L_0044dfcc:
        cmp ebx,edx
    L_0044dfce:
        jge asm_target_0044e08e
    L_0044dfd4:
        lea eax,[ecx+esi+8]
    L_0044dfd8:
        mov dword ptr [esp+28h],eax
    L_0044dfdc:
        lea eax,[ebp+4]
    L_0044dfdf:
        mov dword ptr [esp+10h],eax
    L_0044dfe3:
        jmp short L_0044dff0
    L_0044dfe5:
        mov eax,dword ptr [esp+10h]
    L_0044dfe9:
        lea esp,[esp+force_disp32_zero]
    L_0044dff0:
        mov ecx,dword ptr [edi]
    L_0044dff2:
        mov dl,byte ptr [ecx+ebp+10h]
    L_0044dff6:
        cmp dl,66h
    L_0044dff9:
        je short L_0044e033
    L_0044dffb:
        cmp dl,67h
    L_0044dffe:
        je short L_0044e033
    L_0044e000:
        mov edx,dword ptr [esp+24h]
    L_0044e004:
        shr eax,2
    L_0044e007:
        mov ecx,dword ptr [ecx+eax*4+10h]
    L_0044e00b:
        push ecx
    L_0044e00c:
        push ebx
    L_0044e00d:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0044e012:
        mov edx,dword ptr [edi]
    L_0044e014:
        cmp byte ptr [edx+ebp+11h],66h
    L_0044e019:
        mov dword ptr [esp+18h],eax
    L_0044e01d:
        jne short L_0044e02b
    L_0044e01f:
        fild dword ptr [esp+18h]
    L_0044e023:
        mov eax,dword ptr [esp+28h]
    L_0044e027:
        fstp dword ptr [eax]
    L_0044e029:
        jmp short L_0044e062
    L_0044e02b:
        mov ecx,dword ptr [esp+28h]
    L_0044e02f:
        mov dword ptr [ecx],eax
    L_0044e031:
        jmp short L_0044e062
    L_0044e033:
        shr eax,2
    L_0044e036:
        mov edx,dword ptr [ecx+eax*4+10h]
    L_0044e03a:
        mov eax,dword ptr [esp+24h]
    L_0044e03e:
        push edx
    L_0044e03f:
        mov ecx,ebx
    L_0044e041:
        call asm_ECL_ResolveFloatValue_0044ff80
    L_0044e046:
        mov eax,dword ptr [edi]
    L_0044e048:
        cmp byte ptr [eax+ebp+11h],66h
    L_0044e04d:
        jne short L_0044e057
    L_0044e04f:
        mov ecx,dword ptr [esp+28h]
    L_0044e053:
        fstp dword ptr [ecx]
    L_0044e055:
        jmp short L_0044e062
    L_0044e057:
        call asm_FUN_00463b2c_00463b2c
    L_0044e05c:
        mov edx,dword ptr [esp+28h]
    L_0044e060:
        mov dword ptr [edx],eax
    L_0044e062:
        mov ecx,dword ptr [esp+28h]
    L_0044e066:
        mov eax,dword ptr [edi]
    L_0044e068:
        mov edx,dword ptr [esp+10h]
    L_0044e06c:
        add ecx,4
    L_0044e06f:
        mov dword ptr [esp+28h],ecx
    L_0044e073:
        movzx ecx,byte ptr [eax+0Bh]
    L_0044e077:
        inc ebx
    L_0044e078:
        add edx,8
    L_0044e07b:
        add ebp,8
    L_0044e07e:
        cmp ebx,ecx
    L_0044e080:
        mov dword ptr [esp+10h],edx
    L_0044e084:
        jl asm_target_0044dfe5
    L_0044e08a:
        mov eax,dword ptr [esp+1Ch]
    L_0044e08e:
        test eax,eax
    L_0044e090:
        mov edx,dword ptr [esp+24h]
    L_0044e094:
        mov ebx,4
    L_0044e099:
        je short L_0044e0f4
    L_0044e09b:
        mov ecx,dword ptr [esi+1008h]
    L_0044e0a1:
        add ecx,0FFFFFFFCh
    L_0044e0a4:
        js short L_0044e0b4
    L_0044e0a6:
        mov dword ptr [esi+1008h],ecx
    L_0044e0ac:
        mov ecx,dword ptr [ecx+esi+8]
    L_0044e0b0:
        mov dword ptr [esp+14h],ecx
    L_0044e0b4:
        mov ecx,dword ptr [esp+14h]
    L_0044e0b8:
        mov dword ptr [esi+1008h],eax
    L_0044e0be:
        mov dword ptr [eax+esi+4],ecx
    L_0044e0c2:
        mov eax,dword ptr [esi+1008h]
    L_0044e0c8:
        lea ecx,[eax+4]
    L_0044e0cb:
        cmp ecx,1000h
    L_0044e0d1:
        jge short L_0044e0df
    L_0044e0d3:
        mov ecx,dword ptr [edx]
    L_0044e0d5:
        mov dword ptr [eax+esi+8],ecx
    L_0044e0d9:
        add dword ptr [esi+1008h],ebx
    L_0044e0df:
        mov eax,dword ptr [esi+1008h]
    L_0044e0e5:
        lea ecx,[eax+4]
    L_0044e0e8:
        cmp ecx,1000h
    L_0044e0ee:
        jge short L_0044e12e
    L_0044e0f0:
        mov ecx,dword ptr [edi]
    L_0044e0f2:
        jmp short L_0044e124
    L_0044e0f4:
        mov eax,ebx
    L_0044e0f6:
        lea ebp,[eax+4]
    L_0044e0f9:
        xor ecx,ecx
    L_0044e0fb:
        cmp ebp,1000h
    L_0044e101:
        mov dword ptr [esi+1008h],ebx
    L_0044e107:
        jge short L_0044e113
    L_0044e109:
        mov dword ptr [eax+esi+8],ecx
    L_0044e10d:
        add dword ptr [esi+1008h],ebx
    L_0044e113:
        mov eax,dword ptr [esi+1008h]
    L_0044e119:
        lea ebp,[eax+4]
    L_0044e11c:
        cmp ebp,1000h
    L_0044e122:
        jge short L_0044e12e
    L_0044e124:
        mov dword ptr [eax+esi+8],ecx
    L_0044e128:
        add dword ptr [esi+1008h],ebx
    L_0044e12e:
        mov eax,dword ptr [edx+1014h]
    L_0044e134:
        mov ebx,dword ptr [eax+4]
    L_0044e137:
        mov dword ptr [eax+4],esi
    L_0044e13a:
        mov esi,dword ptr [edx+1014h]
    L_0044e140:
        mov edx,dword ptr [edi]
    L_0044e142:
        mov eax,dword ptr [esi+102Ch]
    L_0044e148:
        add edx,14h
    L_0044e14b:
        push edx
    L_0044e14c:
        call asm_FUN_00450470_00450470
    L_0044e151:
        mov ecx,dword ptr [esi+4]
    L_0044e154:
        mov dword ptr [ecx+4],eax
    L_0044e157:
        mov edx,dword ptr [esi+4]
    L_0044e15a:
        mov dword ptr [edx],0
    L_0044e160:
        mov eax,dword ptr [esi+4]
    L_0044e163:
        mov ecx,dword ptr [eax+4]
    L_0044e166:
        test ecx,ecx
    L_0044e168:
        jne short L_0044e17d
    L_0044e16a:
        mov dword ptr [edi],0
    L_0044e170:
        pop edi
    L_0044e171:
        pop esi
    L_0044e172:
        pop ebp
    L_0044e173:
        or eax,0FFFFFFFFh
    L_0044e176:
        pop ebx
    L_0044e177:
        add esp,10h
    L_0044e17a:
        ret 8
    L_0044e17d:
        mov ecx,dword ptr [esp+24h]
    L_0044e181:
        mov edx,dword ptr [ecx+1014h]
    L_0044e187:
        pop edi
    L_0044e188:
        pop esi
    L_0044e189:
        pop ebp
    L_0044e18a:
        mov dword ptr [edx+4],ebx
    L_0044e18d:
        xor eax,eax
    L_0044e18f:
        pop ebx
    L_0044e190:
        add esp,10h
    L_0044e193:
        ret 8
    }
}
