// 0x00435DC0..0x00435F9A: DecompressDatLzss.
// The x86 entry contract is four stack arguments, EAX pointer return, and
// callee cleanup of 16 bytes (__stdcall).

extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);

namespace {

enum {
    kLzssDictionaryAddress = 0x0048f868,
    kLzssDictionaryMask = 0x1fff,
    kLzssFirstDictionaryPosition = 1
};

class LzssBitReader {
public:
    LzssBitReader(const unsigned char* source, int sourceLength)
        : source_(source), sourceLength_(sourceLength), sourcePosition_(0),
          currentByte_(0), bitMask_(0x80) {
    }

    unsigned int readBits(unsigned int count) {
        unsigned int value = 0;
        while (count != 0) {
            value <<= 1;
            if (readBit()) {
                value |= 1;
            }
            --count;
        }
        return value;
    }

private:
    bool readBit() {
        if (bitMask_ == 0x80) {
            // Retail reads the input byte before checking sourceLength, then
            // discards the loaded byte when the cursor is out of range. Keep
            // the raw x86 memory read visible, including its fault behavior
            // for a truncated buffer at an inaccessible address.
            const unsigned int source_address =
                reinterpret_cast<unsigned int>(source_)
                + static_cast<unsigned int>(sourcePosition_);
            const volatile unsigned char* raw_source_byte =
                reinterpret_cast<const volatile unsigned char*>(source_address);
            const unsigned char loaded_byte = *raw_source_byte;
            if (sourcePosition_ < sourceLength_) {
                currentByte_ = loaded_byte;
                ++sourcePosition_;
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
    int sourceLength_;
    int sourcePosition_;
    unsigned char currentByte_;
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
    volatile unsigned char* const dictionary =
        reinterpret_cast<volatile unsigned char*>(kLzssDictionaryAddress);
    unsigned char* outputPosition = output;
    unsigned int dictionaryPosition = kLzssFirstDictionaryPosition;

    for (;;) {
        if (bits.readBits(1) != 0) {
            const unsigned char value =
                static_cast<unsigned char>(bits.readBits(8));
            *outputPosition = value;
            ++outputPosition;
            dictionary[dictionaryPosition] = value;
            dictionaryPosition = (dictionaryPosition + 1) & kLzssDictionaryMask;
            continue;
        }

        unsigned int matchPosition = bits.readBits(13);
        if (matchPosition == 0) {
            break;
        }

        const unsigned int matchLength = bits.readBits(4) + 3;
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
