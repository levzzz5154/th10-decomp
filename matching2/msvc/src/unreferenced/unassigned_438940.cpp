// 0x00438940..0x00438949: point the record at itself and clear its first byte.
struct Object16 {
    __declspec(noinline) void Init();
};

#pragma code_seg(".text$01accessor")
void Object16::Init() {
    *(Object16**)((unsigned char*)this + 0x2000) = this;
    *(unsigned char*)this = 0;
}

#pragma code_seg()
