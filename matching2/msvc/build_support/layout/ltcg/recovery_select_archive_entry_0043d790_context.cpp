// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sound/recovery_select_archive_entry_0043d790.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoverySelectArchiveEntry0043D790CompilerContext(
        PathName* path, PlatformD790ArchiveOwner* owner) {
    return path->SelectArchiveEntry(owner);
}
#pragma code_seg()
