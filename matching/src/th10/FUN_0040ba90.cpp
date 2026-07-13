// 0040BA90: FUN_0040ba90
// Original size: 656 bytes, actual code: 209 instructions
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_0040ba90(void) {
    __asm {
        push  0xffffffff
        push  0x4654ce
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        sub  esp,0xc
        push  ebp
        mov  ebp,DWORD PTR [esp+0x20]
        push  esi
        mov  esi,DWORD PTR [ebp+0x14]
        mov  eax,0xfffffffe
        and  esi,eax
        mov  DWORD PTR [ebp+0x14],esi
        and  DWORD PTR [ebp+0x28],eax
        mov  ecx,DWORD PTR [ebp+0x3c]
        xor  edx,edx
        and  ecx,eax
        mov  DWORD PTR [ebp+0x3c],ecx
        push  edi
        mov  DWORD PTR [ebp+0xd0],0x4703e4
        mov  DWORD PTR [ebp+0xd4],edx
        mov  DWORD PTR [ebp+0xd8],edx
        mov  DWORD PTR [ebp+0xdc],edx
        mov  DWORD PTR [ebp+0xe0],edx
        xor  eax,eax
        mov  DWORD PTR [esp+0x20],edx
        mov  esi,DWORD PTR ds:0x491c10
        mov  ecx,0x3b
        mov  edi,ebp
        rep stosd
        lea  eax,[ebp+0x40]
        mov  DWORD PTR [esp+0xc],edx
        mov  DWORD PTR [esp+0x10],eax
        push  ebx
        nop
    loc_0040BB10:
        mov  ecx,DWORD PTR ds:0x4776e0
        mov  edi,DWORD PTR [ecx+0x899c]
        call FUN_00449950
        mov  edx,DWORD PTR [esp+0x10]
        mov  ebx,eax
        mov  eax,DWORD PTR [ebx+0x35c]
        add  edx,0x42
        push  edx
        or   eax,0x40000000
        push  ebx
        mov  ecx,edi
        mov  DWORD PTR [ebx+0x20],0xf
        mov  DWORD PTR [ebx+0x35c],eax
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x18]
        mov  edx,esi
        call FUN_004489d0
        mov  eax,DWORD PTR [esp+0x18]
        mov  edi,DWORD PTR [esp+0x14]
        mov  ecx,eax
        test  ecx,ecx
        mov  DWORD PTR [edi],eax
        jne loc_0040BB70
    loc_0040BB6C:
        xor  eax,eax
        jmp loc_0040BBAC
    loc_0040BB70:
        mov  eax,DWORD PTR [esi+0x72dad4]
        test  eax,eax
        je loc_0040BB8D
        lea  ebx,[ebx+0x0]
    loc_0040BB80:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_0040BBA6
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_0040BB80
    loc_0040BB8D:
        mov  eax,DWORD PTR [esi+0x72dadc]
        test  eax,eax
        je loc_0040BB6C
    loc_0040BB97:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_0040BBA6
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_0040BB97
        jmp loc_0040BBAC
    loc_0040BBA6:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        jne loc_0040BBB2
    loc_0040BBAC:
        mov  DWORD PTR [edi],0x0
    loc_0040BBB2:
        mov  dl,0x10
        mov  BYTE PTR [eax+0x3a0],dl
        mov  ecx,DWORD PTR [edi]
        test  ecx,ecx
        jne loc_0040BBC4
    loc_0040BBC0:
        xor  eax,eax
        jmp loc_0040BBFC
    loc_0040BBC4:
        mov  eax,DWORD PTR [esi+0x72dad4]
        test  eax,eax
        je loc_0040BBDD
        mov  edi,edi
    loc_0040BBD0:
        mov  ebx,DWORD PTR [eax]
        cmp  DWORD PTR [ebx],ecx
        je loc_0040BBF6
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_0040BBD0
    loc_0040BBDD:
        mov  eax,DWORD PTR [esi+0x72dadc]
        test  eax,eax
        je loc_0040BBC0
    loc_0040BBE7:
        mov  ebx,DWORD PTR [eax]
        cmp  DWORD PTR [ebx],ecx
        je loc_0040BBF6
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_0040BBE7
        jmp loc_0040BBFC
    loc_0040BBF6:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        jne loc_0040BC02
    loc_0040BBFC:
        mov  DWORD PTR [edi],0x0
    loc_0040BC02:
        mov  BYTE PTR [eax+0x3a1],dl
        mov  ecx,DWORD PTR [edi]
        test  ecx,ecx
        jne loc_0040BC12
    loc_0040BC0E:
        xor  eax,eax
        jmp loc_0040BC4C
    loc_0040BC12:
        mov  eax,DWORD PTR [esi+0x72dad4]
        test  eax,eax
        je loc_0040BC2D
        nop
    loc_0040BC20:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_0040BC46
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_0040BC20
    loc_0040BC2D:
        mov  eax,DWORD PTR [esi+0x72dadc]
        test  eax,eax
        je loc_0040BC0E
    loc_0040BC37:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_0040BC46
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_0040BC37
        jmp loc_0040BC4C
    loc_0040BC46:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        jne loc_0040BC52
    loc_0040BC4C:
        mov  DWORD PTR [edi],0x0
    loc_0040BC52:
        or   DWORD PTR [eax+0x360],0x2
        mov  eax,DWORD PTR [esp+0x10]
        inc  eax
        add  edi,0x4
        cmp  eax,0x5
        mov  DWORD PTR [esp+0x10],eax
        mov  DWORD PTR [esp+0x14],edi
        jb loc_0040BB10
        mov  eax,DWORD PTR [esp+0x30]
        mov  DWORD PTR [ebp+0x54],eax
        mov  ecx,DWORD PTR [ebp+0x14]
        xor  eax,eax
        test  cl,0x1
        mov  esi,0xfff0bdc1
        mov  edx,0x476f78
        pop  ebx
        jne loc_0040BCA0
        or   ecx,0x1
        mov  DWORD PTR [ebp+0x8],eax
        mov  DWORD PTR [ebp+0x4],esi
        mov  DWORD PTR [ebp+0xc],eax
        mov  DWORD PTR [ebp+0x10],edx
        mov  DWORD PTR [ebp+0x14],ecx
    loc_0040BCA0:
        or   edi,0xffffffff
        mov  DWORD PTR [ebp+0x8],eax
        mov  DWORD PTR [ebp+0xc],eax
        mov  DWORD PTR [ebp+0x4],edi
        mov  ecx,DWORD PTR [ebp+0x28]
        test  cl,0x1
        jne loc_0040BCC6
        or   ecx,0x1
        mov  DWORD PTR [ebp+0x1c],eax
        mov  DWORD PTR [ebp+0x18],esi
        mov  DWORD PTR [ebp+0x20],eax
        mov  DWORD PTR [ebp+0x24],edx
        mov  DWORD PTR [ebp+0x28],ecx
    loc_0040BCC6:
        mov  DWORD PTR [ebp+0x1c],eax
        mov  DWORD PTR [ebp+0x20],eax
        mov  DWORD PTR [ebp+0x18],edi
        mov  ecx,DWORD PTR [ebp+0x3c]
        test  cl,0x1
        jne loc_0040BCE9
        or   ecx,0x1
        mov  DWORD PTR [ebp+0x30],eax
        mov  DWORD PTR [ebp+0x2c],esi
        mov  DWORD PTR [ebp+0x34],eax
        mov  DWORD PTR [ebp+0x38],edx
        mov  DWORD PTR [ebp+0x3c],ecx
    loc_0040BCE9:
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [ebp+0x30],eax
        mov  DWORD PTR [ebp+0x34],eax
        mov  DWORD PTR [ebp+0x2c],edi
        mov  eax,DWORD PTR [ebp+0x74]
        or   eax,0x1
        pop  edi
        mov  DWORD PTR [ebp+0x74],eax
        mov  DWORD PTR [ebp+0x7c],0xffffff
        pop  esi
        mov  eax,ebp
        pop  ebp
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x18
        ret  0x8
    }
}
