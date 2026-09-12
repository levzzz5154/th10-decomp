#pragma once

// Replay stage entry load and replay timer end clamp (retail 0x00415DB0, 0x00412FF0).
#include "th10/game/registered_clock.hpp"

// --- 0x00415DB0 --------------------------------------------------------------
void* ReplayStage_LoadEntry(char* archive, int index, void** current_slot,
                            void* (*allocate)(unsigned int size),
                            void* (*construct)(void* memory, void* payload),
                            int* stage_slot, int* frame_slot);

void ReplayTimer_ClampToEnd(RegisteredClock* clock, float amount,
                            void (*advance)(float amount),
                            float* frame_scale);
