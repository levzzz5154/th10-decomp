#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E2B5..0x0045E374: ___mbtowc_mt
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_mbtowc_mt_0045e2b5() {
    __asm {
    L_0045e2b5:
        push ebp
    L_0045e2b6:
        mov ebp,esp
    L_0045e2b8:
        push ebx
    L_0045e2b9:
        push esi
    L_0045e2ba:
        push edi
    L_0045e2bb:
        mov edi,dword ptr [ebp+10h]
    L_0045e2be:
        xor ebx,ebx
    L_0045e2c0:
        cmp edi,ebx
    L_0045e2c2:
        je short L_0045e2d9
    L_0045e2c4:
        cmp dword ptr [ebp+14h],ebx
    L_0045e2c7:
        je short L_0045e2d9
    L_0045e2c9:
        mov al,byte ptr [edi]
    L_0045e2cb:
        cmp al,bl
    L_0045e2cd:
        jne short L_0045e2e0
    L_0045e2cf:
        mov eax,dword ptr [ebp+0Ch]
    L_0045e2d2:
        cmp eax,ebx
    L_0045e2d4:
        je short L_0045e2d9
    L_0045e2d6:
        mov word ptr [eax],bx
    L_0045e2d9:
        xor eax,eax
    L_0045e2db:
        pop edi
    L_0045e2dc:
        pop esi
    L_0045e2dd:
        pop ebx
    L_0045e2de:
        pop ebp
    L_0045e2df:
        ret
    L_0045e2e0:
        mov esi,dword ptr [ebp+8]
    L_0045e2e3:
        cmp dword ptr [esi+14h],ebx
    L_0045e2e6:
        jne short L_0045e2fb
    L_0045e2e8:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045e2eb:
        cmp ecx,ebx
    L_0045e2ed:
        je short L_0045e2f6
    L_0045e2ef:
        movzx ax,al
    L_0045e2f3:
        mov word ptr [ecx],ax
    L_0045e2f6:
        xor eax,eax
    L_0045e2f8:
        inc eax
    L_0045e2f9:
        jmp short L_0045e2db
    L_0045e2fb:
        mov ecx,dword ptr [esi+48h]
    L_0045e2fe:
        movzx eax,al
    L_0045e301:
        test byte ptr [ecx+eax*2+1],80h
    L_0045e306:
        je short L_0045e344
    L_0045e308:
        mov eax,dword ptr [esi+28h]
    L_0045e30b:
        cmp eax,1
    L_0045e30e:
        jle short L_0045e332
    L_0045e310:
        cmp dword ptr [ebp+14h],eax
    L_0045e313:
        jl short L_0045e332
    L_0045e315:
        xor ecx,ecx
    L_0045e317:
        cmp dword ptr [ebp+0Ch],ebx
    L_0045e31a:
        setne cl
    L_0045e31d:
        push ecx
    L_0045e31e:
        push dword ptr [ebp+0Ch]
    L_0045e321:
        push eax
    L_0045e322:
        push edi
    L_0045e323:
        push 9
    L_0045e325:
        push dword ptr [esi+4]
    L_0045e328:
        call dword ptr [data_00466104]
    L_0045e32e:
        test eax,eax
    L_0045e330:
        jne short L_0045e33f
    L_0045e332:
        mov eax,dword ptr [ebp+14h]
    L_0045e335:
        cmp eax,dword ptr [esi+28h]
    L_0045e338:
        jb short L_0045e362
    L_0045e33a:
        cmp byte ptr [edi+1],bl
    L_0045e33d:
        je short L_0045e362
    L_0045e33f:
        mov eax,dword ptr [esi+28h]
    L_0045e342:
        jmp short L_0045e2db
    L_0045e344:
        xor eax,eax
    L_0045e346:
        cmp dword ptr [ebp+0Ch],ebx
    L_0045e349:
        setne al
    L_0045e34c:
        push eax
    L_0045e34d:
        push dword ptr [ebp+0Ch]
    L_0045e350:
        push 1
    L_0045e352:
        push edi
    L_0045e353:
        push 9
    L_0045e355:
        push dword ptr [esi+4]
    L_0045e358:
        call dword ptr [data_00466104]
    L_0045e35e:
        test eax,eax
    L_0045e360:
        jne short L_0045e2f6
    L_0045e362:
        call asm_FUN_00456af2_00456af2
    L_0045e367:
        mov dword ptr [eax],2Ah
    L_0045e36d:
        or eax,0FFFFFFFFh
    L_0045e370:
        jmp asm_target_0045e2db
    }
}
