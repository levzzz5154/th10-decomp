// 0x0043AA30..0x0043AA5A: release one slot of the record's pointer table.
extern "C" void __cdecl entry_free_00452422(void* memory);

struct Object_0043aa30 {
    unsigned char pad_000[0x98];
    void* slots;                     // base of the table is this+0x98
    __declspec(noinline) void Release(int index);
};

#pragma code_seg(".text$01accessor")
void Object_0043aa30::Release(int index) {
    void** table = (void**)((unsigned char*)this + 0x98);
    if (table[index]) {
        entry_free_00452422(table[index]);
        table[index] = 0;
    }
    table[index] = 0;
}
#pragma code_seg()
