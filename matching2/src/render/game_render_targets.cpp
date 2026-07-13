#include "th10/render/game_render_targets.hpp"

void GameRender_ReleaseCaptureTarget(
    GameRenderTargets* targets, int32_t handle, const uint32_t* arguments);
void GameRender_ReleasePrimaryTarget(
    GameRenderTargets* targets, int32_t handle, const uint32_t* arguments);

// Initialization is inlined into GameStateInit at 0x00445900.
void GameRenderTargets_Initialize(GameRenderTargets* targets) {
    targets->primary_handle = -1;
    targets->capture_handle = -1;
    for (uint32_t index = 0; index < 9; ++index) {
        targets->capture_args[index] = 0;
    }
    for (uint32_t index = 0; index < 8; ++index) {
        targets->primary_args[index] = 0;
    }
}

// 0x00438A60 - Release reset-sensitive capture and primary render targets.
void GameRenderTargets_Release(GameRenderTargets* targets) {
    if (targets->capture_handle >= 0) {
        GameRender_ReleaseCaptureTarget(
            targets, targets->capture_handle, targets->capture_args);
        targets->capture_handle = -1;
    }
    if (targets->primary_handle >= 0) {
        GameRender_ReleasePrimaryTarget(
            targets, targets->primary_handle, targets->primary_args);
        targets->primary_handle = -1;
    }
}
