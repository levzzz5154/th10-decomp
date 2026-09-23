// Semantic model for 0x004559B4..0x00455A8F (___lc_strtolc).
extern "C" void* __cdecl asm_memset_0045bed0(
    void* destination, int value, unsigned int count);
extern "C" char* __cdecl asm_strncpy_00452960(
    char* destination, const char* source, unsigned int count);
extern "C" unsigned int __cdecl asm_strcspn_0045be80(
    const unsigned char* string, const unsigned char* reject);

extern "C" int __cdecl asm_lc_strtolc_004559b4(char* fields,
                                                 const char* text) {
    static const unsigned char separators[] = { '_', '.', ',', 0 };

    asm_memset_0045bed0(fields, 0, 0x90);

    if (*text == '\0') {
        return 0;
    }

    // A leading period is a special spelling of the final field.
    if (text[0] == '.' && text[1] != '\0') {
        asm_strncpy_00452960(fields + 0x80, text + 1, 0x0f);
        fields[0x8f] = '\0';
        return 0;
    }

    unsigned int field_index = 0;
    const char* field_text = text;
    for (;;) {
        const unsigned int length = asm_strcspn_0045be80(
            (const unsigned char*)field_text, separators);
        if (length == 0) {
            return -1;
        }

        const char separator = field_text[length];
        char* destination;
        if (field_index == 0) {
            if (length >= 0x40 || separator == '.') {
                return -1;
            }
            destination = fields;
        } else if (field_index == 1) {
            if (length >= 0x40 || separator == '_') {
                return -1;
            }
            destination = fields + 0x40;
        } else if (field_index == 2) {
            if (length >= 0x10 ||
                (separator != '\0' && separator != ',')) {
                return -1;
            }
            destination = fields + 0x80;
        } else {
            return -1;
        }

        asm_strncpy_00452960(destination, field_text, length);
        if (separator == ',' || separator == '\0') {
            return 0;
        }

        ++field_index;
        field_text += length + 1;
    }
}
