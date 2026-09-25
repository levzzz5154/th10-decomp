#include <cstddef>
#include <cstdint>

// Existing assembly callers use the old cdecl entry label.
#pragma comment(linker, "/alternatename:_asm_FUN_00460e41_00460e41=_DecimalConversionRecord_00460E41")

extern "C" unsigned int data_00473660;
extern "C" void __cdecl asm_dtold_00460d87(
    std::uint32_t* extended_words, const std::uint32_t* binary64_words);
extern "C" int __cdecl asm_FUN_00461841_00461841(
    std::uint32_t significand_low,
    std::uint32_t significand_high,
    std::uint16_t sign_and_exponent,
    int precision,
    unsigned char flags,
    std::int16_t* output_record);
extern "C" char* __cdecl asm_FUN_0045bd80_0045bd80(
    char* destination, const char* source);
extern "C" void __fastcall asm_security_check_cookie_00458ea5(
    unsigned int stack_cookie);

namespace {

// ___dtold writes the x87 extended value as three little-endian words. The
// first ten bytes are significant; the 32-bit alignment may leave two bytes
// of tail padding in this C++ object, which no helper reads or writes.
struct Extended80Words {
    std::uint32_t significand_low;
    std::uint32_t significand_high;
    std::uint16_t sign_and_exponent;
};

struct DecimalTextRecord {
    std::int16_t exponent;
    signed char sign;
    unsigned char digit_count;
    char digits[20];
};

typedef char Extended80Words_offset_check[
    offsetof(Extended80Words, sign_and_exponent) == 8 ? 1 : -1];
typedef char DecimalTextRecord_offset_check[
    offsetof(DecimalTextRecord, digits) == 4 ? 1 : -1];
typedef char DecimalTextRecord_size_check[
    sizeof(DecimalTextRecord) == 24 ? 1 : -1];

}  // namespace

// The two leading dwords are the exact 64-bit input representation on the
// x86 stack. The caller supplies a four-int result record and a digit buffer.
extern "C" __declspec(noinline) int* __cdecl DecimalConversionRecord_00460E41(
    std::uint32_t binary64_low,
    std::uint32_t binary64_high,
    int* result_record,
    char* digit_buffer) {
    // Retain the retail stack-cookie check in ordinary C++: the saved word is
    // XORed with a stable address in this frame and decoded before checking.
    volatile unsigned int saved_cookie = 0;
    const std::uintptr_t cookie_anchor =
        reinterpret_cast<std::uintptr_t>(&saved_cookie);
    saved_cookie = data_00473660 ^ static_cast<unsigned int>(cookie_anchor);

    const std::uint32_t binary64_words[2] = {
        binary64_low,
        binary64_high,
    };
    Extended80Words extended = {0};
    asm_dtold_00460d87(&extended.significand_low, binary64_words);

    DecimalTextRecord decimal_text = {0};
    const int conversion_status = asm_FUN_00461841_00461841(
        extended.significand_low,
        extended.significand_high,
        extended.sign_and_exponent,
        0x11,
        0,
        &decimal_text.exponent);

    result_record[2] = conversion_status;
    result_record[0] = static_cast<int>(decimal_text.sign);
    result_record[1] = static_cast<int>(decimal_text.exponent);
    asm_FUN_0045bd80_0045bd80(digit_buffer, decimal_text.digits);
    result_record[3] = static_cast<int>(
        reinterpret_cast<std::intptr_t>(digit_buffer));

    const unsigned int decoded_cookie = saved_cookie ^
        static_cast<unsigned int>(cookie_anchor);
    asm_security_check_cookie_00458ea5(decoded_cookie);
    return result_record;
}
