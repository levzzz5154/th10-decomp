// 00413790: FUN_00413790
// Original size: 128 bytes, actual code: 34 instructions

extern "C" __declspec(naked) void FUN_00413790(void) {
    __asm {
        xor  edx,edx
        test  ecx,ecx
        push  edi
        mov  edi,eax
        jle loc_004137B5
        push  esi
        lea  eax,[edi+0x4cdc]
        mov  esi,ecx
        mov  edx,ecx
    loc_004137A4:
        or   DWORD PTR [eax],0x2
        add  eax,0x3ac
        dec  esi
        jne loc_004137A4
        cmp  ecx,0x9
        pop  esi
        jge loc_004137DB
    loc_004137B5:
        mov  eax,edx
        imul  eax,eax,0x3ac
        mov  ecx,0x9
        lea  eax,[eax+edi*1+0x4cdc]
        sub  ecx,edx
        jmp loc_004137D0
        nop
    loc_004137D0:
        and  DWORD PTR [eax],0xfffffffd
        add  eax,0x3ac
        dec  ecx
        jne loc_004137D0
    loc_004137DB:
        pop  edi
        ret
    }
}
