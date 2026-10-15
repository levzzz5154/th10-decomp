// 0x00402720: per-frame stage update. Runs the stage script and its layer
// animations, ticks the overlay animations at unscaled game speed, then
// publishes the stage camera. Native LTCG passes the stage in EAX.
// 0x00403050: the scheduler callback, which forwards its ECX context.
#include "th10/game/background_update.hpp"

#pragma code_seg(".text$00stage_update")
int BackGround::Update() {
    if (state_flags & 8)
        return 1;
    if ((state_flags & 4) && fade_frames >= 60)
        return 1;
    camera.shake_offset = CameraVector(0.0f, 0.0f, 0.0f);
    camera.camera.clip_x = 0;
    camera.camera.clip_y = 0;
    CameraNormalize(&camera.camera.unknown_024, &camera.camera.direction);
    clear_color = 0x808080;
    Sweep();
    BackGround_RunScript(this);
    for (int i = 0; i < 8; ++i)
        RunAnimationVm(&layers[i]);
    if (overlay_active) {
        float game_speed = g_game_speed;
        g_game_speed = 1.0f;
        RunAnimationVm(&overlays[0]);
        RunAnimationVm(&overlays[1]);
        RunAnimationVm(&overlays[2]);
        g_game_speed = game_speed;
    }
    overlay_active = 0;
    memcpy(&data_00491d7c, &camera, sizeof(BackGroundCamera));
    ++frame;
    return 1;
}
#pragma code_seg()

#pragma code_seg(".text$00task_callback")
int __fastcall BackGround_OnUpdate(BackGround* stage) {
    return stage->Update();
}
#pragma code_seg()
