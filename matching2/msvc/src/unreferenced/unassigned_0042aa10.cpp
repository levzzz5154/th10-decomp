// 0x0042AA10..0x0042AA41 (50 bytes): initialise the replay header.
//
// Retail zeroes the nine dwords at +0x00..+0x20 through one zero register and
// one shared base, then stamps the record: the magic 0x72303174 ("t10r"), the
// version word 5 at +0x04 and the size 0x100 at +0x10.  The header arrives in
// EAX.  The magic and the version are the single-source record header the
// replay writer and the reader agree on.

#include <string.h>

struct ReplayHeader_0042aa10 {
    int magic;                             // +0x00
    unsigned short version;                // +0x04
    unsigned short unknown_06;             // +0x06
    int unknown_08;                        // +0x08
    int unknown_0c;                        // +0x0C
    int size;                              // +0x10
    int unknown_14;                        // +0x14
    int unknown_18;                        // +0x18
    int unknown_1c;                        // +0x1C
    int unknown_20;                        // +0x20

    __declspec(noinline) void Initialize();
};

#pragma code_seg(".text$01init")
void ReplayHeader_0042aa10::Initialize() {
    memset(this, 0, 0x24);
    magic = 0x72303174;
    version = 5;
    size = 0x100;
}
#pragma code_seg()
