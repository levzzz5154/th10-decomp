#pragma once

#include "th10/game/entity.hpp"

struct DatArchive;

const uint32_t kResourceArchiveCapacity = 20;

void Resource_ArchivePathForAsset(
    const char* asset_path, char archive_path[260]);

DatArchive* Resource_FindArchive(const char* asset_path);
bool Resource_RegisterArchive(const char* archive_path);
void Resource_CloseArchives();

uint8_t* Resource_LoadFile(const char* path, uint8_t* output);
uint32_t Resource_GetFileSize(const char* path);
