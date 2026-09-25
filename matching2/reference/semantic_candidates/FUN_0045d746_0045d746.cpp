#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" unsigned int data_00473660;
extern "C" unsigned char data_00473af4;

extern "C" int __cdecl asm_isdigit_0045685e(int character);
extern "C" void __cdecl asm_FUN_00460872_00460872(
    char* decimal_digits, int digit_count, std::uint32_t* extended_words);
extern "C" void __cdecl asm_FUN_00460b90_00460b90(
    std::uint32_t* extended_words, std::uint32_t decimal_power,
    int retain_rounding_tail);
extern "C" void __fastcall asm_security_check_cookie_00458ea5(
    unsigned int stack_cookie);

namespace {

enum ParseState {
    ParseInitial = 0,
    ParseAfterLeadingZero = 1,
    ParseAfterSign = 2,
    ParseIntegerDigits = 3,
    ParseFractionDigits = 4,
    ParsePointWithoutInteger = 5,
    ParseAfterExponentMarker = 6,
    ParseAfterExponentSign = 7,
    ParseExponentLeadingZero = 8,
    ParseExponentDigits = 9,
    ParseStopped = 10,
    ParseOptionalSign = 11,
};

bool is_nonzero_ascii_digit(unsigned char value) {
    return value >= '1' && value <= '9';
}

bool is_exponent_marker(unsigned char value) {
    return (value >= 'D' && value <= 'E') ||
           (value >= 'd' && value <= 'e');
}

bool is_crt_digit(unsigned char value) {
    return asm_isdigit_0045685e(static_cast<int>(value)) != 0;
}

// Interpret a 32-bit x86 arithmetic result as a signed int without relying on
// signed-overflow behavior in the C++ source.
std::int32_t signed_from_bits(std::uint32_t bits) {
    if (bits <= 0x7fffffffu) {
        return static_cast<std::int32_t>(bits);
    }
    return -1 - static_cast<std::int32_t>(~bits);
}

void write_zero_extended_value(unsigned char* output, std::uint16_t sign) {
    std::memset(output, 0, 12);
    std::memcpy(output + 10, &sign, sizeof(sign));
}

}  // namespace

// Parse a decimal spelling into the CRT's 12-byte _LDBL12 intermediate.
// Keep the raw C-linkage name used by current callers.
extern "C" __declspec(noinline) std::uint32_t __cdecl
asm_FUN_0045d746_0045d746(
    unsigned char* output,
    int* parsed_end_address,
    const unsigned char* text,
    int retain_rounding_tail,
    int exponent_adjustment_without_marker,
    int exponent_adjustment_without_point,
    int accept_optional_sign) {
    volatile unsigned int saved_cookie = 0;
    const std::uintptr_t cookie_anchor =
        reinterpret_cast<std::uintptr_t>(&saved_cookie);
    saved_cookie = data_00473660 ^ static_cast<unsigned int>(cookie_anchor);

    std::uint16_t sign_word = 0;
    int exponent_sign = 1;
    std::uint32_t exponent_magnitude_bits = 0;
    std::uint32_t exponent_adjustment_bits = 0;
    unsigned char digits[25] = {};
    unsigned int digit_count = 0;
    ParseState state = ParseInitial;

    bool has_numeric_syntax = false;
    bool has_decimal_point = false;
    bool has_exponent_value = false;
    bool parsing_finished = false;

    const unsigned char* const original_text = text;
    while (*text == 0x20 || *text == 0x09 || *text == 0x0a || *text == 0x0d) {
        ++text;
    }
    const unsigned char* exponent_fallback = text;

    while (!parsing_finished) {
        const unsigned char character = *text;
        const unsigned char* const next = text + 1;

        switch (state) {
        case ParseInitial:
            if (is_nonzero_ascii_digit(character)) {
                state = ParseIntegerDigits;
                continue;
            }
            if (character == data_00473af4) {
                has_decimal_point = true;
                state = ParsePointWithoutInteger;
                text = next;
                continue;
            }
            state = ParseAfterSign;
            if (character == '+') {
                text = next;
                continue;
            }
            if (character == '-') {
                sign_word = 0x8000;
                text = next;
                continue;
            }
            if (character == '0') {
                state = ParseAfterLeadingZero;
                text = next;
                continue;
            }
            parsing_finished = true;
            continue;

        case ParseAfterSign:
            if (is_nonzero_ascii_digit(character)) {
                state = ParseIntegerDigits;
                continue;
            }
            if (character == data_00473af4) {
                has_decimal_point = true;
                state = ParsePointWithoutInteger;
                text = next;
                continue;
            }
            text = original_text;
            if (character == '0') {
                state = ParseAfterLeadingZero;
                text = next;
                continue;
            }
            parsing_finished = true;
            continue;

        case ParseAfterLeadingZero:
            has_numeric_syntax = true;
            if (is_nonzero_ascii_digit(character)) {
                state = ParseIntegerDigits;
                continue;
            }
            if (character == data_00473af4) {
                has_decimal_point = true;
                state = ParseFractionDigits;
                text = next;
                continue;
            }
            if (character == '+' || character == '-') {
                state = ParseOptionalSign;
                continue;
            }
            if (character == '0') {
                text = next;
                continue;
            }
            if (is_exponent_marker(character)) {
                state = ParseAfterExponentMarker;
                text = next;
                continue;
            }
            parsing_finished = true;
            continue;

        case ParseIntegerDigits: {
            const unsigned char* current = text;
            while (is_crt_digit(*current)) {
                if (digit_count < 25) {
                    digits[digit_count++] = static_cast<unsigned char>(
                        *current - static_cast<unsigned char>('0'));
                } else {
                    ++exponent_adjustment_bits;
                }
                ++current;
            }
            has_numeric_syntax = true;
            const unsigned char following = *current;
            if (following == data_00473af4) {
                has_decimal_point = true;
                state = ParseFractionDigits;
                text = current + 1;
                continue;
            }
            if (following == '+' || following == '-') {
                state = ParseOptionalSign;
                text = current;
                continue;
            }
            if (is_exponent_marker(following)) {
                state = ParseAfterExponentMarker;
                text = current + 1;
                continue;
            }
            text = current;
            parsing_finished = true;
            continue;
        }

        case ParseFractionDigits: {
            has_decimal_point = true;
            has_numeric_syntax = true;
            const unsigned char* current = text;
            if (digit_count == 0) {
                while (*current == '0') {
                    --exponent_adjustment_bits;
                    ++current;
                }
            }
            while (is_crt_digit(*current)) {
                if (digit_count < 25) {
                    digits[digit_count++] = static_cast<unsigned char>(
                        *current - static_cast<unsigned char>('0'));
                    --exponent_adjustment_bits;
                }
                ++current;
            }
            const unsigned char following = *current;
            if (following == '+' || following == '-') {
                state = ParseOptionalSign;
                text = current;
                continue;
            }
            if (is_exponent_marker(following)) {
                state = ParseAfterExponentMarker;
                text = current + 1;
                continue;
            }
            text = current;
            parsing_finished = true;
            continue;
        }

        case ParsePointWithoutInteger:
            has_decimal_point = true;
            if (is_crt_digit(character)) {
                state = ParseFractionDigits;
                continue;
            }
            text = original_text;
            parsing_finished = true;
            continue;

        case ParseAfterExponentMarker:
            exponent_fallback = text - 1;
            if (is_nonzero_ascii_digit(character)) {
                state = ParseExponentDigits;
                continue;
            }
            if (character == '+') {
                state = ParseAfterExponentSign;
                text = next;
                continue;
            }
            if (character == '-') {
                exponent_sign = -1;
                state = ParseAfterExponentSign;
                text = next;
                continue;
            }
            if (character == '0') {
                state = ParseExponentLeadingZero;
                text = next;
                continue;
            }
            text = exponent_fallback;
            parsing_finished = true;
            continue;

        case ParseAfterExponentSign:
            if (is_nonzero_ascii_digit(character)) {
                state = ParseExponentDigits;
                continue;
            }
            if (character == '0') {
                state = ParseExponentLeadingZero;
                text = next;
                continue;
            }
            text = exponent_fallback;
            parsing_finished = true;
            continue;

        case ParseExponentLeadingZero: {
            has_exponent_value = true;
            const unsigned char* current = text;
            while (*current == '0') {
                ++current;
            }
            if (is_nonzero_ascii_digit(*current)) {
                state = ParseExponentDigits;
                text = current;
                continue;
            }
            text = current;
            parsing_finished = true;
            continue;
        }

        case ParseExponentDigits: {
            has_exponent_value = true;
            exponent_magnitude_bits = 0;
            const unsigned char* current = text;
            bool exponent_saturated = false;
            while (is_crt_digit(*current)) {
                const std::int32_t signed_digit =
                    static_cast<std::int32_t>(
                        static_cast<signed char>(*current)) - '0';
                exponent_magnitude_bits = exponent_magnitude_bits * 10u +
                    static_cast<std::uint32_t>(signed_digit);
                if (signed_from_bits(exponent_magnitude_bits) > 0x1450) {
                    exponent_magnitude_bits = 0x1451;
                    exponent_saturated = true;
                    break;
                }
                ++current;
            }
            if (exponent_saturated) {
                while (is_crt_digit(*current)) {
                    ++current;
                }
            } else if (!is_crt_digit(*current)) {
                // The loop already leaves the cursor on the first non-digit.
            }
            text = current;
            parsing_finished = true;
            continue;
        }

        case ParseOptionalSign:
            if (accept_optional_sign != 0) {
                exponent_fallback = text;
                if (character == '+') {
                    state = ParseAfterExponentSign;
                    text = next;
                    continue;
                }
                if (character == '-') {
                    exponent_sign = -1;
                    state = ParseAfterExponentSign;
                    text = next;
                    continue;
                }
            } else {
                state = ParseStopped;
            }
            parsing_finished = true;
            continue;

        case ParseStopped:
        default:
            parsing_finished = true;
            continue;
        }
    }

    *parsed_end_address = static_cast<int>(
        reinterpret_cast<std::intptr_t>(text));

    std::uint32_t status = 0;
    std::uint32_t converted_words[3] = {};
    if (!has_numeric_syntax) {
        status = 4;
    } else if (digit_count != 0) {
        if (digit_count > 24) {
            if (digits[23] > 4) {
                ++digits[23];
            }
            --digit_count;
            ++exponent_adjustment_bits;
        }

        while (digit_count != 0 && digits[digit_count - 1] == 0) {
            --digit_count;
            ++exponent_adjustment_bits;
        }

        if (digit_count != 0) {
            asm_FUN_00460872_00460872(
                reinterpret_cast<char*>(digits),
                static_cast<int>(digit_count), converted_words);

            if (exponent_sign < 0) {
                exponent_magnitude_bits = 0u - exponent_magnitude_bits;
            }
            std::uint32_t effective_exponent_bits =
                exponent_magnitude_bits + exponent_adjustment_bits;
            if (!has_exponent_value) {
                effective_exponent_bits += static_cast<std::uint32_t>(
                    exponent_adjustment_without_marker);
            }
            if (!has_decimal_point) {
                effective_exponent_bits -= static_cast<std::uint32_t>(
                    exponent_adjustment_without_point);
            }

            const std::int32_t effective_exponent =
                signed_from_bits(effective_exponent_bits);
            if (effective_exponent > 0x1450) {
                status = 2;
                std::memset(output, 0, 12);
                const std::uint32_t integer_significand = 0x80000000u;
                const std::uint16_t exponent = static_cast<std::uint16_t>(
                    0x7fff | sign_word);
                std::memcpy(output + 6, &integer_significand,
                            sizeof(integer_significand));
                std::memcpy(output + 10, &exponent, sizeof(exponent));
            } else if (effective_exponent > -0x1451) {
                asm_FUN_00460b90_00460b90(
                    converted_words, effective_exponent,
                    retain_rounding_tail);
                std::memcpy(output, converted_words, 12);
            } else {
                status = 1;
                write_zero_extended_value(output, sign_word);
            }
        } else {
            write_zero_extended_value(output, sign_word);
        }
    } else {
        write_zero_extended_value(output, sign_word);
    }

    if (status == 0 || status == 1 || status == 4) {
        std::uint16_t sign_and_exponent = 0;
        std::memcpy(&sign_and_exponent, output + 10,
                    sizeof(sign_and_exponent));
        sign_and_exponent = static_cast<std::uint16_t>(
            sign_and_exponent | sign_word);
        std::memcpy(output + 10, &sign_and_exponent,
                    sizeof(sign_and_exponent));
    }

    const unsigned int decoded_cookie = static_cast<unsigned int>(saved_cookie) ^
        static_cast<unsigned int>(cookie_anchor);
    asm_security_check_cookie_00458ea5(decoded_cookie);
    return status;
}
