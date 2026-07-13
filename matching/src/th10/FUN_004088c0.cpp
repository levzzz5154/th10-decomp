// 004088C0: FUN_004088c0
// Original size: 80 bytes, actual code: 28 instructions

extern "C" __declspec(naked) void FUN_004088c0(void) {
    __asm {
        xor  eax,eax
        xor  ecx,ecx
        push  esi
    loc_004088C5:
        movsx esi,BYTE PTR [ecx+0x4743c0]
        cmp  esi,edx
        jne loc_004088D1
        inc  eax
    loc_004088D1:
        movsx esi,BYTE PTR [ecx+0x4743c1]
        cmp  esi,edx
        jne loc_004088DD
        inc  eax
    loc_004088DD:
        movsx esi,BYTE PTR [ecx+0x4743c2]
        cmp  esi,edx
        jne loc_004088E9
        inc  eax
    loc_004088E9:
        movsx esi,BYTE PTR [ecx+0x4743c3]
        cmp  esi,edx
        jne loc_004088F5
        inc  eax
    loc_004088F5:
        movsx esi,BYTE PTR [ecx+0x4743c4]
        cmp  esi,edx
        jne loc_00408901
        inc  eax
    loc_00408901:
        add  ecx,0x5
        cmp  ecx,0x6e
        jl loc_004088C5
        pop  esi
        ret
    }
}
