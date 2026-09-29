// 0x00465950: register a static destructor with the runtime's exit list.
//
// The registered function is an ordinary __cdecl void(void) in the image; the
// runtime keeps it in the atexit table and runs it from doexit.

void __cdecl StopGlobalWorker_00465a30(void);
extern "C" int __cdecl asm_atexit_00452e0a(void (__cdecl*)(void));

extern "C" void __cdecl unassigned_00465950(void) {
    asm_atexit_00452e0a(StopGlobalWorker_00465a30);
}
