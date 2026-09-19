struct Record_004126d0 {
    unsigned char prefix[0x1148];
    int values[4];
};

extern "C" __declspec(noinline) int* __fastcall FUN_004126d0(
        Record_004126d0* self, void*, int selector) {
    switch (selector) {
    case -0x26FD: return &self->values[0];
    case -0x26FC: return &self->values[1];
    case -0x26FB: return &self->values[2];
    case -0x26FA: return &self->values[3];
    default: return 0;
    }
}
