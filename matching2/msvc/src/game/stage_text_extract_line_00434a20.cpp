// 0x00434A20: extract one bounded stage-text line in place and consume its
// CR/LF terminator.  The native-LTCG context supplies the original internal
// register convention for this otherwise ordinary stdcall function.
#pragma code_seg(".text$01extractline")
__declspec(noinline) char* StageText_ExtractLine(char* cursor, char* destination,
                                                 int* remaining) {
    char* end = cursor;
    while (*end != '\n') {
        if (*end == '\r')
            break;
        if (*remaining == 0)
            return end;
        ++end;
        --*remaining;
    }
    if (*remaining == 0)
        return end;
    *end = 0;
    char* source = cursor;
    char* output = destination;
    while ((*output++ = *source++) != 0) {}
    ++end;
    --*remaining;
    while (*end == '\n' || *end == '\r') {
        if (*remaining == 0)
            break;
        ++end;
        --*remaining;
    }
    return end;
}
#pragma code_seg()
