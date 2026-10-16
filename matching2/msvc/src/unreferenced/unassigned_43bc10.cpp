// 0x0043BC10..0x0043BC13: the pointer just past the twelve-byte header.
struct Object30 {
    unsigned char pad_000[0xc];
    __declspec(noinline) unsigned char* Tail();
};

#pragma code_seg(".text$01accessor")
unsigned char* Object30::Tail() { return (unsigned char*)this + 0xc; }

#pragma code_seg()
