#ifndef TH10_GAME_SIDE_PANEL_RELEASE_00414570_HPP
#define TH10_GAME_SIDE_PANEL_RELEASE_00414570_HPP

void __cdecl operator delete(void* memory);
extern "C" void __cdecl crt_free(void* memory);

// An owned animation slot of the side panel.
struct PanelSlot {
    // 0x004136C0: hand the slot's animation back to the manager.
    __declspec(noinline) void Release();
};

// A loaded animation file.
struct PanelResource2 {
    // 0x00447810: retire the file and everything it owns.
    __declspec(noinline) void Release();
};

// The animation manager's stage-owned file slot.
struct PanelAnimationManager2 {
    unsigned char reserved_000000[0x3AD0DC];
    PanelResource2* stage_resource;   // +0x3AD0DC
};

extern "C" PanelAnimationManager2* g_sprt_ctrl;
// The run's counters; the run flags sit at +0x60.
struct RunState3 {
    unsigned char reserved_00[0x60];
    unsigned int flags;                       // +0x60
};

extern "C" RunState3 g_globals;

// The side panel's stage-owned parts.
struct FrontStagePartsView {
    unsigned char reserved_0000[0x9E80];
    int stage_state;                          // +0x9E80
    unsigned char reserved_9e84[0x9EB8 - 0x9E84];
    PanelSlot* stage_slot;           // +0x9EB8
    void* stage_buffer;                       // +0x9EBC

    // 0x00414570: give back everything loaded for the stage.
    __declspec(noinline) void ReleaseStageParts();
};

#endif
