// Semantic candidate for 0x00435DC0..0x00435F9A: DecompressDatLzss.
// Not selected by the exact-build manifest.
// The x86 entry contract is four stack arguments, EAX pointer return, and
// callee cleanup of 16 bytes (__stdcall).

extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);
extern "C" unsigned char data_0048f868[0x2000];

namespace {

enum {
    kLzssDictionaryMask = 0x1fff,
    kLzssFirstDictionaryPosition = 1
};

class LzssBitReader {
public:
    LzssBitReader(const unsigned char* source, int sourceLength)
        : source_(source), cursor_(source), sourceLength_(sourceLength),
          currentByte_(0), bitMask_(0x80) {
    }

    __forceinline unsigned int readBits(unsigned int mask) {
        unsigned int value = 0;
        do {
            if (readBit()) {
                value |= mask;
            }
            mask >>= 1;
        } while (mask);
        return value;
    }

private:
    __forceinline bool readBit() {
        if (bitMask_ == 0x80) {
            // Retail reads the input byte before checking sourceLength, then
            // discards the loaded byte when the cursor is out of range. Keep
            // the raw x86 memory read visible, including its fault behavior
            // for a truncated buffer at an inaccessible address.
            const unsigned char loaded_byte =
                *static_cast<const volatile unsigned char*>(cursor_);
            if (cursor_ - source_ < sourceLength_) {
                currentByte_ = loaded_byte;
                ++cursor_;
            } else {
                currentByte_ = 0;
            }
        }

        const bool set = (currentByte_ & bitMask_) != 0;
        bitMask_ >>= 1;
        if (bitMask_ == 0) {
            bitMask_ = 0x80;
        }
        return set;
    }

    const unsigned char* source_;
    const unsigned char* cursor_;
    int sourceLength_;
    unsigned int currentByte_;
    unsigned char bitMask_;
};

} // namespace

extern "C" unsigned char* __stdcall DecompressDatLzss_00435dc0(
    const unsigned char* source,
    int sourceLength,
    unsigned char* output,
    unsigned int outputCapacity) {
    if (output == 0) {
        output = static_cast<unsigned char*>(asm_malloc_00452706(outputCapacity));
        if (output == 0) {
            return 0;
        }
    }

    LzssBitReader bits(source, sourceLength);
    // The decoder preserves the shared dictionary between calls. Matches may
    // refer to earlier output in this call or to bytes already in the ring.
    unsigned char* const dictionary = data_0048f868;
    unsigned char* outputPosition = output;
    unsigned int dictionaryPosition = kLzssFirstDictionaryPosition;

    for (;;) {
        if (bits.readBits(1) != 0) {
            const unsigned char value =
                static_cast<unsigned char>(bits.readBits(0x80));
            *outputPosition = value;
            ++outputPosition;
            dictionary[dictionaryPosition] = value;
            dictionaryPosition = (dictionaryPosition + 1) & kLzssDictionaryMask;
            continue;
        }

        unsigned int matchPosition = bits.readBits(0x1000);
        if (matchPosition == 0) {
            break;
        }

        const unsigned int matchLength = bits.readBits(8) + 3;
        unsigned int copied = 0;
        while (copied < matchLength) {
            const unsigned int sourcePosition =
                (matchPosition + copied) & kLzssDictionaryMask;
            const unsigned char value = dictionary[sourcePosition];
            *outputPosition = value;
            ++outputPosition;
            dictionary[dictionaryPosition] = value;
            dictionaryPosition = (dictionaryPosition + 1) & kLzssDictionaryMask;
            ++copied;
        }
    }

    return output;
}
