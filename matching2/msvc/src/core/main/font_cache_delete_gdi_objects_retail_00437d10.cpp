struct GdiSurface_00436a30;
extern "C" GdiSurface_00436a30 data_00474cb0;
bool __stdcall ReleaseSurface_00436a30(GdiSurface_00436a30* surface);
extern "C" int (__stdcall* imp_DeleteObject)(void* object);
extern "C" void* data_00491868[15];

// Release the shared drawing surface, then each cache handle in reverse order.
#pragma code_seg(".text$04bcleanup")
extern "C" __declspec(noinline) void __cdecl DeleteFontCacheObjects_00437d10() {
    ReleaseSurface_00436a30(&data_00474cb0);
    int (__stdcall* delete_object)(void*) = imp_DeleteObject;
    delete_object(data_00491868[14]);
    delete_object(data_00491868[13]);
    delete_object(data_00491868[12]);
    delete_object(data_00491868[11]);
    delete_object(data_00491868[10]);
    delete_object(data_00491868[9]);
    delete_object(data_00491868[8]);
    delete_object(data_00491868[7]);
    delete_object(data_00491868[6]);
    delete_object(data_00491868[5]);
    delete_object(data_00491868[4]);
    delete_object(data_00491868[3]);
    delete_object(data_00491868[2]);
    delete_object(data_00491868[1]);
    delete_object(data_00491868[0]);
}
#pragma code_seg()
