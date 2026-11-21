struct ScanStream {
    char* ptr;
    int count;
    char* base;
    int flags;
    unsigned int padding[4];
};
extern "C" unsigned int __cdecl asm_strlen_00456720(const char*);
extern "C" int __cdecl asm_FUN_00457a7c_00457a7c(ScanStream*, const char*, void*);

extern "C" int __cdecl crt_sscanf(char* input, const char* format, ...) {
    ScanStream stream;
    stream.flags = 0x49;
    stream.base = input;
    stream.ptr = input;
    stream.count = asm_strlen_00456720(input);
    return asm_FUN_00457a7c_00457a7c(&stream, format, &format + 1);
}
