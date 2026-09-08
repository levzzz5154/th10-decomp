#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00454094..0x00454199: ___sbh_alloc_new_group
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_sbh_alloc_new_group_00454094() {
    __asm {
    L_00454094:
        push ebp
    L_00454095:
        mov ebp,esp
    L_00454097:
        push ecx
    L_00454098:
        push ecx
    L_00454099:
        mov ecx,dword ptr [ebp+8]
    L_0045409c:
        mov eax,dword ptr [ecx+8]
    L_0045409f:
        push ebx
    L_004540a0:
        push esi
    L_004540a1:
        mov esi,dword ptr [ecx+10h]
    L_004540a4:
        push edi
    L_004540a5:
        xor ebx,ebx
    L_004540a7:
        jmp short L_004540ac
    L_004540a9:
        shl eax,1
    L_004540ab:
        inc ebx
    L_004540ac:
        test eax,eax
    L_004540ae:
        jge short L_004540a9
    L_004540b0:
        mov eax,ebx
    L_004540b2:
        imul eax,204h
    L_004540b8:
        lea eax,[eax+esi+144h]
    L_004540bf:
        push 3Fh
    L_004540c1:
        mov dword ptr [ebp-8],eax
    L_004540c4:
        pop edx
    L_004540c5:
        mov dword ptr [eax+8],eax
    L_004540c8:
        mov dword ptr [eax+4],eax
    L_004540cb:
        add eax,8
    L_004540ce:
        dec edx
    L_004540cf:
        jne short L_004540c5
    L_004540d1:
        push 4
    L_004540d3:
        mov edi,ebx
    L_004540d5:
        push 1000h
    L_004540da:
        shl edi,0Fh
    L_004540dd:
        add edi,dword ptr [ecx+0Ch]
    L_004540e0:
        push 8000h
    L_004540e5:
        push edi
    L_004540e6:
        call dword ptr [data_0046617c]
    L_004540ec:
        test eax,eax
    L_004540ee:
        jne short L_004540f8
    L_004540f0:
        or eax,0FFFFFFFFh
    L_004540f3:
        jmp asm_target_00454195
    L_004540f8:
        lea edx,[edi+7000h]
    L_004540fe:
        cmp edi,edx
    L_00454100:
        mov dword ptr [ebp-4],edx
    L_00454103:
        ja short L_00454148
    L_00454105:
        mov ecx,edx
    L_00454107:
        sub ecx,edi
    L_00454109:
        shr ecx,0Ch
    L_0045410c:
        lea eax,[edi+10h]
    L_0045410f:
        inc ecx
    L_00454110:
        or dword ptr [eax-8],0FFFFFFFFh
    L_00454114:
        or dword ptr [eax+0FECh],0FFFFFFFFh
    L_0045411b:
        lea edx,[eax+0FFCh]
    L_00454121:
        mov dword ptr [eax],edx
    L_00454123:
        lea edx,[eax-1004h]
    L_00454129:
        mov dword ptr [eax-4],0FF0h
    L_00454130:
        mov dword ptr [eax+4],edx
    L_00454133:
        mov dword ptr [eax+0FE8h],0FF0h
    L_0045413d:
        add eax,1000h
    L_00454142:
        dec ecx
    L_00454143:
        jne short L_00454110
    L_00454145:
        mov edx,dword ptr [ebp-4]
    L_00454148:
        mov eax,dword ptr [ebp-8]
    L_0045414b:
        add eax,1F8h
    L_00454150:
        lea ecx,[edi+0Ch]
    L_00454153:
        mov dword ptr [eax+4],ecx
    L_00454156:
        mov dword ptr [ecx+8],eax
    L_00454159:
        lea ecx,[edx+0Ch]
    L_0045415c:
        mov dword ptr [eax+8],ecx
    L_0045415f:
        mov dword ptr [ecx+4],eax
    L_00454162:
        and dword ptr [esi+ebx*4+44h],0
    L_00454167:
        xor edi,edi
    L_00454169:
        inc edi
    L_0045416a:
        mov dword ptr [esi+ebx*4+0C4h],edi
    L_00454171:
        mov al,byte ptr [esi+43h]
    L_00454174:
        mov cl,al
    L_00454176:
        inc cl
    L_00454178:
        test al,al
    L_0045417a:
        mov eax,dword ptr [ebp+8]
    L_0045417d:
        mov byte ptr [esi+43h],cl
    L_00454180:
        jne short L_00454185
    L_00454182:
        or dword ptr [eax+4],edi
    L_00454185:
        mov edx,80000000h
    L_0045418a:
        mov ecx,ebx
    L_0045418c:
        shr edx,cl
    L_0045418e:
        not edx
    L_00454190:
        and dword ptr [eax+8],edx
    L_00454193:
        mov eax,ebx
    L_00454195:
        pop edi
    L_00454196:
        pop esi
    L_00454197:
        pop ebx
    L_00454198:
        leave
    L_00454199:
        ret
    }
}
