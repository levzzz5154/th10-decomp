#ifndef TH10_GAME_SIDE_PANEL_CONTENTS_RELEASE_00414370_HPP
#define TH10_GAME_SIDE_PANEL_CONTENTS_RELEASE_00414370_HPP
#include <stddef.h>

void __cdecl operator delete(void* memory);
extern "C" void __cdecl entry_free_00452422(void* memory);

// An owned animation slot of the side panel.
struct PanelSlot_00414370 {
    // 0x004136C0: hand the slot's animation back to the manager.
    __declspec(noinline) void Release();
};

// A loaded animation file.
struct PanelResource_00414370 {
    // 0x00447810: retire the file and everything it owns.
    __declspec(noinline) void Release();
};

struct PanelAnimationId_00414370 {
    int value;
};

// A node of the animation manager's lists; `object` is the animation itself,
// which starts with its id.
struct PanelAnimationEntry_00414370 {
    PanelAnimationEntry_00414370* object;
    PanelAnimationEntry_00414370* next;
    unsigned char reserved_08[0x0C];
    PanelAnimationEntry_00414370* children;
    int children_flagged;
    unsigned char reserved_1c[0x308 - 0x1C];
    void* resource;                                 // +0x308
    unsigned char reserved_30c[0x35C - 0x30C];
    unsigned int flags;                             // +0x35C
};

enum { kPanelAnimationMarkedForRemoval_00414370 = 0x04000000 };

// The animation manager, as far as the side panel reaches it.
struct PanelAnimationManager_00414370 {
    unsigned char reserved_000000[0x3AD0DC];
    PanelResource_00414370* stage_resource;         // +0x3AD0DC
    unsigned char reserved_3ad0e0[0x72DAD4 - 0x3AD0E0];
    PanelAnimationEntry_00414370* primary;          // +0x72DAD4
    int reserved_72dad8;
    PanelAnimationEntry_00414370* secondary;        // +0x72DADC

    // 0x004493E0: let every animation that plays from this file be removed.
    __declspec(noinline) void MarkResourceForRemoval(void* resource);
};

// 0x004491C0 / 0x004492A0: find an animation by id; let it and its children
// be removed.
__declspec(noinline) PanelAnimationEntry_00414370* __fastcall PanelAnimation_Find_004491c0(
    PanelAnimationManager_00414370* manager, PanelAnimationId_00414370 id);
__declspec(noinline) PanelAnimationEntry_00414370* __fastcall PanelAnimation_SetFlag_004492a0(
    PanelAnimationManager_00414370* manager, PanelAnimationId_00414370 id);

// The same two routines, expanded in place by the loop over the effects.
__forceinline PanelAnimationEntry_00414370* PanelAnimation_FindInPlace(PanelAnimationManager_00414370* manager,
                                                                      PanelAnimationId_00414370 id) {
    PanelAnimationEntry_00414370* node;
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
__forceinline void PanelAnimation_SetFlagInPlace(PanelAnimationManager_00414370* manager,
                                                 PanelAnimationId_00414370 id) {
    PanelAnimationEntry_00414370* entry = PanelAnimation_FindInPlace(manager, id);
    if (entry) {
        entry->flags |= kPanelAnimationMarkedForRemoval_00414370;
        if (!entry->children_flagged)
            for (entry = entry->children; entry != 0; entry = entry->next)
                entry->object->flags |= kPanelAnimationMarkedForRemoval_00414370;
    }
}

// An animation the panel owns, named by its id.
struct PanelAnimation_00414370 {
    PanelAnimationId_00414370 id;

    // Let the animation manager dispose of the animation and forget it.
    void Release(PanelAnimationManager_00414370* manager) {
        PanelAnimation_SetFlag_004492a0(manager, id);
        id.value = 0;
    }
    __forceinline void ReleaseInPlace(PanelAnimationManager_00414370* manager) {
        PanelAnimation_SetFlagInPlace(manager, id);
        id.value = 0;
    }
};

struct PanelTask_00414370 {
    unsigned int reserved_00;
    unsigned int flags;                             // +0x04; 2 = enabled
};

// The run's counters; the run flags sit at +0x60.
struct RunState_00414370 {
    unsigned char reserved_00[0x60];
    unsigned int flags;                             // +0x60 (0x00474CA0)
};

// The side panel (0x9ED0 bytes, published at 0x0047770C), as far as its
// contents release reaches it.
struct SidePanel_00414370 {
    unsigned int flags;
    unsigned int reserved_0004;
    PanelTask_00414370* update_task;                // +0x0008
    unsigned char reserved_000c[0x9DF4 - 0x0C];
    PanelAnimation_00414370 effects[8];             // +0x9DF4
    PanelAnimation_00414370 frame;                  // +0x9E14
    PanelAnimation_00414370 caption;                // +0x9E18
    unsigned char reserved_9e1c[8];
    PanelAnimation_00414370 gauge;                  // +0x9E24
    int counters[10];                               // +0x9E28
    unsigned char reserved_9e50[0x9E80 - 0x9E50];
    void* stage_file;                               // +0x9E80
    unsigned char reserved_9e84[0x9E90 - 0x9E84];
    int stage_ready;                                // +0x9E90
    unsigned char reserved_9e94[0x9EB8 - 0x9E94];
    PanelSlot_00414370* stage_slot;                 // +0x9EB8
    void* stage_buffer;                             // +0x9EBC
};
typedef char SidePanelEffects_00414370[offsetof(SidePanel_00414370, effects) == 0x9DF4 ? 1 : -1];
typedef char SidePanelCounters_00414370[offsetof(SidePanel_00414370, counters) == 0x9E28 ? 1 : -1];
typedef char SidePanelStageFile_00414370[offsetof(SidePanel_00414370, stage_file) == 0x9E80 ? 1 : -1];
typedef char SidePanelStageReady_00414370[offsetof(SidePanel_00414370, stage_ready) == 0x9E90 ? 1 : -1];
typedef char SidePanelStageSlot_00414370[offsetof(SidePanel_00414370, stage_slot) == 0x9EB8 ? 1 : -1];

extern "C" {
extern PanelAnimationManager_00414370* g_sprt_ctrl;
extern RunState_00414370 data_00474c40;
extern void* data_00491be8;         // the stage buffer kept for the next stage
}

// 0x00414370: release everything the panel's stage holds.
void __stdcall SidePanel_ReleaseContents_00414370(SidePanel_00414370* panel);

#endif
