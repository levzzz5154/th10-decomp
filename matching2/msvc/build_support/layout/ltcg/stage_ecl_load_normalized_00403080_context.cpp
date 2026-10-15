#include "../../../src/game/background/background_load_normalized.cpp"
#pragma code_seg(".text$03context")
extern "C" int __stdcall StageEclLoadNormalizedContext(BackGround** loaders, const char** names, int count) {
    int result = 0;
    for (int i = 0; i < count; ++i) result += loaders[i]->LoadNormalized(names[i]);
    return result;
}
#pragma code_seg()
