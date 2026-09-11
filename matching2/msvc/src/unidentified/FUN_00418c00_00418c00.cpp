// 0x00418C00..0x00418C05: reads the shared 32-bit state word at 0x00491FC4.
extern "C" unsigned char data_00491fc4;

int GetStateWord_00491fc4(void) {
    return *(int*)&data_00491fc4;
}
