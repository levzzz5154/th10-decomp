#pragma once

// Manager factory/registration paths and owned scheduler callbacks (retail batches 7-8).
#include "th10/game/scheduler.hpp"
#include "th10/util/scalars.hpp"

void* EnemyManager_Create(void* script_name, void* (*allocate)(unsigned int size),
                          void** global_slot,
                          int (*initialize)(void* script_name),
                          void (*destroy)(void* manager),
                          void (*free_memory)(void* memory));

void* AsciiManager_Create(void* (*allocate)(unsigned int size),
                          void (*initialize)(void* manager));

enum AsciiCallbackKind {
    kAsciiUpdateBasic = 0,
    kAsciiUpdateMode1,
    kAsciiUpdateMode2,
    kAsciiUpdateMode4,
    kAsciiUpdateMode6,
    kAsciiUpdateMode8,
    kAsciiDrawMode0,
    kAsciiDrawMode2,
    kAsciiDrawMode4,
    kAsciiDrawMode6,
    kAsciiDrawMode7,
};

struct AsciiManagerInitState {
    void* update_task;          // retail +0x08
    void* draw_task;            // retail +0x0C
    int mode;                   // retail +0x10
    int argument_4;             // retail +0x1C
    int argument_5;             // retail +0x20
    int argument_6;             // retail +0x24
    int argument_7;             // retail +0x28
    int color;                  // retail +0x18
    int timer_target;           // retail +0x30
    int timer_current;          // retail +0x34
    int timer_previous;         // retail +0x38
    const float* timer_speed;   // retail +0x3C
    unsigned int timer_flags;   // retail +0x40
};

struct AsciiManagerInitHooks {
    void* context;
    const float* frame_speed;
    void* (*create_update)(void* context, int callback_kind, int priority,
                           void* owner);
    void* (*create_draw)(void* context, int callback_kind, void* queue,
                         void* owner);
    void (*set_finish_callback)(void* context, void* update_task);
};

// 0x0043C970 - Select the update/draw callback pair for modes 0..8,
// initialize the embedded timer, and store the five creation arguments.
int AsciiManager_Initialize(AsciiManagerInitState* state, void* draw_queue,
                            int mode, int argument_4, int argument_5,
                            int argument_6, int argument_7,
                            const AsciiManagerInitHooks* hooks);

void* StageManager_Create(const char* stage_path,
                          void* (*allocate)(unsigned int size),
                          void (*construct_slots)(void* slots, int stride,
                                                  int count),
                          int (*initialize)(void* manager,
                                            const char* stage_path),
                          void (*destroy)(void* manager),
                          void (*free_memory)(void* memory));

void EffectManager_InitializePools(Word* manager_words,
                                   unsigned int word_count,
                                   const Byte* (*load_effect_table)(
                                       unsigned int* size_out),
                                   const Byte** table_slot,
                                   void (*initialize_shared)(void* shared_block),
                                   void* shared_block,
                                   void (*initialize_pool)(void* pool),
                                   Byte* first_pool,
                                   unsigned int pool_stride,
                                   unsigned int pool_count,
                                   void (*finalize)(void));

// Callback node fields the registration leaves touch (retail node +0x04/+0x20).
struct SchedulerCallbackNode {
    unsigned int flags;
    void* owner;
};

SchedulerCallbackNode* Scheduler_RegisterOwnedCallback(
    void* owner, void* callback,
    SchedulerCallbackNode* (*create)(void* callback),
    void (*enqueue)(void* queue), void* queue);

// Registration block shared by the update/draw registration leaves.
struct ManagerRegistration {
    int frame_stamp;                // retail +0x10
    SchedulerCallbackNode* update;     // retail +0x08
    SchedulerCallbackNode* draw;       // retail +0x0C
    int stored_stamp;               // retail +0x320
};

int EffectManager_OnRegister(ManagerRegistration* manager, int frame_stamp,
                             void* update_callback, void* draw_callback,
                             SchedulerCallbackNode* (*create)(void* callback),
                             void (*enqueue_update)(void* queue),
                             void (*enqueue_draw)(void* queue), void* queue,
                             void (*reset_timer)(void* timer_block),
                             void* timer_block,
                             void (*preload)(int frame_stamp, int argument));

struct ParticleEffectRuntimeBindings {
    SchedulerFunction update;
    SchedulerFunction draw;
};

void ParticleEffectRuntime_SetBindings(
    const ParticleEffectRuntimeBindings* bindings);
int ParticleEffectRuntime_Initialize(void* manager);

// --- 0x00408C90 / 0x00414830 ---------------------------------------------------
void* PlayerManager_Create(void* (*allocate)(unsigned int size),
                           void* (*construct)(void* memory),
                           int (*initialize)(void),
                           void (*destroy)(void* manager),
                           void (*free_memory)(void* memory));
void* PlayerManager_Construct(void* memory);

void* ItemManager_Create(void* (*allocate)(unsigned int size),
                         void* (*construct)(void* memory),
                         int (*initialize)(void),
                         void (*destroy)(void* manager),
                         void (*free_memory)(void* memory));
void* ItemManager_Construct(void* memory);

// --- 0x00429610 --------------------------------------------------------------
void* StageManager_CreateFromScript(
    const char* script_path, void* (*allocate)(unsigned int size),
    void (*construct_slots)(void* slots, int stride, int count),
    int (*initialize)(const char* script_path), void (*destroy)(void* manager),
    void (*free_memory)(void* memory));

// --- 0x0041AED0 --------------------------------------------------------------
void* EffectManager_Create(void* (*allocate)(unsigned int size),
                           void (*construct_slots)(void* slots, int stride,
                                                   int count),
                           void** global_slot, int (*initialize)(void),
                           void (*destroy)(void* manager),
                           void (*free_memory)(void* memory));
