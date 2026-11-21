struct PrintStream {
    char* ptr;
    int count;
    char* base;
    int flags;
    unsigned int padding[4];
};
extern "C" int __cdecl crt_helper_454ed7(PrintStream*, const char*, void*);
extern "C" int __cdecl crt_flsbuf(int, PrintStream*);

extern "C" int __cdecl crt_sprintf(char* destination, const char* format, ...) {
    PrintStream stream;
    stream.count = 0x7fffffff;
    stream.flags = 0x42;
    stream.base = destination;
    stream.ptr = destination;
    int written = crt_helper_454ed7(&stream, format, &format + 1);
    if (destination) {
        if (--stream.count >= 0) *stream.ptr = 0;
        else crt_flsbuf(0, &stream);
    }
    return written;
}
