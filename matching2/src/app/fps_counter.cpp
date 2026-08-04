#include "th10/app/fps_counter.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

#ifdef _MSC_VER
extern "C" double sub_439540(void);
extern "C" double dbl_470BC0;
extern "C" double dbl_470B30;
extern "C" float flt_470BB8;
extern "C" double dbl_492540;
extern "C" double dbl_492538;
extern "C" double dbl_492528;
extern "C" double dbl_492530;
extern "C" double dbl_492508;
extern "C" double dbl_49250C;
extern "C" double dbl_470BB0;
extern "C" float flt_470BA8;
extern "C" void* dword_477810;
#endif

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


#include <cmath>
#include <cstring>

namespace {



} // namespace

// 0x004135D0 - FPS counter draw callback: refresh the rolling average, and
// unless the game is in state 0xE (shutdown) or the game thread is gone,
// print "%2.1ffps" tinted by the frame rate (red below the low threshold,
// pink below the mid threshold, white otherwise), restoring white after.
// The frame accumulator then absorbs the skipped-frame count plus one.
int FpsCounter_Render(void (*update_average)(void), int game_state,
                      void* game_thread, float fps, float low_threshold,
                      float mid_threshold, Word* overlay_color,
                      void (*print_overlay)(const char* format),
                      int* accumulator, int skipped_frames) {
	update_average();
	if (game_state != 0xE && game_thread != 0) {
		Word color;
		if (fps < low_threshold) {
			color = 0xFF5050FF;
		} else if (fps < mid_threshold) {
			color = 0xFFA0A0FF;
		} else {
			color = 0xFFFFFFFF;
		}
		*overlay_color = color;
		print_overlay("%2.1ffps");
		*overlay_color = 0xFFFFFFFF;
	}
	*accumulator += skipped_frames + 1;
	return 1;
}

// 0x004134B0 - frame-rate counter update: measures fps over the elapsed
// window, resynchronizes the global frame stamps after repeated timer
// stalls, and accumulates played time while the game is not paused/skipping.
#ifdef _MSC_VER
__declspec(naked) int FrameRateCounter_UpdateRetail() {
    __asm {
        push ebp
        mov ebp, esp
        and esp, 0FFFFFFF8h
        push ecx
        push edi
        call sub_439540
        fcom qword ptr [esi+14h]
        fnstsw ax
        test ah, 5
        jp loc_4134CA
        fst qword ptr [esi+14h]
loc_4134CA:
        fsub qword ptr [esi+14h]
        fcom qword ptr [dbl_470BC0]
        fnstsw ax
        test ah, 1
        jnz loc_4135BC
        mov eax, [esi+20h]
        fld st(0)
        test eax, eax
        fadd qword ptr [esi+14h]
        fstp qword ptr [esi+14h]
        fild dword ptr [esi+20h]
        jge loc_4134F6
        fadd qword ptr [dbl_470B30]
loc_4134F6:
        fdivrp st(1), st
        xor edi, edi
        fst dword ptr [esi+34h]
        fcomp dword ptr [flt_470BB8]
        fnstsw ax
        test ah, 41h
        jnz loc_413565
        mov edx, [esi+1Ch]
        inc edx
        mov eax, edx
        cmp eax, 2
        mov [esi+1Ch], edx
        jnz loc_413537
        call sub_439540
        fst qword ptr [dbl_492540]
        fst qword ptr [dbl_492538]
        fst qword ptr [dbl_492528]
        fstp qword ptr [dbl_492530]
        jmp loc_413568
loc_413537:
        cmp eax, 4
        jnz loc_413568
        mov dword ptr [dbl_492508], edi
        mov dword ptr [dbl_49250C], edi
        call sub_439540
        fst qword ptr [dbl_492540]
        fst qword ptr [dbl_492538]
        fst qword ptr [dbl_492528]
        fstp qword ptr [dbl_492530]
loc_413565:
        mov [esi+1Ch], edi
loc_413568:
        mov ecx, dword ptr [dword_477810]
        cmp ecx, edi
        jz loc_4135AF
        test byte ptr [ecx+58h], 14h
        jnz loc_4135A8
        fld qword ptr [esi+2Ch]
        fadd qword ptr [dbl_470BB0]
        fstp qword ptr [esi+2Ch]
        fld dword ptr [esi+34h]
        fcomp dword ptr [flt_470BA8]
        fnstsw ax
        test ah, 41h
        jnz loc_41359F
        fld qword ptr [esi+24h]
        fadd qword ptr [dbl_470BB0]
        jmp loc_4135A5
loc_41359F:
        fld dword ptr [esi+34h]
        fadd qword ptr [esi+24h]
loc_4135A5:
        fstp qword ptr [esi+24h]
loc_4135A8:
        and dword ptr [ecx+58h], 0FFFFFF7Fh
loc_4135AF:
        mov [esi+20h], edi
        mov eax, 1
        pop edi
        mov esp, ebp
        pop ebp
        ret
loc_4135BC:
        fstp st(0)
        mov eax, 1
        pop edi
        mov esp, ebp
        pop ebp
        ret
    }
}
#endif

int FrameRateCounter_Update(FrameRateCounter* counter,
                            FrameRateEnv* env) {
	double now = env->read_seconds();
	if (now < counter->last_stamp) counter->last_stamp = now;
	double delta = now - counter->last_stamp;
	if (delta < env->min_interval) return 1;
	counter->last_stamp += delta;

	double frames = (double)counter->frame_count;
	if (counter->frame_count < 0) frames += env->negative_wrap;
	counter->fps = (float)(frames / delta);

	if (env->stall_threshold < frames / delta) {
		counter->stall_count += 1;
		if (counter->stall_count == 2) {
			double stamp = env->read_seconds();
			for (int i = 0; i < 4; ++i) *env->sync_stamps[i] = stamp;
		} else if (counter->stall_count == 4) {
			*env->skip_accumulator = 0.0;
			double stamp = env->read_seconds();
			for (int i = 0; i < 4; ++i) *env->sync_stamps[i] = stamp;
			counter->stall_count = 0;
		}
	} else {
		counter->stall_count = 0;
	}

	if (env->input_flags != 0) {
		if ((*env->input_flags & 0x14) == 0) {
			counter->total_seconds += env->second_unit;
			if ((double)counter->fps <= env->fps_cap) {
				counter->active_seconds += (double)counter->fps;
			} else {
				counter->active_seconds += env->second_unit;
			}
		}
		*env->input_flags &= ~0x80u;
	}
	counter->frame_count = 0;
	return 1;
}
