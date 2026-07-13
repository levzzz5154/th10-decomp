// 00418E30: FUN_00418e30
// Original size: 176 bytes, actual code: 40 instructions
extern "C" void FUN_00419960(void);
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);

extern "C" __declspec(naked) void FUN_00418e30(void) {
    __asm {
        push  esi
        push  edi
        push  0x4198a0
        call FUN_00449ed0
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x4]
        mov  eax,ds:0x491be4
        and  edx,0xfffffffd
        push  eax
        mov  edi,0x19
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],edx
        call FUN_00449ae0
        push  0x4198b0
        mov  DWORD PTR [ebx+0x8],esi
        call FUN_00449ed0
        mov  ecx,DWORD PTR ds:0x491be4
        mov  esi,eax
        and  DWORD PTR [esi+0x4],0xfffffffd
        push  ecx
        mov  edi,0x2c
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449b70
        mov  DWORD PTR [ebx+0xc],esi
        mov  DWORD PTR [ebx+0x10],0x0
        mov  al,ds:0x491d6a
        test  al,al
        pop  edi
        pop  esi
        je loc_00418EB0
        push  0x0
        push  0x46d6d8
        push  ebx
        call FUN_00419960
        push  0x1
        push  0x46d6c4
        push  ebx
        call FUN_00419960
    loc_00418EB0:
        xor  eax,eax
        ret
    }
}
