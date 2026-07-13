// 004465B0: FUN_004465b0
// Original size: 1728 bytes, actual code: 602 instructions
extern "C" void FUN_0044b360(void);
extern "C" void D3DXCreateTextureFromFileInMemoryEx(void);
extern "C" void _free(void);
extern "C" void _sprintf(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_004465b0(void) {
    __asm {
        sub  esp,0x40
        mov  eax,DWORD PTR [eax]
        push  esi
        lea  edx,[esp+0x4]
        push  edx
        xor  esi,esi
        push  esi
        mov  DWORD PTR [esp+0xc],esi
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x48]
        mov  eax,DWORD PTR [esp+0x4]
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esp+0x24]
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x30]
        mov  eax,DWORD PTR [esp+0x4]
        mov  ecx,DWORD PTR [eax]
        push  esi
        push  esi
        lea  edx,[esp+0x18]
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x34]
        mov  eax,DWORD PTR [esp+0x24]
        cmp  eax,0x1a
        ja loc_00446B20
        movzx eax,BYTE PTR [eax+0x446b4c]
        push  ebx
        push  ebp
        push  edi
        jmp  DWORD PTR [eax*4+0x446b3c]
        mov  eax,DWORD PTR [esp+0x4c]
        xor  edx,edx
        cmp  eax,esi
        mov  DWORD PTR [esp+0x14],edx
        jbe loc_00446B1D
        mov  ebp,DWORD PTR [esp+0x48]
        nop
    loc_00446620:
        mov  edi,DWORD PTR [esp+0x1c]
        mov  ebx,DWORD PTR [esp+0x20]
        imul  edi,edx
        xor  eax,eax
        add  edi,ebx
        cmp  ebp,esi
        mov  DWORD PTR [esp+0x18],eax
        jbe loc_00446782
        lea  ecx,[edi-0x2]
        mov  edi,edi
    loc_00446640:
        mov  bl,BYTE PTR [ecx+0x5]
        test  bl,bl
        jne loc_0044676D
        mov  DWORD PTR [esp+0x2c],esi
        mov  DWORD PTR [esp+0x28],esi
        xor  ebx,ebx
        xor  esi,esi
        test  eax,eax
        jbe loc_00446679
        cmp  BYTE PTR [ecx+0x1],0x0
        je loc_00446679
        movzx esi,BYTE PTR [ecx-0x1]
        movzx ebx,BYTE PTR [ecx]
        mov  DWORD PTR [esp+0x28],esi
        movzx esi,BYTE PTR [ecx-0x2]
        mov  DWORD PTR [esp+0x2c],esi
        mov  esi,0x1
    loc_00446679:
        dec  ebp
        cmp  eax,ebp
        jae loc_004466A2
        mov  al,BYTE PTR [ecx+0x9]
        test  al,al
        je loc_004466A2
        movzx eax,BYTE PTR [ecx+0x8]
        mov  ebp,DWORD PTR [esp+0x28]
        add  ebx,eax
        movzx eax,BYTE PTR [ecx+0x7]
        add  ebp,eax
        movzx eax,BYTE PTR [ecx+0x6]
        mov  DWORD PTR [esp+0x28],ebp
        add  DWORD PTR [esp+0x2c],eax
        inc  esi
    loc_004466A2:
        test  edx,edx
        jbe loc_004466E5
        mov  eax,DWORD PTR [esp+0x1c]
        cdq
        and  edx,0x3
        add  eax,edx
        sar  eax,0x2
        shl  eax,0x2
        mov  edx,eax
        mov  eax,edi
        sub  eax,edx
        mov  dl,BYTE PTR [eax+0x3]
        test  dl,dl
        je loc_004466E5
        movzx edx,BYTE PTR [eax+0x2]
        mov  ebp,DWORD PTR [esp+0x28]
        add  ebx,edx
        movzx edx,BYTE PTR [eax+0x1]
        movzx eax,BYTE PTR [eax]
        add  ebp,edx
        mov  edx,DWORD PTR [esp+0x2c]
        add  edx,eax
        mov  DWORD PTR [esp+0x28],ebp
        mov  DWORD PTR [esp+0x2c],edx
        inc  esi
    loc_004466E5:
        mov  edx,DWORD PTR [esp+0x4c]
        mov  eax,DWORD PTR [esp+0x14]
        dec  edx
        cmp  eax,edx
        jae loc_0044672C
        mov  eax,DWORD PTR [esp+0x1c]
        cdq
        and  edx,0x3
        add  eax,edx
        sar  eax,0x2
        mov  dl,BYTE PTR [edi+eax*4+0x3]
        test  dl,dl
        lea  eax,[edi+eax*4]
        je loc_0044672C
        movzx edx,BYTE PTR [eax+0x2]
        mov  ebp,DWORD PTR [esp+0x28]
        add  ebx,edx
        movzx edx,BYTE PTR [eax+0x1]
        movzx eax,BYTE PTR [eax]
        add  ebp,edx
        mov  edx,DWORD PTR [esp+0x2c]
        add  edx,eax
        mov  DWORD PTR [esp+0x28],ebp
        mov  DWORD PTR [esp+0x2c],edx
        inc  esi
    loc_0044672C:
        cmp  esi,0x1
        jbe loc_00446751
        xor  edx,edx
        mov  eax,ebx
        div  esi
        xor  edx,edx
        mov  ebx,eax
        mov  eax,DWORD PTR [esp+0x28]
        div  esi
        xor  edx,edx
        mov  DWORD PTR [esp+0x28],eax
        mov  eax,DWORD PTR [esp+0x2c]
        div  esi
        mov  DWORD PTR [esp+0x2c],eax
    loc_00446751:
        mov  dl,BYTE PTR [esp+0x28]
        mov  al,BYTE PTR [esp+0x2c]
        mov  BYTE PTR [ecx+0x3],dl
        mov  edx,DWORD PTR [esp+0x14]
        mov  BYTE PTR [edi],al
        mov  eax,DWORD PTR [esp+0x18]
        mov  BYTE PTR [ecx+0x4],bl
        mov  ebp,DWORD PTR [esp+0x48]
    loc_0044676D:
        add  edi,0x4
        add  ecx,0x4
        inc  eax
        xor  esi,esi
        cmp  eax,ebp
        mov  DWORD PTR [esp+0x18],eax
        jb loc_00446640
    loc_00446782:
        mov  eax,DWORD PTR [esp+0x4c]
        inc  edx
        cmp  edx,eax
        mov  DWORD PTR [esp+0x14],edx
        jb loc_00446620
        jmp loc_00446B1D
        mov  eax,DWORD PTR [esp+0x4c]
        xor  ecx,ecx
        cmp  eax,esi
        mov  DWORD PTR [esp+0x14],ecx
        jbe loc_00446B1D
        mov  edx,DWORD PTR [esp+0x48]
        mov  edi,edi
    loc_004467B0:
        mov  ebx,DWORD PTR [esp+0x20]
        mov  ebp,ecx
        imul  ebp,DWORD PTR [esp+0x1c]
        xor  eax,eax
        add  ebp,ebx
        cmp  edx,esi
        mov  DWORD PTR [esp+0x18],eax
        jbe loc_00446948
        jmp loc_004467D0
        nop
    loc_004467D0:
        test  BYTE PTR [ebp+0x1],0x80
        jne loc_00446934
        xor  ebx,ebx
        xor  ecx,ecx
        xor  edi,edi
        cmp  eax,esi
        mov  DWORD PTR [esp+0x2c],esi
        jbe loc_0044680F
        mov  ax,WORD PTR [ebp-0x2]
        test  ah,ah
        jns loc_0044680F
        movzx esi,ax
        mov  ecx,esi
        mov  ebx,esi
        shr  ecx,0xa
        shr  ebx,0x5
        and  ecx,0x1f
        and  ebx,0x1f
        and  esi,0x1f
        mov  DWORD PTR [esp+0x2c],esi
        mov  edi,0x1
    loc_0044680F:
        mov  eax,DWORD PTR [esp+0x18]
        dec  edx
        cmp  eax,edx
        jae loc_00446845
        mov  ax,WORD PTR [ebp+0x2]
        test  ah,ah
        jns loc_00446845
        movzx esi,ax
        mov  edx,esi
        shr  edx,0xa
        and  edx,0x1f
        mov  eax,esi
        add  ecx,edx
        mov  edx,DWORD PTR [esp+0x2c]
        shr  eax,0x5
        and  esi,0x1f
        and  eax,0x1f
        add  edx,esi
        add  ebx,eax
        mov  DWORD PTR [esp+0x2c],edx
        inc  edi
    loc_00446845:
        mov  eax,DWORD PTR [esp+0x14]
        xor  esi,esi
        cmp  eax,esi
        jbe loc_0044688C
        mov  eax,DWORD PTR [esp+0x1c]
        cdq
        sub  eax,edx
        sar  eax,1
        shl  eax,1
        mov  edx,eax
        mov  eax,ebp
        sub  eax,edx
        mov  ax,WORD PTR [eax]
        test  ah,ah
        jns loc_0044688C
        movzx eax,ax
        mov  edx,eax
        shr  edx,0xa
        and  edx,0x1f
        add  ecx,edx
        mov  edx,eax
        shr  edx,0x5
        and  edx,0x1f
        add  ebx,edx
        mov  edx,DWORD PTR [esp+0x2c]
        and  eax,0x1f
        add  edx,eax
        mov  DWORD PTR [esp+0x2c],edx
        inc  edi
    loc_0044688C:
        mov  eax,DWORD PTR [esp+0x4c]
        mov  edx,DWORD PTR [esp+0x14]
        dec  eax
        cmp  edx,eax
        jae loc_004468D2
        mov  eax,DWORD PTR [esp+0x1c]
        cdq
        sub  eax,edx
        sar  eax,1
        lea  eax,[ebp+eax*2+0x0]
        mov  ax,WORD PTR [eax]
        test  ah,ah
        jns loc_004468D2
        movzx eax,ax
        mov  edx,eax
        shr  edx,0xa
        and  edx,0x1f
        add  ecx,edx
        mov  edx,eax
        shr  edx,0x5
        and  edx,0x1f
        add  ebx,edx
        mov  edx,DWORD PTR [esp+0x2c]
        and  eax,0x1f
        add  edx,eax
        mov  DWORD PTR [esp+0x2c],edx
        inc  edi
    loc_004468D2:
        cmp  edi,0x1
        jbe loc_004468F3
        xor  edx,edx
        mov  eax,ecx
        div  edi
        xor  edx,edx
        mov  ecx,eax
        mov  eax,ebx
        div  edi
        xor  edx,edx
        mov  ebx,eax
        mov  eax,DWORD PTR [esp+0x2c]
        div  edi
        mov  DWORD PTR [esp+0x2c],eax
    loc_004468F3:
        and  cl,0x1f
        movzx cx,cl
        and  bl,0x1f
        movzx dx,bl
        xor  eax,eax
        mov  ax,WORD PTR [ebp+0x0]
        shl  ecx,0x5
        or   ecx,edx
        shl  ecx,0x5
        and  eax,0x801f
        or   ecx,eax
        mov  al,BYTE PTR [esp+0x2c]
        and  al,0x1f
        movzx dx,al
        mov  eax,DWORD PTR [esp+0x18]
        and  ecx,0xffe0
        or   ecx,edx
        mov  WORD PTR [ebp+0x0],cx
        mov  edx,DWORD PTR [esp+0x48]
    loc_00446934:
        add  ebp,0x2
        inc  eax
        cmp  eax,edx
        mov  DWORD PTR [esp+0x18],eax
        jb loc_004467D0
        mov  ecx,DWORD PTR [esp+0x14]
    loc_00446948:
        mov  eax,DWORD PTR [esp+0x4c]
        inc  ecx
        cmp  ecx,eax
        mov  DWORD PTR [esp+0x14],ecx
        jb loc_004467B0
        jmp loc_00446B1D
        mov  eax,DWORD PTR [esp+0x4c]
        xor  ecx,ecx
        cmp  eax,esi
        mov  DWORD PTR [esp+0x14],ecx
        jbe loc_00446B1D
        mov  edx,DWORD PTR [esp+0x48]
    loc_00446974:
        mov  ebx,DWORD PTR [esp+0x20]
        mov  ebp,ecx
        imul  ebp,DWORD PTR [esp+0x1c]
        xor  eax,eax
        add  ebp,ebx
        cmp  edx,esi
        mov  DWORD PTR [esp+0x18],eax
        jbe loc_00446B0C
        nop
    loc_00446990:
        test  BYTE PTR [ebp+0x1],0xf0
        jne loc_00446AF8
        xor  ebx,ebx
        xor  ecx,ecx
        xor  edi,edi
        cmp  eax,esi
        mov  DWORD PTR [esp+0x2c],esi
        jbe loc_004469D0
        mov  ax,WORD PTR [ebp-0x2]
        test  ah,0xf0
        je loc_004469D0
        movzx esi,ax
        mov  ecx,esi
        mov  ebx,esi
        shr  ecx,0x8
        shr  ebx,0x4
        and  ecx,0xf
        and  ebx,0xf
        and  esi,0xf
        mov  DWORD PTR [esp+0x2c],esi
        mov  edi,0x1
    loc_004469D0:
        mov  eax,DWORD PTR [esp+0x18]
        dec  edx
        cmp  eax,edx
        jae loc_00446A07
        mov  ax,WORD PTR [ebp+0x2]
        test  ah,0xf0
        je loc_00446A07
        movzx esi,ax
        mov  edx,esi
        shr  edx,0x4
        and  edx,0xf
        mov  eax,esi
        add  ebx,edx
        mov  edx,DWORD PTR [esp+0x2c]
        shr  eax,0x8
        and  esi,0xf
        and  eax,0xf
        add  edx,esi
        add  ecx,eax
        mov  DWORD PTR [esp+0x2c],edx
        inc  edi
    loc_00446A07:
        mov  eax,DWORD PTR [esp+0x14]
        xor  esi,esi
        cmp  eax,esi
        jbe loc_00446A4F
        mov  eax,DWORD PTR [esp+0x1c]
        cdq
        sub  eax,edx
        sar  eax,1
        shl  eax,1
        mov  edx,eax
        mov  eax,ebp
        sub  eax,edx
        mov  ax,WORD PTR [eax]
        test  ah,0xf0
        je loc_00446A4F
        movzx eax,ax
        mov  edx,eax
        shr  edx,0x8
        and  edx,0xf
        add  ecx,edx
        mov  edx,eax
        shr  edx,0x4
        and  edx,0xf
        add  ebx,edx
        mov  edx,DWORD PTR [esp+0x2c]
        and  eax,0xf
        add  edx,eax
        mov  DWORD PTR [esp+0x2c],edx
        inc  edi
    loc_00446A4F:
        mov  eax,DWORD PTR [esp+0x4c]
        mov  edx,DWORD PTR [esp+0x14]
        dec  eax
        cmp  edx,eax
        jae loc_00446A96
        mov  eax,DWORD PTR [esp+0x1c]
        cdq
        sub  eax,edx
        sar  eax,1
        lea  eax,[ebp+eax*2+0x0]
        mov  ax,WORD PTR [eax]
        test  ah,0xf0
        je loc_00446A96
        movzx eax,ax
        mov  edx,eax
        shr  edx,0x8
        and  edx,0xf
        add  ecx,edx
        mov  edx,eax
        shr  edx,0x4
        and  edx,0xf
        add  ebx,edx
        mov  edx,DWORD PTR [esp+0x2c]
        and  eax,0xf
        add  edx,eax
        mov  DWORD PTR [esp+0x2c],edx
        inc  edi
    loc_00446A96:
        cmp  edi,0x1
        jbe loc_00446AB7
        xor  edx,edx
        mov  eax,ecx
        div  edi
        xor  edx,edx
        mov  ecx,eax
        mov  eax,ebx
        div  edi
        xor  edx,edx
        mov  ebx,eax
        mov  eax,DWORD PTR [esp+0x2c]
        div  edi
        mov  DWORD PTR [esp+0x2c],eax
    loc_00446AB7:
        and  cl,0xf
        movzx cx,cl
        and  bl,0xf
        movzx dx,bl
        xor  eax,eax
        mov  ax,WORD PTR [ebp+0x0]
        shl  ecx,0x4
        or   ecx,edx
        shl  ecx,0x4
        and  eax,0xf00f
        or   ecx,eax
        mov  al,BYTE PTR [esp+0x2c]
        and  al,0xf
        movzx dx,al
        mov  eax,DWORD PTR [esp+0x18]
        and  ecx,0xfff0
        or   ecx,edx
        mov  WORD PTR [ebp+0x0],cx
        mov  edx,DWORD PTR [esp+0x48]
    loc_00446AF8:
        add  ebp,0x2
        inc  eax
        cmp  eax,edx
        mov  DWORD PTR [esp+0x18],eax
        jb loc_00446990
        mov  ecx,DWORD PTR [esp+0x14]
    loc_00446B0C:
        mov  eax,DWORD PTR [esp+0x4c]
        inc  ecx
        cmp  ecx,eax
        mov  DWORD PTR [esp+0x14],ecx
        jb loc_00446974
    loc_00446B1D:
        pop  edi
        pop  ebp
        pop  ebx
    loc_00446B20:
        mov  eax,DWORD PTR [esp+0x4]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x38]
        mov  eax,DWORD PTR [esp+0x4]
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        pop  esi
        add  esp,0x40
        ret
        nop
        push  es
        inc  sp
        add  BYTE PTR [eax+0x5e004467],bl
        imul  eax,DWORD PTR [eax+eax*1+0x1d],0x446b
        add  eax,DWORD PTR [ebx]
        add  eax,DWORD PTR [ebx]
        add  eax,DWORD PTR [ebx]
        add  eax,DWORD PTR [ebx]
        add  eax,DWORD PTR [ebx]
        add  eax,DWORD PTR [ebx]
        add  eax,DWORD PTR [ebx]
        add  eax,DWORD PTR [ebx]
        add  eax,DWORD PTR [ebx]
        add  eax,DWORD PTR [ebx]
        add  BYTE PTR [ebx],al
        add  eax,DWORD PTR [ebx]
        add  DWORD PTR [edx],eax
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        sub  esp,0x10c
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebx
        mov  DWORD PTR [esp+0x10c],eax
        mov  eax,DWORD PTR [esp+0x114]
        mov  ebx,ecx
        test  BYTE PTR ds:0x491d78,0x1
        mov  DWORD PTR [esp+0x4],eax
        mov  eax,DWORD PTR [esp+0x118]
        push  edi
        je loc_00446BC4
        mov  ecx,DWORD PTR [ebx*4+0x46f288]
        cmp  ecx,0x15
        je loc_00446BBF
        test  ecx,ecx
        je loc_00446BBF
        cmp  ecx,0x14
        jne loc_00446BC4
        mov  ebx,0x3
        jmp loc_00446BC4
    loc_00446BBF:
        mov  ebx,0x5
    loc_00446BC4:
        push  eax
        lea  ecx,[esp+0x10]
        push  0x46e1c8
        push  ecx
        call _sprintf
        add  esp,0xc
        push  0x1
        lea  edx,[esp+0xc]
        push  edx
        lea  eax,[esp+0x14]
        call FUN_0044b360
        mov  edi,eax
        test  edi,edi
        je loc_00446C31
        mov  ecx,DWORD PTR [esp+0x120]
        mov  eax,DWORD PTR [esp+0x8]
        push  esi
        push  0x0
        push  0x0
        push  ecx
        push  0xffffffff
        push  0x3
        push  0x1
        mov  DWORD PTR [esi+0x8],eax
        mov  edx,DWORD PTR [ebx*4+0x46f288]
        push  edx
        push  0x0
        push  0x0
        push  0x0
        push  0x0
        push  eax
        mov  eax,ds:0x491c30
        push  edi
        push  eax
        call D3DXCreateTextureFromFileInMemoryEx
        test  eax,eax
        je loc_00446C36
        push  edi
        call _free
        add  esp,0x4
    loc_00446C31:
        or   eax,0xffffffff
        jmp loc_00446C4C
    loc_00446C36:
        mov  eax,esi
        call FUN_004465b0
        mov  ecx,DWORD PTR [ebx*4+0x46f2a0]
        mov  DWORD PTR [esi+0xc],ecx
        mov  DWORD PTR [esi+0x4],edi
        xor  eax,eax
    loc_00446C4C:
        mov  ecx,DWORD PTR [esp+0x110]
        pop  edi
        pop  ebx
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x10c
        ret  0xc
    }
}
