// 0x0040CEA0 - Mark a bullet's active animation for deferred removal and
// invalidate the bullet-local handle.

struct AnimationLookupContext;
class SprtCtrl {
public:
    void* __fastcall SetFlag(AnimationLookupContext* context, int id);
};

struct BulletEntity4 {
    unsigned char reserved_000[0x774];
    int animation_handle;
    unsigned char reserved_778[0x378c - 0x778];
    __declspec(noinline) void __fastcall MarkAnimationForRemoval(
            SprtCtrl* manager);
};

extern "C" AnimationLookupContext* g_sprt_ctrl;

#pragma code_seg(".text$01mark")
__forceinline void MarkAnimationPending(unsigned int* flags) {
    *flags |= 0x10;
}

void __fastcall BulletEntity4::MarkAnimationForRemoval(
        SprtCtrl* manager) {
    MarkAnimationPending(reinterpret_cast<unsigned int*>(
        reinterpret_cast<unsigned char*>(this) + 0x378c));
    const int handle = animation_handle;
    manager->SetFlag(g_sprt_ctrl, handle);
    animation_handle = 0;
}
#pragma code_seg()
