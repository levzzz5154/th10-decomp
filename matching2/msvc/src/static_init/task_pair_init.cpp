// 0x00465960: dynamic initializer of the scheduler task pair at 0x00492548:
// zero it, mark it in use and register its destructor with atexit.

extern "C" int g_task_pair_flags;
extern "C" int g_task_pair[0x11];
extern "C" void __cdecl StaticExit_TaskPair(void);
extern "C" int __cdecl asm_atexit_00452e0a(void (__cdecl*)(void));
extern "C" void* __cdecl memset(void* destination, int value, unsigned int count);

extern "C" void __cdecl StaticInit_TaskPair(void) {
    g_task_pair_flags &= ~1;
    memset(g_task_pair, 0, 0x44);
    g_task_pair[0] |= 2;
    asm_atexit_00452e0a(StaticExit_TaskPair);
}
