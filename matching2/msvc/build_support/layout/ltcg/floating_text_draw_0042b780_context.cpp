// Compiler context only; never selected as recovered game code. The batch
// flush is an ABI anchor for its ESI receiver.
#include "../../../src/core/sprtfunc/anm_batch_flush.cpp"
#include "../../../src/game/smollscore/smoll_score_draw.cpp"

extern "C" void __cdecl crt_free_startup(void* memory);

// Stand-in for 0x00443080, whose real body is recovered in the render batch
// cluster: it keeps the entity live across calls so the entity arrives in ESI,
// and it lets the render state's address escape, as the real draw does, so the
// caller cannot assume the device and the state never overlap.
#pragma code_seg(".text$08entity")
extern "C" __declspec(noinline) int __stdcall FloatingText_DrawEntity(SprtCtrlBatchView* manager, FloatingTextSprite* entity) {
    int a = (int)entity->x;
    crt_free_startup(entity);
    a += (int)entity->y;
    crt_free_startup((void*)&manager);
    crt_free_startup(&g_application);
    return a + (int)entity->sprite_width;
}
#pragma code_seg()

// Stand-in for the item collector 0x0041AFD0, the spawner's only caller: it
// keeps the position live in EDI and reloads the pool for every call, which is
// what selects the spawner's EAX/ESI/EDI argument registers.
extern "C" SmollScoreDrawView* g_smoll_score;
#pragma code_seg(".text$04zcaller")
__declspec(noinline) int __stdcall FloatingTextSpawnCaller(FloatingTextPosition* position, int kind) {
    int score = position->x > 0 ? 10 : 20;
    switch (kind) {
    case 0:
        crt_free_startup(position);
        g_smoll_score->Spawn(-1, position, 0xFFFFFF40);
        crt_free_startup(position);
        break;
    case 1:
        g_smoll_score->Spawn(score / 2, position, 0xFFFF4040);
        crt_free_startup(position);
        break;
    default:
        g_smoll_score->Spawn(score, position, 0xFF00FF00);
        crt_free_startup(&score);
        break;
    }
    crt_free_startup(position);
    return score;
}
#pragma code_seg()

#pragma code_seg(".text$04context")
void* __stdcall FloatingTextDrawCompilerContext(void** caller) {
    *caller = reinterpret_cast<void*>(FloatingTextSpawnCaller);
    return reinterpret_cast<void*>(SmollScore_DrawTask2);
}
#pragma code_seg()
