// 0x004423A0..0x004423A5: copy the source dword into destination +0x0c.
// Native LTCG supplies the source object in EAX and destination in EDX.
struct Destination_004423a0 {
    unsigned char pad_000[0x0c];
    int value;
};

struct Source_004423a0 {
    int value;

    __declspec(noinline) void CopyTo(Destination_004423a0* destination) const;
};

#pragma code_seg(".text$01target")
void Source_004423a0::CopyTo(Destination_004423a0* destination) const {
    destination->value = value;
}
#pragma code_seg()
