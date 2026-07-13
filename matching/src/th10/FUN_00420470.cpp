// 00420470: FUN_00420470
// Original size: 512 bytes, actual code: 59 instructions
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);

extern "C" __declspec(naked) void FUN_00420470(void) {
    __asm {
        push  ebx
        push  ebp
        push  esi
        push  edi
        xor  eax,eax
        push  0x41ff80
        mov  DWORD PTR ds:0x491fb4,0xfffffffe
        mov  ds:0x491fb8,eax
        mov  ds:0x491fc0,eax
        call FUN_00449ed0
        mov  esi,DWORD PTR [eax+0x4]
        mov  ecx,DWORD PTR ds:0x491be4
        mov  ebx,0x2
        or   esi,ebx
        mov  DWORD PTR [eax+0x4],esi
        mov  ebp,0x491c28
        push  ecx
        mov  edi,0x1
        mov  esi,eax
        mov  DWORD PTR [eax+0x20],ebp
        mov  DWORD PTR [eax+0xc],0x4201b0
        call FUN_00449ae0
        test  eax,eax
        jne loc_00420537
        push  0x420000
        call FUN_00449ed0
        mov  edi,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        or   edi,ebx
        mov  DWORD PTR [eax+0x4],edi
        push  edx
        mov  edi,0x1
        mov  esi,eax
        mov  DWORD PTR [eax+0x20],ebp
        call FUN_00449b70
        push  0x4200c0
        call FUN_00449ed0
        or   DWORD PTR [eax+0x4],ebx
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0x28
        mov  esi,eax
        mov  DWORD PTR [eax+0x20],ebp
        call FUN_00449b70
        push  0x4200d0
        call FUN_00449ed0
        or   DWORD PTR [eax+0x4],ebx
        mov  edx,DWORD PTR ds:0x491be4
        push  edx
        mov  edi,0x32
        mov  esi,eax
        mov  DWORD PTR [eax+0x20],ebp
        call FUN_00449b70
        xor  eax,eax
    loc_00420537:
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        ret
    }
}
