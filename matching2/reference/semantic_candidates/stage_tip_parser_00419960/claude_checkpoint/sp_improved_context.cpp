// Retail 0x00419960: stage-tip file dispatch and record construction.
// Contract: loaded file is readable as a NUL-terminated text sequence, scratch
// allocations and record allocations succeed, and all lines fit 4096 bytes.
// These are the same preconditions as the retail helpers' unchecked scans.
#include "stage_parser_model.hpp"
#include "th10/platform/archive_file.hpp"
#include <new>
#include <string.h>

#pragma intrinsic(memset, strcmp, strcpy, strlen)
#pragma code_seg(".text$p00b_ctor")
__declspec(noinline) Tip::Tip() {
    memset(this, 0, sizeof *this);
    node.next = 0;
    node.previous = 0;
    node.owner = this;
    *reinterpret_cast<int*>(&blue) = -1;
    remain = -1;
    time = 300;
    scale = 1.0f;
}
#pragma code_seg(".text$p00zfind")
__declspec(noinline) int FindNamedValue(const char* name, const NamedValue* table, int count) {
    for (int index = 0; index < count; ++index) {
        if (strcmp(name, table[index].key) == 0)
            return table[index].value;
    }
    return 0;
}
#pragma code_seg(".text$p01parser")
extern "C" __declspec(noinline) int __stdcall
ParseStageTips(TipManager* manager, const char* filename, int noDuplicate) {
    int stage = -1, count = 0, remaining;
    char* data = Archive_LoadFile(filename, &remaining, 1);
    if (!data)
        return -1;
    char* line = (char*)asm_malloc_00452706(4096);
    char* key = (char*)asm_malloc_00452706(4096);
    char* value = (char*)asm_malloc_00452706(4096);
    char* cursor = data;
    while (remaining > 0) {
        cursor = ReadLine(cursor, line, &remaining, 4096);
        SplitResourcePath_0041a050(line, value, key);
        SplitResourcePath_0041a050(line, value, key);
        if ((strcmp(key, "Version") == 0)) {
            if (!(strcmp(value, "0.0") == 0)) {
                manager->Clear();
                break;
            }
        } else if ((strcmp(key, "Stage") == 0)) {
            stage = parser_atol(value);
            count = 0;
            if (stage <= 0 || stage >= 8)
                stage = -1;
        } else if ((strcmp(key, "StageEnd") == 0)) {
            stage = -1;
        } else if ((strcmp(key, "Tips") == 0) && stage > 0) {
            if (count >= 255) {
                stage = -1;
                continue;
            }
            Tip* tip = new Tip;
            ++count;
            tip->reserved018 = 0;
            if (remaining > 0) do {
                cursor = ReadLine(cursor, line, &remaining, 4096);
                SplitResourcePath_0041a050(line, value, key);
                if ((strcmp(key, "Pos") == 0)) {
                    char* second = asm_FUN_00452730_00452730(value, ',');
                    if (second) {
                        *second++ = 0;
                        TrimWhitespace_0041a0a0(value);
                        TrimWhitespace_0041a0a0(second);
                        tip->x = (float)parser_atol(value);
                        tip->y = (float)parser_atol(second);
                    }
                } else if ((strcmp(key, "Text") == 0)) {
                    char* text = asm_FUN_00452730_00452730(value, '"');
                    if (text) {
                        ++text;
                        char* end = parser_strrchr(text, '"');
                        if (!end)
                            break;
                        *end = 0;
                        parser_strncpy(tip->name, text, 65);
                    }
                } else if ((strcmp(key, "Count") == 0)) {
                    tip->count = parser_atol(value);
                } else if ((strcmp(key, "Time") == 0)) {
                    tip->time = parser_atol(value);
                } else if ((strcmp(key, "Base") == 0)) {
                    tip->base = FindNamedValue(value, (const NamedValue*)0x4744b0, 61);
                } else if ((strcmp(key, "Align") == 0)) {
                    tip->align = FindNamedValue(value, (const NamedValue*)0x474494, 3);
                } else if ((strcmp(key, "Remain") == 0)) {
                    tip->remain = parser_atol(value);
                } else if ((strcmp(key, "Scale") == 0)) {
                    double scale = parser_atof(value);
                    tip->scale = (float)scale;
                    if (scale > *(const float*)0x470c40)
                        tip->scale = 4.0f;
                    else if (scale < *(const float*)0x470c60)
                        tip->scale = -4.0f;
                } else if ((strcmp(key, "Color") == 0)) {
                    char* second = asm_FUN_00452730_00452730(value, ',');
                    if (second) {
                        *second++ = 0;
                        TrimWhitespace_0041a0a0(value);
                        tip->red = (unsigned char)parser_atol(value);
                        char* third = asm_FUN_00452730_00452730(second, ',');
                        if (third) {
                            *third = 0;
                            TrimWhitespace_0041a0a0(second);
                            tip->green = (unsigned char)parser_atol(second);
                            tip->blue = (unsigned char)parser_atol(
                                TrimWhitespace_0041a0a0(third + 1));
                        }
                    }
                } else if ((strcmp(key, "Alpha") == 0)) {
                    tip->alpha = (unsigned char)parser_atol(value);
                } else if ((strcmp(key, "End") == 0))
                    break;
            } while (remaining > 0);
            tip->width = (float)strlen(tip->name) * tip->scale * 7.5f;
            manager->lists[stage].Append(&tip->node);
            if (!noDuplicate) {
                Tip* other = new Tip;
                *other = *tip;
                other->node.owner = other;
                other->node.next = 0;
                other->node.previous = 0;
                manager->lists[stage + 8].Append(&other->node);
            }
        }
    }
    parser_free(line);
    parser_free(key);
    parser_free(value);
    parser_free(data);
    return 0;
}
#pragma code_seg()

#include "../../src/script/script_text_reader.cpp"
#include "stage_archive_loader.cpp"
