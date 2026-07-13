// 00444CE0: FUN_00444ce0
// Original size: 1024 bytes, actual code: 120 instructions
extern "C" void FUN_004425a0(void);
extern "C" void FUN_00442f50(void);
extern "C" void FUN_00442fe0(void);

extern "C" __declspec(naked) void FUN_00444ce0(void) {
    __asm {
        push  esi
        push  edi
        mov  edi,eax
        mov  eax,DWORD PTR [edi+0x35c]
        test  al,0x1
        mov  esi,ecx
        je loc_00444CF4
        test  al,0x2
        jne loc_00444CFC
    loc_00444CF4:
        pop  edi
        or   eax,0xffffffff
        pop  esi
        ret  0x8
    loc_00444CFC:
        mov  al,BYTE PTR [edi+0x2ff]
        test  al,al
        jne loc_00444D10
        pop  edi
        mov  eax,0xffffffff
        pop  esi
        ret  0x8
    loc_00444D10:
        mov  eax,DWORD PTR [esi+0x3adac8]
        test  eax,eax
        je loc_00444D1F
        call FUN_00442f50
    loc_00444D1F:
        mov  eax,DWORD PTR [edi+0x394]
        mov  eax,DWORD PTR [eax+0x4]
        cmp  DWORD PTR [esi+0x3ada64],eax
        je loc_00444D48
        push  eax
        mov  DWORD PTR [esi+0x3ada64],eax
        mov  ecx,DWORD PTR ds:0x491c30
        mov  edx,DWORD PTR [ecx]
        push  0x0
        push  ecx
        call  DWORD PTR [edx+0x104]
    loc_00444D48:
        cmp  BYTE PTR [esi+0x3ada6a],0x3
        je loc_00444D6B
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x144
        push  eax
        call  DWORD PTR [ecx+0x164]
        mov  BYTE PTR [esi+0x3ada6a],0x3
    loc_00444D6B:
        mov  eax,esi
        call FUN_004425a0
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x0
        push  0x6
        push  0x0
        push  eax
        call  DWORD PTR [edx+0x10c]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x0
        push  0x3
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x10c]
        mov  ecx,DWORD PTR [esp+0xc]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x1c
        push  ecx
        mov  ecx,DWORD PTR [esp+0x18]
        add  ecx,0xfffffffe
        push  ecx
        push  0x5
        push  eax
        call  DWORD PTR [edx+0x14c]
        pop  edi
        xor  eax,eax
        pop  esi
        ret  0x8
        push  esi
        push  edi
        mov  edi,eax
        mov  eax,DWORD PTR [edi+0x35c]
        test  al,0x1
        mov  esi,ecx
        je loc_00444DD4
        test  al,0x2
        jne loc_00444DDC
    loc_00444DD4:
        pop  edi
        or   eax,0xffffffff
        pop  esi
        ret  0x4
    loc_00444DDC:
        mov  al,BYTE PTR [edi+0x2ff]
        test  al,al
        jne loc_00444DF0
        pop  edi
        mov  eax,0xffffffff
        pop  esi
        ret  0x4
    loc_00444DF0:
        mov  eax,DWORD PTR [edi+0x394]
        mov  eax,DWORD PTR [eax+0x4]
        cmp  DWORD PTR [esi+0x3ada64],eax
        je loc_00444E23
        mov  DWORD PTR [esi+0x3ada64],eax
        call FUN_00442f50
        mov  edx,DWORD PTR [esi+0x3ada64]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  edx
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x104]
    loc_00444E23:
        cmp  BYTE PTR [esi+0x3ada6a],0x1
        je loc_00444E38
        call FUN_00442f50
        mov  BYTE PTR [esi+0x3ada6a],0x1
    loc_00444E38:
        mov  eax,esi
        call FUN_004425a0
        mov  edx,DWORD PTR [esp+0xc]
        mov  eax,esi
        call FUN_00442fe0
        pop  edi
        xor  eax,eax
        pop  esi
        ret  0x4
    }
}
