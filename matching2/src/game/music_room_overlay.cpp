// MSVC-only exact overlay for the per-shot parameter file loader (retail
// 0x00426520). The readable semantic reconstruction lives in
// music_room.cpp; this translation unit keeps the overlay free of C++11 so
// the MSVC 7.1 hybrid build can compile it.
#ifdef _MSC_VER
extern "C" void* sub_44B360(void*, int);
extern "C" double dbl_470C50;
extern "C" unsigned long dword_47476C[];
extern "C" unsigned long dword_474778[];
extern "C" unsigned long dword_491BF4[];
extern "C" unsigned long dword_491BF8[];

__declspec(naked) int ParameterFile_LoadAndRelocateRetail() {
    __asm {
        push 0
        push 0
        call sub_44B360
        test eax, eax
        mov [esi+45Ch], eax
        jnz loc_426537
        or eax, 0FFFFFFFFh
        ret
loc_426537:
        fld qword ptr [dbl_470C50]
        xor edx, edx
        fsin
        fld st(0)
        fmul dword ptr [eax+10h]
        fstp dword ptr [eax+18h]
        mov eax, [esi+45Ch]
        fld st(0)
        fmul dword ptr [eax+14h]
        fstp dword ptr [eax+1Ch]
        mov eax, [esi+45Ch]
        fld st(0)
        fmul dword ptr [eax+10h]
        fstp dword ptr [eax+18h]
        mov eax, [esi+45Ch]
        fmul dword ptr [eax+14h]
        fstp dword ptr [eax+1Ch]
        mov eax, [esi+45Ch]
        cmp [eax+2], dx
        jbe loc_426602
        push ebx
        mov ecx, 110h
        push edi
        jmp loc_426590
        _emit 8Dh
        _emit 9Bh
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
loc_426590:
        mov eax, [esi+45Ch]
        add [ecx+eax], eax
        mov eax, [esi+45Ch]
        mov eax, [ecx+eax]
        cmp byte ptr [eax], 0
        jl loc_4265EE
        jmp loc_4265B0
        _emit 8Dh
        _emit 0A4h
        _emit 24h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
loc_4265B0:
        mov edi, [eax+24h]
        mov edi, dword ptr dword_47476C[edi*4]
        mov [eax+24h], edi
        mov edi, [eax+28h]
        mov edi, dword ptr dword_474778[edi*4]
        mov [eax+28h], edi
        mov edi, [eax+2Ch]
        mov edi, dword ptr dword_491BF4[edi*4]
        mov [eax+2Ch], edi
        mov edi, [eax+30h]
        mov edi, dword ptr dword_491BF8[edi*4]
        mov [eax+30h], edi
        mov bl, [eax+34h]
        add eax, 34h
        test bl, bl
        jge loc_4265B0
loc_4265EE:
        mov eax, [esi+45Ch]
        movzx eax, word ptr [eax+2]
        inc edx
        add ecx, 8
        cmp edx, eax
        jl loc_426590
        pop edi
        pop ebx
loc_426602:
        xor eax, eax
        ret
    }
}
#endif
