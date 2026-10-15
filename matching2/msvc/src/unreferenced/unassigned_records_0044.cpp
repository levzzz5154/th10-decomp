// Three-dword record copies: the source record arrives in EAX and the
// destination pointer in ECX, a private /LTCG pair, so the four are compiled as
// one cluster with an array-walking compiler context.

struct UnassignedHolder_00442130 {
    unsigned char pad_000[0x18];
    unsigned int first;   // +0x0018
    unsigned int second;  // +0x001C
    unsigned int third;   // +0x0020
};

struct UnassignedHolder_00442150 {
    unsigned char pad_000[0x24];
    unsigned int first;   // +0x0024
    unsigned int second;  // +0x0028
    unsigned int third;   // +0x002C
};

struct UnassignedHolder_004421c0 {
    unsigned char pad_000[0x0C];
    unsigned int first;   // +0x000C
    unsigned int second;  // +0x0010
    unsigned int third;   // +0x0014
};

struct UnassignedTriple_00442130 {
    unsigned int first;   // +0x0000
    unsigned int second;  // +0x0004
    unsigned int third;   // +0x0008
    __declspec(noinline) void CopyInto(UnassignedHolder_00442130* dest) const;
};

struct UnassignedTriple_00442150 {
    unsigned int first;   // +0x0000
    unsigned int second;  // +0x0004
    unsigned int third;   // +0x0008
    __declspec(noinline) void CopyInto(UnassignedHolder_00442150* dest) const;
};

struct UnassignedTriple_004421c0 {
    unsigned int first;   // +0x0000
    unsigned int second;  // +0x0004
    unsigned int third;   // +0x0008
    __declspec(noinline) void CopyInto(UnassignedHolder_004421c0* dest) const;
};

struct UnassignedByteTriple_00442180 {
    unsigned char b0;  // +0x0000
    unsigned char b1;  // +0x0001
    unsigned char b2;  // +0x0002
};

struct UnassignedWide_00442180 {
    unsigned int first;   // +0x0000
    unsigned int second;  // +0x0004
    unsigned int third;   // +0x0008
    __declspec(noinline) void FromBytes(const UnassignedByteTriple_00442180* source);
};
#pragma code_seg(".text$01")
void UnassignedTriple_00442130::CopyInto(UnassignedHolder_00442130* dest) const {
    *(UnassignedTriple_00442130*)((char*)dest + 0x18) = *this;
}
#pragma code_seg()

#pragma code_seg(".text$03")
void UnassignedTriple_00442150::CopyInto(UnassignedHolder_00442150* dest) const {
    *(UnassignedTriple_00442150*)((char*)dest + 0x24) = *this;
}
#pragma code_seg()

#pragma code_seg(".text$05")
void UnassignedTriple_004421c0::CopyInto(UnassignedHolder_004421c0* dest) const {
    *(UnassignedTriple_004421c0*)((char*)dest + 0x0C) = *this;
}
#pragma code_seg()

