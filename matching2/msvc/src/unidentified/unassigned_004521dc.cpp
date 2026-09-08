#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004521DC..0x0045232B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004521dc() {
    __asm {
    L_004521dc:
        jmp dword ptr [data_00466270]
    L_004521e2:
        jmp dword ptr [data_00466274]
    L_004521e8:
        jmp dword ptr [data_00466278]
    L_004521ee:
        jmp dword ptr [data_004662ac]
    L_004521f4:
        jmp dword ptr [data_004662a8]
    L_004521fa:
        jmp dword ptr [data_004662a4]
    L_00452200:
        jmp dword ptr [data_004662a0]
    L_00452206:
        jmp dword ptr [data_0046629c]
    L_0045220c:
        jmp dword ptr [data_00466298]
    L_00452212:
        jmp dword ptr [data_00466294]
    L_00452218:
        jmp dword ptr [data_00466290]
    L_0045221e:
        jmp dword ptr [data_0046628c]
    L_00452224:
        jmp dword ptr [data_00466288]
    L_0045222a:
        jmp dword ptr [data_00466284]
    L_00452230:
        jmp dword ptr [data_00466280]
    L_00452236:
        jmp dword ptr [data_0046627c]
    L_0045223c:
        jmp dword ptr [data_004660a0]
    L_00452242:
        jmp dword ptr [data_004660a4]
    L_00452248:
        jmp dword ptr [data_004660a8]
    L_0045224e:
        jmp dword ptr [data_004660ac]
    L_00452254:
        jmp dword ptr [data_004660b0]
    L_0045225a:
        jmp dword ptr [data_004660b4]
    L_00452260:
        jmp dword ptr [data_004660b8]
    L_00452266:
        jmp dword ptr [data_004660bc]
    L_0045226c:
        jmp dword ptr [data_004660c0]
    L_00452272:
        jmp dword ptr [data_004660c4]
    L_00452278:
        jmp dword ptr [data_004660c8]
    L_0045227e:
        jmp dword ptr [data_004660cc]
    L_00452284:
        jmp dword ptr [data_004660d0]
    L_0045228a:
        jmp dword ptr [data_004660d4]
    L_00452290:
        jmp dword ptr [data_004660d8]
    L_00452296:
        jmp dword ptr [data_004660dc]
    L_0045229c:
        jmp dword ptr [data_004660e0]
    L_004522a2:
        jmp dword ptr [data_004660e4]
    L_004522a8:
        jmp dword ptr [data_004660e8]
    L_004522ae:
        jmp dword ptr [data_004660ec]
    L_004522b4:
        jmp dword ptr [data_004661dc]
    L_004522ba:
        jmp dword ptr [data_004660f4]
    L_004522c0:
        jmp dword ptr [data_004660f8]
    L_004522c6:
        jmp dword ptr [data_004660fc]
    L_004522cc:
        jmp dword ptr [data_00466100]
    L_004522d2:
        jmp dword ptr [data_00466104]
    L_004522d8:
        jmp dword ptr [data_00466108]
    L_004522de:
        jmp dword ptr [data_0046610c]
    L_004522e4:
        jmp dword ptr [data_00466110]
    L_004522ea:
        jmp dword ptr [data_00466114]
    L_004522f0:
        jmp dword ptr [data_00466118]
    L_004522f6:
        jmp dword ptr [data_0046611c]
    L_004522fc:
        jmp dword ptr [data_00466120]
    L_00452302:
        jmp dword ptr [data_00466124]
    L_00452308:
        jmp dword ptr [data_00466128]
    L_0045230e:
        jmp dword ptr [data_0046612c]
    L_00452314:
        jmp dword ptr [data_00466130]
    L_0045231a:
        jmp dword ptr [data_00466268]
    L_00452320:
        jmp dword ptr [data_004661f4]
    L_00452326:
        jmp dword ptr [data_004661f8]
    }
}
