// Exact native-LTCG body for the private EAX/DL/stack scratch writer.
#include <string.h>

struct EclScratchVm_004505b0 {
    unsigned char scratch[0x1000];
    int top;
    int saved_top;
    __declspec(noinline) int WriteScratch(char type, unsigned int size,
                                           const void* source);
};

#pragma code_seg(".text$03write")
int EclScratchVm_004505b0::WriteScratch(char type, unsigned int size,
                                         const void* source) {
    if (top + (int)size >= 0x1000)
        return -1;
    if (type != 0) {
        scratch[top] = (unsigned char)type;
        top += 4;
    }
    memcpy(scratch + top, source, size);
    top += (int)size;
    return 0;
}
#pragma code_seg()
