// 0041FB50: FUN_0041fb50
// Original size: 432 bytes, actual code: 119 instructions
extern "C" void FUN_00401260(void);
extern "C" void FUN_0041f930(void);
extern "C" void FUN_0042b1e0(void);
extern "C" void FUN_00447810(void);
extern "C" void FUN_00449f60(void);
extern "C" void FUN_0044c150(void);
extern "C" void _free(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0041fb50(void) {
    __asm {
        push  0xffffffff
        push  0x465696
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  DWORD PTR [esp+0x1c],0x1
        mov  edi,DWORD PTR [esp+0x24]
        lea  esi,[edi+0x10]
        mov  DWORD PTR [esp+0x10],esi
        call FUN_0044c150
        mov  edi,DWORD PTR [edi+0x8]
        test  edi,edi
        mov  ebx,DWORD PTR ds:0x491be4
        mov  esi,DWORD PTR ds:0x4660b0
        mov  ebp,DWORD PTR ds:0x4660b4
        je loc_0041FBBE
        push  0x492274
        call  esi
        inc  BYTE PTR ds:0x49231c
        mov  ecx,edi
        mov  edx,ebx
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0041FBBE:
        mov  eax,DWORD PTR [esp+0x24]
        mov  edi,DWORD PTR [eax+0xc]
        test  edi,edi
        mov  ebx,DWORD PTR ds:0x491be4
        je loc_0041FBF2
        push  0x492274
        call  esi
        inc  BYTE PTR ds:0x49231c
        mov  ecx,edi
        mov  edx,ebx
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0041FBF2:
        call FUN_0041f930
        mov  ebx,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ebx+0x3ad070]
        add  ebx,0x3ad070
        xor  ebp,ebp
        cmp  edi,ebp
        je loc_0041FC21
        call FUN_00447810
        mov  ecx,DWORD PTR [ebx]
        push  ecx
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebx],ebp
    loc_0041FC21:
        mov  esi,DWORD PTR ds:0x4776e0
        cmp  esi,ebp
        mov  DWORD PTR ds:0x477820,ebp
        je loc_0041FC40
        push  esi
        call FUN_00401260
        push  esi
        call _free
        add  esp,0x4
    loc_0041FC40:
        mov  ebx,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ebx+0x3ad06c]
        add  ebx,0x3ad06c
        cmp  edi,ebp
        je loc_0041FC68
        call FUN_00447810
        mov  edx,DWORD PTR [ebx]
        push  edx
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebx],ebp
    loc_0041FC68:
        mov  ebx,DWORD PTR ds:0x47783c
        call FUN_0042b1e0
        mov  edi,DWORD PTR ds:0x47783c
        cmp  edi,ebp
        je loc_0041FCAA
        mov  eax,DWORD PTR [edi]
        cmp  eax,ebp
        je loc_0041FC8E
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [edi],ebp
    loc_0041FC8E:
        mov  eax,DWORD PTR [edi+0x4]
        cmp  eax,ebp
        je loc_0041FCA1
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [edi+0x4],ebp
    loc_0041FCA1:
        push  edi
        call _free
        add  esp,0x4
    loc_0041FCAA:
        mov  esi,DWORD PTR [esp+0x24]
        mov  eax,DWORD PTR [esi+0x388]
        cmp  eax,ebp
        mov  DWORD PTR ds:0x47783c,ebp
        je loc_0041FCC7
        push  eax
        call _free
        add  esp,0x4
    loc_0041FCC7:
        mov  DWORD PTR [esi+0x388],ebp
        mov  esi,DWORD PTR [esp+0x10]
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
