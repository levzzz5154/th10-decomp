#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D3FB..0x0045D475: __ShrMan
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ShrMan_0045d3fb() {
    __asm {
    L_0045d3fb:
        push ebp
    L_0045d3fc:
        mov ebp,esp
    L_0045d3fe:
        sub esp,0Ch
    L_0045d401:
        mov eax,dword ptr [ebp+0Ch]
    L_0045d404:
        push ebx
    L_0045d405:
        push esi
    L_0045d406:
        push edi
    L_0045d407:
        push 20h
    L_0045d409:
        pop esi
    L_0045d40a:
        cdq
    L_0045d40b:
        mov ecx,esi
    L_0045d40d:
        idiv ecx
    L_0045d40f:
        mov ebx,dword ptr [ebp+8]
    L_0045d412:
        or edi,0FFFFFFFFh
    L_0045d415:
        mov dword ptr [ebp+0Ch],esi
    L_0045d418:
        mov ecx,edx
    L_0045d41a:
        shl edi,cl
    L_0045d41c:
        mov dword ptr [ebp-8],eax
    L_0045d41f:
        xor eax,eax
    L_0045d421:
        sub dword ptr [ebp+0Ch],edx
    L_0045d424:
        not edi
    L_0045d426:
        mov dword ptr [ebp-4],eax
    L_0045d429:
        mov esi,dword ptr [ebx+eax*4]
    L_0045d42c:
        mov ecx,esi
    L_0045d42e:
        and ecx,edi
    L_0045d430:
        mov dword ptr [ebp-0Ch],ecx
    L_0045d433:
        mov ecx,edx
    L_0045d435:
        shr esi,cl
    L_0045d437:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045d43a:
        or esi,dword ptr [ebp-4]
    L_0045d43d:
        mov dword ptr [ebx+eax*4],esi
    L_0045d440:
        mov esi,dword ptr [ebp-0Ch]
    L_0045d443:
        shl esi,cl
    L_0045d445:
        inc eax
    L_0045d446:
        cmp eax,3
    L_0045d449:
        mov dword ptr [ebp-4],esi
    L_0045d44c:
        jl short L_0045d429
    L_0045d44e:
        push 2
    L_0045d450:
        pop eax
    L_0045d451:
        mov ecx,eax
    L_0045d453:
        sub ecx,dword ptr [ebp-8]
    L_0045d456:
        lea ecx,[ebx+ecx*4]
    L_0045d459:
        cmp eax,dword ptr [ebp-8]
    L_0045d45c:
        jl short L_0045d465
    L_0045d45e:
        mov edx,dword ptr [ecx]
    L_0045d460:
        mov dword ptr [ebx+eax*4],edx
    L_0045d463:
        jmp short L_0045d469
    L_0045d465:
        and dword ptr [ebx+eax*4],0
    L_0045d469:
        dec eax
    L_0045d46a:
        sub ecx,4
    L_0045d46d:
        test eax,eax
    L_0045d46f:
        jge short L_0045d459
    L_0045d471:
        pop edi
    L_0045d472:
        pop esi
    L_0045d473:
        pop ebx
    L_0045d474:
        leave
    L_0045d475:
        ret
    }
}
