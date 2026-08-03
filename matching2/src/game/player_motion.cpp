#include "th10/game/player_motion.hpp"

#ifdef _MSC_VER
extern "C" void sub_4065C0(void*);
extern "C" void sub_4061D0(void*, void*);
extern "C" void sub_44BF40(float);
extern "C" void sub_43DC90(void*, int, void*);
extern "C" float flt_470B40;
extern "C" float flt_470B3C;
extern "C" float flt_470B38;
extern "C" float flt_470B54;
extern "C" double dbl_470B70;
extern "C" float flt_470C6C;
extern "C" float flt_470C68;
extern "C" float flt_470B68;
extern "C" float flt_470B64;
extern "C" float flt_470AFC;
extern "C" void sub_408750(void*, float, float);
extern "C" void sub_463B2C(void);
#endif
#include "th10/util/scalars.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.

// Shared per-frame clock advance used by the update callbacks below. When
// the global frame-scale control sits inside the normal span the frame
// counter simply increments; otherwise the scaled control value is
// accumulated and the frame is re-derived by truncation.
static void AdvanceFrameClock(PlayerDeathClock* clock, float span_low,
                              float span_high, float frame_step,
                              long long (*float_to_long)(float value)) {
	float control = *clock->control;
	clock->previous = clock->frame;
	if (span_low < control && control < span_high) {
		clock->timer += frame_step;
		clock->frame += 1;
	} else {
		clock->timer += control;
		clock->frame = (int)float_to_long(clock->timer);
	}
}

// 0x0040678E - Register-thunk onto the player axis wrap helper. Retail only
// moves the fastcall registers into the callee frame and jumps to 0x004065C0.
#ifdef _MSC_VER
__declspec(naked) void Player_ForwardAxisWrap(
        float* axis, float delta, void (*wrap)(float* axis, float delta)) {
    __asm {
        push esi
        mov esi, ecx
        call sub_4065C0
        pop esi
        ret
    }
}
#else
void Player_ForwardAxisWrap(float* axis, float delta,
                            void (*wrap)(float* axis, float delta)) {
    if (wrap != 0) wrap(axis, delta);
}
#endif

// --- Player field-wrap leaves ------------------------------------------------

// Shared body of the horizontal/vertical player wrap leaves: when the probe
// admits a wrap check and the coordinate leaves [low_bound, high_bound], the
// coordinate is folded back across the field extent plus margin, the wrap
// sound plays with a hard -1.0 pan, and the wrap effect spawns when the
// effect slot is armed. Returns nonzero when the coordinate wrapped.
int Player_WrapAxisCore(float* axis, float field_extent, float low_bound,
                        float high_bound, float margin, int (*probe)(void),
                        void (*play_wrap_sound)(float pan), int effect_slot,
                        void (*spawn_wrap_effect)(void)) {
    if (probe != 0 && probe() == 0) return 0;
    float value = *axis;
    if (low_bound <= value) {
        if (value <= high_bound) return 0;
        value = value - (field_extent + margin);
    } else {
        value = field_extent + value + margin;
    }
    *axis = value;
    if (play_wrap_sound != 0) play_wrap_sound(-1.0f);
    if (-1 < effect_slot && spawn_wrap_effect != 0) spawn_wrap_effect();
    return 1;
}

// 0x00407DA0 - Wrap the player's horizontal coordinate across the playfield.
// After the wrap check, retail toggles pose-flag bit 0x100000 whenever the
// focus counter (+0x750) is not positive.
#ifdef _MSC_VER
__declspec(naked) void Player_WrapHorizontal(
        float* axis, float field_extent, float low_bound,
        float high_bound, float margin, int (*probe)(void),
        void (*play_wrap_sound)(float pan), int effect_slot,
        void (*spawn_wrap_effect)(void), int focus_count,
        unsigned int* pose_flags) {
    __asm {
        mov edx, [ebx+39Ch]
        mov eax, [edx+30h]
        push eax
        mov eax, [edx+34h]
        lea ecx, [ebx+3B4h]
        push eax
        call sub_4061D0
        test eax, eax
        je done
        fld dword ptr [ecx]
        push esi
        fcomp dword ptr [flt_470B40]
        push edi
        fnstsw ax
        test ah, 5
        jp wrap_low
        fld dword ptr [edx+34h]
        fadd dword ptr [ecx]
        fadd dword ptr [flt_470B54]
        jmp store_wrap
wrap_low:
        fld dword ptr [ecx]
        fcomp dword ptr [flt_470B3C]
        fnstsw ax
        test ah, 41h
        jne after_effect
        fld dword ptr [edx+34h]
        fadd dword ptr [flt_470B54]
        fsubr dword ptr [ecx]
store_wrap:
        lea esi, [ebx+74Ch]
        fstp dword ptr [ecx]
        push 0BF800000h
        call sub_44BF40
        mov edi, [ebx+458h]
        test edi, edi
        jl after_effect
        mov ecx, 492590h
        push 0
        call sub_43DC90
after_effect:
        mov eax, [ebx+750h]
        test eax, eax
        pop edi
        pop esi
        jg done
        xor dword ptr [ebx+43Ch], 100000h
done:
        ret
    }
}
#else
void Player_WrapHorizontal(float* axis, float field_extent, float low_bound,
                           float high_bound, float margin, int (*probe)(void),
                           void (*play_wrap_sound)(float pan), int effect_slot,
                           void (*spawn_wrap_effect)(void), int focus_count,
                           unsigned int* pose_flags) {
    Player_WrapAxisCore(axis, field_extent, low_bound, high_bound, margin,
                        probe, play_wrap_sound, effect_slot,
                        spawn_wrap_effect);
    if (focus_count < 1) *pose_flags = *pose_flags ^ 0x100000u;
}
#endif

// 0x00407E40 - Wrap the player's vertical coordinate across the playfield.
// Identical frame to the horizontal leaf, but the focus counter lives at
// +0x784 and the toggled pose-flag bit is 0x200000.
#ifdef _MSC_VER
__declspec(naked) void Player_WrapVertical(
        float* axis, float field_extent, float low_bound,
        float high_bound, float margin, int (*probe)(void),
        void (*play_wrap_sound)(float pan), int effect_slot,
        void (*spawn_wrap_effect)(void), int focus_count,
        unsigned int* pose_flags) {
    __asm {
        mov edx, [ebx+39Ch]
        mov eax, [edx+30h]
        mov ecx, [edx+34h]
        push eax
        push ecx
        lea ecx, [ebx+3B4h]
        call sub_4061D0
        test eax, eax
        je done
        fld dword ptr [ebx+3B8h]
        push esi
        fcomp qword ptr [dbl_470B70]
        push edi
        fnstsw ax
        test ah, 5
        jp wrap_low
        fld dword ptr [edx+30h]
        fadd dword ptr [ebx+3B8h]
        fadd dword ptr [flt_470B38]
        jmp store_wrap
wrap_low:
        fld dword ptr [ebx+3B8h]
        fcomp dword ptr [flt_470B38]
        fnstsw ax
        test ah, 41h
        jne after_effect
        fld dword ptr [edx+30h]
        fadd dword ptr [flt_470B38]
        fsubr dword ptr [ebx+3B8h]
store_wrap:
        lea esi, [ebx+780h]
        fstp dword ptr [ebx+3B8h]
        push 0BF800000h
        call sub_44BF40
        mov edi, [ebx+458h]
        test edi, edi
        jl after_effect
        mov ecx, 492590h
        push 0
        call sub_43DC90
after_effect:
        mov eax, [ebx+784h]
        test eax, eax
        pop edi
        pop esi
        jg done
        xor dword ptr [ebx+43Ch], 200000h
done:
        ret
    }
}
#else
void Player_WrapVertical(float* axis, float field_extent, float low_bound,
                         float high_bound, float margin, int (*probe)(void),
                         void (*play_wrap_sound)(float pan), int effect_slot,
                         void (*spawn_wrap_effect)(void), int focus_count,
                         unsigned int* pose_flags) {
    Player_WrapAxisCore(axis, field_extent, low_bound, high_bound, margin,
                        probe, play_wrap_sound, effect_slot,
                        spawn_wrap_effect);
    if (focus_count < 1) *pose_flags = *pose_flags ^ 0x200000u;
}
#endif

// --- Frame-timer leaves -------------------------------------------------------

// 0x004074B0 - Advance the player animation frame timer. While the frame
// counter stays below the trail limit (retail 0x11) the motion-trail sprite
// is emitted; afterwards pose-flag bit 0 toggles each tick instead. The
// counter then advances exactly like the droplet timers: inside the control
// span it increments by one and the timer gains one frame step; outside, the
// timer absorbs the control value and the counter is retruncated from it.
#ifdef _MSC_VER
__declspec(naked) void PlayerAnimation_AdvanceFrame(
        PlayerFrameTimer* timer,
        unsigned int* pose_flags, float span_low,
        float span_high, float frame_step,
        int trail_frame_limit,
        void (*emit_trail)(void),
        long long (*float_to_long)(float value)) {
    __asm {
        cmp dword ptr [esi+618h], 10h
        jg no_trail
        fld dword ptr [esi+61Ch]
        mov eax, [esi+3E4h]
        fmul dword ptr [flt_470C6C]
        push ecx
        lea ecx, [esi+3C0h]
        fsubr dword ptr [flt_470C68]
        fadd dword ptr [esi+3D8h]
        fstp dword ptr [esp]
        push eax
        call sub_408750
        jmp after_trail
no_trail:
        xor dword ptr [esi+43Ch], 1
after_trail:
        mov edx, [esi+618h]
        mov ecx, [esi+620h]
        mov [esi+614h], edx
        fld dword ptr [ecx]
        fcomp dword ptr [flt_470B68]
        fnstsw ax
        test ah, 41h
        jne outside
        fld dword ptr [ecx]
        fcomp dword ptr [flt_470B64]
        fnstsw ax
        test ah, 5
        jp outside
        fld dword ptr [esi+61Ch]
        inc edx
        fadd dword ptr [flt_470AFC]
        mov [esi+618h], edx
        fstp dword ptr [esi+61Ch]
        ret
outside:
        fld dword ptr [ecx]
        fadd dword ptr [esi+61Ch]
        fst dword ptr [esi+61Ch]
        call sub_463B2C
        mov [esi+618h], eax
        ret
    }
}
#else
void PlayerAnimation_AdvanceFrame(PlayerFrameTimer* timer,
                                  unsigned int* pose_flags, float span_low,
                                  float span_high, float frame_step,
                                  int trail_frame_limit,
                                  void (*emit_trail)(void),
                                  long long (*float_to_long)(float value)) {
    if (timer->frame < trail_frame_limit) {
        if (emit_trail != 0) emit_trail();
    } else {
        *pose_flags = *pose_flags ^ 1u;
    }
    timer->previous = timer->frame;
    float control = *timer->control;
    if (span_low < control && control < span_high) {
        timer->timer = timer->timer + frame_step;
        timer->frame = timer->frame + 1;
        return;
    }
    timer->timer = control + timer->timer;
    timer->frame = (int)float_to_long(timer->timer);
}
#endif

// --- ECL child-VM list leaves -------------------------------------------------

// 0x004076A0 - Player death shrink: until the deadline frame the collision
// radius eases toward zero and the sprite falls, after which the shrink
// status bit (0x20) clears. The player's frame clock always advances.
void Player_DeathShrink(PlayerDeathClock* clock, int deadline_frame,
                        float* radius, float* fall_y, float shrink_rate,
                        float fall_rate, float delta,
                        Word* status_flags, void* hitbox,
                        float (*approach)(float value, float step),
                        void (*move_hitbox)(void* hitbox, float radius,
                                            float y),
                        float span_low, float span_high, float frame_step,
                        long long (*float_to_long)(float value)) {
	if (clock->frame < deadline_frame) {
		*radius = approach(*radius, delta * shrink_rate);
		*fall_y += delta * fall_rate;
		move_hitbox(hitbox, *radius, *fall_y);
	} else {
		*status_flags &= ~0x20u;
	}
	AdvanceFrameClock(clock, span_low, span_high, frame_step, float_to_long);
}
