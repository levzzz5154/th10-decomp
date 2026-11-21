// 0x00405ED0 - Re-arm the bullet pool: retire the pool's animation resource,
// zero the whole slot array, rewind the free-slot cursor, and set the state
// word back to 5.
#include <string.h>

class SprtCtrl {
public:
    void MarkResourceForRemoval(void* resource);
};

extern "C" SprtCtrl* g_sprt_ctrl;

struct BulletPool {
    unsigned char reserved_000[0x10];
    unsigned int* cursor;
    unsigned char reserved_014[0x60 - 0x14];
    unsigned int slots[0xF82BC];
    void* animation;

    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$01reset")
void BulletPool::Reset() {
    SprtCtrl* manager = g_sprt_ctrl;
    manager->MarkResourceForRemoval(animation);
    memset(slots, 0, sizeof(slots));
    cursor = slots;
    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this) + 0x3E07A6) = 5;
}
#pragma code_seg()
