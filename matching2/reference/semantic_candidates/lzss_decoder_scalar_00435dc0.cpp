// Native-MSVC semantic candidate for DecompressDatLzss at 0x00435DC0.
// Not selected by regions.json: 503 compiled bytes versus retail's 475.
// The supplied MSVC object passes the existing 203-case retail differential
// suite, including ordered input reads and guard-page faults. See the
// lzss_decoder_native_00435dc0_2026_10_02 recovery note.
//
// The dictionary survives calls. Reads at input exhaustion occur before
// the signed length check, as they do in retail; the single volatile byte
// read preserves that observable fault behavior.

extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);
extern "C" unsigned char data_0048f868[0x2000];

__forceinline unsigned int ReadLzssBit(const unsigned char* source, int sourceLength,
                        const unsigned char*& cursor, unsigned int& currentByte,
                        unsigned char& bitMask) {
    if (bitMask == 0x80) {
        currentByte = *static_cast<const volatile unsigned char*>(cursor);
        if (cursor - source >= sourceLength)
            currentByte = 0;
        else
            ++cursor;
    }
    const unsigned int bit = currentByte & bitMask;
    bitMask >>= 1;
    if (!bitMask)
        bitMask = 0x80;
    return bit;
}

__forceinline void ReadLzssField(unsigned int& value, unsigned int mask,
                        const unsigned char* source, int sourceLength,
                        const unsigned char*& cursor, unsigned int& currentByte,
                        unsigned char& bitMask) {
    do {
        if (bitMask == 0x80) {
            currentByte = *static_cast<const volatile unsigned char*>(cursor);
            if (cursor - source >= sourceLength)
                currentByte = 0;
            else
                ++cursor;
        }
        if (currentByte & bitMask)
            value |= mask;
        bitMask >>= 1;
        mask >>= 1;
        if (!bitMask)
            bitMask = 0x80;
    } while(mask);
}

extern "C" unsigned char* __stdcall DecompressDatLzss_00435dc0(
    const unsigned char* source, int sourceLength, unsigned char* output,
    unsigned int outputCapacity) {
    unsigned int currentByte = 0;
    unsigned char bitMask = 0x80;
    unsigned int accumulator = 0;
    if (!output) {
        output = (unsigned char*)asm_malloc_00452706(outputCapacity);
        if (!output)
            return 0;
    }
    const unsigned char* cursor = source;
    unsigned char* outputPosition = output;
    unsigned int dictionaryPosition = 1;
    for (;;) {
        if (ReadLzssBit(source,sourceLength,cursor,currentByte,bitMask)) {
            unsigned int value = 0;
            ReadLzssField(value,0x80,source,sourceLength,cursor,currentByte,bitMask);
            *outputPosition++ = (unsigned char)value;
            data_0048f868[dictionaryPosition] = (unsigned char)value;
            dictionaryPosition = (dictionaryPosition + 1) & 0x1fff;
            continue;
        }
        ReadLzssField(accumulator,0x1000,source,sourceLength,cursor,currentByte,bitMask);
        const unsigned int matchPosition = accumulator;
        if (!matchPosition)
            break;
        accumulator = 0;
        ReadLzssField(accumulator,8,source,sourceLength,cursor,currentByte,bitMask);
        const int matchLengthMinusOne = accumulator + 2;
        for (int copied=0; copied<=matchLengthMinusOne; ++copied) {
            const unsigned char value = data_0048f868[(matchPosition + copied) & 0x1fff];
            *outputPosition++ = value;
            data_0048f868[dictionaryPosition] = value;
            dictionaryPosition = (dictionaryPosition + 1) & 0x1fff;
        }
        accumulator = 0;
    }
    while (bitMask != 0x80) {
        bitMask >>= 1;
        if (!bitMask)
            break;
    }
    return output;
}
