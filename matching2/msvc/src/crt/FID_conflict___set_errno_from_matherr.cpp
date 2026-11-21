extern "C" int* __cdecl crt_errno();

// 0x0045E86C..0x0045E893: Set errno for a CRT math error class.
extern "C" unsigned int __cdecl
crt_set_errno(int value) {
    if (value != 1) {
        if (value <= 1) return value;
        if (value > 3) return value;
        int* error = crt_errno();
        *error = 0x22;
        return reinterpret_cast<unsigned int>(error);
    }
    int* error = crt_errno();
    *error = 0x21;
    return reinterpret_cast<unsigned int>(error);
}
