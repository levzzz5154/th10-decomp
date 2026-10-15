// 0x004658C0: dynamic initializer of the global frame timer at 0x00474C54:
// point its delta at the default game speed (0x00476F78) and mark it set up.

extern "C" int data_00474c64;
extern "C" int data_00474c60;

extern "C" void __cdecl StaticInit_FrameTimer(void) {
    data_00474c64 &= ~1;
    if ((data_00474c64 & 1) == 0) {
        int live = data_00474c64 | 1;
        data_00474c60 = 0x476F78;
        data_00474c64 = live;
    }
}
