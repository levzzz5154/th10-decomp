#ifndef TH10_SPELL_RECORD_UPDATE_00431EE0_HPP
#define TH10_SPELL_RECORD_UPDATE_00431EE0_HPP
#include "th10/game/practice_stage_select_update_00430ff0.hpp"

// The title screen object as the spell card record screen uses it: the shot
// type cursor is the room's own, followed by the difficulty and the page.
struct TitleSpellRecordView {
    unsigned char reserved_0000[0xFC];
    MenuCursor difficulty;              // +0x0FC
    MenuCursor page;                    // +0x1D4: 0 is the summary, 1.. the card pages
    unsigned char reserved_02ac[0x5D4 - 0x2AC];
    RecoveryHandle_0040bd80 lines[10];  // +0x5D4: the ten text lines of a page

};
typedef char SpellRecordRoomPage_00431ee0[offsetof(TitleSpellRecordView, page) == 0x1D4 ? 1 : -1];
typedef char SpellRecordRoomLines_00431ee0[offsetof(TitleSpellRecordView, lines) == 0x5D4 ? 1 : -1];

// The room as the page builder 0x00432690 receives it; its own view of the
// fields is in th10/game/title_menu_draw.hpp.
struct TitleDrawView {
    // Fill the ten lines with the cards of the selected page.
    __declspec(noinline) int BuildSpellList();
};

struct GameProgress_0042c8c0;

extern "C" {
extern unsigned char data_00497e90[256];    // keyboard snapshot of this frame
extern unsigned char data_00497d90[256];    // keyboard snapshot of the frame before
extern unsigned char data_004979a8[256];    // keys that went down this frame
extern unsigned int data_004979a4;          // keys of the unlock sequence entered so far
extern int data_004979a0;                   // frames since the last key of the sequence
extern const int data_0046ef10[22];         // the unlock sequence, as scan codes
}

// 0x004088C0: the number of spell cards of a difficulty.
__declspec(noinline) int __stdcall SpellCards_CountOfDifficulty_004088c0(int difficulty);
// 0x0042C8C0: mark every stage of every character and difficulty as reached.
__declspec(noinline) void __stdcall UnlockAllStages_0042c8c0(GameProgress_0042c8c0* progress);

__declspec(noinline) int __stdcall TitleMode11_00431ee0(Title* room);
#endif
