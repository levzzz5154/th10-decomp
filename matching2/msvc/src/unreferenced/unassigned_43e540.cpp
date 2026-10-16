// 0x0043E540..0x0043E55F: release one slot of the record's pointer table.
extern "C" void __cdecl crt_free(void* memory);

struct Object35 {
    unsigned char pad_000[0x1ec0];
    void* slots;                     // base of the table is this+0x1EC0
    __declspec(noinline) void Release(int index);
};

#pragma code_seg(".text$01accessor")
void Object35::Release(int index) {
    void** table = (void**)((unsigned char*)this + 0x1ec0);
    if (table[index]) {
        crt_free(table[index]);
        table[index] = 0;
    }
}
#pragma code_seg()
