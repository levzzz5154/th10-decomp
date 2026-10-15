#ifndef TH10_GAME_SIDE_PANEL_RELEASE_00414570_HPP
#define TH10_GAME_SIDE_PANEL_RELEASE_00414570_HPP

void __cdecl operator delete(void* memory);
extern "C" void __cdecl entry_free_00452422(void* memory);

// An owned animation slot of the side panel.
struct PanelSlot_004136c0 {
    // 0x004136C0: hand the slot's animation back to the manager.
    __declspec(noinline) void Release();
};

// A loaded animation file.
struct PanelResource_00447810 {
    // 0x00447810: retire the file and everything it owns.
    __declspec(noinline) void Release();
};

// The animation manager's stage-owned file slot.
struct PanelAnimationManager_00414570 {
    unsigned char reserved_000000[0x3AD0DC];
    PanelResource_00447810* stage_resource;   // +0x3AD0DC
};

extern "C" PanelAnimationManager_00414570* g_sprt_ctrl;
// The run's counters; the run flags sit at +0x60.
struct RunState_00414570 {
    unsigned char reserved_00[0x60];
    unsigned int flags;                       // +0x60
};

extern "C" RunState_00414570 data_00474c40;

// The side panel's stage-owned parts.
struct FrontStagePartsView {
    unsigned char reserved_0000[0x9E80];
    int stage_state;                          // +0x9E80
    unsigned char reserved_9e84[0x9EB8 - 0x9E84];
    PanelSlot_004136c0* stage_slot;           // +0x9EB8
    void* stage_buffer;                       // +0x9EBC

    // 0x00414570: give back everything loaded for the stage.
    __declspec(noinline) void ReleaseStageParts();
};

#endif
