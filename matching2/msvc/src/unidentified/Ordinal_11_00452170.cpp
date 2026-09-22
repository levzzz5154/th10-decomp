// 0x00452170..0x00452175: Ordinal_11 import thunk.
//
// Ordinal_11 is the three-argument DirectSound creation import used by the
// sound-device startup path.  Declaring it as a stdcall import lets the
// historical linker emit the direct six-byte import-slot jump.
extern "C" __declspec(dllimport) int __stdcall Ordinal_11(
    void* guid, void** sound_device, void* outer);

extern "C" int __stdcall Ordinal_11_00452170(
    void* guid, void** sound_device, void* outer) {
    return Ordinal_11(guid, sound_device, outer);
}
