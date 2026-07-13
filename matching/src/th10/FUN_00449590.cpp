// 00449590: FUN_00449590
// Original size: 80 bytes, actual code: 22 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_00449590(void) {
    __asm {
        mov  ecx,DWORD PTR [eax]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        call FUN_004491c0
        test  eax,eax
        je loc_004495D2
        mov  ecx,DWORD PTR [eax+0x35c]
        mov  edx,0x2
        or   ecx,edx
        mov  DWORD PTR [eax+0x35c],ecx
        mov  ecx,DWORD PTR [eax+0x18]
        test  ecx,ecx
        jne loc_004495D2
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_004495D2
    loc_004495C3:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],edx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004495C3
    loc_004495D2:
        ret
    }
}
