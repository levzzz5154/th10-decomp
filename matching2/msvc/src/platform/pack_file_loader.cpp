#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A1C0..0x0043A28E: FUN_0043a1c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a1c0_0043a1c0() {
    __asm {
    L_0043a1c0:
        sub esp,110h
    L_0043a1c6:
        mov eax,dword ptr [data_00473660]
    L_0043a1cb:
        xor eax,esp
    L_0043a1cd:
        mov dword ptr [esp+10Ch],eax
    L_0043a1d4:
        push 105h
    L_0043a1d9:
        lea eax,[esp+8]
    L_0043a1dd:
        push eax
    L_0043a1de:
        push 0
    L_0043a1e0:
        call dword ptr [data_004660dc]
    L_0043a1e6:
        test eax,eax
    L_0043a1e8:
        je asm_target_0043a277
    L_0043a1ee:
        push ebx
    L_0043a1ef:
        push esi
    L_0043a1f0:
        push 1
    L_0043a1f2:
        lea ecx,[esp+0Ch]
    L_0043a1f6:
        push ecx
    L_0043a1f7:
        lea eax,[esp+14h]
    L_0043a1fb:
        xor esi,esi
    L_0043a1fd:
        call asm_FUN_0044b360_0044b360
    L_0043a202:
        mov ecx,eax
    L_0043a204:
        test ecx,ecx
    L_0043a206:
        mov ebx,ecx
    L_0043a208:
        jne short L_0043a224
    L_0043a20a:
        pop esi
    L_0043a20b:
        or eax,0FFFFFFFFh
    L_0043a20e:
        pop ebx
    L_0043a20f:
        mov ecx,dword ptr [esp+10Ch]
    L_0043a216:
        xor ecx,esp
    L_0043a218:
        call asm_security_check_cookie_00458ea5
    L_0043a21d:
        add esp,110h
    L_0043a223:
        ret
    L_0043a224:
        push edi
    L_0043a225:
        mov edi,dword ptr [esp+0Ch]
    L_0043a229:
        mov eax,edi
    L_0043a22b:
        cdq
    L_0043a22c:
        and edx,3
    L_0043a22f:
        add eax,edx
    L_0043a231:
        sar eax,2
    L_0043a234:
        dec eax
    L_0043a235:
        test eax,eax
    L_0043a237:
        jle short L_0043a248
    L_0043a239:
        lea esp,[esp+force_disp32_zero]
    L_0043a240:
        add esi,dword ptr [ecx]
    L_0043a242:
        add ecx,4
    L_0043a245:
        dec eax
    L_0043a246:
        jne short L_0043a240
    L_0043a248:
        push ebx
    L_0043a249:
        call asm_free_00452422
    L_0043a24e:
        add esp,4
    L_0043a251:
        mov dword ptr [data_00492384],edi
    L_0043a257:
        pop edi
    L_0043a258:
        mov dword ptr [data_00492380],esi
    L_0043a25e:
        mov eax,esi
    L_0043a260:
        pop esi
    L_0043a261:
        pop ebx
    L_0043a262:
        mov ecx,dword ptr [esp+10Ch]
    L_0043a269:
        xor ecx,esp
    L_0043a26b:
        call asm_security_check_cookie_00458ea5
    L_0043a270:
        add esp,110h
    L_0043a276:
        ret
    L_0043a277:
        mov ecx,dword ptr [esp+10Ch]
    L_0043a27e:
        xor ecx,esp
    L_0043a280:
        or eax,0FFFFFFFFh
    L_0043a283:
        call asm_security_check_cookie_00458ea5
    L_0043a288:
        add esp,110h
    L_0043a28e:
        ret
    }
}

