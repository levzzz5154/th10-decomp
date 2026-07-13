// 0042A450: FUN_0042a450
// Original size: 592 bytes, actual code: 157 instructions
extern "C" void FUN_00424d90(void);
extern "C" void FUN_00426f70(void);
extern "C" void FUN_00428e10(void);
extern "C" void FUN_0042aa50(void);
extern "C" void FUN_0042ab20(void);

extern "C" __declspec(naked) void FUN_0042a450(void) {
    __asm {
        mov  eax,DWORD PTR [ebx+0x8]
        test  eax,eax
        mov  ecx,0x2
        je loc_0042A45F
        or   DWORD PTR [eax+0x4],ecx
    loc_0042A45F:
        mov  eax,DWORD PTR [ebx+0x1cc]
        test  eax,eax
        je loc_0042A46C
        or   DWORD PTR [eax+0x4],ecx
    loc_0042A46C:
        mov  eax,DWORD PTR [ebx+0xc]
        test  eax,eax
        je loc_0042A476
        or   DWORD PTR [eax+0x4],ecx
    loc_0042A476:
        mov  eax,DWORD PTR [ebx+0x10]
        test  eax,eax
        push  ebp
        push  esi
        push  edi
        jne loc_0042A5A3
        mov  eax,ds:0x474c7c
        mov  ebp,DWORD PTR [ebx+eax*4+0x1c]
        mov  ecx,ebx
        call FUN_0042ab20
        mov  esi,DWORD PTR ds:0x474c7c
        push  ebx
        call FUN_0042aa50
        mov  DWORD PTR [ebx+0x9c],eax
        mov  eax,ds:0x491fc4
        test  eax,eax
        jne loc_0042A4F0
        mov  eax,ds:0x474c44
        mov  DWORD PTR [ebp+0xc],eax
        mov  cx,WORD PTR ds:0x474c48
        mov  WORD PTR [ebp+0x10],cx
        mov  edx,DWORD PTR ds:0x474c4c
        mov  DWORD PTR [ebp+0x14],edx
        mov  eax,ds:0x474c58
        mov  DWORD PTR [ebp+0x18],eax
        mov  ecx,DWORD PTR ds:0x474c70
        mov  DWORD PTR [ebp+0x1c],ecx
        mov  edx,DWORD PTR ds:0x474c98
        mov  DWORD PTR [ebp+0x20],edx
        mov  eax,ds:0x474c90
        mov  DWORD PTR [ebp+0x1b4],eax
    loc_0042A4F0:
        mov  edx,DWORD PTR ds:0x477834
        mov  ecx,DWORD PTR [edx+0x3cc]
        mov  DWORD PTR [ebp+0x24],ecx
        mov  eax,DWORD PTR [edx+0x3d0]
        mov  DWORD PTR [ebp+0x28],eax
        mov  ecx,DWORD PTR ds:0x474c7c
        mov  edi,DWORD PTR [ebx+ecx*4+0x1c]
        lea  esi,[edx+0x436c]
        add  edi,0x2c
        mov  ecx,0x42
        rep movsd
        lea  ecx,[ebp+0x158]
        lea  eax,[edx+0x32e0]
        mov  esi,0x4
    loc_0042A533:
        mov  edi,DWORD PTR [eax-0xc]
        mov  DWORD PTR [ecx-0x24],edi
        mov  edi,DWORD PTR [eax-0x8]
        mov  DWORD PTR [ecx-0x20],edi
        mov  edi,DWORD PTR [eax-0x4]
        mov  DWORD PTR [ecx-0x4],edi
        mov  edi,DWORD PTR [eax]
        mov  DWORD PTR [ecx],edi
        mov  edi,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x1c],edi
        mov  edi,DWORD PTR [eax+0x8]
        mov  DWORD PTR [ecx+0x20],edi
        mov  edi,DWORD PTR [eax+0xc]
        mov  DWORD PTR [ecx+0x3c],edi
        mov  edi,DWORD PTR [eax+0x10]
        mov  DWORD PTR [ecx+0x40],edi
        add  eax,0x98
        add  ecx,0x8
        dec  esi
        jne loc_0042A533
        mov  eax,ds:0x474c9c
        mov  DWORD PTR [ebp+0x1b8],eax
        mov  ecx,DWORD PTR ds:0x474c7c
        mov  DWORD PTR [ebx+0x1d0],ecx
        mov  edx,DWORD PTR [edx+0x4474]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ebx+eax*4+0x1c]
        mov  DWORD PTR [ecx+0x1bc],edx
    loc_0042A595:
        pop  edi
        pop  esi
        mov  DWORD PTR [ebx+0x1c8],0x0
        pop  ebp
        ret
    loc_0042A5A3:
        cmp  eax,0x1
        jne loc_0042A595
        mov  eax,ds:0x474c7c
        mov  edi,DWORD PTR ds:0x477834
        lea  ecx,[eax+eax*8]
        mov  ebp,DWORD PTR [ebx+ecx*4+0xb0]
        mov  DWORD PTR [ebx+0x1d0],eax
        lea  ecx,[ebp+0x24]
        mov  eax,edi
        call FUN_00428e10
        mov  eax,ds:0x477834
        add  edi,0x436c
        lea  esi,[ebp+0x2c]
        mov  ecx,0x42
        rep movsd
        mov  edx,DWORD PTR [ebp+0x1bc]
        push  eax
        mov  DWORD PTR [eax+0x4474],edx
        call FUN_00426f70
        mov  esi,DWORD PTR ds:0x477834
        lea  eax,[ebp+0x178]
        lea  ecx,[esi+0x32e0]
        mov  edi,0x4
        jmp loc_0042A610
        nop
    loc_0042A610:
        mov  edx,DWORD PTR [eax-0x44]
        mov  DWORD PTR [ecx-0xc],edx
        mov  edx,DWORD PTR [eax-0x40]
        mov  DWORD PTR [ecx-0x8],edx
        mov  edx,DWORD PTR [eax-0x24]
        mov  DWORD PTR [ecx-0x4],edx
        mov  edx,DWORD PTR [eax-0x20]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [eax-0x4]
        mov  DWORD PTR [ecx+0x4],edx
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ecx+0x8],edx
        mov  edx,DWORD PTR [eax+0x1c]
        mov  DWORD PTR [ecx+0xc],edx
        mov  edx,DWORD PTR [eax+0x20]
        mov  DWORD PTR [ecx+0x10],edx
        mov  edx,DWORD PTR ds:0x474c68
        mov  ebp,DWORD PTR ds:0x474c6c
        lea  ebp,[ebp+edx*2+0x0]
        add  ebp,edx
        cmp  ebp,0x5
        jne loc_0042A661
        mov  edx,DWORD PTR [eax-0x44]
        mov  DWORD PTR [ecx+0xc],edx
        mov  edx,DWORD PTR [eax-0x40]
        mov  DWORD PTR [ecx+0x10],edx
    loc_0042A661:
        add  eax,0x8
        add  ecx,0x98
        dec  edi
        jne loc_0042A610
        xor  edi,edi
        mov  DWORD PTR [esi+0x332c],edi
        mov  DWORD PTR [esi+0x33c4],edi
        mov  DWORD PTR [esi+0x345c],edi
        mov  DWORD PTR [esi+0x34f4],edi
        call FUN_00424d90
        mov  DWORD PTR [ebx+0x1c8],edi
        pop  edi
        pop  esi
        pop  ebp
        ret
    }
}
