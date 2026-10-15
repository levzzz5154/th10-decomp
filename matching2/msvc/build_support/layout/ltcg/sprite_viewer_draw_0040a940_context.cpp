// Compiler context only; never selected as recovered game code. The queue
// writer and marked-text formatter are ABI anchors for the ESI/EBX arguments.
#include "../../../src/game/ascii/add_string.cpp"
#include "../../../src/game/ascii/add_formatted_marked.cpp"
#include "../../../src/game/eclview/ecl_view_draw.cpp"

extern "C" void __cdecl crt_free_startup(void* memory);

// Stand-in for 0x00443080, whose real body is recovered in the render batch
// cluster: it keeps the entity live across calls so the entity arrives in ESI.
#pragma code_seg(".text$08entity")
extern "C" __declspec(noinline) int __stdcall EclView_DrawEntity(SprtCtrlBatchView* manager, EclViewSprite* entity) {
    int a = (int)entity->base_position.x;
    crt_free_startup(entity);
    a += (int)entity->base_position.y;
    crt_free_startup((void*)&manager);
    return a + (int)entity->base_position.z;
}
#pragma code_seg()

#pragma code_seg(".text$07context")
void* __stdcall EclViewDrawCompilerContext() {
    return reinterpret_cast<void*>(EclView_DrawTask_0040abf0);
}
#pragma code_seg()
