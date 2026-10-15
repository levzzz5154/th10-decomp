// 0x00438910..0x0043893A: release every entry of the record's pointer table
// when its leading count word is set.
extern "C" void __cdecl crt_free(void* memory);

struct Object_00438910 {
    void* entries[0x2800];           // +0x0000
    unsigned int count;              // +0xA000
    __declspec(noinline) void Clear();
};

#pragma code_seg(".text$01accessor")
void Object_00438910::Clear() {
    if (count) {
        for (int index = 0; index < 0x2800; ++index) {
            if (entries[index]) {
                crt_free(entries[index]);
            }
        }
    }
}
#pragma code_seg()
