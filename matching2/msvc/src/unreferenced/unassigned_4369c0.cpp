// 0x004369C0..0x004369D3: release the GDI object the record owns.
extern "C" __declspec(dllimport) int __stdcall DeleteObject(void* object);

struct Object11 {
    void* handle;                    // +0x00
    __declspec(noinline) void Release();
};

#pragma code_seg(".text$01accessor")
void Object11::Release() {
    if (handle) {
        DeleteObject(handle);
        handle = 0;
    }
}
#pragma code_seg()
