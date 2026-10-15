// 0x0041D870: the line laser's Unlink (vtable 0x0046DA60 slot 0x10). It
// overrides the base list removal with a no-op.
struct LineLaser {
    int Unlink();
};

int LineLaser::Unlink() {
    return 0;
}
