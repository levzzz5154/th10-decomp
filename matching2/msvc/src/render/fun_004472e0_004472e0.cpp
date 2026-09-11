#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004470C0..0x00447270: FUN_004470c0
// Naked body preserves the retail register/stack ABI.

// 0x004472E0..0x004473B5: FUN_004472e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004472e0_004472e0() {
    __asm {
    L_004472e0:
        sub esp,10Ch
    L_004472e6:
        mov eax,dword ptr [data_00473660]
    L_004472eb:
        xor eax,esp
    L_004472ed:
        mov dword ptr [esp+108h],eax
    L_004472f4:
        mov eax,dword ptr [esp+110h]
    L_004472fb:
        test eax,eax
    L_004472fd:
        push ebx
    L_004472fe:
        push edi
    L_004472ff:
        mov ebx,ecx
    L_00447301:
        mov edi,edx
    L_00447303:
        jne short L_0044730c
    L_00447305:
        push 470274h
    L_0044730a:
        jmp short L_00447317
    L_0044730c:
        cmp dword ptr [eax+28h],4
    L_00447310:
        je short L_00447329
    L_00447312:
        push 470254h
    L_00447317:
        mov edi,474F70h
    L_0044731c:
        call asm_TextLog_AppendLine_0044b8e0
    L_00447321:
        add esp,4
    L_00447324:
        or eax,0FFFFFFFFh
    L_00447327:
        jmp short L_0044739d
    L_00447329:
        mov cl,byte ptr [eax+34h]
    L_0044732c:
        test cl,cl
    L_0044732e:
        push esi
    L_0044732f:
        jne short L_00447397
    L_00447331:
        mov esi,dword ptr [eax+1Ch]
    L_00447334:
        add esi,eax
    L_00447336:
        cmp byte ptr [esi],40h
    L_00447339:
        je short L_00447397
    L_0044733b:
        push esi
    L_0044733c:
        lea eax,[esp+14h]
    L_00447340:
        push 46E1C8h
    L_00447345:
        push eax
    L_00447346:
        call asm_sprintf_00452ae8
    L_0044734b:
        add esp,0Ch
    L_0044734e:
        push 1
    L_00447350:
        lea ecx,[esp+10h]
    L_00447354:
        push ecx
    L_00447355:
        lea eax,[esp+18h]
    L_00447359:
        call asm_FUN_0044b360_0044b360
    L_0044735e:
        test eax,eax
    L_00447360:
        jne short L_0044737a
    L_00447362:
        push esi
    L_00447363:
        push 470210h
    L_00447368:
        mov edi,474F70h
    L_0044736d:
        call asm_TextLog_AppendLine_0044b8e0
    L_00447372:
        add esp,8
    L_00447375:
        or eax,0FFFFFFFFh
    L_00447378:
        jmp short L_0044739c
    L_0044737a:
        mov edx,dword ptr [edi+120h]
    L_00447380:
        mov esi,dword ptr [esp+0Ch]
    L_00447384:
        shl ebx,4
    L_00447387:
        mov ecx,ebx
    L_00447389:
        mov dword ptr [edx+ecx+8],esi
    L_0044738d:
        mov edx,dword ptr [edi+120h]
    L_00447393:
        mov dword ptr [edx+ecx+4],eax
    L_00447397:
        mov eax,1
    L_0044739c:
        pop esi
    L_0044739d:
        mov ecx,dword ptr [esp+110h]
    L_004473a4:
        pop edi
    L_004473a5:
        pop ebx
    L_004473a6:
        xor ecx,esp
    L_004473a8:
        call asm_security_check_cookie_00458ea5
    L_004473ad:
        add esp,10Ch
    L_004473b3:
        ret 4
    }
}
