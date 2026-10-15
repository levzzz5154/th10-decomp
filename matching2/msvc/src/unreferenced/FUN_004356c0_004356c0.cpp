// 0x004356C0: install the FileInterface vtable (0x0046F210).
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster
// (layout/ltcg/file_interface_install.json).
// ??_7FileInterface@@6B@ lives at 0x0046F210.

struct FileInterface_004356c0 {
    void* vtable; // +0x00
    __declspec(noinline) void InstallVtable();
};
typedef char FileInterface_004356c0_size_must_fit[sizeof(FileInterface_004356c0) == 4 ? 1 : -1];

#pragma code_seg(".text$01install")
void FileInterface_004356c0::InstallVtable() {
    vtable = (void*)0x0046F210;
}
#pragma code_seg()
