// 004495E0: FUN_004495e0
// Original size: 80 bytes, actual code: 22 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_004495e0(void) {
    __asm {
        mov  ecx,DWORD PTR [eax]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        call FUN_004491c0
        test  eax,eax
        je loc_00449622
        mov  ecx,DWORD PTR [eax+0x35c]
        mov  edx,0xfffffffd
        and  ecx,edx
        mov  DWORD PTR [eax+0x35c],ecx
        mov  ecx,DWORD PTR [eax+0x18]
        test  ecx,ecx
        jne loc_00449622
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00449622
    loc_00449613:
        mov  ecx,DWORD PTR [eax]
        and  DWORD PTR [ecx+0x35c],edx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00449613
    loc_00449622:
        ret
    }
}
