// The leaves only the spell card record screen 0x00431EE0 calls, unselected
// here: the card count of a difficulty 0x004088C0 and the stage unlock
// 0x0042C8C0 with their real bodies (the maintained forms are
// src/game/bullet/input_pattern_count.cpp and
// src/game/title/game_progress_unlock_all_stages_0042c8c0.cpp).
#include "th10/game/spell_record_update_00431ee0.hpp"

extern "C" const signed char g_spell_difficulty[110];

#pragma code_seg(".text$004088c0_fn")
__declspec(noinline) int __stdcall SpellCards_CountOfDifficulty_004088c0(int difficulty) {
    int count = 0;
    for (int spell = 0; spell < 110; ++spell) {
        if (g_spell_difficulty[spell] == difficulty)
            ++count;
    }
    return count;
}
#pragma code_seg()

#define code_seg(name) code_seg(".text$0042c8c0_fn")
#include "../../../../src/game/title/game_progress_unlock_all_stages_0042c8c0.cpp"
#undef code_seg
