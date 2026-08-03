#include "th10/game/weather_pool.hpp"

#ifdef _MSC_VER
extern "C" float flt_476F78;
extern "C" float flt_470B0C;
extern "C" float flt_470B68;
extern "C" float flt_470B64;
extern "C" float flt_470AFC;
extern "C" void sub_463B2C(void);
#endif

// 0x0042B6F0 - Advance every live droplet in the weather pool (retail walks
// 0x2D3 slots with a 0x40-byte stride). Each live slot sinks by
// gravity * gravity_scale, latches the previous frame value, then advances
// its frame counter: while the shared control word stays inside
// (span_low, span_high) the counter increments by one and the timer gains one
// frame step; otherwise the timer absorbs the control value and the counter
// is retruncated from the timer (retail _ftol). Slots past frame 0x3C retire.
#ifdef _MSC_VER
__declspec(naked) int EffectPool_UpdateDrops(
        RainDrop* drops, int count, float gravity,
        float gravity_scale, float span_low,
        float span_high, float frame_step,
        long long (*float_to_long)(float value)) {
    __asm {
        push esi
        mov esi, eax
        push edi
        add esi, 3E8h
        mov edi, 2D3h
        nop
drop_loop:
        mov al, [esi+14h]
        test al, al
        je next_drop
        fld dword ptr [flt_476F78]
        fmul dword ptr [flt_470B0C]
        fsubr dword ptr [esi-14h]
        fstp dword ptr [esi-14h]
        mov edx, [esi-4]
        mov ecx, [esi+4]
        mov [esi-8], edx
        fld dword ptr [ecx]
        fcomp dword ptr [flt_470B68]
        fnstsw ax
        test ah, 41h
        jne else_branch
        fld dword ptr [ecx]
        fcomp dword ptr [flt_470B64]
        fnstsw ax
        test ah, 5
        jp else_branch
        fld dword ptr [esi]
        inc edx
        fadd dword ptr [flt_470AFC]
        mov [esi-4], edx
        fstp dword ptr [esi]
        jmp after_control
else_branch:
        fld dword ptr [esi]
        fadd dword ptr [ecx]
        fst dword ptr [esi]
        call sub_463B2C
        mov [esi-4], eax
after_control:
        cmp dword ptr [esi-4], 3Ch
        jle next_drop
        mov byte ptr [esi+14h], 0
next_drop:
        add esi, 40h
        dec edi
        jne drop_loop
        pop edi
        mov eax, 1
        pop esi
        ret
    }
}
#else
int EffectPool_UpdateDrops(RainDrop* drops, int count, float gravity,
                           float gravity_scale, float span_low,
                           float span_high, float frame_step,
                           long long (*float_to_long)(float value)) {
    for (int index = 0; index < count; ++index) {
        RainDrop* drop = drops + index;
        if (drop->active == 0) continue;
        drop->position = drop->position - gravity * gravity_scale;
        drop->previous_frame = drop->frame;
        float control = *drop->control;
        if (control <= span_low || span_high <= control) {
            drop->timer = drop->timer + control;
            drop->frame = (float)float_to_long(drop->timer);
        } else {
            drop->frame = (float)((int)drop->frame + 1);
            drop->timer = drop->timer + frame_step;
        }
        if (0x3C < (int)drop->frame) drop->active = 0;
    }
    return 1;
}
#endif
