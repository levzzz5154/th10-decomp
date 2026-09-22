// BLOCKED (H3901): closest_byte_count=0/177; first_diff=0x00420000;
// residual_class=member entry ABI plus global/object layout and virtual-call
// scheduling. The IDA model observes the object in ECX, a global manager load,
// the embedded +0x384/+0x388 state, and two calls through unrelated vtables;
// preserving those offsets is insufficient to force retail's register/save
// order in an isolated translation unit.
// variants_tested=["exact retail naked baseline retained",
// "IDA __thiscall semantic translation reviewed; no standalone readable candidate retained"];
// next_lever=caller-inclusive native-LTCG cluster rooted by 0x00420470, with
// FUN_004215A0 and both virtual callees visible to the same schema-2 link.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420000..0x004200B0: FUN_00420000
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00420000_00420000() {
    __asm {
    L_00420000:
        mov eax,dword ptr [data_00491c10]
    L_00420005:
        push ebx
    L_00420006:
        push esi
    L_00420007:
        mov esi,ecx
    L_00420009:
        mov cl,0FFh
    L_0042000b:
        xor ebx,ebx
    L_0042000d:
        push edi
    L_0042000e:
        lea edi,[esi+26Ch]
    L_00420014:
        mov dword ptr [eax+3ADA70h],ebx
    L_0042001a:
        mov dword ptr [eax+3ADA64h],ebx
    L_00420020:
        mov byte ptr [eax+3ADA69h],cl
    L_00420026:
        mov byte ptr [eax+3ADA68h],3
    L_0042002d:
        mov byte ptr [eax+3ADA6Bh],cl
    L_00420033:
        mov byte ptr [eax+3ADA6Ch],cl
    L_00420039:
        mov dword ptr [eax+73245Ch],ebx
    L_0042003f:
        mov dword ptr [eax+732458h],80808080h
    L_00420049:
        mov byte ptr [eax+3ADA6Eh],cl
    L_0042004f:
        mov dword ptr [eax+60h],ebx
    L_00420052:
        mov dword ptr [eax+5Ch],ebx
    L_00420055:
        mov byte ptr [eax+3ADA6Ah],cl
    L_0042005b:
        mov dword ptr [esi+384h],edi
    L_00420061:
        call asm_FUN_004215a0_004215a0
    L_00420066:
        mov edx,dword ptr [esi+384h]
    L_0042006c:
        mov eax,dword ptr [esi+8]
    L_0042006f:
        mov ecx,dword ptr [eax]
    L_00420071:
        add edx,0CCh
    L_00420077:
        push edx
    L_00420078:
        push eax
    L_00420079:
        call dword ptr [ecx+0BCh]
    L_0042007f:
        push ebx
    L_00420080:
        push 3F800000h
    L_00420085:
        mov dword ptr [esi+388h],1
    L_0042008f:
        mov edx,dword ptr [data_004923a8]
    L_00420095:
        mov eax,dword ptr [data_00491c30]
    L_0042009a:
        mov ecx,dword ptr [eax]
    L_0042009c:
        push edx
    L_0042009d:
        push 1
    L_0042009f:
        push ebx
    L_004200a0:
        push ebx
    L_004200a1:
        push eax
    L_004200a2:
        call dword ptr [ecx+0ACh]
    L_004200a8:
        pop edi
    L_004200a9:
        pop esi
    L_004200aa:
        mov eax,1
    L_004200af:
        pop ebx
    L_004200b0:
        ret
    }
}
