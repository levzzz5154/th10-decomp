// Compiler context only; never selected as recovered game code. The archive
// reader bodies are ABI anchors for the loader's EAX name argument.
#include "../native_archive_read/read.cpp"
#include "../native_archive_read/find.cpp"
#include "../native_archive_read/decrypt.cpp"
#include "../native_archive_read/load.cpp"
#include "../../../src/game/spttest/script_viewer_load_0042be20.cpp"

#pragma code_seg(".text$z9context")
void* __stdcall ScriptViewerCompilerContext() {
    return reinterpret_cast<void*>(ScriptViewer_LoadTask_0042be10);
}
#pragma code_seg()
