// 0x00435FD0..0x00435FF9: zero the 0x2000-byte block at 0x0048F868, then walk
// the twelve-byte records below it, clearing each.
void ClearPools_00435fd0() {
    unsigned int* block = (unsigned int*)0x48f868;
    for (unsigned int index = 0; index < 0x800; ++index) {
        block[index] = 0;
    }
    for (int cursor = 0x47785c; cursor < 0x48f868; cursor += 12) {
        *(int*)(cursor - 4) = 0;
        *(int*)cursor = 0;
        *(int*)(cursor + 4) = 0;
    }
}
