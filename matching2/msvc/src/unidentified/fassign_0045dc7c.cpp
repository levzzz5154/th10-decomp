struct DoubleWords { unsigned int low; unsigned int high; };
extern "C" void __cdecl asm_FUN_0045d676_0045d676(DoubleWords*, const char*);
extern "C" void __cdecl asm_FUN_0045d701_0045d701(int*, const char*);

extern "C" void __cdecl asm_fassign_0045dc7c(int flag, void* destination, const char* number) {
    DoubleWords value;
    if (flag != 0) {
        asm_FUN_0045d676_0045d676(&value, number);
        *static_cast<DoubleWords*>(destination) = value;
    } else {
        asm_FUN_0045d701_0045d701(&flag, number);
        *static_cast<int*>(destination) = flag;
    }
}
