#include <cstddef>
#include <cstdint>

extern "C" std::uint32_t data_00473660;
extern "C" void __fastcall asm_security_check_cookie_00458ea5(
    std::uint32_t stack_cookie);

// These CRT arithmetic helpers are separate retail functions. The shift and
// 96-bit addition helpers are already represented by ordinary C++ sources;
// the two extended-float scaling helpers still have assembly implementations.
extern "C" void __cdecl asm_FUN_00460b90_00460b90(
    std::uint32_t words[3], std::int32_t decimal_power, int preserve_exponent);
extern "C" void __cdecl asm_FUN_0046095a_0046095a(
    std::uint32_t destination[3], const std::uint32_t source[3]);
extern "C" void __cdecl asm_shl_12_00460817(std::uint32_t words[3]);
extern "C" void __cdecl asm_shr_12_00460845(std::uint32_t words[3]);
extern "C" void __cdecl asm_add_12_004607b9(
    std::uint32_t destination[3], const std::uint32_t source[3]);

struct DecimalConversionRecord_00461841 {
    std::int16_t exponent;
    char sign;
    std::uint8_t digit_count;
    char digits[20];
};

namespace {

struct Extended96 {
    // A little-endian three-word integer. The retail 80-bit value is laid out
    // at bytes 2..11, leaving two low padding bytes in this 96-bit workspace.
    std::uint32_t words[3];
};

static_assert(offsetof(DecimalConversionRecord_00461841, digits) == 4,
              "the retail digit field starts four bytes into the record");
static_assert(sizeof(DecimalConversionRecord_00461841) == 24,
              "the retail conversion scratch record is six dwords");
static_assert(sizeof(Extended96) == 12,
              "the arithmetic helpers operate on three dwords");

std::int32_t signed_word(std::uint16_t value) {
    if (value < 0x8000u) {
        return static_cast<std::int32_t>(value);
    }
    return static_cast<std::int32_t>(value) - 0x10000;
}

std::int32_t wrap_add(std::int32_t left, std::int16_t right) {
    const std::uint32_t bits = static_cast<std::uint32_t>(left) +
        static_cast<std::uint32_t>(static_cast<std::int32_t>(right));
    if ((bits & 0x80000000u) == 0) {
        return static_cast<std::int32_t>(bits);
    }
    return -1 - static_cast<std::int32_t>(~bits);
}

void write_zero(DecimalConversionRecord_00461841* record) {
    record->exponent = 0;
    record->sign = ' ';
    record->digit_count = 1;
    record->digits[0] = '0';
    record->digits[1] = '\0';
}

void write_special(DecimalConversionRecord_00461841* record, const char* text,
                   std::uint8_t length) {
    record->exponent = 1;
    record->digit_count = length;
    for (std::uint8_t index = 0; index <= length; ++index) {
        record->digits[index] = text[index];
    }
}

}  // namespace

// Converts an 80-bit extended value, passed as its three retail stack words,
// into a decimal exponent, sign, count, and rounded digit string. The six
// arguments and return status match the cdecl entry at 0x00461841.
extern "C" __declspec(noinline) int __cdecl asm_FUN_00461841_00461841(
    std::uint32_t significand_low,
    std::uint32_t significand_high,
    std::uint16_t sign_and_exponent,
    std::int32_t requested_digits,
    std::uint8_t flags,
    DecimalConversionRecord_00461841* output) {
    volatile std::uint32_t saved_cookie = 0;
    const std::uintptr_t cookie_anchor =
        reinterpret_cast<std::uintptr_t>(&saved_cookie);
    saved_cookie = data_00473660 ^ static_cast<std::uint32_t>(cookie_anchor);

    const std::uint16_t binary_exponent =
        static_cast<std::uint16_t>(sign_and_exponent & 0x7fffu);
    const bool negative = (sign_and_exponent & 0x8000u) != 0;
    output->sign = negative ? '-' : ' ';

    int status = 1;
    if (binary_exponent == 0x7fffu) {
        const bool exact_infinity =
            significand_high == 0x80000000u && significand_low == 0;
        const bool quiet_nan = (significand_high & 0x40000000u) != 0;
        if (!exact_infinity && !quiet_nan) {
            write_special(output, "1#SNAN", 6);
        } else if (negative && significand_high == 0xc0000000u) {
            if (significand_low == 0) {
                write_special(output, "1#IND", 5);
            } else {
                write_special(output, "1#QNAN", 6);
            }
        } else if (exact_infinity) {
            write_special(output, "1#INF", 5);
        } else {
            write_special(output, "1#QNAN", 6);
        }
        status = 0;
    } else if (binary_exponent == 0 && significand_high == 0 &&
               significand_low == 0) {
        // Retail normalizes both positive and negative zero to a blank sign.
        write_zero(output);
    } else {
        // The stack workspace begins with two zero bytes, followed by the
        // 64-bit significand and the sign/exponent word at byte offset ten.
        Extended96 scaled = {{
            (significand_low & 0xffffu) << 16,
            (significand_low >> 16) | ((significand_high & 0xffffu) << 16),
            ((significand_high >> 16) & 0xffffu) |
                (static_cast<std::uint32_t>(binary_exponent) << 16),
        }};

        // Integer fixed-point approximation to the binary-to-decimal exponent.
        const std::uint32_t exponent_product =
            static_cast<std::uint32_t>(binary_exponent) * 0x4d10u +
            (static_cast<std::uint32_t>(binary_exponent >> 8) +
             ((significand_high >> 24) << 1)) * 0x4du + 0xecbced0cu;
        const std::int32_t approximate_exponent =
            signed_word(static_cast<std::uint16_t>(exponent_product >> 16));
        std::int16_t decimal_exponent = static_cast<std::int16_t>(
            approximate_exponent);

        // Multiply by the table value 10^(-decimal_exponent). The called CRT
        // helper handles its signed power through the retail power tables.
        asm_FUN_00460b90_00460b90(
            scaled.words, -static_cast<std::int32_t>(decimal_exponent), 1);

        // The scaled significand is kept below one for digit extraction. When
        // its exponent is at least one, advance the decimal exponent and add
        // the retail 0.8 rounding bias before repeatedly multiplying by ten.
        if (static_cast<std::uint16_t>(scaled.words[2] >> 16) >= 0x3fffu) {
            decimal_exponent = static_cast<std::int16_t>(decimal_exponent + 1);
            const std::uint32_t rounding_bias[3] = {
                0xccccccccu, 0xccccccccu, 0x3ffbccccu,
            };
            asm_FUN_0046095a_0046095a(scaled.words, rounding_bias);
        }

        output->exponent = decimal_exponent;
        if ((flags & 1u) != 0) {
            requested_digits = wrap_add(requested_digits, decimal_exponent);
            if (requested_digits < 1) {
                write_zero(output);
                goto conversion_done;
            }
        }
        if (requested_digits > 21) {
            requested_digits = 21;
        }

        // Remove the encoded exponent, then shift the significand into the
        // 96-bit fractional position used by the retail repeated-digit loop.
        const std::int32_t binary_shift =
            static_cast<std::int32_t>(scaled.words[2] >> 16) - 0x3ffe;
        scaled.words[2] &= 0xffffu;
        for (int index = 0; index != 8; ++index) {
            asm_shl_12_00460817(scaled.words);
        }
        if (binary_shift < 0) {
            const std::uint8_t right_shifts =
                static_cast<std::uint8_t>(-binary_shift);
            for (std::uint16_t index = 0; index != right_shifts; ++index) {
                asm_shr_12_00460845(scaled.words);
            }
        }

        // One additional digit is the guard digit used by the retail rounding
        // and trailing-zero removal logic.
        for (std::int32_t index = 0; index <= requested_digits; ++index) {
            const Extended96 previous = scaled;
            asm_shl_12_00460817(scaled.words);
            asm_shl_12_00460817(scaled.words);
            asm_add_12_004607b9(scaled.words, previous.words);
            asm_shl_12_00460817(scaled.words);
            output->digits[index] = static_cast<char>(
                static_cast<unsigned char>(scaled.words[2] >> 24) + '0');
            scaled.words[2] &= 0x00ffffffu;
        }

        std::int32_t last_kept_digit = requested_digits - 1;
        if (output->digits[requested_digits] < '5') {
            while (last_kept_digit >= 0 &&
                   output->digits[last_kept_digit] == '0') {
                --last_kept_digit;
            }
            if (last_kept_digit < 0) {
                output->digits[0] = '0';
                write_zero(output);
                goto conversion_done;
            }
        } else {
            while (last_kept_digit >= 0 &&
                   output->digits[last_kept_digit] == '9') {
                output->digits[last_kept_digit] = '0';
                --last_kept_digit;
            }
            if (last_kept_digit < 0) {
                last_kept_digit = 0;
                output->exponent = static_cast<std::int16_t>(
                    output->exponent + 1);
            }
            ++output->digits[last_kept_digit];
        }

        output->digit_count = static_cast<std::uint8_t>(last_kept_digit + 1);
        output->digits[last_kept_digit + 1] = '\0';
    }

conversion_done:
    const std::uint32_t decoded_cookie = saved_cookie ^
        static_cast<std::uint32_t>(cookie_anchor);
    asm_security_check_cookie_00458ea5(decoded_cookie);
    return status;
}
