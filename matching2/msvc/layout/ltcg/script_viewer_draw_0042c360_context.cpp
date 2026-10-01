// Compiler context only; never selected as recovered game code. The queue
// writer and marked-text formatter are ABI anchors for the ESI/EBX arguments.
#include "../../src/game/game_thread_queue.cpp"
#include "../../src/game/game_thread_append_formatted_marked_retail_00401690.cpp"
#include "../../src/game/script_viewer_draw_0042c360.cpp"

#pragma code_seg(".text$07context")
void* __stdcall ScriptViewerDrawCompilerContext() {
    return reinterpret_cast<void*>(ScriptViewer_DrawTask_0042c590);
}
#pragma code_seg()
