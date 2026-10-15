// Compiler context only; never selected as recovered game code.
#include "../../src/pack/arcmngr/legacy_string_duplicate_00435220.cpp"

struct LegacyStringOwner_00435220 {
    int reserved[2];
    char* text;
};

void __stdcall LegacyStringLoad_00435260(const char* path);

#pragma code_seg(".text$08context")
int __stdcall LegacyStringContext_00435220(LegacyStringOwner_00435220* owners,
                                           const char** paths, int count) {
    for (int i = 0; i < count; ++i) {
        const char* path = paths[i];
        LegacyStringLoad_00435260(path);
        owners[i].text = LegacyString_Duplicate(path);
        if (!owners[i].text)
            return 0;
    }
    return 1;
}
#pragma code_seg()
