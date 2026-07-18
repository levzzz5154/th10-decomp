#include "th10/render/game_render_targets.hpp"

// 0x00443F80 - Prepare projected render state before invoking the normal draw
// path. Preparation failures use the retail -1 result.
int Render_PrepareAndDraw(void* object, int (*prepare)(),
                          int (*draw)(void*, int)) {
    if (prepare == 0 || prepare() != 0)
        return -1;
    return draw != 0 ? draw(object, 0) : -1;
}

// 0x00444580 - Restore the four render scale factors to identity.
void Render_ResetScaleFactors(float factors[4]) {
    factors[0] = 1.0f;
    factors[1] = 1.0f;
    factors[2] = 1.0f;
    factors[3] = 1.0f;
}

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
