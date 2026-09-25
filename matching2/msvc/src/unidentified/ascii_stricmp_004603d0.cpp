#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004603D0..0x0046041D: ___ascii_stricmp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ascii_stricmp_004603d0() {
    __asm {
    L_004603d0:
        push ebp
    L_004603d1:
        mov ebp,esp
    L_004603d3:
        push edi
    L_004603d4:
        push esi
    L_004603d5:
        push ebx
    L_004603d6:
        mov esi,dword ptr [ebp+0Ch]
    L_004603d9:
        mov edi,dword ptr [ebp+8]
    L_004603dc:
        mov al,0FFh
    L_004603de:
        mov edi,edi
    L_004603e0:
        or al,al
    L_004603e2:
        je short L_00460416
    L_004603e4:
        mov al,byte ptr [esi]
    L_004603e6:
        add esi,1
    L_004603e9:
        mov ah,byte ptr [edi]
    L_004603eb:
        add edi,1
    L_004603ee:
        TH10_CMP_R8_STORE(TH10_R8_AH, TH10_R8_AL)
    L_004603f0:
        je short L_004603e0
    L_004603f2:
        sub al,41h
    L_004603f4:
        cmp al,1Ah
    L_004603f6:
        sbb cl,cl
    L_004603f8:
        and cl,20h
    L_004603fb:
        add al,cl
    L_004603fd:
        add al,41h
    L_004603ff:
        xchg ah,al
    L_00460401:
        sub al,41h
    L_00460403:
        cmp al,1Ah
    L_00460405:
        sbb cl,cl
    L_00460407:
        and cl,20h
    L_0046040a:
        add al,cl
    L_0046040c:
        add al,41h
    L_0046040e:
        TH10_CMP_R8_STORE(TH10_R8_AL, TH10_R8_AH)
    L_00460410:
        je short L_004603e0
    L_00460412:
        sbb al,al
    L_00460414:
        sbb al,0FFh
    L_00460416:
        movsx eax,al
    L_00460419:
        pop ebx
    L_0046041a:
        pop esi
    L_0046041b:
        pop edi
    L_0046041c:
        leave
    L_0046041d:
        ret
    }
}
