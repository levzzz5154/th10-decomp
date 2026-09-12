// 0x004349E0..0x00434A1A: advance a stage-text cursor over one line and its
// immediately following CR/LF bytes.
#pragma code_seg(".text$01skipline")
__declspec(noinline) char* StageText_SkipLine(char* cursor, int* remaining) {
    while (*cursor != '\n' && *cursor != '\r') {
        if (*remaining == 0)
            return cursor;
        ++cursor;
        --*remaining;
    }
    if (*remaining != 0) {
        while (*cursor == '\n' || *cursor == '\r') {
            if (*remaining == 0)
                break;
            ++cursor;
            --*remaining;
        }
    }
    return cursor;
}
#pragma code_seg()
