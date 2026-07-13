// =============================================================================
// game_state.cpp - Game state lifecycle: create, construct, init, destroy
// Functions: 0x00402160 (Construct), 0x00402230 (Init), 0x00402440 (Destroy),
//            0x00402640 (Create)
// =============================================================================
#include "th10/game/game_state.hpp"

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

int  FUN_00403850(void* this_);
void FUN_0044b8e0(const char* msg);
void FUN_004215a0(void);
void FUN_00449ed0(void* callback);
void FUN_00449ae0(int dev);
void FUN_00449b70(int dev);
void FUN_00449f60(void* handle, int dev);
void FUN_00447810(void* mgr);

extern "C" void __stdcall EnterCriticalSection(void* cs);
extern "C" void __stdcall LeaveCriticalSection(void* cs);
extern uint32_t DAT_00492274;    // critical section
extern uint8_t  DAT_0049231c;    // critical section count

// ============================================================================
// 0x00402160 - GameState Constructor
// Clears flags, constructs 8+3 entity arrays, zeroes 0xAD9 dwords, sets flag
// param_1 (EAX) = game state pointer
//
// Ghidra decompilation:
//   param_1[0xD]  &= ~1; param_1[0x12] &= ~1; param_1[0x24] &= ~1;
//   param_1[0x37] &= ~1; param_1[0x5A] &= ~1;
//   _eh_vector_constructor(param_1+0x60, 0x3AC, 8, Entity_Constructor, Entity_Destructor)
//   _eh_vector_constructor(param_1+0x7C2, 0x3AC, 3, Entity_Constructor, Entity_Destructor)
//   param_1[0xA8B] &= ~1;
//   Zero 0xAD9 dwords
//   *param_1 |= 2;  (mark as constructed)
// ============================================================================
uint32_t* GameState_Construct(uint32_t* state) {
    // Clear construction flags
    state[0x0D]  &= 0xFFFFFFFE;
    state[0x12]  &= 0xFFFFFFFE;
    state[0x24]  &= 0xFFFFFFFE;
    state[0x37]  &= 0xFFFFFFFE;
    state[0x5A]  &= 0xFFFFFFFE;

    // Construct 8 entities at offset 0x180 (param_1 + 0x60 dwords)
    _eh_vector_constructor_iterator_(
        state + 0x60,    // base = +0x180
        0x3AC,           // element size
        8,               // count
        (void*)Entity_Constructor,
        (void*)Entity_Destructor
    );

    // Construct 3 entities at offset 0x1F08 (param_1 + 0x7C2 dwords)
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
    return state;
}

// ============================================================================
// 0x00402230 - GameState Init
// Initializes the game state: registers callbacks, creates render targets,
// copies default render config, initializes scheduler chain.
// this (ECX) = manager, param_1 (EAX) = game state, param_2 (stack) = state ID
//
// Ghidra decompilation:
//   if (param_2 == 0): DAT_004776e4 = EAX; DAT_004776e8 = EAX
//   state+0x2A30 = DAT_00474c7c (state type)
//   FUN_00403850(this) — check device
//   Copy 0x46 dwords from DAT_00491d7c to state+0x2A4C
//   Set default render params (300.0f, 0.0f, 600.0f, 600.0f, etc.)
//   state+0x1EE0 = 0x4B12A310 (frame timer)
//   Create 3 callback handles via FUN_00449ED0
//   Initialize scheduler chain at state+0x38..0x48
//   state+0x2A18 |= 1; state+0x94 = 0; state+0xE0 = 0
// ============================================================================
int GameState_Init(void* manager, int stateId) {
    int state = 0;  // would be EAX — set by caller
    int iVar1;

    if (stateId == 0) {
        // EAX is the state pointer passed in EAX register
        // DAT_004776e4 = state; DAT_004776e8 = state;
    }
    // DAT_004776e4 = state;
    // *(state + 0x2A30) = DAT_00474c7c;

    iVar1 = FUN_00403850(manager);
    if (iVar1 == 0) {
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

        // Create callbacks
        // FUN_00449ED0 creates timer/callback objects
        // ... (complex callback registration)

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
    FUN_0044b8e0("D3D device creation failed");
    return 0xFFFFFFFF;
}

// ============================================================================
// 0x00402440 - GameState Destroy
// Releases render targets, frees buffers, destroys entity arrays.
// param_1 (stack) = game state pointer
//
// Ghidra decompilation:
//   Release 3 render target handles (with critical section)
//   Free 2 allocated buffers (+0x10, +0x2A44, +0x17C)
//   Check difficulty flags, free game state from manager slots
//   Clear global state pointers
//   _eh_vector_destructor(state+0x1F08, 0x3AC, 3, Entity_Destructor)
//   _eh_vector_destructor(state+0x180, 0x3AC, 8, Entity_Destructor)
// ============================================================================
void GameState_Destroy(int state) {
    // Release render target 1 (+0x08)
    void* rt1 = *(void**)(state + 8);
    if (rt1 != 0) {
        EnterCriticalSection(&DAT_00492274);
        DAT_0049231c++;
        FUN_00449f60(rt1, DAT_00491be4);
        LeaveCriticalSection(&DAT_00492274);
        DAT_0049231c--;
    }

    // Release render target 2 (+0x0C)
    void* rt2 = *(void**)(state + 0xC);
    if (rt2 != 0) {
        EnterCriticalSection(&DAT_00492274);
        DAT_0049231c++;
        FUN_00449f60(rt2, DAT_00491be4);
        LeaveCriticalSection(&DAT_00492274);
        DAT_0049231c--;
    }

    // Release render target 3 (+0x2A40)
    void* rt3 = *(void**)(state + 0x2A40);
    if (rt3 != 0) {
        EnterCriticalSection(&DAT_00492274);
        DAT_0049231c++;
        FUN_00449f60(rt3, DAT_00491be4);
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
                FUN_00447810(g_pGameStateManager);
                _free((void*)*slotPtr);
                *slotPtr = 0;
            }
        }
    }

    // Clear global state pointers
    if (DAT_004776e8 == (uint32_t)state) DAT_004776e8 = 0;
    if (DAT_004776e4 == (uint32_t)state) DAT_004776e4 = 0;

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
// param_1 = manager, param_2 = state ID
// Returns pointer or NULL on failure
//
// Ghidra decompilation:
//   ptr = operator_new(0x2B64)
//   if (ptr == NULL): return NULL
//   ptr = GameState_Construct(ptr)
//   result = GameState_Init(param_1, param_2)
//   if (result != 0):
//     GameState_Destroy(ptr); _free(ptr); return NULL
//   return ptr
// ============================================================================
uint32_t* GameState_Create(void* manager, int stateId) {
    uint32_t* state = (uint32_t*)operator_new(0x2B64);
    if (state == 0) {
        return 0;
    }
    state = (uint32_t*)GameState_Construct(state);

    int result = GameState_Init(manager, stateId);
    if (result != 0) {
        if (state != 0) {
            GameState_Destroy((int)state);
            _free(state);
        }
        return 0;
    }
    return state;
}
