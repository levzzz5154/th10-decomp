// =============================================================================
// score_save.cpp - LZSS compressor and score save/export
// =============================================================================
#include "th10/archive/score_save.hpp"

namespace {
enum { TREE_NIL = LZSS_DICT_SIZE };
}

void Lzss_Reset(LzssState* state) {
    for (int index = 0; index < LZSS_DICT_SIZE + LZSS_MAX_MATCH; ++index)
        state->dictionary[index] = 0;
    for (int index = 0; index <= LZSS_DICT_SIZE; ++index) {
        state->tree_left[index] = TREE_NIL;
        state->tree_parent[index] = TREE_NIL;
    }
    for (int index = 0; index < LZSS_DICT_SIZE + 0x101; ++index)
        state->tree_right[index] = TREE_NIL;
    state->match_position = 0;
    state->match_length = 0;
    state->write_cursor = LZSS_DICT_SIZE - LZSS_MAX_MATCH;
}

// 0x00436000 - Lzss_InsertNode: insert the 0x12-byte string at `position`
// into the binary match tree (roots indexed by first byte at
// tree_right[0x2001 + byte]) and track the longest match found on the way
// down, preferring the most recent position on equal lengths.
void Lzss_InsertNode(LzssState* state, int position) {
    const unsigned char* key = &state->dictionary[position];
    int compare = 1;
    int node = LZSS_DICT_SIZE + 1 + key[0];
    state->tree_left[position] = TREE_NIL;
    state->tree_right[position] = TREE_NIL;
    state->match_length = 0;
    for (;;) {
        int child;
        if (compare >= 0) {
            child = state->tree_right[node];
            if (child == TREE_NIL) {
                state->tree_right[node] = position;
                state->tree_parent[position] = node;
                return;
            }
        } else {
            child = state->tree_left[node];
            if (child == TREE_NIL) {
                state->tree_left[node] = position;
                state->tree_parent[position] = node;
                return;
            }
        }
        node = child;
        int length = 1;
        while (length < LZSS_MAX_MATCH) {
            compare = key[length] - state->dictionary[node + length];
            if (compare != 0)
                break;
            length += 1;
        }
        if (length > state->match_length) {
            state->match_position = node;
            state->match_length = length;
            if (length >= LZSS_MAX_MATCH) {
                // Full match: replace the old node with the new position.
                state->tree_left[position] = state->tree_left[node];
                state->tree_right[position] = state->tree_right[node];
                state->tree_parent[state->tree_left[node]] = position;
                state->tree_parent[state->tree_right[node]] = position;
                int parent = state->tree_parent[node];
                state->tree_parent[position] = parent;
                if (state->tree_right[parent] == node)
                    state->tree_right[parent] = position;
                else
                    state->tree_left[parent] = position;
                state->tree_parent[node] = TREE_NIL;
                return;
            }
        }
    }
}

void Lzss_DeleteNode(LzssState* state, int position) {
    if (state->tree_parent[position] == TREE_NIL)
        return;
    int replacement;
    if (state->tree_right[position] == TREE_NIL) {
        replacement = state->tree_left[position];
    } else if (state->tree_left[position] == TREE_NIL) {
        replacement = state->tree_right[position];
    } else {
        replacement = state->tree_left[position];
        if (state->tree_right[replacement] != TREE_NIL) {
            while (state->tree_right[replacement] != TREE_NIL)
                replacement = state->tree_right[replacement];
            state->tree_right[state->tree_parent[replacement]] =
                state->tree_left[replacement];
            state->tree_parent[state->tree_left[replacement]] =
                state->tree_parent[replacement];
            state->tree_left[replacement] = state->tree_left[position];
            state->tree_parent[state->tree_left[position]] = replacement;
        }
        state->tree_right[replacement] = state->tree_right[position];
        state->tree_parent[state->tree_right[position]] = replacement;
    }
    state->tree_parent[replacement] = state->tree_parent[position];
    if (state->tree_right[state->tree_parent[position]] == position)
        state->tree_right[state->tree_parent[position]] = replacement;
    else
        state->tree_left[state->tree_parent[position]] = replacement;
    state->tree_parent[position] = TREE_NIL;
}

// 0x004359B0 - Lzss_Compress: bit-packed LZSS encode of the whole input.
// Seeds the dictionary with 0x12 zero bytes, then emits literal bits or
// 13+5-bit (position, length-3) match tokens, updating the tree per byte.
unsigned int Lzss_Compress(LzssState* state, const unsigned char* input,
                           unsigned int input_size, unsigned char* output,
                           unsigned int output_capacity) {
    Lzss_Reset(state);
    unsigned int in_pos = 0, out_pos = 0;
    unsigned char bit_buffer = 0;
    int bit_count = 0;
    unsigned char pending[0x11];
    int pending_size = 0;

    auto flush_unit = [&](void) -> bool {
        if (bit_count < 8)
            return true;
        if (out_pos + 1u + static_cast<unsigned int>(pending_size) >
            output_capacity)
            return false;
        output[out_pos++] = bit_buffer;
        for (int index = 0; index < pending_size; ++index)
            output[out_pos++] = pending[index];
        bit_buffer = 0;
        bit_count = 0;
        pending_size = 0;
        return true;
    };

    int fill = 0;
    while (fill < LZSS_MAX_MATCH &&
           static_cast<unsigned int>(fill) < input_size) {
        state->dictionary[state->write_cursor + fill] = input[fill];
        fill += 1;
    }
    for (int index = 1; index <= LZSS_MAX_MATCH; ++index)
        Lzss_InsertNode(state, state->write_cursor - index < 0
                                   ? state->write_cursor - index +
                                         LZSS_DICT_SIZE
                                   : state->write_cursor - index);
    Lzss_InsertNode(state, state->write_cursor);

    int lookahead = fill;
    int cursor = state->write_cursor;
    while (lookahead > 0) {
        int match_length = state->match_length;
        if (match_length > lookahead)
            match_length = lookahead;
        if (match_length < LZSS_MIN_MATCH) {
            match_length = 1;
            bit_buffer = static_cast<unsigned char>(bit_buffer |
                                                    (1 << bit_count));
            pending[pending_size++] = state->dictionary[cursor];
        } else {
            unsigned int token =
                (static_cast<unsigned int>(state->match_position) << 5) |
                static_cast<unsigned int>(match_length - LZSS_MIN_MATCH);
            pending[pending_size++] = static_cast<unsigned char>(token >> 8);
            pending[pending_size++] = static_cast<unsigned char>(token);
        }
        bit_count += 1;
        if (!flush_unit())
            return 0;

        for (int step = 0; step < match_length; ++step) {
            Lzss_DeleteNode(state, (cursor + LZSS_MAX_MATCH) %
                                       LZSS_DICT_SIZE);
            unsigned char next = 0;
            bool have_next = in_pos + LZSS_MAX_MATCH < input_size;
            if (have_next)
                next = input[in_pos + LZSS_MAX_MATCH];
            if (have_next) {
                state->dictionary[(cursor + LZSS_MAX_MATCH) %
                                  LZSS_DICT_SIZE] = next;
                if ((cursor + LZSS_MAX_MATCH) % LZSS_DICT_SIZE <
                    LZSS_MAX_MATCH - 1)
                    state->dictionary[(cursor + LZSS_MAX_MATCH) %
                                          LZSS_DICT_SIZE +
                                      LZSS_DICT_SIZE] = next;
            } else {
                lookahead -= 1;
            }
            in_pos += 1;
            cursor = (cursor + 1) % LZSS_DICT_SIZE;
            if (lookahead > 0)
                Lzss_InsertNode(state, cursor);
        }
    }
    if (bit_count > 0) {
        if (out_pos + 1u + static_cast<unsigned int>(pending_size) >
            output_capacity)
            return 0;
        output[out_pos++] = bit_buffer;
        for (int index = 0; index < pending_size; ++index)
            output[out_pos++] = pending[index];
    }
    return out_pos;
}

// 0x0042B1E0 - ScoreFile_Save: serialize the seven 'CR' sections with their
// per-section checksums into a work buffer, LZSS-compress the image, apply
// the stream cipher, and write scoreth10.dat.
int ScoreFile_Save(const char* file_name, int section_count,
                   LzssState* lzss, const ScoreSaveHooks* hooks) {
    const unsigned int kWorkSize = 0x200000;
    unsigned char* work = static_cast<unsigned char*>(
        hooks->alloc(hooks->context, kWorkSize));
    if (work == 0)
        return -1;
    unsigned int used = 0x18; // six-dword header, patched below
    for (int section = 0; section < section_count; ++section)
        used += hooks->write_section(hooks->context, section, work + used,
                                     kWorkSize - used);
    // Header: magic, version, payload size, checksum of the payload.
    unsigned int checksum = 0;
    for (unsigned int index = 0x18; index < used; ++index)
        checksum += work[index];
    reinterpret_cast<unsigned int*>(work)[0] = 0x30524353u; // 'SCR0' tag
    reinterpret_cast<unsigned int*>(work)[1] = 1;
    reinterpret_cast<unsigned int*>(work)[2] = used;
    reinterpret_cast<unsigned int*>(work)[3] = checksum;
    reinterpret_cast<unsigned int*>(work)[4] = 0;
    reinterpret_cast<unsigned int*>(work)[5] = 0;

    unsigned char* packed = static_cast<unsigned char*>(
        hooks->alloc(hooks->context, used + (used >> 3) + 0x20));
    if (packed == 0) {
        hooks->release(hooks->context, work);
        return -1;
    }
    unsigned int packed_size = Lzss_Compress(lzss, work, used, packed,
                                             used + (used >> 3) + 0x20);
    hooks->release(hooks->context, work);
    if (packed_size == 0) {
        hooks->release(hooks->context, packed);
        return -1;
    }
    hooks->encrypt(hooks->context, packed, packed_size, '5', 0x10);
    int status = hooks->write_file(hooks->context, file_name, packed,
                                   packed_size);
    hooks->release(hooks->context, packed);
    return status;
}

// 0x0041A200 - ScoreFile_ExportText: write the human-readable score dump.
// Emits the commented banner (title rows, timestamp, version), then walks
// every record chain and prints one line per record.
int ScoreFile_ExportText(const char* file_name,
                         const ScoreExportHooks* hooks) {
    char* line = static_cast<char*>(hooks->alloc(hooks->context, 0x1000));
    if (line == 0)
        return -1;
    if (hooks->open_text_file(hooks->context, file_name) != 0) {
        hooks->release(hooks->context, line);
        return -1;
    }
    hooks->write_line(hooks->context,
                      "# =====================================\r\n");
    int year = 0, month = 0, day = 0, hour = 0, minute = 0;
    hooks->local_time(hooks->context, &year, &month, &day, &hour, &minute);
    char stamp[0x60];
    {
        // "#  Time-stamp: <YYYY/MM/DD HH:MM>" (retail %.4d/%.2d/%.2d %.2d:%.2d)
        int cursor = 0;
        const char prefix[] = "#  Time-stamp: <";
        for (const char* p = prefix; *p != '\0'; ++p) stamp[cursor++] = *p;
        auto put = [&](int value, int digits) {
            for (int digit = digits - 1; digit >= 0; --digit) {
                int divisor = 1;
                for (int i = 0; i < digit; ++i) divisor *= 10;
                stamp[cursor++] =
                    static_cast<char>('0' + (value / divisor) % 10);
            }
        };
        put(year, 4); stamp[cursor++] = '/';
        put(month, 2); stamp[cursor++] = '/';
        put(day, 2); stamp[cursor++] = ' ';
        put(hour, 2); stamp[cursor++] = ':';
        put(minute, 2);
        stamp[cursor++] = '>'; stamp[cursor++] = '\r';
        stamp[cursor++] = '\n'; stamp[cursor] = '\0';
    }
    hooks->write_line(hooks->context, stamp);
    hooks->write_line(hooks->context, "#\r\n\r\n");
    {
        char version_line[0x80];
        int cursor = 0;
        const char prefix[] = "Version = ";
        for (const char* p = prefix; *p != '\0'; ++p)
            version_line[cursor++] = *p;
        for (const char* p = hooks->version_string; *p != '\0'; ++p)
            version_line[cursor++] = *p;
        version_line[cursor++] = '\r';
        version_line[cursor++] = '\n';
        version_line[cursor++] = '\r';
        version_line[cursor++] = '\n';
        version_line[cursor] = '\0';
        hooks->write_line(hooks->context, version_line);
    }
    for (int list_index = 0; list_index < hooks->list_count; ++list_index)
        while (hooks->next_record(hooks->context, list_index, line,
                                  0x1000) != 0)
            hooks->write_line(hooks->context, line);
    hooks->close_file(hooks->context);
    hooks->release(hooks->context, line);
    return 0;
}
