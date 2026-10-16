#include <new>
#include "th10/game/score_archive_manager.hpp"
extern "C" ScoreArchiveManager *g_score;
#pragma code_seg(".text$03b")
__declspec(noinline) void __stdcall ScoreManager_Create2() {
    g_score = new ScoreArchiveManager;
}
#pragma code_seg()
