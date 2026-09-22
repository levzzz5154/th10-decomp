// BLOCKED (D3506): closest_byte_count=0/143; first_diff=0x00447940;
// residual_class=private EAX index/EDX manager/EBX source inputs, x87
// division and copy-loop register pressure, and the real caller's private ABI.
// variants_tested=exact retail wrapper, live-Ghidra decompilation plus
// caller/callee topology, and MSVC 13.10 probe path (the wrapper is exact);
// no readable candidate was byte-measured without changing the fixed-address
// ownership manifest.
// next_lever=native-LTCG schema-2 cluster over caller 0x00447470 and this
// body, with the animation-record layout and EAX/EDX/EBX handoff confirmed,
// then measure the complete 143-byte contribution.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00447940..0x004479CE: ?AnimationManager_CopyPositionRecord@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_CopyPositionRecord_00447940() {
    __asm {
    L_00447940:
        imul eax,44h
    L_00447943:
        push esi
    L_00447944:
        push edi
    L_00447945:
        mov edi,dword ptr [edx+118h]
    L_0044794b:
        add edi,eax
    L_0044794d:
        mov ecx,11h
    L_00447952:
        mov esi,ebx
    L_00447954:
        rep movsd
    L_00447956:
        mov ecx,dword ptr [edx+118h]
    L_0044795c:
        add ecx,eax
    L_0044795e:
        pop edi
    L_0044795f:
        pop esi
    L_00447960:
        fld dword ptr [ecx+8]
    L_00447963:
        fdiv dword ptr [ecx+1Ch]
    L_00447966:
        fstp dword ptr [ecx+20h]
    L_00447969:
        mov ecx,dword ptr [edx+118h]
    L_0044796f:
        fld dword ptr [ecx+eax+10h]
    L_00447973:
        fdiv dword ptr [ecx+eax+1Ch]
    L_00447977:
        add ecx,eax
    L_00447979:
        fstp dword ptr [ecx+28h]
    L_0044797c:
        mov ecx,dword ptr [edx+118h]
    L_00447982:
        fld dword ptr [ecx+eax+0Ch]
    L_00447986:
        fdiv dword ptr [ecx+eax+18h]
    L_0044798a:
        add ecx,eax
    L_0044798c:
        fstp dword ptr [ecx+24h]
    L_0044798f:
        mov ecx,dword ptr [edx+118h]
    L_00447995:
        fld dword ptr [ecx+eax+14h]
    L_00447999:
        fdiv dword ptr [ecx+eax+18h]
    L_0044799d:
        add ecx,eax
    L_0044799f:
        fstp dword ptr [ecx+2Ch]
    L_004479a2:
        mov ecx,dword ptr [edx+118h]
    L_004479a8:
        fld dword ptr [ecx+eax+10h]
    L_004479ac:
        fsub dword ptr [ecx+eax+8]
    L_004479b0:
        add ecx,eax
    L_004479b2:
        fdiv dword ptr [ebx+38h]
    L_004479b5:
        fstp dword ptr [ecx+34h]
    L_004479b8:
        mov edx,dword ptr [edx+118h]
    L_004479be:
        fld dword ptr [eax+edx+14h]
    L_004479c2:
        fsub dword ptr [eax+edx+0Ch]
    L_004479c6:
        add eax,edx
    L_004479c8:
        fdiv dword ptr [ebx+3Ch]
    L_004479cb:
        fstp dword ptr [eax+30h]
    L_004479ce:
        ret
    }
}
