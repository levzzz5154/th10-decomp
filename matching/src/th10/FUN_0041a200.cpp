// 0041A200: FUN_0041a200
// Original size: 2320 bytes, actual code: 766 instructions
extern "C" void FUN_0044b620(void);
extern "C" void FUN_0044b740(void);
extern "C" void _free(void);
extern "C" void _malloc(void);
extern "C" void FUN_00452abc(void);
extern "C" void _sprintf(void);
extern "C" void FID_conflict:__time32(void);
extern "C" void _localtime(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0041a200(void) {
    __asm {
        push  ebp
        mov  ebp,esp
        and  esp,0xfffffff8
        sub  esp,0x4c
        push  ebx
        push  esi
        push  edi
        push  0x1000
        call _malloc
        push  0x46d574
        mov  edi,eax
        call FUN_00452abc
        mov  eax,DWORD PTR [ebp+0xc]
        add  esp,0x8
        push  eax
        call FUN_0044b620
        test  eax,eax
        jne loc_0041AA79
        push  0x46d534
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0x8
        lea  edx,[eax+0x1]
        nop
    loc_0041A250:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A250
        sub  eax,edx
        mov  esi,eax
        mov  edx,edi
        call FUN_0044b740
        push  0x46d510
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0x8
        lea  edx,[eax+0x1]
    loc_0041A275:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A275
        sub  eax,edx
        mov  esi,eax
        mov  edx,edi
        call FUN_0044b740
        push  0x46d50c
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0x8
        lea  edx,[eax+0x1]
        lea  ebx,[ebx+0x0]
    loc_0041A2A0:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A2A0
        sub  eax,edx
        mov  esi,eax
        mov  edx,edi
        call FUN_0044b740
        push  0x46d4d8
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0x8
        lea  edx,[eax+0x1]
    loc_0041A2C5:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A2C5
        sub  eax,edx
        mov  esi,eax
        mov  edx,edi
        call FUN_0044b740
        push  0x46d490
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0x8
        lea  edx,[eax+0x1]
        lea  ebx,[ebx+0x0]
    loc_0041A2F0:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A2F0
        sub  eax,edx
        mov  esi,eax
        mov  edx,edi
        call FUN_0044b740
        push  0x46d50c
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0x8
        lea  edx,[eax+0x1]
    loc_0041A315:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A315
        sub  eax,edx
        mov  esi,eax
        mov  edx,edi
        call FUN_0044b740
        lea  ecx,[esp+0x18]
        push  ecx
        call FID_conflict:__time32
        lea  edx,[esp+0x1c]
        push  edx
        call _localtime
        mov  ecx,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR [eax+0x8]
        push  ecx
        mov  ecx,DWORD PTR [eax+0xc]
        push  edx
        mov  edx,DWORD PTR [eax+0x10]
        mov  eax,DWORD PTR [eax+0x14]
        push  ecx
        inc  edx
        push  edx
        add  eax,0x76c
        push  eax
        push  0x46d440
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0x24
        lea  edx,[eax+0x1]
    loc_0041A368:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A368
        sub  eax,edx
        mov  esi,eax
        mov  edx,edi
        call FUN_0044b740
        push  0x46d434
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0x8
        lea  edx,[eax+0x1]
        nop
    loc_0041A390:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A390
        sub  eax,edx
        mov  esi,eax
        mov  edx,edi
        call FUN_0044b740
        push  0x46d654
        push  0x46d420
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0xc
        lea  edx,[eax+0x1]
        lea  ebx,[ebx+0x0]
    loc_0041A3C0:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A3C0
        sub  eax,edx
        mov  esi,eax
        mov  edx,edi
        call FUN_0044b740
        mov  ecx,DWORD PTR [ebp+0x8]
        add  ecx,0x7c
        mov  DWORD PTR [esp+0xc],0x0
        mov  DWORD PTR [esp+0x14],ecx
    loc_0041A3E4:
        mov  edx,DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [edx]
        test  eax,eax
        mov  DWORD PTR [esp+0x10],0x0
        je loc_0041AA5C
        lea  ebx,[ebx+0x0]
    loc_0041A400:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  ebx,DWORD PTR [eax]
        mov  eax,DWORD PTR [ebx+0x70]
        test  eax,eax
        mov  DWORD PTR [esp+0x18],ecx
        jne loc_0041A417
        mov  eax,ecx
        jmp loc_0041A9F0
    loc_0041A417:
        mov  eax,DWORD PTR [esp+0x10]
        test  eax,eax
        jne loc_0041A4E0
        push  0x46d3f8
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0x8
        lea  edx,[eax+0x1]
    loc_0041A436:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A436
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A47F
        push  0x0
        lea  ecx,[esp+0x20]
        push  ecx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x1c]
        je loc_0041A47F
        mov  edx,DWORD PTR ds:0x474c38
        push  edx
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A47F:
        mov  eax,DWORD PTR [esp+0xc]
        push  eax
        push  0x46d3e8
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0xc
        lea  edx,[eax+0x1]
    loc_0041A497:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A497
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A4E0
        push  0x0
        lea  ecx,[esp+0x24]
        push  ecx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x20]
        je loc_0041A4E0
        mov  edx,DWORD PTR ds:0x474c38
        push  edx
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A4E0:
        mov  eax,DWORD PTR [esp+0xc]
        push  eax
        push  0x46d3e0
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0xc
        lea  edx,[eax+0x1]
    loc_0041A4F8:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A4F8
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A542
        push  0x0
        lea  ecx,[esp+0x28]
        push  ecx
        push  esi
        push  edi
        mov  edx,eax
        push  edx
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x24]
        je loc_0041A542
        mov  eax,ds:0x474c38
        push  eax
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A542:
        mov  eax,DWORD PTR [ebx+0x70]
        test  eax,eax
        jle loc_0041A558
        push  eax
        push  0x46d3d0
        push  edi
        call _sprintf
        add  esp,0xc
    loc_0041A558:
        mov  eax,edi
        lea  edx,[eax+0x1]
        nop
    loc_0041A560:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A560
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A5AA
        push  0x0
        lea  ecx,[esp+0x2c]
        push  ecx
        push  esi
        push  edi
        mov  edx,eax
        push  edx
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x28]
        je loc_0041A5AA
        mov  eax,ds:0x474c38
        push  eax
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A5AA:
        lea  ecx,[ebx+0x1c]
        push  ecx
        push  0x46d3c0
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0xc
        lea  edx,[eax+0x1]
    loc_0041A5C1:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A5C1
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A609
        push  0x0
        lea  edx,[esp+0x30]
        push  edx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x2c]
        je loc_0041A609
        mov  eax,ds:0x474c38
        push  eax
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A609:
        fld  DWORD PTR [ebx+0x4]
        call FUN_00463b2c
        fld  DWORD PTR [ebx]
        push  eax
        call FUN_00463b2c
        push  eax
        push  0x46d3ac
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0x10
        lea  edx,[eax+0x1]
        nop
    loc_0041A630:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A630
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A679
        push  0x0
        lea  ecx,[esp+0x34]
        push  ecx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x30]
        je loc_0041A679
        mov  edx,DWORD PTR ds:0x474c38
        push  edx
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A679:
        mov  eax,DWORD PTR [ebx+0x60]
        push  eax
        push  0x46d39c
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0xc
        lea  edx,[eax+0x1]
    loc_0041A690:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A690
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A6D9
        push  0x0
        lea  ecx,[esp+0x38]
        push  ecx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x34]
        je loc_0041A6D9
        mov  edx,DWORD PTR ds:0x474c38
        push  edx
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A6D9:
        mov  ecx,DWORD PTR [ebx+0x68]
        xor  eax,eax
        mov  edi,edi
    loc_0041A6E0:
        cmp  DWORD PTR [eax*8+0x4744b4],ecx
        je loc_0041AAAF
        inc  eax
        cmp  eax,0x3d
        jl loc_0041A6E0
        xor  eax,eax
    loc_0041A6F5:
        push  eax
        push  0x46d38c
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0xc
        lea  edx,[eax+0x1]
        nop
    loc_0041A710:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A710
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A759
        push  0x0
        lea  ecx,[esp+0x3c]
        push  ecx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x38]
        je loc_0041A759
        mov  edx,DWORD PTR ds:0x474c38
        push  edx
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A759:
        mov  ecx,DWORD PTR [ebx+0x64]
        xor  eax,eax
        mov  edi,edi
    loc_0041A760:
        cmp  DWORD PTR [eax*8+0x474498],ecx
        je loc_0041AABB
        inc  eax
        cmp  eax,0x3
        jl loc_0041A760
        xor  eax,eax
    loc_0041A775:
        push  eax
        push  0x46d37c
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0xc
        lea  edx,[eax+0x1]
        nop
    loc_0041A790:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A790
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A7D9
        push  0x0
        lea  ecx,[esp+0x40]
        push  ecx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x3c]
        je loc_0041A7D9
        mov  edx,DWORD PTR ds:0x474c38
        push  edx
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A7D9:
        mov  eax,DWORD PTR [ebx+0x6c]
        push  eax
        push  0x46d36c
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0xc
        lea  edx,[eax+0x1]
    loc_0041A7F0:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A7F0
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A839
        push  0x0
        lea  ecx,[esp+0x44]
        push  ecx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x40]
        je loc_0041A839
        mov  edx,DWORD PTR ds:0x474c38
        push  edx
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A839:
        movzx eax,BYTE PTR [ebx+0x87]
        push  eax
        push  0x46d35c
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0xc
        lea  edx,[eax+0x1]
    loc_0041A854:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A854
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A89D
        push  0x0
        lea  ecx,[esp+0x48]
        push  ecx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x44]
        je loc_0041A89D
        mov  edx,DWORD PTR ds:0x474c38
        push  edx
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A89D:
        movzx eax,BYTE PTR [ebx+0x84]
        movzx ecx,BYTE PTR [ebx+0x85]
        movzx edx,BYTE PTR [ebx+0x86]
        push  eax
        push  ecx
        push  edx
        push  0x46d344
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0x14
        lea  edx,[eax+0x1]
    loc_0041A8C8:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A8C8
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A911
        push  0x0
        lea  ecx,[esp+0x4c]
        push  ecx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x48]
        je loc_0041A911
        mov  edx,DWORD PTR ds:0x474c38
        push  edx
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A911:
        fld  DWORD PTR [ebx+0x7c]
        sub  esp,0x8
        fstp  QWORD PTR [esp]
        push  0x46d334
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0x10
        lea  edx,[eax+0x1]
        nop
    loc_0041A930:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A930
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A979
        push  0x0
        lea  ecx,[esp+0x50]
        push  ecx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x4c]
        je loc_0041A979
        mov  edx,DWORD PTR ds:0x474c38
        push  edx
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A979:
        mov  eax,DWORD PTR [esp+0xc]
        push  eax
        push  0x46d32c
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0xc
        lea  edx,[eax+0x1]
    loc_0041A991:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041A991
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041A9DA
        push  0x0
        lea  ecx,[esp+0x54]
        push  ecx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x50]
        je loc_0041A9DA
        mov  edx,DWORD PTR ds:0x474c38
        push  edx
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041A9DA:
        mov  eax,DWORD PTR [esp+0x10]
        inc  eax
        cmp  eax,0xff
        mov  DWORD PTR [esp+0x10],eax
        jge loc_0041A9F8
        mov  eax,DWORD PTR [esp+0x18]
        mov  ecx,eax
    loc_0041A9F0:
        test  ecx,ecx
        jne loc_0041A400
    loc_0041A9F8:
        mov  eax,DWORD PTR [esp+0x10]
        test  eax,eax
        je loc_0041AA5C
        push  0x46d320
        push  edi
        call _sprintf
        mov  eax,edi
        add  esp,0x8
        lea  edx,[eax+0x1]
    loc_0041AA13:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0041AA13
        sub  eax,edx
        mov  esi,eax
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041AA5C
        push  0x0
        lea  ecx,[esp+0x58]
        push  ecx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x54]
        je loc_0041AA5C
        mov  edx,DWORD PTR ds:0x474c38
        push  edx
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041AA5C:
        mov  eax,DWORD PTR [esp+0xc]
        mov  edx,DWORD PTR [esp+0x14]
        inc  eax
        add  edx,0xc
        cmp  eax,0x8
        mov  DWORD PTR [esp+0xc],eax
        mov  DWORD PTR [esp+0x14],edx
        jl loc_0041A3E4
    loc_0041AA79:
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0041AA9B
        push  eax
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0041AA9B:
        push  edi
        call _free
        add  esp,0x4
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebx
        mov  esp,ebp
        pop  ebp
        ret  0x8
    loc_0041AAAF:
        mov  eax,DWORD PTR [eax*8+0x4744b0]
        jmp loc_0041A6F5
    loc_0041AABB:
        mov  eax,DWORD PTR [eax*8+0x474494]
        jmp loc_0041A775
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        mov  eax,ds:0x474c7c
        lea  eax,[eax+eax*2]
        mov  eax,DWORD PTR [ecx+eax*4+0x7c]
        test  eax,eax
        je loc_0041AAF6
    loc_0041AAE0:
        mov  edx,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax+0x70]
        test  ecx,ecx
        jle loc_0041AAF0
        dec  ecx
        mov  DWORD PTR [eax+0x70],ecx
    loc_0041AAF0:
        test  edx,edx
        mov  eax,edx
        jne loc_0041AAE0
    loc_0041AAF6:
        ret
    }
}
