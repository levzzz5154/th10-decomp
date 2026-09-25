#include <cstddef>
#include <cstdint>
#include <cstring>

// Prefix fields used by the CRT's FILE-like stream at offsets 0 through 0xF.
struct WriteStringStreamPrefix {
    char* current;
    int remaining;
    char* base;
    unsigned int flags;
};

typedef char WriteStringStreamPrefix_current_check[
    offsetof(WriteStringStreamPrefix, current) == 0x0 ? 1 : -1];
typedef char WriteStringStreamPrefix_remaining_check[
    offsetof(WriteStringStreamPrefix, remaining) == 0x4 ? 1 : -1];
typedef char WriteStringStreamPrefix_base_check[
    offsetof(WriteStringStreamPrefix, base) == 0x8 ? 1 : -1];
typedef char WriteStringStreamPrefix_flags_check[
    offsetof(WriteStringStreamPrefix, flags) == 0xc ? 1 : -1];

extern "C" int __cdecl asm_flsbuf_00454d11(
    int character,
    WriteStringStreamPrefix* stream);

namespace {

int add32(int left, int right) {
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

int subtract32(int left, int right) {
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

bool isCountOnly(const WriteStringStreamPrefix* stream) {
    return (stream->flags & 0x40) != 0 && stream->base == 0;
}

void writeCharacter(
    WriteStringStreamPrefix* stream,
    int* outputCount,
    unsigned char character) {
    if (isCountOnly(stream)) {
        *outputCount = add32(*outputCount, 1);
        return;
    }

    stream->remaining = subtract32(stream->remaining, 1);
    int result;
    if (stream->remaining >= 0) {
        *stream->current = static_cast<char>(character);
        ++stream->current;
        result = character;
    } else {
        result = asm_flsbuf_00454d11(
            static_cast<signed char>(character), stream);
    }

    if (result == -1) {
        *outputCount = -1;
    } else {
        *outputCount = add32(*outputCount, 1);
    }
}

} // namespace

// The retail helper used EAX=count, ECX=bytes, EDI=stream, and one stack
// argument for length. This typed cdecl signature is the conventional form of
// that data flow; the semantic formatter has local writers with the same
// behavior and does not depend on the old register entry.
extern "C" void __cdecl asm_write_string_00454e81(
    WriteStringStreamPrefix* stream,
    int* outputCount,
    const char* bytes,
    int length) {
    if (isCountOnly(stream)) {
        *outputCount = add32(*outputCount, length);
        return;
    }

    // Retail enters the loop based on length alone. It tests the error count
    // only after writing one byte, so a preexisting -1 still permits that
    // first attempt when length is positive.
    while (length > 0) {
        const unsigned char character = static_cast<unsigned char>(*bytes);
        length = subtract32(length, 1);
        writeCharacter(stream, outputCount, character);
        ++bytes;
        if (*outputCount == -1) {
            break;
        }
    }
}
