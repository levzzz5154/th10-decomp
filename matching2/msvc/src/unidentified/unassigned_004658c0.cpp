// 0x004658C0: mark the onexit table live.

extern "C" int data_00474c64;
extern "C" int data_00474c60;

extern "C" void __cdecl unassigned_004658c0(void) {
    data_00474c64 &= ~1;
    if ((data_00474c64 & 1) == 0) {
        int live = data_00474c64 | 1;
        data_00474c60 = 0x476F78;
        data_00474c64 = live;
    }
}
