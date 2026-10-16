// 0x00438410 - return the object pointer unchanged. The stack argument is
// unused: the retail body only moves ECX into EAX.
struct Object00438410 {
    void* Self(int unused);
};

void* Object00438410::Self(int unused) {
    (void)unused;
    return this;
}
