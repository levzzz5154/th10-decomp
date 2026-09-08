#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452FF0..0x00453110: FUN_00452ff0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00452ff0_00452ff0() {
    __asm {
    L_00452ff0:
        cmp dword ptr [data_00499300],0
    L_00452ff7:
        je asm_floor_default_00458c39
    L_00452ffd:
        sub esp,8
    L_00453000:
        stmxcsr dword ptr [esp+4]
    L_00453005:
        mov eax,dword ptr [esp+4]
    L_00453009:
        and eax,1F80h
    L_0045300e:
        cmp eax,1F80h
    L_00453013:
        jne short L_00453024
    L_00453015:
        fnstcw word ptr [esp]
    L_00453018:
        mov ax,word ptr [esp]
    L_0045301c:
        TH10_OPERAND16()
        and eax,7Fh
    L_00453020:
        TH10_OPERAND16()
        cmp eax,7Fh
    L_00453024:
        lea esp,[esp+8]
    L_00453028:
        jne asm_floor_default_00458c39
    L_0045302e:
        jmp short L_00453030
    L_00453030:
        movq xmm0,qword ptr [esp+4]
    L_00453036:
        movapd xmm2,xmmword ptr [data_0046a710]
    L_0045303e:
        movapd xmm1,xmm0
    L_00453042:
        movapd xmm7,xmm0
    L_00453046:
        psrlq xmm0,34h
    L_0045304b:
        movd eax,xmm0
    L_0045304f:
        andpd xmm0,xmmword ptr [data_0046a740]
    L_00453057:
        psubd xmm2,xmm0
    L_0045305b:
        psrlq xmm1,xmm2
    L_0045305f:
        test eax,800h
    L_00453064:
        jne short L_004530b2
    L_00453066:
        cmp eax,3FFh
    L_0045306b:
        jl short L_004530ea
    L_0045306d:
        psllq xmm1,xmm2
    L_00453071:
        cmp eax,432h
    L_00453076:
        jg short L_00453083
    L_00453078:
        movq qword ptr [esp+4],xmm1
    L_0045307e:
        fld qword ptr [esp+4]
    L_00453082:
        ret
    L_00453083:
        ucomisd xmm7,xmm7
    L_00453087:
        jnp short L_004530ad
    L_00453089:
        mov edx,3EDh
    L_0045308e:
        sub esp,10h
    L_00453091:
        mov dword ptr [esp+0Ch],edx
    L_00453095:
        mov edx,esp
    L_00453097:
        add edx,14h
    L_0045309a:
        mov dword ptr [esp+8],edx
    L_0045309e:
        mov dword ptr [esp+4],edx
    L_004530a2:
        mov dword ptr [esp],edx
    L_004530a5:
        call asm_FUN_004588a7_004588a7
    L_004530aa:
        add esp,10h
    L_004530ad:
        fld qword ptr [esp+4]
    L_004530b1:
        ret
    L_004530b2:
        movq xmm0,qword ptr [esp+4]
    L_004530b8:
        psllq xmm1,xmm2
    L_004530bc:
        movapd xmm3,xmm0
    L_004530c0:
        cmpltpd xmm0,xmm1
    L_004530c5:
        cmp eax,0BFFh
    L_004530ca:
        jl short L_004530ed
    L_004530cc:
        cmp eax,0C32h
    L_004530d1:
        jg short L_00453083
    L_004530d3:
        andpd xmm0,xmmword ptr [data_0046a700]
    L_004530db:
        subsd xmm1,xmm0
    L_004530df:
        movq qword ptr [esp+4],xmm1
    L_004530e5:
        fld qword ptr [esp+4]
    L_004530e9:
        ret
    L_004530ea:
        fldz
    L_004530ec:
        ret
    L_004530ed:
        cmpltpd xmm3,xmmword ptr [data_0046a730]
    L_004530f6:
        orpd xmm3,xmmword ptr [data_0046a730]
    L_004530fe:
        andpd xmm3,xmmword ptr [data_0046a720]
    L_00453106:
        movq qword ptr [esp+4],xmm3
    L_0045310c:
        fld qword ptr [esp+4]
    L_00453110:
        ret
    }
}
