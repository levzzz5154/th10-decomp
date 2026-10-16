extern "C" unsigned int __cdecl asm_Strftime_0045afe0(char* destination, unsigned int capacity, const char* format, const void* time, void* locale);

extern "C" unsigned int __cdecl asm_unassigned_0045b012(char* destination, unsigned int capacity, const char* format, const void* time) {
    return asm_Strftime_0045afe0(destination, capacity, format, time, 0);
}
