// 0x0045071E..0x00450723 - the import thunk for DirectInput8Create.  The call
// tail-merges into the imported routine, so the compiler emits the retail
// six-byte jump through the import address table slot at 0x00466000.
extern "C" __declspec(dllimport) long __stdcall DirectInput8Create(
    void* instance, unsigned int version, void* riid, void** out, void* outer);

extern "C" long __stdcall DirectInput8Create_0045071e(
    void* instance, unsigned int version, void* riid, void** out, void* outer) {
    return DirectInput8Create(instance, version, riid, out, outer);
}
