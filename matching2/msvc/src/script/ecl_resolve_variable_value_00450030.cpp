// BLOCKED (D2701): closest_byte_count=58; first_diff=unmeasured;
// residual_class=abi: retail receives the VM in ESI and the variable index in
// ECX, tests the instruction-table mask, then selects a pooled-frame pointer
// or a private virtual external-variable pointer.  A standalone C++ member
// cannot name the promoted ESI receiver while retaining the observed ECX
// index and EAX return.
// variants_tested=exact retail wrapper, the legacy ECL_ResolveVariableValue
// semantic model, the readable integer/float destination accessors, and the
// ECL variable-table layout recovered from the dispatcher; native-LTCG
// contexts shaped from the actual interpreter writer/resolver/find call order,
// live resolver pointers across helper calls, same-TU resolver definition,
// free/member declarations, widened masks, and dummy pressure parameters all
// retained EDX as the private receiver; no compiler-readable candidate matched.
// next_lever=compile the actual interpreter caller body (0x0044E1A0) in the
// same native-LTCG scope, or use a purpose-built context that genuinely pins
// the VM in ESI; retain the 58-byte wrapper until that ABI is reproduced.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF70..0x0044E195: EclVm_StartChildRetail
// Naked body preserves the retail register/stack ABI.

// 0x00450030..0x00450069: ?ECL_ResolveVariableValue@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResolveVariableValue_00450030() {
    __asm {
    L_00450030:
        mov eax,dword ptr [esi+4]
    L_00450033:
        movzx edx,word ptr [eax+8]
    L_00450037:
        push edi
    L_00450038:
        mov edi,1
    L_0045003d:
        shl edi,cl
    L_0045003f:
        test edx,edi
    L_00450041:
        pop edi
    L_00450042:
        je short L_00450067
    L_00450044:
        mov edx,dword ptr [eax+ecx*4+10h]
    L_00450048:
        test edx,edx
    L_0045004a:
        jl short L_0045005a
    L_0045004c:
        mov eax,dword ptr [esi+100Ch]
    L_00450052:
        lea ecx,[esi+8]
    L_00450055:
        add eax,edx
    L_00450057:
        add eax,ecx
    L_00450059:
        ret
    L_0045005a:
        mov ecx,dword ptr [esi+1014h]
    L_00450060:
        mov eax,dword ptr [ecx]
    L_00450062:
        push edx
    L_00450063:
        call dword ptr [eax+8]
    L_00450066:
        ret
    L_00450067:
        xor eax,eax
    L_00450069:
        ret
    }
}
