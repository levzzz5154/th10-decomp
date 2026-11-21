// 0x004659d0: register a static destructor with the runtime's exit list.
//
// The registered function is an ordinary __cdecl void(void) in the image; the
// runtime keeps it in the atexit table and runs it from doexit.

extern "C" void __cdecl StaticExit_Empty1(void);
extern "C" int __cdecl crt_atexit(void (__cdecl*)(void));

extern "C" void __cdecl StaticInit_EmptyExit1(void) {
    crt_atexit(StaticExit_Empty1);
}
