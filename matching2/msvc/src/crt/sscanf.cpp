struct ScanStream {
    char* ptr;
    int count;
    char* base;
    int flags;
    unsigned int padding[4];
};
extern "C" unsigned int __cdecl crt_strlen(const char*);
extern "C" int __cdecl crt_helper_457a7c(ScanStream*, const char*, void*);

extern "C" int __cdecl crt_sscanf(char* input, const char* format, ...) {
    ScanStream stream;
    stream.flags = 0x49;
    stream.base = input;
    stream.ptr = input;
    stream.count = crt_strlen(input);
    return crt_helper_457a7c(&stream, format, &format + 1);
}
