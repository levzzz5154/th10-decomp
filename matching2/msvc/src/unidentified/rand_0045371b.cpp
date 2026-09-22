struct ThreadData { unsigned char padding[0x14]; unsigned int holdrand; };
extern "C" ThreadData* __cdecl asm_getptd_00456357();

extern "C" int __cdecl asm_rand_0045371b() {
    ThreadData* data = asm_getptd_00456357();
    data->holdrand = data->holdrand * 0x343fdu + 0x269ec3u;
    return (data->holdrand >> 16) & 0x7fff;
}
