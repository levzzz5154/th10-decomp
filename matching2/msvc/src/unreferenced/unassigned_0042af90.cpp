// 0x0042AF90: free the pair held by the global at 0x47783C, then the record
// itself, then clear the global.
extern "C" void* g_score;
extern "C" void __cdecl crt_free(void* memory);
extern "C" void __cdecl crt_free_startup(void* memory);
extern "C" void FlushHolder(void) {
    void** record = (void**)g_score;
    if (record) {
        if (record[0]) { crt_free(record[0]); record[0] = 0; }
        if (record[1]) { crt_free(record[1]); record[1] = 0; }
        crt_free_startup(record);
    }
    g_score = 0;
}
