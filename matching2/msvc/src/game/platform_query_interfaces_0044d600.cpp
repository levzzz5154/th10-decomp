// 0x0044D600 - Rewind each DirectSound buffer with SetCurrentPosition(0),
// combining their HRESULTs with OR. The historical Query name is retained.
// Native LTCG gives this member's internal receiver convention: the state
// arrives in EDI and the result is returned in EAX.
typedef int (__stdcall *RecoveryLeafD600Query)(void*, unsigned int);

struct PlatformQueryInterfaces_0044D600 {
    unsigned char unknown_000[4];
    void** entries_004;
    unsigned char unknown_008[8];
    unsigned int count_010;

    __declspec(noinline) int Query();
};

#pragma code_seg(".text$01query")
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
