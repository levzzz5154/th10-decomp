// 0x0043A6F0: swap the two bytes of the incoming low word in AX. The
// four-byte volatile scratch preserves the original byte-store/load order;
// GCC's regparm(1) accepts and returns the word in AX.
union WordBytes_0043a6f0 {
    unsigned int storage;
    unsigned short word;
    struct {
        unsigned char low;
        unsigned char high;
    } bytes;
};

static_assert(sizeof(WordBytes_0043a6f0) == 4, "scratch word must occupy four bytes");

extern "C" __attribute__((regparm(1), noinline, used,
                           section(".text$swap_low_word_0043a6f0"), aligned(1)))
unsigned short SwapLowWordBytes_0043a6f0(unsigned short value) {
    volatile WordBytes_0043a6f0 result;
    result.bytes.low = static_cast<unsigned char>(value >> 8);
    result.bytes.high = static_cast<unsigned char>(value);
    return result.word;
}
