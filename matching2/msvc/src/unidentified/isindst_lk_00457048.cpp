#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457048..0x004571CE: __isindst_lk
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_isindst_lk_00457048() {
    __asm {
    L_00457048:
        push esi
    L_00457049:
        xor esi,esi
    L_0045704b:
        cmp dword ptr [data_00473524],esi
    L_00457051:
        jne short L_00457057
    L_00457053:
        xor eax,eax
    L_00457055:
        pop esi
    L_00457056:
        ret
    L_00457057:
        push ebp
    L_00457058:
        xor ebp,ebp
    L_0045705a:
        push edi
    L_0045705b:
        mov edi,dword ptr [ebx+14h]
    L_0045705e:
        inc ebp
    L_0045705f:
        cmp edi,dword ptr [data_004735b8]
    L_00457065:
        jne short L_00457073
    L_00457067:
        cmp edi,dword ptr [data_004735c4]
    L_0045706d:
        je asm_target_0045715f
    L_00457073:
        cmp dword ptr [data_0047743c],esi
    L_00457079:
        je asm_target_00457133
    L_0045707f:
        cmp word ptr [data_00477428],si
    L_00457086:
        movzx eax,word ptr [data_00477436]
    L_0045708d:
        movzx ecx,word ptr [data_00477430]
    L_00457094:
        push eax
    L_00457095:
        movzx eax,word ptr [data_00477434]
    L_0045709c:
        push eax
    L_0045709d:
        movzx eax,word ptr [data_00477432]
    L_004570a4:
        push eax
    L_004570a5:
        jne short L_004570bc
    L_004570a7:
        movzx eax,word ptr [data_0047742c]
    L_004570ae:
        push esi
    L_004570af:
        push eax
    L_004570b0:
        movzx eax,word ptr [data_0047742e]
    L_004570b7:
        push eax
    L_004570b8:
        push edi
    L_004570b9:
        push ebp
    L_004570ba:
        jmp short L_004570c8
    L_004570bc:
        movzx eax,word ptr [data_0047742e]
    L_004570c3:
        push eax
    L_004570c4:
        push esi
    L_004570c5:
        push esi
    L_004570c6:
        push edi
    L_004570c7:
        push esi
    L_004570c8:
        movzx eax,word ptr [data_0047742a]
    L_004570cf:
        push ebp
    L_004570d0:
        call asm_cvtdate_00456e90
    L_004570d5:
        movzx eax,word ptr [data_004773e2]
    L_004570dc:
        movzx ecx,word ptr [data_004773dc]
    L_004570e3:
        add esp,24h
    L_004570e6:
        cmp word ptr [data_004773d4],si
    L_004570ed:
        push eax
    L_004570ee:
        movzx eax,word ptr [data_004773e0]
    L_004570f5:
        push eax
    L_004570f6:
        movzx eax,word ptr [data_004773de]
    L_004570fd:
        push eax
    L_004570fe:
        jne short L_00457125
    L_00457100:
        movzx eax,word ptr [data_004773d8]
    L_00457107:
        push esi
    L_00457108:
        push eax
    L_00457109:
        movzx eax,word ptr [data_004773da]
    L_00457110:
        push eax
    L_00457111:
        push edi
    L_00457112:
        push ebp
    L_00457113:
        movzx eax,word ptr [data_004773d6]
    L_0045711a:
        push esi
    L_0045711b:
        call asm_cvtdate_00456e90
    L_00457120:
        add esp,24h
    L_00457123:
        jmp short L_0045715f
    L_00457125:
        movzx eax,word ptr [data_004773da]
    L_0045712c:
        push eax
    L_0045712d:
        push esi
    L_0045712e:
        push esi
    L_0045712f:
        push edi
    L_00457130:
        push esi
    L_00457131:
        jmp short L_00457113
    L_00457133:
        push esi
    L_00457134:
        push esi
    L_00457135:
        push esi
    L_00457136:
        push esi
    L_00457137:
        push esi
    L_00457138:
        push ebp
    L_00457139:
        push edi
    L_0045713a:
        push ebp
    L_0045713b:
        push ebp
    L_0045713c:
        push 2
    L_0045713e:
        pop ecx
    L_0045713f:
        push 4
    L_00457141:
        pop eax
    L_00457142:
        call asm_cvtdate_00456e90
    L_00457147:
        push esi
    L_00457148:
        push esi
    L_00457149:
        push esi
    L_0045714a:
        push esi
    L_0045714b:
        push esi
    L_0045714c:
        push 5
    L_0045714e:
        push edi
    L_0045714f:
        push ebp
    L_00457150:
        push esi
    L_00457151:
        push 2
    L_00457153:
        pop ecx
    L_00457154:
        push 0Ah
    L_00457156:
        pop eax
    L_00457157:
        call asm_cvtdate_00456e90
    L_0045715c:
        add esp,48h
    L_0045715f:
        mov edx,dword ptr [data_004735bc]
    L_00457165:
        mov eax,dword ptr [data_004735c8]
    L_0045716a:
        cmp edx,eax
    L_0045716c:
        mov ecx,dword ptr [ebx+1Ch]
    L_0045716f:
        jge short L_0045718b
    L_00457171:
        cmp ecx,edx
    L_00457173:
        jl short L_00457187
    L_00457175:
        cmp ecx,eax
    L_00457177:
        jg short L_00457187
    L_00457179:
        cmp ecx,edx
    L_0045717b:
        jle short L_0045719b
    L_0045717d:
        cmp ecx,eax
    L_0045717f:
        jge short L_0045719b
    L_00457181:
        mov eax,ebp
    L_00457183:
        pop edi
    L_00457184:
        pop ebp
    L_00457185:
        pop esi
    L_00457186:
        ret
    L_00457187:
        xor eax,eax
    L_00457189:
        jmp short L_00457183
    L_0045718b:
        cmp ecx,eax
    L_0045718d:
        jl short L_00457181
    L_0045718f:
        cmp ecx,edx
    L_00457191:
        jg short L_00457181
    L_00457193:
        cmp ecx,eax
    L_00457195:
        jle short L_0045719b
    L_00457197:
        cmp ecx,edx
    L_00457199:
        jl short L_00457187
    L_0045719b:
        mov eax,dword ptr [ebx+8]
    L_0045719e:
        imul eax,3Ch
    L_004571a1:
        add eax,dword ptr [ebx+4]
    L_004571a4:
        imul eax,3Ch
    L_004571a7:
        add eax,dword ptr [ebx]
    L_004571a9:
        imul eax,3E8h
    L_004571af:
        cmp ecx,edx
    L_004571b1:
        jne short L_004571c2
    L_004571b3:
        xor ecx,ecx
    L_004571b5:
        cmp eax,dword ptr [data_004735c0]
    L_004571bb:
        setge cl
    L_004571be:
        mov eax,ecx
    L_004571c0:
        jmp short L_00457183
    L_004571c2:
        xor ecx,ecx
    L_004571c4:
        cmp eax,dword ptr [data_004735cc]
    L_004571ca:
        setl cl
    L_004571cd:
        jmp short L_004571be
    }
}
