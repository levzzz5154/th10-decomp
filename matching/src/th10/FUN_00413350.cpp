// 00413350: FUN_00413350
// Original size: 256 bytes, actual code: 56 instructions
extern "C" void FUN_00449b70(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_00413350(void) {
    __asm {
        push  ebx
        push  ebp
        push  esi
        push  edi
        push  0x8c
        call operator_new
        mov  edx,eax
        xor  ebp,ebp
        add  esp,0x4
        cmp  edx,ebp
        je loc_00413381
        xor  eax,eax
        mov  ecx,0x23
        mov  edi,edx
        rep stosd
        or   DWORD PTR [edx],0x2
        mov  DWORD PTR ds:0x477708,edx
        mov  ebx,edx
        jmp loc_00413383
    loc_00413381:
        xor  ebx,ebx
    loc_00413383:
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebp
        je loc_004133B2
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebp
        mov  DWORD PTR [eax+0xc],ebp
        mov  DWORD PTR [eax+0x10],ebp
        mov  DWORD PTR [eax],ebp
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebp
        mov  DWORD PTR [eax+0x1c],ebp
        mov  esi,eax
        jmp loc_004133B4
    loc_004133B2:
        xor  esi,esi
    loc_004133B4:
        mov  edx,DWORD PTR [esi+0x4]
        mov  eax,ds:0x491be4
        or   edx,0x3
        push  eax
        mov  edi,0x2f
        mov  DWORD PTR [esi+0x8],0x413690
        mov  DWORD PTR [esi+0xc],ebp
        mov  DWORD PTR [esi+0x10],ebp
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],edx
        call FUN_00449b70
        pop  edi
        mov  DWORD PTR [ebx+0xc],esi
        pop  esi
        pop  ebp
        mov  eax,ebx
        pop  ebx
        ret
    }
}
