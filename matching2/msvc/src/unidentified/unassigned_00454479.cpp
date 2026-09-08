#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00454479..0x00454549: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00454479() {
    __asm {
    L_00454479:
        mov eax,dword ptr [data_00499324]
    L_0045447e:
        test eax,eax
    L_00454480:
        je asm_target_00454549
    L_00454486:
        mov ecx,dword ptr [data_0049933c]
    L_0045448c:
        push 4000h
    L_00454491:
        shl ecx,0Fh
    L_00454494:
        add ecx,dword ptr [eax+0Ch]
    L_00454497:
        push 8000h
    L_0045449c:
        push ecx
    L_0045449d:
        call dword ptr [data_00466188]
    L_004544a3:
        mov ecx,dword ptr [data_0049933c]
    L_004544a9:
        mov eax,dword ptr [data_00499324]
    L_004544ae:
        mov edx,80000000h
    L_004544b3:
        shr edx,cl
    L_004544b5:
        or dword ptr [eax+8],edx
    L_004544b8:
        mov eax,dword ptr [data_00499324]
    L_004544bd:
        mov eax,dword ptr [eax+10h]
    L_004544c0:
        mov ecx,dword ptr [data_0049933c]
    L_004544c6:
        and dword ptr [eax+ecx*4+0C4h],0
    L_004544ce:
        mov eax,dword ptr [data_00499324]
    L_004544d3:
        mov eax,dword ptr [eax+10h]
    L_004544d6:
        dec byte ptr [eax+43h]
    L_004544d9:
        mov eax,dword ptr [data_00499324]
    L_004544de:
        mov ecx,dword ptr [eax+10h]
    L_004544e1:
        cmp byte ptr [ecx+43h],0
    L_004544e5:
        jne short L_004544f0
    L_004544e7:
        and dword ptr [eax+4],0FFFFFFFEh
    L_004544eb:
        mov eax,dword ptr [data_00499324]
    L_004544f0:
        cmp dword ptr [eax+8],0FFFFFFFFh
    L_004544f4:
        jne short L_00454542
    L_004544f6:
        cmp dword ptr [data_00499328],1
    L_004544fd:
        jle short L_00454542
    L_004544ff:
        push dword ptr [eax+10h]
    L_00454502:
        push 0
    L_00454504:
        push dword ptr [data_00499340]
    L_0045450a:
        call dword ptr [data_004661e8]
    L_00454510:
        mov eax,dword ptr [data_00499328]
    L_00454515:
        mov edx,dword ptr [data_0049932c]
    L_0045451b:
        lea eax,[eax+eax*4]
    L_0045451e:
        shl eax,2
    L_00454521:
        mov ecx,eax
    L_00454523:
        mov eax,dword ptr [data_00499324]
    L_00454528:
        sub ecx,eax
    L_0045452a:
        lea ecx,[ecx+edx-14h]
    L_0045452e:
        push ecx
    L_0045452f:
        lea ecx,[eax+14h]
    L_00454532:
        push ecx
    L_00454533:
        push eax
    L_00454534:
        call asm_memmove_00453280
    L_00454539:
        add esp,0Ch
    L_0045453c:
        dec dword ptr [data_00499328]
    L_00454542:
        and dword ptr [data_00499324],0
    L_00454549:
        ret
    }
}
