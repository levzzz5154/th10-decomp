#ifndef TH10_PLATFORM_ARCHIVE_FILE_HPP
#define TH10_PLATFORM_ARCHIVE_FILE_HPP

// Shared native-LTCG definition: retail passes name in EAX and the other two
// arguments on the stack. Callers must share the loader's optimization scope.
extern "C" char* __stdcall Archive_LoadFile(const char* name, int* out_size,
                                           int from_disk);

#endif
