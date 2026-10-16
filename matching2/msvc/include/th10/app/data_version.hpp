#ifndef TH10_APP_DATA_VERSION_00420100_HPP
#define TH10_APP_DATA_VERSION_00420100_HPP

// The version file of the data archive, kept loaded for the whole run.
extern "C" char* g_data_version_buffer;
extern "C" int g_data_version_size;             // its size

// 0x00420100: open th10.dat and load its version file; 0 on success, -1 with
// a logged error otherwise.
int __cdecl DataVersion_Load2();

#endif
