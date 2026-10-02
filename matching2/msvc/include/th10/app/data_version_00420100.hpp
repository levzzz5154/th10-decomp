#ifndef TH10_APP_DATA_VERSION_00420100_HPP
#define TH10_APP_DATA_VERSION_00420100_HPP

// The version file of the data archive, kept loaded for the whole run.
extern "C" char* data_0049238c;
extern "C" int data_00492388;             // its size

// 0x00420100: open th10.dat and load its version file; 0 on success, -1 with
// a logged error otherwise.
int __cdecl DataVersion_Load_00420100();

#endif
