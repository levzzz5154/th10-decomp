// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sprtlib/animation_manager_mark_resource_for_removal_004493e0.cpp"

struct BulletPool {
    unsigned char reserved_0000[0x3E0B54];
    __declspec(noinline) void Reset();
};

struct AnimationResource_00447810 {
    unsigned char pad_000[0x108];
    void* resource_108;
    int entry_count_10c;
    unsigned char pad_110[0x118 - 0x110];
    void* auxiliary_118;
    void* auxiliary_11c;
    void* entries_120;
    unsigned char pad_124[0x12C - 0x124];
    void* auxiliary_12c;
    __declspec(noinline) void Release();
};

struct AnimationManager_004477d0 {
    unsigned char pad_000[0x3AD06C];
    AnimationResource_00447810* slots_3ad06c[0x21];
    __declspec(noinline) void ClearResourceSlot(int index);
};

extern "C" __declspec(noinline) int __cdecl ReleasePair_0041f930();

struct AnimationResourceEntry {
    void* handle;
    void* allocation;
    unsigned char pad_008[8];
    __declspec(noinline) void Release();
};

#pragma code_seg(".text$30context")
int __stdcall AnimationManagerHelperCompilerContext(BulletPool** pools,
                                                    AnimationResource_00447810** records,
                                                    AnimationManager_004477d0* manager,
                                                    int first, int count) {
    while (count--) {
        BulletPool* pool = *pools++;
        pool->Reset();
        pool->Reset();
        AnimationResource_00447810* record = *records++;
        record->Release();
    }
    int index = first;
    while (count--) {
        manager->ClearResourceSlot(index);
        index++;
    }
    index += ReleasePair_0041f930();
    ((AnimationResourceEntry*)records[index])->Release();
    return index;
}
#pragma code_seg()
