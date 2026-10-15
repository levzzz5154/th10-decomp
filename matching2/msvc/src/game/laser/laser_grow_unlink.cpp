// 0x0041EAF0: the growing laser's Unlink (vtable 0x0046DA10 slot 0x10). It
// overrides the base list removal with a no-op.
struct GrowLaser {
    int Unlink();
};

int GrowLaser::Unlink() {
    return 0;
}
