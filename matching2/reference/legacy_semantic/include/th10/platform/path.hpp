#pragma once

// Decode the short obfuscated path/string used by retail 0x00417010.
const char* Path_DecodeXor(const unsigned char* encoded, char* decoded);
unsigned int Path_FindBasenameSlot(const char* path, const char* table,
                                   unsigned int count, unsigned int stride);
