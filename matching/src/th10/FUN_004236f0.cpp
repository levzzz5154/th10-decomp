// 004236F0: FUN_004236f0
// Original size: 3328 bytes, actual code: 951 instructions
extern "C" void FUN_00405410(void);
extern "C" void FUN_0040ac90(void);
extern "C" void FUN_0040ace0(void);
extern "C" void FUN_0040ad20(void);
extern "C" void FUN_0040c4d0(void);
extern "C" void FUN_00421f60(void);
extern "C" void FUN_00423510(void);
extern "C" void FUN_00423570(void);
extern "C" void FUN_004243f0(void);
extern "C" void FUN_004294a0(void);
extern "C" void FUN_004296f0(void);
extern "C" void FUN_004297b0(void);
extern "C" void FUN_00429b60(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00449470(void);
extern "C" void FUN_00449590(void);
extern "C" void FUN_004495e0(void);
extern "C" void FUN_004497d0(void);
extern "C" void FUN_0044be20(void);
extern "C" void FUN_0044be70(void);
extern "C" void FUN_0044bea0(void);
extern "C" void _free(void);
extern "C" void _sprintf(void);
extern "C" void FID_conflict:__time32(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_004236f0(void) {
    __asm {
        sub  esp,0x4c
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebp
        mov  ebp,DWORD PTR [esp+0x54]
        mov  DWORD PTR [esp+0x4c],eax
        mov  eax,DWORD PTR [ebp+0x4]
        add  eax,0xfffffffa
        cmp  eax,0x7
        ja loc_00424379
        push  ebx
        push  esi
        push  edi
        jmp  DWORD PTR [eax*4+0x42438c]
        mov  eax,DWORD PTR [ebp+0x14]
        mov  edi,0xa
        cmp  eax,edi
        jl loc_00424376
        test  DWORD PTR ds:0x474e36,0x1001
        je loc_00424376
        push  0x0
        mov  ecx,0x492590
        call FUN_0043dc90
        lea  eax,[ebp+0x1d4]
        mov  esi,0x2
        mov  DWORD PTR [ebp+0x4],0x7
        call FUN_00449470
        push  0x0
        lea  eax,[ebp+0x10]
        call FUN_00405410
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x48]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
        cmp  DWORD PTR [ebp+0x14],0xa
        jl loc_00424376
        mov  eax,ds:0x47770c
        call FUN_00421f60
        test  BYTE PTR ds:0x474ca0,0x10
        je loc_00423849
        mov  eax,ds:0x474c68
        mov  ecx,DWORD PTR ds:0x474c6c
        mov  esi,DWORD PTR ds:0x47783c
        lea  edx,[ecx+eax*2]
        mov  ecx,DWORD PTR ds:0x474c7c
        add  edx,eax
        mov  eax,ds:0x474c74
        imul  edx,edx,0x437c
        lea  eax,[eax+eax*2]
        add  edx,esi
        lea  eax,[ecx+eax*2]
        mov  ecx,DWORD PTR ds:0x474c44
        lea  eax,[edx+eax*8+0x4dc]
        cmp  ecx,DWORD PTR [eax]
        jle loc_004237E1
        mov  DWORD PTR [eax],ecx
    loc_004237E1:
        mov  DWORD PTR [ebp+0x4],0x8
        mov  DWORD PTR [ebp+0x2c],0x3
        mov  DWORD PTR [ebp+0xf4],0x1
        mov  eax,DWORD PTR [ebp+0x2c]
        test  eax,eax
        je loc_0042380F
        cmp  eax,0x2
        jg loc_0042388E
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00423816
    loc_0042380F:
        mov  DWORD PTR [ebp+0x24],0x2
    loc_00423816:
        lea  edi,[ebp+0x1d4]
        mov  eax,edi
        call FUN_0040c4d0
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x24]
        add  si,0x7
        mov  eax,edi
        call FUN_00449470
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x48]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
    loc_00423849:
        push  ebp
        call FUN_00423570
        push  0x0
        lea  eax,[ebp+0x10]
        call FUN_00405410
        mov  eax,DWORD PTR [ebp+0x1e8]
        test  eax,eax
        jne loc_004237E1
        lea  eax,[ebp+0x1d4]
        mov  DWORD PTR [ebp+0x4],0xc
        call FUN_004495e0
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x48]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
    loc_0042388E:
        mov  eax,0x2
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00423816
        mov  ecx,DWORD PTR [ebp+0x24]
        lea  esi,[ebp+0x24]
        mov  DWORD PTR [esi+0x4],ecx
        test  BYTE PTR ds:0x474e36,0x10
        jne loc_004238B6
        test  BYTE PTR ds:0x474e34,0x10
        je loc_004238BF
    loc_004238B6:
        push  0xffffffff
        mov  eax,esi
        call FUN_0044bea0
    loc_004238BF:
        test  BYTE PTR ds:0x474e36,0x20
        jne loc_004238D1
        test  BYTE PTR ds:0x474e34,0x20
        je loc_004238DA
    loc_004238D1:
        push  0x1
        mov  eax,esi
        call FUN_0044bea0
    loc_004238DA:
        mov  edx,DWORD PTR [esi+0x4]
        mov  eax,DWORD PTR [esi]
        cmp  edx,eax
        je loc_00423906
        movsx esi,ax
        add  si,0x7
        lea  eax,[ebp+0x1d4]
        call FUN_00449470
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_00423906:
        test  DWORD PTR ds:0x474e36,0x1001
        je loc_00423A0A
        mov  eax,DWORD PTR [ebp+0x24]
        lea  esi,[ebp+0x1d4]
        lea  ebx,[eax+0x7c]
        lea  edi,[esp+0x14]
        call FUN_004497d0
        call FUN_004243f0
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        lea  edi,[ebp+0x10]
        push  0x0
        mov  eax,edi
        mov  DWORD PTR [ebp+0x4],0xd
        call FUN_00405410
        mov  eax,ds:0x47770c
        call FUN_00421f60
        mov  eax,DWORD PTR [ebp+0x24]
        dec  eax
        je loc_00423991
        dec  eax
        jne loc_00423A0A
        push  0x0
        mov  eax,edi
        mov  DWORD PTR [ebp+0x4],0xd
        call FUN_00405410
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        jmp loc_00423A0A
    loc_00423991:
        push  0x0
        mov  eax,edi
        mov  DWORD PTR [ebp+0x4],0xa
        call FUN_00405410
        mov  eax,esi
        call FUN_004495e0
        lea  eax,[ebp+0x24]
        call FUN_0044be20
        mov  esi,0x1
        mov  DWORD PTR [ebp+0x2c],0x19
        mov  DWORD PTR [ebp+0xf4],esi
        mov  ecx,DWORD PTR [eax+0x8]
        test  ecx,ecx
        je loc_004239D6
        jg loc_004239D0
        dec  ecx
        mov  DWORD PTR [eax],ecx
        jmp loc_004239DC
    loc_004239D0:
        xor  ecx,ecx
        mov  DWORD PTR [eax],ecx
        jmp loc_004239DC
    loc_004239D6:
        mov  DWORD PTR [eax],0x0
    loc_004239DC:
        lea  edi,[ebp+0x1ec]
    loc_004239E2:
        push  esi
        lea  eax,[esp+0x1c]
        push  0x46e0c8
        push  eax
        call _sprintf
        add  esp,0xc
        lea  ecx,[esp+0x18]
        push  ecx
        call FUN_004296f0
        mov  DWORD PTR [edi],eax
        inc  esi
        add  edi,0x4
        cmp  esi,0x19
        jle loc_004239E2
    loc_00423A0A:
        test  BYTE PTR ds:0x474e36,0xa
        je loc_00424376
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        cmp  DWORD PTR [ebp+0x24],0x2
        je loc_00424376
        mov  eax,DWORD PTR [ebp+0x2c]
        test  eax,eax
        je loc_00423A4E
        cmp  eax,0x2
        jg loc_00423A44
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00423A55
    loc_00423A44:
        mov  eax,0x2
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00423A55
    loc_00423A4E:
        mov  DWORD PTR [ebp+0x24],0x2
    loc_00423A55:
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x24]
        add  si,0x7
        lea  eax,[ebp+0x1d4]
        call FUN_00449470
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x48]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
        cmp  DWORD PTR [ebp+0x14],0xa
        jl loc_00424376
        mov  edx,DWORD PTR [ebp+0x24]
        lea  esi,[ebp+0x24]
        mov  eax,0x10
        mov  ecx,0x474e30
        mov  DWORD PTR [esi+0x4],edx
        call FUN_0040ace0
        test  ax,ax
        je loc_00423AAF
        push  0xffffffff
        mov  eax,esi
        call FUN_0044bea0
    loc_00423AAF:
        mov  eax,0x20
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00423ACC
        push  0x1
        mov  eax,esi
        call FUN_0044bea0
    loc_00423ACC:
        mov  eax,DWORD PTR [esi+0x4]
        cmp  eax,DWORD PTR [esi]
        je loc_00423AE4
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_00423AE4:
        mov  eax,ds:0x474e36
        test  eax,0x1001
        je loc_00423C20
        push  0x0
        lea  eax,[ebp+0x10]
        mov  DWORD PTR [ebp+0x4],0xb
        call FUN_00405410
        mov  eax,DWORD PTR [ebp+0x104]
        test  eax,eax
        lea  ebx,[ebp+0xfc]
        je loc_00423B22
        jg loc_00423B1C
        dec  eax
        mov  DWORD PTR [ebx],eax
        jmp loc_00423B28
    loc_00423B1C:
        xor  eax,eax
        mov  DWORD PTR [ebx],eax
        jmp loc_00423B28
    loc_00423B22:
        mov  DWORD PTR [ebx],0x0
    loc_00423B28:
        mov  eax,ds:0x4746d8
        lea  edx,[eax+0x1]
    loc_00423B30:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00423B30
        sub  eax,edx
        mov  DWORD PTR [ebp+0x104],eax
        mov  eax,DWORD PTR [ebp+0x1e4]
        test  eax,eax
        mov  DWORD PTR [ebp+0x1cc],0x1
        je loc_00423B7C
        test  BYTE PTR ds:0x474ca0,0x10
        jne loc_00423B7C
        mov  esi,DWORD PTR ds:0x477838
        mov  ecx,DWORD PTR [esi+0x18]
        add  esi,0x18
        add  ecx,0xc
        push  ecx
        call FID_conflict:__time32
        mov  edx,DWORD PTR [esi]
        mov  DWORD PTR [edx+0x5c],0x8
        jmp loc_00423B9C
    loc_00423B7C:
        mov  esi,DWORD PTR ds:0x477838
        mov  eax,DWORD PTR [esi+0x18]
        add  esi,0x18
        add  eax,0xc
        push  eax
        call FID_conflict:__time32
        mov  ecx,DWORD PTR [esi]
        mov  edx,DWORD PTR ds:0x474c7c
        mov  DWORD PTR [ecx+0x5c],edx
    loc_00423B9C:
        mov  eax,ds:0x47783c
        lea  esi,[ebp+0x2b4]
        add  eax,0x1d878
        mov  edx,esi
        add  esp,0x4
        sub  edx,eax
    loc_00423BB3:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_00423BB3
        mov  edi,0x46e354
        mov  ecx,0x9
        xor  eax,eax
        mov  DWORD PTR [ebp+0x1e0],0x0
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        je loc_00423BE0
        push  0xffffffff
        mov  eax,ebx
        call FUN_0044bea0
    loc_00423BE0:
        mov  eax,0x8
    loc_00423BE5:
        cmp  BYTE PTR [eax+ebp*1+0x2b3],0x20
        jne loc_00423BF4
        dec  eax
        test  eax,eax
        jg loc_00423BE5
    loc_00423BF4:
        mov  DWORD PTR [ebp+0x1e0],eax
    loc_00423BFA:
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x48]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
    loc_00423C20:
        test  al,0xa
        je loc_00424376
        lea  ebx,[ebp+0x10]
        push  0x0
        mov  eax,ebx
        mov  DWORD PTR [ebp+0x4],0x8
        call FUN_00405410
        lea  edi,[ebp+0x1d4]
        mov  eax,edi
        call FUN_00449590
        mov  eax,esi
        call FUN_0044be70
        movsx esi,WORD PTR [esi]
        add  si,0x7
        mov  eax,edi
        mov  DWORD PTR [ebp+0x2c],0x3
        mov  DWORD PTR [ebp+0xf4],0x1
        call FUN_00449470
        lea  esi,[ebp+0x1ec]
        mov  DWORD PTR [esp+0x10],0x19
        nop
    loc_00423C80:
        mov  edi,DWORD PTR [esi]
        test  edi,edi
        je loc_00423C95
        push  edi
        call FUN_004294a0
        push  edi
        call _free
        add  esp,0x4
    loc_00423C95:
        mov  eax,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi],0x0
        add  esi,0x4
        dec  eax
        mov  DWORD PTR [esp+0x10],eax
        jne loc_00423C80
        push  0x0
        mov  eax,ebx
        mov  DWORD PTR [ebp+0x4],0x8
        call FUN_00405410
    loc_00423CB9:
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x48]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
        mov  eax,DWORD PTR [ebp+0x14]
        mov  ebx,0xa
        cmp  eax,ebx
        jl loc_00424376
        mov  ecx,DWORD PTR [ebp+0xfc]
        lea  esi,[ebp+0xfc]
        mov  DWORD PTR [esi+0x4],ecx
        mov  eax,0x10
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00423D1B
        push  0xfffffff3
        mov  eax,esi
        call FUN_0044bea0
    loc_00423D1B:
        mov  eax,0x20
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00423D38
        push  0xd
        mov  eax,esi
        call FUN_0044bea0
    loc_00423D38:
        mov  eax,0x40
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00423D67
        mov  eax,DWORD PTR [esi]
        cdq
        mov  ecx,0xd
        idiv  ecx
        mov  eax,esi
        test  edx,edx
        je loc_00423D60
        push  0xffffffff
        jmp loc_00423D62
    loc_00423D60:
        push  0xc
    loc_00423D62:
        call FUN_0044bea0
    loc_00423D67:
        mov  eax,0x80
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00423D97
        mov  eax,DWORD PTR [esi]
        cdq
        mov  ecx,0xd
        idiv  ecx
        mov  eax,esi
        cmp  edx,0xc
        je loc_00423D90
        push  0x1
        jmp loc_00423D92
    loc_00423D90:
        push  0xfffffff4
    loc_00423D92:
        call FUN_0044bea0
    loc_00423D97:
        mov  edx,DWORD PTR [esi+0x4]
        cmp  edx,DWORD PTR [esi]
        je loc_00423DAF
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_00423DAF:
        test  DWORD PTR ds:0x474e36,0x1001
        je loc_00423E07
        mov  edi,DWORD PTR ds:0x4746d8
        mov  eax,edi
        lea  edx,[eax+0x1]
    loc_00423DC6:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00423DC6
        mov  ecx,DWORD PTR [esi]
        sub  eax,edx
        lea  edx,[eax-0x3]
        cmp  ecx,edx
        jge loc_00423E53
        mov  edx,DWORD PTR [ebp+0x1e0]
        cmp  edx,0x8
        jge loc_00423DEF
        mov  cl,BYTE PTR [ecx+edi*1]
        mov  BYTE PTR [edx+ebp*1+0x2b4],cl
        jmp loc_00423E68
    loc_00423DEF:
        mov  al,BYTE PTR [ecx+edi*1]
        mov  BYTE PTR [edx+ebp*1+0x2b3],al
    loc_00423DF9:
        push  0x0
        mov  edi,ebx
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_00423E07:
        test  BYTE PTR ds:0x474e36,bl
        je loc_00424376
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  eax,DWORD PTR [ebp+0x1e0]
        test  eax,eax
        jne loc_00423F6F
        push  eax
        lea  eax,[ebp+0x10]
        mov  DWORD PTR [ebp+0x4],ebx
        call FUN_00405410
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x48]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
    loc_00423E53:
        jne loc_00423E9C
        mov  ecx,DWORD PTR [ebp+0x1e0]
        cmp  ecx,0x8
        jge loc_00423E8F
        mov  BYTE PTR [ecx+ebp*1+0x2b4],0x20
    loc_00423E68:
        mov  edx,DWORD PTR [ebp+0x1e0]
        inc  edx
        mov  ecx,edx
        cmp  ecx,0x8
        mov  DWORD PTR [ebp+0x1e0],edx
        jl loc_00423DF9
        lea  ecx,[eax-0x1]
        mov  edx,esi
        call FUN_0040ad20
        jmp loc_00423DF9
    loc_00423E8F:
        mov  BYTE PTR [ecx+ebp*1+0x2b3],0x20
        jmp loc_00423DF9
    loc_00423E9C:
        lea  edx,[eax-0x2]
        cmp  ecx,edx
        jne loc_00423EC5
        mov  eax,DWORD PTR [ebp+0x1e0]
        test  eax,eax
        je loc_00424376
        dec  eax
        mov  DWORD PTR [ebp+0x1e0],eax
        mov  BYTE PTR [eax+ebp*1+0x2b4],0x20
        jmp loc_00423CB9
    loc_00423EC5:
        dec  eax
        cmp  ecx,eax
        jne loc_00423DF9
        push  0x0
        mov  edi,0x2c
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  eax,DWORD PTR [ebp+0x24]
        inc  eax
        push  eax
        lea  ecx,[esp+0x1c]
        push  0x46e0c8
        push  ecx
        call _sprintf
        mov  edx,DWORD PTR [ebp+0x24]
        mov  esi,DWORD PTR [ebp+edx*4+0x1ec]
        add  esp,0xc
        call FUN_004297b0
        mov  ecx,DWORD PTR ds:0x477838
        lea  esi,[ebp+0x2b4]
        push  esi
        lea  edx,[esp+0x1c]
        call FUN_00429b60
        mov  edi,DWORD PTR [ebp+0x24]
        lea  eax,[esp+0x18]
        push  eax
        call FUN_004296f0
        mov  DWORD PTR [ebp+edi*4+0x1ec],eax
        push  0x0
        lea  eax,[ebp+0x10]
        mov  DWORD PTR [ebp+0x4],ebx
        call FUN_00405410
        mov  ecx,DWORD PTR ds:0x47783c
        add  ecx,0x1d878
        mov  eax,esi
        sub  ecx,esi
        nop
    loc_00423F50:
        mov  dl,BYTE PTR [eax]
        mov  BYTE PTR [ecx+eax*1],dl
        inc  eax
        test  dl,dl
        jne loc_00423F50
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x48]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
    loc_00423F6F:
        pop  edi
        dec  eax
        pop  esi
        mov  DWORD PTR [ebp+0x1e0],eax
        pop  ebx
        mov  BYTE PTR [eax+ebp*1+0x2b4],0x20
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x48]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
        cmp  DWORD PTR [ebp+0x14],0xa
        jl loc_00424376
        mov  eax,DWORD PTR [ebp+0x1e8]
        test  eax,eax
        mov  ebx,0x1
        jne loc_0042406F
        mov  ecx,DWORD PTR [ebp+0xfc]
        lea  esi,[ebp+0xfc]
        mov  DWORD PTR [esi+0x4],ecx
        mov  eax,0x10
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00423FDC
        push  0xfffffff3
        mov  eax,esi
        call FUN_0044bea0
    loc_00423FDC:
        mov  eax,0x20
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00423FF9
        push  0xd
        mov  eax,esi
        call FUN_0044bea0
    loc_00423FF9:
        mov  eax,0x40
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00424028
        mov  eax,DWORD PTR [esi]
        cdq
        mov  ecx,0xd
        idiv  ecx
        mov  eax,esi
        test  edx,edx
        je loc_00424021
        push  0xffffffff
        jmp loc_00424023
    loc_00424021:
        push  0xc
    loc_00424023:
        call FUN_0044bea0
    loc_00424028:
        mov  eax,0x80
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00424057
        mov  eax,DWORD PTR [esi]
        cdq
        mov  ecx,0xd
        idiv  ecx
        mov  eax,esi
        cmp  edx,0xc
        je loc_00424050
        push  ebx
        jmp loc_00424052
    loc_00424050:
        push  0xfffffff4
    loc_00424052:
        call FUN_0044bea0
    loc_00424057:
        mov  edx,DWORD PTR [esi+0x4]
        cmp  edx,DWORD PTR [esi]
        je loc_0042406F
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_0042406F:
        test  DWORD PTR ds:0x474e36,0x1001
        je loc_0042426D
        mov  eax,DWORD PTR [ebp+0x1e8]
        test  eax,eax
        jne loc_00424217
        mov  edi,DWORD PTR ds:0x4746d8
        mov  eax,edi
        lea  edx,[eax+0x1]
    loc_00424098:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00424098
        mov  ecx,DWORD PTR [ebp+0xfc]
        sub  eax,edx
        lea  edx,[ebp+0xfc]
        lea  esi,[eax-0x3]
        cmp  ecx,esi
        jge loc_004240DA
        mov  esi,DWORD PTR [ebp+0x1e0]
        cmp  esi,0x8
        jge loc_004240CB
        mov  cl,BYTE PTR [ecx+edi*1]
        mov  BYTE PTR [esi+ebp*1+0x2b4],cl
        jmp loc_004240EF
    loc_004240CB:
        mov  dl,BYTE PTR [ecx+edi*1]
        mov  BYTE PTR [esi+ebp*1+0x2b3],dl
        jmp loc_00424204
    loc_004240DA:
        jne loc_00424121
        mov  ecx,DWORD PTR [ebp+0x1e0]
        cmp  ecx,0x8
        jge loc_00424114
        mov  BYTE PTR [ecx+ebp*1+0x2b4],0x20
    loc_004240EF:
        mov  esi,DWORD PTR [ebp+0x1e0]
        inc  esi
        mov  ecx,esi
        cmp  ecx,0x8
        mov  DWORD PTR [ebp+0x1e0],esi
        jl loc_00424204
        lea  ecx,[eax-0x1]
        call FUN_0040ad20
        jmp loc_00424204
    loc_00424114:
        mov  BYTE PTR [ecx+ebp*1+0x2b3],0x20
        jmp loc_00424204
    loc_00424121:
        lea  edx,[eax-0x2]
        cmp  ecx,edx
        jne loc_0042414A
        mov  eax,DWORD PTR [ebp+0x1e0]
        test  eax,eax
        je loc_00424376
        dec  eax
        mov  DWORD PTR [ebp+0x1e0],eax
        mov  BYTE PTR [eax+ebp*1+0x2b4],0x20
        jmp loc_00424204
    loc_0042414A:
        dec  eax
        cmp  ecx,eax
        jne loc_00424204
        mov  ecx,DWORD PTR ds:0x474c68
        mov  eax,ds:0x474c6c
        mov  edi,DWORD PTR [ebp+0x24]
        lea  eax,[eax+ecx*2]
        add  eax,ecx
        mov  ecx,DWORD PTR ds:0x474c74
        imul  eax,eax,0x437c
        lea  ecx,[ecx+ecx*4]
        lea  ecx,[edi+ecx*2]
        mov  edi,DWORD PTR ds:0x47783c
        lea  esi,[ebp+0x2b4]
        lea  ecx,[ecx+ecx*2]
        add  eax,edi
        mov  edx,esi
        lea  ecx,[eax+ecx*8+0x1e]
        nop
    loc_00424190:
        mov  al,BYTE PTR [edx]
        inc  edx
        mov  BYTE PTR [ecx],al
        inc  ecx
        test  al,al
        jne loc_00424190
        lea  edx,[edi+0x1d878]
        mov  eax,esi
        sub  edx,esi
    loc_004241A4:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_004241A4
        lea  edi,[ebp+0x1d4]
        mov  eax,edi
        call FUN_00449590
        mov  DWORD PTR [ebp+0x4],0x8
        mov  DWORD PTR [ebp+0x2c],0x3
        mov  DWORD PTR [ebp+0xf4],ebx
        mov  eax,DWORD PTR [ebp+0x2c]
        test  eax,eax
        je loc_004241E5
        jg loc_004241DE
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_004241EC
    loc_004241DE:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_004241EC
    loc_004241E5:
        mov  DWORD PTR [ebp+0x24],0x0
    loc_004241EC:
        mov  eax,edi
        call FUN_0040c4d0
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x24]
        add  si,0x7
        mov  eax,edi
        call FUN_00449470
    loc_00424204:
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        jmp loc_0042426D
    loc_00424217:
        lea  edi,[ebp+0x1d4]
        mov  eax,edi
        call FUN_00449590
        mov  DWORD PTR [ebp+0x4],0x8
        mov  DWORD PTR [ebp+0x2c],0x3
        mov  DWORD PTR [ebp+0xf4],ebx
        mov  eax,DWORD PTR [ebp+0x2c]
        test  eax,eax
        je loc_0042424E
        jg loc_00424247
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00424255
    loc_00424247:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00424255
    loc_0042424E:
        mov  DWORD PTR [ebp+0x24],0x0
    loc_00424255:
        mov  eax,edi
        call FUN_0040c4d0
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x24]
        add  si,0x7
        mov  eax,edi
        call FUN_00449470
    loc_0042426D:
        test  BYTE PTR ds:0x474e36,0xa
        je loc_00424376
        mov  eax,DWORD PTR [ebp+0x24]
        test  eax,eax
        jl loc_004242CA
        mov  eax,DWORD PTR [ebp+0x1e0]
        test  eax,eax
        je loc_00424376
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  eax,DWORD PTR [ebp+0x1e0]
        pop  edi
        dec  eax
        pop  esi
        mov  DWORD PTR [ebp+0x1e0],eax
        pop  ebx
        mov  BYTE PTR [eax+ebp*1+0x2b4],0x20
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x48]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
    loc_004242CA:
        mov  DWORD PTR [ebp+0x4],0x8
        mov  DWORD PTR [ebp+0x2c],0x3
        mov  eax,DWORD PTR [ebp+0x2c]
        test  eax,eax
        je loc_00424307
        jg loc_004242F4
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        push  0x0
        lea  eax,[ebp+0x10]
        call FUN_00405410
        jmp loc_00423BFA
    loc_004242F4:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        push  eax
        lea  eax,[ebp+0x10]
        call FUN_00405410
        jmp loc_00423BFA
    loc_00424307:
        push  0x0
        lea  eax,[ebp+0x10]
        mov  DWORD PTR [ebp+0x24],0x0
        call FUN_00405410
        jmp loc_00423BFA
        cmp  DWORD PTR [ebp+0x14],0xc
        jl loc_00424376
        mov  esi,ebp
        call FUN_00423510
        mov  eax,DWORD PTR [ebp+0x24]
        sub  eax,0x0
        mov  DWORD PTR [ebp+0x4],0x15
        je loc_00424360
        dec  eax
        je loc_0042433F
        dec  eax
        jne loc_00424376
    loc_0042433F:
        push  0x4
        mov  eax,0x491c28
        call FUN_0040ac90
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x48]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
    loc_00424360:
        mov  edx,DWORD PTR [ebp+0x1e4]
        neg  edx
        sbb  edx,edx
        and  edx,0xfffffffd
        add  edx,0xd
        mov  DWORD PTR ds:0x491fb8,edx
    loc_00424376:
        pop  edi
        pop  esi
        pop  ebx
    loc_00424379:
        mov  ecx,DWORD PTR [esp+0x4c]
        pop  ebp
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
    }
}
