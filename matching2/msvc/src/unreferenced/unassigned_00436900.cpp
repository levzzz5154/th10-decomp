// 0x00436900..0x00436937: release the GDI object and the heap-backed string.
extern "C" __declspec(dllimport) int __stdcall DeleteObject(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);

struct Object_00436900 {
    void* handle;                    // +0x00
    unsigned char pad_004[0xc];
    char* heap;                      // +0x10
    unsigned char pad_014[0xc];
    unsigned int length;             // +0x20
    unsigned int capacity;           // +0x24
    __declspec(noinline) void Destroy();
};

#pragma code_seg(".text$01accessor")
void Object_00436900::Destroy() {
    if (handle) {
        DeleteObject(handle);
        handle = 0;
    }
    if (capacity >= 0x10) {
        crt_free_startup(heap);
    }
    capacity = 0xf;
    length = 0;
    ((char*)this)[0x10] = 0;
}
#pragma code_seg()
