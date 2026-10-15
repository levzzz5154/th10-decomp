#ifndef TH10_KEY_CONFIG_UPDATE_0042F540_HPP
#define TH10_KEY_CONFIG_UPDATE_0042F540_HPP
#include "th10/game/ending_screen_0042d300.hpp"

// The title screen object seen by the key configuration helpers: the five
// bindings being edited (shot, bomb, focus, pause, skip).
struct TitleKeyConfigView {
    unsigned char reserved_0000[0x59CC];
    short bindings_59cc[5];
};

// The pad bindings of the configuration (18 bytes at 0x00474E88, and their
// copy inside the application state at 0x00491D4C).
struct KeyBindings {
    short keys[4];          // +0x00
    short reserved_08[4];
    short skip;             // +0x10
};
typedef char KeyBindingsSize[sizeof(KeyBindings) == 18 ? 1 : -1];

// The key state at 0x00474E30.
struct KeyState {
    unsigned short raw;            // +0x00
    unsigned char reserved_02[2];
    unsigned short held;           // +0x04
    unsigned short pressed;        // +0x06

    // 0x0040ACE0, inlined here: a key of the mask was pressed or is repeating.
    int Active(unsigned short mask) { return (mask & pressed) != 0 || (mask & held) != 0; }
};

struct AnimationLookupContext;
struct AnimationScriptId { unsigned int value; };

extern "C" {
extern KeyBindings g_key_bindings_current;
extern KeyBindings g_key_bindings;
extern KeyState g_input_keys_raw;
__declspec(noinline) void __stdcall RefreshTitleKeyConfigView(TitleKeyConfigView* state);
__declspec(noinline) void __stdcall KeyConfigReassignSlot_00430250(
    TitleKeyConfigView* state, int slot, int key);
unsigned char* __fastcall Input_PollJoystickButtons_0044a4e0(int padIndex);
}
__declspec(noinline) void __fastcall AnimationManager_SetStopFrameAndRun(
    unsigned short frame, AnimationLookupContext* context, AnimationScriptId id);

__declspec(noinline) int __stdcall TitleMenuFlow(Title* room);
#endif
