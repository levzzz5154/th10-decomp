extern "C" int data_00473084[];
extern "C" void* data_00473080[];
extern "C" char data_00477210;
extern "C" int __cdecl asm_crtInitCritSecAndSpinCount_0045980e(void*, unsigned int);

extern "C" int __cdecl asm_mtinitlocks_00453aa1() {
    int i = 0;
    char* next = &data_00477210;
    do {
        if (data_00473084[i * 2] == 1) {
            data_00473080[i * 2] = next;
            next += 24;
            if (!asm_crtInitCritSecAndSpinCount_0045980e(data_00473080[i * 2], 4000)) {
                data_00473080[i * 2] = 0;
                return 0;
            }
        }
        ++i;
    } while (i < 36);
    return 1;
}
