#include <cstddef>
#include <cstdint>
#include <cstring>

// This is the four-field prefix used by the retail FILE-like output object.
// The formatters that call this routine initialize these fields at offsets
// 0, 4, 8, and 0xC respectively.
struct RetailPrintStream {
    char* current;
    int remaining;
    char* base;
    unsigned int flags;
};

using FloatToText = int(__cdecl*)(double*, char*, int, int, int);
using FloatTextPostProcessor = void(__cdecl*)(char*);

extern "C" int __cdecl asm_flsbuf_00454d11(int character, RetailPrintStream* stream);
extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);
extern "C" void __cdecl asm_free_00452422(void* block);
extern "C" unsigned int __cdecl asm_strlen_00456720(const char* text);
extern "C" int __cdecl asm_wctomb_0045a16e(char* destination, unsigned short wide);

extern "C" const char* data_004731a0;
extern "C" const wchar_t* data_004731a4;
extern "C" FloatToText data_004739c0;
extern "C" FloatTextPostProcessor data_004739c4;
extern "C" FloatTextPostProcessor data_004739cc;
extern "C" unsigned short* data_004739d8;

namespace {

// The retail parser uses a small combined character-class / state-transition
// table at 0x0046A790.  Its first 72 bytes are the 9 x 8 transition matrix;
// bytes 0 through 88 also provide the low-nibble character classes for ASCII
// space through 'x'.  Keeping the bytes here gives the same table-driven
// parser without depending on a fixed absolute address.
constexpr unsigned char kFormatClassAndTransition[89] = {
    6, 0, 0, 6, 0, 1, 0, 0, 16,
    0, 3, 6, 0, 6, 2, 16, 4, 69,
    69, 69, 69, 5, 5, 5, 5, 5, 53, 48,
    0, 80, 0, 0, 0, 0, 32, 40, 56,
    80, 88, 7, 8, 0, 55, 48, 48, 87,
    80, 7, 0, 0, 32, 32, 8, 0, 0,
    0, 8, 96, 104, 96, 96, 96, 96, 0,
    0, 112, 112, 120, 120, 120, 120, 8,
    7, 8, 0, 0, 7, 0, 8, 8, 8,
    0, 0, 8, 0, 8, 0, 7, 8
};

constexpr unsigned int kPlus = 0x0001;
constexpr unsigned int kSpace = 0x0002;
constexpr unsigned int kLeftJustify = 0x0004;
constexpr unsigned int kZeroPad = 0x0008;
constexpr unsigned int kLong = 0x0010;
constexpr unsigned int kShort = 0x0020;
constexpr unsigned int kSignedConversion = 0x0040;
constexpr unsigned int kAlternate = 0x0080;
constexpr unsigned int kNegative = 0x0100;
constexpr unsigned int kAlternateOctal = 0x0200;
constexpr unsigned int kWide = 0x0800;
constexpr unsigned int kI64 = 0x8000;

struct OutputCounter {
    RetailPrintStream* stream;
    int count;
};

int wrapAdd(int left, int right) {
    std::uint32_t leftBits;
    std::uint32_t rightBits;
    std::uint32_t resultBits;
    int result;
    std::memcpy(&leftBits, &left, sizeof(leftBits));
    std::memcpy(&rightBits, &right, sizeof(rightBits));
    resultBits = leftBits + rightBits;
    std::memcpy(&result, &resultBits, sizeof(result));
    return result;
}

int wrapSubtract(int left, int right) {
    std::uint32_t leftBits;
    std::uint32_t rightBits;
    std::uint32_t resultBits;
    int result;
    std::memcpy(&leftBits, &left, sizeof(leftBits));
    std::memcpy(&rightBits, &right, sizeof(rightBits));
    resultBits = leftBits - rightBits;
    std::memcpy(&result, &resultBits, sizeof(result));
    return result;
}

int wrapMultiplyByTen(int value) {
    std::uint32_t bits;
    std::memcpy(&bits, &value, sizeof(bits));
    bits *= 10;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

int wrapNegate(int value) {
    std::uint32_t bits;
    std::memcpy(&bits, &value, sizeof(bits));
    bits = 0u - bits;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

std::uint32_t readDword(const unsigned char* address) {
    std::uint32_t value;
    std::memcpy(&value, address, sizeof(value));
    return value;
}

std::uint64_t readQword(const unsigned char* address) {
    std::uint64_t value;
    std::memcpy(&value, address, sizeof(value));
    return value;
}

std::uint32_t nextDword(const unsigned char*& arguments) {
    const std::uint32_t value = readDword(arguments);
    arguments += 4;
    return value;
}

bool isCountOnly(const RetailPrintStream* stream) {
    return (stream->flags & 0x40) != 0 && stream->base == nullptr;
}

void writeCharacter(OutputCounter& output, unsigned char character) {
    RetailPrintStream* const stream = output.stream;
    if (isCountOnly(stream)) {
        output.count = wrapAdd(output.count, 1);
        return;
    }

    stream->remaining = wrapSubtract(stream->remaining, 1);
    int result;
    if (stream->remaining >= 0) {
        *stream->current = static_cast<char>(character);
        ++stream->current;
        result = character;
    } else {
        result = asm_flsbuf_00454d11(static_cast<signed char>(character), stream);
    }

    if (result == -1) {
        output.count = -1;
    } else {
        output.count = wrapAdd(output.count, 1);
    }
}

void writeRepeated(OutputCounter& output, unsigned char character, int count) {
    while (count > 0 && output.count != -1) {
        count = wrapSubtract(count, 1);
        writeCharacter(output, character);
    }
}

void writeBytes(OutputCounter& output, const char* bytes, int count) {
    if (isCountOnly(output.stream)) {
        output.count = wrapAdd(output.count, count);
        return;
    }

    while (count > 0 && output.count != -1) {
        writeCharacter(output, static_cast<unsigned char>(*bytes));
        ++bytes;
        count = wrapSubtract(count, 1);
    }
}

bool isLeadByte(unsigned char character) {
    return (data_004739d8[character] & 0x8000) != 0;
}

void writeLiteralCharacter(OutputCounter& output,
                           unsigned char character,
                           const unsigned char*& nextFormatByte) {
    if (isLeadByte(character)) {
        writeCharacter(output, character);
        // The retail routine emits a lead byte and the following byte as one
        // multibyte character, even when that following byte is the terminator.
        writeCharacter(output, *nextFormatByte);
        ++nextFormatByte;
    } else {
        writeCharacter(output, character);
    }
}

int boundedNarrowLength(const char* text, int precision) {
    int length = 0;
    std::uint32_t remaining = precision == -1
        ? 0x7fffffffu
        : static_cast<std::uint32_t>(precision);
    while (remaining != 0 && text[length] != '\0') {
        --remaining;
        length = wrapAdd(length, 1);
    }
    return length;
}

int boundedWideLength(const wchar_t* text, int precision) {
    int length = 0;
    std::uint32_t remaining = precision == -1
        ? 0x7fffffffu
        : static_cast<std::uint32_t>(precision);
    while (remaining != 0 && text[length] != L'\0') {
        --remaining;
        length = wrapAdd(length, 1);
    }
    return length;
}

int signed32(std::uint32_t bits) {
    int value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

} // namespace

// 0x00454ED7..0x00455670: Visual C++ 7.1 CRT printf-format engine.
// Ghidra's entry and all four callers agree on the ordinary cdecl shape:
// (stream/state, format, byte-addressed va_list cursor) -> output byte count.
extern "C" int __cdecl asm_FUN_00454ed7_00454ed7(
    RetailPrintStream* stream,
    const unsigned char* format,
    void* argumentCursor) {
    OutputCounter output = { stream, 0 };
    const unsigned char* arguments = static_cast<const unsigned char*>(argumentCursor);
    const unsigned char* nextFormatByte = format;
    int parserState = 0;

    // Per-conversion state.  State 1 in the retail transition table resets all
    // of these fields after a percent sign.
    int precision = -1;
    int width = 0;
    int floatCapitalization = 0;
    int prefixLength = 0;
    unsigned int flags = 0;
    bool skipText = false;
    bool wideText = false;
    const char* narrowText = nullptr;
    const wchar_t* unicodeText = nullptr;
    int textLength = 0;
    char prefix[2] = { 0, 0 };
    char characterBuffer[8] = { 0 };
    char numberBuffer[514] = { 0 };

    while (*nextFormatByte != 0 && output.count >= 0) {
        const unsigned char character = *nextFormatByte++;
        const signed char signedCharacter = static_cast<signed char>(character);
        unsigned int characterClass = 0;
        if (signedCharacter >= ' ' && signedCharacter <= 'x') {
            characterClass = kFormatClassAndTransition[
                static_cast<unsigned int>(signedCharacter - ' ')] & 0x0f;
        }

        // Each table entry stores the next parser state in its high nibble.
        parserState = kFormatClassAndTransition[characterClass * 8u +
                                               static_cast<unsigned int>(parserState)] >> 4;
        if (parserState == 0) {
            writeLiteralCharacter(output, character, nextFormatByte);
            continue;
        }
        if (parserState == 1) {
            precision = -1;
            width = 0;
            floatCapitalization = 0;
            prefixLength = 0;
            flags = 0;
            skipText = false;
            wideText = false;
            narrowText = nullptr;
            unicodeText = nullptr;
            textLength = 0;
            prefix[0] = prefix[1] = 0;
            continue;
        }

        switch (parserState) {
        case 2: // flags
            switch (character) {
            case ' ': flags |= kSpace; break;
            case '#': flags |= kAlternate; break;
            case '+': flags |= kPlus; break;
            case '-': flags |= kLeftJustify; break;
            case '0': flags |= kZeroPad; break;
            }
            break;

        case 3: // field width
            if (character == '*') {
                width = signed32(nextDword(arguments));
                if (width < 0) {
                    flags |= kLeftJustify;
                    width = wrapNegate(width);
                }
            } else {
                width = wrapAdd(wrapMultiplyByTen(width),
                                static_cast<int>(character) - '0');
            }
            break;

        case 4: // precision dot
            precision = 0;
            break;

        case 5: // precision digits or '*'
            if (character == '*') {
                precision = signed32(nextDword(arguments));
                if (precision < 0) {
                    precision = -1;
                }
            } else {
                precision = wrapAdd(wrapMultiplyByTen(precision),
                                    static_cast<int>(character) - '0');
            }
            break;

        case 6: // h, l, w, or I32/I64 length modifier
            if (character == 'h') {
                flags |= kShort;
            } else if (character == 'l') {
                flags |= kLong;
            } else if (character == 'w') {
                flags |= kWide;
            } else if (character == 'I') {
                if (nextFormatByte[0] == '6' && nextFormatByte[1] == '4') {
                    nextFormatByte += 2;
                    flags |= kI64;
                } else if (nextFormatByte[0] == '3' && nextFormatByte[1] == '2') {
                    nextFormatByte += 2;
                    flags &= ~kI64;
                } else {
                    const unsigned char following = *nextFormatByte;
                    const bool supportedIntegerConversion =
                        following == 'd' || following == 'i' || following == 'o' ||
                        following == 'u' || following == 'x' || following == 'X';
                    if (!supportedIntegerConversion) {
                        parserState = 0;
                        writeLiteralCharacter(output, character, nextFormatByte);
                    }
                }
            }
            break;

        case 7: {
            unsigned int integerBase = 0;
            unsigned int digitOffset = 0;
            bool signedInteger = false;
            void* allocatedFloatBuffer = nullptr;
            char stackFloatBuffer[0x200];

            if (character == 'C') {
                if ((flags & (kWide | kLong | kShort)) == 0) {
                    flags |= kWide;
                }
            } else if (character == 'S') {
                if ((flags & (kWide | kLong | kShort)) == 0) {
                    flags |= kWide;
                }
            } else if (character == 'E' || character == 'G') {
                floatCapitalization = 1;
            }

            unsigned char conversion = character;
            if (conversion == 'C') conversion = 'c';
            if (conversion == 'S') conversion = 's';
            if (conversion == 'E' || conversion == 'G') {
                conversion = static_cast<unsigned char>(conversion + 0x20);
            }

            switch (conversion) {
            case 'c': {
                arguments += 4;
                const std::uint32_t value = readDword(arguments - 4);
                if ((flags & (kWide | kLong)) == 0) {
                    characterBuffer[0] = static_cast<char>(value);
                    narrowText = characterBuffer;
                    textLength = 1;
                } else {
                    const int converted = asm_wctomb_0045a16e(
                        characterBuffer, static_cast<unsigned short>(value));
                    if (converted < 0) {
                        skipText = true;
                    } else {
                        narrowText = characterBuffer;
                        textLength = converted;
                    }
                }
                break;
            }

            case 's': {
                const int stringLimit = precision == -1 ? 0x7fffffff : precision;
                arguments += 4;
                const std::uint32_t pointerBits = readDword(arguments - 4);
                if ((flags & (kWide | kLong)) == 0) {
                    const char* const value = reinterpret_cast<const char*>(pointerBits);
                    narrowText = value == nullptr ? data_004731a0 : value;
                    textLength = boundedNarrowLength(narrowText, stringLimit);
                } else {
                    const wchar_t* value = reinterpret_cast<const wchar_t*>(pointerBits);
                    if (value == nullptr) {
                        value = data_004731a4;
                    }
                    unicodeText = value;
                    wideText = true;
                    textLength = boundedWideLength(unicodeText, stringLimit);
                }
                break;
            }

            case 'Z': {
                arguments += 4;
                const std::uint32_t pointerBits = readDword(arguments - 4);
                if (pointerBits == 0) {
                    narrowText = data_004731a0;
                    textLength = static_cast<int>(asm_strlen_00456720(narrowText));
                    break;
                }

                const unsigned char* const countedString =
                    reinterpret_cast<const unsigned char*>(pointerBits);
                short signedByteLength;
                std::memcpy(&signedByteLength, countedString, sizeof(signedByteLength));
                const std::uint32_t stringPointerBits = readDword(countedString + 4);

                if (stringPointerBits == 0) {
                    narrowText = data_004731a0;
                    textLength = static_cast<int>(asm_strlen_00456720(narrowText));
                } else if ((flags & kWide) != 0) {
                    unicodeText = reinterpret_cast<const wchar_t*>(
                        static_cast<std::uintptr_t>(stringPointerBits));
                    wideText = true;
                    textLength = static_cast<int>(signedByteLength) / 2;
                } else {
                    narrowText = reinterpret_cast<const char*>(
                        static_cast<std::uintptr_t>(stringPointerBits));
                    textLength = static_cast<int>(signedByteLength);
                }
                break;
            }

            case 'n': {
                arguments += 4;
                const std::uint32_t pointerBits = readDword(arguments - 4);
                void* const destination = reinterpret_cast<void*>(pointerBits);
                if ((flags & kShort) != 0) {
                    const short count = static_cast<short>(output.count);
                    std::memcpy(destination, &count, sizeof(count));
                } else {
                    std::memcpy(destination, &output.count, sizeof(output.count));
                }
                skipText = true;
                break;
            }

            case 'd':
            case 'i':
                flags |= kSignedConversion;
                signedInteger = true;
                integerBase = 10;
                break;

            case 'u':
                integerBase = 10;
                break;

            case 'o':
                integerBase = 8;
                if ((flags & kAlternate) != 0) {
                    flags |= kAlternateOctal;
                }
                break;

            case 'x':
                integerBase = 16;
                digitOffset = 0x27;
                if ((flags & kAlternate) != 0) {
                    prefix[0] = '0';
                    prefix[1] = 'x';
                    prefixLength = 2;
                }
                break;

            case 'X':
                integerBase = 16;
                digitOffset = 7;
                if ((flags & kAlternate) != 0) {
                    prefix[0] = '0';
                    prefix[1] = 'X';
                    prefixLength = 2;
                }
                break;

            case 'p':
                precision = 8;
                digitOffset = 7;
                integerBase = 16;
                if ((flags & kAlternate) != 0) {
                    prefix[0] = '0';
                    prefix[1] = 'X';
                    prefixLength = 2;
                }
                break;

            case 'e':
            case 'f':
            case 'g': {
                flags |= kSignedConversion;
                int floatPrecision = precision;
                if (floatPrecision < 0) {
                    floatPrecision = 6;
                } else if (floatPrecision == 0 && conversion == 'g') {
                    floatPrecision = 1;
                }
                if (floatPrecision > 0x200) {
                    floatPrecision = 0x200;
                }

                char* floatBuffer = stackFloatBuffer;
                if (floatPrecision > 0xa3) {
                    allocatedFloatBuffer = asm_malloc_00452706(
                        static_cast<unsigned int>(floatPrecision + 0x15d));
                    if (allocatedFloatBuffer != nullptr) {
                        floatBuffer = static_cast<char*>(allocatedFloatBuffer);
                    } else {
                        floatPrecision = 0xa3;
                    }
                }

                double value;
                std::memcpy(&value, arguments, sizeof(value));
                arguments += 8;
                data_004739c0(&value, floatBuffer, conversion, floatPrecision,
                              floatCapitalization);

                if ((flags & kAlternate) != 0 && floatPrecision == 0) {
                    data_004739cc(floatBuffer);
                }
                if (conversion == 'g' && (flags & kAlternate) == 0) {
                    data_004739c4(floatBuffer);
                }

                if (floatBuffer[0] == '-') {
                    flags |= kNegative;
                    narrowText = floatBuffer + 1;
                } else {
                    narrowText = floatBuffer;
                }
                textLength = static_cast<int>(asm_strlen_00456720(narrowText));
                break;
            }

            default:
                // The retail conversion state silently consumes unsupported
                // specifiers.  The parser table routes ordinary text through
                // state 0, so this covers only conversion-state misses.
                break;
            }

            if (integerBase != 0) {
                std::uint64_t value;
                if ((flags & kI64) != 0) {
                    value = readQword(arguments);
                    arguments += 8;
                } else {
                    const std::uint32_t rawValue = nextDword(arguments);
                    if ((flags & kShort) != 0) {
                        if (signedInteger) {
                            value = static_cast<std::uint64_t>(
                                static_cast<std::int64_t>(static_cast<short>(rawValue)));
                        } else {
                            value = static_cast<unsigned short>(rawValue);
                        }
                    } else if (signedInteger) {
                        value = static_cast<std::uint64_t>(
                            static_cast<std::int64_t>(signed32(rawValue)));
                    } else {
                        value = rawValue;
                    }
                }

                if (signedInteger && (static_cast<std::int64_t>(value) < 0)) {
                    flags |= kNegative;
                    value = std::uint64_t(0) - value;
                }

                if (value == 0 && integerBase == 16) {
                    prefixLength = 0;
                }
                if (precision < 0) {
                    precision = 1;
                } else {
                    flags &= ~kZeroPad;
                }
                if (precision > 0x200) {
                    precision = 0x200;
                }

                int digitCount = 0;
                if (precision > 0 || value != 0) {
                    do {
                        const unsigned int digit =
                            static_cast<unsigned int>(value % integerBase);
                        value /= integerBase;
                        int encodedDigit = static_cast<int>(digit) + '0';
                        if (encodedDigit > '9') {
                            encodedDigit += static_cast<int>(digitOffset);
                        }
                        numberBuffer[digitCount++] = static_cast<char>(encodedDigit);
                        precision = wrapSubtract(precision, 1);
                    } while (precision > 0 || value != 0);
                }

                if ((flags & kAlternateOctal) != 0 &&
                    (digitCount == 0 || numberBuffer[digitCount - 1] != '0')) {
                    numberBuffer[digitCount++] = '0';
                }
                for (int left = 0, right = digitCount - 1; left < right; ++left, --right) {
                    const char temporary = numberBuffer[left];
                    numberBuffer[left] = numberBuffer[right];
                    numberBuffer[right] = temporary;
                }
                narrowText = numberBuffer;
                textLength = digitCount;
            }

            if (!skipText) {
                if ((flags & kSignedConversion) != 0) {
                    if ((flags & kNegative) != 0) {
                        prefix[0] = '-';
                        prefixLength = 1;
                    } else if ((flags & kPlus) != 0) {
                        prefix[0] = '+';
                        prefixLength = 1;
                    } else if ((flags & kSpace) != 0) {
                        prefix[0] = ' ';
                        prefixLength = 1;
                    }
                }

                const int padding = wrapSubtract(
                    wrapSubtract(width, prefixLength), textLength);
                if ((flags & (kLeftJustify | kZeroPad)) == 0) {
                    writeRepeated(output, ' ', padding);
                }
                writeBytes(output, prefix, prefixLength);
                if ((flags & kZeroPad) != 0 && (flags & kLeftJustify) == 0) {
                    writeRepeated(output, '0', padding);
                }

                if (wideText && textLength > 0) {
                    for (int index = 0; index < textLength; ++index) {
                        int converted = asm_wctomb_0045a16e(
                            characterBuffer, static_cast<unsigned short>(unicodeText[index]));
                        if (converted < 1) {
                            break;
                        }
                        writeBytes(output, characterBuffer, converted);
                    }
                } else if (wideText) {
                    // The retail helper receives a nonpositive counted-wide
                    // length without converting characters. In count-only
                    // mode it adds that signed length directly to the count.
                    writeBytes(output, reinterpret_cast<const char*>(unicodeText), textLength);
                } else {
                    writeBytes(output, narrowText, textLength);
                }

                if ((flags & kLeftJustify) != 0) {
                    writeRepeated(output, ' ', padding);
                }
            }

            if (allocatedFloatBuffer != nullptr) {
                asm_free_00452422(allocatedFloatBuffer);
            }
            break;
        }

        default:
            // The retail machine has only states 0 through 7.  Keep this
            // guard so corrupted table data cannot index parser state.
            parserState = 0;
            break;
        }
    }

    return output.count;
}
