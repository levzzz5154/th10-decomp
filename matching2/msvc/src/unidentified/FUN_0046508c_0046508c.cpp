#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046508C..0x00465187: FUN_0046508c
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0046508c_0046508c() {
    __asm {
    L_0046508c:
        push ebp
    L_0046508d:
        mov ebp,esp
    L_0046508f:
        and esp,0FFFFFFF0h
    L_00465092:
        sub esp,84h
    L_00465098:
        mov eax,dword ptr [data_00473660]
    L_0046509d:
        xor eax,ebp
    L_0046509f:
        mov dword ptr [esp+80h],eax
    L_004650a6:
        mov eax,dword ptr [ebp+10h]
    L_004650a9:
        movzx ecx,word ptr [eax]
    L_004650ac:
        push ebx
    L_004650ad:
        push esi
    L_004650ae:
        mov esi,dword ptr [ebp+0Ch]
    L_004650b1:
        mov eax,dword ptr [esi]
    L_004650b3:
        dec eax
    L_004650b4:
        push edi
    L_004650b5:
        mov dword ptr [esp+0Ch],ecx
    L_004650b9:
        je short L_004650e6
    L_004650bb:
        dec eax
    L_004650bc:
        je short L_004650e2
    L_004650be:
        dec eax
    L_004650bf:
        je short L_004650de
    L_004650c1:
        dec eax
    L_004650c2:
        je short L_004650da
    L_004650c4:
        dec eax
    L_004650c5:
        je short L_004650e6
    L_004650c7:
        dec eax
    L_004650c8:
        dec eax
    L_004650c9:
        je short L_004650d2
    L_004650cb:
        dec eax
    L_004650cc:
        jne short L_00465142
    L_004650ce:
        push 10h
    L_004650d0:
        jmp short L_004650e8
    L_004650d2:
        mov dword ptr [esi],1
    L_004650d8:
        jmp short L_00465142
    L_004650da:
        push 12h
    L_004650dc:
        jmp short L_004650e8
    L_004650de:
        push 11h
    L_004650e0:
        jmp short L_004650e8
    L_004650e2:
        push 4
    L_004650e4:
        jmp short L_004650e8
    L_004650e6:
        push 8
    L_004650e8:
        pop ebx
    L_004650e9:
        push ecx
    L_004650ea:
        lea edi,[esi+18h]
    L_004650ed:
        push edi
    L_004650ee:
        push ebx
    L_004650ef:
        call asm_handle_exc_0045e648
    L_004650f4:
        add esp,0Ch
    L_004650f7:
        test eax,eax
    L_004650f9:
        jne short L_00465142
    L_004650fb:
        mov eax,dword ptr [ebp+8]
    L_004650fe:
        cmp eax,10h
    L_00465101:
        je short L_00465114
    L_00465103:
        cmp eax,16h
    L_00465106:
        je short L_00465114
    L_00465108:
        cmp eax,1Dh
    L_0046510b:
        je short L_00465114
    L_0046510d:
        and dword ptr [esp+50h],0FFFFFFFEh
    L_00465112:
        jmp short L_00465129
    L_00465114:
        mov ecx,dword ptr [esp+50h]
    L_00465118:
        fld qword ptr [esi+10h]
    L_0046511b:
        and ecx,0FFFFFFE3h
    L_0046511e:
        fstp qword ptr [esp+40h]
    L_00465122:
        or ecx,3
    L_00465125:
        mov dword ptr [esp+50h],ecx
    L_00465129:
        push edi
    L_0046512a:
        lea ecx,[esi+8]
    L_0046512d:
        push ecx
    L_0046512e:
        push eax
    L_0046512f:
        push ebx
    L_00465130:
        lea eax,[esp+1Ch]
    L_00465134:
        push eax
    L_00465135:
        lea eax,[esp+24h]
    L_00465139:
        push eax
    L_0046513a:
        call asm_raise_exc_0045e3a3
    L_0046513f:
        add esp,18h
    L_00465142:
        push 0FFFFh
    L_00465147:
        push dword ptr [esp+10h]
    L_0046514b:
        call asm_ctrlfp_0045ed87
    L_00465150:
        cmp dword ptr [esi],8
    L_00465153:
        pop ecx
    L_00465154:
        pop ecx
    L_00465155:
        je short L_0046516b
    L_00465157:
        cmp dword ptr [data_00473c90],0
    L_0046515e:
        jne short L_0046516b
    L_00465160:
        push esi
    L_00465161:
        call asm_FUN_0045e3a0_0045e3a0
    L_00465166:
        test eax,eax
    L_00465168:
        pop ecx
    L_00465169:
        jne short L_00465173
    L_0046516b:
        push dword ptr [esi]
    L_0046516d:
        call asm_FID_conflict___set_errno_from_matherr_0045e86c
    L_00465172:
        pop ecx
    L_00465173:
        mov ecx,dword ptr [esp+8Ch]
    L_0046517a:
        pop edi
    L_0046517b:
        pop esi
    L_0046517c:
        xor ecx,ebp
    L_0046517e:
        pop ebx
    L_0046517f:
        call asm_security_check_cookie_00458ea5
    L_00465184:
        mov esp,ebp
    L_00465186:
        pop ebp
    L_00465187:
        ret
    }
}
