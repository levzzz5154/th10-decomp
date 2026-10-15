#include "th10/platform/startup_shortcut.hpp"
// 0x0043A290: load a shell link through IPersistFile and fetch its ANSI path.
#pragma code_seg(".text$02resolver")
__declspec(noinline) int __stdcall ResolveShortcutTarget(const char* shortcut, char* target, DWORD capacity) {
    if (!target)
        return 0;
    int resolved = 0;
    ShellLink* link;
    PersistFile* persist;
    CoInitialize(0);
    if (CoCreateInstance(&shellLinkClass, 0, 1, &shellLinkInterface, (void**)&link) >= 0) {
        if (link->vtable->QueryInterface(link, &persistFileInterface, (void**)&persist) >= 0) {
            WORD* widePath = (WORD*)Startup_New(capacity * sizeof(WORD));
            MultiByteToWideChar(0, 0, shortcut, -1, widePath, capacity);
            if (persist->vtable->Load(persist, widePath, 0) >= 0) {
                FindDataA findData;
                if (link->vtable->GetPath(link, target, capacity, &findData, 0) >= 0)
                    resolved = 1;
            }
            Startup_Free(widePath);
            persist->vtable->Release(persist);
        }
        link->vtable->Release(link);
    }
    CoUninitialize();
    return resolved;
}
#pragma code_seg()
