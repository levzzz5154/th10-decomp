// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../../src/unreferenced/unassigned_0040d660.cpp"

extern "C" void __cdecl crt_free(void* memory);

// 0x0040D680's body, compiled only so the whole-program pass can carry its
// object in ESI: no declaration names that register, and the pointer has to
// outlive the free.  The layout's gaps place this section at the retail
// address, so the destructor's call bakes retail's own displacement.  None of
// these bytes are selected as recovered code.
#pragma code_seg(".text$03anchor")
void BulletEntity_0040d680::ReleaseResource() {
    void* const resource = owned_resource;
    vtable = 0x0046D0F0;
    if (resource != 0) {
        crt_free(resource);
        owned_resource = 0;
    }
}
#pragma code_seg()

#pragma code_seg(".text$05context")
extern "C" int __stdcall DtorDeleteContext_0040d660(Releaseable_0040d660** items, int count) {
    int freed = 0;
    while (count--) {
        freed += (*items++)->Delete(1) != 0;
    }
    return freed;
}
#pragma code_seg()
