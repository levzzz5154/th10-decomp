// 0x00442390..0x00442395: copy the source dword into destination +0x8.
// Native LTCG selects the source object in EAX and destination in EDX.
struct CopyDestination2 {
    unsigned char pad_000[8];
    int value_008;
};

struct CopySource2 {
    int value_000;

    __declspec(noinline) void CopyTo(CopyDestination2* destination);
};

typedef char CopyDestination_00442390_size_must_fit[
    sizeof(CopyDestination2) == 0xC ? 1 : -1];
typedef char CopySource_00442390_size_must_fit[
    sizeof(CopySource2) == 0x4 ? 1 : -1];

#pragma code_seg(".text$01copy")
void CopySource2::CopyTo(CopyDestination2* destination) {
    destination->value_008 = value_000;
}
#pragma code_seg()
