// 00433570: FUN_00433570
// Original size: 1472 bytes, actual code: 409 instructions
extern "C" void FUN_00409e50(void);
extern "C" void FUN_0040ad20(void);
extern "C" void FUN_00420a90(void);
extern "C" void FUN_00420b10(void);
extern "C" void FUN_004294a0(void);
extern "C" void FUN_004296f0(void);
extern "C" void FUN_004297b0(void);
extern "C" void FUN_00429b60(void);
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c620(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c6d0(void);
extern "C" void FUN_0042c770(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_0044be70(void);
extern "C" void FUN_0044bea0(void);
extern "C" void _free(void);
extern "C" void _sprintf(void);
extern "C" void FID_conflict:__time32(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_00433570(void) {
    __asm {
        sub  esp,0x44
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebp
        mov  ebp,DWORD PTR [esp+0x4c]
        mov  DWORD PTR [esp+0x44],eax
        mov  eax,DWORD PTR [ebp+0x20]
        cmp  eax,0x4
        ja loc_00433AF9
        push  ebx
        push  esi
        push  edi
        jmp  DWORD PTR [eax*4+0x433b10]
        mov  DWORD PTR [ebp+0x2c],0x19
        mov  DWORD PTR [ebp+0xf4],0x1
        mov  eax,DWORD PTR [ebp+0x2c]
        test  eax,eax
        je loc_004335C0
        jg loc_004335B9
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_004335C7
    loc_004335B9:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_004335C7
    loc_004335C0:
        mov  DWORD PTR [ebp+0x24],0x0
    loc_004335C7:
        mov  eax,0x8
        mov  DWORD PTR ds:0x477848,0x474908
        mov  ds:0x474c7c,eax
        mov  ds:0x474c80,eax
        mov  esi,0x1
        lea  edi,[ebp+0x59e4]
        jmp loc_004335F0
        nop
    loc_004335F0:
        push  esi
        lea  eax,[esp+0x14]
        push  0x46e0c8
        push  eax
        call _sprintf
        add  esp,0xc
        lea  ecx,[esp+0x10]
        push  ecx
        call FUN_004296f0
        mov  DWORD PTR [edi],eax
        inc  esi
        add  edi,0x4
        cmp  esi,0x19
        jle loc_004335F0
        push  ebp
        mov  edi,0x69
        call FUN_0042c670
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c620
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jle loc_00433AF6
    loc_0043363C:
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c620
        jmp loc_00433AF6
        mov  edx,DWORD PTR [ebp+0x24]
        lea  esi,[ebp+0x24]
        mov  DWORD PTR [esi+0x4],edx
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x10
        test  al,cl
        jne loc_0043366A
        test  BYTE PTR ds:0x474e34,al
        je loc_00433673
    loc_0043366A:
        push  0xffffffff
        mov  eax,esi
        call FUN_0044bea0
    loc_00433673:
        test  BYTE PTR ds:0x474e36,0x20
        jne loc_00433685
        test  BYTE PTR ds:0x474e34,0x20
        je loc_0043368E
    loc_00433685:
        push  0x1
        mov  eax,esi
        call FUN_0044bea0
    loc_0043368E:
        mov  eax,DWORD PTR [esi+0x4]
        cmp  eax,DWORD PTR [esi]
        je loc_004336A6
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_004336A6:
        mov  eax,ds:0x474e36
        test  al,0xa
        je loc_004336D1
        mov  ecx,0x4
        mov  eax,ebp
        call FUN_0042c620
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        jmp loc_00433AF6
    loc_004336D1:
        test  eax,0x1001
        je loc_00433AF6
        mov  ecx,DWORD PTR [esi]
        lea  ebx,[ebp+0x58f4]
        mov  DWORD PTR [ebp+0x59dc],ecx
        mov  eax,DWORD PTR [ebx+0x8]
        test  eax,eax
        je loc_004336FE
        jg loc_004336F8
        dec  eax
        mov  DWORD PTR [ebx],eax
        jmp loc_00433704
    loc_004336F8:
        xor  eax,eax
        mov  DWORD PTR [ebx],eax
        jmp loc_00433704
    loc_004336FE:
        mov  DWORD PTR [ebx],0x0
    loc_00433704:
        mov  eax,ds:0x4746d8
        lea  edx,[eax+0x1]
        nop
    loc_00433710:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00433710
        mov  esi,DWORD PTR ds:0x477838
        sub  eax,edx
        mov  DWORD PTR [ebp+0x58fc],eax
        mov  DWORD PTR [ebp+0x59c4],0x1
        mov  edx,DWORD PTR [esi+0x18]
        add  esi,0x18
        add  edx,0xc
        push  edx
        call FID_conflict:__time32
        mov  eax,DWORD PTR [esi]
        mov  DWORD PTR [eax+0x5c],0x8
        mov  eax,ds:0x47783c
        lea  esi,[ebp+0x58dc]
        add  eax,0x1d878
        mov  ecx,esi
        add  esp,0x4
        sub  ecx,eax
        mov  edi,edi
    loc_00433760:
        mov  dl,BYTE PTR [eax]
        mov  BYTE PTR [eax+ecx*1],dl
        inc  eax
        test  dl,dl
        jne loc_00433760
        mov  edi,0x46e354
        mov  ecx,0x9
        xor  edx,edx
        mov  DWORD PTR [ebp+0x58e8],0x0
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        je loc_0043378D
        push  0xffffffff
        mov  eax,ebx
        call FUN_0044bea0
    loc_0043378D:
        mov  eax,0x8
    loc_00433792:
        cmp  BYTE PTR [eax+ebp*1+0x58db],0x20
        jne loc_004337A1
        dec  eax
        test  eax,eax
        jg loc_00433792
    loc_004337A1:
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        mov  DWORD PTR [ebp+0x58e8],eax
        call FUN_0043dc90
        mov  ecx,0x3
        mov  eax,ebp
        call FUN_0042c620
        jmp loc_00433AF6
        mov  eax,DWORD PTR [ebp+0x58f4]
        lea  esi,[ebp+0x58f4]
        mov  DWORD PTR [esi+0x4],eax
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x10
        test  al,cl
        jne loc_004337EC
        test  BYTE PTR ds:0x474e34,al
        je loc_004337F5
    loc_004337EC:
        push  0xfffffff3
        mov  eax,esi
        call FUN_0044bea0
    loc_004337F5:
        test  BYTE PTR ds:0x474e36,0x20
        jne loc_00433807
        test  BYTE PTR ds:0x474e34,0x20
        je loc_00433810
    loc_00433807:
        push  0xd
        mov  eax,esi
        call FUN_0044bea0
    loc_00433810:
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x40
        test  al,cl
        jne loc_00433824
        test  BYTE PTR ds:0x474e34,al
        je loc_0043383F
    loc_00433824:
        mov  eax,DWORD PTR [esi]
        cdq
        mov  ecx,0xd
        idiv  ecx
        mov  eax,esi
        test  edx,edx
        je loc_00433838
        push  0xffffffff
        jmp loc_0043383A
    loc_00433838:
        push  0xc
    loc_0043383A:
        call FUN_0044bea0
    loc_0043383F:
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x80
        test  al,cl
        jne loc_00433853
        test  BYTE PTR ds:0x474e34,al
        je loc_0043386F
    loc_00433853:
        mov  eax,DWORD PTR [esi]
        cdq
        mov  ecx,0xd
        idiv  ecx
        mov  eax,esi
        cmp  edx,0xc
        je loc_00433868
        push  0x1
        jmp loc_0043386A
    loc_00433868:
        push  0xfffffff4
    loc_0043386A:
        call FUN_0044bea0
    loc_0043386F:
        mov  edx,DWORD PTR [esi+0x4]
        cmp  edx,DWORD PTR [esi]
        je loc_00433887
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_00433887:
        test  DWORD PTR ds:0x474e36,0x1001
        je loc_004339ED
        mov  edi,DWORD PTR ds:0x4746d8
        mov  eax,edi
        lea  edx,[eax+0x1]
    loc_004338A2:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_004338A2
        mov  ecx,DWORD PTR [esi]
        sub  eax,edx
        lea  edx,[eax-0x3]
        cmp  ecx,edx
        jge loc_004338DA
        mov  edx,DWORD PTR [ebp+0x58e8]
        cmp  edx,0x8
        jge loc_004338CB
        mov  cl,BYTE PTR [ecx+edi*1]
        mov  BYTE PTR [edx+ebp*1+0x58dc],cl
        jmp loc_004338EF
    loc_004338CB:
        mov  al,BYTE PTR [ecx+edi*1]
        mov  BYTE PTR [edx+ebp*1+0x58db],al
        jmp loc_004339DC
    loc_004338DA:
        jne loc_00433923
        mov  ecx,DWORD PTR [ebp+0x58e8]
        cmp  ecx,0x8
        jge loc_00433916
        mov  BYTE PTR [ecx+ebp*1+0x58dc],0x20
    loc_004338EF:
        mov  edx,DWORD PTR [ebp+0x58e8]
        inc  edx
        mov  ecx,edx
        cmp  ecx,0x8
        mov  DWORD PTR [ebp+0x58e8],edx
        jl loc_004339DC
        lea  ecx,[eax-0x1]
        mov  edx,esi
        call FUN_0040ad20
        jmp loc_004339DC
    loc_00433916:
        mov  BYTE PTR [ecx+ebp*1+0x58db],0x20
        jmp loc_004339DC
    loc_00433923:
        lea  edx,[eax-0x2]
        cmp  ecx,edx
        jne loc_0043394C
        mov  eax,DWORD PTR [ebp+0x58e8]
        test  eax,eax
        je loc_00433AF6
        dec  eax
        mov  DWORD PTR [ebp+0x58e8],eax
        mov  BYTE PTR [eax+ebp*1+0x58dc],0x20
        jmp loc_004339DC
    loc_0043394C:
        dec  eax
        cmp  ecx,eax
        jne loc_004339DC
        push  0x0
        mov  edi,0x2c
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  eax,DWORD PTR [ebp+0x24]
        inc  eax
        push  eax
        lea  ecx,[esp+0x14]
        push  0x46e0c8
        push  ecx
        call _sprintf
        mov  edx,DWORD PTR [ebp+0x24]
        mov  esi,DWORD PTR [ebp+edx*4+0x59e4]
        add  esp,0xc
        call FUN_004297b0
        mov  ecx,DWORD PTR ds:0x477838
        lea  esi,[ebp+0x58dc]
        push  esi
        lea  edx,[esp+0x14]
        call FUN_00429b60
        mov  edi,DWORD PTR [ebp+0x24]
        lea  eax,[esp+0x10]
        push  eax
        call FUN_004296f0
        mov  edx,DWORD PTR ds:0x47783c
        add  edx,0x1d878
        mov  DWORD PTR [ebp+edi*4+0x59e4],eax
        mov  eax,esi
        sub  edx,esi
    loc_004339C6:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [eax+edx*1],cl
        inc  eax
        test  cl,cl
        jne loc_004339C6
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c620
    loc_004339DC:
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_004339ED:
        test  BYTE PTR ds:0x474e36,0xa
        je loc_00433AF6
        mov  eax,DWORD PTR [ebp+0x58e8]
        test  eax,eax
        je loc_0043363C
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  eax,DWORD PTR [ebp+0x58e8]
        dec  eax
        mov  DWORD PTR [ebp+0x58e8],eax
        mov  BYTE PTR [eax+ebp*1+0x58dc],0x20
        jmp loc_00433AF6
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jl loc_00433AF6
        mov  esi,0x69
        mov  edi,ebp
        call FUN_0042c6d0
        mov  esi,0x8
        mov  ecx,0x5a
        mov  eax,ebp
        call FUN_0042c770
        mov  ecx,0x5b
        mov  eax,ebp
        call FUN_0042c770
        mov  esi,0x5e
        call FUN_0042c6d0
        lea  eax,[ebp+0x5d0]
        call FUN_00409e50
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c5c0
        lea  eax,[ebp+0x24]
        call FUN_0044be70
        mov  esi,DWORD PTR ds:0x477838
        test  esi,esi
        je loc_00433AAB
        push  esi
        call FUN_004294a0
        push  esi
        call _free
        add  esp,0x4
    loc_00433AAB:
        push  0x46f018
        push  0x0
        call FUN_00420a90
        push  0x0
        push  0x0
        call FUN_00420b10
        lea  ebx,[ebp+0x59e4]
        mov  esi,ebx
        mov  edi,0x19
        nop
    loc_00433AD0:
        mov  ebp,DWORD PTR [esi]
        test  ebp,ebp
        je loc_00433AE5
        push  ebp
        call FUN_004294a0
        push  ebp
        call _free
        add  esp,0x4
    loc_00433AE5:
        add  esi,0x4
        dec  edi
        jne loc_00433AD0
        mov  ecx,0x32
        xor  eax,eax
        mov  edi,ebx
        rep stosd
    loc_00433AF6:
        pop  edi
        pop  esi
        pop  ebx
    loc_00433AF9:
        mov  ecx,DWORD PTR [esp+0x44]
        pop  ebp
        xor  ecx,esp
        mov  eax,0x1
        call __security_check_cookie
        add  esp,0x44
        ret  0x4
        cdq
        xor  eax,0x362f0043
        inc  ebx
        add  BYTE PTR [ebp+0x36],cl
        inc  ebx
        add  cl,cl
        aaa
        inc  ebx
        add  BYTE PTR [ebx],dh
        cmp  al,BYTE PTR [ebx+0x0]
    }
}
