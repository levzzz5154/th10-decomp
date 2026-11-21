// 0x004052E0: release the whole bullet-pool usage mask and clear its pending flag.
//
// The pool state lives in the tail of the game state object (g_pGameStateManager,
// 0x00491C10), so only the widths and offsets are certain; the field names below
// describe the values the retail code writes. 0x80808080 marks every pool slot
// free. The object address arrives in EAX, which is why this body is compiled
// through the native LTCG cluster driver.

struct GameStateBulletPool {
    unsigned char unused_0000[0x732458];
    unsigned int pool_usage_mask;   // +0x732458, 0x80808080 = every slot free
    int pool_pending;               // +0x73245C

    __declspec(noinline) void ReleasePoolMask();
};

#pragma code_seg(".text$01pool_mask")
void GameStateBulletPool::ReleasePoolMask() {
    this->pool_pending = 0;
    this->pool_usage_mask = 0x80808080u;
}
#pragma code_seg()
