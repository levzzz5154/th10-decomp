// 00438510: FUN_00438510
// Original size: 128 bytes, actual code: 52 instructions
extern "C" void _memmove(void);
extern "C" void FUN_00462428(void);

extern "C" __declspec(naked) void FUN_00438510(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        push  esi
        mov  esi,ecx
        cmp  DWORD PTR [esi+0x14],ebp
        push  edi
        jae loc_00438523
        call FUN_00462428
    loc_00438523:
        mov  eax,DWORD PTR [esi+0x14]
        mov  edi,DWORD PTR [esp+0x14]
        sub  eax,ebp
        cmp  eax,edi
        jae loc_00438532
        mov  edi,eax
    loc_00438532:
        test  edi,edi
        jbe loc_0043857D
        mov  ecx,DWORD PTR [esi+0x18]
        cmp  ecx,0x10
        push  ebx
        lea  ebx,[esi+0x4]
        jb loc_00438546
        mov  edx,DWORD PTR [ebx]
        jmp loc_00438548
    loc_00438546:
        mov  edx,ebx
    loc_00438548:
        cmp  ecx,0x10
        jb loc_00438551
        mov  ecx,DWORD PTR [ebx]
        jmp loc_00438553
    loc_00438551:
        mov  ecx,ebx
    loc_00438553:
        sub  eax,edi
        add  edx,ebp
        push  eax
        add  edx,edi
        push  edx
        add  ecx,ebp
        push  ecx
        call _memmove
        mov  eax,DWORD PTR [esi+0x14]
        mov  ecx,DWORD PTR [esi+0x18]
        sub  eax,edi
        add  esp,0xc
        cmp  ecx,0x10
        mov  DWORD PTR [esi+0x14],eax
        jb loc_00438578
        mov  ebx,DWORD PTR [ebx]
    loc_00438578:
        mov  BYTE PTR [ebx+eax*1],0x0
        pop  ebx
    loc_0043857D:
        pop  edi
        mov  eax,esi
        pop  esi
        pop  ebp
        ret  0x8
    }
}
