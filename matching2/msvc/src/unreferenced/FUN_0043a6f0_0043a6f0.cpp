// 0x0043A6F0: swap the two bytes of a 16-bit word. Retail has no callers left;
// the whole-program pass gave the out-of-line copy a private convention with
// the word in AX both ways, which the LTCG layout reproduces.
union WordBytes {
    unsigned short word;
    struct {
        unsigned char low;
        unsigned char high;
    } bytes;
};

#pragma code_seg(".text$01swap")
__declspec(noinline) unsigned short SwapLowWordBytes(unsigned short value) {
    WordBytes result;
    result.bytes.low = static_cast<unsigned char>(value >> 8);
    result.bytes.high = static_cast<unsigned char>(value);
    return result.word;
}
#pragma code_seg()
