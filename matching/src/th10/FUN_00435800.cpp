// 00435800: FUN_00435800
// Original size: 224 bytes, actual code: 66 instructions
extern "C" void FUN_00434dd0(void);
extern "C" void FUN_00435370(void);
extern "C" void FUN_00435580(void);
extern "C" void FUN_004356f0(void);
extern "C" void FUN_00452730(void);

extern "C" __declspec(naked) void FUN_00435800(void) {
    __asm {
        mov  eax,fs:0x0
        push  0xffffffff
        push  0x4653a8
        push  eax
        mov  DWORD PTR fs:0x0,esp
        sub  esp,0xc
        push  esi
        push  edi
        mov  esi,ecx
        call FUN_004356f0
        mov  edi,eax
        test  edi,edi
        je loc_00435859
        push  0x2f
        push  esi
        call FUN_00452730
        add  esp,0x8
        test  eax,eax
        lea  ecx,[eax+0x1]
        jne loc_0043583B
        mov  ecx,esi
    loc_0043583B:
        mov  eax,DWORD PTR [esp+0x24]
        push  eax
        push  edi
        call FUN_00434dd0
        pop  edi
        pop  esi
        mov  ecx,DWORD PTR [esp+0xc]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x18
        ret  0x4
    loc_00435859:
        mov  edi,0x46f230
        mov  DWORD PTR [esp+0x8],edi
        mov  DWORD PTR [esp+0xc],0xffffffff
        mov  DWORD PTR [esp+0x10],0x0
        mov  DWORD PTR [esp+0x1c],0x0
        mov  ecx,DWORD PTR ds:0x474908
        push  ecx
        push  esi
        lea  ecx,[esp+0x10]
        call FUN_00435370
        mov  eax,DWORD PTR [esp+0xc]
        cmp  eax,0xffffffff
        jne loc_00435898
        xor  eax,eax
        jmp loc_004358A1
    loc_00435898:
        push  0x0
        push  eax
        call  DWORD PTR ds:0x4660d8
    loc_004358A1:
        push  eax
        lea  ecx,[esp+0xc]
        call FUN_00435580
        mov  esi,eax
        mov  eax,DWORD PTR [esp+0xc]
        cmp  eax,0xffffffff
        mov  DWORD PTR [esp+0x8],edi
        je loc_004358C1
        push  eax
        call  DWORD PTR ds:0x4660cc
    loc_004358C1:
        mov  ecx,DWORD PTR [esp+0x14]
        pop  edi
        mov  eax,esi
        pop  esi
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x18
        ret  0x4
    }
}
