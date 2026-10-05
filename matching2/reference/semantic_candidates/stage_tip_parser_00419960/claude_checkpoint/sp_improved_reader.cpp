// Retail 0x00419F40: return the next nonempty, trimmed script line.
// Cursor is in EAX; output, remaining count, and capacity are stack arguments.
// Inputs retain retail contracts: a readable NUL-terminated scan buffer,
// positive capacity, disjoint output, and enough output room for the final tail.
// Split/trim/append/clear below are complete C++ ABI anchors, not new ownership.
#include "stage_parser_model.hpp"
#include <string.h>

#pragma code_seg(".text$p03reader")
extern "C" __declspec(noinline) char* __stdcall
ReadLine(char* cursor, char* out, int* remaining, unsigned int capacity) {
    memset(out, 0, capacity);
    while (!*out) {
        char* end = asm_FUN_00452730_00452730(cursor, '\n');
        if (!end)
            end = asm_FUN_00452730_00452730(cursor, '\r');
        if (!end) {
            memcpy(out, cursor, *remaining);
            *remaining = 0;
            break;
        }
        int length = (int)(end - cursor);
        if (length >= (int)capacity - 1)
            length = capacity - 1;
        memcpy(out, cursor, length);
        *remaining -= (int)(end - cursor);
        cursor = end;
        while (*cursor == '\n' || *cursor == '\r') {
            ++cursor;
            --*remaining;
        }
        char* hash = asm_FUN_00452730_00452730(out, '#');
        if (hash) {
            memset(hash, 0, capacity - (unsigned int)(hash - out));
            *hash = 0;
        }
        TrimWhitespace_0041a0a0(out);
    }
    return cursor;
}
#pragma code_seg(".text$p05split")
extern "C" char* __stdcall
SplitResourcePath_0041a050(char* line, char* value, char* key) {
    strcpy(key, line);
    char* colon = asm_FUN_00452730_00452730(key, ':');
    if (!colon)
        return TrimWhitespace_0041a0a0(key);
    strcpy(value, colon + 1);
    *colon = 0;
    TrimWhitespace_0041a0a0(key);
    return TrimWhitespace_0041a0a0(value);
}
#pragma code_seg(".text$p07trim")
__declspec(noinline) char* __stdcall TrimWhitespace_0041a0a0(char* text) {
    while (*text == ' ' || *text == '\t' || *text == '\n' || *text == '\r') {
        int length = (int)strlen(text);
        for (int i = 0; i < length; ++i)
            text[i] = text[i + 1];
    }
    int length = (int)strlen(text);
    for (int i = length - 1; i >= 0; --i) {
        char c = text[i];
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
            break;
        text[i] = 0;
    }
    return text;
}
#pragma code_seg(".text$p09append")
void TipNode::Append(TipNode* node) {
    TipNode* tail = this;
    while (tail->next)
        tail = tail->next;
    if (tail->next) {
        node->next = tail->next;
        tail->next->previous = node;
    }
    tail->next = node;
    node->previous = tail;
}
#pragma code_seg(".text$p00clear")
void TipManager::Clear() {
    for (int i = 0; i < 8; ++i) {
        TipNode* node = lists[i].next;
        while (node) {
            TipNode* next = node->next;
            entry_free_004524a1(node->owner);
            node = next;
        }
        node = lists[i + 8].next;
        while (node) {
            TipNode* next = node->next;
            entry_free_004524a1(node->owner);
            node = next;
        }
    }
}
#pragma code_seg()
