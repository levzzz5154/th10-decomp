#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E204..0x0045E26F: FID_conflict:_ungetc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FID_conflict__ungetc_0045e204() {
    __asm {
    L_0045e204:
        push ebx
    L_0045e205:
        mov ebx,dword ptr [esp+8]
    L_0045e209:
        cmp ebx,0FFFFFFFFh
    L_0045e20c:
        push esi
    L_0045e20d:
        je short L_0045e250
    L_0045e20f:
        mov esi,dword ptr [esp+10h]
    L_0045e213:
        mov eax,dword ptr [esi+0Ch]
    L_0045e216:
        test al,1
    L_0045e218:
        jne short L_0045e222
    L_0045e21a:
        test al,al
    L_0045e21c:
        jns short L_0045e250
    L_0045e21e:
        test al,2
    L_0045e220:
        jne short L_0045e250
    L_0045e222:
        cmp dword ptr [esi+8],0
    L_0045e226:
        jne short L_0045e22f
    L_0045e228:
        push esi
    L_0045e229:
        call asm_getbuf_00459f39
    L_0045e22e:
        pop ecx
    L_0045e22f:
        mov eax,dword ptr [esi]
    L_0045e231:
        cmp eax,dword ptr [esi+8]
    L_0045e234:
        jne short L_0045e23f
    L_0045e236:
        cmp dword ptr [esi+4],0
    L_0045e23a:
        jne short L_0045e250
    L_0045e23c:
        inc eax
    L_0045e23d:
        mov dword ptr [esi],eax
    L_0045e23f:
        dec dword ptr [esi]
    L_0045e241:
        test byte ptr [esi+0Ch],40h
    L_0045e245:
        mov eax,dword ptr [esi]
    L_0045e247:
        je short L_0045e256
    L_0045e249:
        cmp byte ptr [eax],bl
    L_0045e24b:
        je short L_0045e258
    L_0045e24d:
        inc eax
    L_0045e24e:
        mov dword ptr [esi],eax
    L_0045e250:
        or eax,0FFFFFFFFh
    L_0045e253:
        pop esi
    L_0045e254:
        pop ebx
    L_0045e255:
        ret
    L_0045e256:
        mov byte ptr [eax],bl
    L_0045e258:
        mov eax,dword ptr [esi+0Ch]
    L_0045e25b:
        inc dword ptr [esi+4]
    L_0045e25e:
        and eax,0FFFFFFEFh
    L_0045e261:
        or eax,1
    L_0045e264:
        mov dword ptr [esi+0Ch],eax
    L_0045e267:
        mov eax,ebx
    L_0045e269:
        and eax,0FFh
    L_0045e26e:
        jmp short L_0045e253
    }
}
