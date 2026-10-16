// 0x004389A0..0x004389AF: clear the 0x58-byte record that arrives in EDX.
#include <string.h>

void* __fastcall ClearRecord2(int unused, void* record) {
    memset(record, 0, 0x16 * 4);
    return record;
}
