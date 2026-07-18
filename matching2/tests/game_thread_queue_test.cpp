#include "th10/game/game_thread_queue.hpp"

#include <cassert>
#include <cstring>

int main() {
    unsigned char storage[0x8A00] = {};
    GameThread* thread = (GameThread*)storage;
    *(uint32_t*)(storage + 0x8974) = 11;
    *(uint32_t*)(storage + 0x8978) = 22;
    *(uint32_t*)(storage + 0x897C) = 33;
    *(uint32_t*)(storage + 0x8980) = 44;
    *(uint32_t*)(storage + 0x8988) = 55;
    const GameThreadQueueWord vector[3] = {101, 202, 303};
    GameThread_AppendRecord(thread, "capture", vector);
    unsigned char* record = storage + 0x76C;
    assert(*(uint32_t*)(storage + 0x896C) == 1);
    assert(std::strcmp((char*)record, "capture") == 0);
    assert(*(uint32_t*)(record + 0x40) == 101);
    assert(*(uint32_t*)(record + 0x44) == 202);
    assert(*(uint32_t*)(record + 0x48) == 303);
    assert(*(uint32_t*)(record + 0x4C) == 11);
    assert(*(uint32_t*)(record + 0x50) == 22);
    assert(*(uint32_t*)(record + 0x54) == 33);
    assert(*(uint32_t*)(record + 0x5C) == 44);
    assert(*(uint32_t*)(record + 0x60) == 0);
    assert(*(uint32_t*)(record + 0x64) == 55);

    GameThread_AppendFormatted(thread, vector, "stage-%d", 7);
    assert(std::strcmp((char*)(storage + 0x76C + 0x68), "stage-7") == 0);
    GameThread_AppendFormattedMarked(thread, vector, "marked-%s", "ok");
    assert(std::strcmp((char*)(storage + 0x76C + 2 * 0x68), "marked-ok") == 0);
    assert(*(uint32_t*)(storage + 0x764 + 2 * 0x68) == 1);

    *(uint32_t*)(storage + 0x896C) = 0x100;
    GameThread_AppendRecord(thread, "ignored", vector);
    assert(*(uint32_t*)(storage + 0x896C) == 0x100);
    return 0;
}
