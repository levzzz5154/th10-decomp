#include <string.h>

extern "C" char data_00497c38[]; // shared asset filename buffer

// Retail 0x00418850..0x00418890 receives the source string in EAX.
extern "C" char* __cdecl CopyAssetPath_00418850(const char* path) {
    data_00497c38[0] = '\0';
    return strcat(data_00497c38, path);
}
