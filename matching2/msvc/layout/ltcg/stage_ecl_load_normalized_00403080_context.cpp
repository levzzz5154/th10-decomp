#include "../../src/script/stage_ecl_load_normalized_00403080.cpp"
#pragma code_seg(".text$03context")
extern "C" int __stdcall StageEclLoadNormalizedContext(StageEclLoader_00403850** loaders, const char** names, int count) {
    int result = 0;
    for (int i = 0; i < count; ++i) result += loaders[i]->LoadNormalized(names[i]);
    return result;
}
#pragma code_seg()
