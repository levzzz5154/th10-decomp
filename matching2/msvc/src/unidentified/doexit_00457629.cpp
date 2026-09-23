#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457629..0x004576D2: doexit
// Ghidra recovers the public shape as __cdecl doexit(UINT code, int quick,
// int return_to_caller). The entry also installs an MSVC SEH frame through a
// frame-building prolog and exits through its matching frame epilog; those are
// stack-transforming sequences, not ordinary helper calls. Keep them intact
// until a C++/SEH source form is shown to preserve that behavior.
extern "C" __declspec(naked) void __cdecl asm_doexit_00457629() {
    __asm {
    L_00457629:
        push 8
    L_0045762b:
        push 46AB18h
    L_00457630:
        call asm_SEH_prolog_00454bbc
    // Acquire CRT exit lock 8 (__cdecl; caller removes its argument below).
    L_00457635:
        push 8
    L_00457637:
        call asm_lock_00453c0c
    L_0045763c:
        pop ecx
    L_0045763d:
        xor edi,edi
    L_0045763f:
        mov dword ptr [ebp-4],edi
    L_00457642:
        xor esi,esi
    L_00457644:
        inc esi
    L_00457645:
        cmp dword ptr [data_004774b0],esi
    L_0045764b:
        jne short L_0045765d
    // A recursive exit request first asks TerminateProcess to stop the process.
    // The code value is staged before GetCurrentProcess; the latter is stdcall
    // with no parameters, and TerminateProcess consumes (handle, code).
    L_0045764d:
        push dword ptr [ebp+8]
    L_00457650:
        call dword ptr [data_00466144]
    L_00457656:
        push eax
    L_00457657:
        call dword ptr [data_00466148]
    L_0045765d:
        mov dword ptr [data_004774ac],esi
    L_00457663:
        mov al,byte ptr [ebp+10h]
    L_00457666:
        mov byte ptr [data_004774a8],al
    L_0045766b:
        cmp dword ptr [ebp+0Ch],edi
    L_0045766e:
        jne short L_004576a7
    // With quick == 0, run registered on-exit callbacks in reverse order,
    // skipping null slots, then visit the first initializer range.
    L_00457670:
        cmp dword ptr [data_00499310],edi
    L_00457676:
        je short L_00457697
    L_00457678:
        mov eax,dword ptr [data_0049930c]
    L_0045767d:
        sub eax,4
    L_00457680:
        mov dword ptr [data_0049930c],eax
    L_00457685:
        cmp eax,dword ptr [data_00499310]
    L_0045768b:
        jb short L_00457697
    L_0045768d:
        mov eax,dword ptr [eax]
    L_0045768f:
        cmp eax,edi
    L_00457691:
        je short L_00457678
    L_00457693:
        call eax
    L_00457695:
        jmp short L_00457678
    L_00457697:
        push 473058h
    L_0045769c:
        mov eax,473050h
    L_004576a1:
        call asm_initterm_00457589
    L_004576a6:
        pop ecx
    // This initializer range always runs, including the quick-exit path.
    L_004576a7:
        push 473064h
    L_004576ac:
        mov eax,47305Ch
    L_004576b1:
        call asm_initterm_00457589
    L_004576b6:
        pop ecx
    L_004576b7:
        or dword ptr [ebp-4],0FFFFFFFFh
    // This shared block reads return_to_caller from our EBP frame and releases
    // lock 8 only when the caller will regain control; it is not an ordinary
    // no-argument function despite Ghidra's split function boundary here.
    L_004576bb:
        call asm_FUN_004576d8_004576d8
    L_004576c0:
        cmp dword ptr [ebp+10h],edi
    L_004576c3:
        TH10_REL8(0x75, 0x004576c3, VA_asm_doexit_part_004576e6)
    // The non-returning path marks exit in progress and delegates termination.
    L_004576c5:
        mov dword ptr [data_004774b0],esi
    L_004576cb:
        push dword ptr [ebp+8]
    L_004576ce:
        call asm_crtExitProcess_00457547
    }
}

// 0x004576E6..0x004576EB: doexit
// This is the return_to_caller branch's matching SEH/frame epilog and RET.
extern "C" __declspec(naked) void __cdecl asm_doexit_part_004576e6() {
    __asm {
    L_004576e6:
        call asm_SEH_epilog_00454bf7
    L_004576eb:
        ret
    }
}
