// Out-of-line copies of six single-field object methods. Each region reads the
// object from EAX and takes no argument, a private /LTCG receiver, so the six
// are compiled together as one cluster with an array-walking compiler context
// that establishes the register (see build_support/layout/ltcg/unassigned_members_0044.json).

struct UnassignedFlagged_004452e0 {
    unsigned char pad_000[0x35C];
    unsigned int flags_35c;  // +0x035C

    __declspec(noinline) unsigned int LowBit() const;
};

struct UnassignedMasked_0044bf20 {
    unsigned char pad_000[0x10];
    unsigned int flags_010;  // +0x0010

    __declspec(noinline) void ClearLowBit();
};

struct UnassignedMarked_0044c250 {
    unsigned int flags_000;  // +0x0000

    __declspec(noinline) void MarkBit1();
};

struct UnassignedRef_0044c600 {
    unsigned char pad_000[4];
    int references_004;  // +0x0004

    __declspec(noinline) void Release();
};

struct UnassignedAttach_0044c640 {
    unsigned char flag_0000;                // +0x0000
    unsigned char pad_0001[0x1FFF];
    UnassignedAttach_0044c640* owner_2000;  // +0x2000
    unsigned char flag_2004;                // +0x2004

    __declspec(noinline) void AttachSelf();
};

struct UnassignedZero_0044c760 {
    unsigned int value_000;  // +0x0000

    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$01flag")
unsigned int UnassignedFlagged_004452e0::LowBit() const {
    return flags_35c & 1;
}
#pragma code_seg()

#pragma code_seg(".text$03mask")
void UnassignedMasked_0044bf20::ClearLowBit() {
    flags_010 &= ~1u;
}
#pragma code_seg()

#pragma code_seg(".text$05mark")
void UnassignedMarked_0044c250::MarkBit1() {
    flags_000 |= 2u;
}
#pragma code_seg()

#pragma code_seg(".text$07ref")
void UnassignedRef_0044c600::Release() {
    --references_004;
}
#pragma code_seg()

#pragma code_seg(".text$09attach")
void UnassignedAttach_0044c640::AttachSelf() {
    owner_2000 = this;
    flag_0000 = 0;
    flag_2004 = 0;
}
#pragma code_seg()

#pragma code_seg(".text$0Bzero")
void UnassignedZero_0044c760::Reset() {
    value_000 = 0;
}
#pragma code_seg()
