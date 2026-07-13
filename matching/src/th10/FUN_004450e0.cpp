// 004450E0: FUN_004450e0
// Original size: 224 bytes, actual code: 66 instructions
extern "C" void FUN_004425a0(void);
extern "C" void FUN_00442f50(void);

extern "C" __declspec(naked) void FUN_004450e0(void) {
    __asm {
        push  esi
        push  edi
        mov  esi,ecx
        mov  edi,eax
        mov  eax,DWORD PTR [esi+0x3adac8]
        test  eax,eax
        je loc_004450F5
        call FUN_00442f50
    loc_004450F5:
        cmp  BYTE PTR [esi+0x3ada6a],0x3
        je loc_00445118
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x144
        push  eax
        call  DWORD PTR [ecx+0x164]
        mov  BYTE PTR [esi+0x3ada6a],0x3
    loc_00445118:
        mov  eax,esi
        call FUN_004425a0
        mov  edx,DWORD PTR [edi+0x394]
        mov  eax,DWORD PTR [edx+0x4]
        cmp  DWORD PTR [esi+0x3ada64],eax
        je loc_00445148
        push  eax
        mov  DWORD PTR [esi+0x3ada64],eax
        mov  ecx,DWORD PTR ds:0x491c30
        mov  edx,DWORD PTR [ecx]
        push  0x0
        push  ecx
        call  DWORD PTR [edx+0x104]
    loc_00445148:
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x0
        push  0xe
        push  eax
        call  DWORD PTR [ecx+0xe4]
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
        push  0x6
        push  eax
        call  DWORD PTR [edx+0x14c]
        pop  edi
        xor  eax,eax
        pop  esi
        ret  0x8
    }
}
