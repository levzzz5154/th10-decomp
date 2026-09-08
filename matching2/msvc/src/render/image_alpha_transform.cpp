#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00437160..0x004371FC: FUN_00437160
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00437160_00437160() {
    __asm {
    L_00437160:
        mov eax,dword ptr [ecx+110h]
    L_00437166:
        mov edx,dword ptr [ecx+120h]
    L_0043716c:
        imul eax,dword ptr [esp+4]
    L_00437171:
        mov ecx,dword ptr [ecx+100h]
    L_00437177:
        sub ecx,15h
    L_0043717a:
        push esi
    L_0043717b:
        je short L_004371df
    L_0043717d:
        sub ecx,4
    L_00437180:
        je short L_004371a5
    L_00437182:
        dec ecx
    L_00437183:
        je short L_0043718b
    L_00437185:
        xor al,al
    L_00437187:
        pop esi
    L_00437188:
        ret 4
    L_0043718b:
        mov ecx,1
    L_00437190:
        cmp eax,ecx
    L_00437192:
        jle short L_004371f7
    L_00437194:
        xor byte ptr [ecx+edx],0F0h
    L_00437198:
        add ecx,2
    L_0043719b:
        cmp ecx,eax
    L_0043719d:
        jl short L_00437194
    L_0043719f:
        mov al,1
    L_004371a1:
        pop esi
    L_004371a2:
        ret 4
    L_004371a5:
        test eax,eax
    L_004371a7:
        jle short L_004371f7
    L_004371a9:
        lea esi,[eax-1]
    L_004371ac:
        shr esi,1
    L_004371ae:
        inc esi
    L_004371af:
        nop
    L_004371b0:
        xor ecx,ecx
    L_004371b2:
        mov cx,word ptr [edx]
    L_004371b5:
        mov eax,ecx
    L_004371b7:
        not eax
    L_004371b9:
        xor eax,ecx
    L_004371bb:
        and eax,7FFFh
    L_004371c0:
        not ecx
    L_004371c2:
        xor eax,ecx
    L_004371c4:
        test ah,ah
    L_004371c6:
        mov word ptr [edx],ax
    L_004371c9:
        js short L_004371d3
    L_004371cb:
        and eax,8000h
    L_004371d0:
        mov word ptr [edx],ax
    L_004371d3:
        add edx,2
    L_004371d6:
        dec esi
    L_004371d7:
        jne short L_004371b0
    L_004371d9:
        mov al,1
    L_004371db:
        pop esi
    L_004371dc:
        ret 4
    L_004371df:
        mov esi,3
    L_004371e4:
        cmp eax,esi
    L_004371e6:
        jle short L_004371f7
    L_004371e8:
        mov cl,byte ptr [esi+edx]
    L_004371eb:
        not cl
    L_004371ed:
        mov byte ptr [esi+edx],cl
    L_004371f0:
        add esi,4
    L_004371f3:
        cmp esi,eax
    L_004371f5:
        jl short L_004371e8
    L_004371f7:
        mov al,1
    L_004371f9:
        pop esi
    L_004371fa:
        ret 4
    }
}
