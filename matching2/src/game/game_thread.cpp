// =============================================================================
// game_thread.cpp - Main game thread lifecycle
// Functions: 0x00401000 (Construct), 0x00401110 (Init), 0x00401260 (Destroy),
//            0x00401440 (Create)
// =============================================================================
#include "th10/game/game_state.hpp"

extern "C" void* operator_new(uint32_t size);
extern "C" void _free(void*);
extern void* g_pGameStateManager;
extern void* g_pGameThread;
extern void* PTR_LAB_0046cb14;     // vtable for GameThread
extern uint32_t DAT_00491be4;      // D3D device handle
extern void*   ExceptionList;

extern "C" void __stdcall EnterCriticalSection(void* cs);
extern "C" void __stdcall LeaveCriticalSection(void* cs);
extern uint32_t DAT_00492274;
extern uint8_t  DAT_0049231c;

void __fastcall Entity_Init(void* unused, Entity* entity);
void FUN_0044b810(char* buf, const char* msg);
void FUN_0044b8e0(const char* msg);
void FUN_00449ed0(void* callback);
void FUN_00449ae0(int dev);
void FUN_00449b70(int dev);
void FUN_00449f60(void* handle, int dev);
void FUN_00447810(void* mgr);
void* FUN_00447280(int type, int mgr, const char* name);
void FUN_0043e5a0(int handle, int idx);

// ============================================================================
// 0x00401000 - GameThread Constructor
// ESI = game thread pointer (unaff_ESI — set by caller)
// Constructs two entity blocks (0x3AC each), zeroes 0x226B dwords,
// sets default values.
//
// Ghidra decompilation:
//   *unaff_ESI = &PTR_LAB_0046cb14  (vtable)
//   Clear construction flags at offsets: 0x20, 0x31, 0x44, 0x4F, 0x62, 0x71,
//     0x84, 0x8F, 0xE3
//   Zero 0xEB dwords from unaff_ESI+5 (first entity block)
//   Set word at unaff_ESI+0xE6 = 0xFFFF
//   Clear flags at 0x10B, 0x11C, 0x12F, 0x13A, 0x14D, 0x15C, 0x16F, 0x17A, 0x1CE
//   Zero 0xEB dwords from unaff_ESI+0xF0 (second entity block)
//   Set word at unaff_ESI+0x1D1 = 0xFFFF
//   Zero 0x226B dwords total
//   *unaff_ESI |= 2 (mark constructed)
//   g_pGameThread = unaff_ESI
//   unaff_ESI[0x225D] = 0xFFFFFFFF
//   unaff_ESI[0x225E] = 0x3F800000 (1.0f)
//   unaff_ESI[0x225F] = 0x3F800000 (1.0f)
//   unaff_ESI[0x2261] = 0
//   unaff_ESI[0x2263] = 9
// ============================================================================
void GameThread_Construct(uint32_t* gt) {
    *gt = (uint32_t)&PTR_LAB_0046cb14;  // vtable

    // Clear construction flags
    gt[0x20]  &= 0xFFFFFFFE;
    gt[0x31]  &= 0xFFFFFFFE;
    gt[0x44]  &= 0xFFFFFFFE;
    gt[0x4F]  &= 0xFFFFFFFE;
    gt[0x62]  &= 0xFFFFFFFE;
    gt[0x71]  &= 0xFFFFFFFE;
    gt[0x84]  &= 0xFFFFFFFE;
    gt[0x8F]  &= 0xFFFFFFFE;
    gt[0xE3]  &= 0xFFFFFFFE;

    // Zero first entity block (0xEB dwords from gt+5)
    uint32_t* p = gt + 5;
    for (int i = 0xEB; i != 0; i--) {
        *p++ = 0;
    }
    *(uint16_t*)(gt + 0xE6) = 0xFFFF;

    // Clear more construction flags
    gt[0x10B] &= 0xFFFFFFFE;
    gt[0x11C] &= 0xFFFFFFFE;
    gt[0x12F] &= 0xFFFFFFFE;
    gt[0x13A] &= 0xFFFFFFFE;
    gt[0x14D] &= 0xFFFFFFFE;
    gt[0x15C] &= 0xFFFFFFFE;
    gt[0x16F] &= 0xFFFFFFFE;
    gt[0x17A] &= 0xFFFFFFFE;
    gt[0x1CE] &= 0xFFFFFFFE;

    // Zero second entity block (0xEB dwords from gt+0xF0)
    p = gt + 0xF0;
    for (int i = 0xEB; i != 0; i--) {
        *p++ = 0;
    }
    *(uint16_t*)(gt + 0x1D1) = 0xFFFF;

    // Zero entire game thread (0x226B dwords)
    p = gt;
    for (int i = 0x226B; i != 0; i--) {
        *p++ = 0;
    }

    // Set flags and defaults
    *gt |= 2;
    g_pGameThread = gt;
    gt[0x225D] = 0xFFFFFFFF;
    gt[0x225E] = 0x3F800000;  // 1.0f
    gt[0x225F] = 0x3F800000;  // 1.0f
    gt[0x2261] = 0;
    gt[0x2263] = 9;
}

// ============================================================================
// 0x00401110 - GameThread Init
// EAX = game thread pointer
// Loads animation resources (ascii.anm, text.anm, capture.anm),
// creates callback timers, initializes two entities.
//
// Ghidra decompilation:
//   Load "ascii.anm" -> +0x8994
//   Load "text.anm" -> +0x899C
//   Load "capture.anm" -> +0x8998
//   Create 3 callback handles
//   Entity_Init(entity at +0x14, anim=ascii.anm slot 0)
//   Entity_Init(entity at +0x3C0, anim=ascii.anm slot 0x62)
// ============================================================================
int GameThread_Init(void) {
    // EAX is the game thread pointer (passed via EAX register)
    int gt = 0;  // placeholder — actually from EAX

    // Load animation resources
    void* asciiAnm = FUN_00447280(2, (int)g_pGameStateManager, "ascii.anm");
    *(void**)(gt + 0x8994) = asciiAnm;
    if (asciiAnm == 0) goto fail;

    void* textAnm = FUN_00447280(0, (int)g_pGameStateManager, "text.anm");
    *(void**)(gt + 0x899C) = textAnm;
    if (textAnm == 0) goto fail;

    void* captureAnm = FUN_00447280(3, (int)g_pGameStateManager, "capture.anm");
    *(void**)(gt + 0x8998) = captureAnm;
    if (captureAnm == 0) goto fail;

    // Create callback timers
    // ... (complex callback registration)

    // Initialize entities with animation data
    Entity_Init(0, (Entity*)(gt + 0x14));
    *(uint32_t*)(gt + 0x31C) = (uint32_t)asciiAnm;
    FUN_0043e5a0((int)asciiAnm, 0);

    Entity_Init(0, (Entity*)(gt + 0x3C0));
    *(uint32_t*)(gt + 0x6C8) = (uint32_t)asciiAnm;
    FUN_0043e5a0((int)asciiAnm, 0x62);

    return 0;

fail:
    FUN_0044b810((char*)0x00474F70, (const char*)0x0046CB68);
    return 0xFFFFFFFF;
}

// ============================================================================
// 0x00401260 - GameThread Destroy
// param_1 = game thread pointer
// Releases animation resources, frees buffers, destroys entities.
//
// Ghidra decompilation:
//   Set vtable
//   Release 3 resource handles (+0xC, +0x10, +0x89A8) with critical section
//   Free 3 game state slots from manager
//   g_pGameThread = NULL
//   Free buffer at +0x1C6*4
//   Free buffer at +0xDB*4
// ============================================================================
void GameThread_Destroy(uint32_t* gt) {
    *gt = (uint32_t)&PTR_LAB_0046cb14;

    // Release callback handle 1 (gt[3])
    void* h1 = (void*)gt[3];
    if (h1 != 0) {
        EnterCriticalSection(&DAT_00492274);
        DAT_0049231c++;
        FUN_00449f60(h1, DAT_00491be4);
        LeaveCriticalSection(&DAT_00492274);
        DAT_0049231c--;
    }

    // Release callback handle 2 (gt[4])
    void* h2 = (void*)gt[4];
    if (h2 != 0) {
        EnterCriticalSection(&DAT_00492274);
        DAT_0049231c++;
        FUN_00449f60(h2, DAT_00491be4);
        LeaveCriticalSection(&DAT_00492274);
        DAT_0049231c--;
    }

    // Release callback handle 3 (gt[0x226A])
    void* h3 = (void*)gt[0x226A];
    if (h3 != 0) {
        EnterCriticalSection(&DAT_00492274);
        DAT_0049231c++;
        FUN_00449f60(h3, DAT_00491be4);
        LeaveCriticalSection(&DAT_00492274);
        DAT_0049231c--;
    }

    // Free game state slots from manager
    uint32_t* slot;
    slot = (uint32_t*)((int)g_pGameStateManager + 0x3AD074);
    if (*slot != 0) { FUN_00447810(g_pGameStateManager); _free((void*)*slot); *slot = 0; }

    slot = (uint32_t*)((int)g_pGameStateManager + 0x3AD06C);
    if (*slot != 0) { FUN_00447810(g_pGameStateManager); _free((void*)*slot); *slot = 0; }

    slot = (uint32_t*)((int)g_pGameStateManager + 0x3AD078);
    if (*slot != 0) { FUN_00447810(g_pGameStateManager); _free((void*)*slot); *slot = 0; }

    g_pGameThread = 0;

    // Free allocated buffers
    void* buf1 = (void*)gt[0x1C6];
    if (buf1 != 0) _free(buf1);
    gt[0x1C6] = 0;

    void* buf2 = (void*)gt[0xDB];
    if (buf2 != 0) { _free(buf2); gt[0xDB] = 0; }
    else { gt[0xDB] = 0; }
}

// ============================================================================
// 0x00401440 - GameThread Create
// Allocates 0x89AC bytes, constructs, and initializes the game thread.
// Returns pointer or NULL on failure
//
// Ghidra decompilation:
//   ptr = operator_new(0x89AC)
//   if (ptr == NULL): return NULL
//   ptr = GameThread_Construct(ptr)  (uses ESI)
//   result = GameThread_Init(ptr)   (uses EAX)
//   if (result != 0):
//     GameThread_Destroy(ptr); _free(ptr); return NULL
//   return ptr
// ============================================================================
uint32_t* GameThread_Create(void) {
    uint32_t* gt = (uint32_t*)operator_new(0x89AC);
    if (gt == 0) {
        return 0;
    }
    GameThread_Construct(gt);

    // GameThread_Init uses EAX = gt (non-standard register passing)
    // In real code, we'd need to set EAX before calling
    int result = 0;  // would call GameThread_Init with EAX=gt
    if (result != 0) {
        if (gt != 0) {
            GameThread_Destroy(gt);
            _free(gt);
        }
        return 0;
    }
    return gt;
}
