// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_44dee0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(ArchiveCursor4** c, int n) {
    int s = 0;
    for (int i = 0; i < n; ++i) s += c[i]->Close();
    return s;
}
#pragma code_seg()
