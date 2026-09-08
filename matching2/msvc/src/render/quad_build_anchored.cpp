#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00443080..0x00443282: FUN_00443080
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00443080_00443080() {
    __asm {
    L_00443080:
        sub esp,0Ch
    L_00443083:
        fld dword ptr [esi+4Ch]
    L_00443086:
        mov eax,dword ptr [esi+35Ch]
    L_0044308c:
        fmul dword ptr [esi+3Ch]
    L_0044308f:
        shr eax,12h
    L_00443092:
        and eax,3
    L_00443095:
        sub eax,0
    L_00443098:
        fstp dword ptr [esp]
    L_0044309b:
        fld dword ptr [esi+50h]
    L_0044309e:
        fmul dword ptr [esi+40h]
    L_004430a1:
        fst dword ptr [esp+4]
    L_004430a5:
        fmul dword ptr [data_00470b0c]
    L_004430ab:
        fstp dword ptr [esp+8]
    L_004430af:
        je short L_00443125
    L_004430b1:
        dec eax
    L_004430b2:
        je short L_004430f0
    L_004430b4:
        dec eax
    L_004430b5:
        jne asm_target_00443177
    L_004430bb:
        fld dword ptr [esi+334h]
    L_004430c1:
        fadd dword ptr [esi+340h]
    L_004430c7:
        fadd dword ptr [esi+34Ch]
    L_004430cd:
        fsub dword ptr [esp]
    L_004430d0:
        fst dword ptr [data_004978f8]
    L_004430d6:
        fstp dword ptr [data_004978c0]
    L_004430dc:
        fld dword ptr [esi+334h]
    L_004430e2:
        fadd dword ptr [esi+340h]
    L_004430e8:
        fadd dword ptr [esi+34Ch]
    L_004430ee:
        jmp short L_0044316b
    L_004430f0:
        fld dword ptr [esi+334h]
    L_004430f6:
        fadd dword ptr [esi+340h]
    L_004430fc:
        fadd dword ptr [esi+34Ch]
    L_00443102:
        fst dword ptr [data_004978f8]
    L_00443108:
        fstp dword ptr [data_004978c0]
    L_0044310e:
        fld dword ptr [esi+334h]
    L_00443114:
        fadd dword ptr [esi+340h]
    L_0044311a:
        fadd dword ptr [esp]
    L_0044311d:
        fadd dword ptr [esi+34Ch]
    L_00443123:
        jmp short L_0044316b
    L_00443125:
        fld dword ptr [esi+34Ch]
    L_0044312b:
        sub esp,8
    L_0044312e:
        fadd dword ptr [esi+340h]
    L_00443134:
        fadd dword ptr [esi+334h]
    L_0044313a:
        fld dword ptr [esp+8]
    L_0044313e:
        fmul dword ptr [data_00470b0c]
    L_00443144:
        fsubp st(1),st
    L_00443146:
        fstp qword ptr [esp]
    L_00443149:
        call asm_FUN_00452ff0_00452ff0
    L_0044314e:
        fstp dword ptr [data_004978f8]
    L_00443154:
        mov eax,dword ptr [data_004978f8]
    L_00443159:
        fld dword ptr [data_004978f8]
    L_0044315f:
        fadd dword ptr [esp+8]
    L_00443163:
        add esp,8
    L_00443166:
        mov dword ptr [data_004978c0],eax
    L_0044316b:
        fst dword ptr [data_00497914]
    L_00443171:
        fstp dword ptr [data_004978dc]
    L_00443177:
        mov eax,dword ptr [esi+35Ch]
    L_0044317d:
        shr eax,14h
    L_00443180:
        and eax,3
    L_00443183:
        sub eax,0
    L_00443186:
        je short L_004431fa
    L_00443188:
        dec eax
    L_00443189:
        je short L_004431c8
    L_0044318b:
        dec eax
    L_0044318c:
        jne asm_target_00443246
    L_00443192:
        fld dword ptr [esi+344h]
    L_00443198:
        fadd dword ptr [esi+350h]
    L_0044319e:
        fadd dword ptr [esi+338h]
    L_004431a4:
        fsub dword ptr [esp+4]
    L_004431a8:
        fst dword ptr [data_004978e0]
    L_004431ae:
        fstp dword ptr [data_004978c4]
    L_004431b4:
        fld dword ptr [esi+344h]
    L_004431ba:
        fadd dword ptr [esi+350h]
    L_004431c0:
        fadd dword ptr [esi+338h]
    L_004431c6:
        jmp short L_0044323a
    L_004431c8:
        fld dword ptr [esi+344h]
    L_004431ce:
        fadd dword ptr [esi+350h]
    L_004431d4:
        fadd dword ptr [esi+338h]
    L_004431da:
        fst dword ptr [data_004978e0]
    L_004431e0:
        fstp dword ptr [data_004978c4]
    L_004431e6:
        fld dword ptr [esi+344h]
    L_004431ec:
        fadd dword ptr [esi+350h]
    L_004431f2:
        fadd dword ptr [esi+338h]
    L_004431f8:
        jmp short L_00443236
    L_004431fa:
        fld dword ptr [esi+350h]
    L_00443200:
        sub esp,8
    L_00443203:
        fadd dword ptr [esi+344h]
    L_00443209:
        fadd dword ptr [esi+338h]
    L_0044320f:
        fsub dword ptr [esp+10h]
    L_00443213:
        fstp qword ptr [esp]
    L_00443216:
        call asm_FUN_00452ff0_00452ff0
    L_0044321b:
        fstp dword ptr [data_004978e0]
    L_00443221:
        mov ecx,dword ptr [data_004978e0]
    L_00443227:
        fld dword ptr [data_004978e0]
    L_0044322d:
        add esp,8
    L_00443230:
        mov dword ptr [data_004978c4],ecx
    L_00443236:
        fadd dword ptr [esp+4]
    L_0044323a:
        fst dword ptr [data_00497918]
    L_00443240:
        fstp dword ptr [data_004978fc]
    L_00443246:
        fld dword ptr [esi+354h]
    L_0044324c:
        mov ecx,dword ptr [esp+10h]
    L_00443250:
        fadd dword ptr [esi+348h]
    L_00443256:
        push 1
    L_00443258:
        mov eax,esi
    L_0044325a:
        fadd dword ptr [esi+33Ch]
    L_00443260:
        fst dword ptr [data_0049791c]
    L_00443266:
        fst dword ptr [data_00497900]
    L_0044326c:
        fst dword ptr [data_004978e4]
    L_00443272:
        fstp dword ptr [data_004978c8]
    L_00443278:
        call asm_FUN_00442670_00442670
    L_0044327d:
        add esp,0Ch
    L_00443280:
        ret 4
    }
}
