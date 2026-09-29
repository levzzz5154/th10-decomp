typedef unsigned int CursorWord;
typedef unsigned short CursorHalf;

// The stream cursor stores the address just after the consumed value.
extern "C" __attribute__((regparm(1), noinline, used,
                           section(".text$01cursor_word"), aligned(1)))
CursorWord Cursor_ReadWord_00454eb8(volatile CursorWord* cursor) {
    *cursor += 4;
    return *reinterpret_cast<CursorWord*>(*cursor - 4);
}

extern "C" __attribute__((regparm(1), noinline, used,
                           section(".text$03cursor_half"), aligned(1)))
CursorHalf Cursor_ReadHalf_00454ecd(volatile CursorWord* cursor) {
    *cursor += 4;
    return *reinterpret_cast<CursorHalf*>(*cursor - 4);
}

