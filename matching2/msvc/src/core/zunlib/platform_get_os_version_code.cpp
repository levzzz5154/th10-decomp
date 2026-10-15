#include "th10/source_views/process_00435c_0.hpp"
int Platform_GetOsVersionCode() {
    OSVERSIONINFOA version_info;
    memset(&version_info, 0, sizeof(version_info));
    version_info.dwOSVersionInfoSize = sizeof(version_info);
    GetVersionExA(&version_info);

    switch (version_info.dwPlatformId) {
    case 0:
        return 31;
    case 1:
        if (version_info.dwMajorVersion == 4)
            return version_info.dwMinorVersion != 0 ? 98 : 95;
        return version_info.dwMajorVersion * 100 + version_info.dwMinorVersion;
    case 2:
        if (version_info.dwMajorVersion == 5)
            return 2000;
        return (version_info.dwMajorVersion * 100 + version_info.dwMinorVersion) * 10;
    default:
        return -1;
    }
}
