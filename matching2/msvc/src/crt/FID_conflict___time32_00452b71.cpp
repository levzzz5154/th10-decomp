struct FileTime { unsigned int low; unsigned int high; };
extern "C" void (__stdcall *data_004661b0)(FileTime*);

extern "C" unsigned int __cdecl asm_FID_conflict___time32_00452b71(unsigned int* output) {
    FileTime time;
    data_004661b0(&time);
    unsigned long long ticks = *reinterpret_cast<unsigned long long*>(&time);
    unsigned int seconds = static_cast<unsigned int>((ticks + 0xfe624e212ac18000ULL) / 10000000ULL);
    if (output) *output = seconds;
    return seconds;
}
