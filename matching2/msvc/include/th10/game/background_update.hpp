#pragma once
#include <stddef.h>
#include <string.h>
#include "th10/render/anm_script_table_sweep.hpp"
#include "th10/render/camera_batch.hpp"

// The camera block a stage owns; the live copy at 0x00491D7C has this extent.
struct BackGroundCamera {
    RenderCamera camera;
    CameraVector shake_offset;
    char reserved_0fc[0x118 - 0xFC];
};

// The stage object starts with its script table, whose sweep keeps the
// receiver in EBX.
struct BackGround : ScriptTableSweep {
    SweepAnimation layers[8];
    char reserved_1ee0[8];
    int clear_color;
    int overlay_active;
    char reserved_1ef0[0x1F08 - 0x1EF0];
    SweepAnimation overlays[3];
    char reserved_2a0c[0x2A18 - 0x2A0C];
    unsigned int state_flags;
    int reserved_2a1c;
    int fade_frames;
    char reserved_2a24[0x2A34 - 0x2A24];
    int frame;
    char reserved_2a38[0x2A4C - 0x2A38];
    BackGroundCamera camera;
    __declspec(noinline) int Update();
};
typedef char BackGroundLayersOffset[offsetof(BackGround, layers) == 0x180 ? 1 : -1];
typedef char BackGroundClearColorOffset[offsetof(BackGround, clear_color) == 0x1EE8 ? 1 : -1];
typedef char BackGroundOverlaysOffset[offsetof(BackGround, overlays) == 0x1F08 ? 1 : -1];
typedef char BackGroundFlagsOffset[offsetof(BackGround, state_flags) == 0x2A18 ? 1 : -1];
typedef char BackGroundCameraOffset[offsetof(BackGround, camera) == 0x2A4C ? 1 : -1];
typedef char StageCameraSize[sizeof(BackGroundCamera) == 0x118 ? 1 : -1];

extern "C" {
// 0x00403C80: the stage script interpreter, one stack argument.
void __stdcall BackGround_RunScript(BackGround* stage);
extern float data_00476f78;
extern BackGroundCamera data_00491d7c;
}
