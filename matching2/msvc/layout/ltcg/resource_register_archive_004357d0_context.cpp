// Compiler context only; the synthetic Open body exists to let native LTCG
// see both sides of the private ECX/EAX archive-open call. It is not the
// recovered 0x00434C30 implementation and is never exported as game code.
#include "../../src/unidentified/unassigned_004357d0.cpp"

#pragma code_seg(".text$00bopen")
bool DatArchiveRecord_004357D0::Open(const char* archive_path) {
    return archive_path != 0 && file != 0;
}
#pragma code_seg()

#pragma code_seg(".text$03context")
int __stdcall ResourceRegisterArchive004357D0CompilerContext(
        const char** archive_paths, int count) {
    int opened_count = 0;
    for (int index = 0; index < count; ++index)
        opened_count += Resource_RegisterArchive(archive_paths[index]);
    return opened_count;
}
#pragma code_seg()
