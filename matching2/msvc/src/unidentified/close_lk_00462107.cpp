#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462107..0x00462189: __close_lk
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_close_lk_00462107() {
    __asm {
    L_00462107:
        push esi
    L_00462108:
        mov esi,dword ptr [esp+8]
    L_0046210c:
        push edi
    L_0046210d:
        push esi
    L_0046210e:
        call asm_get_osfhandle_0045f6d4
    L_00462113:
        cmp eax,0FFFFFFFFh
    L_00462116:
        pop ecx
    L_00462117:
        je short L_00462155
    L_00462119:
        cmp esi,1
    L_0046211c:
        je short L_00462123
    L_0046211e:
        cmp esi,2
    L_00462121:
        jne short L_00462139
    L_00462123:
        push 2
    L_00462125:
        call asm_get_osfhandle_0045f6d4
    L_0046212a:
        push 1
    L_0046212c:
        mov edi,eax
    L_0046212e:
        call asm_get_osfhandle_0045f6d4
    L_00462133:
        cmp eax,edi
    L_00462135:
        pop ecx
    L_00462136:
        pop ecx
    L_00462137:
        je short L_00462155
    L_00462139:
        push esi
    L_0046213a:
        call asm_get_osfhandle_0045f6d4
    L_0046213f:
        pop ecx
    L_00462140:
        push eax
    L_00462141:
        call dword ptr [data_004660cc]
    L_00462147:
        test eax,eax
    L_00462149:
        jne short L_00462155
    L_0046214b:
        call dword ptr [data_0046610c]
    L_00462151:
        mov edi,eax
    L_00462153:
        jmp short L_00462157
    L_00462155:
        xor edi,edi
    L_00462157:
        push esi
    L_00462158:
        call asm_free_osfhnd_0045f655
    L_0046215d:
        mov eax,esi
    L_0046215f:
        sar eax,5
    L_00462162:
        mov eax,dword ptr [eax*4+499200h]
    L_00462169:
        and esi,1Fh
    L_0046216c:
        test edi,edi
    L_0046216e:
        pop ecx
    L_0046216f:
        lea ecx,[esi+esi*8]
    L_00462172:
        mov byte ptr [eax+ecx*4+4],0
    L_00462177:
        je short L_00462185
    L_00462179:
        push edi
    L_0046217a:
        call asm_dosmaperr_00456b04
    L_0046217f:
        pop ecx
    L_00462180:
        or eax,0FFFFFFFFh
    L_00462183:
        jmp short L_00462187
    L_00462185:
        xor eax,eax
    L_00462187:
        pop edi
    L_00462188:
        pop esi
    L_00462189:
        ret
    }
}
