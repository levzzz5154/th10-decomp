// 0x00418C00..0x00418C05: reads the shared 32-bit state word at 0x00491FC4.
extern "C" unsigned char g_stage_flags;

int GetStateWord(void) {
    return *(int*)&g_stage_flags;
}
