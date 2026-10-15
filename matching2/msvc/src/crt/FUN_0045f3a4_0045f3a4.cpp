extern "C" unsigned int data_00477698;

// 0x0045F3A4..0x0045F3B3: Replace a global value and return its old value.
extern "C" unsigned int __cdecl asm_FUN_0045f3a4_0045f3a4(unsigned int value) {
    unsigned int previous = data_00477698;
    data_00477698 = value;
    return previous;
}
