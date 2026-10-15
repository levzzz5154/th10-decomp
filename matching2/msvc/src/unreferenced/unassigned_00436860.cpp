// 0x00436860..0x0043686D: `return field_11c != 0;`
struct HandleHolder {
    unsigned char pad_000[0x11c];
    void* handle;                    // +0x11C

    __declspec(noinline) int HasHandle() const;
};

int HandleHolder::HasHandle() const {
    return handle != 0;
}
