#pragma once

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#else
#include <cstdint>
#endif

#include "th10/game/scheduler.hpp"
#include "th10/game/score_queue.hpp"
#include "th10/math/timer.hpp"

// Shared edges for the retail scheduler-pair registration skeleton:
// FUN_00449ED0 creates a callback, FUN_00449AE0 / FUN_00449B70 register
// it on the primary / secondary list with the device token from the
// retail global 0x00491BE4 (the retail priority argument travels in a
// register and stays behind the injected edge).
typedef SchedulerCallback* (*SchedulerCreateFn)(SchedulerFunction function);
typedef void (*SchedulerRegisterFn)(SchedulerCallback* callback,
                                    uint32_t token);

// Update/render callback slots shared by several managers (retail
// offsets +0x08 / +0x0C).
struct TaskPairSlots {
    SchedulerCallback* update_task;  // +0x08
    SchedulerCallback* render_task;  // +0x0C
};

// 0x00418E30 - Register the stage-tip manager's update/render callbacks
// (both created with cleared flag bit 1 and the manager as owner), zero
// the counter at +0x10, and, when the retail tips flag at 0x00491D6A is
// set, spawn the two demo tips (retail 0x00419960) with the retail text
// records at 0x0046D6D8 (slot 0) and 0x0046D6C4 (slot 1). Returns 0.
uint32_t StageTip_RegisterTasks(
    void* owner, TaskPairSlots* slots, uint32_t* counter,
    SchedulerCreateFn create, SchedulerRegisterFn register_primary,
    SchedulerRegisterFn register_secondary, SchedulerFunction update_proc,
    SchedulerFunction render_proc,
    void (*spawn_tip)(void* owner, uint32_t text_address, int32_t slot));

// State fragment for 0x00422150: the callback pair plus an embedded
// countdown timer at +0x10.
struct TimedTaskState {
    SchedulerCallback* update_task;  // +0x08
    SchedulerCallback* render_task;  // +0x0C
    EmbeddedTimerState timer;        // +0x10..+0x20
};

// 0x00422150 - Register an update/render callback pair and reset the
// embedded timer: first the sentinel initialization (flag bit 0 guards
// target 0xFFF0BDC1 and the unit speed at retail 0x00476F78), then
// current/previous clear to 0 and the target becomes -1. Returns 0.
uint32_t TimedTask_RegisterPair(void* owner, TimedTaskState* state,
                                SchedulerCreateFn create,
                                SchedulerRegisterFn register_primary,
                                SchedulerRegisterFn register_secondary,
                                SchedulerFunction update_proc,
                                SchedulerFunction render_proc);

// 0x0041C120 - Initialize the score display: look up the "bullet.anm"
// resource in slot 7 (retail 0x00447280 against the global game state
// manager), storing it at +0x458; a missing resource reports the retail
// error record (0x0044B810 with 0x00474F70 / 0x0046CD54) and returns
// -1. Otherwise the callback pair registers and the popup-queue tail at
// +0x434 points at the sentinel node at owner+0x10. Returns 0.
int32_t ScoreDisplay_RegisterTasks(
    void* owner, TaskPairSlots* slots, int32_t** resource_slot,
    ScorePopupNode** queue_tail, ScorePopupNode* queue_head,
    int32_t* (*find_resource)(int32_t slot, const char* name),
    void (*report_error)(), SchedulerCreateFn create,
    SchedulerRegisterFn register_primary,
    SchedulerRegisterFn register_secondary, SchedulerFunction update_proc,
    SchedulerFunction render_proc);

// 0x00413980 - Initialize the front UI: look up "front.anm" in slot 6,
// storing it at +0x9EC8 (even when null); a missing resource reports
// the retail error record (0x0046CB68) and returns -1. The sprite setup
// step (retail 0x00413A20) must return 0 or the call fails with -1;
// afterwards the callback pair registers. Returns 0 on success.
int32_t FrontAnm_RegisterTasks(
    void* owner, TaskPairSlots* slots, int32_t** resource_slot,
    int32_t* (*find_resource)(int32_t slot, const char* name),
    void (*report_error)(), int32_t (*initialize)(void* owner),
    SchedulerCreateFn create, SchedulerRegisterFn register_primary,
    SchedulerRegisterFn register_secondary, SchedulerFunction update_proc,
    SchedulerFunction render_proc);

struct ItemFrontRuntimeBindings {
    int (*initialize_score_task)(void* owner);
};

void ItemFrontRuntime_SetBindings(
    const ItemFrontRuntimeBindings* bindings);
int ItemFrontRuntime_Initialize(void* owner);

// State fragment for 0x0042CAA0 (retail offsets in comments; the title
// screen keeps its callbacks one word later than the other managers).
struct TitleInitState {
    SchedulerCallback* update_task;  // +0x0C
    SchedulerCallback* render_task;  // +0x10
    int32_t* title_resource;         // +0x14, "title.anm" slot 0x19
    int32_t* title_v_resource;       // +0x18, "title_v.anm" slot 0x1A
    uint32_t ready_flag;             // +0xF4, set to 1 on success
};

// 0x0042CAA0 - Initialize the title screen: register the callback pair,
// then look up "title.anm" (slot 0x19) and "title_v.anm" (slot 0x1A).
// When both resolve the ready flag sets, the retail selection global at
// 0x004918A4 clears, and the call returns 0; otherwise the retail error
// record (0x0046CB68) is reported and the call returns -1.
int32_t Title_RegisterTasks(
    void* owner, TitleInitState* state,
    int32_t* (*find_resource)(int32_t slot, const char* name),
    void (*report_error)(), SchedulerCreateFn create,
    SchedulerRegisterFn register_primary,
    SchedulerRegisterFn register_secondary, SchedulerFunction update_proc,
    SchedulerFunction render_proc);
