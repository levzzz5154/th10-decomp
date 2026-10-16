#ifndef TH10_GAME_SIDE_PANEL_CONTENTS_RELEASE_00414370_HPP
#define TH10_GAME_SIDE_PANEL_CONTENTS_RELEASE_00414370_HPP
#include <stddef.h>

void __cdecl operator delete(void* memory);
extern "C" void __cdecl crt_free(void* memory);

// An owned animation slot of the side panel.
struct PanelSlot2 {
    // 0x004136C0: hand the slot's animation back to the manager.
    __declspec(noinline) void Release();
};

// A loaded animation file.
struct PanelResource {
    // 0x00447810: retire the file and everything it owns.
    __declspec(noinline) void Release();
};

struct PanelAnimationId {
    int value;
};

// A node of the animation manager's lists; `object` is the animation itself,
// which starts with its id.
struct PanelAnimationEntry {
    PanelAnimationEntry* object;
    PanelAnimationEntry* next;
    unsigned char reserved_08[0x0C];
    PanelAnimationEntry* children;
    int children_flagged;
    unsigned char reserved_1c[0x308 - 0x1C];
    void* resource;                                 // +0x308
    unsigned char reserved_30c[0x35C - 0x30C];
    unsigned int flags;                             // +0x35C
};

enum { kPanelAnimationMarkedForRemoval = 0x04000000 };

// The animation manager, as far as the side panel reaches it.
struct PanelAnimationManager {
    unsigned char reserved_000000[0x3AD0DC];
    PanelResource* stage_resource;         // +0x3AD0DC
    unsigned char reserved_3ad0e0[0x72DAD4 - 0x3AD0E0];
    PanelAnimationEntry* primary;          // +0x72DAD4
    int reserved_72dad8;
    PanelAnimationEntry* secondary;        // +0x72DADC

    // 0x004493E0: let every animation that plays from this file be removed.
    __declspec(noinline) void MarkResourceForRemoval(void* resource);
};

// 0x004491C0 / 0x004492A0: find an animation by id; let it and its children
// be removed.
__declspec(noinline) PanelAnimationEntry* __fastcall PanelAnimation_Find2(
    PanelAnimationManager* manager, PanelAnimationId id);
__declspec(noinline) PanelAnimationEntry* __fastcall PanelAnimation_SetFlag2(
    PanelAnimationManager* manager, PanelAnimationId id);

// The same two routines, expanded in place by the loop over the effects.
__forceinline PanelAnimationEntry* PanelAnimation_FindInPlace(PanelAnimationManager* manager,
                                                                      PanelAnimationId id) {
    PanelAnimationEntry* node;
    int* object;
    if (!id.value)
        return 0;
    for (node = manager->primary; node != 0; node = node->next) {
        object = (int*)node->object;
        if (*object == id.value)
            return node->object;
    }
    for (node = manager->secondary; node != 0; node = node->next) {
        object = (int*)node->object;
        if (*object == id.value)
            return node->object;
    }
    return 0;
}
__forceinline void PanelAnimation_SetFlagInPlace(PanelAnimationManager* manager,
                                                 PanelAnimationId id) {
    PanelAnimationEntry* entry = PanelAnimation_FindInPlace(manager, id);
    if (entry) {
        entry->flags |= kPanelAnimationMarkedForRemoval;
        if (!entry->children_flagged)
            for (entry = entry->children; entry != 0; entry = entry->next)
                entry->object->flags |= kPanelAnimationMarkedForRemoval;
    }
}

// An animation the panel owns, named by its id.
struct PanelAnimation {
    PanelAnimationId id;

    // Let the animation manager dispose of the animation and forget it.
    void Release(PanelAnimationManager* manager) {
        PanelAnimation_SetFlag2(manager, id);
        id.value = 0;
    }
    __forceinline void ReleaseInPlace(PanelAnimationManager* manager) {
        PanelAnimation_SetFlagInPlace(manager, id);
        id.value = 0;
    }
};

struct PanelTask {
    unsigned int reserved_00;
    unsigned int flags;                             // +0x04; 2 = enabled
};

// The run's counters; the run flags sit at +0x60.
struct RunState2 {
    unsigned char reserved_00[0x60];
    unsigned int flags;                             // +0x60 (0x00474CA0)
};

// The side panel (0x9ED0 bytes, published at 0x0047770C), as far as its
// contents release reaches it.
struct SidePanel {
    unsigned int flags;
    unsigned int reserved_0004;
    PanelTask* update_task;                // +0x0008
    unsigned char reserved_000c[0x9DF4 - 0x0C];
    PanelAnimation effects[8];             // +0x9DF4
    PanelAnimation frame;                  // +0x9E14
    PanelAnimation caption;                // +0x9E18
    unsigned char reserved_9e1c[8];
    PanelAnimation gauge;                  // +0x9E24
    int counters[10];                               // +0x9E28
    unsigned char reserved_9e50[0x9E80 - 0x9E50];
    void* stage_file;                               // +0x9E80
    unsigned char reserved_9e84[0x9E90 - 0x9E84];
    int stage_ready;                                // +0x9E90
    unsigned char reserved_9e94[0x9EB8 - 0x9E94];
    PanelSlot2* stage_slot;                 // +0x9EB8
    void* stage_buffer;                             // +0x9EBC
};
typedef char SidePanelEffects[offsetof(SidePanel, effects) == 0x9DF4 ? 1 : -1];
typedef char SidePanelCounters[offsetof(SidePanel, counters) == 0x9E28 ? 1 : -1];
typedef char SidePanelStageFile[offsetof(SidePanel, stage_file) == 0x9E80 ? 1 : -1];
typedef char SidePanelStageReady[offsetof(SidePanel, stage_ready) == 0x9E90 ? 1 : -1];
typedef char SidePanelStageSlot[offsetof(SidePanel, stage_slot) == 0x9EB8 ? 1 : -1];

extern "C" {
extern PanelAnimationManager* g_sprt_ctrl;
extern RunState2 g_globals;
extern void* g_next_stage_buffer;         // the stage buffer kept for the next stage
}

// 0x00414370: release everything the panel's stage holds.
void __stdcall SidePanel_ReleaseContents2(SidePanel* panel);

#endif
