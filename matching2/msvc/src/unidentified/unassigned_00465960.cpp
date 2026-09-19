// 0x00465960: clear the onexit table, mark it in use and register the
// destructor that tears it down.

extern "C" int data_00492588;
extern "C" int data_00492548[0x11];
extern "C" void __cdecl asm_FUN_00465a50_00465a50(void);
extern "C" int __cdecl asm_atexit_00452e0a(void (__cdecl*)(void));
extern "C" void* __cdecl memset(void* destination, int value, unsigned int count);

extern "C" void __cdecl unassigned_00465960(void) {
    data_00492588 &= ~1;
    memset(data_00492548, 0, 0x44);
    data_00492548[0] |= 2;
    asm_atexit_00452e0a(asm_FUN_00465a50_00465a50);
}
