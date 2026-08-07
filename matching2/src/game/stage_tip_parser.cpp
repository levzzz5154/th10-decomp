// Semantic reconstruction of retail 0x00419960 (ParseStageTips), built on the
// already-recovered stage-tip record and manager types in stage_tips.hpp.
//
// The retail body reads the tips file through the pack loader (0x0044B360),
// pulls one line at a time with the shared line reader (0x00419F40), splits
// each line at its first colon (0x0041A050), trims both halves (0x0041A0A0),
// and dispatches on the key.  Tip records are 0x88-byte allocations
// initialized by 0x00418D00 and appended to the manager's per-stage chains
// (0x0041AB10).  The two name tables below are the retail data at 0x00474494
// (Align) and 0x004744B0 (Base).  The helper models in this file mirror the
// retail helper bodies so the parser stays self-contained; the same helper
// addresses are overlaid in recovery_leaves.cpp for the MSVC build.

#include "th10/game/stage_tip_parser.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace {

// One {name, value} record of the retail 8-byte lookup tables below.
struct NamedValue {
    const char* name;
    int value;
};

// Retail 0x0041A0A0: trim the four whitespace classes from both ends of a
// string, in place.
char* Trim(char* text) {
    while (*text == ' ' || *text == '\t' || *text == '\n' || *text == '\r') {
        char* rest = text + 1;
        std::memmove(text, rest, std::strlen(rest) + 1);
    }
    int length = static_cast<int>(std::strlen(text));
    for (int i = length - 1; i >= 0; --i) {
        char c = text[i];
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
            break;
        text[i] = 0;
    }
    return text;
}

// Retail 0x0041A050: copy the line into the key buffer, split it at the
// first colon, move the value into the value buffer, trim both halves.
void SplitLine(char* line, char* value, char* key) {
    std::strcpy(key, line);
    char* colon = std::strchr(key, ':');
    if (colon == 0) {
        Trim(key);
        return;
    }
    std::strcpy(value, colon + 1);
    *colon = 0;
    Trim(key);
    Trim(value);
}

// Retail 0x00419F40: pull the next meaningful line out of the buffer.
// Lines are terminated by LF or CR, stripped of '#' comments, trimmed, and
// empty results are skipped.  `remaining` tracks unread bytes and `cursor`
// advances past each consumed line and its line-ending run.
char* ReadLine(char* cursor, char* out, unsigned int* remaining,
               unsigned int max) {
    std::memset(out, 0, max);
    for (;;) {
        // Retail uses strchr here; the loaded buffer is not NUL-terminated,
        // so the scan is bounded to the unread byte count instead.
        char* newline = 0;
        char* carriage = 0;
        for (unsigned int i = 0; i < *remaining; ++i) {
            if (cursor[i] == '\n') {
                newline = cursor + i;
                break;
            }
            if (cursor[i] == '\r' && carriage == 0)
                carriage = cursor + i;
        }
        char* end = newline != 0 ? newline : carriage;
        if (end == 0) {
            // Tail of the buffer: copy what remains and mark it exhausted.
            unsigned int left = *remaining;
            if (left >= max)
                left = max - 1;
            std::memcpy(out, cursor, left);
            *remaining = 0;
            break;
        }
        unsigned int length = static_cast<unsigned int>(end - cursor);
        if (length >= max - 1)
            length = max - 1;
        std::memcpy(out, cursor, length);
        *remaining -= static_cast<unsigned int>(end - cursor);
        cursor = end;
        while (*remaining > 0 && (*cursor == '\n' || *cursor == '\r')) {
            ++cursor;
            --*remaining;
        }
        char* hash = std::strchr(out, '#');
        if (hash != 0) {
            // Retail zeroes the buffer from the comment marker to its end;
            // the next line copy relies on that to stay NUL-terminated.
            std::memset(hash, 0,
                        max - static_cast<std::size_t>(hash - out));
        }
        Trim(out);
        if (*out != 0)
            break;
    }
    return cursor;
}

// Retail 0x004198C0: linear lookup of a name over an 8-byte {name, value}
// table, returning 0 when the name is absent.
int ResolveName(const char* name, const NamedValue* table, int count) {
    for (int index = 0; index < count; ++index) {
        if (std::strcmp(name, table[index].name) == 0)
            return table[index].value;
    }
    return 0;
}

// Retail 0x0041AB10: append the node to the tail of the chain anchored by
// the sentinel.  The node's own next/previous were cleared by the record
// initializer.
void AppendTip(StageTipNode* head, StageTipNode* node) {
    StageTipNode* tail = head;
    while (tail->next != 0)
        tail = tail->next;
    tail->next = node;
    node->previous = tail;
}

// Retail 0x00419040: free every tip record in the sixteen chains.  Retail
// leaves the sentinels dangling (callers re-initialize the manager); the
// readable form clears them so the manager is safe to reuse directly.
void ReleaseTips(StageTipManager* manager) {
    for (int index = 0; index < 16; ++index) {
        StageTipNode* node = manager->lists[index].next;
        while (node != 0) {
            StageTipNode* next = node->next;
            std::free(node->owner);
            node = next;
        }
        manager->lists[index].next = 0;
        manager->lists[index].previous = 0;
    }
}

// Retail data at 0x00474494: tip alignment names.
static const NamedValue kAlignTable[] = {
    {"center", 0},
    {"left", 1},
    {"right", 2},
};

// Retail data at 0x004744B0: tip base names.  61 entries; note the retail
// table skips `boss_card_11`.
static const NamedValue kBaseTable[] = {
    {"start", 0},
    {"converse_1", 1}, {"converse_2", 2}, {"converse_3", 3},
    {"converse_4", 4}, {"converse_5", 5},
    {"mboss_1", 6}, {"mboss_2", 7}, {"mboss_3", 8}, {"mboss_4", 9},
    {"mboss_5", 10}, {"mboss_6", 11}, {"mboss_7", 12}, {"mboss_8", 13},
    {"mboss_9", 14},
    {"mboss_card_1", 15}, {"mboss_card_2", 16}, {"mboss_card_3", 17},
    {"mboss_card_4", 18}, {"mboss_card_5", 19}, {"mboss_card_6", 20},
    {"mboss_card_7", 21}, {"mboss_card_8", 22}, {"mboss_card_9", 23},
    {"boss_1", 24}, {"boss_2", 25}, {"boss_3", 26}, {"boss_4", 27},
    {"boss_5", 28}, {"boss_6", 29}, {"boss_7", 30}, {"boss_8", 31},
    {"boss_9", 32}, {"boss_10", 33}, {"boss_11", 34}, {"boss_12", 35},
    {"boss_13", 36}, {"boss_14", 37}, {"boss_15", 38}, {"boss_16", 39},
    {"boss_17", 40}, {"boss_18", 41}, {"boss_19", 42},
    {"boss_card_1", 43}, {"boss_card_2", 44}, {"boss_card_3", 45},
    {"boss_card_4", 46}, {"boss_card_5", 47}, {"boss_card_6", 48},
    {"boss_card_7", 49}, {"boss_card_8", 50}, {"boss_card_9", 51},
    {"boss_card_10", 52}, {"boss_card_12", 53}, {"boss_card_13", 54},
    {"boss_card_14", 55}, {"boss_card_15", 56}, {"boss_card_16", 57},
    {"boss_card_17", 58}, {"boss_card_18", 59}, {"boss_card_19", 60},
};

}  // namespace

// 0x00419960 - ParseStageTips: open the tips file through the pack loader
// (retail passes from_disk = 1), walk the key/value lines, and build one
// 0x88-byte StageTip record per `Tips:` block.  Records are appended to
// lists[stage]; when the duplicate flag is clear, a copy is appended to
// lists[stage + 8] as well.  A `Version:` line whose value is not "0.0"
// releases every record parsed so far and aborts the walk.
int ParseStageTips(StageTipManager* manager, const char* filename,
                   int suppress_duplicate, const PackFileTable* table,
                   const PackFileHooks* hooks) {
    unsigned int file_size = 0;
    char* data = static_cast<char*>(
        PackFile_Load(filename, &file_size, 1, table, hooks));
    if (data == 0)
        return -1;

    char* line = static_cast<char*>(std::malloc(0x1000));
    char* key = static_cast<char*>(std::malloc(0x1000));
    char* value = static_cast<char*>(std::malloc(0x1000));

    int current_stage = -1;
    int tip_count = 0;
    unsigned int remaining = file_size;
    char* cursor = data;

    while (remaining > 0) {
        cursor = ReadLine(cursor, line, &remaining, 0x1000);
        SplitLine(line, value, key);

        if (std::strcmp(key, "Version") == 0) {
            if (std::strcmp(value, "0.0") != 0) {
                ReleaseTips(manager);
                break;
            }
            continue;  // retail keeps walking past the version header
        }
        if (std::strcmp(key, "Stage") == 0) {
            current_stage = std::atoi(value);
            tip_count = 0;
            if (current_stage < 1 || current_stage > 7)
                current_stage = -1;
        } else if (std::strcmp(key, "StageEnd") == 0) {
            current_stage = -1;
        } else if (std::strcmp(key, "Tips") == 0 && current_stage > 0) {
            if (tip_count < 255) {
                ++tip_count;
                StageTip* tip = static_cast<StageTip*>(std::malloc(sizeof(StageTip)));
                if (tip == 0) {
                    // Retail dereferences the uninitialized record here.
                    current_stage = -1;
                } else {
                    tip = StageTip_Initialize(0, tip);
                    std::memset(tip->reserved_018, 0, 4);  // retail dword store
                    for (;;) {
                        if (remaining == 0)
                            break;
                        cursor = ReadLine(cursor, line, &remaining, 0x1000);
                        SplitLine(line, value, key);

                        if (std::strcmp(key, "Pos") == 0) {
                            char* comma = std::strchr(value, ',');
                            if (comma != 0) {
                                *comma = 0;
                                Trim(value);
                                char* second = comma + 1;
                                Trim(second);
                                tip->x = static_cast<float>(std::atoi(value));
                                tip->y = static_cast<float>(std::atoi(second));
                            }
                        } else if (std::strcmp(key, "Text") == 0) {
                            char* open = std::strchr(value, '"');
                            if (open != 0) {
                                char* text = open + 1;
                                char* close = std::strrchr(text, '"');
                                if (close == 0)
                                    break;  // retail aborts the tip's lines
                                *close = 0;
                                // Retail strncpy's 0x41 bytes at +0x1C: the
                                // full 0x40-char name plus one byte into the
                                // following reserved word, which terminates
                                // names of exactly 64 characters.
                                std::strncpy(tip->name, text,
                                             sizeof(tip->name));
                                tip->reserved_05C[0] = 0;
                            }
                        } else if (std::strcmp(key, "Count") == 0) {
                            tip->display_value = std::atoi(value);
                        } else if (std::strcmp(key, "Time") == 0) {
                            tip->duration = std::atoi(value);
                        } else if (std::strcmp(key, "Base") == 0) {
                            tip->display_mode =
                                ResolveName(value, kBaseTable, 61);
                        } else if (std::strcmp(key, "Align") == 0) {
                            tip->display_zero =
                                ResolveName(value, kAlignTable, 3);
                        } else if (std::strcmp(key, "Remain") == 0) {
                            tip->selection = std::atoi(value);
                        } else if (std::strcmp(key, "Scale") == 0) {
                            float scale = static_cast<float>(std::atof(value));
                            tip->scale = scale;
                            if (scale <= 4.0f) {
                                if (scale < -4.0f)
                                    tip->scale = -4.0f;
                            } else {
                                tip->scale = 4.0f;
                            }
                        } else if (std::strcmp(key, "Color") == 0) {
                            unsigned char* bytes = reinterpret_cast<unsigned char*>(&tip->state);
                            char* first = std::strchr(value, ',');
                            if (first != 0) {
                                *first = 0;
                                Trim(value);
                                bytes[2] = static_cast<unsigned char>(std::atoi(value));
                                char* second = first + 1;
                                char* third = std::strchr(second, ',');
                                if (third != 0) {
                                    *third = 0;
                                    Trim(second);
                                    bytes[1] = static_cast<unsigned char>(std::atoi(second));
                                    bytes[0] = static_cast<unsigned char>(
                                        std::atoi(Trim(third + 1)));
                                }
                            }
                        } else if (std::strcmp(key, "Alpha") == 0) {
                            reinterpret_cast<unsigned char*>(&tip->state)[3] =
                                static_cast<unsigned char>(std::atoi(value));
                        } else if (std::strcmp(key, "End") == 0) {
                            break;
                        }
                    }
                    float width = static_cast<float>(std::strlen(tip->name)) *
                                  tip->scale * 7.5f;
                    std::memcpy(&tip->rendered_width, &width, sizeof(width));
                    AppendTip(&manager->lists[current_stage], &tip->node);
                    if (suppress_duplicate == 0) {
                        StageTip* duplicate =
                            static_cast<StageTip*>(std::malloc(sizeof(StageTip)));
                        if (duplicate != 0) {
                            duplicate = StageTip_Initialize(0, duplicate);
                            std::memcpy(duplicate, tip, sizeof(StageTip));
                            duplicate->node.owner = duplicate;
                            duplicate->node.next = 0;
                            duplicate->node.previous = 0;
                            AppendTip(&manager->lists[current_stage + 8],
                                      &duplicate->node);
                        }
                    }
                }
            } else {
                current_stage = -1;
            }
        }
    }

    std::free(line);
    std::free(key);
    std::free(value);
    std::free(data);
    return 0;
}
