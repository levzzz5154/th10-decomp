// Semantic C++ model for retail 0x0041BA30 (29 bytes).
//
// The callback receives its context in ECX. It skips the scene update when
// the active scene's flag byte at +0x58 has bit 2 set; otherwise it forwards
// that context to the 0x0041B8E0 update routine.

struct ActiveSceneFlags_0041BA30 {
    unsigned char unknown_000[0x58];
    unsigned char flags_058;
};

struct SceneCallbackContext_0041BA30 {
    __declspec(noinline) int UpdateSceneSecondaryCallback();
};

extern "C" ActiveSceneFlags_0041BA30* data_00477810;

// Semantic contract for 0x0041B8E0. Retail expects the context in EAX and
// reaches it with a tail jump; this explicit C++ parameter is stack-passed and
// does not provide an ABI bridge.
extern "C" int __cdecl asm_FUN_0041b8e0_0041b8e0(
    SceneCallbackContext_0041BA30* context);

// The __thiscall receiver occupies ECX and the int result is returned in EAX,
// matching the callback's external retail register/return convention.
int SceneCallbackContext_0041BA30::UpdateSceneSecondaryCallback() {
    ActiveSceneFlags_0041BA30* activeScene = data_00477810;
    if (activeScene != 0 && (activeScene->flags_058 & 0x04) != 0)
        return 1;

    return asm_FUN_0041b8e0_0041b8e0(this);
}
