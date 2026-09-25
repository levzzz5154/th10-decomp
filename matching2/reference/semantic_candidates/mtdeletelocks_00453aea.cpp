// Semantic model for 0x00453AEA..0x00453B3E (__mtdeletelocks).
// The lock table consists of 36 records, each holding a critical-section
// pointer followed by a flag. A flag value of 1 denotes a static lock.
extern "C" void* data_00473080[];
extern "C" int data_00473084[];
extern "C" unsigned char data_004660bc;
extern "C" void __cdecl asm_free_00452422(void* memory);

typedef void (__stdcall *DeleteCriticalSectionFn_00453aea)(void* critical_section);

extern "C" void __cdecl asm_mtdeletelocks_00453aea(void) {
    DeleteCriticalSectionFn_00453aea delete_critical_section =
        *(DeleteCriticalSectionFn_00453aea*)&data_004660bc;

    // First release dynamically allocated locks and clear their table slots.
    for (int index = 0; index != 36; ++index) {
        void* critical_section = data_00473080[index * 2];
        if (critical_section != 0 && data_00473084[index * 2] != 1) {
            delete_critical_section(critical_section);
            asm_free_00452422(critical_section);
            data_00473080[index * 2] = 0;
        }
    }

    // Static lock storage is owned elsewhere, so only destroy the lock.
    for (int index = 0; index != 36; ++index) {
        void* critical_section = data_00473080[index * 2];
        if (critical_section != 0 && data_00473084[index * 2] == 1) {
            delete_critical_section(critical_section);
        }
    }
}
