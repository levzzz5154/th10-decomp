// Compiler context only; never selected as recovered game code. The archive
// reader bodies are ABI anchors for the loader's EAX name argument.
#include "../native_archive_read/read.cpp"
#include "../../../../src/pack/arcmngr/archive_find.cpp"
#include "../native_archive_read/decrypt.cpp"
#include "../../../../src/core/zunlib/archive_load_file.cpp"
#include "../../../../src/game/spttest/spt_test_load.cpp"

#pragma code_seg(".text$z9context")
void* __stdcall SptTestCompilerContext() {
    return reinterpret_cast<void*>(SptTest_LoadTask2);
}
#pragma code_seg()
