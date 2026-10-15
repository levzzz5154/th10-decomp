#include <new>
#include "th10/game/score_archive_manager_0042ae60.hpp"
extern "C" ScoreArchiveManager *g_score;
#pragma code_seg(".text$03b")
__declspec(noinline) void __stdcall ScoreManager_Create_0042af20() {
    g_score = new ScoreArchiveManager;
}
#pragma code_seg()
