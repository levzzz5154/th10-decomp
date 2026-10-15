// 0x0041FEB0: the loading screen's update task (registered by
// 0x0041FAC0). Release the three resources the object owns when
// its "hold" bit is set, then drop the engine flag that keeps the game on hold
// and ask for game state 4.  The object arrives in ECX and the routine always
// reports success.
extern "C" unsigned char g_ascii_manager;                 // 0x004776E0 resource manager
extern "C" unsigned char g_app_flags;                 // 0x00491FF4 engine flags
extern "C" unsigned char g_main_state;                 // 0x00491FB8 game state

struct ResourceHandle { int reserved; int flags; };
struct ResourceOwner {
    unsigned char pad_0000[0x0C];
    ResourceHandle* slot_0C;                            // 0x0C
    ResourceHandle* slot_10;                            // 0x10
    unsigned char pad_0014[0x89A8 - 0x14];
    ResourceHandle* slot_89A8;                          // 0x89A8
};

extern "C" int __fastcall Loading_OnUpdate(unsigned int* owner) {
    if ((*owner & 2) == 0)
        return 1;
    ResourceOwner* resources = *(ResourceOwner**)&g_ascii_manager;
    resources->slot_0C->flags |= 2;
    resources->slot_10->flags |= 2;
    resources->slot_89A8->flags |= 2;
    *(unsigned int*)&g_app_flags &= ~0x1000u;
    *(unsigned int*)&g_main_state = 4;
    *owner &= ~2u;
    return 1;
}
