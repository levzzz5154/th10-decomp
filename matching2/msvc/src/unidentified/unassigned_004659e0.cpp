// 0x004659e0: register a static destructor with the runtime's exit list.
//
// The registered function is an ordinary __cdecl void(void) in the image; the
// runtime keeps it in the atexit table and runs it from doexit.

extern "C" void __cdecl asm_FUN_00465a80_00465a80(void);
extern "C" int __cdecl asm_atexit_00452e0a(void (__cdecl*)(void));

extern "C" void __cdecl unassigned_004659e0(void) {
    asm_atexit_00452e0a(asm_FUN_00465a80_00465a80);
}
