struct PrintStream {
    char* ptr;
    int count;
    char* base;
    int flags;
    unsigned int padding[4];
};
extern "C" int __cdecl asm_FUN_00454ed7_00454ed7(PrintStream*, const char*, void*);
extern "C" int __cdecl asm_flsbuf_00454d11(int, PrintStream*);

extern "C" int __cdecl asm_vsprintf_004524a6(char* destination, const char* format, void* arguments) {
    PrintStream stream;
    stream.count = 0x7fffffff;
    stream.flags = 0x42;
    stream.base = destination;
    stream.ptr = destination;
    int written = asm_FUN_00454ed7_00454ed7(&stream, format, arguments);
    if (destination) {
        if (--stream.count >= 0) *stream.ptr = 0;
        else asm_flsbuf_00454d11(0, &stream);
    }
    return written;
}
