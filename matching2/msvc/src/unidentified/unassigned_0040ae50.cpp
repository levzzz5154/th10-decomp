// 0x0040AE50..0x0040AE6D: initialize and publish the bullet-manager state.
//
// Native LTCG selects the retail private receiver convention (state in EAX)
// when this member is called from small_private_abi_a_context.cpp.  The
// memset spelling is intentional: MSVC 13.10 expands it to the retail
// register-zero/store schedule rather than folding the first field to 2.
struct BulletManagerState_0040ae50 {
    unsigned flags;
    unsigned reserved_004;
    void *primary;
    void *secondary;
    void *resource;
    unsigned reserved_014;

    __declspec(noinline) void Initialize();
};

extern "C" void *memset(void *, int, unsigned);
extern "C" BulletManagerState_0040ae50 *data_004776fc;

#pragma code_seg(".text$01init")
void BulletManagerState_0040ae50::Initialize() {
    memset(this, 0, sizeof(BulletManagerState_0040ae50));
    flags |= 2u;
    data_004776fc = this;
}
#pragma code_seg()
