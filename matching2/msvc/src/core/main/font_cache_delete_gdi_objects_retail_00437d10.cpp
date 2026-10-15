struct GdiSurface_00436a30;
extern "C" GdiSurface_00436a30 g_font_atlas_surface;
bool __stdcall ReleaseSurface_00436a30(GdiSurface_00436a30* surface);
extern "C" int (__stdcall* imp_DeleteObject)(void* object);
extern "C" void* g_font_height_60[15];

// Release the shared drawing surface, then each cache handle in reverse order.
#pragma code_seg(".text$04bcleanup")
extern "C" __declspec(noinline) void __cdecl DeleteFontCacheObjects_00437d10() {
    ReleaseSurface_00436a30(&g_font_atlas_surface);
    int (__stdcall* delete_object)(void*) = imp_DeleteObject;
    delete_object(g_font_height_60[14]);
    delete_object(g_font_height_60[13]);
    delete_object(g_font_height_60[12]);
    delete_object(g_font_height_60[11]);
    delete_object(g_font_height_60[10]);
    delete_object(g_font_height_60[9]);
    delete_object(g_font_height_60[8]);
    delete_object(g_font_height_60[7]);
    delete_object(g_font_height_60[6]);
    delete_object(g_font_height_60[5]);
    delete_object(g_font_height_60[4]);
    delete_object(g_font_height_60[3]);
    delete_object(g_font_height_60[2]);
    delete_object(g_font_height_60[1]);
    delete_object(g_font_height_60[0]);
}
#pragma code_seg()
