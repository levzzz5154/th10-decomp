#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453111..0x0045318C: FUN_00453111
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00453111_00453111() {
    __asm {
    L_00453111:
        push 128h
    L_00453116:
        push 46A750h
    L_0045311b:
        call asm_SEH_prolog_00454bbc
    L_00453120:
        mov eax,dword ptr [data_00473660]
    L_00453125:
        xor eax,ebp
    L_00453127:
        mov dword ptr [ebp-1Ch],eax
    L_0045312a:
        mov eax,dword ptr [ebp+8]
    L_0045312d:
        lea edi,[ebp-124h]
    L_00453133:
        xor ebx,ebx
    L_00453135:
        mov dword ptr [ebp-130h],ebx
    L_0045313b:
        or dword ptr [ebp-12Ch],0FFFFFFFFh
    L_00453142:
        push eax
    L_00453143:
        call dword ptr [data_004661a0]
    L_00453149:
        test eax,eax
    L_0045314b:
        je asm_target_00453221
    L_00453151:
        mov eax,edi
    L_00453153:
        push eax
    L_00453154:
        push 105h
    L_00453159:
        call dword ptr [data_004661a4]
    L_0045315f:
        mov esi,eax
    L_00453161:
        mov dword ptr [ebp-134h],esi
    L_00453167:
        cmp esi,104h
    L_0045316d:
        TH10_REL8(0x7e, 0x0045316d, VA_asm_target_004531d2)
    L_0045316f:
        mov dword ptr [ebp-4],ebx
    L_00453172:
        lea eax,[esi+1]
    L_00453175:
        add eax,3
    L_00453178:
        and eax,0FFFFFFFCh
    L_0045317b:
        call asm_chkstk_00458ec0
    L_00453180:
        mov dword ptr [ebp-18h],esp
    L_00453183:
        mov edi,esp
    L_00453185:
        mov dword ptr [ebp-138h],edi
    L_0045318b:
        TH10_REL8(0xeb, 0x0045318b, VA_asm_FUN_00453111_part_004531bf)
        _emit 0x33
        _emit 0xc0
        _emit 0x40
        _emit 0xc3
        _emit 0x8b
        _emit 0x65
        _emit 0xe8
        _emit 0xe8
        _emit 0xf8
        _emit 0x5b
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xb5
        _emit 0xcc
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x8d
        _emit 0x46
        _emit 0x01
        _emit 0x50
        _emit 0xe8
        _emit 0x5e
        _emit 0xf5
        _emit 0xff
        _emit 0xff
        _emit 0x59
        _emit 0x8b
        _emit 0xf8
        _emit 0x33
        _emit 0xdb
        _emit 0x3b
        _emit 0xfb
        _emit 0x75
        _emit 0x04
        _emit 0x33
        _emit 0xf6
        _emit 0xeb
        _emit 0x0a
        _emit 0xc7
        _emit 0x85
        _emit 0xd0
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_004531bf:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004531c3:
        cmp esi,ebx
    L_004531c5:
        je short L_00453221
    L_004531c7:
        push edi
    L_004531c8:
        inc esi
    L_004531c9:
        push esi
    L_004531ca:
        call dword ptr [data_004661a4]
    L_004531d0:
        mov esi,eax
    L_004531d2:
        cmp esi,ebx
    L_004531d4:
        je short L_00453221
    L_004531d6:
        mov al,byte ptr [edi]
    L_004531d8:
        cmp al,5Ch
    L_004531da:
        je short L_004531e0
    L_004531dc:
        cmp al,2Fh
    L_004531de:
        jne short L_004531e5
    L_004531e0:
        cmp al,byte ptr [edi+1]
    L_004531e3:
        je short L_0045321b
    L_004531e5:
        mov byte ptr [ebp-128h],3Dh
    L_004531ec:
        movzx eax,byte ptr [edi]
    L_004531ef:
        push eax
    L_004531f0:
        call asm_mbctoupper_00458d0c
    L_004531f5:
        pop ecx
    L_004531f6:
        mov byte ptr [ebp-127h],al
    L_004531fc:
        mov byte ptr [ebp-126h],3Ah
    L_00453203:
        mov byte ptr [ebp-125h],bl
    L_00453209:
        push edi
    L_0045320a:
        lea eax,[ebp-128h]
    L_00453210:
        push eax
    L_00453211:
        call dword ptr [data_004661a8]
    L_00453217:
        test eax,eax
    L_00453219:
        je short L_00453221
    L_0045321b:
        mov dword ptr [ebp-12Ch],ebx
    L_00453221:
        call dword ptr [data_0046610c]
    L_00453227:
        push eax
    L_00453228:
        call asm_dosmaperr_00456b04
    L_0045322d:
        pop ecx
    L_0045322e:
        cmp dword ptr [ebp-130h],ebx
    L_00453234:
        je short L_0045323d
    L_00453236:
        push edi
    L_00453237:
        call asm_free_00452422
    L_0045323c:
        pop ecx
    L_0045323d:
        mov eax,dword ptr [ebp-12Ch]
    L_00453243:
        lea esp,[ebp-144h]
    L_00453249:
        mov ecx,dword ptr [ebp-1Ch]
    L_0045324c:
        xor ecx,ebp
    L_0045324e:
        call asm_security_check_cookie_00458ea5
    L_00453253:
        call asm_SEH_epilog_00454bf7
    L_00453258:
        ret
    }
}
