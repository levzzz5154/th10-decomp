#pragma code_seg(".text$13query")
__declspec(noinline) int PlatformQueryInterfaces_0044D600::Query() {
    if (entries_004 == 0) return (int)0x800401F0u;
    int result = 0;
    for (unsigned int index = 0; index < count_010; ++index) {
        void* entry = entries_004[index];
        void** vtable = *reinterpret_cast<void***>(entry);
        result |= reinterpret_cast<RecoveryLeafD600Query>(
            vtable[0x34 / 4])(entry, 0);
    }
    return result;
}
#pragma code_seg()
