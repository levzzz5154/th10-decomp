// 0042CB60: FUN_0042cb60
// Original size: 496 bytes, actual code: 143 instructions
extern "C" void FUN_004294a0(void);
extern "C" void FUN_00447810(void);
extern "C" void FUN_00449f60(void);
extern "C" void FUN_0044c150(void);
extern "C" void _free(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0042cb60(void) {
    __asm {
        push  0xffffffff
        push  0x46562e
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  edi,DWORD PTR [esp+0x24]
        mov  DWORD PTR [edi],0x46ecf0
        lea  esi,[edi+0x5ab0]
        mov  DWORD PTR [esp+0x1c],0x0
        mov  DWORD PTR [esp+0x10],esi
        call FUN_0044c150
        mov  edi,DWORD PTR [edi+0xc]
        test  edi,edi
        mov  ebx,DWORD PTR ds:0x491be4
        mov  esi,DWORD PTR ds:0x4660b0
        mov  ebp,DWORD PTR ds:0x4660b4
        je loc_0042CBD7
        push  0x492274
        call  esi
        inc  BYTE PTR ds:0x49231c
        mov  ecx,edi
        mov  edx,ebx
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0042CBD7:
        mov  eax,DWORD PTR [esp+0x24]
        mov  edi,DWORD PTR [eax+0x10]
        test  edi,edi
        mov  ebx,DWORD PTR ds:0x491be4
        je loc_0042CC0B
        push  0x492274
        call  esi
        inc  BYTE PTR ds:0x49231c
        mov  ecx,edi
        mov  edx,ebx
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0042CC0B:
        mov  ebx,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ebx+0x3ad0d0]
        add  ebx,0x3ad0d0
        xor  ebp,ebp
        cmp  edi,ebp
        je loc_0042CC35
        call FUN_00447810
        mov  ecx,DWORD PTR [ebx]
        push  ecx
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebx],ebp
    loc_0042CC35:
        mov  ebx,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ebx+0x3ad0d4]
        add  ebx,0x3ad0d4
        cmp  edi,ebp
        je loc_0042CC5D
        call FUN_00447810
        mov  edx,DWORD PTR [ebx]
        push  edx
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebx],ebp
    loc_0042CC5D:
        mov  ebx,DWORD PTR [esp+0x24]
        add  ebx,0x59e4
        mov  esi,0x32
        nop
    loc_0042CC70:
        mov  edi,DWORD PTR [ebx]
        cmp  edi,ebp
        je loc_0042CC85
        push  edi
        call FUN_004294a0
        push  edi
        call _free
        add  esp,0x4
    loc_0042CC85:
        add  ebx,0x4
        dec  esi
        jne loc_0042CC70
        mov  esi,DWORD PTR [esp+0x24]
        mov  ecx,DWORD PTR [esi+0x5d0]
        cmp  ecx,ebp
        je loc_0042CD04
        mov  edx,DWORD PTR ds:0x491c10
        mov  eax,DWORD PTR [edx+0x72dad4]
        cmp  eax,ebp
        je loc_0042CCBD
        nop
    loc_0042CCB0:
        mov  edi,DWORD PTR [eax]
        cmp  DWORD PTR [edi],ecx
        je loc_0042CCD6
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebp
        jne loc_0042CCB0
    loc_0042CCBD:
        mov  eax,DWORD PTR [edx+0x72dadc]
        cmp  eax,ebp
        je loc_0042CD04
    loc_0042CCC7:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_0042CCD6
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebp
        jne loc_0042CCC7
        jmp loc_0042CD04
    loc_0042CCD6:
        mov  eax,DWORD PTR [eax]
        cmp  eax,ebp
        je loc_0042CD04
        cmp  DWORD PTR [eax+0x18],ebp
        mov  ecx,0x1
        mov  WORD PTR [eax+0x304],cx
        jne loc_0042CD04
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,ebp
        je loc_0042CD04
    loc_0042CCF4:
        mov  edx,DWORD PTR [eax]
        mov  WORD PTR [edx+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebp
        jne loc_0042CCF4
    loc_0042CD04:
        mov  eax,DWORD PTR [esi+0x5aac]
        cmp  eax,ebp
        je loc_0042CD21
        push  eax
        call _free
        mov  eax,DWORD PTR [esp+0x28]
        add  esp,0x4
        mov  DWORD PTR [eax+0x5aac],ebp
    loc_0042CD21:
        mov  esi,DWORD PTR [esp+0x10]
        mov  DWORD PTR ds:0x47784c,ebp
        mov  DWORD PTR [esi],0x4703e4
        call FUN_0044c150
        mov  ecx,DWORD PTR [esp+0x14]
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret  0x4
    }
}
