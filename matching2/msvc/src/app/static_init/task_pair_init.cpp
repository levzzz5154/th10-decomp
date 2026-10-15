// 0x00465960: dynamic initializer of the scheduler task pair at 0x00492548:
// zero it, mark it in use and register its destructor with atexit.

extern "C" int data_00492588;
extern "C" int data_00492548[0x11];
extern "C" void __cdecl StaticExit_TaskPair(void);
extern "C" int __cdecl asm_atexit_00452e0a(void (__cdecl*)(void));
extern "C" void* __cdecl memset(void* destination, int value, unsigned int count);

extern "C" void __cdecl StaticInit_TaskPair(void) {
    data_00492588 &= ~1;
    memset(data_00492548, 0, 0x44);
    data_00492548[0] |= 2;
    asm_atexit_00452e0a(StaticExit_TaskPair);
}
