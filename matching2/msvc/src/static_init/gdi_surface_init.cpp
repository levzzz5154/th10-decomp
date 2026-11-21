// 0x00465940: register a static destructor with the runtime's exit list.
//
// The registered function is an ordinary __cdecl void(void) in the image; the
// runtime keeps it in the atexit table and runs it from doexit.

extern "C" void __cdecl StaticExit_GdiSurface(void);
extern "C" int __cdecl crt_atexit(void (__cdecl*)(void));

extern "C" void __cdecl StaticInit_GdiSurface(void) {
    crt_atexit(StaticExit_GdiSurface);
}
