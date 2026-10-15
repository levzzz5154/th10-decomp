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

    GameConfig_InitializeDefaults(0, &data_00491c28.config);
    char* file = Archive_LoadFile(path, &size, 1);
    if (file == 0) {
        data_00474f70.Append(data_0046de7c);
    } else {
        memcpy(&data_00491c28.config, file, sizeof(GameConfig));
        free(file);
        if (data_00491c28.config.field_1a >= 2 || data_00491c28.config.field_1b >= 3 ||
            data_00491c28.config.field_1c >= 2 || data_00491c28.config.field_1d >= 2 ||
            data_00491c28.config.field_1e >= 3 || data_00491c28.config.field_1f >= 3 ||
            data_00491c28.config.version_marker != 0x100003 || size != sizeof(GameConfig)) {
            data_00474f70.Append(data_0046de48);
        } else {
            memcpy(data_00474e88, data_00491c28.config.version_prefix, 18);
            valid = true;
        }
    }
    if (!valid)
        GameConfig_InitializeDefaults(0, &data_00491c28.config);

    no_vsync = 0;
    if (config.flags & 4)
        data_00474f70.Append(data_0046de2c);
    if (config.flags & 1)
        data_00474f70.Append(data_0046de04);
    if (config.field_1d)
        data_00474f70.Append(data_0046dde4);
    if (config.flags & 2)
        data_00474f70.Append(data_0046ddbc);
    if (config.flags & 8)
        data_00474f70.Append(data_0046dd84);
    if (config.flags & 0x10)
        data_00474f70.Append(data_0046dd64);
    if (config.flags & 0x20) {
        data_00474f70.Append(data_0046dd4c);
        data_00491c28.no_vsync = 1;
    }
    if (config.flags & 0x40)
        data_00474f70.Append(data_0046dd28);

    if (File_WriteWholeFile(path, &data_00491c28.config, sizeof(GameConfig)) != 0) {
        data_00474f70.AppendLine(data_0046dd08, path);
        data_00474f70.AppendLine(data_0046dcb0);
        return -1;
    }
    return 0;
}
#pragma code_seg()
