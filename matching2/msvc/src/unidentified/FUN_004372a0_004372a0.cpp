#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004372A0..0x0043737D: FUN_004372a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004372a0_004372a0() {
    __asm {
    L_004372a0:
        sub esp,30h
    L_004372a3:
        mov eax,dword ptr [data_00473660]
    L_004372a8:
        xor eax,esp
    L_004372aa:
        push ebx
    L_004372ab:
        mov dword ptr [esp+30h],eax
    L_004372af:
        push edi
    L_004372b0:
        lea eax,[esp+8]
    L_004372b4:
        push eax
    L_004372b5:
        mov edi,ecx
    L_004372b7:
        call asm_FUN_00436890_00436890
    L_004372bc:
        mov eax,dword ptr [esp+8]
    L_004372c0:
        test eax,eax
    L_004372c2:
        mov ecx,dword ptr [esp+44h]
    L_004372c6:
        mov dword ptr [esp+0Ch],0
    L_004372ce:
        mov dword ptr [esp+10h],ecx
    L_004372d2:
        je short L_004372e3
    L_004372d4:
        push eax
    L_004372d5:
        call dword ptr [data_00466030]
    L_004372db:
        mov dword ptr [esp+8],0
    L_004372e3:
        cmp dword ptr [esp+2Ch],10h
    L_004372e8:
        mov eax,dword ptr [esp+18h]
    L_004372ec:
        jae short L_004372f2
    L_004372ee:
        lea eax,[esp+18h]
    L_004372f2:
        mov edx,dword ptr [esp+30h]
    L_004372f6:
        push eax
    L_004372f7:
        mov eax,dword ptr [esp+10h]
    L_004372fb:
        push 30h
    L_004372fd:
        mov ecx,dword ptr [esp+18h]
    L_00437301:
        push 0
    L_00437303:
        push 0
    L_00437305:
        push 0
    L_00437307:
        push 1
    L_00437309:
        push 0
    L_0043730b:
        push 0
    L_0043730d:
        push 0
    L_0043730f:
        push edx
    L_00437310:
        push 0
    L_00437312:
        push 0
    L_00437314:
        push eax
    L_00437315:
        push ecx
    L_00437316:
        call dword ptr [data_00466034]
    L_0043731c:
        mov edx,dword ptr [esp+4Ch]
    L_00437320:
        mov ecx,dword ptr [esp+48h]
    L_00437324:
        push edx
    L_00437325:
        mov edx,dword ptr [esp+44h]
    L_00437329:
        push ecx
    L_0043732a:
        push eax
    L_0043732b:
        mov dword ptr [esp+14h],eax
    L_0043732f:
        mov eax,dword ptr [esp+48h]
    L_00437333:
        push edx
    L_00437334:
        push eax
    L_00437335:
        mov eax,esi
    L_00437337:
        call asm_FUN_00437380_00437380
    L_0043733c:
        mov bl,al
    L_0043733e:
        mov eax,dword ptr [esp+8]
    L_00437342:
        test eax,eax
    L_00437344:
        je short L_00437355
    L_00437346:
        push eax
    L_00437347:
        call dword ptr [data_00466030]
    L_0043734d:
        mov dword ptr [esp+8],0
    L_00437355:
        cmp dword ptr [esp+2Ch],10h
    L_0043735a:
        jb short L_00437369
    L_0043735c:
        mov ecx,dword ptr [esp+18h]
    L_00437360:
        push ecx
    L_00437361:
        call asm_free_004524a1
    L_00437366:
        add esp,4
    L_00437369:
        mov ecx,dword ptr [esp+34h]
    L_0043736d:
        pop edi
    L_0043736e:
        mov al,bl
    L_00437370:
        pop ebx
    L_00437371:
        xor ecx,esp
    L_00437373:
        call asm_security_check_cookie_00458ea5
    L_00437378:
        add esp,30h
    L_0043737b:
        ret 14h
    }
}
