// 00415B00: FUN_00415b00
// Original size: 688 bytes, actual code: 195 instructions
extern "C" void FUN_00408030(void);
extern "C" void FUN_0040e6a0(void);
extern "C" void FUN_004489d0(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_00415b00(void) {
    __asm {
        sub  esp,0xc
        push  ebp
        mov  ebp,DWORD PTR [esp+0x14]
        push  esi
        push  edi
        mov  edi,DWORD PTR [ebp+0x14]
        mov  eax,0xfffffffe
        and  edi,eax
        mov  DWORD PTR [ebp+0x14],edi
        and  DWORD PTR [ebp+0x28],eax
        mov  edx,DWORD PTR [ebp+0x3c]
        and  edx,eax
        xor  eax,eax
        mov  DWORD PTR [ebp+0x3c],edx
        mov  ecx,0x24
        mov  edi,ebp
        rep stosd
        mov  eax,DWORD PTR [ebp+0x14]
        xor  edi,edi
        test  al,0x1
        mov  esi,0xfff0bdc1
        mov  edx,0x476f78
        jne loc_00415B52
        or   eax,0x1
        mov  DWORD PTR [ebp+0x8],edi
        mov  DWORD PTR [ebp+0x4],esi
        mov  DWORD PTR [ebp+0xc],edi
        mov  DWORD PTR [ebp+0x10],edx
        mov  DWORD PTR [ebp+0x14],eax
    loc_00415B52:
        or   ecx,0xffffffff
        mov  DWORD PTR [ebp+0x8],edi
        mov  DWORD PTR [ebp+0xc],edi
        mov  DWORD PTR [ebp+0x4],ecx
        mov  eax,DWORD PTR [ebp+0x28]
        test  al,0x1
        jne loc_00415B77
        or   eax,0x1
        mov  DWORD PTR [ebp+0x1c],edi
        mov  DWORD PTR [ebp+0x18],esi
        mov  DWORD PTR [ebp+0x20],edi
        mov  DWORD PTR [ebp+0x24],edx
        mov  DWORD PTR [ebp+0x28],eax
    loc_00415B77:
        mov  DWORD PTR [ebp+0x1c],edi
        mov  DWORD PTR [ebp+0x20],edi
        mov  DWORD PTR [ebp+0x18],ecx
        mov  DWORD PTR [ebp+0x58],edi
        mov  eax,DWORD PTR [ebp+0x3c]
        test  al,0x1
        jne loc_00415B9C
        or   eax,0x1
        mov  DWORD PTR [ebp+0x30],edi
        mov  DWORD PTR [ebp+0x2c],esi
        mov  DWORD PTR [ebp+0x34],edi
        mov  DWORD PTR [ebp+0x38],edx
        mov  DWORD PTR [ebp+0x3c],eax
    loc_00415B9C:
        mov  eax,DWORD PTR [esp+0x20]
        mov  esi,DWORD PTR ds:0x491c10
        mov  DWORD PTR [ebp+0x2c],ecx
        mov  ecx,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [ebp+0x30],edi
        mov  DWORD PTR [ebp+0x34],edi
        mov  DWORD PTR [ebp+0x5c],eax
        mov  edx,DWORD PTR [ecx+0x899c]
        push  ebx
        mov  DWORD PTR [esp+0x20],edx
        call FUN_00449950
        mov  ecx,DWORD PTR [esp+0x20]
        mov  ebx,eax
        mov  eax,DWORD PTR [ebx+0x35c]
        push  edi
        or   eax,0x40000000
        push  ebx
        mov  DWORD PTR [ebx+0x20],0xf
        mov  DWORD PTR [ebx+0x35c],eax
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x20]
        mov  edx,esi
        call FUN_004489d0
        mov  eax,DWORD PTR [esp+0x20]
        mov  ecx,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [ebp+0x4c],eax
        mov  edx,DWORD PTR [ecx+0x899c]
        mov  DWORD PTR [esp+0x20],edx
        call FUN_00449950
        mov  ebx,eax
        mov  ecx,DWORD PTR [ebx+0x35c]
        or   ecx,0x40000000
        push  0x1
        mov  DWORD PTR [ebx+0x35c],ecx
        mov  ecx,DWORD PTR [esp+0x24]
        push  ebx
        mov  DWORD PTR [ebx+0x20],0xf
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x20]
        mov  edx,esi
        call FUN_004489d0
        mov  eax,DWORD PTR [esp+0x20]
        mov  DWORD PTR [ebp+0x50],eax
        mov  ecx,DWORD PTR [ebp+0x4c]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,edi
        jne loc_00415C6B
        mov  DWORD PTR [ebp+0x4c],edi
    loc_00415C6B:
        mov  bl,0x10
        mov  BYTE PTR [eax+0x3a0],bl
        mov  edx,DWORD PTR [ebp+0x4c]
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,edi
        jne loc_00415C85
        mov  DWORD PTR [ebp+0x4c],edi
    loc_00415C85:
        mov  BYTE PTR [eax+0x3a1],bl
        mov  eax,DWORD PTR [ebp+0x50]
        push  eax
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,edi
        jne loc_00415C9D
        mov  DWORD PTR [ebp+0x50],edi
    loc_00415C9D:
        mov  BYTE PTR [eax+0x3a0],bl
        mov  ecx,DWORD PTR [ebp+0x50]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,edi
        jne loc_00415CB5
        mov  DWORD PTR [ebp+0x50],edi
    loc_00415CB5:
        mov  esi,DWORD PTR ds:0x4776f0
        mov  BYTE PTR [eax+0x3a1],bl
        mov  DWORD PTR [esp+0x10],0x41000000
        mov  eax,DWORD PTR [esp+0x10]
        lea  edx,[ebp+0x60]
        mov  DWORD PTR [edx],eax
        mov  DWORD PTR [esp+0x14],0x0
        mov  ecx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [edx+0x4],ecx
        mov  DWORD PTR [esp+0x18],0x0
        mov  eax,DWORD PTR [esp+0x18]
        mov  DWORD PTR [edx+0x8],eax
        mov  DWORD PTR [esp+0x10],0x41c00000
        mov  edx,DWORD PTR [esp+0x10]
        lea  ecx,[ebp+0x6c]
        mov  DWORD PTR [ecx],edx
        mov  DWORD PTR [esp+0x14],0x0
        mov  eax,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp+0x18],0x0
        mov  edx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [ebp+0x80],edi
        mov  DWORD PTR [ebp+0x88],0xf8f08f
        mov  DWORD PTR [ebp+0x8c],0x8088ff
        mov  DWORD PTR [ebp+0x84],edi
        mov  DWORD PTR [ecx+0x8],edx
        add  esi,0x60
        mov  ebx,0x7d0
        jmp loc_00415D50
        nop
    loc_00415D50:
        mov  ax,WORD PTR [esi+0x446]
        cmp  ax,di
        je loc_00415D67
        cmp  ax,0x3
        je loc_00415D67
        call FUN_00408030
    loc_00415D67:
        add  esi,0x7f0
        dec  ebx
        jne loc_00415D50
        mov  eax,ds:0x47781c
        mov  ecx,DWORD PTR [eax+0x18]
        cmp  ecx,edi
        pop  ebx
        je loc_00415D95
        nop
    loc_00415D80:
        cmp  DWORD PTR [ecx+0xc],0x1
        mov  esi,DWORD PTR [ecx+0x8]
        je loc_00415D8F
        mov  edx,DWORD PTR [ecx]
        push  edi
        call  DWORD PTR [edx+0x14]
    loc_00415D8F:
        cmp  esi,edi
        mov  ecx,esi
        jne loc_00415D80
    loc_00415D95:
        mov  eax,ds:0x477704
        push  eax
        call FUN_0040e6a0
        pop  edi
        pop  esi
        mov  eax,ebp
        pop  ebp
        add  esp,0xc
        ret  0x8
    }
}
