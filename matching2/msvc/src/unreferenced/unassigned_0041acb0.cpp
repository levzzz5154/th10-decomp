// 0x0041ACB0: construct the effect manager. Its 2198 effect entities are
// built by their own constructor (0x0041ACF0, destructor 0x0041AD60) through
// the compiler's exception-aware vector iterator; the constructor body then
// clears the whole manager, marks it active and publishes it. Native LTCG
// passes the manager in ESI.
#include <string.h>

struct EffectEntity_0041acb0 {
    unsigned char bytes[0x3F0];

    EffectEntity_0041acb0();
    ~EffectEntity_0041acb0();
};

struct EffectManager {
    unsigned int flags;                     // +0x00
    unsigned char reserved_004[0x10];
    EffectEntity_0041acb0 effects[2198];    // +0x14
    unsigned char reserved_tail[0x873B0 * 4 - 0x14 - 2198 * 0x3F0];

    __declspec(noinline) EffectManager();
};

extern "C" EffectManager* g_item_manager;

#pragma code_seg(".text$01fn")
EffectManager::EffectManager() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    g_item_manager = this;
}
#pragma code_seg()
