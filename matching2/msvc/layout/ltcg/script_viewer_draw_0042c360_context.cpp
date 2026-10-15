// Compiler context only; never selected as recovered game code. The queue
// writer and marked-text formatter are ABI anchors for the ESI/EBX arguments.
#include "../../src/game/ascii/add_string.cpp"
#include "../../src/game/ascii/add_formatted_marked.cpp"
#include "../../src/game/spttest/script_viewer_draw_0042c360.cpp"

#pragma code_seg(".text$07context")
void* __stdcall ScriptViewerDrawCompilerContext() {
    return reinterpret_cast<void*>(ScriptViewer_DrawTask_0042c590);
}
#pragma code_seg()
