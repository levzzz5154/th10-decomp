// Compiler context only; never selected as recovered game code.
#include "../../src/render/animation_manager_mark_resource_for_removal_004493e0.cpp"

struct BulletPool {
    unsigned char reserved_0000[0x3E0B54];
    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$30context")
int __stdcall AnimationManagerHelperCompilerContext(BulletPool** pools, int count) {
    while (count--) {
        BulletPool* pool = *pools++;
        pool->Reset();
        pool->Reset();
    }
    return 0;
}
#pragma code_seg()
