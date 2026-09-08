#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462FE0..0x0046316B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00462fe0() {
    __asm {
    L_00462fe0:
        call asm_getptd_00456357
    L_00462fe5:
        xor ecx,ecx
    L_00462fe7:
        cmp dword ptr [eax+84h],ecx
    L_00462fed:
        setne cl
    L_00462ff0:
        mov al,cl
    L_00462ff2:
        ret
    L_00462ff3:
        mov eax,dword ptr [esp+4]
    L_00462ff7:
        test eax,eax
    L_00462ff9:
        push esi
    L_00462ffa:
        push edi
    L_00462ffb:
        mov edi,dword ptr [esp+10h]
    L_00462fff:
        je short L_00463062
    L_00463001:
        mov esi,dword ptr [eax]
    L_00463003:
        test esi,esi
    L_00463005:
        je short L_00463062
    L_00463007:
        cmp dword ptr [esi],0E06D7363h
    L_0046300d:
        jne short L_00463034
    L_0046300f:
        cmp dword ptr [esi+10h],3
    L_00463013:
        jne short L_00463034
    L_00463015:
        mov eax,dword ptr [esi+14h]
    L_00463018:
        cmp eax,19930520h
    L_0046301d:
        je short L_00463026
    L_0046301f:
        cmp eax,19930521h
    L_00463024:
        jne short L_00463034
    L_00463026:
        cmp dword ptr [esi+1Ch],0
    L_0046302a:
        jne short L_00463034
    L_0046302c:
        call asm_getptd_00456357
    L_00463031:
        mov esi,dword ptr [eax+7Ch]
    L_00463034:
        push dword ptr [esi+18h]
    L_00463037:
        push edi
    L_00463038:
        call asm_CreateFrameInfo_004629eb
    L_0046303d:
        pop ecx
    L_0046303e:
        pop ecx
    L_0046303f:
        call asm_getptd_00456357
    L_00463044:
        mov eax,dword ptr [eax+7Ch]
    L_00463047:
        mov dword ptr [edi+8],eax
    L_0046304a:
        call asm_getptd_00456357
    L_0046304f:
        mov eax,dword ptr [eax+80h]
    L_00463055:
        mov dword ptr [edi+0Ch],eax
    L_00463058:
        call asm_getptd_00456357
    L_0046305d:
        mov dword ptr [eax+7Ch],esi
    L_00463060:
        jmp short L_0046306a
    L_00463062:
        or dword ptr [edi+8],0FFFFFFFFh
    L_00463066:
        or dword ptr [edi+0Ch],0FFFFFFFFh
    L_0046306a:
        call asm_getptd_00456357
    L_0046306f:
        add eax,84h
    L_00463074:
        dec dword ptr [eax]
    L_00463076:
        call asm_getptd_00456357
    L_0046307b:
        cmp dword ptr [eax+84h],0
    L_00463082:
        pop edi
    L_00463083:
        pop esi
    L_00463084:
        jge short L_00463092
    L_00463086:
        call asm_getptd_00456357
    L_0046308b:
        and dword ptr [eax+84h],0
    L_00463092:
        xor eax,eax
    L_00463094:
        inc eax
    L_00463095:
        ret
    L_00463096:
        mov eax,dword ptr [esp+4]
    L_0046309a:
        test eax,eax
    L_0046309c:
        je short L_004630cb
    L_0046309e:
        mov eax,dword ptr [eax]
    L_004630a0:
        cmp dword ptr [eax],0E06D7363h
    L_004630a6:
        jne short L_004630cb
    L_004630a8:
        cmp dword ptr [eax+10h],3
    L_004630ac:
        jne short L_004630cb
    L_004630ae:
        mov ecx,dword ptr [eax+14h]
    L_004630b1:
        cmp ecx,19930520h
    L_004630b7:
        je short L_004630c1
    L_004630b9:
        cmp ecx,19930521h
    L_004630bf:
        jne short L_004630cb
    L_004630c1:
        cmp dword ptr [eax+1Ch],0
    L_004630c5:
        jne short L_004630cb
    L_004630c7:
        xor eax,eax
    L_004630c9:
        inc eax
    L_004630ca:
        ret
    L_004630cb:
        xor eax,eax
    L_004630cd:
        ret
    L_004630ce:
        push esi
    L_004630cf:
        mov esi,dword ptr [esp+8]
    L_004630d3:
        cmp dword ptr [esi+8],0FFFFFFFFh
    L_004630d7:
        je asm_target_0046316a
    L_004630dd:
        push esi
    L_004630de:
        call asm_FindAndUnlinkFrame_00462a34
    L_004630e3:
        cmp dword ptr [esp+10h],0
    L_004630e8:
        pop ecx
    L_004630e9:
        jne short L_00463151
    L_004630eb:
        call asm_getptd_00456357
    L_004630f0:
        mov eax,dword ptr [eax+7Ch]
    L_004630f3:
        cmp dword ptr [eax],0E06D7363h
    L_004630f9:
        jne short L_00463151
    L_004630fb:
        call asm_getptd_00456357
    L_00463100:
        mov eax,dword ptr [eax+7Ch]
    L_00463103:
        cmp dword ptr [eax+10h],3
    L_00463107:
        jne short L_00463151
    L_00463109:
        call asm_getptd_00456357
    L_0046310e:
        mov eax,dword ptr [eax+7Ch]
    L_00463111:
        cmp dword ptr [eax+14h],19930520h
    L_00463118:
        je short L_0046312b
    L_0046311a:
        call asm_getptd_00456357
    L_0046311f:
        mov eax,dword ptr [eax+7Ch]
    L_00463122:
        cmp dword ptr [eax+14h],19930521h
    L_00463129:
        jne short L_00463151
    L_0046312b:
        call asm_getptd_00456357
    L_00463130:
        mov eax,dword ptr [eax+7Ch]
    L_00463133:
        push dword ptr [eax+18h]
    L_00463136:
        call asm_IsExceptionObjectToBeDestroyed_00462a13
    L_0046313b:
        test eax,eax
    L_0046313d:
        pop ecx
    L_0046313e:
        je short L_00463151
    L_00463140:
        push 1
    L_00463142:
        call asm_getptd_00456357
    L_00463147:
        push dword ptr [eax+7Ch]
    L_0046314a:
        call asm_DestructExceptionObject_00462f7c
    L_0046314f:
        pop ecx
    L_00463150:
        pop ecx
    L_00463151:
        call asm_getptd_00456357
    L_00463156:
        mov ecx,dword ptr [esi+8]
    L_00463159:
        mov dword ptr [eax+7Ch],ecx
    L_0046315c:
        call asm_getptd_00456357
    L_00463161:
        mov ecx,dword ptr [esi+0Ch]
    L_00463164:
        mov dword ptr [eax+80h],ecx
    L_0046316a:
        pop esi
    L_0046316b:
        ret
    }
}
