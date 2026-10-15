// 0x00465A50: atexit destructor of the scheduler task pair at 0x00492548.
extern "C" void __stdcall asm_Recovery_ReleaseRawPair_0043cb00(void* pair);
extern "C" unsigned char g_task_pair;

extern "C" void __cdecl StaticExit_TaskPair() {
    asm_Recovery_ReleaseRawPair_0043cb00(&g_task_pair);
}
