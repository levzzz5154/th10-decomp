// 0x0040AF90 (86 bytes) - BulletManager_Create
//
// Allocate the 0x18-byte bullet-manager state, clear it, raise its live flag,
// publish it through the manager global and load the bullet scripts.  On a
// script-load failure the freshly built manager is released and freed, and the
// factory reports NULL, so callers can tell "not created" from "created".
//
// Retail keeps the manager in EBX across the script-load and release calls -
// that is the register LoadScripts receives it in and the register the teardown
// calls are reached with.

struct BulletManagerState_0040af90 {
    unsigned flags;             // +0x00
    unsigned reserved_004;      // +0x04
    void *primary_callback;     // +0x08
    void *secondary_callback;   // +0x0C
    void *bullet_resource;      // +0x10
    unsigned reserved_014;      // +0x14
};

extern "C" void *__cdecl memset(void *dest, int value, unsigned size);
extern "C" int __stdcall BulletManager_LoadScripts_0040ae70(
        BulletManagerState_0040af90 *state);
extern "C" void __stdcall asm_BulletManager_Release_0040af00(
        BulletManagerState_0040af90 *state);
extern "C" void __cdecl entry_free_004524a1(void *memory);
extern "C" BulletManagerState_0040af90 *data_004776fc;

__declspec(noinline) BulletManagerState_0040af90 *BulletManager_Create_0040af90();
#pragma code_seg(".text$00c_create")
BulletManagerState_0040af90 *BulletManager_Create_0040af90() {
    BulletManagerState_0040af90 *fresh = new BulletManagerState_0040af90;
    BulletManagerState_0040af90 *state;
    if (fresh) {
        memset(fresh, 0, sizeof(BulletManagerState_0040af90));
        fresh->flags |= 2u;
        data_004776fc = fresh;
        state = fresh;
    } else {
        state = 0;
    }
    if (BulletManager_LoadScripts_0040ae70(state)) {
        if (state) {
            asm_BulletManager_Release_0040af00(state);
            entry_free_004524a1(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
