// 0x00442000..0x00442005: copy the source dword into destination +0x4.
// Native LTCG selects the source object in EAX and destination in EDX.
struct CopyDestination {
    unsigned char pad_000[4];
    int value_004;
};

struct CopySource {
    int value_000;

    __declspec(noinline) void CopyTo(CopyDestination* destination);
};

typedef char CopyDestination_00442000_size_must_fit[
    sizeof(CopyDestination) == 0x8 ? 1 : -1];
typedef char CopySource_00442000_size_must_fit[
    sizeof(CopySource) == 0x4 ? 1 : -1];

#pragma code_seg(".text$01copy")
void CopySource::CopyTo(CopyDestination* destination) {
    destination->value_004 = value_000;
}
#pragma code_seg()
