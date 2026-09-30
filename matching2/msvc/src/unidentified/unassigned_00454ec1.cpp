typedef unsigned int CursorWord;
typedef unsigned long long CursorPair;

// Volatile reads preserve the low-then-high order of the original stream access.
extern "C" __attribute__((regparm(1), noinline, used,
                           section(".text$02cursor_pair"), aligned(1)))
CursorPair Cursor_ReadPair_00454ec1(volatile CursorWord* cursor) {
    *cursor += 8;
    volatile CursorWord* value =
        reinterpret_cast<volatile CursorWord*>(*cursor - 8);
    CursorWord low = value[0];
    CursorWord high = value[1];
    return (static_cast<CursorPair>(high) << 32) | low;
}
