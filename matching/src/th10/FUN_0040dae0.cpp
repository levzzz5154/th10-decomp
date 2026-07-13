// 0040DAE0: FUN_0040dae0
// Original size: 416 bytes, actual code: 126 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0040dae0(void) {
    __asm {
        push  ecx
        mov  ecx,DWORD PTR ds:0x477704
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x10]
        mov  DWORD PTR [ebp+0x0],0x46d0c0
        mov  edx,DWORD PTR [ecx+0x58]
        lea  eax,[ebp+0x116c]
        cmp  edx,eax
        push  esi
        push  edi
        jne loc_0040DB0C
        mov  edx,DWORD PTR [ebp+0x1170]
        mov  DWORD PTR [ecx+0x58],edx
    loc_0040DB0C:
        cmp  DWORD PTR [ecx+0x5c],eax
        jne loc_0040DB1A
        mov  edx,DWORD PTR [ebp+0x1174]
        mov  DWORD PTR [ecx+0x5c],edx
    loc_0040DB1A:
        mov  edx,DWORD PTR [eax+0x4]
        xor  ebx,ebx
        cmp  edx,ebx
        je loc_0040DB29
        mov  esi,DWORD PTR [eax+0x8]
        mov  DWORD PTR [edx+0x8],esi
    loc_0040DB29:
        mov  edx,DWORD PTR [eax+0x8]
        cmp  edx,ebx
        je loc_0040DB36
        mov  esi,DWORD PTR [eax+0x4]
        mov  DWORD PTR [edx+0x4],esi
    loc_0040DB36:
        mov  DWORD PTR [eax+0x4],ebx
        mov  DWORD PTR [eax+0x8],ebx
        dec  DWORD PTR [ecx+0x60]
        mov  eax,DWORD PTR [ebp+0x2480]
        test  ah,ah
        jns loc_0040DB53
        mov  eax,DWORD PTR [ebp+0x248c]
        mov  DWORD PTR [ecx+eax*4+0x10],ebx
    loc_0040DB53:
        mov  edi,DWORD PTR ds:0x491c10
        lea  edx,[ebp+0x10fc]
        mov  DWORD PTR [esp+0x10],0xa
        mov  esi,0x4000000
        nop
    loc_0040DB70:
        mov  ecx,DWORD PTR [edx]
        cmp  ecx,ebx
        je loc_0040DBE5
        mov  eax,DWORD PTR [edi+0x72dad4]
        cmp  eax,ebx
        je loc_0040DB92
    loc_0040DB80:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_0040DBB0
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0040DB80
        mov  ebp,DWORD PTR [esp+0x18]
    loc_0040DB92:
        mov  eax,DWORD PTR [edi+0x72dadc]
        cmp  eax,ebx
        je loc_0040DBE5
        nop
    loc_0040DBA0:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_0040DBB0
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0040DBA0
        jmp loc_0040DBE1
    loc_0040DBB0:
        mov  eax,DWORD PTR [eax]
        cmp  eax,ebx
        je loc_0040DBE1
        mov  ebp,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        or   ebp,esi
        cmp  ecx,ebx
        mov  DWORD PTR [eax+0x35c],ebp
        jne loc_0040DBE1
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,ebx
        je loc_0040DBE1
    loc_0040DBD2:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],esi
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0040DBD2
    loc_0040DBE1:
        mov  ebp,DWORD PTR [esp+0x18]
    loc_0040DBE5:
        mov  eax,DWORD PTR [esp+0x10]
        mov  DWORD PTR [edx],ebx
        add  edx,0x4
        dec  eax
        mov  DWORD PTR [esp+0x10],eax
        jne loc_0040DB70
        mov  eax,ds:0x477834
        cmp  eax,ebx
        je loc_0040DC2C
        cmp  DWORD PTR [eax+0x3504],ebp
        jne loc_0040DC16
        mov  DWORD PTR [eax+0x3504],ebx
        mov  BYTE PTR [eax+0x3508],bl
    loc_0040DC16:
        add  eax,0x4e8
        mov  ecx,0x80
    loc_0040DC20:
        cmp  DWORD PTR [eax],ebp
        jne loc_0040DC26
        mov  DWORD PTR [eax],ebx
    loc_0040DC26:
        add  eax,0x5c
        dec  ecx
        jne loc_0040DC20
    loc_0040DC2C:
        mov  esi,DWORD PTR [ebp+0x1034]
        cmp  esi,ebx
        mov  DWORD PTR [ebp+0x0],0x46d0d8
        je loc_0040DC5A
        nop
    loc_0040DC40:
        mov  ecx,DWORD PTR [esi]
        mov  edi,DWORD PTR [esi+0x4]
        push  ecx
        call _free
        push  esi
        call _free
        add  esp,0x8
        cmp  edi,ebx
        mov  esi,edi
        jne loc_0040DC40
    loc_0040DC5A:
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        pop  ecx
        ret  0x4
    }
}
