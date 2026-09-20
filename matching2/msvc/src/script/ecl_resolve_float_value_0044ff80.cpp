// BLOCKED (D2701): closest_byte_count=171; first_diff=unmeasured;
// residual_class=abi+x87: retail enters with the VM receiver in EAX, the
// operand bit index in CL, and the encoded float on the stack, then combines
// local-frame loads, scratch-stack type conversion, and a private virtual
// float resolver while returning through x87.  A normal declaration cannot
// preserve that complete entry tuple and the retail x87 branch scheduling.
// variants_tested=exact retail wrapper, the legacy ECL_ResolveFloatValue
// semantic model, the float-destination sibling layout, and the integer
// resolver's local/external/scratch source shapes; no compiler-readable
// candidate was byte-measured.
// next_lever=compile the value resolver with a synthetic native-LTCG context
// that pins EAX/CL and its stack float, co-compiling the variable resolver and
// scratch pop/write helpers; retain this exact wrapper until that cluster
// produces the 171-byte extent.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF70..0x0044E195: EclVm_StartChildRetail
// Naked body preserves the retail register/stack ABI.

// 0x0044FF80..0x0045002A: ?ECL_ResolveFloatValue@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResolveFloatValue_0044ff80() {
    __asm {
    L_0044ff80:
        push esi
    L_0044ff81:
        mov esi,eax
    L_0044ff83:
        mov eax,dword ptr [esi+4]
    L_0044ff86:
        movzx edx,word ptr [eax+8]
    L_0044ff8a:
        mov eax,1
    L_0044ff8f:
        shl eax,cl
    L_0044ff91:
        test edx,eax
    L_0044ff93:
        je short L_00450006
    L_0044ff95:
        fld dword ptr [esp+8]
    L_0044ff99:
        fcomp dword ptr [data_00470b04]
    L_0044ff9f:
        fnstsw ax
    L_0044ffa1:
        test ah,1
    L_0044ffa4:
        jne short L_0044ffbd
    L_0044ffa6:
        fld dword ptr [esp+8]
    L_0044ffaa:
        call asm_FUN_00463b2c_00463b2c
    L_0044ffaf:
        add eax,dword ptr [esi+100Ch]
    L_0044ffb5:
        fld dword ptr [eax+esi+8]
    L_0044ffb9:
        pop esi
    L_0044ffba:
        ret 4
    L_0044ffbd:
        fld dword ptr [data_00470b60]
    L_0044ffc3:
        fld dword ptr [esp+8]
    L_0044ffc7:
        fucompp
    L_0044ffc9:
        fnstsw ax
    L_0044ffcb:
        test ah,44h
    L_0044ffce:
        jp short L_0045000e
    L_0044ffd0:
        mov eax,dword ptr [esi+1008h]
    L_0044ffd6:
        add eax,0FFFFFFFCh
    L_0044ffd9:
        js short L_00450006
    L_0044ffdb:
        mov dword ptr [esi+1008h],eax
    L_0044ffe1:
        mov ecx,dword ptr [eax+esi+8]
    L_0044ffe5:
        add eax,0FFFFFFFCh
    L_0044ffe8:
        mov dword ptr [esi+1008h],eax
    L_0044ffee:
        mov al,byte ptr [eax+esi+8]
    L_0044fff2:
        cmp al,66h
    L_0044fff4:
        mov dword ptr [esp+8],ecx
    L_0044fff8:
        je short L_00450006
    L_0044fffa:
        cmp al,69h
    L_0044fffc:
        jne short L_00450006
    L_0044fffe:
        fild dword ptr [esp+8]
    L_00450002:
        fstp dword ptr [esp+8]
    L_00450006:
        fld dword ptr [esp+8]
    L_0045000a:
        pop esi
    L_0045000b:
        ret 4
    L_0045000e:
        mov esi,dword ptr [esi+1014h]
    L_00450014:
        fld dword ptr [esp+8]
    L_00450018:
        push edi
    L_00450019:
        mov edi,dword ptr [esi]
    L_0045001b:
        call asm_FUN_00463b2c_00463b2c
    L_00450020:
        push eax
    L_00450021:
        mov ecx,esi
    L_00450023:
        call dword ptr [edi+0Ch]
    L_00450026:
        pop edi
    L_00450027:
        pop esi
    L_00450028:
        ret 4
    }
}
