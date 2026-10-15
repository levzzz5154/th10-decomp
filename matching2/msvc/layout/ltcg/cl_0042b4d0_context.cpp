// Compiler context only; never selected as recovered game code.
#include "../../src/game/smollscore/smoll_score_initialize.cpp"

#pragma code_seg(".text$00h_init")
#include "../../src/game/entity_initialize_00401de0.cpp"
#pragma code_seg()

#include "scheduler_register_anchors.cpp"

void* __cdecl operator new(unsigned int size);

struct SmollScore;
extern "C" SmollScore* __cdecl SmollScore_Create();

#pragma code_seg(".text$30context")
int __stdcall SmollScoreContext_0042b4d0(unsigned int size, SchedulerTask* task) {
    // Keeps the full registration anchors in the link.
    int result = Scheduler_RegisterPrimary(data_00491be4, task, size);
    SmollScoreView* pool = static_cast<SmollScoreView*>(operator new(size));
    if (pool->Initialize())
        return result;
    return (int)SmollScore_Create();
}
#pragma code_seg()
