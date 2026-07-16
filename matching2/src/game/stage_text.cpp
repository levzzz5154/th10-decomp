#include "th10/game/stage_text.hpp"

// 0x004349E0 - Advance past the current text line and all immediately
// following CR/LF bytes while maintaining the parser's remaining-byte count.
char* StageText_SkipLine(char* cursor, int* remaining) {
    while (*remaining != 0 && *cursor != '\n' && *cursor != '\r') {
        ++cursor;
        --*remaining;
    }
    while (*remaining != 0 && (*cursor == '\n' || *cursor == '\r')) {
        ++cursor;
        --*remaining;
    }
    return cursor;
}
