// 0x00418C40..0x00418CBC: fill the game-configuration block with its defaults.
//
// The block is 0x34 bytes. It is zeroed first, then the version marker at
// +0x00 becomes 0x100003 with the three option bytes around it cleared, the
// window size pair at +0x16/+0x18 becomes 0x258, the enable bytes at
// +0x1B/+0x1C are turned on, capability bit 0x100 is raised in the flags dword
// at +0x30, and the 18-byte version prefix is copied in from the shared table
// at 0x00474E88. The statement order follows the retail schedule: MSVC
// materialises both byte constants through one register, which fixes where the
// zero stores sit relative to the two 0x258 shorts.

#include <string.h>

extern "C" char data_00474e88[];

struct GameConfig {
    int version_marker;            // +0x00
    char version_prefix[0x12];     // +0x04 .. +0x15
    unsigned short window_width;   // +0x16
    unsigned short window_height;  // +0x18
    unsigned char field_1a;        // +0x1A
    unsigned char field_1b;        // +0x1B
    unsigned char field_1c;        // +0x1C
    unsigned char field_1d;        // +0x1D
    unsigned char field_1e;        // +0x1E
    unsigned char field_1f;        // +0x1F
    unsigned char field_20;        // +0x20
    unsigned char field_21;        // +0x21
    unsigned char field_22;        // +0x22
    char unknown_23[0x0D];         // +0x23 .. +0x2F
    int flags;                     // +0x30
};

char __fastcall GameConfig_InitializeDefaults(int unused, GameConfig* config) {
    memset(config, 0, 0x34);
    config->field_1a = 0;
    config->version_marker = 0x100003;
    config->field_1d = 0;
    config->field_1e = 0;
    config->window_width = 0x258;
    config->window_height = 0x258;
    config->field_1b = 1;
    config->field_1c = 1;
    config->flags |= 0x100;
    memcpy(config->version_prefix, data_00474e88, 18);
    config->field_1f = 2;
    config->field_22 = 0;
    config->field_20 = 100;
    config->field_21 = 0x50;
    return 0;
}
