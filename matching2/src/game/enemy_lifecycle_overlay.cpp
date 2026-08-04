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
extern "C" int sub_40DC80(void*);

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

// 0x0040D750 - Sweep the live enemy list each frame: advance the timer for
// enemies whose busy latch is clear, and release enemies whose timer is
// still armed. The trailing timer interpolation is the same shared tail as
// 0x0040E6A0.
__declspec(naked) int Enemy_TimerSweepRetail() {
    __asm {
        push esi
        mov esi, [edi+58h]
        test esi, esi
        jz loc_40D7A2
        push ebx
        _emit 8Dh
        _emit 0A4h
        _emit 24h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
loc_40D760:
        mov eax, [esi]
        test dword ptr [eax+2480h], 20000h
        mov ebx, [esi+4]
        jnz loc_40D78E
        add eax, 103Ch
        push eax
        call sub_40DC80
        test eax, eax
        jnz loc_40D78E
        mov esi, [esi]
        and dword ptr [esi+2480h], 0FFFFFBFFh
        jmp loc_40D79B
loc_40D78E:
        mov ecx, [esi]
        test ecx, ecx
        jz loc_40D79B
        mov eax, [ecx]
        push 1
        call dword ptr [eax+14h]
loc_40D79B:
        test ebx, ebx
        mov esi, ebx
        jnz loc_40D760
        pop ebx
loc_40D7A2:
        mov edx, [edi+44h]
        mov ecx, [edi+4Ch]
        mov [edi+40h], edx
        fld dword ptr [ecx]
        fcomp dword ptr [flt_470B68]
        pop esi
        fnstsw ax
        test ah, 41h
        jnz loc_40D7E0
        fld dword ptr [ecx]
        fcomp dword ptr [flt_470B64]
        fnstsw ax
        test ah, 5
        jp loc_40D7E0
        fld dword ptr [edi+48h]
        inc edx
        fadd dword ptr [flt_470AFC]
        mov [edi+44h], edx
        mov eax, 1
        fstp dword ptr [edi+48h]
        ret
loc_40D7E0:
        fld dword ptr [ecx]
        fadd dword ptr [edi+48h]
        fst dword ptr [edi+48h]
        call __ftol2
        mov [edi+44h], eax
        mov eax, 1
        ret
    }
}
#endif
