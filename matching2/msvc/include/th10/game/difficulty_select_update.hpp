#ifndef TH10_DIFFICULTY_SELECT_UPDATE_00430320_HPP
#define TH10_DIFFICULTY_SELECT_UPDATE_00430320_HPP
#include "th10/game/title_opening_screen.hpp"

// The key state at 0x00474E30.
struct KeyRepeatState {
    unsigned char  unknown_00[4];
    unsigned short pressed;     // +0x04
    unsigned short unknown_06;  // +0x06
    // 0x0040ACE0: a key of the mask was pressed or is repeating.  Left to
    // the compiler: the difficulty selection calls it, the character
    // selection inlines it.
    int InputMaskActive(unsigned short mask);
};

// A reference to a child animation, as 0x004497D0 returns it.
struct AnimationRef2 {
    int value;
    AnimationRef2(int value) : value(value) {}
};
// An animation slot seen as the handle 0x004497D0 searches.
struct ChildLookupAnmHandle {
    AnimationScriptId id;
    AnimationRef2 FindChildRef(int script_id);
};
// A child reference seen as the handle 0x00449470 works on.
struct StopFrameAnmHandle {
    unsigned int value;
    __declspec(noinline) void SetStopFrame(unsigned short frame);
};

// The title screen object past the music-room view: the difficulty to go
// back to when the selection is cancelled on a fixed-difficulty entry.
struct TitleDifficultyView {
    unsigned char reserved_0000[0x58F0];
    int saved_difficulty;
};

// The room's animation slots seen by 0x0042C750, which restarts the script of
// one slot at frame 3.
struct TitleAnimationSlotView {
    unsigned char reserved_000[0x2C4];
    AnimationScriptId slots[195];
    __declspec(noinline) void RestartSlot(int slot);
    // 0x0042C730: the same at frame 2.
    __declspec(noinline) void StopSlot(int slot);
};

extern "C" {
extern KeyRepeatState g_input_keys_raw;
extern int g_globals_difficulty;               // difficulty (4 and above: fixed entry)
extern int g_globals_character;               // character
extern AsciiManagerSpinnerView* g_ascii_manager;
}

// 0x00449250: set the stop frame of an animation and run it once.
void __fastcall AnimationManager_SetStopFrameAndRun(
    unsigned short frame, AnmLookupContext* context, AnimationScriptId id);
// 0x0040AD20: store the requested value in a counter, clamped to its bound.
// Never expanded in the image, not even where the inliner's own score would
// accept it (0x00431602); the one inline clamp, in 0x00430FF0, has another
// shape.
__declspec(noinline) unsigned int __fastcall UpdateBoundedCounter(unsigned int requested, unsigned int* counter);
// 0x00448D00.
__declspec(noinline) void** __stdcall AnimationManager_CreatePrimaryBack(
    void* resource, void** handle, int script, int layer);

// The four selection screens share this backdrop. Keep the creator's output
// slot in the caller: a helper-local slot changes the difficulty screen's frame.
static __forceinline void EnsureTitleMenuBackdrop(Title* room, void*& handle) {
    enum { BackdropSlot = 94, BackdropScript = 8, MenuLayer = 15 };
    if (reinterpret_cast<AnmLookup*>(g_sprt_ctrl)->Find(
            reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl),
            room->animation_slots[BackdropSlot]) != 0)
        return;

    Title_InstallAnimationSlot(room, BackdropSlot);
    void* resource = g_ascii_manager->animation_resource;
    void** result = AnimationManager_CreatePrimaryBack(resource, &handle, BackdropScript, MenuLayer);
    room->fallback_handle.value = reinterpret_cast<unsigned int>(*result);
}

__declspec(noinline) int __stdcall TitleMode6(Title* room);
#endif
