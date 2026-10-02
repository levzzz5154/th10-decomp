// Complete 0x0043E460: find an empty resource-request slot and copy the name.
#include "th10/game/pause_initializer_00422ab0.hpp"
#pragma code_seg(".text$09registrar")
char* AnimationManager_0043e460::RegisterResource(const char* name, int resource, int parameter) {
    int index = 0;
    for (; index < 31; ++index) {
        if (records[index].resource == 0) {
            records[index].resource = resource;
            records[index].parameter = parameter;
            char* out = records[index].name;
            const char* text = name;
            while ((*out++ = *text++) != 0) {}
            records[index].state = 0;
            return const_cast<char*>(text);
        }
    }
    return (char*)(long)index;
}
#pragma code_seg()
