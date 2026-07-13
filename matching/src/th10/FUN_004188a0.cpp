// 004188A0: FUN_004188a0
// Original size: 144 bytes, actual code: 42 instructions
extern "C" void FUN_00413790(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_004492a0(void);

extern "C" __declspec(naked) void FUN_004188a0(void) {
    __asm {
        push  ecx
        push  esi
        mov  esi,DWORD PTR [eax+0x30]
        add  esi,ecx
        mov  ecx,esi
        cmp  ecx,0x9
        mov  DWORD PTR [eax+0x30],esi
        jle loc_004188CB
        mov  DWORD PTR [eax+0x30],0x9
        mov  ecx,DWORD PTR ds:0x474c70
        mov  eax,ds:0x47770c
        call FUN_00413790
        pop  esi
        pop  ecx
        ret
    loc_004188CB:
        push  edi
        push  0x0
        mov  edi,0x2c
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  edi,DWORD PTR ds:0x47770c
        mov  edx,DWORD PTR [edi+0x9e18]
        lea  esi,[edi+0x9e18]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        call FUN_004492a0
        push  0xf
        mov  DWORD PTR [esi],0x0
        mov  eax,DWORD PTR [edi+0x9ec8]
        push  0x4b
        push  eax
        lea  edi,[esp+0x14]
        call FUN_00448d00
        mov  ecx,DWORD PTR [eax]
        mov  eax,ds:0x47770c
        mov  DWORD PTR [esi],ecx
        mov  ecx,DWORD PTR ds:0x474c70
        pop  edi
        call FUN_00413790
        pop  esi
        pop  ecx
        ret
    }
}
