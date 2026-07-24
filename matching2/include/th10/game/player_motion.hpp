#pragma once

// Player axis wrap helpers, death shrink, and animation frame timer (retail 0x0040678E, 0x00407DA0, 0x00407E40, 0x004074B0, 0x004076A0).
#include "th10/util/scalars.hpp"

void Player_ForwardAxisWrap(float* axis, float delta,
                            void (*wrap)(float* axis, float delta));

int Player_WrapAxisCore(float* axis, float field_extent, float low_bound,
                        float high_bound, float margin, int (*probe)(void),
                        void (*play_wrap_sound)(float pan), int effect_slot,
                        void (*spawn_wrap_effect)(void));

void Player_WrapHorizontal(float* axis, float field_extent, float low_bound,
                           float high_bound, float margin, int (*probe)(void),
                           void (*play_wrap_sound)(float pan), int effect_slot,
                           void (*spawn_wrap_effect)(void), int focus_count,
                           unsigned int* pose_flags);

void Player_WrapVertical(float* axis, float field_extent, float low_bound,
                         float high_bound, float margin, int (*probe)(void),
                         void (*play_wrap_sound)(float pan), int effect_slot,
                         void (*spawn_wrap_effect)(void), int focus_count,
                         unsigned int* pose_flags);

// Player animation frame block (retail player +0x614..+0x620).
struct PlayerFrameTimer {
    int previous;             // retail +0x614
    int frame;                // retail +0x618
    float timer;              // retail +0x61C
    const float* control;     // retail +0x620
};

void PlayerAnimation_AdvanceFrame(PlayerFrameTimer* timer,
                                  unsigned int* pose_flags, float span_low,
                                  float span_high, float frame_step,
                                  int trail_frame_limit,
                                  void (*emit_trail)(void),
                                  long long (*float_to_long)(float value));

// Shared frame clock used by the per-frame update callbacks (retail keeps
// {previous, frame, timer, control} together; control points at the global
// frame-scale value).
struct PlayerDeathClock {
	int previous;
	int frame;
	float timer;
	float* control;
};

// --- 0x004076A0 --------------------------------------------------------------
void Player_DeathShrink(PlayerDeathClock* clock, int deadline_frame,
                        float* radius, float* fall_y, float shrink_rate,
                        float fall_rate, float delta,
                        Word* status_flags, void* hitbox,
                        float (*approach)(float value, float step),
                        void (*move_hitbox)(void* hitbox, float radius,
                                            float y),
                        float span_low, float span_high, float frame_step,
                        long long (*float_to_long)(float value));
