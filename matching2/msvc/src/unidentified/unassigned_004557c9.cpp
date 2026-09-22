struct ThreadData { unsigned char padding[0x64]; void* locale; };
extern "C" ThreadData* __cdecl asm_getptd_00456357();
extern "C" void* __cdecl asm_updatetlocinfo_00455ade();
extern "C" void* data_0047320c;
extern "C" int __cdecl asm_isctype_mt_00455752(void* locale, int character, int mask);

extern "C" int __cdecl asm_unassigned_004557c9(int character, int mask) {
    void* locale = asm_getptd_00456357()->locale;
    if (locale != data_0047320c) locale = asm_updatetlocinfo_00455ade();
    return asm_isctype_mt_00455752(locale, character, mask);
}
