#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046253E..0x00462639: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046253e() {
    __asm {
    L_0046253e:
        jmp dword ptr [data_004661e8]
    L_00462544:
        jmp dword ptr [data_004661e4]
    L_0046254a:
        jmp dword ptr [data_004661e0]
    L_00462550:
        jmp dword ptr [data_004661b0]
    L_00462556:
        jmp dword ptr [data_004661ac]
    L_0046255c:
        jmp dword ptr [data_004661a8]
    L_00462562:
        jmp dword ptr [data_004661a4]
    L_00462568:
        jmp dword ptr [data_004661a0]
    L_0046256e:
        jmp dword ptr [data_0046619c]
    L_00462574:
        jmp dword ptr [data_00466198]
    L_0046257a:
        jmp dword ptr [data_00466194]
    L_00462580:
        jmp dword ptr [data_00466190]
    L_00462586:
        jmp dword ptr [data_0046618c]
    L_0046258c:
        jmp dword ptr [data_00466188]
    L_00462592:
        jmp dword ptr [data_00466180]
    L_00462598:
        jmp dword ptr [data_0046617c]
    L_0046259e:
        jmp dword ptr [data_00466178]
    L_004625a4:
        jmp dword ptr [data_00466174]
    L_004625aa:
        jmp dword ptr [data_00466170]
    L_004625b0:
        jmp dword ptr [data_0046616c]
    L_004625b6:
        jmp dword ptr [data_00466168]
    L_004625bc:
        jmp dword ptr [data_00466164]
    L_004625c2:
        jmp dword ptr [data_00466160]
    L_004625c8:
        jmp dword ptr [data_0046615c]
    L_004625ce:
        jmp dword ptr [data_00466158]
    L_004625d4:
        jmp dword ptr [data_00466154]
    L_004625da:
        jmp dword ptr [data_00466150]
    L_004625e0:
        jmp dword ptr [data_0046614c]
    L_004625e6:
        jmp dword ptr [data_00466148]
    L_004625ec:
        jmp dword ptr [data_00466144]
    L_004625f2:
        jmp dword ptr [data_00466140]
    L_004625f8:
        jmp dword ptr [data_0046613c]
    L_004625fe:
        jmp dword ptr [data_00466138]
    L_00462604:
        jmp dword ptr [data_00466134]
    L_0046260a:
        jmp dword ptr [data_0046609c]
    L_00462610:
        jmp dword ptr [data_00466098]
    L_00462616:
        jmp dword ptr [data_00466094]
    L_0046261c:
        jmp dword ptr [data_00466090]
    L_00462622:
        jmp dword ptr [data_0046608c]
    L_00462628:
        jmp dword ptr [data_00466088]
    L_0046262e:
        jmp dword ptr [data_00466084]
    L_00462634:
        jmp dword ptr [data_00466080]
    }
}
