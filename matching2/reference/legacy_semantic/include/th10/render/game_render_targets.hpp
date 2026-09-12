#pragma once

#include "th10/game/entity.hpp"

// Render-target descriptors stored at the front of GameStateManager. The two
// signed handles are valid when non-negative; each creation path preserves its
// parameters so the target can be released/recreated during a device reset.
struct GameRenderTargets {
    int32_t primary_handle;       // +0x00
    int32_t capture_handle;       // +0x04
    uint32_t capture_args[9];     // +0x08 .. +0x28
    uint32_t primary_args[8];     // +0x2C .. +0x48
};
// sizeof(GameRenderTargets) == 0x4C

void GameRenderTargets_Initialize(GameRenderTargets* targets);
void GameRenderTargets_Release(GameRenderTargets* targets);
int Render_PrepareAndDraw(void* object, int (*prepare)(),
                          int (*draw)(void*, int));
void Render_ResetScaleFactors(float factors[4]);
