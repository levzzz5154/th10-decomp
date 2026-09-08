#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004590D8..0x00459134: __wincmdln
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_wincmdln_004590d8() {
    __asm {
    L_004590d8:
        push esi
    L_004590d9:
        push edi
    L_004590da:
        xor edi,edi
    L_004590dc:
        cmp dword ptr [data_00499314],edi
    L_004590e2:
        jne short L_004590e9
    L_004590e4:
        call asm_initmbctable_0045d2ac
    L_004590e9:
        mov esi,dword ptr [data_00499348]
    L_004590ef:
        test esi,esi
    L_004590f1:
        jne short L_004590f8
    L_004590f3:
        mov esi,46D275h
    L_004590f8:
        mov al,byte ptr [esi]
    L_004590fa:
        cmp al,20h
    L_004590fc:
        ja short L_00459106
    L_004590fe:
        test al,al
    L_00459100:
        je short L_00459130
    L_00459102:
        test edi,edi
    L_00459104:
        je short L_0045912a
    L_00459106:
        cmp al,22h
    L_00459108:
        jne short L_00459113
    L_0045910a:
        xor ecx,ecx
    L_0045910c:
        test edi,edi
    L_0045910e:
        sete cl
    L_00459111:
        mov edi,ecx
    L_00459113:
        movzx eax,al
    L_00459116:
        push eax
    L_00459117:
        call asm_ismbblead_0045f590
    L_0045911c:
        test eax,eax
    L_0045911e:
        pop ecx
    L_0045911f:
        je short L_00459122
    L_00459121:
        inc esi
    L_00459122:
        inc esi
    L_00459123:
        jmp short L_004590f8
    L_00459125:
        cmp al,20h
    L_00459127:
        ja short L_00459130
    L_00459129:
        inc esi
    L_0045912a:
        mov al,byte ptr [esi]
    L_0045912c:
        test al,al
    L_0045912e:
        jne short L_00459125
    L_00459130:
        pop edi
    L_00459131:
        mov eax,esi
    L_00459133:
        pop esi
    L_00459134:
        ret
    }
}
