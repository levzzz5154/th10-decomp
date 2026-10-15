// 0x00420870..0x00420A86: load the configuration file.
//
// The configuration starts from its defaults. A file that is missing, has
// out-of-range option bytes, another version or another size is replaced by
// the defaults again; a valid one also supplies the key configuration. The
// options in force are written to the log (unsynchronised display is latched
// in the application object) and the configuration is written back.
//
// The application object arrives on the stack and the path in EBX (the
// compiler's own convention for the single call in the entry point).
#include "th10/app/config_load_00420870.hpp"
#include <string.h>

#pragma code_seg(".text$00cload")
int GameApp_00420870::LoadConfig(const char* path) {
    int size;
    bool valid = false;

    GameConfig_InitializeDefaults(0, &g_application.config);
    char* file = Archive_LoadFile(path, &size, 1);
    if (file == 0) {
        g_log.Append(str_config_missing_reset);
    } else {
        memcpy(&g_application.config, file, sizeof(GameConfig));
        free(file);
        if (g_application.config.field_1a >= 2 || g_application.config.field_1b >= 3 ||
            g_application.config.field_1c >= 2 || g_application.config.field_1d >= 2 ||
            g_application.config.field_1e >= 3 || g_application.config.field_1f >= 3 ||
            g_application.config.version_marker != 0x100003 || size != sizeof(GameConfig)) {
            g_log.Append(str_config_invalid_reset);
        } else {
            memcpy(g_key_bindings_current, g_application.config.version_prefix, 18);
            valid = true;
        }
    }
    if (!valid)
        GameConfig_InitializeDefaults(0, &g_application.config);

    no_vsync = 0;
    if (config.flags & 4)
        g_log.Append(str_no_fog);
    if (config.flags & 1)
        g_log.Append(str_force_16bit_textures);
    if (config.field_1d)
        g_log.Append(str_window_mode);
    if (config.flags & 2)
        g_log.Append(str_force_reference_rasterizer);
    if (config.flags & 8)
        g_log.Append(str_no_directinput);
    if (config.flags & 0x10)
        g_log.Append(str_bgm_in_memory);
    if (config.flags & 0x20) {
        g_log.Append(str_no_vsync);
        g_application.no_vsync = 1;
    }
    if (config.flags & 0x40)
        g_log.Append(str_no_text_autodetect);

    if (File_WriteWholeFile(path, &g_application.config, sizeof(GameConfig)) != 0) {
        g_log.AppendLine(str_cannot_write_file_format, path);
        g_log.AppendLine(str_folder_not_writable);
        return -1;
    }
    return 0;
}
#pragma code_seg()
