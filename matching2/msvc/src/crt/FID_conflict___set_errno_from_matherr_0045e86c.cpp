extern "C" int* __cdecl asm_FUN_00456af2_00456af2();

// 0x0045E86C..0x0045E893: Set errno for a CRT math error class.
extern "C" unsigned int __cdecl
asm_FID_conflict___set_errno_from_matherr_0045e86c(int value) {
    if (value != 1) {
        if (value <= 1) return value;
        if (value > 3) return value;
        int* error = asm_FUN_00456af2_00456af2();
        *error = 0x22;
        return reinterpret_cast<unsigned int>(error);
    }
    int* error = asm_FUN_00456af2_00456af2();
    *error = 0x21;
    return reinterpret_cast<unsigned int>(error);
}
