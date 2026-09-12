#include "th10/game/asset_buffer.hpp"

#include <cstring>

// 0x0040B480 - Append the requested name to the retail shared path buffer,
// load the complete file, release the slot's previous allocation exactly once,
// and publish the new buffer (including a null result on load failure).
unsigned char* AssetBuffer_ReplaceFromPath(
        AssetBufferSlot* slot, char* shared_path, const char* resource_name,
        AssetBufferLoadHook load_file, AssetBufferFreeHook free_file) {
    std::strcat(shared_path, resource_name);
    unsigned char* replacement = load_file(shared_path, 0);
    if (slot->data != 0) {
        free_file(slot->data);
        slot->data = 0;
    }
    slot->data = replacement;
    return replacement;
}
