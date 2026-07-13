// 00413980: FUN_00413980
// Original size: 160 bytes, actual code: 43 instructions
extern "C" void FUN_00413a20(void);
extern "C" void FUN_00447280(void);
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);
extern "C" void FUN_0044b810(void);

extern "C" __declspec(naked) void FUN_00413980(void) {
    __asm {
        mov  edx,DWORD PTR ds:0x491c10
        push  0x46d254
        mov  ecx,0x6
        call FUN_00447280
        test  eax,eax
        mov  DWORD PTR [ebx+0x9ec8],eax
        jne loc_004139B5
        push  0x46cb68
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_004139B1:
        or   eax,0xffffffff
        ret
    loc_004139B5:
        push  ebx
        call FUN_00413a20
        test  eax,eax
        jne loc_004139B1
        push  esi
        push  edi
        push  0x415ae0
        call FUN_00449ed0
        mov  esi,eax
        and  DWORD PTR [esi+0x4],0xfffffffd
        mov  eax,ds:0x491be4
        push  eax
        mov  edi,0x18
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449ae0
        push  0x415af0
        mov  DWORD PTR [ebx+0x8],esi
        call FUN_00449ed0
        mov  esi,eax
        and  DWORD PTR [esi+0x4],0xfffffffd
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0x2b
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449b70
        pop  edi
        mov  DWORD PTR [ebx+0xc],esi
        xor  eax,eax
        pop  esi
        ret
    }
}
