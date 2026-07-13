// 004492A0: FUN_004492a0
// Original size: 80 bytes, actual code: 22 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_004492a0(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x4]
        push  eax
        call FUN_004491c0
        test  eax,eax
        je loc_004492DF
        mov  ecx,DWORD PTR [eax+0x35c]
        mov  edx,0x4000000
        or   ecx,edx
        mov  DWORD PTR [eax+0x35c],ecx
        mov  ecx,DWORD PTR [eax+0x18]
        test  ecx,ecx
        jne loc_004492DF
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_004492DF
        nop
    loc_004492D0:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],edx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004492D0
    loc_004492DF:
        ret  0x4
    }
}
