#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E123..0x0045E203: __filbuf
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_filbuf_0045e123() {
    __asm {
    L_0045e123:
        push esi
    L_0045e124:
        mov esi,dword ptr [esp+8]
    L_0045e128:
        mov eax,dword ptr [esi+0Ch]
    L_0045e12b:
        test al,83h
    L_0045e12d:
        je asm_target_0045e1ff
    L_0045e133:
        test al,40h
    L_0045e135:
        jne asm_target_0045e1ff
    L_0045e13b:
        test al,2
    L_0045e13d:
        je short L_0045e14a
    L_0045e13f:
        or eax,20h
    L_0045e142:
        mov dword ptr [esi+0Ch],eax
    L_0045e145:
        jmp asm_target_0045e1ff
    L_0045e14a:
        or eax,1
    L_0045e14d:
        test ax,10Ch
    L_0045e151:
        mov dword ptr [esi+0Ch],eax
    L_0045e154:
        jne short L_0045e15f
    L_0045e156:
        push esi
    L_0045e157:
        call asm_getbuf_00459f39
    L_0045e15c:
        pop ecx
    L_0045e15d:
        jmp short L_0045e164
    L_0045e15f:
        mov eax,dword ptr [esi+8]
    L_0045e162:
        mov dword ptr [esi],eax
    L_0045e164:
        push dword ptr [esi+18h]
    L_0045e167:
        push dword ptr [esi+8]
    L_0045e16a:
        push dword ptr [esi+10h]
    L_0045e16d:
        call asm_read_00461361
    L_0045e172:
        add esp,0Ch
    L_0045e175:
        test eax,eax
    L_0045e177:
        mov dword ptr [esi+4],eax
    L_0045e17a:
        je short L_0045e1ee
    L_0045e17c:
        cmp eax,0FFFFFFFFh
    L_0045e17f:
        je short L_0045e1ee
    L_0045e181:
        mov edx,dword ptr [esi+0Ch]
    L_0045e184:
        test dl,82h
    L_0045e187:
        jne short L_0045e1c3
    L_0045e189:
        mov ecx,dword ptr [esi+10h]
    L_0045e18c:
        cmp ecx,0FFFFFFFFh
    L_0045e18f:
        push edi
    L_0045e190:
        je short L_0045e1a9
    L_0045e192:
        mov edi,ecx
    L_0045e194:
        sar edi,5
    L_0045e197:
        mov edi,dword ptr [edi*4+499200h]
    L_0045e19e:
        and ecx,1Fh
    L_0045e1a1:
        lea ecx,[ecx+ecx*8]
    L_0045e1a4:
        lea edi,[edi+ecx*4]
    L_0045e1a7:
        jmp short L_0045e1ae
    L_0045e1a9:
        mov edi,473708h
    L_0045e1ae:
        mov cl,byte ptr [edi+4]
    L_0045e1b1:
        and cl,82h
    L_0045e1b4:
        cmp cl,82h
    L_0045e1b7:
        pop edi
    L_0045e1b8:
        jne short L_0045e1c3
    L_0045e1ba:
        or edx,2000h
    L_0045e1c0:
        mov dword ptr [esi+0Ch],edx
    L_0045e1c3:
        cmp dword ptr [esi+18h],200h
    L_0045e1ca:
        jne short L_0045e1e0
    L_0045e1cc:
        mov ecx,dword ptr [esi+0Ch]
    L_0045e1cf:
        test cl,8
    L_0045e1d2:
        je short L_0045e1e0
    L_0045e1d4:
        test ch,4
    L_0045e1d7:
        jne short L_0045e1e0
    L_0045e1d9:
        mov dword ptr [esi+18h],1000h
    L_0045e1e0:
        mov ecx,dword ptr [esi]
    L_0045e1e2:
        dec eax
    L_0045e1e3:
        mov dword ptr [esi+4],eax
    L_0045e1e6:
        movzx eax,byte ptr [ecx]
    L_0045e1e9:
        inc ecx
    L_0045e1ea:
        mov dword ptr [esi],ecx
    L_0045e1ec:
        pop esi
    L_0045e1ed:
        ret
    L_0045e1ee:
        neg eax
    L_0045e1f0:
        sbb eax,eax
    L_0045e1f2:
        and eax,10h
    L_0045e1f5:
        add eax,10h
    L_0045e1f8:
        or dword ptr [esi+0Ch],eax
    L_0045e1fb:
        and dword ptr [esi+4],0
    L_0045e1ff:
        or eax,0FFFFFFFFh
    L_0045e202:
        pop esi
    L_0045e203:
        ret
    }
}
