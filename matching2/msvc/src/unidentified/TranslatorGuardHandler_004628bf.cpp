#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004628BF..0x0046296A: TranslatorGuardHandler
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_TranslatorGuardHandler_004628bf() {
    __asm {
    L_004628bf:
        push ebp
    L_004628c0:
        mov ebp,esp
    L_004628c2:
        push ecx
    L_004628c3:
        push ebx
    L_004628c4:
        cld
    L_004628c5:
        mov eax,dword ptr [ebp+0Ch]
    L_004628c8:
        mov eax,dword ptr [eax+8]
    L_004628cb:
        cmp eax,dword ptr [data_00473660]
    L_004628d1:
        je short L_004628ea
    L_004628d3:
        mov eax,dword ptr [ebp+8]
    L_004628d6:
        mov eax,dword ptr [eax+4]
    L_004628d9:
        or eax,8
    L_004628dc:
        mov ecx,dword ptr [ebp+8]
    L_004628df:
        mov dword ptr [ecx+4],eax
    L_004628e2:
        xor eax,eax
    L_004628e4:
        inc eax
    L_004628e5:
        jmp asm_TranslatorGuardHandler_part_0046296e
    L_004628ea:
        mov eax,dword ptr [ebp+8]
    L_004628ed:
        mov eax,dword ptr [eax+4]
    L_004628f0:
        and eax,66h
    L_004628f3:
        je short L_00462904
    L_004628f5:
        mov eax,dword ptr [ebp+0Ch]
    L_004628f8:
        mov dword ptr [eax+24h],1
    L_004628ff:
        xor eax,eax
    L_00462901:
        inc eax
    L_00462902:
        TH10_REL8(0xeb, 0x00462902, VA_asm_TranslatorGuardHandler_part_0046296e)
    L_00462904:
        push 1
    L_00462906:
        mov eax,dword ptr [ebp+0Ch]
    L_00462909:
        push dword ptr [eax+18h]
    L_0046290c:
        mov eax,dword ptr [ebp+0Ch]
    L_0046290f:
        push dword ptr [eax+14h]
    L_00462912:
        mov eax,dword ptr [ebp+0Ch]
    L_00462915:
        push dword ptr [eax+0Ch]
    L_00462918:
        push 0
    L_0046291a:
        push dword ptr [ebp+10h]
    L_0046291d:
        mov eax,dword ptr [ebp+0Ch]
    L_00462920:
        push dword ptr [eax+10h]
    L_00462923:
        push dword ptr [ebp+8]
    L_00462926:
        call asm_InternalCxxFrameHandler_00463963
    L_0046292b:
        add esp,20h
    L_0046292e:
        mov eax,dword ptr [ebp+0Ch]
    L_00462931:
        cmp dword ptr [eax+24h],0
    L_00462935:
        jne short L_00462942
    L_00462937:
        push dword ptr [ebp+8]
    L_0046293a:
        push dword ptr [ebp+0Ch]
    L_0046293d:
        call asm_UnwindNestedFrames_0046271b
    L_00462942:
        push 0
    L_00462944:
        push 0
    L_00462946:
        push 0
    L_00462948:
        push 0
    L_0046294a:
        push 0
    L_0046294c:
        lea eax,[ebp-4]
    L_0046294f:
        push eax
    L_00462950:
        push 123h
    L_00462955:
        call asm_CallSETranslator_004627f8
    L_0046295a:
        add esp,1Ch
    L_0046295d:
        mov eax,dword ptr [ebp-4]
    L_00462960:
        mov ebx,dword ptr [ebp+0Ch]
    L_00462963:
        mov esp,dword ptr [ebx+1Ch]
    L_00462966:
        mov ebp,dword ptr [ebx+20h]
    L_00462969:
        jmp eax
    }
}

// 0x0046296E..0x00462970: TranslatorGuardHandler
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_TranslatorGuardHandler_part_0046296e() {
    __asm {
    L_0046296e:
        pop ebx
    L_0046296f:
        leave
    L_00462970:
        ret
    }
}
