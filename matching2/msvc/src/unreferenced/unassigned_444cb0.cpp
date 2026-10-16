// 0x00444CB0..0x00444CD1: copy one source field into a strided destination
// array. Native LTCG supplies this method's internal register convention:
// destination in EAX, source in EDX, and count in ECX.

struct DestinationCopySource {
    unsigned char pad_000[0x2fc];
    int field_2fc;
};

struct DestinationCopy {
    __declspec(noinline) int Copy(const DestinationCopySource* source,
                                   int count);
};

#pragma code_seg(".text$01copy")
int DestinationCopy::Copy(
    const DestinationCopySource* source, int count) {
    if (count > 0) {
        unsigned char* cursor =
            reinterpret_cast<unsigned char*>(this) + 0x10;
        do {
            *reinterpret_cast<int*>(cursor) = source->field_2fc;
            cursor += 0x1c;
        } while (--count);
    }
    return 0;
}
#pragma code_seg()
