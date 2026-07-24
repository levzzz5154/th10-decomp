#pragma once

// Game-thread render stage selection (retail 0x00401D20).
#include "th10/util/scalars.hpp"

// One render stage record (0x118 retail bytes; viewport block at +0xCC).
struct RenderStage {
    Byte state[0xCC];
    Byte viewport[0x4C];
};

void GameThread_SelectRenderStage(RenderStage* stages, int stage_index,
                                  RenderStage** active_stage_out,
                                  int* active_index_out,
                                  void (*apply_camera)(void),
                                  void (*set_viewport)(const void* viewport));
