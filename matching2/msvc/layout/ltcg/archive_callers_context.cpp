// Compiler context only; no context bytes count as recovered game code.
#include "../../src/game/asset_buffer.cpp"
#pragma code_seg(".text$07context")
int __stdcall ArchiveCallersContext(AssetBuffer** buffers, const char** names, MapResource** maps, ParameterLoader** parameters, int count) {
    for (int i = 0; i < count; ++i) {
        LoadAsset(names[i], buffers[i]);
        maps[i]->LoadMap(names[i]);
        parameters[i]->Load(names[i]);
    }
    return count;
}
#pragma code_seg()
