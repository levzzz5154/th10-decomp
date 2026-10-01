// 0x00431410: draw the six stage rows of the title's practice menu.
//
// Each row shows the stage name and, once the stage has been reached with the
// selected character and difficulty, its best practice score. The selected
// row is highlighted and blinks while the choice is being confirmed.
//
// Native LTCG passes the menu in EDI and the text position to the formatter
// in EBX.
#include "th10/game/game_thread_queue_native.hpp"

struct PracticeRecord_00431410 {
    int best_score;                      // +0x00
    unsigned char pad_04;
    unsigned char unlocked;              // +0x05
    unsigned char pad_06[2];
};

struct ScoreCharacter_00431410 {
    unsigned char pad_000[0x4DC];
    PracticeRecord_00431410 practice[1]; // +0x4DC: six per difficulty, stage first
    unsigned char pad_4E4[0x437C - 0x4E4];
};

// Part of the global game state; the title menus write it through pointers.
struct GameSelection_00431410 {
    int shot_type;                       // 0x00474C68
    int character;                       // 0x00474C6C
    int unknown_08;
    int difficulty;                      // 0x00474C74
};

struct TitleMenu_00431410 {
    unsigned char pad_000[0x20];
    int phase;                           // +0x020
    int cursor;                          // +0x024
    unsigned char pad_028[0x2B4 - 0x28];
    int phase_frames;                    // +0x2B4

    __declspec(noinline) int DrawPracticeRows();
};

extern "C" {
extern GameThread_00401530* data_004776e0;
extern GameSelection_00431410 data_00474c68;
extern ScoreCharacter_00431410* data_0047783c;
extern const char* data_0047471c[];      // "test", "Stage 1" .. "Stage 6", "Extra"
}

#pragma code_seg(".text$05rows")
int TitleMenu_00431410::DrawPracticeRows() {
    if (phase >= 2 && phase <= 3) {
        data_004776e0->current_64 = 1;
        Vec3_00401530 position = {80.0f, 80.0f, 0.0f};
        if (phase_frames >= 10 || phase == 3) {
            position.y = 216.0f;
            position.x = 168.0f;
            if (data_00474c68.shot_type != 0)
                position.x = 296.0f;
            for (int stage = 1; stage < 7; ++stage) {
                if (cursor == stage - 1) {
                    if (data_0047783c[data_00474c68.character + data_00474c68.shot_type * 3]
                            .practice[stage + data_00474c68.difficulty * 6].unlocked) {
                        if (phase == 3 && phase_frames % 4 >= 2)
                            data_004776e0->current_4c = 0xFF000000;
                        else
                            data_004776e0->current_4c = 0xFFFFFF00;
                    } else {
                        data_004776e0->current_4c = 0xFFDFDFDF;
                    }
                } else {
                    data_004776e0->current_4c = 0xFF808080;
                }
                if (!data_0047783c[data_00474c68.character + data_00474c68.shot_type * 3]
                         .practice[stage + data_00474c68.difficulty * 6].unlocked)
                    AppendFormatted_00401630(data_004776e0, &position, "%s  ---------",
                                             data_0047471c[stage]);
                else
                    AppendFormatted_00401630(
                        data_004776e0, &position, "%s  %.8d0", data_0047471c[stage],
                        data_0047783c[data_00474c68.character + data_00474c68.shot_type * 3]
                            .practice[stage + data_00474c68.difficulty * 6].best_score);
                position.y += 18.0f;
            }
        }
        data_004776e0->current_4c = 0xFFFFFFFF;
        data_004776e0->current_64 = 0;
    }
    return 1;
}
#pragma code_seg()
