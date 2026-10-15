// 0x00456344..0x00456356: Initialize the thread-local CRT data.
extern "C" void __cdecl asm_initptd_00456344(void* thread_data, void* locale) {
    (void)locale;
    unsigned char* data = static_cast<unsigned char*>(thread_data);
    *reinterpret_cast<unsigned int*>(data + 0x54) = 0x004735d0;
    *reinterpret_cast<unsigned int*>(data + 0x14) = 1;
}
