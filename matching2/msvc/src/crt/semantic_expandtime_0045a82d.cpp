#include <cstddef>
#include <cstdint>

// A 32-bit CRT struct tm as read by __expandtime.  The retail function uses
// all nine dwords, including tm_isdst at offset 0x20.
struct ExpandTimeFields_0045a82d {
    std::int32_t second;
    std::int32_t minute;
    std::int32_t hour;
    std::int32_t month_day;
    std::int32_t month;
    std::int32_t year_since_1900;
    std::int32_t week_day;
    std::int32_t year_day;
    std::int32_t daylight_saving;
};

static_assert(sizeof(ExpandTimeFields_0045a82d) == 0x24,
              "the CRT time fields must match the observed 36-byte layout");

// The CRT __lc_time_data string table used by %a/%A/%b/%B/%p.  These offsets
// are the ones read by the retail instructions at 0x0045A88D..0x0045AA83.
struct ExpandTimeLocaleStrings_0045a82d {
    const char* abbreviated_weekdays[7]; // +0x00
    const char* full_weekdays[7];        // +0x1C
    const char* abbreviated_months[12];  // +0x38
    const char* full_months[12];          // +0x68
    const char* am_pm[2];                 // +0x98
};

using StoreLocalizedWord_0045a82d = int(__cdecl*)(
    const void* crt_locale,
    int format_kind,
    const ExpandTimeFields_0045a82d* time_fields,
    char** output_cursor,
    std::uint32_t* remaining_capacity,
    const ExpandTimeLocaleStrings_0045a82d* locale_strings);

using RefreshTimeZone_0045a82d = void(__cdecl*)();

extern "C" void semantic_store_str_0045a75e(
    char** output_cursor,
    std::uint32_t* remaining_capacity,
    const char* source);

namespace {

void store_number(
    char** output_cursor,
    std::uint32_t* remaining_capacity,
    std::int32_t value,
    unsigned width,
    bool suppress_zero_padding) {
    if (!suppress_zero_padding) {
        // __store_num only emits a fixed-width value when one extra byte is
        // available for the caller's eventual NUL terminator.
        if (width >= *remaining_capacity) {
            *remaining_capacity = 0;
            return;
        }

        char* const first = *output_cursor;
        std::int32_t quotient = value;
        for (unsigned i = 0; i < width; ++i) {
            first[width - i - 1] = static_cast<char>(quotient % 10 + '0');
            quotient /= 10;
        }
        *output_cursor += width;
        *remaining_capacity -= width;
        return;
    }

    // The alternate form writes least-significant digits first, then reverses
    // them in place.  Retail checks for two bytes up front and relies on the
    // caller to provide enough room for this conversion's full digit count.
    if (*remaining_capacity < 2) {
        return;
    }

    char* const first = *output_cursor;
    char* next = first;
    std::int32_t quotient = value;
    do {
        *next++ = static_cast<char>(quotient % 10 + '0');
        --*remaining_capacity;
        quotient /= 10;
    } while (quotient > 0);
    *output_cursor = next;

    char* left = first;
    char* right = next - 1;
    while (left < right) {
        const char digit = *left;
        *left++ = *right;
        *right-- = digit;
    }
}

void store_week_number(
    char** output_cursor,
    std::uint32_t* remaining_capacity,
    const ExpandTimeFields_0045a82d* time_fields,
    bool week_starts_monday,
    bool suppress_zero_padding) {
    const std::int32_t first_weekday = week_starts_monday
        ? (time_fields->week_day == 0 ? 6 : time_fields->week_day - 1)
        : time_fields->week_day;

    std::int32_t week = 0;
    if (time_fields->year_day >= first_weekday) {
        const std::int32_t quotient = time_fields->year_day / 7;
        const std::int32_t remainder = time_fields->year_day % 7;
        week = quotient + (remainder >= first_weekday ? 1 : 0);
    }
    store_number(output_cursor, remaining_capacity, week, 2, suppress_zero_padding);
}

} // namespace

// Semantic model of the CRT __expandtime helper at 0x0045A82D.
//
// This is deliberately not named asm_expandtime_0045a82d: the retail ABI has
// no ordinary MSVC spelling.  AL carries the token, ECX points to the output
// cursor, EBX points to the remaining-capacity count, and four values are on
// the stack.  The typed parameters below make those values explicit for a
// future caller conversion.  `store_localized_word` and `refresh_timezone`
// stand for the normal-ABI CRT helpers used by the original implementation.
extern "C" int semantic_expandtime_0045a82d(
    std::int8_t conversion,
    char** output_cursor,
    std::uint32_t* remaining_capacity,
    const void* crt_locale,
    const ExpandTimeFields_0045a82d* time_fields,
    const ExpandTimeLocaleStrings_0045a82d* locale_strings,
    int alternate_format,
    const char* const* timezone_names,
    StoreLocalizedWord_0045a82d store_localized_word,
    RefreshTimeZone_0045a82d refresh_timezone) {
    const bool suppress_padding = alternate_format != 0;

    switch (conversion) {
    case '%':
        // The retail caller only enters this helper while capacity is nonzero.
        **output_cursor = '%';
        ++*output_cursor;
        --*remaining_capacity;
        return 1;

    case 'A':
        semantic_store_str_0045a75e(
            output_cursor, remaining_capacity,
            locale_strings->full_weekdays[time_fields->week_day]);
        return 1;
    case 'a':
        semantic_store_str_0045a75e(
            output_cursor, remaining_capacity,
            locale_strings->abbreviated_weekdays[time_fields->week_day]);
        return 1;
    case 'B':
        semantic_store_str_0045a75e(
            output_cursor, remaining_capacity,
            locale_strings->full_months[time_fields->month]);
        return 1;
    case 'b':
        semantic_store_str_0045a75e(
            output_cursor, remaining_capacity,
            locale_strings->abbreviated_months[time_fields->month]);
        return 1;
    case 'p':
        semantic_store_str_0045a75e(
            output_cursor, remaining_capacity,
            locale_strings->am_pm[time_fields->hour > 11 ? 1 : 0]);
        return 1;

    case 'd':
        store_number(output_cursor, remaining_capacity,
                     time_fields->month_day, 2, suppress_padding);
        return 1;
    case 'H':
        store_number(output_cursor, remaining_capacity,
                     time_fields->hour, 2, suppress_padding);
        return 1;
    case 'I': {
        std::int32_t hour = time_fields->hour % 12;
        if (hour == 0) {
            hour = 12;
        }
        store_number(output_cursor, remaining_capacity, hour, 2, suppress_padding);
        return 1;
    }
    case 'j':
        store_number(output_cursor, remaining_capacity,
                     time_fields->year_day + 1, 3, suppress_padding);
        return 1;
    case 'm':
        store_number(output_cursor, remaining_capacity,
                     time_fields->month + 1, 2, suppress_padding);
        return 1;
    case 'M':
        store_number(output_cursor, remaining_capacity,
                     time_fields->minute, 2, suppress_padding);
        return 1;
    case 'S':
        store_number(output_cursor, remaining_capacity,
                     time_fields->second, 2, suppress_padding);
        return 1;
    case 'U':
        store_week_number(output_cursor, remaining_capacity,
                          time_fields, false, suppress_padding);
        return 1;
    case 'W':
        store_week_number(output_cursor, remaining_capacity,
                          time_fields, true, suppress_padding);
        return 1;
    case 'w':
        store_number(output_cursor, remaining_capacity,
                     time_fields->week_day, 1, suppress_padding);
        return 1;
    case 'y':
        store_number(output_cursor, remaining_capacity,
                     time_fields->year_since_1900 % 100, 2, suppress_padding);
        return 1;
    case 'Y':
        store_number(output_cursor, remaining_capacity,
                     time_fields->year_since_1900 + 1900, 4, suppress_padding);
        return 1;

    case 'Z':
    case 'z':
        if (refresh_timezone != nullptr) {
            refresh_timezone();
        }
        semantic_store_str_0045a75e(
            output_cursor, remaining_capacity,
            timezone_names[time_fields->daylight_saving != 0 ? 1 : 0]);
        return 1;

    case 'X':
        return store_localized_word != nullptr
            ? store_localized_word(crt_locale, 2, time_fields,
                                   output_cursor, remaining_capacity, locale_strings) != 0
            : 0;
    case 'x':
        return store_localized_word != nullptr
            ? store_localized_word(crt_locale, alternate_format != 0 ? 1 : 0, time_fields,
                                   output_cursor, remaining_capacity, locale_strings) != 0
            : 0;
    case 'c':
        if (store_localized_word == nullptr ||
            !store_localized_word(crt_locale, alternate_format != 0 ? 1 : 0, time_fields,
                                  output_cursor, remaining_capacity, locale_strings) ||
            *remaining_capacity == 0) {
            return 0;
        }
        **output_cursor = ' ';
        ++*output_cursor;
        --*remaining_capacity;
        return store_localized_word(crt_locale, 2, time_fields,
                                    output_cursor, remaining_capacity, locale_strings) != 0;

    default:
        // Unknown tokens are consumed by the caller and emit no bytes.
        return 1;
    }
}
