#ifndef TH10_OPTIONS_UPDATE_0042D920_HPP
#define TH10_OPTIONS_UPDATE_0042D920_HPP
#include "th10/game/title_main_menu_update_0042d420.hpp"

// The configuration inside the application state at 0x00491D4C, as the
// options screen edits it.
struct OptionsConfig_0042d920 {
    unsigned char reserved_00[0x1C];
    signed char music_volume;           // +0x1C (0x00491D68), 0..100
    signed char sound_volume;           // +0x1D (0x00491D69), 0..100
    unsigned char screen_mode;          // +0x1E (0x00491D6A): 0 window, 1 and 2 full screen
};

// A child animation reference seen as the handle 0x00449670 works on.
struct SpriteHandle_00449670 {
    unsigned int value;
    // 0x00449670: show a sprite of the animation's own resource.
    __declspec(noinline) void SelectSprite(int sprite);
};

// An animation and the list of its children, as the label search walks them.
struct LabelAnimation_0042d920 {
    unsigned int id;                    // +0x000
    unsigned char reserved_004[0x358];
    unsigned int flags_35c;             // +0x35C, bit 1 set = label visible
    unsigned char reserved_360[0x2A];
    short script;                       // +0x38A
};
struct LabelLink_0042d920 {
    LabelAnimation_0042d920* object;
    LabelLink_0042d920* next;
};
struct LabelParent_0042d920 {
    unsigned char reserved_000[0x10];
    LabelLink_0042d920 children;        // +0x010
};

// The room timer's frame pair seen by 0x00427C70.
struct FrameCounterPair {
    int previous;
    int current;
    // The frame changed and is a multiple of `interval`.
    int AtInterval(int interval);
};

// The application state block at 0x00491C00 with the two members the options
// screen works on.  The block is one object whose address is handed around,
// so a call that writes into one member makes the others be read again.
struct ApplicationState_0042d920 {
    unsigned char reserved_000[0x10];
    RecoveryLookupContext_0040bd80* animations; // +0x010 (0x00491C10)
    unsigned char reserved_014[0x14C - 0x14];
    OptionsConfig_0042d920 config;      // +0x14C (0x00491D4C)
    unsigned char reserved_16b[0x990 - 0x16B];
    SoundQueue sound;                   // +0x990 (0x00492590)
};
extern "C" {
extern ApplicationState_0042d920 application_state_00491c00;
// The volume bytes seen as the plain symbols at their own addresses.
extern unsigned char data_00491d68;
extern unsigned char data_00491d69;
}
#define data_00491d4c application_state_00491c00.config

// 0x0042E5A0: apply the volumes and rewrite the option labels.
__declspec(noinline) void __stdcall RefreshOptions_0042e5a0(RecoveryMusicRoom_00433ef0* room);

__declspec(noinline) int __stdcall TitleOptions_0042d920(RecoveryMusicRoom_00433ef0* room);
#endif
