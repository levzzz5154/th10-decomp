// MSVC-only exact overlay for the MIDI worker message pump (retail
// 0x0043E3A0). The readable semantic reconstruction lives in
// midi_worker.cpp; this translation unit keeps the overlay free of C++11 so
// the MSVC 7.1 hybrid build can compile it.
#ifdef _MSC_VER
extern "C" void* __imp_PeekMessageA;
extern "C" void* __imp_MsgWaitForMultipleObjects;
extern "C" void sub_44D850(void*, void*);
extern "C" unsigned long dword_497798;

__declspec(naked) int MidiWorker_MessageLoopRetail() {
    __asm {
        sub esp, 20h
        push ebx
        mov ebx, dword ptr [__imp_PeekMessageA]
        push ebp
        mov ebp, dword ptr [__imp_MsgWaitForMultipleObjects]
        push esi
        mov dword ptr [esp+0Ch], 0
        mov esi, 1
        nop
loc_43E3C0:
        push 0BFh
        push 0FFFFFFFFh
        push 0
        push 49779Ch
        push esi
        call ebp
        mov ecx, dword ptr [dword_497798]
        test ecx, ecx
        jnz loc_43E3DF
        mov [esp+0Ch], esi
loc_43E3DF:
        sub eax, 0
        jz loc_43E41F
        dec eax
        jnz loc_43E446
        push esi
        push 0
        push 0
        push 0
        lea eax, [esp+20h]
        push eax
        call ebx
        test eax, eax
        jz loc_43E446
        _emit 8Dh
        _emit 0A4h
        _emit 24h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
loc_43E400:
        cmp dword ptr [esp+14h], 12h
        jnz loc_43E40B
        mov [esp+0Ch], esi
loc_43E40B:
        push esi
        push 0
        push 0
        push 0
        lea ecx, [esp+20h]
        push ecx
        call ebx
        test eax, eax
        jnz loc_43E400
        jmp loc_43E446
loc_43E41F:
        test ecx, ecx
        jz loc_43E446
        mov eax, [ecx+30h]
        test eax, eax
        jz loc_43E446
        mov [ecx+74h], esi
        mov edx, dword ptr [dword_497798]
        push esi
        push edx
        call sub_44D850
        mov eax, dword ptr [dword_497798]
        mov dword ptr [eax+74h], 0
loc_43E446:
        mov eax, [esp+0Ch]
        test eax, eax
        jz loc_43E3C0
        pop esi
        pop ebp
        xor eax, eax
        pop ebx
        add esp, 20h
        ret 4
    }
}
#endif
