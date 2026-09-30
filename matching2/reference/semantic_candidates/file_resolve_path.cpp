// Behavioral candidate for 0x00435610 (121 bytes). Retail receives the source
// in EAX and destination in ECX; this ordinary C++ signature is unpromoted.
#include "th10/platform/file.hpp"

extern "C" char* __cdecl FirstByteSearch_00452730(const char* text, int character);
extern "C" char* __cdecl strrchr(const char* text, int character);
extern "C" __declspec(dllimport) DWORD __stdcall GetModuleFileNameA(
    HANDLE module, char* output, DWORD capacity);

void File_ResolvePath(const char* path, char output[260]) {
    if (FirstByteSearch_00452730(path, ':')) {
        // Any colon bypasses the module directory. Copy forward byte by byte,
        // including the current terminator, even when the ranges overlap.
        char byte;
        do {
            byte = *path++;
            *output++ = byte;
        } while (byte);
        return;
    }

    GetModuleFileNameA(0, output, 260);
    char* separator = strrchr(output, '\\');
    if (!separator)
        *output = 0;
    // Preserve the unconditional write, including address 1 on the failed
    // search path. Integer arithmetic avoids a C++ null-pointer increment.
    *reinterpret_cast<volatile char*>(reinterpret_cast<unsigned int>(separator) + 1) = 0;

    // Retain byte reads rather than a compiler-substituted strlen that may
    // inspect bytes beyond the terminator at a memory boundary.
    const volatile char* measured_path = path;
    unsigned int length = 0;
    do {
        ++length;
    } while (measured_path[length - 1]);
    while (*static_cast<volatile char*>(output))
        ++output;

    // Retail appends with forward dword copies followed by byte copies. Keep
    // the four-byte snapshot so partially overlapping buffers behave alike.
    while (length >= 4) {
        unsigned int word = static_cast<unsigned char>(path[0]) |
            (static_cast<unsigned int>(static_cast<unsigned char>(path[1])) << 8) |
            (static_cast<unsigned int>(static_cast<unsigned char>(path[2])) << 16) |
            (static_cast<unsigned int>(static_cast<unsigned char>(path[3])) << 24);
        output[0] = static_cast<char>(word);
        output[1] = static_cast<char>(word >> 8);
        output[2] = static_cast<char>(word >> 16);
        output[3] = static_cast<char>(word >> 24);
        path += 4;
        output += 4;
        length -= 4;
    }
    while (length--) {
        *output++ = *path++;
    }
}
