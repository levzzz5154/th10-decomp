#ifndef TH10_GAME_REPLAY_FILE_LOAD_0042A200_HPP
#define TH10_GAME_REPLAY_FILE_LOAD_0042A200_HPP
#include "th10/game/replay_stage_begin_0042a6a0.hpp"

extern "C" unsigned int g_globals_flags;     // game flags; 0x20 = replays come from the data archive

// The shared-handle file helpers (build_support/layout/units/file_581343.cpp, 0x0044B790).
int __stdcall asm_File_ProbeExists_0044b4d0(const char* path);
int __stdcall asm_File_OpenSharedRead_0044b6b0(const char* path);
int File_CloseProbeHandle();
void* __stdcall ReadShared_0044b790(unsigned int size);

// The archive helpers (src/archive).
extern "C" char* __stdcall Archive_LoadFile(const char* name, int* out_size, int from_disk);
extern "C" unsigned char* __stdcall DatDecrypt(unsigned char* data, int size, unsigned char key,
                                               unsigned char step, int block_size, int limit);
extern "C" unsigned char* __stdcall DecompressDatLzss_00435dc0(const unsigned char* source, int source_size,
                                                               unsigned char* destination,
                                                               unsigned int destination_size);

#endif
