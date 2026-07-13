// 0044A190: FUN_0044a190
// Original size: 848 bytes, actual code: 282 instructions
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0044a190(void) {
    __asm {
        push  ebp
        mov  ebp,esp
        and  esp,0xfffffff8
        sub  esp,0x154
        mov  eax,ds:0x473660
        xor  eax,ebp
        mov  DWORD PTR [esp+0x150],eax
        mov  eax,DWORD PTR [ebp+0x8]
        imul  eax,eax,0x6a
        add  eax,0x474e30
        push  ebx
        mov  ebx,eax
        mov  eax,ds:0x491ff4
        test  ah,0x4
        push  esi
        push  edi
        mov  esi,ecx
        jne loc_0044A32E
        xor  eax,eax
        mov  ecx,0xd
        lea  edi,[esp+0x14]
        rep stosd
        mov  edi,DWORD PTR [ebp+0xc]
        xor  ecx,ecx
        test  edi,edi
        setne cl
        lea  eax,[esp+0x14]
        push  eax
        mov  DWORD PTR [esp+0x18],0x34
        mov  DWORD PTR [esp+0x1c],0xff
        push  ecx
        call  DWORD PTR ds:0x466280
        test  eax,eax
        jne loc_0044A3C2
        mov  cx,WORD PTR [ebx+0x58]
        test  cx,cx
        mov  edx,DWORD PTR [esp+0x34]
        jl loc_0044A223
        mov  eax,0x1
        shl  eax,cl
        and  eax,edx
        neg  eax
        sbb  eax,eax
        neg  eax
        or   esi,eax
    loc_0044A223:
        mov  cx,WORD PTR [ebx+0x5a]
        test  cx,cx
        jl loc_0044A23E
        mov  eax,0x1
        shl  eax,cl
        and  eax,edx
        neg  eax
        sbb  eax,eax
        and  eax,0x2
        or   esi,eax
    loc_0044A23E:
        mov  cx,WORD PTR [ebx+0x5e]
        test  cx,cx
        jl loc_0044A259
        mov  eax,0x1
        shl  eax,cl
        and  eax,edx
        neg  eax
        sbb  eax,eax
        and  eax,0x8
        or   esi,eax
    loc_0044A259:
        mov  cx,WORD PTR [ebx+0x5c]
        test  cx,cx
        jl loc_0044A274
        mov  eax,0x1
        shl  eax,cl
        and  eax,edx
        neg  eax
        sbb  eax,eax
        and  eax,0x4
        or   esi,eax
    loc_0044A274:
        mov  bx,WORD PTR [ebx+0x68]
        test  bx,bx
        jl loc_0044A293
        mov  eax,0x1
        mov  cl,bl
        shl  eax,cl
        and  eax,edx
        neg  eax
        sbb  eax,eax
        and  eax,0x100
        or   esi,eax
    loc_0044A293:
        mov  eax,DWORD PTR [ebp+0xc]
        imul  eax,eax,0x194
        mov  edx,DWORD PTR [eax+0x4918e0]
        mov  edi,DWORD PTR [eax+0x4918dc]
        mov  ebx,DWORD PTR [eax+0x4918e0]
        mov  ecx,edx
        sub  ecx,edi
        add  edi,edx
        mov  edx,DWORD PTR [esp+0x1c]
        shr  edi,1
        shr  ecx,0x2
        add  edi,ecx
        cmp  edi,edx
        sbb  edi,edi
        add  ebx,DWORD PTR [eax+0x4918dc]
        and  edi,0x80
        shr  ebx,1
        sub  ebx,ecx
        cmp  edx,ebx
        sbb  edx,edx
        and  edx,0x40
        or   edi,edx
        mov  edx,DWORD PTR [eax+0x4918e8]
        or   esi,edi
        mov  edi,DWORD PTR [eax+0x4918e4]
        mov  ebx,edi
        add  ebx,edx
        mov  ecx,edx
        sub  ecx,edi
        shr  ecx,0x2
        shr  ebx,1
        sub  ebx,ecx
        mov  eax,ebx
        mov  ebx,DWORD PTR [esp+0x20]
        cmp  ebx,eax
        sbb  eax,eax
        add  edi,edx
        shr  edi,1
        add  edi,ecx
        and  eax,0x10
        cmp  edi,ebx
        sbb  ecx,ecx
        and  ecx,0x20
        or   eax,ecx
        or   eax,esi
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x150]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret  0x8
    loc_0044A32E:
        mov  edx,DWORD PTR [ebp+0xc]
        mov  eax,DWORD PTR [edx*4+0x491c3c]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x64]
        test  eax,eax
        jge loc_0044A397
        mov  ebx,DWORD PTR [ebp+0xc]
        mov  eax,DWORD PTR [ebx*4+0x491c3c]
        mov  edx,DWORD PTR [eax]
        push  eax
        xor  edi,edi
        call  DWORD PTR [edx+0x1c]
        cmp  eax,0x8007001e
        jne loc_0044A3C2
        jmp loc_0044A360
        nop
    loc_0044A360:
        mov  eax,DWORD PTR [ebx*4+0x491c3c]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x1c]
        inc  edi
        cmp  edi,0x190
        jge loc_0044A3C2
        cmp  eax,0x8007001e
        je loc_0044A360
        mov  ax,si
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x150]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret  0x8
    loc_0044A397:
        mov  edx,DWORD PTR [ebp+0xc]
        xor  eax,eax
        mov  ecx,0x44
        lea  edi,[esp+0x48]
        rep stosd
        mov  eax,DWORD PTR [edx*4+0x491c3c]
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esp+0x48]
        push  edx
        push  0x110
        push  eax
        call  DWORD PTR [ecx+0x24]
        test  eax,eax
        jge loc_0044A3DC
    loc_0044A3C2:
        mov  ax,si
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x150]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret  0x8
    loc_0044A3DC:
        mov  ax,WORD PTR [ebx+0x58]
        test  ax,ax
        jl loc_0044A3F2
        movsx eax,ax
        movzx eax,BYTE PTR [esp+eax*1+0x78]
        shr  eax,0x7
        or   esi,eax
    loc_0044A3F2:
        mov  ax,WORD PTR [ebx+0x5a]
        test  ax,ax
        jl loc_0044A40B
        movsx ecx,ax
        movzx eax,BYTE PTR [esp+ecx*1+0x78]
        shr  eax,0x6
        and  eax,0x2
        or   esi,eax
    loc_0044A40B:
        mov  ax,WORD PTR [ebx+0x5e]
        test  ax,ax
        jl loc_0044A424
        movsx edx,ax
        movzx eax,BYTE PTR [esp+edx*1+0x78]
        shr  eax,0x4
        and  eax,0x8
        or   esi,eax
    loc_0044A424:
        mov  ax,WORD PTR [ebx+0x5c]
        test  ax,ax
        jl loc_0044A43D
        movsx eax,ax
        movzx eax,BYTE PTR [esp+eax*1+0x78]
        shr  eax,0x5
        and  eax,0x4
        or   esi,eax
    loc_0044A43D:
        mov  bx,WORD PTR [ebx+0x68]
        test  bx,bx
        jl loc_0044A457
        movsx ecx,bx
        movzx eax,BYTE PTR [esp+ecx*1+0x78]
        and  eax,0x80
        shl  eax,1
        or   esi,eax
    loc_0044A457:
        movsx ecx,WORD PTR ds:0x491d5e
        mov  ebx,DWORD PTR [esp+0x48]
        movsx eax,WORD PTR ds:0x491d60
        mov  edi,DWORD PTR [esp+0x4c]
        neg  ecx
        xor  edx,edx
        cmp  ebx,ecx
        setge dl
        xor  ebx,ebx
        mov  ecx,eax
        neg  ecx
        dec  edx
        and  edx,0x40
        cmp  edi,ecx
        movsx edi,WORD PTR ds:0x491d5e
        setge bl
        xor  ecx,ecx
        dec  ebx
        and  ebx,0x10
        or   edx,ebx
        cmp  DWORD PTR [esp+0x48],edi
        mov  edi,DWORD PTR [esp+0x4c]
        setle cl
        dec  ecx
        and  ecx,0x80
        or   edx,ecx
        xor  ecx,ecx
        cmp  edi,eax
        setle cl
        pop  edi
        dec  ecx
        and  ecx,0x20
        or   edx,ecx
        mov  ecx,DWORD PTR [esp+0x158]
        or   edx,esi
        pop  esi
        xor  ecx,ebp
        mov  ax,dx
        pop  ebx
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret  0x8
    }
}
