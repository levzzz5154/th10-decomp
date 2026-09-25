#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045BFC0..0x0045C01A: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_0045bfc0() {
    __asm {
    L_0045bfc0:
        push ebp
    L_0045bfc1:
        mov ebp,esp
    L_0045bfc3:
        push edi
    L_0045bfc4:
        push esi
    L_0045bfc5:
        mov esi,dword ptr [ebp+0Ch]
    L_0045bfc8:
        mov ecx,dword ptr [ebp+10h]
    L_0045bfcb:
        mov edi,dword ptr [ebp+8]
    L_0045bfce:
        mov eax,ecx
    L_0045bfd0:
        mov edx,ecx
    L_0045bfd2:
        add eax,esi
    L_0045bfd4:
        cmp edi,esi
    L_0045bfd6:
        jbe short L_0045bfe0
    L_0045bfd8:
        cmp edi,eax
    L_0045bfda:
        jb asm_memcpy_part_0045c15c
    L_0045bfe0:
        test edi,3
    L_0045bfe6:
        jne short L_0045bffc
    L_0045bfe8:
        shr ecx,2
    L_0045bfeb:
        and edx,3
    L_0045bfee:
        cmp ecx,8
    L_0045bff1:
        TH10_REL8(0x72, 0x0045bff1, VA_asm_memcpy_part_0045c01c)
    L_0045bff3:
        rep movsd
    L_0045bff5:
        jmp dword ptr [edx*4+45C10Ch]
    L_0045bffc:
        mov eax,edi
    L_0045bffe:
        mov edx,3
    L_0045c003:
        sub ecx,4
    L_0045c006:
        jb short L_0045c014
    L_0045c008:
        and eax,3
    L_0045c00b:
        add ecx,eax
    L_0045c00d:
        jmp dword ptr [eax*4+45C020h]
    L_0045c014:
        jmp dword ptr [ecx*4+45C11Ch]
    }
}

// 0x0045C01C..0x0045C022: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c01c() {
    __asm {
    L_0045c01c:
        jmp dword ptr [ecx*4+45C0A0h]
    }
}

// 0x0045C030..0x0045C058: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c030() {
    __asm {
    L_0045c030:
        and edx,ecx
    L_0045c032:
        mov al,byte ptr [esi]
    L_0045c034:
        mov byte ptr [edi],al
    L_0045c036:
        mov al,byte ptr [esi+1]
    L_0045c039:
        mov byte ptr [edi+1],al
    L_0045c03c:
        mov al,byte ptr [esi+2]
    L_0045c03f:
        shr ecx,2
    L_0045c042:
        mov byte ptr [edi+2],al
    L_0045c045:
        add esi,3
    L_0045c048:
        add edi,3
    L_0045c04b:
        cmp ecx,8
    L_0045c04e:
        TH10_REL8(0x72, 0x0045c04e, VA_asm_memcpy_part_0045c01c)
    L_0045c050:
        rep movsd
    L_0045c052:
        jmp dword ptr [edx*4+45C10Ch]
    }
}

// 0x0045C05C..0x0045C07E: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c05c() {
    __asm {
    L_0045c05c:
        and edx,ecx
    L_0045c05e:
        mov al,byte ptr [esi]
    L_0045c060:
        mov byte ptr [edi],al
    L_0045c062:
        mov al,byte ptr [esi+1]
    L_0045c065:
        shr ecx,2
    L_0045c068:
        mov byte ptr [edi+1],al
    L_0045c06b:
        add esi,2
    L_0045c06e:
        add edi,2
    L_0045c071:
        cmp ecx,8
    L_0045c074:
        TH10_REL8(0x72, 0x0045c074, VA_asm_memcpy_part_0045c01c)
    L_0045c076:
        rep movsd
    L_0045c078:
        jmp dword ptr [edx*4+45C10Ch]
    }
}

// 0x0045C080..0x0045C09C: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c080() {
    __asm {
    L_0045c080:
        and edx,ecx
    L_0045c082:
        mov al,byte ptr [esi]
    L_0045c084:
        mov byte ptr [edi],al
    L_0045c086:
        add esi,1
    L_0045c089:
        shr ecx,2
    L_0045c08c:
        add edi,1
    L_0045c08f:
        cmp ecx,8
    L_0045c092:
        TH10_REL8(0x72, 0x0045c092, VA_asm_memcpy_part_0045c01c)
    L_0045c094:
        rep movsd
    L_0045c096:
        jmp dword ptr [edx*4+45C10Ch]
    }
}

// 0x0045C0C0..0x0045C109: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c0c0() {
    __asm {
    L_0045c0c0:
        mov eax,dword ptr [esi+ecx*4-1Ch]
    L_0045c0c4:
        mov dword ptr [edi+ecx*4-1Ch],eax
    L_0045c0c8:
        mov eax,dword ptr [esi+ecx*4-18h]
    L_0045c0cc:
        mov dword ptr [edi+ecx*4-18h],eax
    L_0045c0d0:
        mov eax,dword ptr [esi+ecx*4-14h]
    L_0045c0d4:
        mov dword ptr [edi+ecx*4-14h],eax
    L_0045c0d8:
        mov eax,dword ptr [esi+ecx*4-10h]
    L_0045c0dc:
        mov dword ptr [edi+ecx*4-10h],eax
    L_0045c0e0:
        mov eax,dword ptr [esi+ecx*4-0Ch]
    L_0045c0e4:
        mov dword ptr [edi+ecx*4-0Ch],eax
    L_0045c0e8:
        mov eax,dword ptr [esi+ecx*4-8]
    L_0045c0ec:
        mov dword ptr [edi+ecx*4-8],eax
    L_0045c0f0:
        mov eax,dword ptr [esi+ecx*4-4]
    L_0045c0f4:
        mov dword ptr [edi+ecx*4-4],eax
    L_0045c0f8:
        lea eax,[ecx*4]
    L_0045c0ff:
        add esi,eax
    L_0045c101:
        add edi,eax
    L_0045c103:
        jmp dword ptr [edx*4+45C10Ch]
    }
}

// 0x0045C11C..0x0045C122: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c11c() {
    __asm {
    L_0045c11c:
        mov eax,dword ptr [ebp+8]
    L_0045c11f:
        pop esi
    L_0045c120:
        pop edi
    L_0045c121:
        leave
    L_0045c122:
        ret
    }
}

// 0x0045C124..0x0045C12E: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c124() {
    __asm {
    L_0045c124:
        mov al,byte ptr [esi]
    L_0045c126:
        mov byte ptr [edi],al
    L_0045c128:
        mov eax,dword ptr [ebp+8]
    L_0045c12b:
        pop esi
    L_0045c12c:
        pop edi
    L_0045c12d:
        leave
    L_0045c12e:
        ret
    }
}

// 0x0045C130..0x0045C140: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c130() {
    __asm {
    L_0045c130:
        mov al,byte ptr [esi]
    L_0045c132:
        mov byte ptr [edi],al
    L_0045c134:
        mov al,byte ptr [esi+1]
    L_0045c137:
        mov byte ptr [edi+1],al
    L_0045c13a:
        mov eax,dword ptr [ebp+8]
    L_0045c13d:
        pop esi
    L_0045c13e:
        pop edi
    L_0045c13f:
        leave
    L_0045c140:
        ret
    }
}

// 0x0045C144..0x0045C15A: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c144() {
    __asm {
    L_0045c144:
        mov al,byte ptr [esi]
    L_0045c146:
        mov byte ptr [edi],al
    L_0045c148:
        mov al,byte ptr [esi+1]
    L_0045c14b:
        mov byte ptr [edi+1],al
    L_0045c14e:
        mov al,byte ptr [esi+2]
    L_0045c151:
        mov byte ptr [edi+2],al
    L_0045c154:
        mov eax,dword ptr [ebp+8]
    L_0045c157:
        pop esi
    L_0045c158:
        pop edi
    L_0045c159:
        leave
    L_0045c15a:
        ret
    }
}

// 0x0045C15C..0x0045C181: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c15c() {
    __asm {
    L_0045c15c:
        lea esi,[ecx+esi-4]
    L_0045c160:
        lea edi,[ecx+edi-4]
    L_0045c164:
        test edi,3
    L_0045c16a:
        TH10_REL8(0x75, 0x0045c16a, VA_asm_memcpy_part_0045c190)
    L_0045c16c:
        shr ecx,2
    L_0045c16f:
        and edx,3
    L_0045c172:
        cmp ecx,8
    L_0045c175:
        TH10_REL8(0x72, 0x0045c175, VA_asm_memcpy_part_0045c184)
    L_0045c177:
        std
    L_0045c178:
        rep movsd
    L_0045c17a:
        cld
    L_0045c17b:
        jmp dword ptr [edx*4+45C2A8h]
    }
}

// 0x0045C184..0x0045C18C: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c184() {
    __asm {
    L_0045c184:
        neg ecx
    L_0045c186:
        jmp dword ptr [ecx*4+45C258h]
    }
}

// 0x0045C190..0x0045C1AE: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c190() {
    __asm {
    L_0045c190:
        mov eax,edi
    L_0045c192:
        mov edx,3
    L_0045c197:
        cmp ecx,4
    L_0045c19a:
        jb short L_0045c1a8
    L_0045c19c:
        and eax,3
    L_0045c19f:
        sub ecx,eax
    L_0045c1a1:
        jmp dword ptr [eax*4+45C1ACh]
    L_0045c1a8:
        jmp dword ptr [ecx*4+45C2A8h]
    }
}

// 0x0045C1BC..0x0045C1DC: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c1bc() {
    __asm {
    L_0045c1bc:
        mov al,byte ptr [esi+3]
    L_0045c1bf:
        and edx,ecx
    L_0045c1c1:
        mov byte ptr [edi+3],al
    L_0045c1c4:
        sub esi,1
    L_0045c1c7:
        shr ecx,2
    L_0045c1ca:
        sub edi,1
    L_0045c1cd:
        cmp ecx,8
    L_0045c1d0:
        TH10_REL8(0x72, 0x0045c1d0, VA_asm_memcpy_part_0045c184)
    L_0045c1d2:
        std
    L_0045c1d3:
        rep movsd
    L_0045c1d5:
        cld
    L_0045c1d6:
        jmp dword ptr [edx*4+45C2A8h]
    }
}

// 0x0045C1E0..0x0045C206: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c1e0() {
    __asm {
    L_0045c1e0:
        mov al,byte ptr [esi+3]
    L_0045c1e3:
        and edx,ecx
    L_0045c1e5:
        mov byte ptr [edi+3],al
    L_0045c1e8:
        mov al,byte ptr [esi+2]
    L_0045c1eb:
        shr ecx,2
    L_0045c1ee:
        mov byte ptr [edi+2],al
    L_0045c1f1:
        sub esi,2
    L_0045c1f4:
        sub edi,2
    L_0045c1f7:
        cmp ecx,8
    L_0045c1fa:
        TH10_REL8(0x72, 0x0045c1fa, VA_asm_memcpy_part_0045c184)
    L_0045c1fc:
        std
    L_0045c1fd:
        rep movsd
    L_0045c1ff:
        cld
    L_0045c200:
        jmp dword ptr [edx*4+45C2A8h]
    }
}

// 0x0045C208..0x0045C238: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c208() {
    __asm {
    L_0045c208:
        mov al,byte ptr [esi+3]
    L_0045c20b:
        and edx,ecx
    L_0045c20d:
        mov byte ptr [edi+3],al
    L_0045c210:
        mov al,byte ptr [esi+2]
    L_0045c213:
        mov byte ptr [edi+2],al
    L_0045c216:
        mov al,byte ptr [esi+1]
    L_0045c219:
        shr ecx,2
    L_0045c21c:
        mov byte ptr [edi+1],al
    L_0045c21f:
        sub esi,3
    L_0045c222:
        sub edi,3
    L_0045c225:
        cmp ecx,8
    L_0045c228:
        jb asm_memcpy_part_0045c184
    L_0045c22e:
        std
    L_0045c22f:
        rep movsd
    L_0045c231:
        cld
    L_0045c232:
        jmp dword ptr [edx*4+45C2A8h]
    }
}

// 0x0045C25C..0x0045C2A5: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c25c() {
    __asm {
    L_0045c25c:
        mov eax,dword ptr [esi+ecx*4+1Ch]
    L_0045c260:
        mov dword ptr [edi+ecx*4+1Ch],eax
    L_0045c264:
        mov eax,dword ptr [esi+ecx*4+18h]
    L_0045c268:
        mov dword ptr [edi+ecx*4+18h],eax
    L_0045c26c:
        mov eax,dword ptr [esi+ecx*4+14h]
    L_0045c270:
        mov dword ptr [edi+ecx*4+14h],eax
    L_0045c274:
        mov eax,dword ptr [esi+ecx*4+10h]
    L_0045c278:
        mov dword ptr [edi+ecx*4+10h],eax
    L_0045c27c:
        mov eax,dword ptr [esi+ecx*4+0Ch]
    L_0045c280:
        mov dword ptr [edi+ecx*4+0Ch],eax
    L_0045c284:
        mov eax,dword ptr [esi+ecx*4+8]
    L_0045c288:
        mov dword ptr [edi+ecx*4+8],eax
    L_0045c28c:
        mov eax,dword ptr [esi+ecx*4+4]
    L_0045c290:
        mov dword ptr [edi+ecx*4+4],eax
    L_0045c294:
        lea eax,[ecx*4]
    L_0045c29b:
        add esi,eax
    L_0045c29d:
        add edi,eax
    L_0045c29f:
        jmp dword ptr [edx*4+45C2A8h]
    }
}

// 0x0045C2B8..0x0045C2BE: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c2b8() {
    __asm {
    L_0045c2b8:
        mov eax,dword ptr [ebp+8]
    L_0045c2bb:
        pop esi
    L_0045c2bc:
        pop edi
    L_0045c2bd:
        leave
    L_0045c2be:
        ret
    }
}

// 0x0045C2C0..0x0045C2CC: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c2c0() {
    __asm {
    L_0045c2c0:
        mov al,byte ptr [esi+3]
    L_0045c2c3:
        mov byte ptr [edi+3],al
    L_0045c2c6:
        mov eax,dword ptr [ebp+8]
    L_0045c2c9:
        pop esi
    L_0045c2ca:
        pop edi
    L_0045c2cb:
        leave
    L_0045c2cc:
        ret
    }
}

// 0x0045C2D0..0x0045C2E2: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c2d0() {
    __asm {
    L_0045c2d0:
        mov al,byte ptr [esi+3]
    L_0045c2d3:
        mov byte ptr [edi+3],al
    L_0045c2d6:
        mov al,byte ptr [esi+2]
    L_0045c2d9:
        mov byte ptr [edi+2],al
    L_0045c2dc:
        mov eax,dword ptr [ebp+8]
    L_0045c2df:
        pop esi
    L_0045c2e0:
        pop edi
    L_0045c2e1:
        leave
    L_0045c2e2:
        ret
    }
}

// 0x0045C2E4..0x0045C2FC: _memcpy
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcpy_part_0045c2e4() {
    __asm {
    L_0045c2e4:
        mov al,byte ptr [esi+3]
    L_0045c2e7:
        mov byte ptr [edi+3],al
    L_0045c2ea:
        mov al,byte ptr [esi+2]
    L_0045c2ed:
        mov byte ptr [edi+2],al
    L_0045c2f0:
        mov al,byte ptr [esi+1]
    L_0045c2f3:
        mov byte ptr [edi+1],al
    L_0045c2f6:
        mov eax,dword ptr [ebp+8]
    L_0045c2f9:
        pop esi
    L_0045c2fa:
        pop edi
    L_0045c2fb:
        leave
    L_0045c2fc:
        ret
    }
}
