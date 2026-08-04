// MSVC-only exact overlay for the enemy death sweep and timer interpolation
// (retail 0x0040E6A0). The readable semantic reconstruction lives in
// enemy_lifecycle.cpp; this translation unit keeps the overlay free of
// C++11 so the MSVC 7.1 hybrid build can compile it.
#ifdef _MSC_VER
extern "C" int sub_448DB0(void*, int, int, int);
extern "C" void* dword_477704;
extern "C" float flt_470B68;
extern "C" float flt_470B64;
extern "C" float flt_470AFC;
extern "C" long __cdecl __ftol2(void);

__declspec(naked) int Enemy_DeathSweepRetail() {
    __asm {
        push ebp
        mov ebp, [esp+8]
        mov eax, [ebp+58h]
        test eax, eax
        jz loc_40E707
        push ebx
        push esi
        push edi
        nop
loc_40E6B0:
        mov esi, [eax]
        mov ebx, [eax+4]
        mov eax, [esi+2480h]
        test al, 50h
        jnz loc_40E6C4
        test ah, 0C0h
        jz loc_40E6C8
loc_40E6C4:
        test al, al
        jns loc_40E6FE
loc_40E6C8:
        mov eax, [esi+2448h]
        test eax, eax
        jl loc_40E6F4
        mov ecx, [esi+244Ch]
        mov edx, dword ptr [dword_477704]
        push eax
        lea eax, [esp+18h]
        push eax
        mov eax, [edx+ecx*4+30h]
        lea edi, [esi+1068h]
        push eax
        call sub_448DB0
loc_40E6F4:
        or dword ptr [esi+2480h], 20000h
loc_40E6FE:
        test ebx, ebx
        mov eax, ebx
        jnz loc_40E6B0
        pop edi
        pop esi
        pop ebx
loc_40E707:
        mov edx, [ebp+44h]
        mov ecx, [ebp+4Ch]
        mov [ebp+40h], edx
        fld dword ptr [ecx]
        fcomp dword ptr [flt_470B68]
        fnstsw ax
        test ah, 41h
        jnz loc_40E742
        fld dword ptr [ecx]
        fcomp dword ptr [flt_470B64]
        fnstsw ax
        test ah, 5
        jp loc_40E742
        fld dword ptr [ebp+48h]
        inc edx
        fadd dword ptr [flt_470AFC]
        mov [ebp+44h], edx
        fstp dword ptr [ebp+48h]
        pop ebp
        ret 4
loc_40E742:
        fld dword ptr [ecx]
        fadd dword ptr [ebp+48h]
        fst dword ptr [ebp+48h]
        call __ftol2
        mov [ebp+44h], eax
        pop ebp
        ret 4
    }
}
#endif
