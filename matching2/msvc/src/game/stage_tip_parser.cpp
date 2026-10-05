// Retail 0x00419960: load a stage-tip script and build the per-stage tip lists.
// Contract: the loaded file is readable as a NUL-terminated text sequence, the
// scratch and record allocations succeed, and all lines fit 4096 bytes. These
// are the same preconditions as the retail helpers' unchecked scans.
#include "stage_parser_model.hpp"
#include "th10/platform/archive_file.hpp"
#include <new>
#include <string.h>

#pragma intrinsic(memset, strcmp, strcpy, strlen)
// Line reads go through this forwarding helper at every parser call site.
static inline char* ReadScriptLine(char* cursor, char* out, int* remaining, unsigned int capacity) {
    return ReadLine(cursor, out, remaining, capacity);
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
        cursor = ReadScriptLine(cursor, line, &remaining, 4096);
        SplitResourcePath_0041a050(key, value, line);
        SplitResourcePath_0041a050(key, value, line);
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
                cursor = ReadScriptLine(cursor, line, &remaining, 4096);
                SplitResourcePath_0041a050(key, value, line);
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
                    float scale = (float)parser_atof(value);
                    tip->scale = scale;
                    if (scale > 4.0f)
                        tip->scale = 4.0f;
                    else if (scale < -4.0f)
                        tip->scale = -4.0f;
                } else if ((strcmp(key, "Color") == 0)) {
                    char* second = asm_FUN_00452730_00452730(value, ',');
                    if (second) {
                        *second++ = 0;
                        TrimWhitespace_0041a0a0(value);
                        tip->red = (unsigned char)parser_atol(value);
                        char* green = second;
                        second = asm_FUN_00452730_00452730(second, ',');
                        if (second) {
                            *second = 0;
                            TrimWhitespace_0041a0a0(green);
                            tip->green = (unsigned char)parser_atol(green);
                            tip->blue = (unsigned char)parser_atol(
                                TrimWhitespace_0041a0a0(second + 1));
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
                other->node.Unlink();
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
