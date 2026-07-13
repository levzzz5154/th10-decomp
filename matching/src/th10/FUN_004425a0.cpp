// 004425A0: FUN_004425a0
// Original size: 208 bytes, actual code: 66 instructions
extern "C" void FUN_00442f50(void);

extern "C" __declspec(naked) void FUN_004425a0(void) {
    __asm {
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [edi+0x35c]
        mov  cl,BYTE PTR [esi+0x3ada68]
        shr  eax,0x4
        and  eax,0x3
        cmp  cl,al
        je loc_00442600
        call FUN_00442f50
        mov  eax,DWORD PTR [edi+0x35c]
        shr  eax,0x4
        and  al,0x3
        mov  BYTE PTR [esi+0x3ada68],al
        movzx eax,al
        sub  eax,0x0
        je loc_004425EE
        dec  eax
        jne loc_00442600
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x2
        push  0x14
        push  eax
        call  DWORD PTR [ecx+0xe4]
        jmp loc_00442600
    loc_004425EE:
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x6
        push  0x14
        push  eax
        call  DWORD PTR [edx+0xe4]
    loc_00442600:
        mov  eax,DWORD PTR [edi+0x35c]
        mov  cl,BYTE PTR [esi+0x3ada6e]
        shr  eax,0x1f
        cmp  cl,al
        je loc_00442664
        call FUN_00442f50
        mov  eax,DWORD PTR [edi+0x35c]
        shr  eax,0x1f
        and  al,0x1
        mov  BYTE PTR [esi+0x3ada6e],al
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        jne loc_00442643
        push  0x2
        push  0x5
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x114]
        push  0x2
        jmp loc_00442652
    loc_00442643:
        push  0x1
        push  0x5
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x114]
        push  0x1
    loc_00442652:
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x6
        push  0x0
        push  eax
        call  DWORD PTR [edx+0x114]
    loc_00442664:
        inc  DWORD PTR [esi+0x54]
        pop  esi
        ret
    }
}
