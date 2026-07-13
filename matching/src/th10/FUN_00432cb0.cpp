// 00432CB0: FUN_00432cb0
// Original size: 1408 bytes, actual code: 386 instructions
extern "C" void FUN_00405410(void);
extern "C" void FUN_0040ace0(void);
extern "C" void FUN_0040ad20(void);
extern "C" void FUN_00420a90(void);
extern "C" void FUN_00420b10(void);
extern "C" void FUN_00421fa0(void);
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c620(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c6d0(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_0044bea0(void);

extern "C" __declspec(naked) void FUN_00432cb0(void) {
    __asm {
        push  ecx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        mov  eax,DWORD PTR [ebp+0x20]
        cmp  eax,0x3
        ja loc_0043320C
        push  ebx
        push  esi
        push  edi
        jmp  DWORD PTR [eax*4+0x433218]
        push  0x46e0d8
        xor  ebx,ebx
        push  ebx
        mov  DWORD PTR [ebp+0x2c],0x1e
        call FUN_00420a90
        push  0x11
        push  ebx
        call FUN_00420b10
        mov  eax,DWORD PTR [ebp+0x43c]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        test  eax,eax
        jne loc_00432D2B
        push  ebp
        mov  edi,0x5e
        call FUN_0042c670
        mov  ecx,DWORD PTR ds:0x4776e0
        mov  eax,DWORD PTR [ecx+0x8994]
        push  0xf
        push  0x8
        push  eax
        lea  edi,[esp+0x1c]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x5d0],edx
    loc_00432D2B:
        push  ebp
        mov  edi,0x68
        call FUN_0042c670
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c620
        mov  edi,DWORD PTR ds:0x474c68
        add  edi,0x98
        push  ebp
        call FUN_0042c670
        mov  eax,ds:0x474c68
        mov  ecx,DWORD PTR ds:0x474c6c
        lea  edx,[ecx+eax*2]
        lea  edi,[eax+edx*1+0x9a]
        push  ebp
        call FUN_0042c670
        mov  edi,DWORD PTR ds:0x474c74
        add  edi,0xa0
        push  ebp
        call FUN_0042c670
        mov  ecx,DWORD PTR ds:0x474c6c
        mov  eax,0x8
        mov  ds:0x474c7c,eax
        mov  ds:0x474c80,eax
        mov  eax,ds:0x474c68
        lea  edx,[ecx+eax*2]
        add  edx,eax
        mov  eax,ds:0x47783c
        imul  edx,edx,0x437c
        lea  edi,[edx+eax*1+0x8]
        mov  DWORD PTR ds:0x477848,0x474908
        call FUN_00421fa0
        mov  esi,eax
        cmp  esi,ebx
        mov  DWORD PTR ds:0x477848,0x474788
        mov  DWORD PTR ds:0x474c7c,ebx
        mov  DWORD PTR ds:0x474c80,ebx
        jl loc_00432EB0
        push  ebx
        lea  eax,[ebp+0x2b0]
        call FUN_00405410
        lea  edx,[ebp+0x24]
        mov  ecx,esi
        mov  DWORD PTR [ebp+0xf4],0x1
        call FUN_0040ad20
        mov  eax,DWORD PTR [ebp+0x58fc]
        test  eax,eax
        lea  ebx,[ebp+0x58f4]
        je loc_00432E1B
        jg loc_00432E15
        dec  eax
        mov  DWORD PTR [ebx],eax
        jmp loc_00432E21
    loc_00432E15:
        xor  eax,eax
        mov  DWORD PTR [ebx],eax
        jmp loc_00432E21
    loc_00432E1B:
        mov  DWORD PTR [ebx],0x0
    loc_00432E21:
        mov  ecx,DWORD PTR ds:0x4746d8
        lea  edx,[ecx+0x1]
        lea  ebx,[ebx+0x0]
    loc_00432E30:
        mov  al,BYTE PTR [ecx]
        inc  ecx
        test  al,al
        jne loc_00432E30
        sub  ecx,edx
        mov  DWORD PTR [ebp+0x58fc],ecx
        mov  ecx,DWORD PTR ds:0x47783c
        lea  esi,[ebp+0x58dc]
        add  ecx,0x1d878
        mov  edx,esi
        mov  DWORD PTR [ebp+0x59c4],0x1
        sub  edx,ecx
        nop
    loc_00432E60:
        mov  al,BYTE PTR [ecx]
        mov  BYTE PTR [edx+ecx*1],al
        inc  ecx
        test  al,al
        jne loc_00432E60
        mov  edi,0x46e354
        mov  ecx,0x9
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        je loc_00432E83
        push  0xffffffff
        mov  eax,ebx
        call FUN_0044bea0
    loc_00432E83:
        mov  eax,0x8
        mov  ebx,0x20
        nop
    loc_00432E90:
        cmp  BYTE PTR [eax+ebp*1+0x58db],bl
        jne loc_00432E9E
        dec  eax
        test  eax,eax
        jg loc_00432E90
    loc_00432E9E:
        mov  DWORD PTR [ebp+0x58e8],eax
        mov  DWORD PTR [ebp+0x58ec],0x0
        jmp loc_00432EDA
    loc_00432EB0:
        mov  eax,DWORD PTR [ebp+0x2c]
        cmp  eax,ebx
        je loc_00432EC9
        cmp  eax,0xffffffff
        jg loc_00432EC2
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00432ED0
    loc_00432EC2:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00432ED0
    loc_00432EC9:
        mov  DWORD PTR [ebp+0x24],0xffffffff
    loc_00432ED0:
        mov  DWORD PTR [ebp+0x58ec],0x1
    loc_00432EDA:
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jle loc_00433209
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c620
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        pop  ecx
        ret  0x4
        mov  eax,DWORD PTR [ebp+0x58ec]
        test  eax,eax
        mov  ebx,0x20
        jne loc_00432FD0
        mov  eax,DWORD PTR [ebp+0x58f4]
        lea  esi,[ebp+0x58f4]
        mov  DWORD PTR [esi+0x4],eax
        mov  eax,0x10
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00432F3F
        push  0xfffffff3
        mov  eax,esi
        call FUN_0044bea0
    loc_00432F3F:
        mov  eax,ebx
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00432F59
        push  0xd
        mov  eax,esi
        call FUN_0044bea0
    loc_00432F59:
        mov  eax,0x40
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00432F88
        mov  eax,DWORD PTR [esi]
        cdq
        mov  ecx,0xd
        idiv  ecx
        mov  eax,esi
        test  edx,edx
        je loc_00432F81
        push  0xffffffff
        jmp loc_00432F83
    loc_00432F81:
        push  0xc
    loc_00432F83:
        call FUN_0044bea0
    loc_00432F88:
        mov  eax,0x80
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00432FB8
        mov  eax,DWORD PTR [esi]
        cdq
        mov  ecx,0xd
        idiv  ecx
        mov  eax,esi
        cmp  edx,0xc
        je loc_00432FB1
        push  0x1
        jmp loc_00432FB3
    loc_00432FB1:
        push  0xfffffff4
    loc_00432FB3:
        call FUN_0044bea0
    loc_00432FB8:
        mov  edx,DWORD PTR [esi+0x4]
        cmp  edx,DWORD PTR [esi]
        je loc_00432FD0
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_00432FD0:
        test  DWORD PTR ds:0x474e36,0x1001
        je loc_0043312B
        mov  eax,DWORD PTR [ebp+0x58ec]
        test  eax,eax
        jne loc_0043310E
        mov  edi,DWORD PTR ds:0x4746d8
        mov  eax,edi
        lea  edx,[eax+0x1]
        nop
    loc_00433000:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00433000
        mov  ecx,DWORD PTR [ebp+0x58f4]
        sub  eax,edx
        lea  edx,[ebp+0x58f4]
        lea  esi,[eax-0x3]
        cmp  ecx,esi
        jge loc_00433042
        mov  esi,DWORD PTR [ebp+0x58e8]
        cmp  esi,0x8
        jge loc_00433033
        mov  cl,BYTE PTR [ecx+edi*1]
        mov  BYTE PTR [esi+ebp*1+0x58dc],cl
        jmp loc_00433056
    loc_00433033:
        mov  dl,BYTE PTR [ecx+edi*1]
        mov  BYTE PTR [esi+ebp*1+0x58db],dl
        jmp loc_0043311A
    loc_00433042:
        jne loc_00433087
        mov  ecx,DWORD PTR [ebp+0x58e8]
        cmp  ecx,0x8
        jge loc_0043307B
        mov  BYTE PTR [ecx+ebp*1+0x58dc],bl
    loc_00433056:
        mov  esi,DWORD PTR [ebp+0x58e8]
        inc  esi
        mov  ecx,esi
        cmp  ecx,0x8
        mov  DWORD PTR [ebp+0x58e8],esi
        jl loc_0043311A
        lea  ecx,[eax-0x1]
        call FUN_0040ad20
        jmp loc_0043311A
    loc_0043307B:
        mov  BYTE PTR [ecx+ebp*1+0x58db],bl
        jmp loc_0043311A
    loc_00433087:
        lea  edx,[eax-0x2]
        cmp  ecx,edx
        jne loc_004330AC
        mov  eax,DWORD PTR [ebp+0x58e8]
        test  eax,eax
        je loc_00433209
        dec  eax
        mov  DWORD PTR [ebp+0x58e8],eax
        mov  BYTE PTR [eax+ebp*1+0x58dc],bl
        jmp loc_0043311A
    loc_004330AC:
        dec  eax
        cmp  ecx,eax
        jne loc_0043311A
        mov  ecx,DWORD PTR ds:0x474c74
        mov  edi,DWORD PTR ds:0x474c6c
        lea  eax,[ecx+ecx*4]
        mov  ecx,DWORD PTR [ebp+0x24]
        lea  ecx,[ecx+eax*2]
        lea  eax,[ecx+ecx*2]
        mov  ecx,DWORD PTR ds:0x474c68
        lea  edi,[edi+ecx*2]
        add  edi,ecx
        imul  edi,edi,0x437c
        mov  ecx,edi
        mov  edi,DWORD PTR ds:0x47783c
        lea  esi,[ebp+0x58dc]
        add  ecx,edi
        mov  edx,esi
        lea  ecx,[ecx+eax*8+0x1e]
    loc_004330F0:
        mov  al,BYTE PTR [edx]
        inc  edx
        mov  BYTE PTR [ecx],al
        inc  ecx
        test  al,al
        jne loc_004330F0
        lea  edx,[edi+0x1d878]
        mov  eax,esi
        sub  edx,esi
    loc_00433104:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_00433104
    loc_0043310E:
        mov  eax,ebp
        mov  ecx,0x3
        call FUN_0042c620
    loc_0043311A:
        mov  ecx,0x492590
        mov  edi,0xa
        push  0x0
        call FUN_0043dc90
    loc_0043312B:
        test  BYTE PTR ds:0x474e36,0xa
        je loc_00433209
        mov  eax,DWORD PTR [ebp+0x58ec]
        test  eax,eax
        jne loc_00433182
        mov  eax,DWORD PTR [ebp+0x58e8]
        test  eax,eax
        je loc_00433209
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  eax,DWORD PTR [ebp+0x58e8]
        dec  eax
        pop  edi
        mov  DWORD PTR [ebp+0x58e8],eax
        mov  BYTE PTR [eax+ebp*1+0x58dc],bl
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        pop  ecx
        ret  0x4
    loc_00433182:
        mov  ecx,0x3
        mov  eax,ebp
        call FUN_0042c620
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        pop  ecx
        ret  0x4
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jl loc_00433209
        mov  esi,0x68
        mov  edi,ebp
        call FUN_0042c6d0
        mov  esi,DWORD PTR ds:0x474c68
        add  esi,0x98
        call FUN_0042c6d0
        mov  eax,ds:0x474c68
        mov  ecx,DWORD PTR ds:0x474c6c
        lea  edx,[ecx+eax*2]
        lea  esi,[eax+edx*1+0x9a]
        call FUN_0042c6d0
        mov  esi,DWORD PTR ds:0x474c74
        add  esi,0xa0
        call FUN_0042c6d0
        mov  ecx,0x10
        mov  eax,ebp
        call FUN_0042c5c0
    loc_00433209:
        pop  edi
        pop  esi
        pop  ebx
    loc_0043320C:
        mov  eax,0x1
        pop  ebp
        pop  ecx
        ret  0x4
        mov  edi,edi
        int3
        sub  al,0x43
        add  dl,bl
        cs inc ebx
        add  BYTE PTR [eax],al
        das
        inc  ebx
        add  BYTE PTR [ecx+esi*1-0x3333ffbd],ch
    }
}
