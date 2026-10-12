#ifndef TH10_UI_FINAL_RUNTIME_00433EF0_HPP
#define TH10_UI_FINAL_RUNTIME_00433EF0_HPP
#include "th10/game/replay_save_update_00433570.hpp"
#include "th10/game/replay_file_load_0042a200.hpp"

// The title screen object as the music room uses it: the track list parsed
// from musiccmt.txt, its eight preview lines and the scroll origin.
struct MusicRoom_00433ef0 {
    unsigned char reserved_0000[0x664];
    RecoveryHandle_0040bd80 preview_handles[8];  // +0x664
    unsigned int reserved_684;
    int parsed_track_count;                      // +0x688
    int preview_cursor;                          // +0x68C: title reveal cursor
    int displayed_track;                         // +0x690
    int preview_armed;                           // +0x694: warning acknowledged
    char titles[32][64];                         // +0x698
    char comments[32][66];                       // +0xE98
    char preview_lines[32][8][66];               // +0x16D8
    int scroll_origin;                           // +0x58D8
    unsigned char reserved_58dc[0x5AAC - 0x58DC];
    char* file_buffer;                           // +0x5AAC
};
typedef char MusicRoomPreviewHandles_00433ef0[offsetof(MusicRoom_00433ef0, preview_handles) == 0x664 ? 1 : -1];
typedef char MusicRoomTitles_00433ef0[offsetof(MusicRoom_00433ef0, titles) == 0x698 ? 1 : -1];
typedef char MusicRoomComments_00433ef0[offsetof(MusicRoom_00433ef0, comments) == 0xE98 ? 1 : -1];
typedef char MusicRoomLines_00433ef0[offsetof(MusicRoom_00433ef0, preview_lines) == 0x16D8 ? 1 : -1];

// 0x00434A20, 0x004349E0: the stage-text line walkers the parser shares.
// Declared in their owning sources; the linker resolves the calls.

// 0x0044B360: read a file of the archive into a fresh buffer, size first.
// Declared in th10/game/replay_file_load_0042a200.hpp as Archive_LoadFile.

// 0x00434A80: (re)initialise one stage-text sprite record; the animation
// objects double as text records (its position vector lives at +0x334).
struct StageTextVector_00434a80 {
    float x, y, z;
};
struct StageText_00434a80 {
    __declspec(noinline) void Initialize(const StageTextVector_00434a80* base,
                                         const StageTextVector_00434a80* position,
                                         int mode, unsigned char flag);
};

// 0x00433EF0: the music room of the title menu, reached from the main menu.
__declspec(noinline) int __stdcall TitleMusicRoom_00433ef0(RecoveryMusicRoom_00433ef0* room);
#endif
