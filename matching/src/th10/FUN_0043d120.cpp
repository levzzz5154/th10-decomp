// 0043D120: FUN_0043d120
// Original size: 304 bytes, actual code: 104 instructions
extern "C" void FUN_0043dab0(void);
extern "C" void _free(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0043d120(void) {
    __asm {
        push  ebp
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x1f84]
        xor  ebp,ebp
        cmp  eax,ebp
        push  edi
        je loc_0043D140
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0x1f84],ebp
    loc_0043D140:
        push  ebx
        lea  edi,[esi+0x8]
        mov  ebx,0x80
        nop
    loc_0043D150:
        mov  eax,DWORD PTR [edi+0x200]
        cmp  eax,ebp
        je loc_0043D166
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edi+0x200],ebp
    loc_0043D166:
        mov  eax,DWORD PTR [edi]
        cmp  eax,ebp
        je loc_0043D174
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        mov  DWORD PTR [edi],ebp
    loc_0043D174:
        add  edi,0x4
        dec  ebx
        jne loc_0043D150
        lea  edi,[esi+0x5230]
        mov  ebx,0x25
    loc_0043D185:
        mov  eax,DWORD PTR [edi]
        cmp  eax,ebp
        je loc_0043D196
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [edi],ebp
    loc_0043D196:
        add  edi,0x4
        dec  ebx
        jne loc_0043D185
        cmp  DWORD PTR [esi+0x610],ebp
        pop  ebx
        je loc_0043D247
        mov  eax,DWORD PTR [esi+0x60c]
        push  0x1
        push  eax
        call  DWORD PTR ds:0x466214
        call FUN_0043dab0
        mov  eax,DWORD PTR [esi+0x608]
        mov  DWORD PTR [esi],ebp
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x48]
        mov  eax,DWORD PTR [esi+0x608]
        cmp  eax,ebp
        je loc_0043D1E1
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        mov  DWORD PTR [esi+0x608],ebp
    loc_0043D1E1:
        mov  ecx,DWORD PTR [esi+0x5208]
        cmp  ecx,ebp
        je loc_0043D1F7
        mov  eax,DWORD PTR [ecx]
        push  0x1
        call  DWORD PTR [eax]
        mov  DWORD PTR [esi+0x5208],ebp
    loc_0043D1F7:
        mov  edi,DWORD PTR [esi+0x610]
        cmp  edi,ebp
        je loc_0043D21E
        mov  eax,DWORD PTR [edi]
        cmp  eax,ebp
        je loc_0043D20F
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edi],ebp
    loc_0043D20F:
        push  edi
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0x610],ebp
    loc_0043D21E:
        add  esi,0x1ec0
        mov  edi,0x10
        nop
    loc_0043D230:
        mov  eax,DWORD PTR [esi]
        cmp  eax,ebp
        je loc_0043D241
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],ebp
    loc_0043D241:
        add  esi,0x4
        dec  edi
        jne loc_0043D230
    loc_0043D247:
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebp
        ret
    }
}
