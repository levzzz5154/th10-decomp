#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045BD90..0x0045BE77: FUN_0045bd90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045bd90_0045bd90() {
    __asm {
    L_0045bd90:
        mov ecx,dword ptr [esp+4]
    L_0045bd94:
        push edi
    L_0045bd95:
        test ecx,3
    L_0045bd9b:
        je short L_0045bdb0
    L_0045bd9d:
        mov al,byte ptr [ecx]
    L_0045bd9f:
        add ecx,1
    L_0045bda2:
        test al,al
    L_0045bda4:
        je short L_0045bde3
    L_0045bda6:
        test ecx,3
    L_0045bdac:
        jne short L_0045bd9d
    L_0045bdae:
        mov edi,edi
    L_0045bdb0:
        mov eax,dword ptr [ecx]
    L_0045bdb2:
        mov edx,7EFEFEFFh
    L_0045bdb7:
        add edx,eax
    L_0045bdb9:
        xor eax,0FFFFFFFFh
    L_0045bdbc:
        xor eax,edx
    L_0045bdbe:
        add ecx,4
    L_0045bdc1:
        test eax,81010100h
    L_0045bdc6:
        je short L_0045bdb0
    L_0045bdc8:
        mov eax,dword ptr [ecx-4]
    L_0045bdcb:
        test al,al
    L_0045bdcd:
        je short L_0045bdf2
    L_0045bdcf:
        test ah,ah
    L_0045bdd1:
        je short L_0045bded
    L_0045bdd3:
        test eax,0FF0000h
    L_0045bdd8:
        je short L_0045bde8
    L_0045bdda:
        test eax,0FF000000h
    L_0045bddf:
        je short L_0045bde3
    L_0045bde1:
        jmp short L_0045bdb0
    L_0045bde3:
        lea edi,[ecx-1]
    L_0045bde6:
        jmp short L_0045bdf5
    L_0045bde8:
        lea edi,[ecx-2]
    L_0045bdeb:
        jmp short L_0045bdf5
    L_0045bded:
        lea edi,[ecx-3]
    L_0045bdf0:
        jmp short L_0045bdf5
    L_0045bdf2:
        lea edi,[ecx-4]
    L_0045bdf5:
        mov ecx,dword ptr [esp+0Ch]
    L_0045bdf9:
        test ecx,3
    L_0045bdff:
        je short L_0045be1e
    L_0045be01:
        mov dl,byte ptr [ecx]
    L_0045be03:
        add ecx,1
    L_0045be06:
        test dl,dl
    L_0045be08:
        je short L_0045be70
    L_0045be0a:
        mov byte ptr [edi],dl
    L_0045be0c:
        add edi,1
    L_0045be0f:
        test ecx,3
    L_0045be15:
        jne short L_0045be01
    L_0045be17:
        jmp short L_0045be1e
    L_0045be19:
        mov dword ptr [edi],edx
    L_0045be1b:
        add edi,4
    L_0045be1e:
        mov edx,7EFEFEFFh
    L_0045be23:
        mov eax,dword ptr [ecx]
    L_0045be25:
        add edx,eax
    L_0045be27:
        xor eax,0FFFFFFFFh
    L_0045be2a:
        xor eax,edx
    L_0045be2c:
        mov edx,dword ptr [ecx]
    L_0045be2e:
        add ecx,4
    L_0045be31:
        test eax,81010100h
    L_0045be36:
        je short L_0045be19
    L_0045be38:
        test dl,dl
    L_0045be3a:
        je short L_0045be70
    L_0045be3c:
        test dh,dh
    L_0045be3e:
        je short L_0045be67
    L_0045be40:
        test edx,0FF0000h
    L_0045be46:
        je short L_0045be5a
    L_0045be48:
        test edx,0FF000000h
    L_0045be4e:
        je short L_0045be52
    L_0045be50:
        jmp short L_0045be19
    L_0045be52:
        mov dword ptr [edi],edx
    L_0045be54:
        mov eax,dword ptr [esp+8]
    L_0045be58:
        pop edi
    L_0045be59:
        ret
    L_0045be5a:
        mov word ptr [edi],dx
    L_0045be5d:
        mov eax,dword ptr [esp+8]
    L_0045be61:
        mov byte ptr [edi+2],0
    L_0045be65:
        pop edi
    L_0045be66:
        ret
    L_0045be67:
        mov word ptr [edi],dx
    L_0045be6a:
        mov eax,dword ptr [esp+8]
    L_0045be6e:
        pop edi
    L_0045be6f:
        ret
    L_0045be70:
        mov byte ptr [edi],dl
    L_0045be72:
        mov eax,dword ptr [esp+8]
    L_0045be76:
        pop edi
    L_0045be77:
        ret
    }
}
