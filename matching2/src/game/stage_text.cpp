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

// 0x00434A20 - Extract one line in place and consume its CR/LF terminator.
void StageText_ExtractLine(char* cursor, char* destination, int* remaining) {
    char* end = cursor;
    while (*remaining != 0 && *end != '\n' && *end != '\r') {
        ++end;
        --*remaining;
    }
    if (*remaining == 0)
        return;
    *end = 0;
    char* source = cursor;
    char* output = destination;
    while ((*output++ = *source++) != 0) {}
    --*remaining;
    while (*remaining != 0 && (*++end == '\n' || *end == '\r'))
        --*remaining;
}

// 0x00434A80 - Initialize the stage-text layout and reset its parser state.
void StageText_Initialize(
        StageTextState* state, const float* first, const float* second,
        int resource, unsigned char mode, const float* defaults) {
    state->resource = resource;
    state->mode = mode;
    for (int index = 0; index != 3; ++index) {
        state->first[index] = first[index];
        state->second[index] = second[index];
        state->defaults_a[index] = defaults[index];
        state->defaults_b[index] = defaults[index];
    }
    state->current = 0;
    state->length = 0;
    state->selection = -1;
}
