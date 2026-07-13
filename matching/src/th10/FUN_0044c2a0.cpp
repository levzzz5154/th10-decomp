// 0044C2A0: FUN_0044c2a0
// Original size: 176 bytes, actual code: 52 instructions
extern "C" void FUN_0044c5d0(void);
extern "C" void FUN_00452ff0(void);

extern "C" __declspec(naked) void FUN_0044c2a0(void) {
    __asm {
        mov  al,BYTE PTR [esi+0x28]
        sub  esp,0x18
        test  al,0x1
        jne loc_0044C2C5
        fld  DWORD PTR [esi]
        fadd  DWORD PTR [esi+0xc]
        fstp  DWORD PTR [esi]
        fld  DWORD PTR [esi+0x10]
        fadd  DWORD PTR [esi+0x4]
        fstp  DWORD PTR [esi+0x4]
        fld  DWORD PTR [esi+0x14]
        fadd  DWORD PTR [esi+0x8]
        fstp  DWORD PTR [esi+0x8]
        jmp loc_0044C30F
    loc_0044C2C5:
        mov  eax,DWORD PTR [esi+0x20]
        mov  ecx,DWORD PTR [esi+0x1c]
        push  eax
        push  ecx
        lea  ecx,[esp+0x14]
        call FUN_0044c5d0
        fld  DWORD PTR [esp+0xc]
        fadd  DWORD PTR [esi+0xc]
        mov  edx,DWORD PTR [esi+0x14]
        mov  DWORD PTR [esp+0x8],edx
        mov  eax,esi
        fstp  DWORD PTR [esp]
        mov  ecx,DWORD PTR [esp]
        fld  DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x14],0x0
        fadd  DWORD PTR [esi+0x10]
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [esp+0x8]
        fstp  DWORD PTR [esp+0x4]
        mov  edx,DWORD PTR [esp+0x4]
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [eax+0x8],ecx
    loc_0044C30F:
        fld  DWORD PTR [esi]
        sub  esp,0x8
        fmul  DWORD PTR ds:0x470b44
        fstp  QWORD PTR [esp]
        call FUN_00452ff0
        fmul  DWORD PTR ds:0x470b00
        fstp  DWORD PTR [esi]
        fld  DWORD PTR [esi+0x4]
        fmul  DWORD PTR ds:0x470b44
        fstp  QWORD PTR [esp]
        call FUN_00452ff0
        fmul  DWORD PTR ds:0x470b00
        add  esp,0x8
        fstp  DWORD PTR [esi+0x4]
        add  esp,0x18
        ret
    }
}
