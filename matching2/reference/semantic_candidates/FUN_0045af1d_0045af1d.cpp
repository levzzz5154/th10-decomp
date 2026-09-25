// 0x0045AF1D..0x0045AFDF: FUN_0045af1d
// This is the public strftime worker.  Its region symbol keeps the existing
// C name and stack ABI while the formerly register-only __expandtime call is
// now expressed through its explicit typed interface.
extern "C" int __cdecl asm_expandtime_0045a82d(
    signed char conversion,
    char** output_cursor,
    unsigned int* remaining_capacity,
    void* crt_locale,
    const void* time_fields,
    const void* locale_time_data,
    int alternate_format);

namespace {

int is_dbcs_lead_0045af1d(void* crt_locale, unsigned char value) {
    const unsigned char* const* const table_slot =
        (const unsigned char* const*)((const unsigned char*)crt_locale + 0x48);
    const unsigned char* const character_types = *table_slot;
    return character_types != 0 &&
           (character_types[(unsigned int)value * 2 + 1] & 0x80) != 0;
}

} // namespace

extern "C" unsigned int __cdecl asm_FUN_0045af1d_0045af1d(
    void* crt_locale,
    char* output,
    unsigned int capacity,
    const char* format,
    const void* time_fields,
    void* locale_time_data) {
    char* const initial_output = output;
    unsigned int remaining = capacity;
    const unsigned char* cursor = (const unsigned char*)format;

    if (locale_time_data == 0) {
        locale_time_data = *(void**)((unsigned char*)crt_locale + 0x4c);
    }

    if (capacity == 0) {
        return 0;
    }

    while (remaining != 0 && *cursor != 0) {
        const unsigned char current = *cursor;
        if (current == '%') {
            int alternate = 0;
            ++cursor;
            if (*cursor == '#') {
                alternate = 1;
                ++cursor;
            }
            if (!asm_expandtime_0045a82d(
                    (signed char)*cursor, &output, &remaining,
                    crt_locale, time_fields, locale_time_data, alternate)) {
                *initial_output = '\0';
                return 0;
            }
            ++cursor;
            continue;
        }

        if (is_dbcs_lead_0045af1d(crt_locale, current) && remaining > 1) {
            ++cursor;
            if (*cursor == 0) {
                *initial_output = '\0';
                return 0;
            }
            *output++ = (char)current;
            --remaining;
        }
        *output++ = (char)*cursor;
        ++cursor;
        --remaining;
    }

    if (remaining != 0) {
        *output = '\0';
        return capacity - remaining;
    }

    return 0;
}
