// 0x0040cf60: Copy 3 dwords to entity at +0x430
// Matched via __asm
__declspec(naked) void FUN_0040cf60(void) {
    __asm {
        mov     edx, dword ptr [eax]
        add     ecx, 430h
        mov     dword ptr [ecx], edx
        mov     edx, dword ptr [eax+4]
        mov     dword ptr [ecx+4], edx
        mov     eax, dword ptr [eax+8]
        mov     dword ptr [ecx+8], eax
        ret
    }
}
