// 00417C80: FUN_00417c80
// Original size: 1120 bytes, actual code: 309 instructions
extern "C" void FUN_00402440(void);
extern "C" void FUN_00405620(void);
extern "C" void FUN_00405f70(void);
extern "C" void FUN_00408af0(void);
extern "C" void FUN_00409f90(void);
extern "C" void FUN_0040af00(void);
extern "C" void FUN_0040c540(void);
extern "C" void FUN_0040d530(void);
extern "C" void FUN_00414570(void);
extern "C" void FUN_004145f0(void);
extern "C" void FUN_00418a90(void);
extern "C" void FUN_00418ee0(void);
extern "C" void FUN_0041adf0(void);
extern "C" void FUN_0041c1c0(void);
extern "C" void FUN_00422220(void);
extern "C" void FUN_00424ed0(void);
extern "C" void FUN_004294a0(void);
extern "C" void FUN_0042b1e0(void);
extern "C" void FUN_0042b570(void);
extern "C" void FUN_0043e460(void);
extern "C" void FUN_00448d50(void);
extern "C" void FUN_00449f60(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00417c80(void) {
    __asm {
        sub  esp,0x10
        push  ebx
        mov  ebx,DWORD PTR ds:0x47783c
        push  ebp
        push  esi
        push  edi
        call FUN_0042b1e0
        mov  edx,DWORD PTR ds:0x474ca0
        mov  eax,ds:0x491fb8
        and  edx,0xfffffffc
        cmp  eax,0xa
        mov  DWORD PTR ds:0x474ca0,edx
        mov  DWORD PTR ds:0x476f78,0x3f800000
        mov  ebx,0x2
        jne loc_00417D26
        mov  ecx,DWORD PTR ds:0x4776e0
        mov  edx,DWORD PTR [ecx+0x89a4]
        test  edx,edx
        lea  esi,[ecx+0x89a4]
        mov  DWORD PTR [esp+0x14],0x43f00000
        mov  DWORD PTR [esp+0x18],0x43c40000
        mov  DWORD PTR [esp+0x1c],0x0
        jne loc_00417D08
        mov  eax,DWORD PTR [ecx+0x8994]
        push  0x6
        lea  ecx,[esp+0x14]
        push  ecx
        push  eax
        lea  edi,[esp+0x20]
        call FUN_00448d50
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [esi],edx
        mov  eax,ds:0x491fb8
    loc_00417D08:
        mov  ecx,DWORD PTR ds:0x474c80
        cmp  ecx,DWORD PTR ds:0x474c7c
        jne loc_00417DB5
        or   DWORD PTR ds:0x474ca0,0x1
        jmp loc_00417DB5
    loc_00417D26:
        cmp  eax,0xb
        jne loc_00417D49
        mov  esi,DWORD PTR ds:0x4776e0
        push  0x43d00000
        push  0x43600000
        call FUN_0040c540
        mov  eax,ds:0x474ca0
        or   eax,ebx
        jmp loc_00417DAB
    loc_00417D49:
        cmp  eax,0x4
        je loc_00417D53
        cmp  eax,0xf
        jne loc_00417D6A
    loc_00417D53:
        mov  esi,DWORD PTR ds:0x4776e0
        push  0x43c40000
        push  0x43f00000
        call FUN_0040c540
        jmp loc_00417DB0
    loc_00417D6A:
        cmp  eax,0xd
        jne loc_00417DB5
        mov  esi,DWORD PTR ds:0x4776e0
        push  0x43c40000
        push  0x43f00000
        call FUN_0040c540
        mov  edx,DWORD PTR ds:0x474c80
        cmp  edx,DWORD PTR ds:0x474c7c
        je loc_00417DA3
        mov  eax,0x474c40
        call FUN_00418a90
        or   DWORD PTR ds:0x474ca0,0x8
    loc_00417DA3:
        mov  eax,ds:0x474ca0
        or   eax,0x1
    loc_00417DAB:
        mov  ds:0x474ca0,eax
    loc_00417DB0:
        mov  eax,ds:0x491fb8
    loc_00417DB5:
        test  BYTE PTR ds:0x474ca0,bl
        jne loc_00417EE7
        cmp  eax,0xe
        je loc_00417DE4
        cmp  eax,0xf
        je loc_00417DE4
        mov  esi,DWORD PTR ds:0x477838
        test  esi,esi
        je loc_00417DE4
        push  esi
        call FUN_004294a0
        push  esi
        call _free
        add  esp,0x4
    loc_00417DE4:
        mov  esi,DWORD PTR ds:0x4776e8
        test  esi,esi
        je loc_00417DFD
        push  esi
        call FUN_00402440
        push  esi
        call _free
        add  esp,0x4
    loc_00417DFD:
        mov  esi,DWORD PTR ds:0x4776e4
        test  esi,esi
        je loc_00417E16
        push  esi
        call FUN_00402440
        push  esi
        call _free
        add  esp,0x4
    loc_00417E16:
        mov  esi,DWORD PTR ds:0x477830
        test  esi,esi
        je loc_00417E2F
        push  esi
        call FUN_00422220
        push  esi
        call _free
        add  esp,0x4
    loc_00417E2F:
        mov  esi,DWORD PTR ds:0x47770c
        test  esi,esi
        je loc_00417E48
        push  esi
        call FUN_004145f0
        push  esi
        call _free
        add  esp,0x4
    loc_00417E48:
        mov  esi,DWORD PTR ds:0x477834
        test  esi,esi
        je loc_00417E61
        push  esi
        call FUN_00424ed0
        push  esi
        call _free
        add  esp,0x4
    loc_00417E61:
        mov  esi,DWORD PTR ds:0x4776f0
        test  esi,esi
        je loc_00417E7A
        push  esi
        call FUN_00405f70
        push  esi
        call _free
        add  esp,0x4
    loc_00417E7A:
        mov  esi,DWORD PTR ds:0x477818
        test  esi,esi
        je loc_00417E93
        push  esi
        call FUN_0041adf0
        push  esi
        call _free
        add  esp,0x4
    loc_00417E93:
        mov  esi,DWORD PTR ds:0x47781c
        test  esi,esi
        je loc_00417EAC
        push  esi
        call FUN_0041c1c0
        push  esi
        call _free
        add  esp,0x4
    loc_00417EAC:
        mov  esi,DWORD PTR ds:0x477814
        test  esi,esi
        je loc_00417EC5
        push  esi
        call FUN_00418ee0
        push  esi
        call _free
        add  esp,0x4
    loc_00417EC5:
        mov  esi,DWORD PTR ds:0x477840
        test  esi,esi
        je loc_00417F80
        push  esi
        call FUN_0042b570
        push  esi
        call _free
        add  esp,0x4
        jmp loc_00417F80
    loc_00417EE7:
        mov  ebx,DWORD PTR ds:0x47770c
        call FUN_00414570
        mov  esi,DWORD PTR ds:0x4776e4
        test  esi,esi
        je loc_00417F0B
        push  esi
        call FUN_00402440
        push  esi
        call _free
        add  esp,0x4
    loc_00417F0B:
        mov  eax,ds:0x4776e8
        mov  ds:0x4776e4,eax
        mov  eax,ds:0x477830
        mov  ecx,DWORD PTR [eax+0x8]
        test  ecx,ecx
        mov  edx,0xfffffffd
        je loc_00417F29
        and  DWORD PTR [ecx+0x4],edx
    loc_00417F29:
        mov  ecx,DWORD PTR [eax+0xc]
        test  ecx,ecx
        je loc_00417F35
        mov  eax,ecx
        and  DWORD PTR [eax+0x4],edx
    loc_00417F35:
        mov  eax,ds:0x4776f0
        mov  ecx,DWORD PTR [eax+0x8]
        test  ecx,ecx
        je loc_00417F44
        and  DWORD PTR [ecx+0x4],edx
    loc_00417F44:
        mov  ecx,DWORD PTR [eax+0xc]
        test  ecx,ecx
        je loc_00417F50
        mov  eax,ecx
        and  DWORD PTR [eax+0x4],edx
    loc_00417F50:
        mov  eax,ds:0x477838
        mov  ecx,DWORD PTR [eax+0x1cc]
        test  ecx,ecx
        je loc_00417F62
        and  DWORD PTR [ecx+0x4],edx
    loc_00417F62:
        mov  ecx,DWORD PTR [eax+0xc]
        test  ecx,ecx
        je loc_00417F6E
        mov  eax,ecx
        and  DWORD PTR [eax+0x4],edx
    loc_00417F6E:
        mov  edi,DWORD PTR ds:0x477818
        xor  eax,eax
        mov  ecx,0x873a8
        add  edi,0x14
        rep stosd
    loc_00417F80:
        test  BYTE PTR ds:0x474ca0,0x9
        jne loc_00417FA5
        mov  esi,DWORD PTR ds:0x477704
        test  esi,esi
        je loc_00417FB1
        mov  eax,esi
        call FUN_0040d530
        push  esi
        call _free
        add  esp,0x4
        jmp loc_00417FB1
    loc_00417FA5:
        mov  ecx,DWORD PTR ds:0x477704
        push  ecx
        call FUN_00409f90
    loc_00417FB1:
        mov  esi,DWORD PTR ds:0x4776fc
        test  esi,esi
        je loc_00417FCA
        push  esi
        call FUN_0040af00
        push  esi
        call _free
        add  esp,0x4
    loc_00417FCA:
        mov  esi,DWORD PTR ds:0x4776ec
        test  esi,esi
        je loc_00417FE3
        push  esi
        call FUN_00405620
        push  esi
        call _free
        add  esp,0x4
    loc_00417FE3:
        mov  esi,DWORD PTR ds:0x4776f4
        test  esi,esi
        je loc_00417FFC
        push  esi
        call FUN_00408af0
        push  esi
        call _free
        add  esp,0x4
    loc_00417FFC:
        mov  edx,DWORD PTR [esp+0x24]
        mov  esi,DWORD PTR [edx+0x8]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        mov  ebx,DWORD PTR ds:0x4660b0
        mov  ebp,DWORD PTR ds:0x4660b4
        je loc_0041803C
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0041803C:
        mov  eax,DWORD PTR [esp+0x24]
        mov  esi,DWORD PTR [eax+0xc]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_00418070
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_00418070:
        test  BYTE PTR ds:0x474ca0,0x22
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR ds:0x477810,0x0
        pop  ebx
        jne loc_004180A7
        test  BYTE PTR ds:0x491d78,0x10
        mov  edx,0x46df98
        push  0x0
        mov  eax,0x492590
        je loc_004180A0
        push  0x4
        jmp loc_004180A2
    loc_004180A0:
        push  0x3
    loc_004180A2:
        call FUN_0043e460
    loc_004180A7:
        mov  eax,ds:0x474ca0
        and  al,0x1
        neg  al
        mov  DWORD PTR ds:0x4918a4,0x1
        sbb  eax,eax
        and  eax,0x1000000
        add  eax,0xff000000
        mov  ds:0x4923a8,eax
        add  esp,0x10
        ret  0x4
    }
}
