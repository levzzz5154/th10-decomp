#define TH10_LZSS_INSERT_CLUSTER
#include "../../src/archive/score_save.cpp"

#pragma code_seg(".text$04context")
int __stdcall LzssInsertCompilerContext(int old_cursor, int position,
                                        int* best_position) {
    return Lzss_InsertString_00436000(old_cursor, position, best_position);
}
#pragma code_seg()
