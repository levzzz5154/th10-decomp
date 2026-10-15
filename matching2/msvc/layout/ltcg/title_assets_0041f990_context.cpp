// Compiler context only; never selected as recovered game code.
#include "../../src/game/loading/title_assets.cpp"
#include "title_assets_dependencies/startup.cpp"
#include "title_assets_dependencies/music_stop.cpp"
#include "title_assets_dependencies/workers.cpp"
#include "../../src/platform/text_log.cpp"

// Two whole-program facts the selected functions depend on: the loader is
// reached only through its address, as a worker entry (0x0041FAC0 installs
// it), and the supervisor block's address is passed around the program.
#pragma code_seg(".text$95context")
void __stdcall TitleAssetsCompilerContext(PlatformWorker* worker, Supervisor** supervisor) {
    worker->entry = reinterpret_cast<PlatformWorkerEntry>(TitleWorker_LoadAssets_0041f990);
    *supervisor = &g_supervisor;
}
#pragma code_seg()
