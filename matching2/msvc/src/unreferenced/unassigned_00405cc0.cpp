// 0x00405CC0: construct the bullet manager. Its 2001 bullet entities are
// built by their own constructor (0x00405D00, destructor 0x00405DE0) through
// the compiler's exception-aware vector iterator; the constructor body then
// clears the whole manager and publishes it. Native LTCG passes the manager
// in ESI.
#include <string.h>

struct BulletEntity_00405cc0 {
    unsigned char bytes[0x7F0];

    BulletEntity_00405cc0();
    ~BulletEntity_00405cc0();
};

struct BulletManager_00405cc0 {
    unsigned char reserved_000[0x60];
    BulletEntity_00405cc0 bullets[2001];    // +0x60
    unsigned char reserved_tail[0x3E0B54 - 0x60 - 2001 * 0x7F0];

    __declspec(noinline) BulletManager_00405cc0();
};

extern "C" BulletManager_00405cc0* data_004776f0;

#pragma code_seg(".text$01fn")
BulletManager_00405cc0::BulletManager_00405cc0() {
    memset(this, 0, sizeof(*this));
    data_004776f0 = this;
}
#pragma code_seg()
