struct ThreadData { unsigned char padding[0x14]; unsigned int holdrand; };
extern "C" ThreadData* __cdecl crt_getptd();

extern "C" int __cdecl crt_rand() {
    ThreadData* data = crt_getptd();
    data->holdrand = data->holdrand * 0x343fdu + 0x269ec3u;
    return (data->holdrand >> 16) & 0x7fff;
}
