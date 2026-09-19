// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00405f40.cpp"

extern "C" void __cdecl opaque_release_004492a0(void* item);
extern "C" char* data_00491c10;

#pragma code_seg(".text$03anchor")
__declspec(noinline) void AnimationResource_00405f40::Release() {
    if (resource_108 == 0) {
        entry_free_004524a1(this);
        return;
    }
    for (int index = 0; index < entry_count_10c; ++index) {
        char* entry = (char*)entries_120 + index * 8;
        if (*(void**)entry != 0) {
            opaque_release_004492a0(*(void**)entry);
            *(void**)entry = 0;
        }
        if (*(void**)(entry + 4) != 0) {
            opaque_release_004492a0(*(void**)(entry + 4));
            *(void**)(entry + 4) = 0;
        }
    }
    if (auxiliary_118 != 0) {
        entry_free_004524a1(auxiliary_118);
        auxiliary_118 = 0;
    }
    if (entries_120 != 0) {
        entry_free_004524a1(entries_120);
        entries_120 = 0;
    }
    entry_free_004524a1(this);
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall ReleaseContext_00405f40(int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += ReleaseCachedResource_00405f40();
    }
    return total;
}
#pragma code_seg()
