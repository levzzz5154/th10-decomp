#include <string.h>
struct UnassignedStream_00450610 {
    unsigned char buffer_000[0x1000];
    int cursor_1000;  // +0x1000
    __declspec(noinline) int Assign(unsigned int count, char type, void* dest);
};
#pragma code_seg(".text$01accessor")
int UnassignedStream_00450610::Assign(unsigned int count, char type, void* dest) {

    int cursor = cursor_1000 - (int)count;
    if (cursor < 0) {
        return -1;
    }
    cursor_1000 = cursor;
    memcpy(dest, (unsigned char*)this + cursor, count);
    if (type == 0) {
        return 0;
    }
    cursor_1000 -= 4;
    char spec = *(char*)((unsigned char*)this + cursor_1000);
    switch (spec) {
    case 'f':
        if (type == 'i') {
            *(int*)dest = (int)*(float*)dest;
        }
        break;
    case 'i':
        if (type == 'f') {
            *(float*)dest = (float)*(int*)dest;
        }
        break;
    }
    return 0;
}
#pragma code_seg()
