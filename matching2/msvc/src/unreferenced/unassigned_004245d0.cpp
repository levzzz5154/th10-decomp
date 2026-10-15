// 0x004245D0..0x004245E5 (22 bytes): is the owned child marked?
//
// Retail loads the child pointer from +0x08, and answers 1 when the child is
// present and bit 1 of the dword at the child's +0x04 is set, 0 otherwise.  The
// object arrives in EAX; nothing on the stack.

struct Child_004245d0 {
    unsigned char unknown_00[0x04];
    unsigned int flags;            // +0x04
};

struct Owner_004245d0 {
    unsigned char unknown_00[0x08];
    Child_004245d0* child;         // +0x08

    __declspec(noinline) int IsChildMarked();
};

#pragma code_seg(".text$01mark")
int Owner_004245d0::IsChildMarked() {
    Child_004245d0* child = this->child;
    if (child != 0 && (child->flags & 2) != 0) {
        return 1;
    }
    return 0;
}
#pragma code_seg()
