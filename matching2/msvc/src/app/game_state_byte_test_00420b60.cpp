// 0x00420B60..0x00420B73 (20 bytes): test a one-byte game-state code.
//
// Retail reads one byte from the shared state word at 0x00491D63 and answers 0
// for the two "ready" codes (2 and 1, tested in that order) and -1 otherwise.
// The same byte is read by the menu builder at 0x00420870, so the value is a
// mode the front end publishes before it lays out a screen.
//
// Nothing is read from a register before it is written, so the body compiles as
// a plain translation unit; /Gz makes it __stdcall with no parameters, whose
// epilogue is the bare `ret` retail has.
//
// The two accepted codes share one return block placed last.  Written as
// `if (mode == 2 || mode == 1) return 0; return -1;` the compiler tests the
// range (22 bytes), and as two straight-line early returns it turns the second
// test branchless (`dec al`/`neg al`/`sbb eax,eax`, 19 bytes); two forward
// jumps onto a trailing shared return reproduce retail's `je`/`jne` pair and
// its 20 bytes exactly.

extern "C" unsigned char data_00491d63;

extern "C" int Fun_420b60() {
    unsigned char mode = data_00491d63;
    if (mode == 2) {
        goto ready;
    }
    if (mode == 1) {
        goto ready;
    }
    return -1;
ready:
    return 0;
}
