// 0x00428F00..0x00428F17: indexed two-word copy from a private LTCG ABI.
struct IndexedCopySource_00428f00 {
    unsigned int first;
    unsigned int second;

    __declspec(noinline) void Copy(void* base, int index);
};

#pragma code_seg(".text$07f0")
__declspec(noinline) void IndexedCopySource_00428f00::Copy(void* base, int index) {
    unsigned char* destination =
        reinterpret_cast<unsigned char*>(base) + index * 0x98 + 0x32EC;
    *reinterpret_cast<unsigned int*>(destination) = first;
    *reinterpret_cast<unsigned int*>(destination + 4) = second;
}
#pragma code_seg()
