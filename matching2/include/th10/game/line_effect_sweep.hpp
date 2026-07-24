#pragma once

// Line sweep spawning sparkles and optional cancellation items (retail 0x0041E260).
// Retail function 0x0041E260.
struct LineEffect{int finished;float origin[3],angle,length;short animation_variant;};struct LineEffectSweepEnv{void(*spawn_spark)(const float[3],int);void(*spawn_item)(const float[3],int,int,float,float);};int LineEffect_SweepIntoItems(LineEffect*,int,const LineEffectSweepEnv*);
