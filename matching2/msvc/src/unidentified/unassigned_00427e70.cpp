// 0x00427E70..0x00427E89 (26 bytes): is the second state busy?
//
// Same body as 0x00427E50 over the dword at +0x2480, so the two are the front
// and back halves of one record family.  The object arrives in EAX.

struct BusyState_00427e70 {
    unsigned char unknown_0000[0x2480];
    unsigned int status;                   // +0x2480

    __declspec(noinline) int IsBusy();
};

#pragma code_seg(".text$01busy")
int BusyState_00427e70::IsBusy() {
    unsigned int status = this->status;
    if ((status & 0x11) != 0 || (status & 0xC0000) != 0) {
        return 1;
    }
    return 0;
}
#pragma code_seg()
