// 00438380: FUN_00438380
// Original size: 160 bytes, actual code: 34 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00438380(void) {
    __asm {
        mov  al,BYTE PTR [esp+0x4]
        test  al,al
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x10]
        mov  ebx,ecx
        je loc_004383BF
        cmp  DWORD PTR [ebx+0x18],0x10
        jb loc_004383BF
        test  ebp,ebp
        mov  eax,DWORD PTR [ebx+0x4]
        push  edi
        lea  edi,[ebx+0x4]
        jbe loc_004383B5
        push  esi
        mov  ecx,ebp
        mov  edx,ecx
        shr  ecx,0x2
        mov  esi,eax
        rep movsd
        mov  ecx,edx
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        pop  esi
    loc_004383B5:
        push  eax
        call _free
        add  esp,0x4
        pop  edi
    loc_004383BF:
        mov  DWORD PTR [ebx+0x14],ebp
        mov  DWORD PTR [ebx+0x18],0xf
        mov  BYTE PTR [ebx+ebp*1+0x4],0x0
        pop  ebp
        pop  ebx
        ret  0x8
    }
}
