// Compiler context only; never selected as recovered game code. The batch
// flush is an ABI anchor for its ESI receiver.
#include "../../src/core/sprtfunc/anm_batch_flush.cpp"
#include "../../src/game/smollscore/smoll_score_draw.cpp"

extern "C" void __cdecl entry_free_004524a1(void* memory);

// Stand-in for 0x00443080, whose real body is recovered in the render batch
// cluster: it keeps the entity live across calls so the entity arrives in ESI,
// and it lets the render state's address escape, as the real draw does, so the
// caller cannot assume the device and the state never overlap.
#pragma code_seg(".text$08entity")
extern "C" __declspec(noinline) int __stdcall FloatingText_DrawEntity_00443080(AnimationManager_00442F50* manager, FloatingTextSprite_0042b780* entity) {
    int a = (int)entity->x;
    entry_free_004524a1(entity);
    a += (int)entity->y;
    entry_free_004524a1((void*)&manager);
    entry_free_004524a1(&data_00491c28);
    return a + (int)entity->sprite_width;
}
#pragma code_seg()

// Stand-in for the item collector 0x0041AFD0, the spawner's only caller: it
// keeps the position live in EDI and reloads the pool for every call, which is
// what selects the spawner's EAX/ESI/EDI argument registers.
extern "C" SmollScoreDrawView* g_smoll_score;
#pragma code_seg(".text$04zcaller")
__declspec(noinline) int __stdcall FloatingTextSpawnCaller(FloatingTextPosition_0042b780* position, int kind) {
    int score = position->x > 0 ? 10 : 20;
    switch (kind) {
    case 0:
        entry_free_004524a1(position);
        g_smoll_score->Spawn(-1, position, 0xFFFFFF40);
        entry_free_004524a1(position);
        break;
    case 1:
        g_smoll_score->Spawn(score / 2, position, 0xFFFF4040);
        entry_free_004524a1(position);
        break;
    default:
        g_smoll_score->Spawn(score, position, 0xFF00FF00);
        entry_free_004524a1(&score);
        break;
    }
    entry_free_004524a1(position);
    return score;
}
#pragma code_seg()

#pragma code_seg(".text$04context")
void* __stdcall FloatingTextDrawCompilerContext(void** caller) {
    *caller = reinterpret_cast<void*>(FloatingTextSpawnCaller);
    return reinterpret_cast<void*>(SmollScore_DrawTask_0042b9b0);
}
#pragma code_seg()
