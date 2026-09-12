// =============================================================================
// score_save.hpp - Score file compression + save/export surfaces
// Retail functions: 0x00436000, 0x004359B0, 0x0042B1E0, 0x0041A200
// =============================================================================
#ifndef TH10_ARCHIVE_SCORE_SAVE_HPP
#define TH10_ARCHIVE_SCORE_SAVE_HPP

enum LzssConstants {
    LZSS_DICT_SIZE = 0x2000,
    LZSS_MAX_MATCH = 0x12,
    LZSS_MIN_MATCH = 3,
};

// LZSS compressor state (retail globals DAT_0048F868 dictionary ring,
// DAT_00477858/5C/60 binary-tree links, DAT_0048F860 tree root,
// DAT_00477864 write cursor).
struct LzssState {
    unsigned char dictionary[LZSS_DICT_SIZE + LZSS_MAX_MATCH];
    int tree_left[LZSS_DICT_SIZE + 1];
    int tree_right[LZSS_DICT_SIZE + 0x101];
    int tree_parent[LZSS_DICT_SIZE + 1];
    int match_position;
    int match_length;
    int write_cursor;
};

void Lzss_Reset(LzssState* state);
// 0x00436000 equivalent: insert the string starting at `position` into the
// match tree and record the best match in match_position/match_length.
void Lzss_InsertNode(LzssState* state, int position);
void Lzss_DeleteNode(LzssState* state, int position);
// 0x004359B0 equivalent: full-buffer compression; returns encoded size.
unsigned int Lzss_Compress(LzssState* state, const unsigned char* input,
                           unsigned int input_size, unsigned char* output,
                           unsigned int output_capacity);

struct ScoreSaveHooks {
    void* context;
    void* (*alloc)(void* context, unsigned int size);
    void (*release)(void* context, void* memory);
    // Serialize one 'CR' section into `out`; returns bytes written.
    unsigned int (*write_section)(void* context, int section_index,
                                  unsigned char* out,
                                  unsigned int capacity);
    void (*encrypt)(void* context, unsigned char* data, unsigned int size,
                    unsigned char key, unsigned int block); // 0x0044B220
    int (*write_file)(void* context, const char* name,
                      const unsigned char* data, unsigned int size);
};

int ScoreFile_Save(const char* file_name, int section_count,
                   LzssState* lzss, const ScoreSaveHooks* hooks);

struct ScoreExportHooks {
    void* context;
    void* (*alloc)(void* context, unsigned int size);
    void (*release)(void* context, void* memory);
    int (*open_text_file)(void* context, const char* name);
    void (*write_line)(void* context, const char* line);   // 0x0044B740
    void (*close_file)(void* context);
    // Current local time for the banner timestamp.
    void (*local_time)(void* context, int* year, int* month, int* day,
                       int* hour, int* minute);
    // Iterate the per-difficulty record chains (param_1+0x7C lists);
    // returns 0 when no record remains.
    int (*next_record)(void* context, int list_index, char* line_out,
                       unsigned int capacity);
    int list_count;
    const char* version_string;
};

int ScoreFile_ExportText(const char* file_name,
                         const ScoreExportHooks* hooks);

#endif // TH10_ARCHIVE_SCORE_SAVE_HPP
