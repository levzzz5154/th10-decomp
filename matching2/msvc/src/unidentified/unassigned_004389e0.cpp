// 0x004389E0..0x004389E3: the pointer just past the eight-byte header.
struct Object_004389e0 {
    unsigned char pad_000[8];
    __declspec(noinline) unsigned char* Tail();
};

#pragma code_seg(".text$01accessor")
unsigned char* Object_004389e0::Tail() { return (unsigned char*)this + 8; }

#pragma code_seg()
