#include "../../layout/ltcg/input_recorder_dependencies.hpp"

#pragma code_seg(".text$07packet")
int RecorderPool::AppendPacket(
        unsigned short first, unsigned short second, unsigned short third) {
    storage.input_cursor->buttons = first;
    storage.input_cursor->value_02 = second;
    storage.input_cursor->value_04 = third;
    ++storage.input_cursor;
    return static_cast<int>(reinterpret_cast<unsigned char*>(storage.input_cursor)
        - reinterpret_cast<unsigned char*>(this)) / 6 >= 3600;
}
#pragma code_seg()
