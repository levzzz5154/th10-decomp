// 00430A60: FUN_00430a60
// Original size: 1424 bytes, actual code: 386 instructions
extern "C" void FUN_0040c540(void);
extern "C" void FUN_00420c30(void);
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c620(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c6d0(void);
extern "C" void FUN_0042c750(void);
extern "C" void FUN_0042c770(void);
extern "C" void FUN_0043c8b0(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00449250(void);
extern "C" void FUN_00449470(void);
extern "C" void FUN_004495e0(void);
extern "C" void FUN_004497d0(void);
extern "C" void FUN_0044be20(void);
extern "C" void FUN_0044be70(void);
extern "C" void FUN_0044bea0(void);

extern "C" __declspec(naked) void FUN_00430a60(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        mov  eax,DWORD PTR [ebp+0x20]
        cmp  eax,0x4
        ja loc_00430FD2
        push  ebx
        push  esi
        push  edi
        jmp  DWORD PTR [eax*4+0x430fdc]
        mov  DWORD PTR [ebp+0x2c],0x3
        cmp  DWORD PTR ds:0x474c74,0x4
        jne loc_00430BFC
        mov  eax,ds:0x474c68
        mov  ecx,DWORD PTR ds:0x47783c
        lea  esi,[ecx+eax*2]
        mov  bl,BYTE PTR [eax+esi*1+0x1d888]
        xor  edx,edx
        cmp  bl,dl
        jne loc_00430B1C
        cmp  DWORD PTR [ebp+0x24],edx
        jne loc_00430B04
        lea  esi,[ecx+eax*2+0x13b06]
        cmp  BYTE PTR [eax+esi*1+0x9d83],dl
        mov  eax,DWORD PTR [ebp+0x2c]
        je loc_00430AE4
        cmp  eax,edx
        je loc_00430ADB
        cmp  eax,0x1
        jg loc_00430AD1
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430B04
    loc_00430AD1:
        mov  eax,0x1
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430B04
    loc_00430ADB:
        mov  DWORD PTR [ebp+0x24],0x1
        jmp loc_00430B04
    loc_00430AE4:
        cmp  eax,edx
        je loc_00430AFD
        cmp  eax,0x2
        jg loc_00430AF3
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430B04
    loc_00430AF3:
        mov  eax,0x2
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430B04
    loc_00430AFD:
        mov  DWORD PTR [ebp+0x24],0x2
    loc_00430B04:
        mov  eax,DWORD PTR [ebp+0xf8]
        mov  DWORD PTR [ebp+eax*4+0xb4],edx
        inc  DWORD PTR [ebp+0xf8]
        mov  eax,ds:0x474c68
    loc_00430B1C:
        lea  esi,[ecx+eax*2+0x13b06]
        cmp  BYTE PTR [eax+esi*1+0x9d83],dl
        mov  esi,0x1
        jne loc_00430B95
        cmp  DWORD PTR [ebp+0x24],esi
        jne loc_00430B7D
        lea  edi,[ecx+eax*2]
        cmp  BYTE PTR [eax+edi*1+0x1d888],dl
        mov  eax,DWORD PTR [ebp+0x2c]
        je loc_00430B5D
        cmp  eax,edx
        je loc_00430B58
        jg loc_00430B51
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430B7D
    loc_00430B51:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430B7D
    loc_00430B58:
        mov  DWORD PTR [ebp+0x24],edx
        jmp loc_00430B7D
    loc_00430B5D:
        cmp  eax,edx
        je loc_00430B76
        cmp  eax,0x2
        jg loc_00430B6C
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430B7D
    loc_00430B6C:
        mov  eax,0x2
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430B7D
    loc_00430B76:
        mov  DWORD PTR [ebp+0x24],0x2
    loc_00430B7D:
        mov  eax,DWORD PTR [ebp+0xf8]
        mov  DWORD PTR [ebp+eax*4+0xb4],esi
        inc  DWORD PTR [ebp+0xf8]
        mov  eax,ds:0x474c68
    loc_00430B95:
        lea  ecx,[ecx+eax*2]
        add  eax,ecx
        cmp  BYTE PTR [eax+0x1d88a],dl
        jne loc_00430BFC
        mov  edi,DWORD PTR [ebp+0x24]
        mov  ecx,0x2
        cmp  edi,ecx
        jne loc_00430BE9
        cmp  BYTE PTR [eax+0x1d888],dl
        mov  eax,DWORD PTR [ebp+0x2c]
        je loc_00430BD1
        cmp  eax,edx
        je loc_00430BCC
        jg loc_00430BC5
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430BE9
    loc_00430BC5:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430BE9
    loc_00430BCC:
        mov  DWORD PTR [ebp+0x24],edx
        jmp loc_00430BE9
    loc_00430BD1:
        cmp  eax,edx
        je loc_00430BE6
        cmp  eax,esi
        jg loc_00430BDF
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430BE9
    loc_00430BDF:
        mov  eax,esi
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430BE9
    loc_00430BE6:
        mov  DWORD PTR [ebp+0x24],esi
    loc_00430BE9:
        mov  edx,DWORD PTR [ebp+0xf8]
        mov  DWORD PTR [ebp+edx*4+0xb4],ecx
        inc  DWORD PTR [ebp+0xf8]
    loc_00430BFC:
        push  ebp
        mov  edi,0x64
        call FUN_0042c670
        mov  esi,DWORD PTR ds:0x474c68
        add  esi,0x96
        mov  edi,ebp
        call FUN_0042c6d0
        mov  edi,DWORD PTR ds:0x474c68
        add  edi,0x96
        push  ebp
        call FUN_0042c670
        mov  eax,ds:0x474c68
        mov  ecx,DWORD PTR [ebp+eax*4+0x51c]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        mov  edi,0x3
        call FUN_00449250
        mov  ecx,DWORD PTR ds:0x474c68
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x24]
        add  si,0x11
        add  ecx,0x96
        mov  eax,ebp
        call FUN_0042c770
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c620
        mov  eax,ds:0x474c68
        mov  edi,DWORD PTR ds:0x474c74
        mov  ecx,DWORD PTR ds:0x47783c
        mov  edx,eax
        imul  edx,edx,0x329d
        add  edx,edi
        mov  esi,DWORD PTR [ecx+edx*4+0x4d0]
        test  esi,esi
        jne loc_00430CBB
        lea  ebx,[eax+eax*2+0x8a]
        lea  esi,[ebp+eax*4+0x51c]
        lea  edi,[esp+0x14]
        call FUN_004497d0
        mov  eax,edi
        call FUN_004495e0
        mov  eax,ds:0x474c68
    loc_00430CBB:
        mov  edi,DWORD PTR ds:0x474c74
        mov  ecx,DWORD PTR ds:0x47783c
        mov  edx,eax
        imul  edx,edx,0x329d
        add  edx,edi
        mov  esi,DWORD PTR [ecx+edx*4+0x484c]
        test  esi,esi
        jne loc_00430CFF
        lea  ebx,[eax+eax*2+0x8b]
        lea  esi,[ebp+eax*4+0x51c]
        lea  edi,[esp+0x14]
        call FUN_004497d0
        mov  eax,edi
        call FUN_004495e0
        mov  eax,ds:0x474c68
    loc_00430CFF:
        mov  edi,DWORD PTR ds:0x474c74
        mov  ecx,DWORD PTR ds:0x47783c
        mov  edx,eax
        imul  edx,edx,0x329d
        add  edx,edi
        mov  esi,DWORD PTR [ecx+edx*4+0x8bc8]
        test  esi,esi
        jne loc_00430D3E
        lea  ebx,[eax+eax*2+0x8c]
        lea  esi,[ebp+eax*4+0x51c]
        lea  edi,[esp+0x14]
        call FUN_004497d0
        mov  eax,edi
        call FUN_004495e0
    loc_00430D3E:
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jle loc_00430FCF
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c620
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        ret  0x4
        mov  edx,DWORD PTR [ebp+0x24]
        lea  ebx,[ebp+0x24]
        mov  DWORD PTR [ebx+0x4],edx
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x10
        test  al,cl
        jne loc_00430D80
        test  BYTE PTR ds:0x474e34,al
        je loc_00430D89
    loc_00430D80:
        push  0xffffffff
        mov  eax,ebx
        call FUN_0044bea0
    loc_00430D89:
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x20
        test  al,cl
        jne loc_00430D9D
        test  BYTE PTR ds:0x474e34,al
        je loc_00430DA6
    loc_00430D9D:
        push  0x1
        mov  eax,ebx
        call FUN_0044bea0
    loc_00430DA6:
        mov  eax,DWORD PTR [ebx+0x4]
        cmp  eax,DWORD PTR [ebx]
        je loc_00430DED
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  ecx,DWORD PTR ds:0x474c68
        add  ecx,0x96
        mov  eax,ebp
        call FUN_0042c750
        mov  ecx,DWORD PTR ds:0x474c68
        xor  esi,esi
        mov  si,WORD PTR [ebx]
        add  si,0x7
        add  ecx,0x96
        mov  eax,ebp
        call FUN_0042c770
    loc_00430DED:
        mov  eax,ds:0x474e36
        test  al,0xa
        je loc_00430E1F
        mov  ecx,0x4
        mov  eax,ebp
        call FUN_0042c620
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_00430E1F:
        test  eax,0x1001
        je loc_00430FCF
        mov  ecx,0x3
        mov  eax,ebp
        call FUN_0042c620
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  eax,ds:0x474c68
        mov  edx,DWORD PTR [ebx]
        lea  ecx,[eax+eax*2+0x3f]
        lea  ebx,[edx+ecx*2]
        lea  esi,[ebp+eax*4+0x51c]
        lea  edi,[esp+0x14]
        call FUN_004497d0
        mov  esi,0x6
        mov  eax,edi
        call FUN_00449470
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        ret  0x4
        cmp  DWORD PTR [ebp+0x2b4],0xa
        jne loc_00430EE3
        test  BYTE PTR ds:0x474ca0,0x10
        jne loc_00430EBA
        mov  esi,DWORD PTR ds:0x4776e0
        push  0x43c40000
        push  0x43f00000
        call FUN_0040c540
        push  0x0
        push  0x0
        push  0x0
        push  0x20
        push  0x5
        mov  ebx,0x2b
        call FUN_0043c8b0
        jmp loc_00430EE3
    loc_00430EBA:
        mov  ecx,DWORD PTR [ebp+0x24]
        lea  eax,[ebp+0x24]
        mov  DWORD PTR ds:0x474c6c,ecx
        call FUN_0044be20
        mov  esi,0x64
        mov  edi,ebp
        call FUN_0042c6d0
        mov  ecx,0x9
        mov  eax,ebp
        call FUN_0042c5c0
    loc_00430EE3:
        cmp  DWORD PTR [ebp+0x2b4],0x28
        jl loc_00430FCF
        mov  edx,DWORD PTR [ebp+0x24]
        lea  eax,[ebp+0x24]
        mov  DWORD PTR ds:0x474c6c,edx
        call FUN_0044be20
        test  BYTE PTR ds:0x474ca0,0x10
        jne loc_00430F71
        mov  ecx,0x3
        mov  eax,ebp
        call FUN_0042c5c0
        cmp  DWORD PTR ds:0x474c74,0x4
        mov  ecx,0x7
        jge loc_00430F3F
        mov  eax,0x1
        mov  DWORD PTR ds:0x477848,0x4747b8
        mov  ds:0x474c7c,eax
        mov  ds:0x474c80,eax
        jmp loc_00430F55
    loc_00430F3F:
        mov  DWORD PTR ds:0x477848,0x4748d8
        mov  DWORD PTR ds:0x474c7c,ecx
        mov  DWORD PTR ds:0x474c80,ecx
    loc_00430F55:
        push  0x40c00000
        mov  DWORD PTR ds:0x491fb8,ecx
        call FUN_00420c30
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_00430F71:
        mov  esi,0x64
        mov  edi,ebp
        call FUN_0042c6d0
        mov  ecx,0x9
        mov  eax,ebp
        call FUN_0042c5c0
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        ret  0x4
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jl loc_00430FCF
        mov  esi,DWORD PTR ds:0x474c68
        add  esi,0x96
        mov  edi,ebp
        call FUN_0042c6d0
        mov  esi,0x64
        call FUN_0042c6d0
        mov  ecx,0x7
        mov  eax,ebp
        call FUN_0042c5c0
        lea  eax,[ebp+0x24]
        call FUN_0044be70
    loc_00430FCF:
        pop  edi
        pop  esi
        pop  ebx
    loc_00430FD2:
        mov  eax,0x1
        pop  ebp
        ret  0x4
    }
}
