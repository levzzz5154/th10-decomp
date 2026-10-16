// 0x00436870..0x0043688E: clear the pooled block whose size is at +0x10C and
// whose base is at +0x120 of the object arriving in EDX.
#include <string.h>

void __fastcall ZeroBlock(int unused, void* object) {
    unsigned char* base = (unsigned char*)object;
    memset(*(void**)(base + 0x120), 0, *(unsigned int*)(base + 0x10c));
}
