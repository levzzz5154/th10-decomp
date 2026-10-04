#ifndef TH10_ARCHIVE_LZSS_HPP
#define TH10_ARCHIVE_LZSS_HPP

// LZSS codec used for th10.dat members, score files and replays. The scheme
// and the match tree follow Mark Nelson's LZSS from "The Data Compression
// Book": a 13-bit window position and a 4-bit length per match, a one-bit
// flag per token, bits written most-significant first.

#define LZSS_INDEX_BIT_COUNT 13
#define LZSS_LENGTH_BIT_COUNT 4
#define LZSS_WINDOW_SIZE (1 << LZSS_INDEX_BIT_COUNT)
#define LZSS_RAW_LOOK_AHEAD_SIZE (1 << LZSS_LENGTH_BIT_COUNT)
// Matches of this length or shorter are cheaper as literals.
#define LZSS_BREAK_EVEN 2
#define LZSS_LOOK_AHEAD_SIZE (LZSS_RAW_LOOK_AHEAD_SIZE + LZSS_BREAK_EVEN)
// The tree's root is one extra node past the window; node 0 means "none".
#define LZSS_TREE_ROOT LZSS_WINDOW_SIZE
#define LZSS_END_OF_STREAM 0
#define LZSS_UNUSED 0
#define LZSS_MOD_WINDOW(a) ((a) & (LZSS_WINDOW_SIZE - 1))

// One binary-tree node per window position, ordering the strings that start
// there. The root only uses larger_child.
struct LzssNode {
    int parent;
    int smaller_child;
    int larger_child;
};

extern LzssNode g_LzssTree[LZSS_WINDOW_SIZE + 1];
extern unsigned char g_LzssWindow[LZSS_WINDOW_SIZE];

// Returns a malloc'd buffer of at most inSize * 2 bytes holding the stream and
// stores its length in *outSize; null when the allocation fails.
unsigned char* __stdcall Lzss_Compress(const unsigned char* in, int inSize, int* outSize);

// Expands a stream into `out`, or into a malloc'd buffer of outSize bytes when
// `out` is null. Returns the output buffer.
extern "C" unsigned char* __stdcall DecompressDatLzss_00435dc0(
    const unsigned char* in, int inSize, unsigned char* out, unsigned int outSize);

void Lzss_InitTree(int r);
void Lzss_InitEncoder();
int Lzss_AddString(int new_node, int* match_position);
void __fastcall Lzss_DeleteString(int p);
void Lzss_ContractNode(int old_node, int new_node);
void Lzss_ReplaceNode(int old_node, int new_node);
int Lzss_FindNextNode(int node);

typedef char LzssNode_size_must_be_12[sizeof(LzssNode) == 12 ? 1 : -1];

#endif
