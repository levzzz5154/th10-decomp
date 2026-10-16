// 0x0042A900: append one byte to the line buffer; nonzero once 120 bytes are used.
struct LineBuffer {
    unsigned char reserved_000[0x5464];
    char text[0x6274 - 0x5464];       // +0x5464
    char* write;                      // +0x6274
    __declspec(noinline) int Append(char c);
};

#pragma code_seg(".text$01accessor")
int LineBuffer::Append(char c) {
    *write = c;
    ++write;
    return write - text >= 0x78;
}
#pragma code_seg()
