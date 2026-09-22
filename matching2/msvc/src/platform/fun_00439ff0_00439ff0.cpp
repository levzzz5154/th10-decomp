#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3604): closest_byte_count=0/442; first_diff=unmeasured;
// residual_class=security-cookie frame, indirect Win32 import slots, local
// STARTUPINFO/buffer layout, and private caller/callee ABI through 0x0043A290,
// 0x0044B8E0, and 0x0044B4D0.
// variants_tested=live Ghidra decompilation, caller GameMain 0x00438AD0,
// callee cluster inspection, readable import-slot candidate (MSVC C2371/C2040),
// and exact retail wrapper baseline.
// next_lever=native-LTCG cluster over GameMain, this entry, 0x0043A290,
// 0x0044B8E0, and 0x0044B4D0 with import-slot declarations retained.
// 0x00438AD0..0x0043900C: GameMain
// Naked body preserves the retail register/stack ABI.

// 0x00439FF0..0x0043A11C: FUN_00439ff0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00439ff0_00439ff0() {
    __asm {
    L_00439ff0:
        sub esp,258h
    L_00439ff6:
        mov eax,dword ptr [data_00473660]
    L_00439ffb:
        xor eax,esp
    L_00439ffd:
        push edi
    L_00439ffe:
        push 46F3ACh
    L_0043a003:
        push 1
    L_0043a005:
        push 0
    L_0043a007:
        mov dword ptr [esp+264h],eax
    L_0043a00e:
        call dword ptr [data_00466110]
    L_0043a014:
        mov dword ptr [data_00497ba8],eax
    L_0043a019:
        call dword ptr [data_0046610c]
    L_0043a01f:
        cmp eax,0B7h
    L_0043a024:
        jne short L_0043a051
    L_0043a026:
        push 46F394h
    L_0043a02b:
        mov edi,474F70h
    L_0043a030:
        call asm_TextLog_AppendLine_0044b8e0
    L_0043a035:
        add esp,4
    L_0043a038:
        or eax,0FFFFFFFFh
    L_0043a03b:
        pop edi
    L_0043a03c:
        mov ecx,dword ptr [esp+254h]
    L_0043a043:
        xor ecx,esp
    L_0043a045:
        call asm_security_check_cookie_00458ea5
    L_0043a04a:
        add esp,258h
    L_0043a050:
        ret
    L_0043a051:
        xor eax,eax
    L_0043a053:
        mov dword ptr [esp+4],44h
    L_0043a05b:
        mov ecx,10h
    L_0043a060:
        lea edi,[esp+8]
    L_0043a064:
        rep stosd
    L_0043a066:
        push 105h
    L_0043a06b:
        lea eax,[esp+154h]
    L_0043a072:
        push eax
    L_0043a073:
        push 0
    L_0043a075:
        call dword ptr [data_004660dc]
    L_0043a07b:
        push 105h
    L_0043a080:
        lea ecx,[esp+4Ch]
    L_0043a084:
        push ecx
    L_0043a085:
        call dword ptr [data_00466100]
    L_0043a08b:
        lea edx,[esp+4]
    L_0043a08f:
        push edx
    L_0043a090:
        call dword ptr [data_00466108]
    L_0043a096:
        mov eax,dword ptr [esp+10h]
    L_0043a09a:
        test eax,eax
    L_0043a09c:
        je asm_target_0043a179
    L_0043a0a2:
        push esi
    L_0043a0a3:
        push 2Eh
    L_0043a0a5:
        push eax
    L_0043a0a6:
        call asm_strrchr_00452930
    L_0043a0ab:
        mov esi,eax
    L_0043a0ad:
        mov eax,dword ptr [esp+1Ch]
    L_0043a0b1:
        add esp,8
    L_0043a0b4:
        push eax
    L_0043a0b5:
        call asm_File_ProbeExists_0044b4d0
    L_0043a0ba:
        test eax,eax
    L_0043a0bc:
        je asm_target_0043a16e
    L_0043a0c2:
        test esi,esi
    L_0043a0c4:
        je asm_target_0043a16e
    L_0043a0ca:
        push ebx
    L_0043a0cb:
        push 46F38Ch
    L_0043a0d0:
        push esi
    L_0043a0d1:
        call asm_stricmp_0046054e
    L_0043a0d6:
        add esp,8
    L_0043a0d9:
        test eax,eax
    L_0043a0db:
        jne short L_0043a111
    L_0043a0dd:
        TH10_NOP_LEA_ECX_DISP8()
    L_0043a0e0:
        mov ecx,dword ptr [esp+18h]
    L_0043a0e4:
        push ecx
    L_0043a0e5:
        mov edi,104h
    L_0043a0ea:
        lea ebx,[esp+54h]
    L_0043a0ee:
        call asm_FUN_0043a290_0043a290
    L_0043a0f3:
        mov edx,ebx
    L_0043a0f5:
        push 2Eh
    L_0043a0f7:
        push edx
    L_0043a0f8:
        call asm_strrchr_00452930
    L_0043a0fd:
        push 46F38Ch
    L_0043a102:
        push eax
    L_0043a103:
        call asm_stricmp_0046054e
    L_0043a108:
        add esp,10h
    L_0043a10b:
        test eax,eax
    L_0043a10d:
        je short L_0043a0e0
    L_0043a10f:
        TH10_REL8(0xeb, 0x0043a10f, VA_asm_target_0043a12a)
    L_0043a111:
        mov eax,dword ptr [esp+18h]
    L_0043a115:
        lea edx,[esp+50h]
    L_0043a119:
        sub edx,eax
    L_0043a11b:
        TH10_REL8(0xeb, 0x0043a11b, VA_asm_FUN_00439ff0_part_0043a120)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0043a120:
        mov cl,byte ptr [eax]
    L_0043a122:
        mov byte ptr [edx+eax],cl
    L_0043a125:
        inc eax
    L_0043a126:
        test cl,cl
    L_0043a128:
        jne short L_0043a120
    L_0043a12a:
        lea esi,[esp+50h]
    L_0043a12e:
        lea eax,[esp+158h]
    L_0043a135:
        mov dl,byte ptr [eax]
    L_0043a137:
        mov bl,byte ptr [esi]
    L_0043a139:
        mov cl,dl
    L_0043a13b:
        cmp dl,bl
    L_0043a13d:
        jne short L_0043a15d
    L_0043a13f:
        test cl,cl
    L_0043a141:
        je short L_0043a159
    L_0043a143:
        mov dl,byte ptr [eax+1]
    L_0043a146:
        mov bl,byte ptr [esi+1]
    L_0043a149:
        mov cl,dl
    L_0043a14b:
        cmp dl,bl
    L_0043a14d:
        jne short L_0043a15d
    L_0043a14f:
        add eax,2
    L_0043a152:
        add esi,2
    L_0043a155:
        test cl,cl
    L_0043a157:
        jne short L_0043a135
    L_0043a159:
        xor eax,eax
    L_0043a15b:
        jmp short L_0043a162
    L_0043a15d:
        sbb eax,eax
    L_0043a15f:
        sbb eax,0FFFFFFFFh
    L_0043a162:
        test eax,eax
    L_0043a164:
        pop ebx
    L_0043a165:
        je short L_0043a16e
    L_0043a167:
        mov byte ptr [data_00492518],1
    L_0043a16e:
        mov eax,dword ptr [data_00491ff4]
    L_0043a173:
        and eax,0FFFFFFBFh
    L_0043a176:
        pop esi
    L_0043a177:
        jmp short L_0043a181
    L_0043a179:
        mov eax,dword ptr [data_00491ff4]
    L_0043a17e:
        or eax,40h
    L_0043a181:
        mov edx,dword ptr [data_00497ba8]
    L_0043a187:
        mov ecx,dword ptr [esp+258h]
    L_0043a18e:
        mov dword ptr [data_00491ff4],eax
    L_0043a193:
        xor eax,eax
    L_0043a195:
        test edx,edx
    L_0043a197:
        setne al
    L_0043a19a:
        pop edi
    L_0043a19b:
        xor ecx,esp
    L_0043a19d:
        dec eax
    L_0043a19e:
        call asm_security_check_cookie_00458ea5
    L_0043a1a3:
        add esp,258h
    L_0043a1a9:
        ret
    }
}
