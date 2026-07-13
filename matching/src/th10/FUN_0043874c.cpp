// 0043874C: FUN_0043874c
// Original size: 118 bytes, actual code: 43 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0043874c(void) {
    __asm {
        mov  ecx,DWORD PTR [ebp+0xc]
        test  ecx,ecx
        mov  DWORD PTR [ebp-0x4],0xffffffff
        jbe loc_0043877E
        cmp  DWORD PTR [esi+0x18],0x10
        jb loc_00438765
        mov  esi,DWORD PTR [esi+0x4]
        jmp loc_00438768
    loc_00438765:
        add  esi,0x4
    loc_00438768:
        mov  eax,ecx
        shr  ecx,0x2
        mov  edi,edx
        rep movsd
        mov  ecx,eax
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  esi,DWORD PTR [ebp-0x14]
        mov  ecx,DWORD PTR [ebp+0xc]
    loc_0043877E:
        cmp  DWORD PTR [esi+0x18],0x10
        jb loc_00438796
        mov  ecx,DWORD PTR [esi+0x4]
        push  ecx
        call _free
        mov  edx,DWORD PTR [ebp+0x8]
        mov  ecx,DWORD PTR [ebp+0xc]
        add  esp,0x4
    loc_00438796:
        cmp  ebx,0x10
        lea  eax,[esi+0x4]
        mov  BYTE PTR [eax],0x0
        mov  DWORD PTR [eax],edx
        mov  DWORD PTR [esi+0x18],ebx
        mov  DWORD PTR [esi+0x14],ecx
        jb loc_004387AB
        mov  eax,edx
    loc_004387AB:
        pop  edi
        mov  BYTE PTR [eax+ecx*1],0x0
        mov  ecx,DWORD PTR [ebp-0xc]
        pop  esi
        mov  DWORD PTR fs:0x0,ecx
        pop  ebx
        mov  esp,ebp
        pop  ebp
        ret  0x8
    }
}
