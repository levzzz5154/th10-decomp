#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00437200..0x0043729E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00437200() {
    __asm {
    L_00437200:
        mov eax,dword ptr [ecx+110h]
    L_00437206:
        imul eax,dword ptr [ecx+108h]
    L_0043720d:
        push esi
    L_0043720e:
        mov esi,dword ptr [ecx+120h]
    L_00437214:
        mov ecx,dword ptr [ecx+100h]
    L_0043721a:
        sub ecx,15h
    L_0043721d:
        push edi
    L_0043721e:
        je short L_00437287
    L_00437220:
        sub ecx,4
    L_00437223:
        je short L_00437257
    L_00437225:
        dec ecx
    L_00437226:
        je short L_0043722d
    L_00437228:
        pop edi
    L_00437229:
        xor al,al
    L_0043722b:
        pop esi
    L_0043722c:
        ret
    L_0043722d:
        mov edi,1
    L_00437232:
        and dl,0F0h
    L_00437235:
        cmp eax,edi
    L_00437237:
        jle short L_0043729a
    L_00437239:
        lea esp,[esp+force_disp32_zero]
    L_00437240:
        mov cl,byte ptr [edi+esi]
    L_00437243:
        and cl,0Fh
    L_00437246:
        or cl,dl
    L_00437248:
        mov byte ptr [edi+esi],cl
    L_0043724b:
        add edi,2
    L_0043724e:
        cmp edi,eax
    L_00437250:
        jl short L_00437240
    L_00437252:
        pop edi
    L_00437253:
        mov al,1
    L_00437255:
        pop esi
    L_00437256:
        ret
    L_00437257:
        test dl,dl
    L_00437259:
        sete cl
    L_0043725c:
        dec cl
    L_0043725e:
        mov edi,1
    L_00437263:
        and ecx,80h
    L_00437269:
        cmp eax,edi
    L_0043726b:
        jle short L_0043729a
    L_0043726d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00437270:
        mov dl,byte ptr [edi+esi]
    L_00437273:
        and dl,7Fh
    L_00437276:
        or dl,cl
    L_00437278:
        mov byte ptr [edi+esi],dl
    L_0043727b:
        add edi,2
    L_0043727e:
        cmp edi,eax
    L_00437280:
        jl short L_00437270
    L_00437282:
        pop edi
    L_00437283:
        mov al,1
    L_00437285:
        pop esi
    L_00437286:
        ret
    L_00437287:
        mov ecx,2
    L_0043728c:
        cmp eax,ecx
    L_0043728e:
        jle short L_0043729a
    L_00437290:
        mov byte ptr [ecx+esi],dl
    L_00437293:
        add ecx,4
    L_00437296:
        cmp ecx,eax
    L_00437298:
        jl short L_00437290
    L_0043729a:
        pop edi
    L_0043729b:
        mov al,1
    L_0043729d:
        pop esi
    L_0043729e:
        ret
    }
}
