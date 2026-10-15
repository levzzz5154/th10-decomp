// 0x00429A30..0x00429A69: pick 6 instead of 1 while the game UI is up, the
// entity is in state 1, flag 0x100 of the global flags at 0x00474E30 is set,
// and the entity's frame counter is not a multiple of four.  Nothing calls
// it any more; the entity arrives in EAX, a convention only a native LTCG
// link chooses, so the region is compiled in its own cluster.
struct GameUi_00429a30;
struct Entity_00429a30 {
    char pad_0000[0x10];
    int state;
    char pad_0014[0x1c8 - 0x14];
    int frame;

    int SelectFrameStep();
};

extern "C" GameUi_00429a30* g_game;
extern "C" unsigned int g_input_keys_raw;

#pragma code_seg(".text$01accessor")
__declspec(noinline) int Entity_00429a30::SelectFrameStep() {
    if (g_game != 0 && state == 1 && (g_input_keys_raw & 0x100) &&
        frame % 4 != 0)
        return 6;
    return 1;
}
#pragma code_seg()
