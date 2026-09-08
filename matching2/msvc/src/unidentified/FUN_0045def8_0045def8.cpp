#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045DEF8..0x0045DF96: FUN_0045def8
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045def8_0045def8() {
    __asm {
    L_0045def8:
        push ebp
    L_0045def9:
        mov ebp,esp
    L_0045defb:
        sub esp,2Ch
    L_0045defe:
        mov eax,dword ptr [data_00473660]
    L_0045df03:
        push ebx
    L_0045df04:
        mov ebx,dword ptr [ebp+0Ch]
    L_0045df07:
        push esi
    L_0045df08:
        push edi
    L_0045df09:
        lea ecx,[ebp-1Ch]
    L_0045df0c:
        push ecx
    L_0045df0d:
        xor eax,ebp
    L_0045df0f:
        lea ecx,[ebp-2Ch]
    L_0045df12:
        mov dword ptr [ebp-4],eax
    L_0045df15:
        mov eax,dword ptr [ebp+8]
    L_0045df18:
        push ecx
    L_0045df19:
        push dword ptr [eax+4]
    L_0045df1c:
        push dword ptr [eax]
    L_0045df1e:
        call asm_FUN_00460e41_00460e41
    L_0045df23:
        mov esi,dword ptr [ebp-28h]
    L_0045df26:
        xor eax,eax
    L_0045df28:
        dec esi
    L_0045df29:
        cmp dword ptr [ebp-2Ch],2Dh
    L_0045df2d:
        sete al
    L_0045df30:
        add eax,ebx
    L_0045df32:
        mov edi,eax
    L_0045df34:
        lea eax,[ebp-2Ch]
    L_0045df37:
        push eax
    L_0045df38:
        push dword ptr [ebp+10h]
    L_0045df3b:
        push edi
    L_0045df3c:
        call asm_fptostr_00460d10
    L_0045df41:
        mov eax,dword ptr [ebp-28h]
    L_0045df44:
        add esp,1Ch
    L_0045df47:
        dec eax
    L_0045df48:
        cmp esi,eax
    L_0045df4a:
        setl cl
    L_0045df4d:
        cmp eax,0FFFFFFFCh
    L_0045df50:
        jl short L_0045df75
    L_0045df52:
        cmp eax,dword ptr [ebp+10h]
    L_0045df55:
        jge short L_0045df75
    L_0045df57:
        test cl,cl
    L_0045df59:
        je short L_0045df65
    L_0045df5b:
        mov al,byte ptr [edi]
    L_0045df5d:
        inc edi
    L_0045df5e:
        test al,al
    L_0045df60:
        jne short L_0045df5b
    L_0045df62:
        mov byte ptr [edi-2],al
    L_0045df65:
        push 1
    L_0045df67:
        push dword ptr [ebp+10h]
    L_0045df6a:
        lea eax,[ebp-2Ch]
    L_0045df6d:
        push ebx
    L_0045df6e:
        call asm_cftof2_0045ddf5
    L_0045df73:
        jmp short L_0045df85
    L_0045df75:
        push 1
    L_0045df77:
        push dword ptr [ebp+14h]
    L_0045df7a:
        lea eax,[ebp-2Ch]
    L_0045df7d:
        push dword ptr [ebp+10h]
    L_0045df80:
        call asm_cftoe2_0045dcd7
    L_0045df85:
        mov ecx,dword ptr [ebp-4]
    L_0045df88:
        add esp,0Ch
    L_0045df8b:
        pop edi
    L_0045df8c:
        pop esi
    L_0045df8d:
        xor ecx,ebp
    L_0045df8f:
        pop ebx
    L_0045df90:
        call asm_security_check_cookie_00458ea5
    L_0045df95:
        leave
    L_0045df96:
        ret
    }
}
