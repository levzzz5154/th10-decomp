// =============================================================================
// game_state.cpp - Game state lifecycle: create, construct, init, destroy
// Functions: 0x00402160 (Construct), 0x00402230 (Init), 0x00402440 (Destroy),
//            0x00402640 (Create)
// =============================================================================
#include "th10/game/game_state.hpp"
#include "th10/game/scheduler.hpp"

extern "C" void* operator_new(uint32_t size);
extern "C" void _free(void*);
extern void* g_pGameStateManager;
extern uint32_t DAT_00476f78;
extern uint32_t DAT_004776e4;    // current game state
extern uint32_t DAT_004776e8;    // previous game state
extern uint32_t DAT_00474c7c;    // state type
extern uint32_t DAT_00474ca0;    // global flags
extern uint32_t DAT_00491be4;    // D3D device handle
extern uint32_t DAT_00491d7c[];  // default render config (0x46 dwords)
extern void*   ExceptionList;

extern "C" void _eh_vector_constructor_iterator_(void*, uint32_t, uint32_t, void*, void*);
extern "C" void _eh_vector_destructor_iterator_(void*, uint32_t, uint32_t, void*);

void __fastcall Entity_Constructor(Entity* e);
void __fastcall Entity_Destructor(Entity* e);
void __fastcall Entity_Init(void* unused, Entity* entity);

int  GameState_InitializeRenderResources(void* this_);
void Platform_LogMessage(const char* msg);
void Render_UpdateCameraMatrices(void);
void Scheduler_UnregisterCallback(void* handle, int dev);
void ResourceManager_DestroyContents(void* mgr);

extern "C" void __stdcall EnterCriticalSection(void* cs);
extern "C" void __stdcall LeaveCriticalSection(void* cs);
extern uint32_t DAT_00492274;    // critical section
extern uint8_t  DAT_0049231c;    // critical section count

int GameState_Update(GameState* state);
int GameState_Draw(GameState* state);
int GameState_AfterDraw(GameState* state);

static int __fastcall GameState_UpdateCallback(void* owner) {
    return GameState_Update((GameState*)owner);
}

static int __fastcall GameState_DrawCallback(void* owner) {
    return GameState_Draw((GameState*)owner);
}

static int __fastcall GameState_AfterDrawCallback(void* owner) {
    return GameState_AfterDraw((GameState*)owner);
}

// ============================================================================
// 0x00402160 - GameState Constructor
// Clears flags, constructs 8+3 entity arrays, zeroes 0xAD9 dwords, sets flag
// state (EAX) = game state pointer
//
// Ghidra decompilation:
//   state[0xD]  &= ~1; state[0x12] &= ~1; state[0x24] &= ~1;
//   state[0x37] &= ~1; state[0x5A] &= ~1;
//   _eh_vector_constructor(state+0x60, 0x3AC, 8, Entity_Constructor, Entity_Destructor)
//   _eh_vector_constructor(state+0x7C2, 0x3AC, 3, Entity_Constructor, Entity_Destructor)
//   state[0xA8B] &= ~1;
//   Zero 0xAD9 dwords
//   *state |= 2;  (mark as constructed)
// ============================================================================
GameState* GameState_Construct(GameState* gameState) {
    uint32_t* state = (uint32_t*)gameState;
    // Clear construction flags
    state[0x0D]  &= 0xFFFFFFFE;
    state[0x12]  &= 0xFFFFFFFE;
    state[0x24]  &= 0xFFFFFFFE;
    state[0x37]  &= 0xFFFFFFFE;
    state[0x5A]  &= 0xFFFFFFFE;

    // Construct 8 entities at offset 0x180 (state + 0x60 dwords)
    _eh_vector_constructor_iterator_(
        state + 0x60,    // base = +0x180
        0x3AC,           // element size
        8,               // count
        (void*)Entity_Constructor,
        (void*)Entity_Destructor
    );

    // Construct 3 entities at offset 0x1F08 (state + 0x7C2 dwords)
    _eh_vector_constructor_iterator_(
        state + 0x7C2,   // base = +0x1F08
        0x3AC,           // element size
        3,               // count
        (void*)Entity_Constructor,
        (void*)Entity_Destructor
    );

    state[0xA8B] &= 0xFFFFFFFE;

    // Zero 0xAD9 dwords of state data
    uint32_t* p = state;
    for (int i = 0xAD9; i != 0; i--) {
        *p++ = 0;
    }

    *state |= 2;  // mark constructed
    return gameState;
}

// ============================================================================
// 0x00402230 - GameState Init
// Initializes the game state: registers callbacks, creates render targets,
// copies default render config, initializes scheduler chain.
// this (ECX) = manager, state (EAX) = game state, state_id (stack)
//
// Ghidra decompilation:
//   if (state_id == 0): DAT_004776e8 = EAX; preserve DAT_004776e4
//   otherwise: DAT_004776e4 = EAX
//   state+0x2A30 = DAT_00474c7c (state type)
//   GameState_InitializeRenderResources(this) — check device
//   Copy 0x46 dwords from DAT_00491d7c to state+0x2A4C
//   Set default render params (300.0f, 0.0f, 600.0f, 600.0f, etc.)
//   state+0x1EE0 = 0x4B12A310 (frame timer)
//   Create 3 callback handles via SchedulerCallback_Create (0x00449ED0)
//   Initialize scheduler chain at state+0x38..0x48
//   state+0x2A18 |= 1; state+0x94 = 0; state+0xE0 = 0
// ============================================================================
int GameState_Init(void* manager, GameState* gameState, int stateId) {
    uint8_t* state = (uint8_t*)gameState;
    int initialization_result;

    // 0x0040223C keeps the active state in DAT_004776e4 when creating
    // state zero, and records the newly created state in DAT_004776e8.
    // Other state IDs replace the active-state pointer directly.
    if (stateId == 0) {
        DAT_004776e8 = (uint32_t)gameState;
    } else {
        DAT_004776e4 = (uint32_t)gameState;
    }
    *(uint32_t*)(state + 0x2A30) = DAT_00474c7c;

    initialization_result = GameState_InitializeRenderResources(manager);
    if (initialization_result == 0) {
        // Copy default render config (0x46 dwords)
        uint32_t* src = &DAT_00491d7c[0];
        uint32_t* dst = (uint32_t*)(state + 0x2A4C);
        for (int i = 0x46; i != 0; i--) {
            *dst++ = *src++;
        }

        // Set default render params
        *(uint32_t*)(state + 0x2A4C) = 0;
        *(uint32_t*)(state + 0x2A50) = 0;
        *(uint32_t*)(state + 0x2A54) = 0xC4160000;  // -300.0f
        *(uint32_t*)(state + 0x2A58) = 0;
        *(uint32_t*)(state + 0x2A5C) = 0x43960000;  // 300.0f
        *(uint32_t*)(state + 0x2A60) = 0x44160000;  // 600.0f
        *(uint32_t*)(state + 0x2A64) = 0;
        *(uint32_t*)(state + 0x2A68) = 0x3F800000;  // 1.0f
        *(uint32_t*)(state + 0x2A6C) = 0;
        *(uint32_t*)(state + 0x2A88) = 0;
        *(uint32_t*)(state + 0x2A8C) = 0;
        *(uint32_t*)(state + 0x2A90) = 0;
        *(uint32_t*)(state + 0x1EE0) = 0x4B12A310;

        SchedulerCallback* callback =
            SchedulerCallback_Create(GameState_UpdateCallback);
        if (callback == 0) return 0xFFFFFFFF;
        callback->owner = gameState;
        callback->flags &= ~2u;
        Scheduler_RegisterPrimary(
            callback, stateId + 0x0C, (void*)DAT_00491be4);
        *(SchedulerCallback**)(state + 8) = callback;

        callback = SchedulerCallback_Create(GameState_DrawCallback);
        if (callback == 0) return 0xFFFFFFFF;
        callback->flags &= ~2u;
        callback->owner = gameState;
        Scheduler_RegisterSecondary(
            callback, stateId + 7, (void*)DAT_00491be4);
        *(SchedulerCallback**)(state + 0x0C) = callback;

        callback = SchedulerCallback_Create(GameState_AfterDrawCallback);
        if (callback == 0) return 0xFFFFFFFF;
        callback->owner = gameState;
        callback->flags &= ~2u;
        Scheduler_RegisterSecondary(
            callback, stateId + 0x0A, (void*)DAT_00491be4);
        *(SchedulerCallback**)(state + 0x2A40) = callback;
        *(uint32_t*)(state + 0x2A34) = 0;

        // Initialize scheduler chain
        if ((*(uint32_t*)(state + 0x48) & 1) == 0) {
            *(uint32_t*)(state + 0x3C) = 0;
            *(uint32_t*)(state + 0x38) = 0xFFF0BDC1;
            *(uint32_t*)(state + 0x40) = 0;
            *(uint32_t*)(state + 0x44) = (uint32_t)&DAT_00476f78;
            *(uint32_t*)(state + 0x48) |= 1;
        }
        *(uint32_t*)(state + 0x3C) = 0;
        *(uint32_t*)(state + 0x40) = 0;
        *(uint32_t*)(state + 0x38) = 0xFFFFFFFF;
        *(uint32_t*)(state + 0x2A18) |= 1;
        *(uint32_t*)(state + 0x94) = 0;
        *(uint32_t*)(state + 0xE0) = 0;
        return 0;
    }
    Platform_LogMessage("D3D device creation failed");
    return 0xFFFFFFFF;
}

// ============================================================================
// 0x00402440 - GameState Destroy
// Releases render targets, frees buffers, destroys entity arrays.
// state (stack) = game state pointer
//
// Ghidra decompilation:
//   Release 3 render target handles (with critical section)
//   Free 2 allocated buffers (+0x10, +0x2A44, +0x17C)
//   Check difficulty flags, free game state from manager slots
//   Clear global state pointers
//   _eh_vector_destructor(state+0x1F08, 0x3AC, 3, Entity_Destructor)
//   _eh_vector_destructor(state+0x180, 0x3AC, 8, Entity_Destructor)
// ============================================================================
void GameState_Destroy(GameState* gameState) {
    uint8_t* state = (uint8_t*)gameState;
    // Release render target 1 (+0x08)
    void* rt1 = *(void**)(state + 8);
    if (rt1 != 0) {
        EnterCriticalSection(&DAT_00492274);
        DAT_0049231c++;
        Scheduler_UnregisterCallback(rt1, DAT_00491be4);
        LeaveCriticalSection(&DAT_00492274);
        DAT_0049231c--;
    }

    // Release render target 2 (+0x0C)
    void* rt2 = *(void**)(state + 0xC);
    if (rt2 != 0) {
        EnterCriticalSection(&DAT_00492274);
        DAT_0049231c++;
        Scheduler_UnregisterCallback(rt2, DAT_00491be4);
        LeaveCriticalSection(&DAT_00492274);
        DAT_0049231c--;
    }

    // Release render target 3 (+0x2A40)
    void* rt3 = *(void**)(state + 0x2A40);
    if (rt3 != 0) {
        EnterCriticalSection(&DAT_00492274);
        DAT_0049231c++;
        Scheduler_UnregisterCallback(rt3, DAT_00491be4);
        LeaveCriticalSection(&DAT_00492274);
        DAT_0049231c--;
    }

    // Free allocated buffers
    void* buf1 = *(void**)(state + 0x10);
    if (buf1 != 0) { _free(buf1); *(uint32_t*)(state + 0x10) = 0; }

    void* buf2 = *(void**)(state + 0x2A44);
    if (buf2 != 0) { _free(buf2); }
    *(uint32_t*)(state + 0x2A44) = 0;

    void* buf3 = *(void**)(state + 0x17C);
    if (buf3 != 0) { _free(buf3); *(uint32_t*)(state + 0x17C) = 0; }

    // Check if this state is in the manager's slots and free it
    if ((DAT_00474ca0 & 1) == 0) {
        uint32_t slot = (*(uint32_t*)(state + 0x2A30) & 1) + 4;
        if (slot < 0x21) {
            uint32_t* slotPtr = (uint32_t*)((int)g_pGameStateManager + slot * 4 + 0x3AD06C);
            if (*slotPtr != 0) {
                ResourceManager_DestroyContents(g_pGameStateManager);
                _free((void*)*slotPtr);
                *slotPtr = 0;
            }
        }
    }

    // Clear global state pointers
    if (DAT_004776e8 == (uint32_t)gameState) DAT_004776e8 = 0;
    if (DAT_004776e4 == (uint32_t)gameState) DAT_004776e4 = 0;

    // Destroy entity arrays (3 then 8, reverse order)
    _eh_vector_destructor_iterator_(
        (void*)(state + 0x1F08),
        0x3AC, 3,
        (void*)Entity_Destructor
    );
    _eh_vector_destructor_iterator_(
        (void*)(state + 0x180),
        0x3AC, 8,
        (void*)Entity_Destructor
    );
}

// ============================================================================
// 0x00402640 - GameState Create
// Allocates 0x2B64 bytes, constructs, and initializes a game state.
// manager = state manager, state_id = requested state ID
// Returns pointer or NULL on failure
//
// Ghidra decompilation:
//   ptr = operator_new(0x2B64)
//   if (ptr == NULL): return NULL
//   ptr = GameState_Construct(ptr)
//   result = GameState_Init(manager, state_id)
//   if (result != 0):
//     GameState_Destroy(ptr); _free(ptr); return NULL
//   return ptr
// ============================================================================
GameState* GameState_Create(void* manager, int stateId) {
    GameState* state = (GameState*)operator_new(sizeof(GameState));
    if (state == 0) {
        return 0;
    }
    state = GameState_Construct(state);

    int result = GameState_Init(manager, state, stateId);
    if (result != 0) {
        if (state != 0) {
            GameState_Destroy(state);
            _free(state);
        }
        return 0;
    }
    return state;
}
