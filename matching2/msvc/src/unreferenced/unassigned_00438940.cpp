// 0x00438940..0x00438949: point the record at itself and clear its first byte.
struct Object_00438940 {
    __declspec(noinline) void Init();
};

#pragma code_seg(".text$01accessor")
void Object_00438940::Init() {
    *(Object_00438940**)((unsigned char*)this + 0x2000) = this;
    *(unsigned char*)this = 0;
}

#pragma code_seg()
