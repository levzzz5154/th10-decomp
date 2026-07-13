// 0041BB00: FUN_0041bb00
// Original size: 896 bytes, actual code: 247 instructions
extern "C" void FUN_00404f30(void);
extern "C" void FUN_0041beb0(void);
extern "C" void FUN_00448db0(void);

extern "C" __declspec(naked) void FUN_0041bb00(void) {
    __asm {
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        push  esi
        xor  ebx,ebx
        cmp  ebp,0x8
        push  edi
        mov  esi,eax
        je loc_0041BCCD
        add  esi,0x14
        xor  eax,eax
        lea  ebx,[ebx+0x0]
    loc_0041BB20:
        cmp  DWORD PTR [esi+0x3dc],ebx
        je loc_0041BB3F
        inc  eax
        add  esi,0x3f0
        cmp  eax,0x96
        jl loc_0041BB20
        pop  edi
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        ret  0x10
    loc_0041BB3F:
        mov  DWORD PTR [esi+0x3dc],0x1
        mov  edx,DWORD PTR [ecx]
        lea  edi,[esi+0x3ac]
        mov  eax,edi
        mov  DWORD PTR [eax],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [eax+0x4],edx
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [eax+0x8],ecx
        fld  DWORD PTR [edi]
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x41
        jp loc_0041BB78
        mov  DWORD PTR [edi],0xc3400000
        jmp loc_0041BB8D
    loc_0041BB78:
        fld  DWORD PTR [edi]
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        test  ah,0x1
        jne loc_0041BB8D
        mov  DWORD PTR [edi],0x43400000
    loc_0041BB8D:
        mov  edx,DWORD PTR [esp+0x20]
        mov  eax,DWORD PTR [esp+0x1c]
        push  edx
        push  eax
        lea  ecx,[esi+0x3b8]
        call FUN_0041beb0
        mov  DWORD PTR [esi+0x3c0],ebx
        mov  eax,DWORD PTR [esi+0x3d8]
        test  al,0x1
        jne loc_0041BBDB
        or   eax,0x1
        mov  DWORD PTR [esi+0x3cc],ebx
        mov  DWORD PTR [esi+0x3c8],0xfff0bdc1
        mov  DWORD PTR [esi+0x3d0],ebx
        mov  DWORD PTR [esi+0x3d4],0x476f78
        mov  DWORD PTR [esi+0x3d8],eax
    loc_0041BBDB:
        mov  DWORD PTR [esi+0x3cc],ebx
        mov  DWORD PTR [esi+0x3d0],ebx
        mov  DWORD PTR [esi+0x3c8],0xffffffff
        mov  DWORD PTR [esi+0x3c4],ebx
        cmp  WORD PTR ds:0x474c48,0x64
        jl loc_0041BC23
        lea  eax,[ebp-0x1]
        cmp  eax,0xa
        ja loc_0041BC23
        movzx ecx,BYTE PTR [eax+0x41be28]
        jmp  DWORD PTR [ecx*4+0x41be1c]
        mov  ebp,0x5
        jmp loc_0041BC23
        mov  ebp,0x9
    loc_0041BC23:
        cmp  DWORD PTR [esi+0x3e0],0x3
        jne loc_0041BC47
        mov  eax,ds:0x4776f0
        mov  ecx,DWORD PTR [eax+0x3e0b50]
        push  0x189
        lea  edx,[esp+0x24]
        push  edx
        push  ecx
        call FUN_00448db0
    loc_0041BC47:
        cmp  ebp,0xa
        mov  DWORD PTR [esi+0x3e0],ebp
        mov  DWORD PTR [esi+0x3e4],ebp
        jne loc_0041BC8C
        mov  edx,DWORD PTR ds:0x4776f0
        mov  DWORD PTR [esi+0x3e4],0x1
        mov  eax,DWORD PTR [edx+0x3e0b50]
        push  eax
        mov  eax,0x177
        call FUN_00404f30
        mov  eax,DWORD PTR [esp+0x18]
        pop  edi
        mov  DWORD PTR [esi+0x2fc],eax
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        ret  0x10
    loc_0041BC8C:
        cmp  ebp,0xb
        mov  ecx,DWORD PTR ds:0x4776f0
        jne loc_0041BCA8
        mov  DWORD PTR [esi+0x3e4],0x4
        mov  eax,0x17a
        jmp loc_0041BCAE
    loc_0041BCA8:
        lea  eax,[ebp+0x176]
    loc_0041BCAE:
        mov  edx,DWORD PTR [ecx+0x3e0b50]
        push  edx
        call FUN_00404f30
        mov  eax,DWORD PTR [esp+0x18]
        pop  edi
        mov  DWORD PTR [esi+0x2fc],eax
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        ret  0x10
    loc_0041BCCD:
        mov  eax,DWORD PTR [esi+0x21ceb8]
        mov  edi,DWORD PTR [esi+0x21cebc]
        mov  edx,eax
        imul  edx,edx,0x3f0
        inc  edi
        lea  edx,[edx+esi*1+0x24eb4]
        mov  DWORD PTR [esi+0x21cebc],edi
        cmp  DWORD PTR [edx+0x3dc],ebx
        jne loc_0041BDF3
        cmp  edi,0x400
        jl loc_0041BD14
        and  eax,0x8000001f
        jns loc_0041BD0F
        dec  eax
        or   eax,0xffffffe0
        inc  eax
    loc_0041BD0F:
        add  eax,0x10
        jmp loc_0041BD52
    loc_0041BD14:
        cmp  edi,0x200
        jl loc_0041BD2D
        and  eax,0x8000000f
        jns loc_0041BD28
        dec  eax
        or   eax,0xfffffff0
        inc  eax
    loc_0041BD28:
        add  eax,0x8
        jmp loc_0041BD52
    loc_0041BD2D:
        cmp  edi,0x100
        jl loc_0041BD46
        and  eax,0x80000007
        jns loc_0041BD41
        dec  eax
        or   eax,0xfffffff8
        inc  eax
    loc_0041BD41:
        add  eax,0x4
        jmp loc_0041BD52
    loc_0041BD46:
        and  eax,0x80000003
        jns loc_0041BD52
        dec  eax
        or   eax,0xfffffffc
        inc  eax
    loc_0041BD52:
        mov  DWORD PTR [edx+0x3ec],eax
        mov  eax,0x8
        mov  DWORD PTR [edx+0x3e0],eax
        mov  DWORD PTR [edx+0x3e4],eax
        mov  DWORD PTR [edx+0x3dc],0x5
        mov  edi,DWORD PTR [ecx]
        lea  eax,[edx+0x3ac]
        mov  DWORD PTR [eax],edi
        mov  edi,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [eax+0x4],edi
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [eax+0x8],ecx
        mov  eax,DWORD PTR [esp+0x20]
        mov  ecx,DWORD PTR [esp+0x1c]
        push  eax
        push  ecx
        lea  ecx,[edx+0x3b8]
        call FUN_0041beb0
        mov  DWORD PTR [edx+0x3c0],ebx
        mov  eax,DWORD PTR [edx+0x3d8]
        test  al,0x1
        jne loc_0041BDD7
        or   eax,0x1
        mov  DWORD PTR [edx+0x3cc],ebx
        mov  DWORD PTR [edx+0x3c8],0xfff0bdc1
        mov  DWORD PTR [edx+0x3d0],ebx
        mov  DWORD PTR [edx+0x3d4],0x476f78
        mov  DWORD PTR [edx+0x3d8],eax
    loc_0041BDD7:
        mov  DWORD PTR [edx+0x3cc],ebx
        mov  DWORD PTR [edx+0x3d0],ebx
        mov  DWORD PTR [edx+0x3c8],0xffffffff
        mov  DWORD PTR [edx+0x3c4],ebx
    loc_0041BDF3:
        mov  edx,DWORD PTR [esi+0x21ceb8]
        inc  edx
        and  edx,0x800007ff
        jns loc_0041BE0A
        dec  edx
        or   edx,0xfffff800
        inc  edx
    loc_0041BE0A:
        pop  edi
        mov  DWORD PTR [esi+0x21ceb8],edx
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        ret  0x10
        nop
        push  ds
        mov  esp,0xbc170041
        inc  ecx
        add  BYTE PTR [ebx],ah
        mov  esp,0x2000041
        add  al,BYTE PTR [eax]
        add  al,BYTE PTR [edx]
        add  al,BYTE PTR [edx]
        add  al,BYTE PTR [ecx]
        add  esp,ecx
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        mov  ecx,DWORD PTR ds:0x4776f0
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x3e0]
        mov  DWORD PTR [esi+0x3dc],0x2
        mov  edx,DWORD PTR [ecx+0x3e0b50]
        add  eax,0x176
        push  edx
        call FUN_00404f30
        xor  eax,eax
        pop  esi
        ret
    }
}
