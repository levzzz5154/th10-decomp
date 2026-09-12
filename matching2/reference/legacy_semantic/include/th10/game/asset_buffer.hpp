#pragma once

struct AssetBufferSlot {
    unsigned char* data; // retail owner +0x14
};

typedef unsigned char* (*AssetBufferLoadHook)(const char* path, int flags);
typedef void (*AssetBufferFreeHook)(void* memory);

// Append a resource name to the shared path, load it, release the previous
// allocation, and publish the replacement.
unsigned char* AssetBuffer_ReplaceFromPath(
    AssetBufferSlot* slot, char* shared_path, const char* resource_name,
    AssetBufferLoadHook load_file, AssetBufferFreeHook free_file);
