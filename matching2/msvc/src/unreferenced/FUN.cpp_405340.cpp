// 0x00405340: publish the bullet-pool usage mask that arrives in ECX and mark the
// pool pending.
//
// The pool state lives in the tail of the game state object (g_pGameStateManager,
// 0x00491C10), so only the widths and offsets are certain. The object address
// arrives in EAX and the mask in ECX, which is why this body is compiled through
// the native LTCG cluster driver.

struct GameStateBulletPool {
    unsigned char unused_0000[0x732458];
    unsigned int pool_usage_mask;   // +0x732458
    int pool_pending;               // +0x73245C

    __declspec(noinline) void SetPoolMask(unsigned int mask);
};

#pragma code_seg(".text$01pool_set")
void GameStateBulletPool::SetPoolMask(unsigned int mask) {
    this->pool_pending = 1;
    this->pool_usage_mask = mask;
}
#pragma code_seg()
