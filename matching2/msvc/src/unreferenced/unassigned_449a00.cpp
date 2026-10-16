// Range predicate used by the private animation-buffer helpers.
struct ResetRange {
    unsigned char reserved_0000[0x68];

    __declspec(noinline) int Contains(unsigned int address);
};

#pragma code_seg(".text$01predicate")
int ResetRange::Contains(unsigned int address) {
    unsigned int begin = reinterpret_cast<unsigned int>(this) + 0x68;
    unsigned int end = reinterpret_cast<unsigned int>(this) + 0x3AC068;
    if (address >= begin) {
        if (address < end)
            return 1;
    }
    return 0;
}
#pragma code_seg()
