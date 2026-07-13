// 0042F540: FUN_0042f540
// Original size: 880 bytes, actual code: 217 instructions
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c620(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c770(void);
extern "C" void FUN_0042f8b0(void);
extern "C" void FUN_00430250(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00449250(void);
extern "C" void FUN_0044a4e0(void);
extern "C" void FUN_0044be70(void);
extern "C" void FUN_0044bea0(void);

extern "C" __declspec(naked) void FUN_0042f540(void) {
    __asm {
        mov  eax,DWORD PTR [ebx+0x20]
        cmp  eax,0x4
        push  ebp
        push  edi
        ja loc_0042F893
        push  esi
        jmp  DWORD PTR [eax*4+0x42f89c]
        mov  DWORD PTR [ebx+0x2c],0x7
        mov  eax,DWORD PTR [ebx+0x2c]
        test  eax,eax
        je loc_0042F573
        jg loc_0042F56C
        dec  eax
        mov  DWORD PTR [ebx+0x24],eax
        jmp loc_0042F57A
    loc_0042F56C:
        xor  eax,eax
        mov  DWORD PTR [ebx+0x24],eax
        jmp loc_0042F57A
    loc_0042F573:
        mov  DWORD PTR [ebx+0x24],0x0
    loc_0042F57A:
        push  ebx
        mov  edi,0x2
        call FUN_0042c670
        mov  ecx,0x1
        mov  eax,ebx
        call FUN_0042c620
        mov  ax,ds:0x474e88
        mov  WORD PTR [ebx+0x59cc],ax
        mov  cx,WORD PTR ds:0x474e8a
        mov  WORD PTR [ebx+0x59ce],cx
        mov  dx,WORD PTR ds:0x474e8c
        mov  WORD PTR [ebx+0x59d0],dx
        mov  ax,ds:0x474e8e
        mov  WORD PTR [ebx+0x59d2],ax
        mov  cx,WORD PTR ds:0x474e98
        mov  eax,ebx
        mov  WORD PTR [ebx+0x59d4],cx
        call FUN_0042f8b0
        cmp  DWORD PTR [ebx+0x2b4],0x6
        jle loc_0042F892
        mov  ecx,0x2
        mov  eax,ebx
        call FUN_0042c620
        mov  edx,DWORD PTR [ebx+0x2cc]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        mov  edi,0x3
        call FUN_00449250
        xor  esi,esi
        mov  si,WORD PTR [ebx+0x24]
        add  si,0x11
        mov  ecx,0x2
        mov  eax,ebx
        call FUN_0042c770
        pop  esi
        pop  edi
        mov  eax,0x1
        pop  ebp
        ret
        mov  eax,DWORD PTR [ebx+0x24]
        lea  ebp,[ebx+0x24]
        mov  DWORD PTR [ebp+0x4],eax
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x10
        test  al,cl
        jne loc_0042F648
        test  BYTE PTR ds:0x474e34,al
        je loc_0042F651
    loc_0042F648:
        push  0xffffffff
        mov  eax,ebp
        call FUN_0044bea0
    loc_0042F651:
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x20
        test  al,cl
        jne loc_0042F665
        test  BYTE PTR ds:0x474e34,al
        je loc_0042F66E
    loc_0042F665:
        push  0x1
        mov  eax,ebp
        call FUN_0044bea0
    loc_0042F66E:
        mov  ecx,DWORD PTR [ebp+0x4]
        cmp  ecx,DWORD PTR [ebp+0x0]
        je loc_0042F6B4
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  edx,DWORD PTR [ebx+0x2cc]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        mov  edi,0x3
        call FUN_00449250
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x0]
        add  si,0x7
        mov  ecx,0x2
        mov  eax,ebx
        call FUN_0042c770
    loc_0042F6B4:
        xor  ecx,ecx
        call FUN_0044a4e0
        xor  edx,edx
        nop
    loc_0042F6C0:
        cmp  BYTE PTR [edx+eax*1],0x0
        js loc_0042F6CE
        inc  edx
        cmp  edx,0x1f
        jl loc_0042F6C0
        jmp loc_0042F6DD
    loc_0042F6CE:
        mov  ecx,DWORD PTR [ebp+0x0]
        cmp  ecx,0x4
        jg loc_0042F6DD
        mov  eax,ebx
        call FUN_00430250
    loc_0042F6DD:
        test  BYTE PTR ds:0x474e36,0xa
        je loc_0042F73C
        cmp  DWORD PTR [ebp+0x0],0x6
        jne loc_0042F73C
        mov  ax,ds:0x474e88
        mov  WORD PTR [ebx+0x59cc],ax
        mov  cx,WORD PTR ds:0x474e8a
        mov  WORD PTR [ebx+0x59ce],cx
        mov  dx,WORD PTR ds:0x474e8c
        mov  WORD PTR [ebx+0x59d0],dx
        mov  ax,ds:0x474e8e
        mov  WORD PTR [ebx+0x59d2],ax
        mov  cx,WORD PTR ds:0x474e98
        mov  eax,ebx
        mov  WORD PTR [ebx+0x59d4],cx
        call FUN_0042f8b0
        jmp loc_0042F7D9
    loc_0042F73C:
        test  DWORD PTR ds:0x474e36,0x1001
        je loc_0042F892
        mov  ebp,DWORD PTR [ebp+0x0]
        sub  ebp,0x5
        je loc_0042F810
        dec  ebp
        jne loc_0042F892
        mov  dx,WORD PTR [ebx+0x59cc]
        mov  WORD PTR ds:0x474e88,dx
        mov  ax,WORD PTR [ebx+0x59ce]
        mov  ds:0x474e8a,ax
        mov  cx,WORD PTR [ebx+0x59d0]
        mov  WORD PTR ds:0x474e8c,cx
        mov  dx,WORD PTR [ebx+0x59d2]
        mov  ecx,DWORD PTR ds:0x474e88
        mov  WORD PTR ds:0x474e8e,dx
        mov  ax,WORD PTR [ebx+0x59d4]
        mov  edx,DWORD PTR ds:0x474e8c
        mov  DWORD PTR ds:0x491d4c,ecx
        mov  ecx,DWORD PTR ds:0x474e90
        mov  DWORD PTR ds:0x491d50,edx
        mov  edx,DWORD PTR ds:0x474e94
        mov  ds:0x474e98,ax
        mov  DWORD PTR ds:0x491d54,ecx
        mov  DWORD PTR ds:0x491d58,edx
        mov  ds:0x491d5c,ax
    loc_0042F7D9:
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  esi,0x6
        mov  ecx,0x2
        mov  eax,ebx
        call FUN_0042c770
        mov  ecx,0x4
        mov  eax,ebx
        call FUN_0042c620
        pop  esi
        pop  edi
        mov  eax,0x1
        pop  ebp
        ret
    loc_0042F810:
        mov  ax,ds:0x474e88
        mov  WORD PTR [ebx+0x59cc],ax
        mov  cx,WORD PTR ds:0x474e8a
        mov  WORD PTR [ebx+0x59ce],cx
        mov  dx,WORD PTR ds:0x474e8c
        mov  WORD PTR [ebx+0x59d0],dx
        mov  ax,ds:0x474e8e
        mov  WORD PTR [ebx+0x59d2],ax
        mov  cx,WORD PTR ds:0x474e98
        mov  eax,ebx
        mov  WORD PTR [ebx+0x59d4],cx
        call FUN_0042f8b0
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        pop  esi
        pop  edi
        mov  eax,0x1
        pop  ebp
        ret
        cmp  DWORD PTR [ebx+0x2b4],0xa
        jl loc_0042F892
        mov  ecx,0x4
        mov  eax,ebx
        call FUN_0042c5c0
        lea  eax,[ebx+0x24]
        call FUN_0044be70
    loc_0042F892:
        pop  esi
    loc_0042F893:
        pop  edi
        mov  eax,0x1
        pop  ebp
        ret
    }
}
