// 0x00465A20: atexit destructor of the global GDI surface at 0x00474CB0.
struct GdiSurface_00436a30;
extern "C" GdiSurface_00436a30 g_font_atlas_surface;
bool __stdcall ReleaseSurface_00436a30(GdiSurface_00436a30* surface);

// Static-exit callback: the linked surface releaser receives this object in ESI.
#pragma code_seg(".text$05wrapper")
extern "C" __declspec(noinline) void __cdecl StaticExit_GdiSurface() {
    ReleaseSurface_00436a30(&g_font_atlas_surface);
}
#pragma code_seg()
