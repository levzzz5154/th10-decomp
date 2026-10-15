// 0x00465950: register a static destructor with the runtime's exit list.
//
// The registered function is an ordinary __cdecl void(void) in the image; the
// runtime keeps it in the atexit table and runs it from doexit.

void __cdecl StaticExit_Worker(void);
extern "C" int __cdecl asm_atexit_00452e0a(void (__cdecl*)(void));

extern "C" void __cdecl StaticInit_Worker(void) {
    asm_atexit_00452e0a(StaticExit_Worker);
}
