// 00421070: FUN_00421070
// Original size: 656 bytes, actual code: 82 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_00421070(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        mov  eax,DWORD PTR [ebp+0x6fc]
        push  esi
        push  edi
        mov  esi,0x1
        xor  edi,edi
        cmp  eax,esi
        jne loc_00421168
        mov  eax,ds:0x477824
        push  ebx
        mov  ebx,DWORD PTR ds:0x491c10
        push  eax
        mov  edx,ebx
        call FUN_004491c0
        cmp  eax,edi
        je loc_004210D0
        cmp  DWORD PTR [eax+0x18],edi
        mov  WORD PTR [eax+0x304],si
        jne loc_004210D0
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,edi
        je loc_004210D0
        jmp loc_004210C0
        nop
    loc_004210C0:
        mov  ecx,DWORD PTR [eax]
        mov  WORD PTR [ecx+0x304],si
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_004210C0
    loc_004210D0:
        mov  edx,DWORD PTR ds:0x477828
        push  edx
        mov  edx,ebx
        call FUN_004491c0
        cmp  eax,edi
        je loc_00421110
        cmp  DWORD PTR [eax+0x18],edi
        mov  WORD PTR [eax+0x304],si
        jne loc_00421110
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,edi
        je loc_00421110
        jmp loc_00421100
        nop
        mov  edi,edi
    loc_00421100:
        mov  ecx,DWORD PTR [eax]
        mov  WORD PTR [ecx+0x304],si
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_00421100
    loc_00421110:
        mov  edx,DWORD PTR ds:0x47782c
        push  edx
        mov  edx,ebx
        call FUN_004491c0
        cmp  eax,edi
        pop  ebx
        je loc_00421150
        cmp  DWORD PTR [eax+0x18],edi
        mov  WORD PTR [eax+0x304],si
        jne loc_00421150
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,edi
        je loc_00421150
        jmp loc_00421140
        nop
        nop
    loc_00421140:
        mov  ecx,DWORD PTR [eax]
        mov  WORD PTR [ecx+0x304],si
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_00421140
    loc_00421150:
        mov  DWORD PTR ds:0x477824,edi
        mov  DWORD PTR ds:0x477828,edi
        mov  DWORD PTR ds:0x47782c,edi
        mov  DWORD PTR [ebp+0x6fc],edi
    loc_00421168:
        cmp  DWORD PTR ds:0x491bec,edi
        je loc_00421176
        mov  DWORD PTR ds:0x491bec,edi
    loc_00421176:
        pop  edi
        pop  esi
        pop  ebp
        ret  0x4
    }
}
