#include <stddef.h>

// The CRT's 36-byte struct tm and locale time-data layouts are read directly
// by this routine.  The larger locale record continues with the three format
// strings, LCID, and the API/fallback selector at offsets 0xa0..0xb0.
struct ExpandTimeFields_0045a82d {
    int second;
    int minute;
    int hour;
    int month_day;
    int month;
    int year_since_1900;
    int week_day;
    int year_day;
    int daylight_saving;
};

struct ExpandTimeLocaleData_0045a82d {
    const char* abbreviated_weekdays[7];
    const char* full_weekdays[7];
    const char* abbreviated_months[12];
    const char* full_months[12];
    const char* am_pm[2];
    const char* date_format;
    const char* alternate_date_format;
    const char* time_format;
    unsigned int locale_id;
    unsigned int use_windows_formatters;
};

extern "C" void __cdecl asm_store_str_0045a75e(
    char** output_cursor,
    unsigned int* remaining_capacity,
    const char* source);
extern "C" int __cdecl asm_store_winword_0045aa93(
    void* crt_locale,
    int format_kind,
    const void* time_fields,
    char** output_cursor,
    unsigned int* remaining_capacity,
    const void* locale_time_data);
extern "C" void __cdecl asm_tzset_004571cf();
extern "C" unsigned char data_004735b0;

namespace {

void store_number_0045a82d(
    char** output_cursor,
    unsigned int* remaining_capacity,
    int value,
    unsigned int width,
    int suppress_zero_padding) {
    if (!suppress_zero_padding) {
        // The retail __store_num path keeps one byte available for the
        // caller's terminating NUL.
        if (width >= *remaining_capacity) {
            *remaining_capacity = 0;
            return;
        }

        char* const first = *output_cursor;
        int quotient = value;
        unsigned int i;
        for (i = 0; i < width; ++i) {
            first[width - i - 1] = (char)(quotient % 10 + '0');
            quotient /= 10;
        }
        *output_cursor += width;
        *remaining_capacity -= width;
        return;
    }

    // The alternate path emits the least-significant digits and reverses
    // them, stopping with one byte reserved whenever it begins a digit.
    if (*remaining_capacity < 2) {
        return;
    }

    char* const first = *output_cursor;
    char* next = first;
    int quotient = value;
    do {
        *next++ = (char)(quotient % 10 + '0');
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

void store_week_number_0045a82d(
    char** output_cursor,
    unsigned int* remaining_capacity,
    const ExpandTimeFields_0045a82d* time_fields,
    int week_starts_monday,
    int suppress_zero_padding) {
    const int first_weekday = week_starts_monday
        ? (time_fields->week_day == 0 ? 6 : time_fields->week_day - 1)
        : time_fields->week_day;

    int week = 0;
    if (time_fields->year_day >= first_weekday) {
        const int quotient = time_fields->year_day / 7;
        const int remainder = time_fields->year_day % 7;
        week = quotient + (remainder >= first_weekday ? 1 : 0);
    }
    store_number_0045a82d(
        output_cursor, remaining_capacity, week, 2, suppress_zero_padding);
}

} // namespace

// 0x0045A82D..0x0045AA92: __expandtime
// Retail uses AL for the conversion, ECX for the output cursor, EBX for the
// capacity counter, and four stack arguments.  Keep the exported region name,
// but make that interface explicit for its converted callers.
extern "C" int __cdecl asm_expandtime_0045a82d(
    signed char conversion,
    char** output_cursor,
    unsigned int* remaining_capacity,
    void* crt_locale,
    const void* time_fields_pointer,
    const void* locale_time_data_pointer,
    int alternate_format) {
    const ExpandTimeFields_0045a82d* const time_fields =
        (const ExpandTimeFields_0045a82d*)time_fields_pointer;
    const ExpandTimeLocaleData_0045a82d* const locale_time_data =
        (const ExpandTimeLocaleData_0045a82d*)locale_time_data_pointer;
    const int suppress_padding = alternate_format != 0;

    switch ((unsigned char)conversion) {
    case '%':
        **output_cursor = '%';
        ++*output_cursor;
        --*remaining_capacity;
        return 1;

    case 'A':
        asm_store_str_0045a75e(
            output_cursor, remaining_capacity,
            locale_time_data->full_weekdays[time_fields->week_day]);
        return 1;
    case 'a':
        asm_store_str_0045a75e(
            output_cursor, remaining_capacity,
            locale_time_data->abbreviated_weekdays[time_fields->week_day]);
        return 1;
    case 'B':
        asm_store_str_0045a75e(
            output_cursor, remaining_capacity,
            locale_time_data->full_months[time_fields->month]);
        return 1;
    case 'b':
        asm_store_str_0045a75e(
            output_cursor, remaining_capacity,
            locale_time_data->abbreviated_months[time_fields->month]);
        return 1;
    case 'p':
        asm_store_str_0045a75e(
            output_cursor, remaining_capacity,
            locale_time_data->am_pm[time_fields->hour > 11 ? 1 : 0]);
        return 1;

    case 'd':
        store_number_0045a82d(output_cursor, remaining_capacity,
                              time_fields->month_day, 2, suppress_padding);
        return 1;
    case 'H':
        store_number_0045a82d(output_cursor, remaining_capacity,
                              time_fields->hour, 2, suppress_padding);
        return 1;
    case 'I': {
        int hour = time_fields->hour % 12;
        if (hour == 0) {
            hour = 12;
        }
        store_number_0045a82d(
            output_cursor, remaining_capacity, hour, 2, suppress_padding);
        return 1;
    }
    case 'j':
        store_number_0045a82d(output_cursor, remaining_capacity,
                              time_fields->year_day + 1, 3, suppress_padding);
        return 1;
    case 'm':
        store_number_0045a82d(output_cursor, remaining_capacity,
                              time_fields->month + 1, 2, suppress_padding);
        return 1;
    case 'M':
        store_number_0045a82d(output_cursor, remaining_capacity,
                              time_fields->minute, 2, suppress_padding);
        return 1;
    case 'S':
        store_number_0045a82d(output_cursor, remaining_capacity,
                              time_fields->second, 2, suppress_padding);
        return 1;
    case 'U':
        store_week_number_0045a82d(output_cursor, remaining_capacity,
                                   time_fields, 0, suppress_padding);
        return 1;
    case 'W':
        store_week_number_0045a82d(output_cursor, remaining_capacity,
                                   time_fields, 1, suppress_padding);
        return 1;
    case 'w':
        store_number_0045a82d(output_cursor, remaining_capacity,
                              time_fields->week_day, 1, suppress_padding);
        return 1;
    case 'y':
        store_number_0045a82d(output_cursor, remaining_capacity,
                              time_fields->year_since_1900 % 100, 2,
                              suppress_padding);
        return 1;
    case 'Y':
        store_number_0045a82d(output_cursor, remaining_capacity,
                              time_fields->year_since_1900 + 1900, 4,
                              suppress_padding);
        return 1;

    case 'Z':
    case 'z': {
        const char* const* const timezone_names =
            (const char* const*)&data_004735b0;
        asm_tzset_004571cf();
        asm_store_str_0045a75e(
            output_cursor, remaining_capacity,
            timezone_names[time_fields->daylight_saving != 0 ? 1 : 0]);
        return 1;
    }

    case 'X':
        return asm_store_winword_0045aa93(
                   crt_locale, 2, time_fields_pointer, output_cursor,
                   remaining_capacity, locale_time_data_pointer) != 0;
    case 'x':
        return asm_store_winword_0045aa93(
                   crt_locale, alternate_format != 0 ? 1 : 0,
                   time_fields_pointer, output_cursor,
                   remaining_capacity, locale_time_data_pointer) != 0;
    case 'c':
        if (!asm_store_winword_0045aa93(
                crt_locale, alternate_format != 0 ? 1 : 0,
                time_fields_pointer, output_cursor,
                remaining_capacity, locale_time_data_pointer) ||
            *remaining_capacity == 0) {
            return 0;
        }
        **output_cursor = ' ';
        ++*output_cursor;
        --*remaining_capacity;
        return asm_store_winword_0045aa93(
                   crt_locale, 2, time_fields_pointer, output_cursor,
                   remaining_capacity, locale_time_data_pointer) != 0;

    default:
        // Unknown conversion letters are consumed by the caller and emit no
        // output in the retail helper.
        return 1;
    }
}
