// 00403990: FUN_00403990
// Original size: 160 bytes, actual code: 51 instructions
extern "C" void FUN_0043ee30(void);

extern "C" __declspec(naked) void FUN_00403990(void) {
    __asm {
        sub  esp,0x8
        mov  ecx,DWORD PTR [ebx+0x10]
        xor  eax,eax
        cmp  WORD PTR [ecx],ax
        mov  DWORD PTR [esp+0x4],eax
        jle loc_00403A24
        push  ebp
        push  esi
        push  edi
        jmp loc_004039B0
        lea  ebx,[ebx+0x0]
    loc_004039B0:
        mov  edx,DWORD PTR [ebx+0x14]
        mov  ebp,DWORD PTR [edx+eax*4]
        test  BYTE PTR [ebp+0x3],0x1
        je loc_00403A0E
        cmp  WORD PTR [ebp+0x1c],0x0
        lea  edi,[ebp+0x1c]
        mov  DWORD PTR [esp+0xc],0x0
        jl loc_00403A0A
        mov  edi,edi
    loc_004039D0:
        movsx esi,WORD PTR [edi+0x6]
        mov  edx,DWORD PTR [ebx+0x17c]
        imul  esi,esi,0x3ac
        add  esi,edx
        push  esi
        call FUN_0043ee30
        mov  eax,DWORD PTR [esi+0x390]
        test  eax,eax
        je loc_004039F6
        inc  DWORD PTR [esp+0xc]
    loc_004039F6:
        movsx eax,WORD PTR [edi+0x2]
        add  edi,eax
        cmp  WORD PTR [edi],0x0
        jge loc_004039D0
        mov  eax,DWORD PTR [esp+0xc]
        test  eax,eax
        jne loc_00403A0E
    loc_00403A0A:
        and  BYTE PTR [ebp+0x3],0xfe
    loc_00403A0E:
        mov  ecx,DWORD PTR [ebx+0x10]
        mov  eax,DWORD PTR [esp+0x10]
        movsx edx,WORD PTR [ecx]
        inc  eax
        cmp  eax,edx
        mov  DWORD PTR [esp+0x10],eax
        jl loc_004039B0
        pop  edi
        pop  esi
        pop  ebp
    loc_00403A24:
        xor  eax,eax
        add  esp,0x8
        ret
    }
}
