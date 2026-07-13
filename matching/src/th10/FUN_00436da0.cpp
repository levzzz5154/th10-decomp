// 00436DA0: FUN_00436da0
// Original size: 960 bytes, actual code: 316 instructions

extern "C" __declspec(naked) void FUN_00436da0(void) {
    __asm {
        sub  esp,0x14
        push  ebx
        push  ebp
        push  esi
        mov  esi,DWORD PTR [esp+0x24]
        mov  eax,DWORD PTR [esi+0x100]
        cmp  eax,0x15
        push  edi
        je loc_00436FA3
        cmp  eax,0x1a
        jne loc_00437146
        mov  eax,DWORD PTR [esp+0x2c]
        test  eax,eax
        mov  edi,DWORD PTR [esi+0x120]
        mov  DWORD PTR [esp+0x10],0x0
        jbe loc_00437146
        nop
    loc_00436DE0:
        mov  edx,DWORD PTR [esi+0x104]
        xor  ebp,ebp
        test  edx,edx
        mov  DWORD PTR [esp+0x14],ebp
        jbe loc_00436F82
    loc_00436DF4:
        test  BYTE PTR [edi+0x1],0xf0
        jne loc_00436F6C
        xor  ecx,ecx
        xor  ebx,ebx
        xor  esi,esi
        test  ebp,ebp
        mov  DWORD PTR [esp+0x20],ecx
        jbe loc_00436E34
        mov  ax,WORD PTR [edi-0x2]
        test  ah,0xf0
        je loc_00436E34
        movzx eax,ax
        mov  ecx,eax
        mov  ebx,eax
        shr  ecx,0x8
        shr  ebx,0x4
        and  ecx,0xf
        and  ebx,0xf
        and  eax,0xf
        mov  DWORD PTR [esp+0x20],eax
        mov  esi,0x1
    loc_00436E34:
        dec  edx
        cmp  ebp,edx
        jae loc_00436E67
        mov  ax,WORD PTR [edi+0x2]
        test  ah,0xf0
        je loc_00436E67
        movzx eax,ax
        mov  edx,eax
        shr  edx,0x8
        and  edx,0xf
        add  ecx,edx
        mov  edx,eax
        shr  edx,0x4
        and  edx,0xf
        add  ebx,edx
        mov  edx,DWORD PTR [esp+0x20]
        and  eax,0xf
        add  edx,eax
        mov  DWORD PTR [esp+0x20],edx
        inc  esi
    loc_00436E67:
        mov  eax,DWORD PTR [esp+0x10]
        test  eax,eax
        mov  ebp,DWORD PTR [esp+0x28]
        jbe loc_00436EB3
        mov  eax,DWORD PTR [ebp+0x110]
        cdq
        sub  eax,edx
        sar  eax,1
        shl  eax,1
        mov  edx,eax
        mov  eax,edi
        sub  eax,edx
        mov  ax,WORD PTR [eax]
        test  ah,0xf0
        je loc_00436EB3
        movzx eax,ax
        mov  edx,eax
        shr  edx,0x8
        and  edx,0xf
        add  ecx,edx
        mov  edx,eax
        shr  edx,0x4
        and  edx,0xf
        add  ebx,edx
        mov  edx,DWORD PTR [esp+0x20]
        and  eax,0xf
        add  edx,eax
        mov  DWORD PTR [esp+0x20],edx
        inc  esi
    loc_00436EB3:
        mov  eax,DWORD PTR [ebp+0x108]
        mov  edx,DWORD PTR [esp+0x10]
        dec  eax
        cmp  edx,eax
        jae loc_00436EFD
        mov  eax,DWORD PTR [ebp+0x110]
        cdq
        sub  eax,edx
        sar  eax,1
        lea  eax,[edi+eax*2]
        mov  ax,WORD PTR [eax]
        test  ah,0xf0
        je loc_00436EFD
        movzx eax,ax
        mov  edx,eax
        shr  edx,0x8
        and  edx,0xf
        add  ecx,edx
        mov  edx,eax
        shr  edx,0x4
        and  edx,0xf
        add  ebx,edx
        mov  edx,DWORD PTR [esp+0x20]
        and  eax,0xf
        add  edx,eax
        mov  DWORD PTR [esp+0x20],edx
        inc  esi
    loc_00436EFD:
        cmp  esi,0x1
        jbe loc_00436F1E
        xor  edx,edx
        mov  eax,ecx
        div  esi
        xor  edx,edx
        mov  ecx,eax
        mov  eax,ebx
        div  esi
        xor  edx,edx
        mov  ebx,eax
        mov  eax,DWORD PTR [esp+0x20]
        div  esi
        mov  DWORD PTR [esp+0x20],eax
    loc_00436F1E:
        mov  edx,DWORD PTR [esp+0x20]
        shr  ecx,1
        and  cl,0xf
        shr  ebx,1
        shr  edx,1
        movzx ax,cl
        mov  esi,DWORD PTR [esp+0x28]
        mov  ebp,DWORD PTR [esp+0x14]
        and  bl,0xf
        mov  DWORD PTR [esp+0x20],edx
        movzx cx,bl
        xor  edx,edx
        mov  dx,WORD PTR [edi]
        shl  eax,0x4
        or   eax,ecx
        mov  cl,BYTE PTR [esp+0x20]
        shl  eax,0x4
        and  edx,0xf00f
        or   eax,edx
        and  cl,0xf
        movzx dx,cl
        and  eax,0xfff0
        or   eax,edx
        mov  WORD PTR [edi],ax
    loc_00436F6C:
        mov  edx,DWORD PTR [esi+0x104]
        add  edi,0x2
        inc  ebp
        cmp  ebp,edx
        mov  DWORD PTR [esp+0x14],ebp
        jb loc_00436DF4
    loc_00436F82:
        mov  eax,DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [esp+0x2c]
        inc  eax
        cmp  eax,ecx
        mov  DWORD PTR [esp+0x10],eax
        jb loc_00436DE0
        pop  edi
        pop  esi
        pop  ebp
        mov  al,0x1
        pop  ebx
        add  esp,0x14
        ret  0x8
    loc_00436FA3:
        mov  eax,DWORD PTR [esp+0x2c]
        mov  ebp,DWORD PTR [esi+0x120]
        xor  ebx,ebx
        xor  edx,edx
        cmp  eax,ebx
        mov  DWORD PTR [esp+0x10],edx
        jbe loc_00437146
        nop
    loc_00436FC0:
        mov  edi,DWORD PTR [esi+0x104]
        xor  eax,eax
        cmp  edi,ebx
        mov  DWORD PTR [esp+0x14],eax
        jbe loc_00437135
        lea  ecx,[ebp-0x2]
        jmp loc_00436FE0
        nop
    loc_00436FE0:
        cmp  BYTE PTR [ecx+0x5],0x0
        jne loc_0043711C
        xor  esi,esi
        test  eax,eax
        mov  DWORD PTR [esp+0x20],ebx
        mov  DWORD PTR [esp+0x1c],ebx
        jbe loc_00437016
        cmp  BYTE PTR [ecx+0x1],0x0
        je loc_00437016
        movzx esi,BYTE PTR [ecx-0x1]
        movzx ebx,BYTE PTR [ecx]
        mov  DWORD PTR [esp+0x1c],esi
        movzx esi,BYTE PTR [ecx-0x2]
        mov  DWORD PTR [esp+0x20],esi
        mov  esi,0x1
    loc_00437016:
        dec  edi
        cmp  eax,edi
        jae loc_0043703F
        mov  al,BYTE PTR [ecx+0x9]
        test  al,al
        je loc_0043703F
        movzx eax,BYTE PTR [ecx+0x8]
        mov  edi,DWORD PTR [esp+0x1c]
        add  ebx,eax
        movzx eax,BYTE PTR [ecx+0x7]
        add  edi,eax
        movzx eax,BYTE PTR [ecx+0x6]
        mov  DWORD PTR [esp+0x1c],edi
        add  DWORD PTR [esp+0x20],eax
        inc  esi
    loc_0043703F:
        test  edx,edx
        jbe loc_00437088
        mov  edx,DWORD PTR [esp+0x28]
        mov  eax,DWORD PTR [edx+0x110]
        cdq
        and  edx,0x3
        add  eax,edx
        sar  eax,0x2
        shl  eax,0x2
        mov  edx,eax
        mov  eax,ebp
        sub  eax,edx
        mov  dl,BYTE PTR [eax+0x3]
        test  dl,dl
        je loc_00437088
        movzx edx,BYTE PTR [eax+0x2]
        mov  edi,DWORD PTR [esp+0x1c]
        add  ebx,edx
        movzx edx,BYTE PTR [eax+0x1]
        movzx eax,BYTE PTR [eax]
        add  edi,edx
        mov  edx,DWORD PTR [esp+0x20]
        add  edx,eax
        mov  DWORD PTR [esp+0x1c],edi
        mov  DWORD PTR [esp+0x20],edx
        inc  esi
    loc_00437088:
        mov  eax,DWORD PTR [esp+0x28]
        mov  edx,DWORD PTR [eax+0x108]
        mov  edi,DWORD PTR [esp+0x10]
        dec  edx
        cmp  edi,edx
        jae loc_004370D8
        mov  eax,DWORD PTR [eax+0x110]
        cdq
        and  edx,0x3
        add  eax,edx
        sar  eax,0x2
        mov  dl,BYTE PTR [ebp+eax*4+0x3]
        test  dl,dl
        lea  eax,[ebp+eax*4+0x0]
        je loc_004370D8
        movzx edx,BYTE PTR [eax+0x2]
        mov  edi,DWORD PTR [esp+0x1c]
        add  ebx,edx
        movzx edx,BYTE PTR [eax+0x1]
        movzx eax,BYTE PTR [eax]
        add  edi,edx
        mov  edx,DWORD PTR [esp+0x20]
        add  edx,eax
        mov  DWORD PTR [esp+0x1c],edi
        mov  DWORD PTR [esp+0x20],edx
        inc  esi
    loc_004370D8:
        cmp  esi,0x1
        jbe loc_004370FD
        xor  edx,edx
        mov  eax,ebx
        div  esi
        xor  edx,edx
        mov  ebx,eax
        mov  eax,DWORD PTR [esp+0x1c]
        div  esi
        xor  edx,edx
        mov  DWORD PTR [esp+0x1c],eax
        mov  eax,DWORD PTR [esp+0x20]
        div  esi
        mov  DWORD PTR [esp+0x20],eax
    loc_004370FD:
        mov  dl,BYTE PTR [esp+0x1c]
        mov  al,BYTE PTR [esp+0x20]
        mov  esi,DWORD PTR [esp+0x28]
        mov  BYTE PTR [ecx+0x4],bl
        mov  BYTE PTR [ecx+0x3],dl
        mov  edx,DWORD PTR [esp+0x10]
        mov  BYTE PTR [ebp+0x0],al
        mov  eax,DWORD PTR [esp+0x14]
        xor  ebx,ebx
    loc_0043711C:
        mov  edi,DWORD PTR [esi+0x104]
        add  ebp,0x4
        add  ecx,0x4
        inc  eax
        cmp  eax,edi
        mov  DWORD PTR [esp+0x14],eax
        jb loc_00436FE0
    loc_00437135:
        mov  eax,DWORD PTR [esp+0x2c]
        inc  edx
        cmp  edx,eax
        mov  DWORD PTR [esp+0x10],edx
        jb loc_00436FC0
    loc_00437146:
        pop  edi
        pop  esi
        pop  ebp
        mov  al,0x1
        pop  ebx
        add  esp,0x14
        ret  0x8
    }
}
