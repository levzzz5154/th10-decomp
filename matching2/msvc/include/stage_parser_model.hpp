#pragma once
#include <stddef.h>
struct Tip;
// Twelve-byte intrusive node, embedded at +0x0C in a tip.
struct TipNode {
    Tip* owner;        // +0x00
    TipNode* next;     // +0x04
    TipNode* previous; // +0x08
    void Unlink() {
        next = 0;
        previous = 0;
    }
    __declspec(noinline) void Append(TipNode* node);
};
// Retail 0x88-byte allocation used by the complete parser compiler context.
struct Tip {
    float x, y, z;            // +0x00, +0x04, +0x08
    TipNode node;             // +0x0C
    unsigned int reserved018; // +0x18
    char name[65];            // +0x1C: strncpy writes 65 bytes, including retail +0x5C
    unsigned char reserved05d[3];          // +0x5D..+0x5F
    int count, align, base, time, remain;  // +0x60, +0x64, +0x68, +0x6C, +0x70
    unsigned int reserved074[2];           // +0x74..+0x7B
    float scale, width;                    // +0x7C, +0x80
    unsigned char blue, green, red, alpha; // +0x84, +0x85, +0x86, +0x87
    Tip();
};
struct TipManager {
    unsigned char reserved000[0x18]; // Task and runtime slots, +0x00..+0x17
    TipNode lists[16];               // +0x18: primary and duplicate stage lists
    __declspec(noinline) void Clear();
};
typedef char TipExtent[sizeof(Tip) == 0x88 ? 1 : -1];
typedef char TipNameOffset[offsetof(Tip, name) == 0x1c ? 1 : -1];
typedef char TipListsOffset[offsetof(TipManager, lists) == 0x18 ? 1 : -1];
char* __stdcall TrimWhitespace_0041a0a0(char* text);
extern "C" void __stdcall SplitResourcePath_0041a050(char* key, char* value, char* line);
extern "C" char* __stdcall ReadLine(char*, char*, int*, unsigned int);
extern "C" char* __cdecl asm_FUN_00452730_00452730(const char*, int);
extern "C" long __cdecl parser_atol(const char*);
extern "C" double __cdecl parser_atof(const char*);
extern "C" char* __cdecl parser_strrchr(const char*, int);
extern "C" char* __cdecl parser_strncpy(char*, const char*, unsigned int);
extern "C" void __cdecl parser_free(void*);
extern "C" void __cdecl entry_free_004524a1(void*);
extern "C" void* __cdecl asm_malloc_00452706(unsigned int);
struct NamedValue {
    const char* key;
    unsigned int value;
};
int FindNamedValue(const char* name, const NamedValue* table, int count);
extern "C" int __stdcall ParseStageTips(TipManager*, const char*, int);
