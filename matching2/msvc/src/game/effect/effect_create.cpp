// 0x0040AF90 (86 bytes) - Effect_Create
//
// Allocate the 0x18-byte effect manager (Effect), clear it, raise its live flag,
// publish it through the manager global and load the bullet scripts.  On a
// script-load failure the freshly built manager is released and freed, and the
// factory reports NULL, so callers can tell "not created" from "created".
//
// Retail keeps the manager in EBX across the script-load and release calls -
// that is the register LoadScripts receives it in and the register the teardown
// calls are reached with.

struct Effect {
    unsigned flags;             // +0x00
    unsigned reserved_004;      // +0x04
    void *primary_callback;     // +0x08
    void *secondary_callback;   // +0x0C
    void *bullet_resource;      // +0x10
    unsigned reserved_014;      // +0x14
};

extern "C" void *__cdecl memset(void *dest, int value, unsigned size);
extern "C" int __stdcall Effect_Initialize(
        Effect *state);
extern "C" void __stdcall asm_BulletManager_Release_0040af00(
        Effect *state);
extern "C" void __cdecl crt_free_startup(void *memory);
extern "C" Effect *g_effect;

__declspec(noinline) Effect *Effect_Create();
#pragma code_seg(".text$00c_create")
Effect *Effect_Create() {
    Effect *fresh = new Effect;
    Effect *state;
    if (fresh) {
        memset(fresh, 0, sizeof(Effect));
        fresh->flags |= 2u;
        g_effect = fresh;
        state = fresh;
    } else {
        state = 0;
    }
    if (Effect_Initialize(state)) {
        if (state) {
            asm_BulletManager_Release_0040af00(state);
            crt_free_startup(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
