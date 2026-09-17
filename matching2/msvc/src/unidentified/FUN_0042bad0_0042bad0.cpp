extern "C" void __cdecl entry_free_00452422(void* memory);
struct OwnedPointerArray_0042bad0 {
    unsigned char unknown_0000[0x34]; void** items; int count;
    __declspec(noinline) void Clear();
};
#pragma code_seg(".text$01cleanup")
void OwnedPointerArray_0042bad0::Clear() {
    if (items) {
        for (int i = 0; i < count; ++i) {
            if (items[i]) { entry_free_00452422(items[i]); items[i] = 0; }
        }
        if (items) { entry_free_00452422(items); items = 0; }
        items = 0;
    }
}
#pragma code_seg()
