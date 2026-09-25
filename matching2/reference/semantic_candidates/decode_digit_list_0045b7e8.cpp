// Retail 0x0045B7E8..0x0045B81A receives a mutable string in ECX.
// Decimal ASCII digits become binary values 0..9; semicolons are removed.
extern "C" void __cdecl DecodeDigitListInPlace_0045b7e8(char* text) {
    for (char* cursor = text; *cursor != '\0'; ) {
        const char value = *cursor;
        if (value >= '0' && value <= '9') {
            *cursor++ = static_cast<char>(value - '0');
        } else if (value == ';') {
            char* destination = cursor;
            do {
                *destination = destination[1];
                ++destination;
            } while (*destination != '\0');
        } else {
            ++cursor;
        }
    }
}
