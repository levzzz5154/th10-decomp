extern "C" char* __cdecl crt_strcat(
    char* destination, const char* source);

extern "C" void __cdecl crt_strcats(void* destination, int count, ...) {
    int remaining = count;
    if (remaining > 0) {
        int* argument = &count;
        do {
            ++argument;
            crt_strcat(
                static_cast<char*>(destination),
                reinterpret_cast<const char*>(*argument));
            --remaining;
        } while (remaining != 0);
    }
}
