// 00449950: FUN_00449950
// Original size: 320 bytes, actual code: 49 instructions
extern "C" void FUN_00401de0(void);
extern "C" void FUN_00402050(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_00449950(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x3ad068]
        mov  ecx,eax
        imul  ecx,ecx,0x3ac
        push  edi
        lea  edi,[ecx+esi*1+0x68]
        mov  cl,BYTE PTR [eax+esi*1+0x3ac068]
        test  cl,cl
        je loc_004499CA
        inc  eax
        and  eax,0x80000fff
        jns loc_0044997D
        dec  eax
        or   eax,0xfffff000
        inc  eax
    loc_0044997D:
        mov  edx,eax
        imul  edx,edx,0x3ac
        mov  DWORD PTR [esi+0x3ad068],eax
        mov  cl,BYTE PTR [eax+esi*1+0x3ac068]
        test  cl,cl
        lea  edi,[edx+esi*1+0x68]
        je loc_004499CA
        push  0x3ac
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_004499BD
        mov  ecx,eax
        call FUN_00402050
        mov  edx,eax
        mov  edi,eax
        call FUN_00401de0
        jmp loc_004499D2
    loc_004499BD:
        xor  eax,eax
        mov  edx,eax
        mov  edi,eax
        call FUN_00401de0
        jmp loc_004499D2
    loc_004499CA:
        mov  BYTE PTR [eax+esi*1+0x3ac068],0x1
    loc_004499D2:
        mov  eax,DWORD PTR [esi+0x3ad068]
        inc  eax
        and  eax,0x80000fff
        jns loc_004499E7
        dec  eax
        or   eax,0xfffff000
        inc  eax
    loc_004499E7:
        mov  DWORD PTR [esi+0x3ad068],eax
        mov  eax,edi
        pop  edi
        ret
    }
}
