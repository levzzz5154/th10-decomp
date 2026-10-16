struct UnassignedSurface_00437200 {
    unsigned char pad_000[0x100];
    int mode_100;             // +0x0100
    unsigned char pad_104[4];
    int field_108;            // +0x0108
    int field_10c;            // +0x010C
    int field_110;            // +0x0110
    unsigned char pad_114[0xC];
    unsigned char* data_120;  // +0x0120
};
extern "C" char __fastcall UnassignedConvert_00437200(UnassignedSurface_00437200* surface,
                                                      unsigned char value) {
    int count = surface->field_110 * surface->field_108;
    unsigned char* data = surface->data_120;
    switch (surface->mode_100) {
    case 0x15:
        for (int index = 2; index < count; index += 4) data[index] = value;
        break;
    case 0x19: {
        unsigned char flag = (value == 0) ? 0 : 0x80;
        for (int index = 1; index < count; index += 2)
            data[index] = (unsigned char)((data[index] & 0x7F) | flag);
        break;
    }
    case 0x1A: {
        unsigned char mask = (unsigned char)(value & 0xF0);
        for (int index = 1; index < count; index += 2)
            data[index] = (unsigned char)((data[index] & 0x0F) | mask);
        break;
    }
    default:
        return 0;
    }
    return 1;
}
