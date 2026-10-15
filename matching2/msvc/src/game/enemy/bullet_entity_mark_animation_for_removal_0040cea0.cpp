// 0x0040CEA0 - Mark a bullet's active animation for deferred removal and
// invalidate the bullet-local handle.

struct AnimationLookupContext;
class AnimationManager {
public:
    void* __fastcall SetFlag(AnimationLookupContext* context, int id);
};

struct BulletEntity_0040cea0 {
    unsigned char reserved_000[0x774];
    int animation_handle;
    unsigned char reserved_778[0x378c - 0x778];
    __declspec(noinline) void __fastcall MarkAnimationForRemoval(
            AnimationManager* manager);
};

extern "C" AnimationLookupContext* data_00491c10;

#pragma code_seg(".text$01mark")
__forceinline void MarkAnimationPending(unsigned int* flags) {
    *flags |= 0x10;
}

void __fastcall BulletEntity_0040cea0::MarkAnimationForRemoval(
        AnimationManager* manager) {
    MarkAnimationPending(reinterpret_cast<unsigned int*>(
        reinterpret_cast<unsigned char*>(this) + 0x378c));
    const int handle = animation_handle;
    manager->SetFlag(data_00491c10, handle);
    animation_handle = 0;
}
#pragma code_seg()
