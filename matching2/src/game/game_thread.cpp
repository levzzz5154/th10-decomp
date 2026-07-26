// =============================================================================
// game_thread.cpp - Main game thread lifecycle
// Functions: 0x00401000 (Construct), 0x00401110 (Init), 0x00401260 (Destroy),
//            0x00401440 (Create)
// =============================================================================
#include "th10/game/game_state.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/render/animation_manager.hpp"

#include <cstdint>

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
void Logger_AppendFormatted(char* buf, const char* msg);
void Platform_LogMessage(const char* msg);
void Scheduler_UnregisterCallback(void* handle, int dev);
void ResourceManager_DestroyResource(void* manager, void* resource);
void* ResourceManager_FindResource(int type, int mgr, const char* name);

int GameThread_Update(GameThread* gameThread);
int GameThread_Draw(GameThread* gameThread);

namespace {

int GameThread_RenderTextQueue(GameThread* gameThread,
                               unsigned int queue_offset,
                               unsigned int count_offset,
                               bool proportional_font_one) {
    if (gameThread == nullptr)
        return 1;
    auto* thread = reinterpret_cast<unsigned char*>(gameThread);
    auto* animation = reinterpret_cast<AnimationObject*>(thread + 0x14);
    auto* object = thread + 0x14;
    auto* resource = *reinterpret_cast<unsigned char**>(thread + 0x8994);
    if (resource == nullptr)
        return 1;
    auto* sprites = *reinterpret_cast<unsigned char**>(resource + 0x118);
    if (sprites == nullptr)
        return 1;

    auto& flags = *reinterpret_cast<unsigned int*>(object + 0x35c);
    flags = (flags & ~0x00280000u) | 0x00140001u;
    const int count = *reinterpret_cast<int*>(thread + count_offset);
    const int glyph_scale =
        *reinterpret_cast<int*>(thread + 0x898c);
    for (int record_index = 0; record_index < count; ++record_index) {
        unsigned char* record =
            thread + queue_offset + record_index * 0x68;
        float start_x = *reinterpret_cast<float*>(record + 0x40);
        float x = start_x;
        float y = *reinterpret_cast<float*>(record + 0x44);
        const float z = *reinterpret_cast<float*>(record + 0x48);
        const float scale_x = *reinterpret_cast<float*>(record + 0x50);
        const float scale_y = *reinterpret_cast<float*>(record + 0x54);
        const int font = *reinterpret_cast<int*>(record + 0x60);
        const float advance =
            proportional_font_one && font == 1 ? 7.0f :
            static_cast<float>(glyph_scale) * scale_x;
        const float line_height =
            proportional_font_one && font == 1 ? 9.0f : 14.0f;
        for (const unsigned char* text = record; *text != 0; ++text) {
            if (*text == '\n') {
                x = start_x;
                y += line_height * scale_y;
                continue;
            }
            if (*text != ' ') {
                const unsigned int glyph =
                    static_cast<unsigned int>(
                        font * 0x62 + static_cast<int>(*text) - 0x20);
                unsigned char* sprite = sprites + glyph * 0x44;
                *reinterpret_cast<void**>(object + 0x394) = sprite;
                *reinterpret_cast<float*>(object + 0x4c) =
                    *reinterpret_cast<float*>(sprite + 0x30);
                *reinterpret_cast<float*>(object + 0x50) =
                    *reinterpret_cast<float*>(sprite + 0x34);
                *reinterpret_cast<float*>(object + 0x3c) = scale_x;
                *reinterpret_cast<float*>(object + 0x40) = scale_y;
                *reinterpret_cast<float*>(object + 0x334) = x;
                *reinterpret_cast<float*>(object + 0x338) = y;
                *reinterpret_cast<float*>(object + 0x33c) = z;
                const unsigned int color =
                    *reinterpret_cast<unsigned int*>(record + 0x4c);
                if (*reinterpret_cast<int*>(record + 0x64) != 0) {
                    *reinterpret_cast<unsigned int*>(object + 0x2fc) =
                        color & 0xff000000u;
                    *reinterpret_cast<float*>(object + 0x334) = x + 1.0f;
                    *reinterpret_cast<float*>(object + 0x338) = y + 1.0f;
                    AnimationObject_Render(
                        g_pGameStateManager, animation);
                    *reinterpret_cast<float*>(object + 0x334) = x;
                    *reinterpret_cast<float*>(object + 0x338) = y;
                }
                *reinterpret_cast<unsigned int*>(object + 0x2fc) = color;
                AnimationObject_Render(g_pGameStateManager, animation);
            }
            x += advance;
        }
    }
    return 1;
}

} // namespace

int GameThread_Update(GameThread* gameThread) {
    // 0x00401760: first text queue, 0x100 records at +0x76C.
    return GameThread_RenderTextQueue(
        gameThread, 0x76c, 0x896c, true);
}

int GameThread_Draw(GameThread* gameThread) {
    // 0x00401A50: second text queue, 0x40 records at +0x6F6C.
    return GameThread_RenderTextQueue(
        gameThread, 0x6f6c, 0x8970, false);
}

static int __fastcall GameThread_BeginFrameCallback(void* owner) {
    uint32_t* gameThread = (uint32_t*)owner;
    *(uint32_t*)((uint8_t*)gameThread + 0x896C) = 0;
    *(uint32_t*)((uint8_t*)gameThread + 0x8970) = 0;
    ++*(uint32_t*)((uint8_t*)gameThread + 0x8990);
    return 1;
}

static int __fastcall GameThread_UpdateCallback(void* owner) {
    return GameThread_Update((GameThread*)owner);
}

static int __fastcall GameThread_DrawCallback(void* owner) {
    return GameThread_Draw((GameThread*)owner);
}

// ============================================================================
// 0x00401000 - GameThread Constructor
// ESI = game_thread pointer (hidden register input set by caller)
// Constructs two entity blocks (0x3AC each), zeroes 0x226B dwords,
// sets default values.
//
// Ghidra decompilation:
//   *game_thread = &PTR_LAB_0046cb14  (vtable)
//   Clear construction flags at offsets: 0x20, 0x31, 0x44, 0x4F, 0x62, 0x71,
//     0x84, 0x8F, 0xE3
//   Zero 0xEB dwords from game_thread+5 (first entity block)
//   Set word at game_thread+0xE6 = 0xFFFF
//   Clear flags at 0x10B, 0x11C, 0x12F, 0x13A, 0x14D, 0x15C, 0x16F, 0x17A, 0x1CE
//   Zero 0xEB dwords from game_thread+0xF0 (second entity block)
//   Set word at game_thread+0x1D1 = 0xFFFF
//   Zero 0x226B dwords total
//   *game_thread |= 2 (mark constructed)
//   g_pGameThread = game_thread
//   game_thread[0x225D] = 0xFFFFFFFF
//   game_thread[0x225E] = 0x3F800000 (1.0f)
//   game_thread[0x225F] = 0x3F800000 (1.0f)
//   game_thread[0x2261] = 0
//   game_thread[0x2263] = 9
// ============================================================================
GameThread* GameThread_Construct(GameThread* gameThread) {
    uint32_t* gt = (uint32_t*)gameThread;
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
    return gameThread;
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
int GameThread_Init(GameThread* gameThread) {
    uint8_t* gt = (uint8_t*)gameThread;
    void* textAnm = 0;
    void* captureAnm = 0;
    SchedulerCallback* callback = 0;

    // Load animation resources
    void* asciiAnm = ResourceManager_FindResource(2, (int)g_pGameStateManager, "ascii.anm");
    *(void**)(gt + 0x8994) = asciiAnm;
    if (asciiAnm == 0) goto fail;

    textAnm = ResourceManager_FindResource(0, (int)g_pGameStateManager, "text.anm");
    *(void**)(gt + 0x899C) = textAnm;
    if (textAnm == 0) goto fail;

    captureAnm = ResourceManager_FindResource(3, (int)g_pGameStateManager, "capture.anm");
    *(void**)(gt + 0x8998) = captureAnm;
    if (captureAnm == 0) goto fail;

    callback = SchedulerCallback_Create(GameThread_BeginFrameCallback);
    if (callback == 0) goto fail;
    callback->flags &= ~2u;
    callback->owner = gameThread;
    Scheduler_RegisterPrimary(callback, 4, (void*)(uintptr_t)DAT_00491be4);
    gameThread->callback1 = callback;

    callback = SchedulerCallback_Create(GameThread_UpdateCallback);
    if (callback == 0) goto fail;
    callback->flags &= ~2u;
    callback->owner = gameThread;
    Scheduler_RegisterSecondary(callback, 0x30, (void*)(uintptr_t)DAT_00491be4);
    gameThread->callback2 = callback;

    callback = SchedulerCallback_Create(GameThread_DrawCallback);
    if (callback == 0) goto fail;
    callback->flags &= ~2u;
    callback->owner = gameThread;
    Scheduler_RegisterSecondary(callback, 0x26, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(gt + 0x89A8) = callback;

    // Initialize entities with animation data
    Entity_Init(0, (Entity*)(gt + 0x14));
    *(uint32_t*)(gt + 0x31C) = (uint32_t)asciiAnm;
    AnimationObject_ConfigureFromResource(gt + 0x14, asciiAnm, 0);

    Entity_Init(0, (Entity*)(gt + 0x3C0));
    *(uint32_t*)(gt + 0x6C8) = (uint32_t)asciiAnm;
    AnimationObject_ConfigureFromResource(gt + 0x3C0, asciiAnm, 0x62);

    return 0;

fail:
    Logger_AppendFormatted((char*)0x00474F70, (const char*)0x0046CB68);
    return 0xFFFFFFFF;
}

// ============================================================================
// 0x00401260 - GameThread Destroy
// game_thread = game thread pointer
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
void GameThread_Destroy(GameThread* gameThread) {
    uint32_t* gt = (uint32_t*)gameThread;
    *gt = (uint32_t)&PTR_LAB_0046cb14;

    // Release callback handle 1 (gt[3])
    void* h1 = (void*)gt[3];
    if (h1 != 0) {
        EnterCriticalSection(&DAT_00492274);
        DAT_0049231c++;
        Scheduler_UnregisterCallback(h1, DAT_00491be4);
        LeaveCriticalSection(&DAT_00492274);
        DAT_0049231c--;
    }

    // Release callback handle 2 (gt[4])
    void* h2 = (void*)gt[4];
    if (h2 != 0) {
        EnterCriticalSection(&DAT_00492274);
        DAT_0049231c++;
        Scheduler_UnregisterCallback(h2, DAT_00491be4);
        LeaveCriticalSection(&DAT_00492274);
        DAT_0049231c--;
    }

    // Release callback handle 3 (gt[0x226A])
    void* h3 = (void*)gt[0x226A];
    if (h3 != 0) {
        EnterCriticalSection(&DAT_00492274);
        DAT_0049231c++;
        Scheduler_UnregisterCallback(h3, DAT_00491be4);
        LeaveCriticalSection(&DAT_00492274);
        DAT_0049231c--;
    }

    // Free game state slots from manager
    uint32_t* slot;
    slot = (uint32_t*)((int)g_pGameStateManager + 0x3AD074);
    if (*slot != 0) { ResourceManager_DestroyResource(g_pGameStateManager, (void*)*slot); _free((void*)*slot); *slot = 0; }

    slot = (uint32_t*)((int)g_pGameStateManager + 0x3AD06C);
    if (*slot != 0) { ResourceManager_DestroyResource(g_pGameStateManager, (void*)*slot); _free((void*)*slot); *slot = 0; }

    slot = (uint32_t*)((int)g_pGameStateManager + 0x3AD078);
    if (*slot != 0) { ResourceManager_DestroyResource(g_pGameStateManager, (void*)*slot); _free((void*)*slot); *slot = 0; }

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
GameThread* GameThread_Create(void) {
    GameThread* gt = (GameThread*)operator_new(sizeof(GameThread));
    if (gt == 0) {
        return 0;
    }
    GameThread_Construct(gt);

    int result = GameThread_Init(gt);
    if (result != 0) {
        if (gt != 0) {
            GameThread_Destroy(gt);
            _free(gt);
        }
        return 0;
    }
    return gt;
}
