// 0x00427E50..0x00427E69 (26 bytes): is the state busy?
//
// Retail loads the dword at +0x1444, answers 1 when either the low-byte mask
// 0x11 or the upper mask 0x000C0000 is set, and 0 otherwise.  The object
// arrives in EAX.

struct BusyState2 {
    unsigned char unknown_0000[0x1444];
    unsigned int status;                   // +0x1444

    __declspec(noinline) int IsBusy();
};

#pragma code_seg(".text$01busy")
int BusyState2::IsBusy() {
    unsigned int status = this->status;
    if ((status & 0x11) != 0 || (status & 0xC0000) != 0) {
        return 1;
    }
    return 0;
}
#pragma code_seg()
