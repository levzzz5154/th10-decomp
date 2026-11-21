struct DoubleWords { unsigned int low; unsigned int high; };
extern "C" void __cdecl crt_helper_45d676(DoubleWords*, const char*);
extern "C" void __cdecl crt_helper_45d701(int*, const char*);

extern "C" void __cdecl crt_fassign(int flag, void* destination, const char* number) {
    DoubleWords value;
    if (flag != 0) {
        crt_helper_45d676(&value, number);
        *static_cast<DoubleWords*>(destination) = value;
    } else {
        crt_helper_45d701(&flag, number);
        *static_cast<int*>(destination) = flag;
    }
}
