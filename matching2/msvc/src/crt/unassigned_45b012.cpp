extern "C" unsigned int __cdecl crt_Strftime(char* destination, unsigned int capacity, const char* format, const void* time, void* locale);

extern "C" unsigned int __cdecl crt_unassigned_45b012(char* destination, unsigned int capacity, const char* format, const void* time) {
    return crt_Strftime(destination, capacity, format, time, 0);
}
