#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED: closest_byte_count=6/206; first_diff=extent (readable
// candidate emitted 130 bytes, retail extent 206); residual_class=private
// ESI/EDI manager ABI and blocked FUN_00448BB0 callee; variants_tested=
// typed list-drain/destructor model from live Ghidra and legacy animation
// layout under MSVC 13.10; next_lever=native-LTCG cluster with the real
// AnimationManager caller and production list/entity declarations.

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00446220..0x004462ED: FUN_00446220
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00446220_00446220() {
    __asm {
    L_00446220:
        mov eax,dword ptr fs:[0]
    L_00446226:
        push 0FFFFFFFFh
    L_00446228:
        push 465225h
    L_0044622d:
        push eax
    L_0044622e:
        mov dword ptr fs:[0],esp
    L_00446235:
        push ebx
    L_00446236:
        push esi
    L_00446237:
        push edi
    L_00446238:
        mov edi,dword ptr [esp+1Ch]
    L_0044623c:
        mov dword ptr [esp+14h],2
    L_00446244:
        mov eax,dword ptr [edi+72DAD4h]
    L_0044624a:
        test eax,eax
    L_0044624c:
        je short L_00446260
    L_0044624e:
        mov edi,edi
    L_00446250:
        mov esi,dword ptr [eax]
    L_00446252:
        mov ebx,dword ptr [eax+4]
    L_00446255:
        call asm_FUN_00448bb0_00448bb0
    L_0044625a:
        test ebx,ebx
    L_0044625c:
        mov eax,ebx
    L_0044625e:
        jne short L_00446250
    L_00446260:
        mov eax,dword ptr [edi+72DADCh]
    L_00446266:
        test eax,eax
    L_00446268:
        je short L_00446280
    L_0044626a:
        lea ebx,[ebx+force_disp32_zero]
    L_00446270:
        mov esi,dword ptr [eax]
    L_00446272:
        mov ebx,dword ptr [eax+4]
    L_00446275:
        call asm_FUN_00448bb0_00448bb0
    L_0044627a:
        test ebx,ebx
    L_0044627c:
        mov eax,ebx
    L_0044627e:
        jne short L_00446270
    L_00446280:
        push 401FF0h
    L_00446285:
        push 14h
    L_00446287:
        push 3ACh
    L_0044628c:
        lea eax,[edi+72DAE4h]
    L_00446292:
        push eax
    L_00446293:
        mov byte ptr [esp+24h],1
    L_00446298:
        call asm_eh_vector_destructor_iterator_004525ff
    L_0044629d:
        mov eax,dword ptr [edi+3AD488h]
    L_004462a3:
        test eax,eax
    L_004462a5:
        je short L_004462b0
    L_004462a7:
        push eax
    L_004462a8:
        call asm_free_00452422
    L_004462ad:
        add esp,4
    L_004462b0:
        push 401FF0h
    L_004462b5:
        push 1000h
    L_004462ba:
        mov dword ptr [edi+3AD488h],0
    L_004462c4:
        push 3ACh
    L_004462c9:
        add edi,68h
    L_004462cc:
        push edi
    L_004462cd:
        mov dword ptr [esp+24h],0FFFFFFFFh
    L_004462d5:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004462da:
        mov ecx,dword ptr [esp+0Ch]
    L_004462de:
        pop edi
    L_004462df:
        pop esi
    L_004462e0:
        mov dword ptr fs:[0],ecx
    L_004462e7:
        pop ebx
    L_004462e8:
        add esp,0Ch
    L_004462eb:
        ret 4
    }
}
