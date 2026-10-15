// 0x0042C8C0: mark every stage of every character and difficulty as reached.
#include <string.h>
#pragma pack(push, 1)
struct StageRecord {
    unsigned char reached;
    unsigned char unknown[7];
};
struct CharacterProgress {
    StageRecord stages[4][6];
    unsigned char unknown[0x437C - sizeof(StageRecord) * 4 * 6];
};
struct GameProgress_0042c8c0 {
    unsigned char unknown_00000[0x4E9];
    CharacterProgress characters[6];
    unsigned char unknown_1a1d1[0x1D882 - 0x4E9 - sizeof(CharacterProgress) * 6];
    unsigned char unlocked[4][4];
};
#pragma pack(pop)

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall UnlockAllStages_0042c8c0(GameProgress_0042c8c0* progress) {
    for (int row = 0; row < 4; ++row) memset(progress->unlocked[row], 1, sizeof(progress->unlocked[row]));
    for (int character = 0; character < 6; ++character) {
        for (int difficulty = 0; difficulty < 4; ++difficulty) {
            for (int stage = 0; stage < 6; ++stage) {
                progress->characters[character].stages[difficulty][stage].reached = 1;
            }
        }
    }
}
#pragma code_seg()
