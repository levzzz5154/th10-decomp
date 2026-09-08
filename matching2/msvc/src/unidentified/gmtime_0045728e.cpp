#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045728E..0x00457394: _gmtime
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_gmtime_0045728e() {
    __asm {
    L_0045728e:
        mov eax,dword ptr [esp+4]
    L_00457292:
        push ebx
    L_00457293:
        push esi
    L_00457294:
        mov esi,dword ptr [eax]
    L_00457296:
        push edi
    L_00457297:
        xor ebx,ebx
    L_00457299:
        call asm_getptd_00456357
    L_0045729e:
        test esi,esi
    L_004572a0:
        mov edi,eax
    L_004572a2:
        jge short L_004572ab
    L_004572a4:
        xor eax,eax
    L_004572a6:
        jmp asm_target_00457391
    L_004572ab:
        cmp dword ptr [edi+44h],0
    L_004572af:
        jne short L_004572c5
    L_004572b1:
        push 24h
    L_004572b3:
        call asm_malloc_00452706
    L_004572b8:
        test eax,eax
    L_004572ba:
        pop ecx
    L_004572bb:
        mov dword ptr [edi+44h],eax
    L_004572be:
        mov ecx,477448h
    L_004572c3:
        je short L_004572c8
    L_004572c5:
        mov ecx,dword ptr [edi+44h]
    L_004572c8:
        mov eax,esi
    L_004572ca:
        cdq
    L_004572cb:
        mov edi,7861F80h
    L_004572d0:
        idiv edi
    L_004572d2:
        mov edx,eax
    L_004572d4:
        imul edx,0F879E080h
    L_004572da:
        add esi,edx
    L_004572dc:
        lea edx,[eax*4+46h]
    L_004572e3:
        mov eax,1E13380h
    L_004572e8:
        cmp esi,eax
    L_004572ea:
        jl short L_00457307
    L_004572ec:
        sub esi,eax
    L_004572ee:
        inc edx
    L_004572ef:
        cmp esi,eax
    L_004572f1:
        jl short L_00457307
    L_004572f3:
        sub esi,eax
    L_004572f5:
        mov eax,1E28500h
    L_004572fa:
        inc edx
    L_004572fb:
        cmp esi,eax
    L_004572fd:
        jl short L_00457304
    L_004572ff:
        inc edx
    L_00457300:
        sub esi,eax
    L_00457302:
        jmp short L_00457307
    L_00457304:
        xor ebx,ebx
    L_00457306:
        inc ebx
    L_00457307:
        mov eax,esi
    L_00457309:
        mov dword ptr [ecx+14h],edx
    L_0045730c:
        cdq
    L_0045730d:
        mov edi,15180h
    L_00457312:
        idiv edi
    L_00457314:
        mov edi,473C28h
    L_00457319:
        mov dword ptr [ecx+1Ch],eax
    L_0045731c:
        imul eax,0FFFEAE80h
    L_00457322:
        add esi,eax
    L_00457324:
        test ebx,ebx
    L_00457326:
        jne short L_0045732d
    L_00457328:
        mov edi,473C5Ch
    L_0045732d:
        mov eax,dword ptr [ecx+1Ch]
    L_00457330:
        xor edx,edx
    L_00457332:
        inc edx
    L_00457333:
        cmp dword ptr [edi+4],eax
    L_00457336:
        jge short L_00457340
    L_00457338:
        mov ebx,eax
    L_0045733a:
        inc edx
    L_0045733b:
        cmp dword ptr [edi+edx*4],ebx
    L_0045733e:
        jl short L_0045733a
    L_00457340:
        dec edx
    L_00457341:
        mov dword ptr [ecx+10h],edx
    L_00457344:
        sub eax,dword ptr [edi+edx*4]
    L_00457347:
        mov edi,15180h
    L_0045734c:
        mov dword ptr [ecx+0Ch],eax
    L_0045734f:
        mov eax,dword ptr [esp+10h]
    L_00457353:
        mov eax,dword ptr [eax]
    L_00457355:
        cdq
    L_00457356:
        idiv edi
    L_00457358:
        push 7
    L_0045735a:
        pop edi
    L_0045735b:
        push 3Ch
    L_0045735d:
        add eax,4
    L_00457360:
        cdq
    L_00457361:
        idiv edi
    L_00457363:
        mov eax,esi
    L_00457365:
        mov edi,0E10h
    L_0045736a:
        mov dword ptr [ecx+18h],edx
    L_0045736d:
        cdq
    L_0045736e:
        idiv edi
    L_00457370:
        pop edi
    L_00457371:
        mov dword ptr [ecx+8],eax
    L_00457374:
        imul eax,0FFFFF1F0h
    L_0045737a:
        add esi,eax
    L_0045737c:
        mov eax,esi
    L_0045737e:
        cdq
    L_0045737f:
        idiv edi
    L_00457381:
        mov dword ptr [ecx+4],eax
    L_00457384:
        imul eax,3Ch
    L_00457387:
        sub esi,eax
    L_00457389:
        and dword ptr [ecx+20h],0
    L_0045738d:
        mov dword ptr [ecx],esi
    L_0045738f:
        mov eax,ecx
    L_00457391:
        pop edi
    L_00457392:
        pop esi
    L_00457393:
        pop ebx
    L_00457394:
        ret
    }
}
