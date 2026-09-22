// 0x00442000..0x00442005: copy the source dword into destination +0x4.
// Native LTCG selects the source object in EAX and destination in EDX.
struct CopyDestination_00442000 {
    unsigned char pad_000[4];
    int value_004;
};

struct CopySource_00442000 {
    int value_000;

    __declspec(noinline) void CopyTo(CopyDestination_00442000* destination);
};

typedef char CopyDestination_00442000_size_must_fit[
    sizeof(CopyDestination_00442000) == 0x8 ? 1 : -1];
typedef char CopySource_00442000_size_must_fit[
    sizeof(CopySource_00442000) == 0x4 ? 1 : -1];

#pragma code_seg(".text$01copy")
void CopySource_00442000::CopyTo(CopyDestination_00442000* destination) {
    destination->value_004 = value_000;
}
#pragma code_seg()
