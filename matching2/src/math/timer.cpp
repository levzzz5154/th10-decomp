// =============================================================================
// timer.cpp - Readable frame-timer advancement from 0x00404ED0
// =============================================================================
#include "th10/math/timer.hpp"

extern float _DAT_00470afc;      // 1.0f
extern float _DAT_00470b68;      // normal-speed lower bound
extern float _DAT_00470b64;      // normal-speed upper bound
extern float DAT_00476f78;       // default speed (1.0f)

#ifdef _MSC_VER
extern "C" float flt_470B68;
extern "C" float flt_470B64;
extern "C" float flt_470AFC;
extern "C" float flt_476F78;
extern "C" long __cdecl __ftol2(void);
#endif

#ifdef _MSC_VER
__declspec(naked) void FrameTimer_Tick(FrameTimer* timer) {
    __asm {
        mov edx, [esi+4]
        mov ecx, [esi+0Ch]
        mov [esi], edx
        fld dword ptr [ecx]
        fcomp dword ptr [flt_470B68]
        fnstsw ax
        test ah, 41h
        jnz loc_404F07
        fld dword ptr [ecx]
        fcomp dword ptr [flt_470B64]
        fnstsw ax
        test ah, 5
        jp loc_404F07
        fld dword ptr [esi+8]
        inc edx
        fadd dword ptr [flt_470AFC]
        mov [esi+4], edx
        fstp dword ptr [esi+8]
        ret
loc_404F07:
        fld dword ptr [ecx]
        fadd dword ptr [esi+8]
        fst dword ptr [esi+8]
        call __ftol2
        mov [esi+4], eax
        ret
    }
}
#else
void FrameTimer_Tick(FrameTimer* timer) {
    timer->previous = timer->current;

    const float speed = *timer->speed;
    if (_DAT_00470b68 < speed && speed < _DAT_00470b64) {
        ++timer->current;
        timer->elapsed += _DAT_00470afc;
        return;
    }

    timer->elapsed += speed;
    timer->current = (int)timer->elapsed;
}
#endif

// 0x0044BF40 / 0x00428DD0 - Advance a timer by an explicit delta while
// retaining the retail previous/current and speed-dependent accumulation.
#ifdef _MSC_VER
__declspec(naked) void FrameTimer_Advance(FrameTimer* timer, float delta) {
    __asm {
        mov eax, [esi+4]
        mov ecx, [esi+0Ch]
        mov [esi], eax
        fld dword ptr [ecx]
        fcomp dword ptr [flt_470B68]
        fnstsw ax
        test ah, 41h
        jnz loc_44BF7E
        fld dword ptr [ecx]
        fcomp dword ptr [flt_470B64]
        fnstsw ax
        test ah, 5
        jp loc_44BF7E
        fld [esp+4]
        fadd dword ptr [esi+8]
        fstp dword ptr [esi+8]
        fld dword ptr [esi+8]
        call __ftol2
        mov [esi+4], eax
        ret 4
loc_44BF7E:
        fld [esp+4]
        fmul dword ptr [ecx]
        fadd dword ptr [esi+8]
        fstp dword ptr [esi+8]
        fld dword ptr [esi+8]
        call __ftol2
        mov [esi+4], eax
        ret 4
    }
}
#else
void FrameTimer_Advance(FrameTimer* timer, float delta) {
    timer->previous = timer->current;
    const float speed = *timer->speed;
    if (_DAT_00470b68 < speed && speed < _DAT_00470b64)
        timer->elapsed += delta;
    else
        timer->elapsed += delta * speed;
    timer->current = (int)timer->elapsed;
}
#endif

// 0x0042C620 - Store the owner value and reset the embedded state timer.
#ifdef _MSC_VER
__declspec(naked) void GameState_SetTimerTarget(
        unsigned char* state, int owner_value,
        int target, const float* speed) {
    __asm {
        mov [eax+20h], ecx
        mov ecx, [eax+2C0h]
        xor edx, edx
        test cl, 1
        jnz loc_42C659
        or ecx, 1
        mov [eax+2B4h], edx
        mov dword ptr [eax+2B0h], 0FFF0BDC1h
        mov [eax+2B8h], edx
        mov dword ptr [eax+2BCh], offset flt_476F78
        mov [eax+2C0h], ecx
loc_42C659:
        mov [eax+2B4h], edx
        mov [eax+2B8h], edx
        mov dword ptr [eax+2B0h], 0FFFFFFFFh
        ret
    }
}
#else
void GameState_SetTimerTarget(unsigned char* state, int owner_value,
                              int target, const float* speed) {
    *(int*)(state + 0x20) = owner_value;
    unsigned int* flags = (unsigned int*)(state + 0x2C0);
    if ((*flags & 1u) == 0) {
        *(int*)(state + 0x2B4) = 0;
        *(int*)(state + 0x2B0) = (int)0xFFF0BDC1;
        *(int*)(state + 0x2B8) = 0;
        *(const float**)(state + 0x2BC) = speed;
        *flags |= 1u;
    }
    *(int*)(state + 0x2B4) = 0;
    *(int*)(state + 0x2B8) = 0;
    *(int*)(state + 0x2B0) = target - 1;
}
#endif

// 0x0042C5C0 - Set the timer owner, clear the previous value at +0x20, and
// disable the timer by resetting the target to -1. The default speed pointer
// is wired to the global DAT_00476f78 the first time the sentinel initializes.
#ifdef _MSC_VER
__declspec(naked) void GameState_DisableTimerWithOwner(void* state, int owner) {
    __asm {
        xor edx, edx
        mov [eax+1Ch], ecx
        mov [eax+20h], edx
        mov ecx, [eax+2C0h]
        test cl, 1
        jnz loc_42C5FC
        or ecx, 1
        mov [eax+2B4h], edx
        mov dword ptr [eax+2B0h], 0FFF0BDC1h
        mov [eax+2B8h], edx
        mov dword ptr [eax+2BCh], offset flt_476F78
        mov [eax+2C0h], ecx
loc_42C5FC:
        mov [eax+2B4h], edx
        mov [eax+2B8h], edx
        mov dword ptr [eax+2B0h], 0FFFFFFFFh
        ret
    }
}
#else
void GameState_DisableTimerWithOwner(void* state, int owner) {
    unsigned char* bytes = (unsigned char*)state;
    *(int*)(bytes + 0x1C) = owner;
    *(int*)(bytes + 0x20) = 0;
    unsigned int* flags = (unsigned int*)(bytes + 0x2C0);
    if ((*flags & 1u) == 0) {
        *(int*)(bytes + 0x2B4) = 0;
        *(int*)(bytes + 0x2B0) = (int)0xFFF0BDC1;
        *(int*)(bytes + 0x2B8) = 0;
        *(const float**)(bytes + 0x2BC) = &DAT_00476f78;
        *flags |= 1u;
    }
    *(int*)(bytes + 0x2B4) = 0;
    *(int*)(bytes + 0x2B8) = 0;
    *(int*)(bytes + 0x2B0) = -1;
}
#endif

// 0x004050D0 - Lazily initialize and then disable the embedded timer at the
// +0x30 state offset, preserving the retail sentinel and flag transitions.
#ifdef _MSC_VER
__declspec(naked) void EmbeddedTimer_Reset(EmbeddedTimerState* timer,
                                           const float* speed) {
    __asm {
        mov ecx, [eax+40h]
        xor edx, edx
        test cl, 1
        jnz loc_4050F4
        or ecx, 1
        mov [eax+34h], edx
        mov dword ptr [eax+30h], 0FFF0BDC1h
        mov [eax+38h], edx
        mov dword ptr [eax+3Ch], offset flt_476F78
        mov [eax+40h], ecx
loc_4050F4:
        mov [eax+34h], edx
        mov [eax+38h], edx
        mov dword ptr [eax+30h], 0FFFFFFFFh
        ret
    }
}
#else
void EmbeddedTimer_Reset(EmbeddedTimerState* timer, const float* speed) {
    if ((timer->flags & 1u) == 0) {
        timer->current = 0;
        timer->target = (int)0xFFF0BDC1;
        timer->previous = 0;
        timer->speed = speed;
        timer->flags |= 1u;
    }
    timer->current = 0;
    timer->previous = 0;
    timer->target = -1;
}
#endif
