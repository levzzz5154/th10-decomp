#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004561C4..0x0045631D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004561c4() {
    __asm {
    L_004561c4:
        push 14h
    L_004561c6:
        push 46AA08h
    L_004561cb:
        call asm_SEH_prolog_00454bbc
    L_004561d0:
        mov edi,dword ptr [ebp+8]
    L_004561d3:
        xor ebx,ebx
    L_004561d5:
        cmp edi,ebx
    L_004561d7:
        jl asm_target_00456316
    L_004561dd:
        cmp edi,5
    L_004561e0:
        jg asm_target_00456316
    L_004561e6:
        push 0Ch
    L_004561e8:
        call asm_lock_00453c0c
    L_004561ed:
        pop ecx
    L_004561ee:
        mov dword ptr [ebp-4],ebx
    L_004561f1:
        cmp dword ptr [ebp+0Ch],ebx
    L_004561f4:
        jne short L_00456215
    L_004561f6:
        xor edx,edx
    L_004561f8:
        mov ecx,edi
    L_004561fa:
        call asm_FUN_00455fe7_00455fe7
    L_004561ff:
        mov esi,eax
    L_00456201:
        push 0FFFFFFFFh
    L_00456203:
        lea eax,[ebp-10h]
    L_00456206:
        push eax
    L_00456207:
        call asm_local_unwind2_004598de
    L_0045620c:
        pop ecx
    L_0045620d:
        pop ecx
    L_0045620e:
        mov eax,esi
    L_00456210:
        jmp asm_target_00456318
    L_00456215:
        push 54h
    L_00456217:
        call asm_malloc_00452706
    L_0045621c:
        pop ecx
    L_0045621d:
        mov esi,eax
    L_0045621f:
        mov dword ptr [ebp-24h],esi
    L_00456222:
        cmp esi,ebx
    L_00456224:
        jne short L_0045622e
    L_00456226:
        mov dword ptr [ebp-1Ch],ebx
    L_00456229:
        jmp asm_target_004562ef
    L_0045622e:
        mov edx,dword ptr [ebp+0Ch]
    L_00456231:
        mov ecx,edi
    L_00456233:
        call asm_FUN_00455fe7_00455fe7
    L_00456238:
        mov dword ptr [ebp-1Ch],eax
    L_0045623b:
        cmp eax,ebx
    L_0045623d:
        je asm_target_004562ef
    L_00456243:
        mov dword ptr [esi],ebx
    L_00456245:
        mov eax,dword ptr [data_00477664]
    L_0045624a:
        mov dword ptr [esi+4],eax
    L_0045624d:
        mov eax,dword ptr [data_00477668]
    L_00456252:
        mov dword ptr [esi+8],eax
    L_00456255:
        xor eax,eax
    L_00456257:
        mov dword ptr [ebp-20h],eax
    L_0045625a:
        cmp eax,5
    L_0045625d:
        jg short L_0045626d
    L_0045625f:
        mov ecx,dword ptr [eax*4+47764Ch]
    L_00456266:
        mov dword ptr [esi+eax*4+0Ch],ecx
    L_0045626a:
        inc eax
    L_0045626b:
        jmp short L_00456257
    L_0045626d:
        mov eax,dword ptr [data_00473ae0]
    L_00456272:
        mov dword ptr [esi+24h],eax
    L_00456275:
        mov eax,dword ptr [data_00473af0]
    L_0045627a:
        mov dword ptr [esi+28h],eax
    L_0045627d:
        mov eax,dword ptr [data_004981cc]
    L_00456282:
        mov dword ptr [esi+2Ch],eax
    L_00456285:
        mov eax,dword ptr [data_004981d0]
    L_0045628a:
        mov dword ptr [esi+30h],eax
    L_0045628d:
        mov eax,dword ptr [data_004981c8]
    L_00456292:
        mov dword ptr [esi+34h],eax
    L_00456295:
        mov eax,dword ptr [data_00473ad4]
    L_0045629a:
        mov dword ptr [esi+38h],eax
    L_0045629d:
        mov eax,dword ptr [data_00477624]
    L_004562a2:
        mov dword ptr [esi+3Ch],eax
    L_004562a5:
        mov eax,dword ptr [data_004981c4]
    L_004562aa:
        mov dword ptr [esi+40h],eax
    L_004562ad:
        mov eax,dword ptr [data_004981c0]
    L_004562b2:
        mov dword ptr [esi+44h],eax
    L_004562b5:
        mov eax,dword ptr [data_004739d8]
    L_004562ba:
        mov dword ptr [esi+48h],eax
    L_004562bd:
        mov eax,dword ptr [data_004739e0]
    L_004562c2:
        mov dword ptr [esi+4Ch],eax
    L_004562c5:
        mov eax,dword ptr [data_00477620]
    L_004562ca:
        mov dword ptr [esi+50h],eax
    L_004562cd:
        mov eax,dword ptr [data_0047320c]
    L_004562d2:
        cmp dword ptr [eax],ebx
    L_004562d4:
        jne short L_004562e4
    L_004562d6:
        cmp eax,4731B8h
    L_004562db:
        je short L_004562e4
    L_004562dd:
        push eax
    L_004562de:
        call asm_freetlocinfo_004557fc
    L_004562e3:
        pop ecx
    L_004562e4:
        mov dword ptr [data_0047320c],esi
    L_004562ea:
        call asm_updatetlocinfo_lk_004558cc
    L_004562ef:
        cmp dword ptr [ebp-1Ch],ebx
    L_004562f2:
        jne short L_004562ff
    L_004562f4:
        cmp esi,ebx
    L_004562f6:
        je short L_004562ff
    L_004562f8:
        push esi
    L_004562f9:
        call asm_free_00452422
    L_004562fe:
        pop ecx
    L_004562ff:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00456303:
        call asm_target_0045630d
    L_00456308:
        mov eax,dword ptr [ebp-1Ch]
    L_0045630b:
        jmp short L_00456318
    L_0045630d:
        push 0Ch
    L_0045630f:
        call asm_FUN_00453b3f_00453b3f
    L_00456314:
        pop ecx
    L_00456315:
        ret
    L_00456316:
        xor eax,eax
    L_00456318:
        call asm_SEH_epilog_00454bf7
    L_0045631d:
        ret
    }
}
