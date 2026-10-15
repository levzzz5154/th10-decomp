// 0x00435220: duplicate a NUL-terminated string into a fresh heap block.
// Returns 0 when the allocation fails.  The DAT archive keeps its filename
// this way (see DatArchive open at 0x00434C30/0x00434CA0).
//
// Retail passes the source string in EDI; native LTCG picks that register
// from the callers, so the body is compiled in the cluster
// layout/ltcg/legacy_string_duplicate_00435220.json.
#include <string.h>

extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);

#pragma code_seg(".text$07duplicate")
__declspec(noinline) char* LegacyString_Duplicate(const char* text) {
    char* copy = (char*)asm_malloc_00452706(strlen(text) + 1);
    if (copy)
        strcpy(copy, text);
    return copy;
}
#pragma code_seg()
