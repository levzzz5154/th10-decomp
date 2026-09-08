#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004610F4..0x00461183: ___wtomb_environ
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_wtomb_environ_004610f4() {
    __asm {
    L_004610f4:
        push ebp
    L_004610f5:
        mov ebp,esp
    L_004610f7:
        push ecx
    L_004610f8:
        push ecx
    L_004610f9:
        push ebx
    L_004610fa:
        push esi
    L_004610fb:
        xor esi,esi
    L_004610fd:
        push edi
    L_004610fe:
        mov edi,dword ptr [data_00477498]
    L_00461104:
        mov dword ptr [ebp-4],esi
    L_00461107:
        mov eax,dword ptr [edi]
    L_00461109:
        cmp eax,esi
    L_0046110b:
        je short L_0046116f
    L_0046110d:
        mov ebx,dword ptr [data_00466154]
    L_00461113:
        push esi
    L_00461114:
        push esi
    L_00461115:
        push esi
    L_00461116:
        push esi
    L_00461117:
        push 0FFFFFFFFh
    L_00461119:
        push eax
    L_0046111a:
        push esi
    L_0046111b:
        push esi
    L_0046111c:
        call ebx
    L_0046111e:
        cmp eax,esi
    L_00461120:
        mov dword ptr [ebp-8],eax
    L_00461123:
        je short L_0046117f
    L_00461125:
        push eax
    L_00461126:
        call asm_malloc_00452706
    L_0046112b:
        cmp eax,esi
    L_0046112d:
        pop ecx
    L_0046112e:
        mov dword ptr [ebp-4],eax
    L_00461131:
        je short L_0046117f
    L_00461133:
        push esi
    L_00461134:
        push esi
    L_00461135:
        push dword ptr [ebp-8]
    L_00461138:
        push eax
    L_00461139:
        push 0FFFFFFFFh
    L_0046113b:
        push dword ptr [edi]
    L_0046113d:
        push esi
    L_0046113e:
        push esi
    L_0046113f:
        call ebx
    L_00461141:
        test eax,eax
    L_00461143:
        je short L_00461176
    L_00461145:
        lea eax,[ebp-4]
    L_00461148:
        push esi
    L_00461149:
        push eax
    L_0046114a:
        call asm_FUN_00461f31_00461f31
    L_0046114f:
        test eax,eax
    L_00461151:
        pop ecx
    L_00461152:
        pop ecx
    L_00461153:
        jge short L_00461166
    L_00461155:
        cmp dword ptr [ebp-4],esi
    L_00461158:
        je short L_00461166
    L_0046115a:
        push dword ptr [ebp-4]
    L_0046115d:
        call asm_free_00452422
    L_00461162:
        pop ecx
    L_00461163:
        mov dword ptr [ebp-4],esi
    L_00461166:
        add edi,4
    L_00461169:
        mov eax,dword ptr [edi]
    L_0046116b:
        cmp eax,esi
    L_0046116d:
        jne short L_00461113
    L_0046116f:
        xor eax,eax
    L_00461171:
        pop edi
    L_00461172:
        pop esi
    L_00461173:
        pop ebx
    L_00461174:
        leave
    L_00461175:
        ret
    L_00461176:
        push dword ptr [ebp-4]
    L_00461179:
        call asm_free_00452422
    L_0046117e:
        pop ecx
    L_0046117f:
        or eax,0FFFFFFFFh
    L_00461182:
        jmp short L_00461171
    }
}
