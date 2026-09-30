// 0x004659c0: register a static destructor with the runtime's exit list.
//
// The registered function is an ordinary __cdecl void(void) in the image; the
// runtime keeps it in the atexit table and runs it from doexit.

extern "C" void __cdecl CloseGlobalArchive_00465a60(void);
extern "C" int __cdecl asm_atexit_00452e0a(void (__cdecl*)(void));

extern "C" void __cdecl unassigned_004659c0(void) {
    asm_atexit_00452e0a(CloseGlobalArchive_00465a60);
}
