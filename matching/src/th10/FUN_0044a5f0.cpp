// 0044A5F0: FUN_0044a5f0
// Original size: 2592 bytes, actual code: 278 instructions
extern "C" void FUN_0044a190(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0044a5f0(void) {
    __asm {
        sub  esp,0x108
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebx
        push  esi
        mov  ebx,ecx
        mov  esi,ebx
        imul  esi,esi,0x6a
        mov  DWORD PTR [esp+0x10c],eax
        mov  eax,ds:0x4924fc
        push  edi
        xor  edi,edi
        add  esi,0x474e30
        test  eax,eax
        je loc_0044A8B3
        mov  eax,ds:0x491ff4
        test  ah,0x2
        jne loc_0044A754
        lea  eax,[esp+0x10]
        push  eax
        call  DWORD PTR ds:0x466208
        mov  al,BYTE PTR [esp+0x20]
        mov  cl,BYTE PTR [esp+0x68]
        mov  dl,BYTE PTR [esp+0x6a]
        and  cl,0xbf
        shr  dl,1
        or   cl,dl
        mov  dl,BYTE PTR [esp+0x2b]
        shr  cl,1
        and  al,0x9f
        or   cl,al
        mov  al,BYTE PTR [esp+0x78]
        shr  cl,1
        and  dl,0x8f
        or   cl,dl
        or   al,BYTE PTR [esp+0x36]
        mov  dl,BYTE PTR [esp+0x72]
        shr  cl,1
        and  al,0x87
        or   cl,al
        or   dl,BYTE PTR [esp+0x38]
        mov  al,BYTE PTR [esp+0x74]
        shr  cl,1
        and  dl,0x83
        or   cl,dl
        or   al,BYTE PTR [esp+0x35]
        mov  dl,BYTE PTR [esp+0x76]
        shr  cl,1
        and  al,0x81
        or   cl,al
        or   dl,BYTE PTR [esp+0x37]
        mov  al,BYTE PTR [esp+0x62]
        shr  cl,1
        and  dl,0x80
        or   cl,dl
        mov  dl,BYTE PTR [esp+0x54]
        movzx di,cl
        and  al,0x80
        and  dl,0x80
        movzx cx,al
        movzx ax,dl
        mov  dl,BYTE PTR [esp+0x1d]
        and  dl,0x80
        shl  ecx,1
        or   ecx,eax
        movzx ax,dl
        mov  dl,BYTE PTR [esp+0x60]
        shl  ecx,1
        or   ecx,eax
        or   dl,BYTE PTR [esp+0x34]
        and  dl,0x80
        movzx ax,dl
        mov  dl,BYTE PTR [esp+0x63]
        shl  ecx,1
        and  dl,0x80
        or   ecx,eax
        movzx ax,dl
        mov  dl,BYTE PTR [esp+0x61]
        shl  ecx,1
        and  dl,0x80
        or   ecx,eax
        movzx ax,dl
        mov  dl,BYTE PTR [esp+0x21]
        shl  ecx,1
        and  dl,0x80
        or   ecx,eax
        movzx ax,dl
        shl  ecx,1
        or   ecx,eax
        shl  ecx,1
        or   edi,ecx
        mov  cl,BYTE PTR [esp+0x73]
        and  cl,0x80
        neg  cl
        mov  dl,BYTE PTR [esp+0x79]
        mov  al,BYTE PTR [esp+0x71]
        sbb  ecx,ecx
        and  ecx,0xa0
        or   edi,ecx
        mov  cl,BYTE PTR [esp+0x77]
        and  dl,0x80
        neg  dl
        sbb  edx,edx
        and  edx,0x90
        and  al,0x80
        or   edi,edx
        neg  al
        sbb  eax,eax
        and  eax,0x60
        and  cl,0x80
        or   edi,eax
        neg  cl
        sbb  ecx,ecx
        and  ecx,0x50
        or   edi,ecx
        jmp loc_0044A8B3
    loc_0044A754:
        mov  eax,ds:0x491c38
        mov  edx,DWORD PTR [eax]
        lea  ecx,[esp+0x10]
        push  ecx
        push  0x100
        push  eax
        call  DWORD PTR [edx+0x24]
        xor  edi,edi
        cmp  eax,0x8007001e
        jne loc_0044A782
        mov  eax,ds:0x491c38
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x1c]
        jmp loc_0044A8B3
    loc_0044A782:
        test  eax,eax
        je loc_0044A796
        mov  eax,ds:0x491c38
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x1c]
        jmp loc_0044A8B3
    loc_0044A796:
        mov  cl,BYTE PTR [esp+0x3a]
        mov  dl,BYTE PTR [esp+0x3d]
        mov  al,BYTE PTR [esp+0x3c]
        and  dl,0xbf
        shr  al,1
        or   dl,al
        shr  dl,1
        mov  al,BYTE PTR [esp+0x11]
        and  cl,0x9f
        or   dl,cl
        mov  cl,BYTE PTR [esp+0x58]
        shr  dl,1
        and  al,0x8f
        or   dl,al
        or   cl,BYTE PTR [esp+0xd8]
        mov  al,BYTE PTR [esp+0xe0]
        shr  dl,1
        and  cl,0x87
        or   dl,cl
        or   al,BYTE PTR [esp+0x60]
        mov  cl,BYTE PTR [esp+0x5b]
        shr  dl,1
        and  al,0x83
        or   dl,al
        or   cl,BYTE PTR [esp+0xdb]
        mov  al,BYTE PTR [esp+0x5d]
        shr  dl,1
        and  cl,0x81
        or   dl,cl
        or   al,BYTE PTR [esp+0xdd]
        mov  cl,BYTE PTR [esp+0x23]
        shr  dl,1
        and  al,0x80
        or   dl,al
        mov  al,BYTE PTR [esp+0x30]
        movzx di,dl
        and  cl,0x80
        and  al,0x80
        movzx dx,cl
        movzx cx,al
        mov  al,BYTE PTR [esp+0x2c]
        and  al,0x80
        shl  edx,1
        or   edx,ecx
        movzx cx,al
        mov  al,BYTE PTR [esp+0x29]
        shl  edx,1
        or   edx,ecx
        or   al,BYTE PTR [esp+0xd7]
        and  al,0x80
        movzx cx,al
        mov  al,BYTE PTR [esp+0x2f]
        shl  edx,1
        and  al,0x80
        or   edx,ecx
        movzx cx,al
        mov  al,BYTE PTR [esp+0x20]
        shl  edx,1
        and  al,0x80
        or   edx,ecx
        movzx cx,al
        mov  al,BYTE PTR [esp+0x2d]
        shl  edx,1
        and  al,0x80
        or   edx,ecx
        movzx cx,al
        shl  edx,1
        or   edx,ecx
        shl  edx,1
        or   edi,edx
        mov  dl,BYTE PTR [esp+0x59]
        and  dl,0x80
        neg  dl
        sbb  edx,edx
        and  edx,0x90
        or   edi,edx
        mov  al,BYTE PTR [esp+0x5f]
        mov  cl,BYTE PTR [esp+0x57]
        mov  dl,BYTE PTR [esp+0x61]
        and  al,0x80
        neg  al
        sbb  eax,eax
        and  eax,0x60
        and  cl,0x80
        or   edi,eax
        neg  cl
        sbb  ecx,ecx
        and  ecx,0x50
        and  dl,0x80
        or   edi,ecx
        neg  dl
        sbb  edx,edx
        and  edx,0xa0
        or   edi,edx
    loc_0044A8B3:
        push  0x0
        push  ebx
        mov  ecx,edi
        call FUN_0044a190
        mov  cx,WORD PTR [esi]
        mov  ebx,0x1
        mov  WORD PTR [esi+0x2],cx
        mov  WORD PTR [esi],ax
        mov  edx,ebx
        mov  DWORD PTR [esp+0xc],eax
        mov  WORD PTR [esi+0x4],0x0
        lea  ecx,[esi+0xa]
        mov  edi,0x10
    loc_0044A8E0:
        test  BYTE PTR [esp+0xc],bl
        je loc_0044A8FA
        inc  WORD PTR [ecx]
        cmp  WORD PTR [ecx],0x1a
        jb loc_0044A8FF
        or   WORD PTR [esi+0x4],dx
        add  WORD PTR [ecx],0xfff8
        jmp loc_0044A8FF
    loc_0044A8FA:
        mov  WORD PTR [ecx],0x0
    loc_0044A8FF:
        shr  WORD PTR [esp+0xc],1
        add  ecx,0x2
        shl  edx,1
        dec  edi
        jne loc_0044A8E0
        xor  ecx,ecx
        mov  cx,WORD PTR [esi]
        xor  edx,edx
        mov  dx,WORD PTR [esi+0x2]
        xor  dx,cx
        mov  edi,edx
        and  edi,ecx
        not  ecx
        and  ecx,edx
        mov  WORD PTR [esi+0x6],di
        mov  WORD PTR [esi+0x8],cx
        mov  ecx,DWORD PTR [esp+0x110]
        pop  edi
        pop  esi
        pop  ebx
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x108
        ret
    }
}
