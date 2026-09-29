struct GdiSurface_00436a30;
extern "C" GdiSurface_00436a30 data_00474cb0;
bool __stdcall ReleaseSurface_00436a30(GdiSurface_00436a30* surface);

// Static-exit callback: the linked surface releaser receives this object in ESI.
#pragma code_seg(".text$05wrapper")
extern "C" __declspec(noinline) void __cdecl ReleaseGlobalGdiSurface_00465a20() {
    ReleaseSurface_00436a30(&data_00474cb0);
}
#pragma code_seg()
