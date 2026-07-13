// 00449350: FUN_00449350
// Original size: 144 bytes, actual code: 43 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_00449350(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x4]
        push  eax
        call FUN_004491c0
        test  eax,eax
        je loc_004493BC
        fld  DWORD PTR [esi]
        fadd  DWORD PTR ds:0x470b4c
        fstp  DWORD PTR [eax+0x340]
        fld  DWORD PTR [esi+0x4]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [eax+0x344]
        mov  ecx,DWORD PTR [esi+0x8]
        mov  DWORD PTR [eax+0x348],ecx
        mov  ecx,DWORD PTR [eax+0x18]
        test  ecx,ecx
        jne loc_004493BC
        mov  ecx,DWORD PTR [eax+0x14]
        test  ecx,ecx
        je loc_004493BC
    loc_00449392:
        fld  DWORD PTR [esi]
        mov  eax,DWORD PTR [ecx]
        fadd  DWORD PTR ds:0x470b4c
        add  eax,0x340
        fstp  DWORD PTR [eax]
        fld  DWORD PTR [esi+0x4]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR [esi+0x8]
        mov  DWORD PTR [eax+0x8],edx
        mov  ecx,DWORD PTR [ecx+0x4]
        test  ecx,ecx
        jne loc_00449392
    loc_004493BC:
        ret  0x4
    }
}
