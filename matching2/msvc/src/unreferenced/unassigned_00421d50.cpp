// 0x00421D50..0x00421D6A: release the cached object, when present.
//
// The native-LTCG context supplies the retail private receiver convention
// (slot in ESI).  The vtable slot is a __stdcall indirect release entry: its
// machine-level sequence is the retail load/push/call/clear schedule.
struct CachedObject {
    void **vtable;
};

typedef void (__stdcall *ReleaseFn_00421d50)(CachedObject *);

struct CachedSlot {
    unsigned char unknown_0000[0x3ADA74];
    CachedObject *cached;

    __declspec(noinline) void Release();
};

#pragma code_seg(".text$03rel")
void CachedSlot::Release() {
    CachedObject *object = cached;
    if (object != 0) {
        ReleaseFn_00421d50 release = (ReleaseFn_00421d50)object->vtable[2];
        release(object);
        cached = 0;
    }
}
#pragma code_seg()
