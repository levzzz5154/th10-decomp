#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462640..0x004626D5: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00462640() {
    __asm {
    L_00462640:
        jmp dword ptr [data_00466078]
    L_00462646:
        jmp dword ptr [data_00466074]
    L_0046264c:
        jmp dword ptr [data_00466070]
    L_00462652:
        jmp dword ptr [data_0046606c]
    L_00462658:
        jmp dword ptr [data_00466068]
    L_0046265e:
        jmp dword ptr [data_00466064]
    L_00462664:
        jmp dword ptr [data_00466060]
    L_0046266a:
        jmp dword ptr [data_0046605c]
    L_00462670:
        jmp dword ptr [data_00466058]
    L_00462676:
        jmp dword ptr [data_00466054]
    L_0046267c:
        jmp dword ptr [data_00466050]
    L_00462682:
        jmp dword ptr [data_0046604c]
    L_00462688:
        jmp dword ptr [data_00466048]
    L_0046268e:
        jmp dword ptr [data_00466044]
    L_00462694:
        jmp dword ptr [data_00466040]
    L_0046269a:
        jmp dword ptr [data_0046603c]
    L_004626a0:
        jmp dword ptr [data_004660f0]
    L_004626a6:
        jmp dword ptr [data_004661b4]
    L_004626ac:
        jmp dword ptr [data_004661b8]
    L_004626b2:
        jmp dword ptr [data_004661bc]
    L_004626b8:
        jmp dword ptr [data_004661c0]
    L_004626be:
        jmp dword ptr [data_004661c4]
    L_004626c4:
        jmp dword ptr [data_004661c8]
    L_004626ca:
        jmp dword ptr [data_004661cc]
    L_004626d0:
        jmp dword ptr [data_004661d0]
    }
}
