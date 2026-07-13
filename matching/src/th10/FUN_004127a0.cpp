// 004127A0: FUN_004127a0
// Original size: 608 bytes, actual code: 147 instructions

extern "C" __declspec(naked) void FUN_004127a0(void) {
    __asm {
        push  ebx
        push  ebp
        xor  ebp,ebp
        push  esi
        xor  eax,eax
        lea  edx,[ecx+0x2494]
        nop
    loc_004127B0:
        cmp  DWORD PTR [edx],ebp
        jge loc_004127E3
        inc  eax
        add  edx,0x10
        cmp  eax,0x8
        jb loc_004127B0
    loc_004127BD:
        xor  ebx,ebx
        lea  eax,[ecx+0x2498]
        push  edi
    loc_004127C6:
        cmp  DWORD PTR [eax-0x4],ebp
        jl loc_004127D3
        cmp  DWORD PTR [eax],ebp
        jg loc_00412879
    loc_004127D3:
        inc  ebx
        add  eax,0x10
        cmp  ebx,0x8
        jb loc_004127C6
    loc_004127DC:
        pop  edi
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        ret
    loc_004127E3:
        mov  esi,DWORD PTR [ecx+0x23fc]
        shl  eax,0x4
        mov  ebx,DWORD PTR [eax+ecx*1+0x2494]
        lea  edx,[eax+ecx*1]
        mov  eax,esi
        sub  eax,ebx
        mov  DWORD PTR [ecx+0x2404],eax
        mov  eax,DWORD PTR [edx+0x2494]
        cmp  esi,eax
        jg loc_004127BD
        or   esi,0xffffffff
        mov  DWORD PTR [ecx+0x23fc],eax
        mov  DWORD PTR [edx+0x2494],esi
        mov  eax,DWORD PTR [ecx+0x1168]
        test  al,0x1
        jne loc_0041284C
        or   eax,0x1
        mov  DWORD PTR [ecx+0x115c],ebp
        mov  DWORD PTR [ecx+0x1158],0xfff0bdc1
        mov  DWORD PTR [ecx+0x1160],ebp
        mov  DWORD PTR [ecx+0x1164],0x476f78
        mov  DWORD PTR [ecx+0x1168],eax
    loc_0041284C:
        mov  DWORD PTR [ecx+0x115c],ebp
        mov  DWORD PTR [ecx+0x1160],ebp
        mov  DWORD PTR [ecx+0x1158],esi
        mov  eax,DWORD PTR [ecx+0x2480]
        pop  esi
        and  eax,0xfffeffff
        pop  ebp
        mov  DWORD PTR [ecx+0x2480],eax
        mov  eax,DWORD PTR [edx+0x249c]
        pop  ebx
        ret
    loc_00412879:
        mov  eax,DWORD PTR [ecx+0x115c]
        mov  edx,ebx
        shl  edx,0x4
        mov  esi,DWORD PTR [edx+ecx*1+0x2498]
        lea  edi,[edx+ecx*1]
        sub  esi,eax
        add  esi,0x3b
        mov  eax,0x88888889
        imul  esi
        add  edx,esi
        sar  edx,0x5
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        cmp  eax,0x63
        jle loc_004128B0
        mov  eax,0x63
    loc_004128B0:
        mov  edx,DWORD PTR ds:0x47770c
        mov  DWORD PTR [edx+0x9ec0],eax
        mov  eax,DWORD PTR [ecx+0x115c]
        cmp  eax,DWORD PTR [edi+0x2498]
        jl loc_004127DC
        mov  edx,DWORD PTR [edi+0x2494]
        or   esi,0xffffffff
        mov  DWORD PTR [ecx+0x23fc],edx
        mov  DWORD PTR [edi+0x2494],esi
        mov  eax,DWORD PTR [ecx+0x1168]
        test  al,0x1
        jne loc_00412916
        or   eax,0x1
        mov  DWORD PTR [ecx+0x115c],ebp
        mov  DWORD PTR [ecx+0x1158],0xfff0bdc1
        mov  DWORD PTR [ecx+0x1160],ebp
        mov  DWORD PTR [ecx+0x1164],0x476f78
        mov  DWORD PTR [ecx+0x1168],eax
    loc_00412916:
        mov  DWORD PTR [ecx+0x115c],ebp
        mov  DWORD PTR [ecx+0x1160],ebp
        mov  DWORD PTR [ecx+0x1158],esi
        or   DWORD PTR [ecx+0x2480],0x10000
        mov  eax,ds:0x474c4c
        sub  eax,0xbb8
        cmp  eax,0x1388
        mov  ds:0x474c4c,eax
        jge loc_00412952
        mov  DWORD PTR ds:0x474c4c,0x1388
    loc_00412952:
        mov  eax,ds:0x4776f4
        mov  edx,DWORD PTR [eax+0x378c]
        test  dl,0x8
        jne loc_004129E0
        cmp  DWORD PTR [eax+0x3738],0x3c
        jl loc_004129E0
        mov  DWORD PTR [eax+0x3790],ebp
        mov  esi,0xfffffffd
        and  edx,esi
        mov  DWORD PTR [eax+0x378c],edx
        mov  edx,DWORD PTR [eax+0xad4]
        mov  ebp,DWORD PTR [eax+0xe80]
        mov  edi,DWORD PTR [eax+0x15d8]
        and  edx,esi
        mov  DWORD PTR [eax+0xad4],edx
        mov  edx,DWORD PTR [eax+0x1984]
        and  ebp,esi
        and  edi,esi
        and  edx,esi
        mov  DWORD PTR [eax+0xe80],ebp
        mov  ebp,DWORD PTR [eax+0x1d30]
        mov  DWORD PTR [eax+0x15d8],edi
        mov  edi,DWORD PTR [eax+0x20dc]
        mov  DWORD PTR [eax+0x1984],edx
        mov  edx,DWORD PTR [eax+0x2488]
        and  ebp,esi
        and  edi,esi
        and  edx,esi
        mov  DWORD PTR [eax+0x1d30],ebp
        mov  DWORD PTR [eax+0x20dc],edi
        mov  DWORD PTR [eax+0x2488],edx
    loc_004129E0:
        pop  edi
        add  ebx,0x24a
        pop  esi
        shl  ebx,0x4
        mov  eax,DWORD PTR [ebx+ecx*1]
        pop  ebp
        pop  ebx
        ret
    }
}
