// 004477D0: FUN_004477d0
// Original size: 64 bytes, actual code: 16 instructions
extern "C" void FUN_00447810(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_004477d0(void) {
    __asm {
        test  esi,esi
        jl loc_00447806
        cmp  esi,0x21
        jae loc_00447806
        push  edi
        mov  edi,DWORD PTR [ebx+esi*4+0x3ad06c]
        test  edi,edi
        je loc_00447805
        call FUN_00447810
        mov  eax,DWORD PTR [ebx+esi*4+0x3ad06c]
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebx+esi*4+0x3ad06c],0x0
    loc_00447805:
        pop  edi
    loc_00447806:
        ret
    }
}
