// 00414570: FUN_00414570
// Original size: 128 bytes, actual code: 38 instructions
extern "C" void FUN_004136c0(void);
extern "C" void FUN_00447810(void);
extern "C" void _free(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00414570(void) {
    __asm {
        push  ebp
        push  esi
        mov  esi,DWORD PTR [ebx+0x9eb8]
        xor  ebp,ebp
        cmp  esi,ebp
        je loc_00414592
        call FUN_004136c0
        push  esi
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebx+0x9eb8],ebp
    loc_00414592:
        test  BYTE PTR ds:0x474ca0,0x9
        jne loc_004145E6
        mov  esi,DWORD PTR ds:0x491c10
        add  esi,0x3ad0dc
        push  edi
        mov  edi,DWORD PTR [esi]
        cmp  edi,ebp
        je loc_004145C0
        call FUN_00447810
        mov  eax,DWORD PTR [esi]
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],ebp
    loc_004145C0:
        mov  eax,DWORD PTR [ebx+0x9ebc]
        cmp  eax,ebp
        mov  DWORD PTR [ebx+0x9e80],ebp
        pop  edi
        je loc_004145E0
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebx+0x9ebc],ebp
    loc_004145E0:
        mov  DWORD PTR [ebx+0x9ebc],ebp
    loc_004145E6:
        pop  esi
        pop  ebp
        ret
    }
}
