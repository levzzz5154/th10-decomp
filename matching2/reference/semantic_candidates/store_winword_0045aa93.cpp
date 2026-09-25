// 0x0045AA93..0x0045AF1C: __store_winword
// Retail already uses a stack-based cdecl interface here.  The explicit
// declaration below also lets __expandtime call this formatter normally.
struct StoreWinwordFields_0045aa93 {
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

struct StoreWinwordLocaleTime_0045aa93 {
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

struct StoreWinwordSystemTime_0045aa93 {
    unsigned short year;
    unsigned short month;
    unsigned short day_of_week;
    unsigned short day;
    unsigned short hour;
    unsigned short minute;
    unsigned short second;
    unsigned short milliseconds;
};

extern "C" unsigned int __stdcall import_GetDateFormatA_00462658(
    unsigned int locale_id,
    unsigned int flags,
    unsigned int system_time,
    unsigned int format,
    unsigned int output_buffer,
    unsigned int output_capacity);
extern "C" unsigned int __stdcall import_GetTimeFormatA_00462652(
    unsigned int locale_id,
    unsigned int flags,
    unsigned int system_time,
    unsigned int format,
    unsigned int output_buffer,
    unsigned int output_capacity);
extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);
extern "C" void __cdecl asm_free_00452422(void* allocation);
extern "C" int __cdecl asm_expandtime_0045a82d(
    signed char conversion,
    char** output_cursor,
    unsigned int* remaining_capacity,
    void* crt_locale,
    const void* time_fields,
    const void* locale_time_data,
    int alternate_format);

namespace {

int is_dbcs_lead_0045aa93(void* crt_locale, unsigned char value) {
    const unsigned char* const* const table_slot =
        (const unsigned char* const*)((const unsigned char*)crt_locale + 0x48);
    const unsigned char* const character_types = *table_slot;
    return character_types != 0 &&
           (character_types[(unsigned int)value * 2 + 1] & 0x80) != 0;
}

int append_pattern_byte_0045aa93(
    void* crt_locale,
    unsigned char first_byte,
    const unsigned char** source_cursor,
    char** output_cursor,
    unsigned int* remaining_capacity) {
    const unsigned char* cursor = *source_cursor;
    if (is_dbcs_lead_0045aa93(crt_locale, first_byte) &&
        *remaining_capacity > 1) {
        ++cursor;
        if (*cursor == 0) {
            return 0;
        }
        **output_cursor = (char)first_byte;
        ++*output_cursor;
        --*remaining_capacity;
    }

    **output_cursor = (char)*cursor;
    ++*output_cursor;
    ++cursor;
    --*remaining_capacity;
    *source_cursor = cursor;
    return 1;
}

int copy_pattern_string_0045aa93(
    void* crt_locale,
    const char* source,
    char** output_cursor,
    unsigned int* remaining_capacity) {
    const unsigned char* cursor = (const unsigned char*)source;
    while (*cursor != 0 && *remaining_capacity != 0) {
        const unsigned char first_byte = *cursor;
        if (!append_pattern_byte_0045aa93(
                crt_locale, first_byte, &cursor,
                output_cursor, remaining_capacity)) {
            return 0;
        }
    }
    return 1;
}

unsigned char lower_ascii_0045aa93(unsigned char value) {
    if (value >= 'A' && value <= 'Z') {
        return (unsigned char)(value + ('a' - 'A'));
    }
    return value;
}

int pattern_matches_0045aa93(const unsigned char* pattern, const char* text) {
    while (*pattern != 0 && *text != '\0' &&
           lower_ascii_0045aa93(*pattern) ==
               lower_ascii_0045aa93((unsigned char)*text)) {
        ++pattern;
        ++text;
    }
    return *pattern == 0 && *text == '\0';
}

unsigned int call_windows_formatter_0045aa93(
    int format_kind,
    const StoreWinwordFields_0045aa93* time_fields,
    const StoreWinwordLocaleTime_0045aa93* locale_time_data,
    char** output_cursor,
    unsigned int* remaining_capacity) {
    StoreWinwordSystemTime_0045aa93 system_time;
    const char* format;
    unsigned int required;
    unsigned int written;
    unsigned int i;
    char* buffer;

    system_time.year = (unsigned short)(time_fields->year_since_1900 + 1900);
    system_time.month = (unsigned short)(time_fields->month + 1);
    system_time.day_of_week = 0;
    system_time.day = (unsigned short)time_fields->month_day;
    system_time.hour = (unsigned short)time_fields->hour;
    system_time.minute = (unsigned short)time_fields->minute;
    system_time.second = (unsigned short)time_fields->second;
    system_time.milliseconds = 0;

    if (format_kind == 0) {
        format = locale_time_data->date_format;
    } else if (format_kind == 1) {
        format = locale_time_data->alternate_date_format;
    } else {
        format = locale_time_data->time_format;
    }

    if (format_kind == 2) {
        required = import_GetTimeFormatA_00462652(
            locale_time_data->locale_id, 0,
            (unsigned int)&system_time, (unsigned int)format, 0, 0);
    } else {
        required = import_GetDateFormatA_00462658(
            locale_time_data->locale_id, 0,
            (unsigned int)&system_time, (unsigned int)format, 0, 0);
    }
    if (required == 0) {
        return 0;
    }

    buffer = (char*)asm_malloc_00452706(required);
    if (buffer == 0) {
        return 0;
    }

    if (format_kind == 2) {
        written = import_GetTimeFormatA_00462652(
            locale_time_data->locale_id, 0,
            (unsigned int)&system_time, (unsigned int)format,
            (unsigned int)buffer, required);
    } else {
        written = import_GetDateFormatA_00462658(
            locale_time_data->locale_id, 0,
            (unsigned int)&system_time, (unsigned int)format,
            (unsigned int)buffer, required);
    }

    if (written != 0) {
        // The Win32 return count includes its terminator.  __store_winword
        // copies at most count - 1 bytes and leaves NUL termination to its
        // outer strftime caller.
        for (i = 1; i < written && *remaining_capacity != 0; ++i) {
            **output_cursor = buffer[i - 1];
            ++*output_cursor;
            --*remaining_capacity;
        }
    }
    asm_free_00452422(buffer);
    return 1;
}

int expand_locale_pattern_0045aa93(
    void* crt_locale,
    int format_kind,
    const StoreWinwordFields_0045aa93* time_fields,
    char** output_cursor,
    unsigned int* remaining_capacity,
    const StoreWinwordLocaleTime_0045aa93* locale_time_data) {
    const char* format;
    const unsigned char* cursor;

    if (format_kind == 0) {
        format = locale_time_data->date_format;
    } else if (format_kind == 1) {
        format = locale_time_data->alternate_date_format;
    } else {
        format = locale_time_data->time_format;
    }
    cursor = (const unsigned char*)format;

    while (*cursor != 0 && *remaining_capacity != 0) {
        const unsigned char* const run_start = cursor;
        const unsigned char current = *cursor;
        const unsigned char* run_end = cursor;
        unsigned int run_length = 0;
        signed char conversion = 0;
        int alternate = 0;

        while (*run_end == current) {
            ++run_end;
            ++run_length;
        }

        if (current == '\'') {
            cursor = run_end;
            if ((run_length & 1) != 0) {
                while (*cursor != 0 && *remaining_capacity != 0 &&
                       *cursor != '\'') {
                    const unsigned char first_byte = *cursor;
                    if (!append_pattern_byte_0045aa93(
                            crt_locale, first_byte, &cursor,
                            output_cursor, remaining_capacity)) {
                        return 0;
                    }
                }
                if (*cursor == '\'') {
                    ++cursor;
                }
            }
            continue;
        }

        switch (current) {
        case 'd':
            if (run_length == 1) {
                conversion = 'd';
                alternate = 1;
            } else if (run_length == 2) {
                conversion = 'd';
            } else if (run_length == 3) {
                conversion = 'a';
            } else if (run_length == 4) {
                conversion = 'A';
            }
            break;

        case 'a':
        case 'A':
            conversion = 'p';
            if (pattern_matches_0045aa93(run_start, "am/pm")) {
                run_end = run_start + 5;
            } else if (pattern_matches_0045aa93(run_start, "a/p")) {
                run_end = run_start + 3;
            }
            break;

        case 'H':
            if (run_length == 1 || run_length == 2) {
                conversion = 'H';
                alternate = run_length == 1;
            }
            break;

        case 'M':
            if (run_length == 1 || run_length == 2) {
                conversion = 'm';
                alternate = run_length == 1;
            } else if (run_length == 3) {
                conversion = 'b';
            } else if (run_length == 4) {
                conversion = 'B';
            }
            break;

        case 'h':
            if (run_length == 1 || run_length == 2) {
                conversion = 'I';
                alternate = run_length == 1;
            }
            break;

        case 'm':
            if (run_length == 1 || run_length == 2) {
                conversion = 'M';
                alternate = run_length == 1;
            }
            break;

        case 's':
            if (run_length == 1 || run_length == 2) {
                conversion = 'S';
                alternate = run_length == 1;
            }
            break;

        case 't': {
            const char* const am_pm =
                locale_time_data->am_pm[time_fields->hour < 12 ? 0 : 1];
            cursor = run_end;
            if (run_length == 1) {
                if (*remaining_capacity != 0) {
                    const unsigned char* am_cursor =
                        (const unsigned char*)am_pm;
                    if (*am_cursor != 0) {
                        const unsigned char first_byte = *am_cursor;
                        if (!append_pattern_byte_0045aa93(
                                crt_locale, first_byte, &am_cursor,
                                output_cursor, remaining_capacity)) {
                            return 0;
                        }
                    }
                }
            } else if (!copy_pattern_string_0045aa93(
                           crt_locale, am_pm,
                           output_cursor, remaining_capacity)) {
                return 0;
            }
            continue;
        }

        case 'y':
            if (run_length == 2) {
                conversion = 'y';
            } else if (run_length == 4) {
                conversion = 'Y';
            }
            break;

        default:
            break;
        }

        if (conversion != 0) {
            if (!asm_expandtime_0045a82d(
                    conversion, output_cursor, remaining_capacity,
                    crt_locale, time_fields, locale_time_data, alternate)) {
                return 0;
            }
            cursor = run_end;
            continue;
        }

        // Unrecognized runs are literal text.  Advance one code page
        // character at a time so lead bytes follow the retail capacity rule.
        cursor = run_start;
        while (cursor < run_end && *remaining_capacity != 0) {
            const unsigned char first_byte = *cursor;
            if (!append_pattern_byte_0045aa93(
                    crt_locale, first_byte, &cursor,
                    output_cursor, remaining_capacity)) {
                return 0;
            }
        }
    }
    return 1;
}

} // namespace

extern "C" int __cdecl asm_store_winword_0045aa93(
    void* crt_locale,
    int format_kind,
    const void* time_fields_pointer,
    char** output_cursor,
    unsigned int* remaining_capacity,
    const void* locale_time_data_pointer) {
    const StoreWinwordFields_0045aa93* const time_fields =
        (const StoreWinwordFields_0045aa93*)time_fields_pointer;
    const StoreWinwordLocaleTime_0045aa93* const locale_time_data =
        (const StoreWinwordLocaleTime_0045aa93*)locale_time_data_pointer;

    if (locale_time_data->use_windows_formatters != 1 &&
        call_windows_formatter_0045aa93(
            format_kind, time_fields, locale_time_data,
            output_cursor, remaining_capacity)) {
        return 1;
    }

    return expand_locale_pattern_0045aa93(
        crt_locale, format_kind, time_fields, output_cursor,
        remaining_capacity, locale_time_data);
}
