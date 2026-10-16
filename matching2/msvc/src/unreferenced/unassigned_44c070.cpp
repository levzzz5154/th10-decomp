// 0x0044C070..0x0044C07C: byte checksum, stride 1.
//
// The accumulator is a single byte and the count arrives in EDX, so the model
// is the free __fastcall form; c2 rotates the guard into the loop's test.
extern "C" unsigned char __fastcall ByteChecksum(const unsigned char* data,
                                                          unsigned int count) {
    unsigned char total = 0;
    while (count != 0) {
        total += *data++;
        --count;
    }
    return total;
}
