// 0x0042A990: rewind both cursors to their starts and clear the count.
struct Cursors_0042a990 {
    int first_start;                  // +0x00
    int first;                        // +0x04
    int second_start;                 // +0x08
    int second;                       // +0x0C
    int reserved_010;
    int count;                        // +0x14
    __declspec(noinline) void Rewind();
};

#pragma code_seg(".text$01accessor")
void Cursors_0042a990::Rewind() {
    first = first_start;
    second = second_start;
    count = 0;
}
#pragma code_seg()
