// 0x00428EE0..0x00428EF7: indexed two-word copy from a private LTCG ABI.
struct IndexedCopySource3 {
    unsigned int first;
    unsigned int second;

    __declspec(noinline) void Copy(void* base, int index);
};

#pragma code_seg(".text$05ee")
__declspec(noinline) void IndexedCopySource3::Copy(void* base, int index) {
    unsigned char* destination =
        reinterpret_cast<unsigned char*>(base) + index * 0x98 + 0x32E4;
    *reinterpret_cast<unsigned int*>(destination) = first;
    *reinterpret_cast<unsigned int*>(destination + 4) = second;
}
#pragma code_seg()
