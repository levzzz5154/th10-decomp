#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045DBDB..0x0045DC16: __forcdecpt
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_forcdecpt_0045dbdb() {
    __asm {
    L_0045dbdb:
        push esi
    L_0045dbdc:
        mov esi,dword ptr [esp+8]
    L_0045dbe0:
        movsx eax,byte ptr [esi]
    L_0045dbe3:
        push eax
    L_0045dbe4:
        call asm_tolower_00460cee
    L_0045dbe9:
        cmp eax,65h
    L_0045dbec:
        jmp short L_0045dbfa
    L_0045dbee:
        inc esi
    L_0045dbef:
        movsx eax,byte ptr [esi]
    L_0045dbf2:
        push eax
    L_0045dbf3:
        call asm_isdigit_0045685e
    L_0045dbf8:
        test eax,eax
    L_0045dbfa:
        pop ecx
    L_0045dbfb:
        jne short L_0045dbee
    L_0045dbfd:
        mov al,byte ptr [esi]
    L_0045dbff:
        mov cl,byte ptr [data_00473af4]
    L_0045dc05:
        mov byte ptr [esi],cl
    L_0045dc07:
        inc esi
    L_0045dc08:
        mov cl,byte ptr [esi]
    L_0045dc0a:
        mov byte ptr [esi],al
    L_0045dc0c:
        mov al,cl
    L_0045dc0e:
        mov cl,byte ptr [esi]
    L_0045dc10:
        inc esi
    L_0045dc11:
        test cl,cl
    L_0045dc13:
        jne short L_0045dc08
    L_0045dc15:
        pop esi
    L_0045dc16:
        ret
    }
}
