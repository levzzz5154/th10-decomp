// 0x004659A0: fill one table with -1.

extern "C" int data_00492998[0x80];

extern "C" void __cdecl unassigned_004659a0(void) {
    for (int index = 0; index < 0x80; ++index)
        data_00492998[index] = -1;
}
