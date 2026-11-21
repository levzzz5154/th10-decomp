// 0x00465A50: atexit destructor of the scheduler task pair at 0x00492548.
extern "C" void __stdcall Scheduler_ReleaseTaskPair(void* pair);
extern "C" unsigned char g_task_pair;

extern "C" void __cdecl StaticExit_TaskPair() {
    Scheduler_ReleaseTaskPair(&g_task_pair);
}
