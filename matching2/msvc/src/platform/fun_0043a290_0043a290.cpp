// BLOCKED (D3503): closest_byte_count=272/272; first_diff=none
// (retail assembly baseline is exact; no readable candidate retained).
// residual_class=private EBX/EDI/ESI inputs, COM vtable/register ABI,
// stack-cookie frame, and caller-specific allocation at 0x00439FF0.
// variants_tested=live Ghidra decompilation at 0x0043A290; caller
// 0x00439FF0 inspection; retail assembly probe.
// next_lever=cluster native-LTCG joining 0x00439FF0 and this member with
// explicit COM/Win32 declarations and the observed register inputs.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438AD0..0x0043900C: GameMain
// Naked body preserves the retail register/stack ABI.

// 0x0043A290..0x0043A39F: FUN_0043a290
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a290_0043a290() {
    __asm {
    L_0043a290:
        sub esp,150h
    L_0043a296:
        mov eax,dword ptr [data_00473660]
    L_0043a29b:
        xor eax,esp
    L_0043a29d:
        test ebx,ebx
    L_0043a29f:
        push ebp
    L_0043a2a0:
        mov ebp,dword ptr [esp+158h]
    L_0043a2a7:
        mov dword ptr [esp+150h],eax
    L_0043a2ae:
        jne short L_0043a2ca
    L_0043a2b0:
        xor eax,eax
    L_0043a2b2:
        pop ebp
    L_0043a2b3:
        mov ecx,dword ptr [esp+14Ch]
    L_0043a2ba:
        xor ecx,esp
    L_0043a2bc:
        call asm_security_check_cookie_00458ea5
    L_0043a2c1:
        add esp,150h
    L_0043a2c7:
        ret 4
    L_0043a2ca:
        push 0
    L_0043a2cc:
        mov dword ptr [esp+10h],0
    L_0043a2d4:
        call dword ptr [data_00466308]
    L_0043a2da:
        lea eax,[esp+4]
    L_0043a2de:
        push eax
    L_0043a2df:
        push 46931Ch
    L_0043a2e4:
        push 1
    L_0043a2e6:
        push 0
    L_0043a2e8:
        push 46954Ch
    L_0043a2ed:
        call dword ptr [data_00466304]
    L_0043a2f3:
        test eax,eax
    L_0043a2f5:
        jl asm_target_0043a37e
    L_0043a2fb:
        mov eax,dword ptr [esp+4]
    L_0043a2ff:
        mov ecx,dword ptr [eax]
    L_0043a301:
        lea edx,[esp+8]
    L_0043a305:
        push edx
    L_0043a306:
        push 46997Ch
    L_0043a30b:
        push eax
    L_0043a30c:
        call dword ptr [ecx]
    L_0043a30e:
        test eax,eax
    L_0043a310:
        jl short L_0043a374
    L_0043a312:
        lea eax,[edi+edi]
    L_0043a315:
        push esi
    L_0043a316:
        push eax
    L_0043a317:
        call asm_operator_new_00452493
    L_0043a31c:
        add esp,4
    L_0043a31f:
        push edi
    L_0043a320:
        mov esi,eax
    L_0043a322:
        push esi
    L_0043a323:
        push 0FFFFFFFFh
    L_0043a325:
        push ebp
    L_0043a326:
        push 0
    L_0043a328:
        push 0
    L_0043a32a:
        call dword ptr [data_00466104]
    L_0043a330:
        mov eax,dword ptr [esp+0Ch]
    L_0043a334:
        mov ecx,dword ptr [eax]
    L_0043a336:
        push 0
    L_0043a338:
        push esi
    L_0043a339:
        push eax
    L_0043a33a:
        call dword ptr [ecx+14h]
    L_0043a33d:
        test eax,eax
    L_0043a33f:
        jl short L_0043a360
    L_0043a341:
        mov eax,dword ptr [esp+8]
    L_0043a345:
        mov edx,dword ptr [eax]
    L_0043a347:
        push 0
    L_0043a349:
        lea ecx,[esp+18h]
    L_0043a34d:
        push ecx
    L_0043a34e:
        push edi
    L_0043a34f:
        push ebx
    L_0043a350:
        push eax
    L_0043a351:
        call dword ptr [edx+0Ch]
    L_0043a354:
        test eax,eax
    L_0043a356:
        jl short L_0043a360
    L_0043a358:
        mov dword ptr [esp+10h],1
    L_0043a360:
        push esi
    L_0043a361:
        call asm_free_004524a1
    L_0043a366:
        mov eax,dword ptr [esp+10h]
    L_0043a36a:
        mov edx,dword ptr [eax]
    L_0043a36c:
        add esp,4
    L_0043a36f:
        push eax
    L_0043a370:
        call dword ptr [edx+8]
    L_0043a373:
        pop esi
    L_0043a374:
        mov eax,dword ptr [esp+4]
    L_0043a378:
        mov ecx,dword ptr [eax]
    L_0043a37a:
        push eax
    L_0043a37b:
        call dword ptr [ecx+8]
    L_0043a37e:
        call dword ptr [data_00466300]
    L_0043a384:
        mov ecx,dword ptr [esp+150h]
    L_0043a38b:
        mov eax,dword ptr [esp+0Ch]
    L_0043a38f:
        pop ebp
    L_0043a390:
        xor ecx,esp
    L_0043a392:
        call asm_security_check_cookie_00458ea5
    L_0043a397:
        add esp,150h
    L_0043a39d:
        ret 4
    }
}
