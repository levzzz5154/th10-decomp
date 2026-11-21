struct CrtWordPair { unsigned int key; unsigned int value; };
extern "C" CrtWordPair crt_libcmt_fpexcept_names_1_get_fname_9_9[29];

// 0x0045E894..0x0045E8B3: Look up a CRT key in the 29-entry table.
extern "C" unsigned int __cdecl crt_unassigned_45e894(unsigned int key) {
    for (int index = 0; index < 29; ++index) {
        if (crt_libcmt_fpexcept_names_1_get_fname_9_9[index].key == key)
            return crt_libcmt_fpexcept_names_1_get_fname_9_9[index].value;
    }
    return 0;
}
