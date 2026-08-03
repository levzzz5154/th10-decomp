// MSVC-only exact overlay for the DirectInput joystick property setter
// (retail 0x0044C7E0). The readable semantic reconstruction lives in
// joystick_property.cpp; this translation unit keeps the overlay free of
// C++11 so the MSVC 7.1 hybrid build can compile it.
#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"

extern "C" unsigned long ___security_cookie;
extern "C" void __stdcall security_check_cookie(unsigned long);

__declspec(naked) int Input_SetJoystickPropertyRetail() {
    __asm {
        sub esp, 40h
        mov eax, ___security_cookie
        xor eax, esp
        mov [esp+3Ch], eax
        mov eax, [esp+44h]
        mov eax, [eax]
        test eax, eax
        push esi
        mov esi, ecx
        mov dword ptr [esp+4], 0
        jnz loc_44C81A
        mov eax, 800401F0h
        pop esi
        mov ecx, [esp+3Ch]
        xor ecx, esp
        call security_check_cookie
        add esp, 40h
        ret 4
loc_44C81A:
        xor ecx, ecx
        mov [esp+1Ch], ecx
        mov [esp+20h], ecx
        mov [esp+24h], ecx
        mov [esp+28h], ecx
        mov [esp+2Ch], ecx
        mov [esp+30h], ecx
        mov [esp+34h], ecx
        mov [esp+38h], ecx
        push ecx
        mov [esp+40h], ecx
        mov [esp+28h], ecx
        mov [esp+30h], ecx
        lea ecx, [esp+8]
        push ecx
        lea ecx, [esp+24h]
        push ecx
        mov dword ptr [esp+28h], 24h
        mov dword ptr [esp+2Ch], 1
        mov edx, [eax]
        push eax
        call dword ptr [edx+0Ch]
        test eax, eax
        jl loc_44C8D2
        xor edx, edx
        mov [esp+8], edx
        mov [esp+0Ch], edx
        mov [esp+10h], edx
        mov [esp+14h], edx
        mov word ptr [esp+16h], si
        shr si, 3
        mov word ptr [esp+18h], dx
        lea edx, [esp+8]
        push edx
        mov word ptr [esp+0Ch], 1
        mov word ptr [esp+0Eh], bx
        mov [esp+10h], edi
        imul esi, ebx
        movzx eax, si
        imul eax, edi
        mov [esp+14h], eax
        mov eax, [esp+8]
        mov word ptr [esp+18h], si
        mov ecx, [eax]
        push eax
        call dword ptr [ecx+38h]
        test eax, eax
        jl loc_44C8D2
        mov eax, [esp+4]
        test eax, eax
        jz loc_44C8D0
        mov ecx, [eax]
        push eax
        call dword ptr [ecx+8]
loc_44C8D0:
        xor eax, eax
loc_44C8D2:
        mov ecx, [esp+40h]
        pop esi
        xor ecx, esp
        call security_check_cookie
        add esp, 40h
        ret 4
    }
}
#endif
