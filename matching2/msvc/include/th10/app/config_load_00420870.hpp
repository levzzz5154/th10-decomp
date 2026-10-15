#ifndef TH10_APP_CONFIG_LOAD_00420870_HPP
#define TH10_APP_CONFIG_LOAD_00420870_HPP
#include <stddef.h>
#include "th10/game/large_initialization_state_00421f00.hpp"

// The application object at 0x00491C28, as far as the configuration load
// reaches it.
struct GameApp_00420870 {
    unsigned char reserved_000[0x120];
    GameConfig config;            // +0x120 (0x00491D48)
    unsigned char reserved_154[0x3B4 - 0x154];
    int no_vsync;                 // +0x3B4 (0x00491FDC)

    // 0x00420870: read the configuration file, fall back to the defaults when
    // it is missing or invalid, log the options in force and write the file
    // back. Returns -1 when the file cannot be written.
    __declspec(noinline) int LoadConfig(const char* path);
};
typedef char GameAppConfigOffset[offsetof(GameApp_00420870, config) == 0x120 ? 1 : -1];
typedef char GameAppVsyncOffset[offsetof(GameApp_00420870, no_vsync) == 0x3B4 ? 1 : -1];

// The 8 KiB diagnostic text log at 0x00474F70.
struct TextLog_00420870 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;

    char* Append(char* format, ...);        // 0x0044B810
    char* AppendLine(char* format, ...);    // 0x0044B8E0
};

extern "C" {
extern GameApp_00420870 g_application;
extern TextLog_00420870 g_log;
extern char g_key_bindings_current[];      // the key configuration in use (18 bytes)

// Log lines (Shift-JIS).
extern char str_config_missing_reset[];      // "no configuration data was found, so it was initialised"
extern char str_config_invalid_reset[];      // "the configuration data was invalid, so it was initialised again"
extern char str_no_fog[];      // "fog is suppressed"
extern char str_force_16bit_textures[];      // "16-bit textures are forced"
extern char str_window_mode[];      // "starting in window mode"
extern char str_force_reference_rasterizer[];      // "the reference rasteriser is forced"
extern char str_no_directinput[];      // "DirectInput is not used for pad and keyboard input"
extern char str_bgm_in_memory[];      // "the music is loaded into memory"
extern char str_no_vsync[];      // "no vertical synchronisation"
extern char str_no_text_autodetect[];      // "the text drawing environment is not detected automatically"
extern char str_cannot_write_file_format[];      // "the file cannot be written %s"
extern char str_folder_not_writable[];      // "is the folder write-protected, or is the disk full?"

char* __stdcall Archive_LoadFile(const char* name, int* out_size, int from_disk);
void __cdecl free(void* block);
}

char __fastcall GameConfig_InitializeDefaults(int unused, GameConfig* config);
int __stdcall File_WriteWholeFile(const char* path, const void* buffer, unsigned long size);

#endif
