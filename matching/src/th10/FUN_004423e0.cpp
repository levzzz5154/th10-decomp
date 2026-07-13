// 004423E0: FUN_004423e0
// Original size: 448 bytes, actual code: 132 instructions
extern "C" void FUN_00442f50(void);

extern "C" __declspec(naked) void FUN_004423e0(void) {
    __asm {
        push  ecx
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x35c]
        mov  cl,BYTE PTR [esi+0x3ada68]
        shr  eax,0x4
        and  eax,0x3
        cmp  cl,al
        je loc_00442448
        call FUN_00442f50
        mov  eax,DWORD PTR [ebx+0x35c]
        shr  eax,0x4
        and  al,0x3
        mov  BYTE PTR [esi+0x3ada68],al
        movzx eax,al
        sub  eax,0x0
        je loc_00442436
        dec  eax
        je loc_00442422
        dec  eax
        jne loc_00442448
        push  0x2
        jmp loc_00442438
    loc_00442422:
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x2
        push  0x14
        push  eax
        call  DWORD PTR [edx+0xe4]
        jmp loc_00442448
    loc_00442436:
        push  0x6
    loc_00442438:
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x14
        push  eax
        call  DWORD PTR [ecx+0xe4]
    loc_00442448:
        mov  eax,DWORD PTR [ebx+0x35c]
        test  ah,ah
        push  edi
        jns loc_0044245B
        mov  edi,DWORD PTR [ebx+0x300]
        jmp loc_00442461
    loc_0044245B:
        mov  edi,DWORD PTR [ebx+0x2fc]
    loc_00442461:
        mov  eax,DWORD PTR [esi+0x73245c]
        test  eax,eax
        mov  DWORD PTR [esp+0x8],edi
        je loc_00442509
        movzx eax,BYTE PTR [esi+0x73245a]
        mov  edx,edi
        shr  edx,0x10
        movzx edx,dl
        imul  eax,edx
        shr  eax,0x7
        cmp  eax,0x100
        jb loc_00442494
        mov  eax,0xff
    loc_00442494:
        mov  BYTE PTR [esp+0xa],al
        mov  ecx,DWORD PTR [esp+0x8]
        movzx eax,BYTE PTR [esi+0x732459]
        shr  ecx,0x8
        movzx ecx,cl
        imul  eax,ecx
        shr  eax,0x7
        cmp  eax,0x100
        jb loc_004424BB
        mov  eax,0xff
    loc_004424BB:
        movzx edx,BYTE PTR [esp+0x8]
        mov  BYTE PTR [esp+0x9],al
        movzx eax,BYTE PTR [esi+0x732458]
        imul  eax,edx
        shr  eax,0x7
        cmp  eax,0x100
        jb loc_004424DD
        mov  eax,0xff
    loc_004424DD:
        mov  BYTE PTR [esp+0x8],al
        movzx eax,BYTE PTR [esi+0x73245b]
        mov  ecx,DWORD PTR [esp+0x8]
        shr  ecx,0x18
        imul  eax,ecx
        shr  eax,0x7
        cmp  eax,0x100
        jb loc_00442501
        mov  eax,0xff
    loc_00442501:
        mov  BYTE PTR [esp+0xb],al
        mov  edi,DWORD PTR [esp+0x8]
    loc_00442509:
        cmp  DWORD PTR [esi+0x3ada60],edi
        je loc_0044252D
        call FUN_00442f50
        push  edi
        mov  DWORD PTR [esi+0x3ada60],edi
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x3c
        push  eax
        call  DWORD PTR [edx+0xe4]
    loc_0044252D:
        mov  eax,DWORD PTR [ebx+0x35c]
        mov  cl,BYTE PTR [esi+0x3ada6e]
        shr  eax,0x1f
        cmp  cl,al
        pop  edi
        je loc_00442592
        call FUN_00442f50
        mov  eax,DWORD PTR [ebx+0x35c]
        shr  eax,0x1f
        and  al,0x1
        mov  BYTE PTR [esi+0x3ada6e],al
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        jne loc_00442571
        push  0x2
        push  0x5
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x114]
        push  0x2
        jmp loc_00442580
    loc_00442571:
        push  0x1
        push  0x5
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x114]
        push  0x1
    loc_00442580:
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x6
        push  0x0
        push  eax
        call  DWORD PTR [edx+0x114]
    loc_00442592:
        inc  DWORD PTR [esi+0x54]
        pop  esi
        pop  ecx
        ret
    }
}
