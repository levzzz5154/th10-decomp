#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004201B0..0x00420269: FUN_004201b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004201b0_004201b0() {
    __asm {
    L_004201b0:
        push ecx
    L_004201b1:
        push esi
    L_004201b2:
        call asm_FUN_00420100_00420100
    L_004201b7:
        mov dword ptr [data_00476f78],3F800000h
    L_004201c1:
        mov dword ptr [data_004923a8],0FF000000h
    L_004201cb:
        call asm_FUN_004216f0_004216f0
    L_004201d0:
        call dword ptr [data_00466270]
    L_004201d6:
        mov dword ptr [data_00491ff8],eax
    L_004201db:
        mov word ptr [data_004918b0],ax
    L_004201e1:
        mov word ptr [data_004918a8],ax
    L_004201e7:
        lea eax,[esp+4]
    L_004201eb:
        push eax
    L_004201ec:
        push 0
    L_004201ee:
        push 492590h
    L_004201f3:
        push 43D080h
    L_004201f8:
        push 0
    L_004201fa:
        push 0
    L_004201fc:
        call dword ptr [data_00466118]
    L_00420202:
        mov dword ptr [data_004977ac],eax
    L_00420207:
        call asm_FUN_00413350_00413350
    L_0042020c:
        mov esi,474DD4h
    L_00420211:
        call asm_Platform_StopWorker_0044c150
    L_00420216:
        push 474DDCh
    L_0042021b:
        push 0
    L_0042021d:
        push 491C28h
    L_00420222:
        push 43BA90h
    L_00420227:
        push 0
    L_00420229:
        push 0
    L_0042022b:
        mov dword ptr [data_00474dec],43BA90h
    L_00420235:
        mov dword ptr [data_00474de4],1
    L_0042023f:
        mov dword ptr [data_00474de0],0
    L_00420249:
        call asm_beginthreadex_00453683
    L_0042024e:
        mov dword ptr [data_00474dd8],eax
    L_00420253:
        mov eax,dword ptr [data_00491c10]
    L_00420258:
        add esp,18h
    L_0042025b:
        call asm_FUN_004462f0_004462f0
    L_00420260:
        call asm_FUN_00437a00_00437a00
    L_00420265:
        xor eax,eax
    L_00420267:
        pop esi
    L_00420268:
        pop ecx
    L_00420269:
        ret
    }
}
