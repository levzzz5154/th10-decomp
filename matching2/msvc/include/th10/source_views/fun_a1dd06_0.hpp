#pragma once
// 0x00439390..0x00439539 (425 bytes): advance the game by one frame.
//
// The frame limiter and the frame's render: it reads the performance timer
// 0x00439540, tracks the frame's start time (0x004924F0+0x38) and the previous
// frame's (+0x40), and gates the body on the fixed-timestep target (+0x48).
// While the target is still ahead of the clock the frame is not due: the
// routine yields through the Sleep thunk 0x004660AC with 0 and returns 0
// without rendering.  Otherwise it catches the target up in 1/60 s steps,
// flushes the quad batch, republishes the *second* stage camera through the
// recovered 0x00421480, hands the camera's viewport block to the device, runs
// the task decoder 0x00449C00 and the dispatcher 0x0043DDF0 over the frame
// parameters, and either reports the decoder's "stop" codes (1 and 2, each
// preceded by the worker-thread stop 0x0044C150) or renders: D3D BeginScene,
// the quad buffer reset, the fog-state restore 0x00420CD0, EndScene, and every
// (hint+1)-th frame the buffer/fog reset block.  Finally it publishes the
// elapsed frame time (0x004923A0) and returns 0.
//
// Retail reaches the body with the frame state as the *only* stack argument
// (read into EBP and never popped, hence RET 4) and saves ESI and EDI only:
// EBX is never touched by the body at all.  The stack argument is the whole
// story of this model - the whole-program pass loads it into EBP *in the
// prologue* (`push ebp; mov ebp,[esp+8]; push esi; push edi; call`) only when
// the function is reached from a real call site; pinned as a `/INCLUDE:` root
// the pass instead keeps it in its stack home and emits the load after the
// timer call, which costs the 11 prologue bytes.  This body is therefore kept
// alive by the cluster driver's synthetic call, exactly as 0x00408580's
// asset loader is.
#include "th10/render/camera_batch.hpp"

// The frame state at 0x004924F0 the message loop hands in: the frame's start
// time, the previous frame's and the fixed-timestep target, plus the tick
// counter the buffer/fog reset block uses.  The first 0x14 bytes are the
// window/device fields this routine never touches.
struct GameFrame_00439390 {
    unsigned char reserved_000[0x14];
    signed char tick;                            // +0x14
    unsigned char reserved_015[0x38 - 0x15];
    double frame_time;                           // +0x38, this frame's start
    double previous_time;                        // +0x40, the previous frame's
    double next_tick_time;                       // +0x48, the next 60 Hz tick
};

// The game-wide render state at 0x00491C28: the device at +0x08, the
// 0x118-byte stage records at +0x154, the active stage at +0x384, the stage
// index at +0x388, and at +0x750/+0x754 whether fog and depth writes are on.
struct RenderStage_00439390 {
    RenderCamera camera;
    unsigned char reserved_0F0[0x118 - sizeof(RenderCamera)];
};
struct RenderStageState_00439390 {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                        // +0x08
    unsigned char reserved_00C[0x154 - 0x0C];
    RenderStage_00439390 stages[2];              // +0x154, stride 0x118
    RenderStage_00439390* active_stage;          // +0x384
    int stage_index;                             // +0x388
    unsigned char reserved_38C[0x750 - 0x38C];
    int fog_enabled;                             // +0x750
    int depth_write_enabled;                     // +0x754

    // 0x00420C90..0x00420D50: flush the pending animation batch, then switch
    // D3DRS_FOGENABLE (28) or D3DRS_ZWRITEENABLE (14) when it changes.
    __declspec(noinline) int EnableFog();
    __declspec(noinline) int DisableFog();
    __declspec(noinline) int EnableDepthWrite();
    __declspec(noinline) int DisableDepthWrite();
};

// The worker thread object at 0x00492254: the Win32 handle at +0x04 plus the
// stop/join flags 0x0044C150 writes.
struct WorkerThread_00439390 {
    unsigned char reserved_000[0x04];
    void* handle;                                // +0x04
    unsigned char reserved_008[0x0C - 0x08];
    int stopping;                                // +0x0C
    int stop_reason;                             // +0x10
    unsigned char reserved_014[0x18 - 0x14];
    int joinable;                                // +0x18

    __declspec(noinline) void* Stop();
};

extern "C" GameFrame_00439390 data_004924f0;
extern "C" RenderStageState_00439390 g_application;
extern "C" WorkerThread_00439390 data_00492254;
// The task manager 0x00449C00/0x00449D40 decode for.
extern "C" int g_func_ctrl;
// The frame parameters 0x0043DDF0 walks.
extern "C" char g_sound_manager[];
// The frame time the renderer publishes.
extern "C" double data_004923a0;
// How many frames one tick covers, read as the reset block's threshold.  Read
// through a reference local: through the bare global the pass hoists the load
// above the tick store.
extern "C" unsigned char data_00491d66;
// The Sleep thunk the "frame not due" path calls with 0 (it cleans the
// argument itself, so retail has no `add esp,4` after the call).
extern "C" void (__stdcall* imp_Sleep)(int);

// 0x00439540 (its own maintained region): the performance timer, result in st(0).
extern "C" double __cdecl FrameTimer_GetDelta(void);
// 0x00449C00 / 0x00449D40: decode the frame's tasks out of the manager.
extern "C" int __stdcall asm_FUN_00449c00_00449c00(int manager);
extern "C" int __stdcall asm_FUN_00449d40_00449d40(int manager);
// 0x004391F0: the per-tick input/state update this routine drives.
extern "C" void __cdecl asm_FUN_004391f0_004391f0(void);
// 0x0043DDF0: the task dispatcher, parameters pointer on the stack, RET 4.
extern "C" void __stdcall asm_FUN_0043ddf0_0043ddf0(void* parameters);

#pragma code_seg(".text$00clayoutfa")
