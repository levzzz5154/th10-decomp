// 0x00436770..0x0043677C: stores one byte through the destination pointer and
// reports the source pointer, the classic byte-copy helper result.
unsigned char* __cdecl CopyByteReturnSource_00436770(unsigned char* destination,
                                                     unsigned char* source) {
    *destination = *source;
    return source;
}
