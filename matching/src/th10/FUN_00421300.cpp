// 00421300: FUN_00421300
// Original size: 384 bytes, actual code: 86 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_00421300(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        mov  eax,DWORD PTR [ebp+0x6fc]
        push  edi
        xor  edi,edi
        cmp  eax,0x1
        jne loc_004213FA
        mov  eax,ds:0x477824
        push  ebx
        mov  ebx,DWORD PTR ds:0x491c10
        push  esi
        push  eax
        mov  edx,ebx
        call FUN_004491c0
        cmp  eax,edi
        mov  esi,0x2
        je loc_00421360
        cmp  DWORD PTR [eax+0x18],edi
        mov  WORD PTR [eax+0x304],si
        jne loc_00421360
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,edi
        je loc_00421360
        jmp loc_00421350
        lea  ebx,[ebx+0x0]
    loc_00421350:
        mov  ecx,DWORD PTR [eax]
        mov  WORD PTR [ecx+0x304],si
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_00421350
    loc_00421360:
        mov  edx,DWORD PTR ds:0x477828
        push  edx
        mov  edx,ebx
        call FUN_004491c0
        cmp  eax,edi
        je loc_004213A0
        cmp  DWORD PTR [eax+0x18],edi
        mov  WORD PTR [eax+0x304],si
        jne loc_004213A0
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,edi
        je loc_004213A0
        jmp loc_00421390
        nop
        mov  edi,edi
    loc_00421390:
        mov  ecx,DWORD PTR [eax]
        mov  WORD PTR [ecx+0x304],si
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_00421390
    loc_004213A0:
        mov  edx,DWORD PTR ds:0x47782c
        push  edx
        mov  edx,ebx
        call FUN_004491c0
        cmp  eax,edi
        je loc_004213E0
        cmp  DWORD PTR [eax+0x18],edi
        mov  WORD PTR [eax+0x304],si
        jne loc_004213E0
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,edi
        je loc_004213E0
        jmp loc_004213D0
        nop
        mov  edi,edi
    loc_004213D0:
        mov  ecx,DWORD PTR [eax]
        mov  WORD PTR [ecx+0x304],si
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_004213D0
    loc_004213E0:
        mov  DWORD PTR ds:0x477824,edi
        mov  DWORD PTR ds:0x477828,edi
        mov  DWORD PTR ds:0x47782c,edi
        mov  DWORD PTR [ebp+0x6fc],esi
        pop  esi
        pop  ebx
    loc_004213FA:
        cmp  DWORD PTR ds:0x491bec,edi
        je loc_00421408
        mov  DWORD PTR ds:0x491bec,edi
    loc_00421408:
        pop  edi
        pop  ebp
        ret  0x4
    }
}
